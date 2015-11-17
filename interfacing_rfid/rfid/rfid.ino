int count = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()){
    count = 0;
    while(Serial.available()){
      Serial.print((char)Serial.read());
      count++;
      delay(5);
    }
    Serial.print("\nLength: ");
    Serial.print(count);
    Serial.println();
  }
}
