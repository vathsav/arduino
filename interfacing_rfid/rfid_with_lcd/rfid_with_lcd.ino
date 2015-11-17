#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
char tag[] ="110077F445D7"; // Test Tag
int count;
char input[12];
boolean flag = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Initialized");
  Serial.println("Initialized");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Reset the input array
  for(int i = 0; i < 12; i++){
    input[i] = 0;
  }
  count = 0;
  if(Serial.available()) {
    while(Serial.available() && count < 12) {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    
    //Print the ID of the tag scanned
    for(int i = 0; i < 12; i++) {
        Serial.print(input[i]);
    }
    Serial.println();
    if(count == 12){
      count = 0;
      flag = true;
      while(count < 12) {
        if(input[count] == tag[count]) {
          flag = true;
        } else {
          flag = false;
          break;
        }
        count++;
      }
    }
    if (flag) {
      // Tag is valid
      Serial.println("Matched!");
      lcd.setCursor(0, 0);
      lcd.print("Matched");
    } else {
      Serial.println("Wrong Tag!");
      lcd.setCursor(0, 0);
      lcd.print("Wrong Tag");
    }
    // Display ID on LCD
    for(int i = 0; i < 12; i++){
      lcd.setCursor(i, 1);
      lcd.print(input[i]);
    }
    delay(1500);
    lcd.clear();
  }
}
