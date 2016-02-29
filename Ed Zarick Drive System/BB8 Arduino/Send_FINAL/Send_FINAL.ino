int potPin1 = 1;
int potPin2 = 2;
int potPin3 = 3;
int potPin4 = 4;
int potPin5 = 5;

int button1 = 3;
int button2 = 4;
int button3 = 5;
int button4 = 6;

int button1state = 0;
int button2state = 0;
int button3state = 0;
int button4state = 0;

int analogValue1;
int analogValue2;
int analogValue3;
int analogValue4;
int analogValue5;


int audio;

void setup()
{
 //Create Serial Object (9600 Baud)
 Serial.begin(19200);
 pinMode(button1, INPUT);
 pinMode(button2, INPUT);
 pinMode(button3, INPUT);
 pinMode(button4, INPUT);

}

void loop()
{

 
  
int val1 = map(analogRead(0), 0, 1023, 0, 180); 

int val2 = map(analogRead(1), 0, 1023, 0, 180);

int val3 = map(analogRead(2), 0, 1023, 0, 180);  

int val4 = map(analogRead(3), 0, 1023, 0, 50);

int val5 = map(analogRead(4), 0, 1023, 0, 180); 


button1state = digitalRead(button1);
button2state = digitalRead(button2);
button3state = digitalRead(button3);
button4state = digitalRead(button4);

if (button1state == HIGH) {
   audio=2;
} 

if (button2state == HIGH) {
   audio=6;
} 

if (button3state == HIGH) {
   audio=4;
} 

if (button4state == HIGH) {
   audio=5;
} 

Serial.write(',');
Serial.write(val1);
Serial.write(val2);
Serial.write(val3);
Serial.write(val4);
Serial.write(val5);
Serial.write(audio);



delay(25);
audio=1;  
  


}
