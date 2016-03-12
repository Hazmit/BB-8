// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            2
#define NUMPIXELS      5

// define the pins used
#define CLK 13       // SPI Clock, shared with SD card
#define MISO 12      // Input data, from VS1053/SD card
#define MOSI 11      // Output data, to VS1053/SD card
#define BREAKOUT_RESET  7      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    6      // VS1053 Data/command select pin (output) XDCS
#define CARDCS 4     // Card chip select pin SDCS
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  
SoftwareSerial mySerial(9, 8); // RX, TX

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int lights;
int sound = 0;
long lights2 = 0;
int soundnumber = 0;

char posarray[7];
int playaudio=0;
int  i;

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 100;           // interval at which to blink (milliseconds)
int ledState = LOW; 

void setup() {
  Serial.begin(9600);
  
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
  SD.begin(CARDCS);    // initialise the SD card
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
  mySerial.begin(9600);
  
  pixels.begin(); // This initializes the NeoPixel library.
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
//  mySerial.println("TEST");
//  Serial.print(mySerial.read());
  if(mySerial.available()) {
    if(mySerial.read() == ',') {
      Serial.print("Received Something (");
      while(mySerial.available() >= 6)  {
        
        for(i = 0; i < 7; i ++) {  
          posarray[i] = mySerial.read();  
        }
      }
      Serial.print(posarray[5]);
      Serial.println(")");
    }
    lights2 = posarray[5];
  }

  delay(10);
  
  if(lights2 == '1') {
    Serial.println("Running Light Test");
    testLights(); 
  }
  
  if (lights2 == '6') {
    Serial.println("Running Theatre Chase");
    theaterChase(strip.Color(127, 127, 127), 50); // White
    
    pixels.show();
    lights2 = 1;
    
    // Play one file, don't return until complete
    Serial.println(F("Playing track 001"));
    musicPlayer.playFullFile("track001.mp3");
    // Play another file in the background, REQUIRES interrupts!
    Serial.println(F("Playing track 002"));
    musicPlayer.startPlayingFile("track002.mp3");
  }

  if (lights<100) {
    pixels.setPixelColor(0, pixels.Color(255,0,0));
    pixels.setPixelColor(1, pixels.Color(0,0,255));
    pixels.setPixelColor(2, pixels.Color(255,0,0));
    pixels.setPixelColor(14, pixels.Color(0,0,255));
    pixels.setPixelColor(15, pixels.Color(255,0,0));
  }

  if ((lights<200)&&(lights>100)) {
    pixels.setPixelColor(0, pixels.Color(0,0,255));
    pixels.setPixelColor(1, pixels.Color(255,0,0));
    pixels.setPixelColor(2, pixels.Color(0,0,255));

    pixels.setPixelColor(14, pixels.Color(255,0,0));
    pixels.setPixelColor(15, pixels.Color(0,0,255));
  }

  pixels.setPixelColor(8, pixels.Color(0,0,255));
  pixels.setPixelColor(9, pixels.Color(0,0,255));

  if (lights>100) {
    pixels.setPixelColor(10, pixels.Color(0,0,255));
  }

  if (lights>200) {
    pixels.setPixelColor(11, pixels.Color(0,0,255));
  }

  if (lights>300) {
    pixels.setPixelColor(12, pixels.Color(0,0,255));
  }

  if (lights>400) {
    pixels.setPixelColor(13, pixels.Color(0,0,255));
  }

  if (lights>500) {
    pixels.setPixelColor(10, pixels.Color(0,0,0));
    pixels.setPixelColor(11, pixels.Color(0,0,0));
    pixels.setPixelColor(12, pixels.Color(0,0,0));
    pixels.setPixelColor(13, pixels.Color(0,0,0));
  }
  
  pixels.setPixelColor(15, pixels.Color(255,0,0));
  pixels.setPixelColor(3, pixels.Color(0,0,255));
  pixels.setPixelColor(4, pixels.Color(255,0,0));
  pixels.setPixelColor(5, pixels.Color(0,0,255));
  pixels.setPixelColor(6, pixels.Color(0,0,255));

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      pixels.setPixelColor(7, pixels.Color(0,0,255));

      ledState = HIGH;
    } 
    else {
      pixels.setPixelColor(7, pixels.Color(0,0,0));

      ledState = LOW;
    }
  }

  pixels.show(); // This sends the updated pixel color to the hardware.
  lights++;
  if (lights>600){
    lights=0;
  } 
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void testLights() {
  mySerial.print('ACK');
  
  for (int i=1; i<=5; i++) {
    strip.setPixelColor(i, pixels.Color(0,255,0));
  }
  strip.show();
  delay(5000);
}

