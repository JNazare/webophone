#include <Event.h>
#include <Timer.h>
#include <Keypad.h>

// KEYPAD SETUP
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] =
 {{'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}};
 
byte rowPins[ROWS] = {
 8, 6, 12, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  9, 10, 5}; // connect to the column pinouts of the keypad
 
// TIMER SETUP
Timer t;

// CONTROL KEY SETUP
char ctrlKey = KEY_LEFT_GUI; 
char tabKey = KEY_TAB;
char returnKey = KEY_RETURN;

int count=0;
int numTabs=15;
String phoneNum=String("");
boolean openedSkype=false;
boolean openedDialpad=false;
boolean placedCall=false;
 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  t.every(10000, openSkype);
}

void loop() {
  t.update();
  char key = keypad.getKey();
  if(phoneNum.length()==10){
    Serial.println("Placing call...");
    placeCall();
    phoneNum = "";
  }
  if (key != NO_KEY){
    Keyboard.print(key);
    phoneNum = phoneNum + key;
    count = count + 1;
    delay(100);
  }
}

void openSkype() {
  if(openedSkype==false){
    Serial.println("Opening Skype...");
    Keyboard.press(ctrlKey);
    Keyboard.press('1');
    delay(100);
    Keyboard.releaseAll();
    delay(2500);
    openedSkype=!openedSkype;
  }
  openDialpad();
}

void openDialpad(){
  if(openedDialpad==false){
    Serial.println("Opening Dialpad...");
    Keyboard.press(ctrlKey);
    Keyboard.press('2');
    delay(100);
    Keyboard.releaseAll();
    openedDialpad=!openedDialpad;
  }
}

void placeCall(){
  if(placedCall==false){
    for (int tab = 0; tab < numTabs; tab++) {
      Keyboard.press(tabKey);
      Keyboard.releaseAll();
    }
    Keyboard.press(returnKey);
    Keyboard.releaseAll();
    placedCall=!placedCall;
  }
}
