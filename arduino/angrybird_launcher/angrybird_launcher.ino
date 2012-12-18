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
  myservo.write(120);  // pin unlatched
  delay(3000);
  myservo.write(70);  // pin latched
}

void loop(){
  buttonState = digitalRead(buttonPin);
  Serial.print("The button state is ");
  Serial.println(buttonState);
  if (buttonState == 1 && ignoreButtonPush == false) {
    ignoreButtonPush = true;
    trapSprung();
    delay(3000);
    buttonState = digitalRead(buttonPin);
  }
  if (buttonState == 1 && ignoreButtonPush == true) {
    ignoreButtonPush = false; // now trap is reset
    trapReset();
    delay(3000);
    buttonState = digitalRead(buttonPin);
  }
 }   

void trapSprung() {
  Serial.print("Laucher FIRE");
  digitalWrite(ledPin, HIGH);
  myservo.write(120); //pin unlatched
  delay(3000);
}
  
void trapReset() {
  Serial.print("Launcher reloaded");
  digitalWrite(ledPin, LOW);
  myservo.write(70); //pin latched
  delay(3000);
}
