void setup() {
  for(int i = 2; i <= 9; i++){
    pinMode(i, INPUT);
  }
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  readSensor();
  delay(100);
}

void readSensor() {
  byte result   = 0b00000000;
  byte left     = 0b11111000;
  byte right    = 0b00011111;
  byte straight = 0b00011000;
  
  for(int j = 2; j <= 9; j++){
    if(digitalRead(j) == HIGH){
      result |= (1 << j-2);
    }
  }
  if(result == left) {
    digitalWrite(10, HIGH);
    digitalWrite(11,  LOW);
  } else if(result == right) {
    digitalWrite(10,  LOW);
    digitalWrite(11, HIGH);
  } else if(result == straight) {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  } else {
    digitalWrite(10, LOW);
    digitalWrite(9,  LOW);
  }
}
