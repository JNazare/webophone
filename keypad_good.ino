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

// VARIABLE SETUP
int count=0;
int numTabs=15;
boolean openedSkype=false;
String phoneNum=String("");

// KEYPAD CREATION
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  t.every(10000, openSkype); // try to open Skype every 10 seconds
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

// Open Skype and the Skype dialpad
void openSkype() {
  // open skype if the arduino has not opened Skype before
  if(openedSkype==false){
    Serial.println("Opening Skype...");
    Keyboard.press(ctrlKey);
    Keyboard.press('1');
    delay(100);
    Keyboard.releaseAll();
    delay(3000);
    openedSkype=!openedSkype;
  }
  // regardless, try to open the dialpad
  openDialpad();
}

// Open the Skype dialpad
void openDialpad(){
    Serial.println("Opening Dialpad...");
    Keyboard.press(ctrlKey);
    Keyboard.press('2');
    delay(100);
    Keyboard.releaseAll();
}

// Why is placed call here?
void placeCall(){
    for (int tab = 0; tab < numTabs; tab++) {
      Keyboard.press(tabKey);
      Keyboard.releaseAll();
    }
    Keyboard.press(returnKey);
    Keyboard.releaseAll();
}
