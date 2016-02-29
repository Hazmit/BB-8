// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      16

SoftwareSerial mySerial(2, 3); // RX, TX

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
int lights;
int sound = 0;
long lights2 = 0;
int soundnumber=0;


char posarray[7];
int playaudio=0;
int  i;

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 100;           // interval at which to blink (milliseconds)
int ledState = LOW; 

void setup() {
  
  Serial.begin(19200);

  mySerial.begin(19200);

  pixels.begin(); // This initializes the NeoPixel library.
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
}

void loop() {

Serial.print(lights2);

if(mySerial.read() == ','){
while(mySerial.available() >= 6)  {
  
    for(i = 0; i < 7; i ++) {         
      
      
        posarray[i] = mySerial.read();      
}
    }
}

delay(10);
lights2 = posarray[5];




if (lights2 == 6) {
  
theaterChase(strip.Color(127, 127, 127), 50); // White

pixels.show();  
lights2 = 1;
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
    } else {
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

