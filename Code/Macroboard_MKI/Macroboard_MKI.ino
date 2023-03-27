#include <Keypad.h>
#include <Keyboard.h>

char MODE = 0;
char LEDMODE = 1;
enum Color { red, green, blue, black };
Color ledColor = blue;

//Keypad
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'3','2','1','0'},
  {'7','6','5','4'},
  {'B','A','9','8'}
};

byte rowPins[ROWS] = {8,7,6};
byte colPins[COLS] = {5,4,3,2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// rotary encoder
int state1, lastState1;
int state2, lastState2;
int counter1 = 0, counter2 = 0;
#define ROTARYPIN1A 10
#define ROTARYPIN1B 16
#define ROTARYPIN2A 14
#define ROTARYPIN2B 15
#define ROTARYCLICKPIN1 9
#define ROTARYCLICKPIN2 A0

// LED
#define LEDBLUE A1
#define LEDGREEN A3
#define LEDRED A2 
char valueBlue = 255;
char valueRed = 0;
char valueGreen = 0;

void setup() {
  //rotary encoder
  pinMode(ROTARYPIN1A, INPUT_PULLUP);
  pinMode(ROTARYPIN1B, INPUT_PULLUP);
  pinMode(ROTARYPIN2A, INPUT_PULLUP);
  pinMode(ROTARYPIN2B, INPUT_PULLUP);
  pinMode(ROTARYCLICKPIN1, INPUT_PULLUP);
  pinMode(ROTARYCLICKPIN2, INPUT_PULLUP);
  lastState1 = digitalRead(ROTARYPIN1A);
  lastState2 = digitalRead(ROTARYPIN2A);

  //keyboard
  Keyboard.begin();

  //LED
  pinMode(LEDBLUE, OUTPUT);
  pinMode(LEDGREEN, OUTPUT);
  pinMode(LEDBLUE, OUTPUT);
  setLight(ledColor);
}

void loop() {
  rotaryUpdate();
  
  if (!digitalRead(ROTARYCLICKPIN1)) {
    doClick('X');
    delay(500);
  }
  if (!digitalRead(ROTARYCLICKPIN2)) {
    doClick('Y');
    delay(500);
  }

  char key = customKeypad.getKey();
  if (key) {
    doClick(key);
  }
}

void rotaryUpdate() {
  state1 = digitalRead(ROTARYPIN1A);
  state2 = digitalRead(ROTARYPIN2A);

  if (state1 != lastState1) {
    if (digitalRead(ROTARYPIN1B) != state1) {
      if (counter1 < 255) counter1++;
      Serial.print("Counter1: ");
      Serial.println(counter1);
    }
    else {
      if (counter1 > 0) counter1--;
      Serial.print("Counter1: ");
      Serial.println(counter1);
    }
  }
  lastState1 = state1;

  if (state2 != lastState2) {
    if (digitalRead(ROTARYPIN2B) != state2) {
      if(counter2 < 255) { counter2++; } 
      Serial.print("Counter2: ");
      Serial.println(counter2);
    }
    else {
      if (counter2 > 0) { counter2--; }
      Serial.print("Counter2: ");
      Serial.println(counter2);
    }
  }
  lastState2 = state2;
}

void doClick(char key) {
  if (MODE == 0) {
    switch(key) {
      case '0':
        Serial.println("0 MODE: 0");
        break;
      case '1':
        Serial.println("1 MODE: 0");
        break;
      case '2':
        Serial.println("2 MODE: 0");
        break;
      case '3':
        Serial.println("3 MODE: 0");
        break;
      case '4':
        Serial.println("4 MODE: 0");
        break;
      case '5':
        Serial.println("5 MODE: 0");
        break;
      case '6':
        Serial.println("6 MODE: 0");
        break;
      case '7':
        Serial.println("7 MODE: 0");
        break;
      case '8':
        Serial.println("8 MODE: 0");
        break;
      case '9':
        Serial.println("9 MODE: 0");
        break;
      case 'A':
        Serial.println("A MODE: 0");
        break;
      case 'B':
        Serial.println("B MODE: 0");
        break;
    }
  }
  else if (MODE == 1) {
    switch(key) {
      case '0':
        Serial.println("0 MODE: 1");
        shortCut(key);
        break;
      case '1':
        Serial.println("1 MODE: 1");
        break;
      case '2':
        Serial.println("2 MODE: 1");
        break;
      case '3':
        Serial.println("3 MODE: 1");
        break;
      case '4':
        Serial.println("4 MODE: 1");
        break;
      case '5':
        Serial.println("5 MODE: 1");
        break;
      case '6':
        Serial.println("6 MODE: 1");
        break;
      case '7':
        Serial.println("7 MODE: 1");
        break;
      case '8':
        Serial.println("8 MODE: 1");
        break;
      case '9':
        Serial.println("9 MODE: 1");
        break;
      case 'A':
        Serial.println("A MODE: 1");
        break;
      case 'B':
        Serial.println("B MODE: 1");
        break;
    }
  }
  if (key == 'X') {
    Serial.println("X");
    LEDMODE = ( LEDMODE + 1 ) % 2;
    setLight(ledColor);
  }
  else if (key == 'Y') {
    MODE = (MODE + 1) % 2;
    Serial.print("Mode switched to: ");
    Serial.println(int(MODE));
    if (MODE == 0) {
      ledColor = blue;
      setLight(ledColor);
    }
    else if (MODE == 1) {
      ledColor = green;
      setLight(ledColor);
    }
  }
}

void setLight(Color color) {
  char valueRed, valueGreen, valueBlue;
  if (LEDMODE == 0) {
    digitalWrite(LEDRED, LOW);
    digitalWrite(LEDGREEN, LOW);
    digitalWrite(LEDBLUE, LOW);
    return;
  }
  switch (color) { 
    case red:
      digitalWrite(LEDRED, HIGH);
      digitalWrite(LEDGREEN, LOW);
      digitalWrite(LEDBLUE, LOW);
      break;
    case green:
      digitalWrite(LEDRED, LOW);
      digitalWrite(LEDGREEN, HIGH);
      digitalWrite(LEDBLUE, LOW);
      break;
    case blue:
      digitalWrite(LEDRED, LOW);
      digitalWrite(LEDGREEN, LOW);
      digitalWrite(LEDBLUE, HIGH);
      break;
    case black:
      digitalWrite(LEDRED, LOW);
      digitalWrite(LEDGREEN, LOW);
      digitalWrite(LEDBLUE, LOW);
      break;
  }
}

void shortCut(char key) {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(key);
  delay(100);
  Keyboard.releaseAll();
}
