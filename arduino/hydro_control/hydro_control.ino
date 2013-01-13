/* Command List
A - turn light on/off
B - turn pump on/off
C - get water temp
D - get air temp
*/

int AC1_pin = 7; // first tail (light)
int AC2_pin = 8; // second tail (pump)

char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character

void setup() {
    Serial.begin(9600);
    Serial.write("Power On");
    pinMode(AC1_pin, OUTPUT); //white
    pinMode(AC2_pin, OUTPUT); //yellow
}

void loop() {

 String content = "";
  char character;

  while(Serial.available()) {
      character = Serial.read();
      content.concat(character);
  }

 if (content == "A") {
    Serial.println(content);
    digitalWrite (AC1_pin, HIGH);
  }

 if (content == "a") {
    Serial.println(content);
    digitalWrite (AC1_pin, LOW);
  }

 if (content == "B") {
    Serial.println(content);
    digitalWrite (AC2_pin, HIGH);
  }

 if (content == "b") {
    Serial.println(content);
    digitalWrite (AC2_pin, LOW);
  }


}
