/* Angrybird (or any other projectile) launcher.  Basically a catapult. Designed by my 6yr old, decorated by my 4yr old, programmed by me (cutting and pasting code from the web) */

#include <Servo.h> 
Servo myservo;

const int buttonPin = 12;
const int ledPin = 4;
int buttonState = 0;
boolean ignoreButtonPush = false; 

void setup(){
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  myservo.attach(9);
  // numbers close to 180 mean pin is all the way released
  // numbers close to 0 mean pin is all the way engaged
  // 
  myservo.write(120);  // move pin back out of way
  delay(3000);
  myservo.write(70);  // set pin in lock position
}

void loop(){
  buttonState = digitalRead(buttonPin);
  Serial.print("The button state is ");
  Serial.println(buttonState);
  if (buttonState == 1 && ignoreButtonPush == false) {
    ignoreButtonPush = true;
    // set trap
    trapSprung();
  }
 }   

void trapSprung() {
  Serial.print("Mouse caught");
  digitalWrite(ledPin, HIGH);
  myservo.write(120); //release pin
}
  
