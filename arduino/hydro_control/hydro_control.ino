#include <OneWire.h>

/* Command List
A - turn light on/off
B - turn pump on/off
C - get water temp (DS18S20)
D - get air temp
*/

int WaterTemp_Pin = 2; //DS18S20 Signal Water temp
int AC1_pin = 7; // first tail (light)
int AC2_pin = 8; // second tail (pump)

//Temperature chip i/o
OneWire ds(WaterTemp_Pin); // on digital pin 2

void setup() {
    Serial.begin(9600);
    Serial.write("Power On");
    pinMode(AC1_pin, OUTPUT); //white
    pinMode(AC2_pin, OUTPUT); //yellow
}

void loop() {
  String content = ""; //var for serial
  char character; // var for serial

 // listen for input from serial
 while(Serial.available()) {
      character = Serial.read();
      content.concat(character);
  }

 // Light Control
 if (content == "A") {
    Serial.print(content);
    Serial.println(":ACK");
    digitalWrite (AC1_pin, HIGH);
  }

 if (content == "a") {
    Serial.print(content);
    Serial.println(":ACK");
    digitalWrite (AC1_pin, LOW);
  }

 // Pump Control
 if (content == "B") {
    Serial.print(content);
    Serial.println(":ACK");
    digitalWrite (AC2_pin, HIGH);
  }

 if (content == "b") {
    Serial.print(content);
    Serial.println(":ACK");
    digitalWrite (AC2_pin, LOW);
  }

 // Water Temperature
 if (content == "C") {
    float temperature = getTemp();
    Serial.print(content);
    Serial.print(":");
    Serial.println(temperature);
  }


}


float getTemp(){
 //returns the temperature from one DS18S20 in DEG Celsius

 byte data[12];
 byte addr[8];

 if ( !ds.search(addr)) {
   //no more sensors on chain, reset search
   ds.reset_search();
   return -1000;
 }

 if ( OneWire::crc8( addr, 7) != addr[7]) {
   Serial.println("CRC is not valid!");
   return -1000;
 }

 if ( addr[0] != 0x10 && addr[0] != 0x28) {
   Serial.print("Device is not recognized");
   return -1000;
 }

 ds.reset();
 ds.select(addr);
 ds.write(0x44,1); // start conversion, with parasite power on at the end

 byte present = ds.reset();
 ds.select(addr);  
 ds.write(0xBE); // Read Scratchpad

 
 for (int i = 0; i < 9; i++) { // we need 9 bytes
  data[i] = ds.read();
 }
 
 ds.reset_search();
 
 byte MSB = data[1];
 byte LSB = data[0];

 float tempRead = ((MSB << 8) | LSB); //using two's compliment
 float TemperatureSum = tempRead / 16;
 
 return TemperatureSum;
 
}
