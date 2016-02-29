
#include <VarSpeedServo.h>


int pos1;
int pos2;
int pos3;
int pos4;
int pos5;
int mappos1;
int mappos2;
int mappos3;
int mappos4;
int mappos5;
int map2pos1;
int map2pos3;
int audiorcv;
int posarray[8];
int i;


//Define Pins
int servo1Pin = 9;
int servo2Pin = 11;
int servo3Pin = 10;
int servo4Pin = 6;
int servo5Pin = 5;




//Create Servo Object
VarSpeedServo servo1;
VarSpeedServo servo2;
VarSpeedServo servo3;
VarSpeedServo servo4;
VarSpeedServo servo5;

void setup()
{
//Start Serial
Serial.begin(19200);

 
 //Attaches the Servo to our object
 servo1.attach(servo1Pin);
 servo2.attach(servo2Pin);
 servo3.attach(servo3Pin);
 servo4.attach(servo4Pin);
 servo5.attach(servo5Pin);
 

 servo4.slowmove(25, 255);

}


void loop() {


if(Serial.read() == ','){
while(Serial.available() >= 6)  {
  
    for(i = 0; i < 7; i ++) {         
      
      
        posarray[i] = Serial.read();      
}
    }
  

}


pos1 = map(posarray[0], 0, 180, 180, 30); //Dome Tilt
pos2 = map(posarray[1], 0, 180, 0, 155); //Dome Spin
pos3 = map(posarray[2], 0, 180, 40, 140); //Pend Tilt
pos4 = map(posarray[3], 0, 50, 20, 50); //Drive
pos5 = map(posarray[4], 0, 180, 0, 180); //Body Spin


mappos1 = constrain(pos1, 40, 130);
mappos2 = constrain(pos2, 0, 180);
mappos3 = constrain(pos3, 40, 150);
mappos4 = constrain(pos4, 0, 50);
mappos5 = constrain(pos5, 0, 180);

/*
map2pos3 = ((mappos4 - 25)*(1.3));
map2pos1 = (mappos1 + map2pos3);
map2pos1 = constrain(map2pos1, 40, 130);
*/

audiorcv = posarray[5];
 
/*  
Serial.println(mappos1);
Serial.println(mappos2);
Serial.println(mappos3);
Serial.println(mappos4);
Serial.println(mappos5);
Serial.println();
*/

servo1.slowmove(mappos3, 20);
servo2.slowmove(mappos2, 80);
servo3.slowmove(mappos1, 20);
servo4.slowmove(mappos4, 5);
servo5.slowmove(mappos5, 255);


delay(10);

}
