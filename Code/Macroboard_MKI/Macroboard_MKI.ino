#include <Keypad.h>
#include <Keyboard.h>

//Keypad
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'}
};

byte rowPins[ROWS] = {8,7,6};
byte colPins[COLS] = {5,4,3,2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// rotary encoder
int state1, lastState1;
int state2, lastState2;
int counter1 = 0, counter2 = 0;
#define ROTARYPIN1A 16
#define ROTARYPIN1B 10
#define ROTARYPIN2A 15
#define ROTARYPIN2B 14
#define ROTARYCLICKPIN1 9
#define ROTARYCLICKPIN2 A0

// LED
#define LEDBLUE A3
#define LEDGREEN A2
#define LEDRED A1 
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
  setLight(valueRed, valueGreen,valueBlue,100);
}

void loop() {
  rotaryUpdate();
  
  if (!digitalRead(ROTARYCLICKPIN1)) {
    doClick('X');
  }
  if (!digitalRead(ROTARYCLICKPIN2)) {
    doClick('Y');
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
  switch(key) {
    case '0':
      Serial.println("0");
      shortCut(key);
      break;
    case '1':
      Serial.println("1");
      break;
    case '2':
      Serial.println("2");
      break;
    case '3':
      Serial.println("3");
      break;
    case '4':
      Serial.println("4");
      break;
    case '5':
      Serial.println("5");
      break;
    case '6':
      Serial.println("6");
      break;
    case '7':
      Serial.println("7");
      break;
    case '8':
      Serial.println("8");
      break;
    case '9':
      Serial.println("9");
      break;
    case 'A':
      Serial.println("A");
      break;
    case 'B':
      Serial.println("B");
      break;
    case 'X':
      Serial.println("X");
      break;
    case 'Y':
      Serial.println("Y");
      break;
  }
}

void setLight(char red, char green, char blue, char brightness) {
  analogWrite(LEDRED, red * brightness / 255.0);
  analogWrite(LEDGREEN, green * brightness /255.0);
  analogWrite(LEDBLUE, blue * brightness / 255.0);
}

void shortCut(char key) {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(key);
  delay(100);
  Keyboard.releaseAll();
}
