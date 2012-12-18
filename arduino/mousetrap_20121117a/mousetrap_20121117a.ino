/* First try on a mousetrap - basically receive signal from a switch/photocell/something, and activate a servo certain amount */

#include <Servo.h> 
Servo myservo;

const int buttonPin = 12;
const int ledPin = 4;
int buttonState = 0;

void setup(){
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  myservo.attach(9);
}

void loop(){
  buttonState = digitalRead(buttonPin);
  
  // delay(100);

  if(buttonState == 1) {
    Serial.print("The button state is ");
    Serial.println(buttonState);
    //light led
    digitalWrite(ledPin, HIGH);
    myservo.write(91);
  }
  if (buttonState == 0) {
    // set trap
    Serial.print("The button state is ");
    Serial.println(buttonState);
    digitalWrite(ledPin, LOW);
    myservo.write(100);
    delay(3000); // simulate move the motor for three seconds
    buttonState = 1;

  }
  return;
}


