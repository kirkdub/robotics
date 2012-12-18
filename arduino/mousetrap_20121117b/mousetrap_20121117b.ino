#include <Servo.h>
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 

/* First try on a mousetrap - basically receive signal from a switch/photocell/something, and activate a servo certain amount */

const int buttonPin = 12;
const int ledPin = 4;
int buttonState = 0;

void setup(){
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
}

void loop(){
  buttonState = digitalRead(buttonPin);
  
  Serial.print("The button state it ");
  Serial.println(buttonState);
  
  delay(100);

  if(buttonState == 1) {
    //light led
    digitalWrite(ledPin, HIGH);
    /* delay(500);
    digitalWrite(ledPin, LOW);
    delay(500); */
  } else {
    // set trap
    digitalWrite(ledPin, LOW);
    delay(3000); // simulate move the motor for three seconds
  }

  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
} 
