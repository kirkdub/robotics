int buzzerPin = 7;
int LED_B = 5; // NOTE is B
int LED_A = 4; // NOTE is A
int LED_G = 3; // NOTE is G
int LED_D = 2; // NOTE is D

#define NOTE_C6 1047
#define NOTE_D6 1175
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_G6 1568
#define NOTE_A6 1760
#define NOTE_B6 1976
#define NOTE_C7 2093

void setup() {
  pinMode(LED_B, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_D, OUTPUT);
}

// I need a function that take in a note name (BAGD) 
// and does a tone(), digitalWrite(), delay()

// lame version
int PlayNoteAndBlink_B() {
  tone(buzzerPin, NOTE_B6, 500);
  digitalWrite(LED_B, HIGH);
  delay(500);
  digitalWrite(LED_B, LOW);
}
int PlayNoteAndBlink_A() {
  tone(buzzerPin, NOTE_A6, 500);
  digitalWrite(LED_A, HIGH);
  delay(500);
  digitalWrite(LED_A, LOW);
}
int PlayNoteAndBlink_G() {
  tone(buzzerPin, NOTE_G6, 500);
  digitalWrite(LED_G, HIGH);
  delay(500);
  digitalWrite(LED_G, LOW);
}
int PlayNoteAndBlink_D() {
  tone(buzzerPin, NOTE_D6, 500);
  digitalWrite(LED_D, HIGH);
  delay(500);
  digitalWrite(LED_D, LOW);
}
void loop() {
  PlayNoteAndBlink_B();
  PlayNoteAndBlink_A();
  PlayNoteAndBlink_G();
  PlayNoteAndBlink_A();
  PlayNoteAndBlink_B();
  PlayNoteAndBlink_B();
  PlayNoteAndBlink_B();
  delay(500);
  PlayNoteAndBlink_A();
  PlayNoteAndBlink_A();
  PlayNoteAndBlink_A();
  delay(500);
  PlayNoteAndBlink_B();
  PlayNoteAndBlink_D();
  PlayNoteAndBlink_D();
  delay(500);
  PlayNoteAndBlink_B();
  PlayNoteAndBlink_A();
  PlayNoteAndBlink_G();
  PlayNoteAndBlink_A();
  PlayNoteAndBlink_B();
  PlayNoteAndBlink_B();
  PlayNoteAndBlink_B();
  PlayNoteAndBlink_B();
  PlayNoteAndBlink_A();
  PlayNoteAndBlink_A();
  PlayNoteAndBlink_B();
  PlayNoteAndBlink_A();
  PlayNoteAndBlink_G();
  delay(1000);
}


