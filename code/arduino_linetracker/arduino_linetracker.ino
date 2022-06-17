// Line tracker returns 1 if nothing is detected.
// Can be out of range, black, too dark, etc. ...
// Return 0 if reflection = white/wood.

#include <Wire.h>

const byte INPUT_LENGTH = 8;
//const byte INPUT_PIN[INPUT_LENGTH] = {PD5, PD6, PD7, PB0, PB1, PB2, PB3, PB4};
const byte INPUT_PIN[INPUT_LENGTH] = {12, 11, 10, 9, 8, 7, 6, 5};
byte input[INPUT_LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0};
//const byte IR_PIN = PB5;
const byte IR_PIN = 4;
const byte ADDRESS = 8;
volatile bool isRequest = false;

void requestEvent(){
  isRequest = true;
}

void i2cSlaveSend(byte dataToSend[], byte dataLength){
  int output = 0;
  for(byte i = 0; i < dataLength; i++){     // Converting array to int
    output |= ((dataToSend[i] & B1) << i);
  }
  Serial.print("output="); Serial.println(output, BIN);
  Wire.write(output); 
}

void readLinetracker(){
  for(byte i = 0; i < INPUT_LENGTH; i++){
    input[i] = digitalRead(INPUT_PIN[i]); 
    Serial.print("D"); Serial.print(i+1); Serial.print("="); Serial.print(input[i]); Serial.print(", ");
  }
  Serial.println();
}

void setup() {
  DDRD &= ~(B1111 << PD4);    // D4-D7 op input
  DDRB &= ~(B1111 << PB0);    // D8-D11 op input
  DDRB |= (1 << PB4);         // D12 op input
  digitalWrite(IR_PIN, HIGH); // Turn on the IR sensors, otherwise returns 1

  Wire.begin(ADDRESS);
  Wire.onRequest(requestEvent);
  
  Serial.begin(9600);
}

void loop() {
  readLinetracker();
  
  if(isRequest){
    i2cSlaveSend(input, INPUT_LENGTH);
    isRequest = false;
  }
}
