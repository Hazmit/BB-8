#include <FatReader.h>
#include <SdReader.h>
#include <avr/pgmspace.h>
#include "WaveUtil.h"
#include "WaveHC.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(14, 15); // RX, TX

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the filesystem on the card
FatReader f;      // This holds the information for the file we're play

WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

#define DEBOUNCE 100  // button debouncer

// this handy function will return the number of bytes currently free in RAM, great for debugging!   
int freeRam(void)
{
  extern int  __bss_end; 
  extern int  *__brkval; 
  int free_memory; 
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end); 
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval); 
  }
  return free_memory; 
} 

void sdErrorCheck(void)
{
  if (!card.errorCode()) return;
  putstring("\n\rSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  putstring(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}

const int buttonPin = 17;    // the number of the pushbutton pin
const int ledPin = 18;      // the number of the LED pin


int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin
int sound = 0;
long lights = 0;
int soundnumber=0;

int eye = 7; 
int psi = 6; 
int holo = 8; 
int sys1 = 9; 
 // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by



long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 10;    // the debounce time; increase if the output flickers

char posarray[7];
int playaudio=0;
int  i;


void setup() {
  // set up serial port
  Serial.begin(19200);
  putstring_nl("WaveHC with 6 buttons");
  mySerial.begin(19200);
  
  
   putstring("Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(freeRam());      // if this is under 150 bytes it may spell trouble!
  
  // Set the output pins for the DAC control. This pins are defined in the library
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
 
  // pin13 LED
  pinMode(13, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  
  pinMode(eye, OUTPUT);
  pinMode(psi, OUTPUT);
  pinMode(holo, OUTPUT);
  pinMode(sys1, OUTPUT);

  
  digitalWrite(eye, HIGH);
  digitalWrite(psi, HIGH);
  digitalWrite(holo, HIGH);
  digitalWrite(sys1, HIGH);
 
 
  digitalWrite(17, HIGH);
  digitalWrite(18, LOW);
  digitalWrite(19, HIGH);
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  

  
 
  //  if (!card.init(true)) { //play with 4 MHz spi if 8MHz isn't working for you
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    putstring_nl("Card init. failed!");  // Something went wrong, lets print out why
    sdErrorCheck();
    while(1);                            // then 'halt' - do nothing!
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
 
// Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {     // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                             // we found one, lets bail
  }
  if (part == 5) {                       // if we ended up not finding one  :(
    putstring_nl("No valid FAT partition!");
    sdErrorCheck();      // Something went wrong, lets print out why
    while(1);                            // then 'halt' - do nothing!
  }
  
  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(),DEC);     // FAT16 or FAT32?
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    putstring_nl("Can't open root dir!"); // Something went wrong,
    while(1);                             // then 'halt' - do nothing!
  }
  
  // Whew! We got past the tough parts.
  putstring_nl("Ready!");
  
  
  


        playcomplete("103.WAV");
 
    
  

  
}

void loop() {
  Serial.print(playaudio);
  
if(mySerial.read() == ','){
while(mySerial.available() >= 6)  {
  
    for(i = 0; i < 7; i ++) {         
      
      
        posarray[i] = mySerial.read();      
}
    }
}


playaudio = posarray[5];







       
      if (lights > 500) {
  
  
  // set the brightness of pin 9:
  analogWrite(psi, brightness);    

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  
  }
 delay(10);


lights++;      
  
  if (lights > 100) {
        digitalWrite(sys1, HIGH);
  }
   
  if (lights > 110) {
        digitalWrite(sys1, LOW);
  }
   
  if (lights > 115) {
        digitalWrite(sys1, HIGH);
  }
   
  if (lights > 130) {
        digitalWrite(sys1, LOW);
  }
  
  
 if (lights > 200) {
        digitalWrite(sys1, LOW);
  }
  
   if (lights > 500) {
        digitalWrite(sys1, HIGH);
  }
   if (lights > 505) {
        digitalWrite(sys1, LOW);
  }
   if (lights > 515) {
        digitalWrite(sys1, HIGH);
  }
   if (lights > 520) {
        digitalWrite(sys1, LOW);
  }
  
    if (lights > 540) {
        digitalWrite(sys1, HIGH);
  }
  
 if (lights > 800) {
        digitalWrite(sys1, LOW);
  }
   if (lights > 900) {
        digitalWrite(sys1, HIGH);
  }
   if (lights > 800) {
        digitalWrite(sys1, LOW);
  }
  
    if (lights > 1000) {
        digitalWrite(sys1, HIGH);
  }
  
 if (lights > 1200) {
        digitalWrite(sys1, LOW);
  }
     
       
     
        
        if (lights > 1500) {
            lights=0;
        } 
       
       
       
       
       
       
  
if (playaudio == 2) {
        
        
        if (sound==0) {
        playcomplete("1.WAV");
        }
        if (sound==1) {
        playcomplete("2.WAV");
        }
        
        if (sound==2) {
        playcomplete("3.WAV");
        }
        
        if (sound==3) {
        playcomplete("4.WAV");
        }
        if (sound==4) {
        playcomplete("5.WAV");
        }
        
        if (sound==5) {
        playcomplete("6.WAV");
        }
        
        if (sound==6) {
        playcomplete("7.WAV");
        }
        if (sound==7) {
        playcomplete("8.WAV");
        }
        
        if (sound==8) {
        playcomplete("9.WAV");
        }
        
        if (sound==9) {
        playcomplete("10.WAV");
        }
        if (sound==10) {
        playcomplete("11.WAV");
        }
        
        if (sound==11) {
        playcomplete("12.WAV");
        }
        
                
        
        sound++;
        
        if (sound==12) {
        sound=0;
        }
}

if (playaudio == 6) {
  playcomplete("100.WAV");
}  

if (playaudio == 4) {
  playcomplete("101.WAV");
} 

if (playaudio == 5) {
  playcomplete("102.WAV");
} 



playaudio = 0;
   
   
   
   
   
   
   
           
}       
        


    
   

  

 
  

  
  
  






// Plays a full file from beginning to end with no pause.
void playcomplete(char *name) {
  // call our helper to find and play this name
  playfile(name);
  while (wave.isplaying) {
  // do nothing while its playing
  }
  // now its done playing
}

void playfile(char *name) {
  // see if the wave object is currently doing something
  if (wave.isplaying) {// already playing something, so stop it!
    wave.stop(); // stop it
  }
  // look in the root directory and open the file
  if (!f.open(root, name)) {
    putstring("Couldn't open file "); Serial.print(name); return;
  }
  // OK read the file and turn it into a wave object
  if (!wave.create(f)) {
    putstring_nl("Not a valid WAV"); return;
  }
  
  // ok time to play! start playback
  wave.play();
}
