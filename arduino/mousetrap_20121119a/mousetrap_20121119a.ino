/* First try on a mousetrap - basically receive signal from a switch/photocell/something, and activate a servo certain amount */

#include <Servo.h> 
#include <Wire.h>

// Possible sensor addresses (suffix correspond to DIP switch positions)
#define SENSOR_ADDR_OFF_OFF  (0x26)
#define SENSOR_ADDR_OFF_ON   (0x22)
#define SENSOR_ADDR_ON_OFF   (0x24)
#define SENSOR_ADDR_ON_ON    (0x20)

// Set the sensor address here
const uint8_t sensorAddr = SENSOR_ADDR_ON_ON;

Servo myservo;
const int buttonPin = 12;
const int ledPinW = 4;
const int ledPinG = 3;
int buttonState = 0;
boolean ignoreButtonPush = false; 

void setup(){
  pinMode(buttonPin, INPUT);
  pinMode(ledPinW, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(90);  // Park the servo in stop position
  Wire.begin(); // Join the I2C bus as master
  
  // Turn on the sensor by configuring pin 1 of the GPIO expander to be an
  // output pin; the default output value is already HI so there's no need
  // to change it
  WriteByte(sensorAddr, 0x3, 0xFE);
}

void loop(){
  //buttonState = digitalRead(buttonPin);
  // need to replace the above with a function that detects proximity sensor
  uint8_t val;
  if (ReadByte(sensorAddr, 0x0, &val) == 0) {
    if (val & 0x2) {
      //Serial.println("Nothing detected");
      buttonState = 1; // Not sure if this is right
    } else {
      //Serial.println("Object detected");
      buttonState = 0;
    } 
  } else {
    Serial.println("Failed to read from sensor");
  }
  
  if (buttonState == 1 && ignoreButtonPush == false) {
    trapWait();
  }

  if (buttonState == 0 && ignoreButtonPush == false) {
    ignoreButtonPush = true;
    trapSprung();
  }
  
  if (buttonState == 1 && ignoreButtonPush == true) {
    trapReset();
  }
 }   

void trapWait() {
  Serial.println("Waiting for a mouse");
}

void trapSprung() {
  Serial.println("Mouse caught");
  digitalWrite(ledPinW, HIGH);  
  myservo.write(122); //set the position
  // delay(3000);
  // myservo.write(91); //stop the servo
}
  
void trapReset() {
  Serial.println("Mouse caught");
  // digitalWrite(ledPinW, HIGH);
  // Need to do a three second push and hold which will reset ignoreButtonPush to false
}

// Read a byte on the i2c interface
int ReadByte(uint8_t addr, uint8_t reg, uint8_t *data)
{
   // Do an i2c write to set the register that we want to read from
   Wire.beginTransmission(addr);
   Wire.write(reg);
   Wire.endTransmission();

   // Read a byte from the device
   Wire.requestFrom(addr, (uint8_t)1);
   if (Wire.available())
   {
      *data = Wire.read();
   }
   else
   {
      // Read nothing back
      return -1;
   }

   return 0;
}

// Write a byte on the i2c interface
void WriteByte(uint8_t addr, uint8_t reg, byte data)
{
   // Begin the write sequence
   Wire.beginTransmission(addr);

   // First byte is to set the register pointer
   Wire.write(reg);

   // Write the data byte
   Wire.write(data);

   // End the write sequence; bytes are actually transmitted now
   Wire.endTransmission();
}



