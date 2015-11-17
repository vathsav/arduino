/*
Done by Vathsav Harikrishnan 
 Date Started [28-03-2013]
 Date Finished [27-06-2013]
 
 > Arduino Uno
 > 4x4 Dot Matrix Keypad
 > 16x2 LCD (With Backlight - Optional)
 > Breadboard
 > Connecting Wires, Female Jumper Wires
 > Resistors
 > Potentiometer
 
 Layout of 4x4 Dot Matrix Keyboard:
 ^
 C R >
 o o o o
 o o o o
 o o o o
 o o o o
 
 [7] [8] [9] [/]
 [4] [5] [6] [*]
 [3] [2] [2] [-]
 [X] [0] [=] [+]
 
 Press X to clear the screen
 
                      1 1 1 1 1 1
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
 *-------------------------------*
 |                            2 +|  <--- Memory here
 |                               |  <--- Cursor set here
 *-------------------------------*
 
 */

#include <LiquidCrystal.h> //import lcd library
#include <Keypad.h> //import keypad library

LiquidCrystal lcd(5, 4, 3, 2, 1, 0); //lcd pins
const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

//define the keymap
char keys [ROWS] [COLS] = {
  {'7', '4', '1', 'X'},
  {'8', '5', '2', '0'},
  {'9', '6', '3', '='},
  {'/', '*', '-', '+'}
};
byte rowPins[ROWS] = {
  9 ,8 ,7 ,6}; //connect keypad ROW1, ROW2, ROW3, ROW4 to these arduino pins
byte colPins[COLS] = {
  13, 12, 11, 10}; //connect keypad COL1, COL2, COL3, COL4 to these arduino pins

//create the keypad
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//variables declaration
boolean valOnePresent = false;
boolean next = false;
boolean final = false;
String num1, num2;
int ans;
char op;

void setup(){
  lcd.begin(16,2);
  lcd.setCursor(2,0);
  lcd.print("Hello World!");
  delay(2500);
  lcd.clear(); //clears the LCD screen and positions the cursor in the upper-left corner. 
}

void loop(){
  char key = myKeypad.getKey();

  if (key != NO_KEY && (key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0')){
    if (valOnePresent != true){
      num1 = num1 + key;
      int numLength = num1.length();
      lcd.setCursor(15 - numLength, 0); //to adjust one whitespace for operator
      lcd.print(num1);
    }
    else {
      num2 = num2 + key;
      int numLength = num2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(num2);
      final = true;
    }
  }

  else if (valOnePresent == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+')){
    if (valOnePresent == false){
      valOnePresent = true;
      op = key;
      lcd.setCursor(15,0); //operator on right corner
      lcd.print(op);
    }
  }

  else if (final == true && key != NO_KEY && key == '='){
    if (op == '+'){
      ans = num1.toInt() + num2.toInt();
    }
    else if (op == '-'){
      ans = num1.toInt() - num2.toInt();
    }
    else if (op == '*'){
      ans = num1.toInt() * num2.toInt();
    }
    else if (op == '/'){
      ans = num1.toInt() / num2.toInt();
    }    
      lcd.clear();
      lcd.setCursor(15,0);
      lcd.autoscroll();
      lcd.print(ans);
      lcd.noAutoscroll();
  }
  else if (key != NO_KEY && key == 'X'){
    lcd.clear();
    valOnePresent = false;
    final = false;
    num1 = "";
    num2 = "";
    ans = 0;
    op = ' ';
  }
}
