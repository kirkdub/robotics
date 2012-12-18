/* Angrybird (or any other projectile) launcher.  Basically a catapult. Designed by my 6yr old, decorated by my 4yr old, programmed by me (cutting and pasting code from the web) */

#include <Servo.h> 
#include <Wire.h> 

// Possible sensor addresses (suffix correspond to DIP switch positions)
#define SENSOR_ADDR_OFF_OFF  (0x26)
#define SENSOR_ADDR_OFF_ON   (0x22)
#define SENSOR_ADDR_ON_OFF   (0x24)
#define SENSOR_ADDR_ON_ON    (0x20)

const uint8_t sensorAddr = SENSOR_ADDR_ON_ON; // Set photosensor address
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
  Wire.begin(); // Join the I2C bus as master

  // Turn on the sensor by configuring pin 1 of the GPIO expander to be an
  // output pin; the default output value is already HI so there's no need
  // to change it
  WriteByte(sensorAddr, 0x3, 0xFE);
}

void loop(){
  buttonState = digitalRead(buttonPin);
  Serial.print("The button state is ");
  Serial.println(buttonState);
  if (buttonState == 1 && ignoreButtonPush == false) {
    ignoreButtonPush = true;
    trapSprung();
    delay(1000);
    buttonState = digitalRead(buttonPin);
  }
  if (buttonState == 1 && ignoreButtonPush == true) {
    ignoreButtonPush = false; // now trap is reset
    trapReset();
    delay(1000);
    buttonState = digitalRead(buttonPin);
  }
 }   

void trapSprung() {
  Serial.print("Laucher FIRE");
  digitalWrite(ledPin, HIGH);
  myservo.write(120); //pin unlatched
  //delay(3000);
}
  
void trapReset() {
  Serial.print("Launcher reloaded");
  digitalWrite(ledPin, LOW);
  myservo.write(70); //pin latched
  //delay(3000);
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

