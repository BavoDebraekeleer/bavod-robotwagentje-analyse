#include <Wire.h>

// Arduino I2C Slave
#define SLAVE_ADDRESS 16
#define PAYLOAD_SIZE 2
// A5 / PC5 = SCL     // A4 / PC4 = SDA

//const int ECHO_PIN = PB0;
//const int TRIG_PIN = PD7;
const int ECHO_PIN = A0;
const int TRIG_PIN = A1;
const byte ADDRESS = 8;
volatile bool isRequest = false;
bool isDistanceCalculated = false;
long duration = 0;
int distance = 0;

void requestEvent(){
  isRequest = true;
}

// Function from https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
void calculateDistance(){
  isDistanceCalculated = false;
  digitalWrite(TRIG_PIN, LOW); // Clears the TRIG_PIN condition
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); // Sets the TRIG_PIN HIGH (ACTIVE) for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH); // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  Serial.print("Distance: "); // Displays the distance on the Serial Monitor
  Serial.print(distance);
  Serial.println(" cm");
  isDistanceCalculated = true;
}

void setup() {
  //pinModeAllToInput();    // Pin reset

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  
  Serial.begin(9600);
}

void loop() {
  calculateDistance();
  if(isRequest & isDistanceCalculated){
    Wire.write(distance & 255); 
    Wire.write(distance >> 8); 
    isRequest = false;
  }
}

void pinModeAllToInput(){
  DDRD &= ~(B11111100);
  DDRC &= ~(B01111111);
  DDRB &= ~(B00111111);
}
