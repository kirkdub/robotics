/* First try on a mousetrap - basically receive signal from a switch/photocell/something, and activate a servo certain amount */

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
  myservo.write(91);  
}

void loop(){
  buttonState = digitalRead(buttonPin);
  Serial.print("The button state is ");
  Serial.println(buttonState);
  if (buttonState == 0 && ignoreButtonPush == false) {
    ignoreButtonPush = true;
    // set trap
    trapSprung();
    //delay(3000); // simulate move the motor for three second
    //trapSprung = false;
    //myservo.write(91);
    //return;
  }
 }   

void trapSprung() {
  Serial.print("Mouse caught");
  digitalWrite(ledPin, HIGH);
  myservo.write(100); //start the servo
  delay(3000);
  myservo.write(91); //stop the servo
}
  
