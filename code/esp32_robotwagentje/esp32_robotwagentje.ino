#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h> // https://github.com/johnrickman/LiquidCrystal_I2C (install as zip)
#include <WiFi.h>              // Standard ESP32 Library
#include <PubSubClient.h>      // https://github.com/knolleary/pubsubclient (intall with library Manager)

// OLED code from Adafruit example for Monochrome OLEDs based on SSD1306 drivers
// Wifi and MQTT code from Maarten Luyts and from IoT Experiments

// VARIABLES -----------------------------------------------------------------------------------------------------
// WIFI Credentials
// Connect to Hotspot on mobile phone
const char* WIFI_SSID = ""; // Fill wifi SSID between quotes
const char* WIFI_PASS = ""; // Fill wifi pass between quotes
const char* NAAM = "robotwagentje";  // constant to make it easier to set the name for MQTT


//MQTT Information
const char* MQTT_SERVER = "";
const char* TOPIC_MODUS = "robotwagentje/modus";
const char* TOPIC_CMD = "robotwagentje/cmd";


// WIFI and MQTT class instances
WiFiClient espClient;
PubSubClient client(espClient);

// Buffer to store MQTT messages
char msg[4]; //we only need an array of 3 chars because the payload should be between 0-255,
char topic[4]; //but just in case, we take an extra char for an end sign like \0

const uint16_t PWM_FREQUENCY = 500;
const byte PWM_RESOLUTION = 8;
const byte PWM_MAX_DC = 255;


// Motor PWM Pin declarations
const byte PWM_CHANNEL_COUNT = 4;
const byte MOTOR_COUNT = 2;
byte MOTOR_PINS[PWM_CHANNEL_COUNT] = {18, 5, 2, 15}; //we use pin 2 and 5 as direction pin and pin 18 and 15 as speed pin
byte MOTOR_CHANNELS[PWM_CHANNEL_COUNT] = {0, 1, 2, 3};


// LED PWM Pin declarations - DO NOT CHANGE
const int LED_CHANNEL_COUNT = 4;
const int LED_COUNT = 4;

int LED_PINS[LED_COUNT] = {13, 12, 14, 27};
int LED_CHANNELS[LED_CHANNEL_COUNT] = {4, 5, 6, 7};
int LED_STATE[] = {0, 0, 0, 0};


// Linetracker
const byte LINETRACKER_LENGTH = 8;
byte linetracker[LINETRACKER_LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0};
int LINETRACKER_ADDRESS = 8;
int LINETRACKER_REQUEST_SIZE = 1;
byte linetrackerInput = B11111111;         // 1 geeft niks gedetecteerd of uit, dan doen we niks, dus dit is ook de default waarde.

// Distance sensors / afstandssensoren
int DISTANCE_ADDRESS = 16;
int DISTANCE_REQUEST_SIZE = 2;
int distance = 0;
const int MIN_DISTANCE = 10; //cm 


// I2C OLED Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };


//  Enums: Modi, commands and motor direction
enum MODI {                
    MANUAL,
    AUTO,
    PATTERN,
    MENU
};

enum COMMANDS {
    FORWARD,                
    RIGHT,
    LEFT,
    STOP,
};

enum MOTOR_DIRECTION {
    MOTOR_BACKWARDS = -1,
    MOTOR_STOP = 0,
    MOTOR_FORWARD = 1
};

byte modus = MENU;
byte previousModus = 0;
byte command = STOP;
byte previousCommand = 0;

byte drivingSpeed = 128;
const byte TURN_DELAY = 200; //ms

bool lineDeviationLeft = false;
bool lineDeviationRight = false;
bool lineLost = false;

// FUNCTIONS ------------------------------------------------------------------------------------------------------
// Function to setup wifi - DO NOT CHANGE
void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
  
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    //Display that we still are trying to connect
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    // Normaly the wifi will connect very fast. If it hangs reset the controller with EN button
    // This needs to be done after the controller is programmed
  
    // Print connection information
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

// Function to (re)connect to the MQTT server - DO NOT CHANGE
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(NAAM)) {//we replaced the literal by a string, so it is easier to configure
      Serial.println("connected");
      // Subscribe
      client.subscribe(TOPIC_MODUS);
      client.publish(TOPIC_MODUS, "connected topic modus");
      client.subscribe(TOPIC_CMD);
      client.publish(TOPIC_CMD, "connected topic command");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//This function is called when MQTT receives a message
void callback(char* topic, byte* message, unsigned int length) {
  memset(topic, '\0', sizeof(topic));   // clear the execisting data in the buffer
  memcpy(topic, (char*)topic, length);  // copy the byte array to char array
  Serial.print("topic: ");              // print msg (1/2)
  Serial.println(topic);                // print msg (2/2)
  
  memset(msg, '\0', sizeof(msg));       // clear the execisting data in the buffer
  memcpy(msg, (char*)message, length);  // copy the byte array to char array
  Serial.print("msg: ");                // print msg (1/2)
  Serial.println(msg);                  // print msg (2/2)
}

void oledSetup(){
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...
}

void oledScrollText(String text){
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  //display.println(F("scroll"));
  display.println(text);
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}

void i2cMasterRead(int slave_address, int dataLength, int *input){
  Wire.requestFrom(slave_address, 1);    

  while(Wire.available()) { 
    *input = Wire.read();
    Serial.print("input="); Serial.println(*input, BIN);
  }
  delay(200);
}

void readLinetrackerI2C(){
  Wire.requestFrom(LINETRACKER_ADDRESS, LINETRACKER_REQUEST_SIZE);    

  while(Wire.available()) { 
    linetrackerInput = Wire.read();
    Serial.print("linetracker data="); Serial.println(linetrackerInput, BIN);
  }
  delay(200);
}

void readDistanceI2C(){
  Wire.requestFrom(DISTANCE_ADDRESS, DISTANCE_REQUEST_SIZE);    

  while(Wire.available()) { 
    byte l = Wire.read();
    byte h = Wire.read();
    distance = l + (h << 8);
    Serial.print("distance data="); Serial.println(distance);
  }
  delay(200);
}

void checkLinetrackerDeviations(){
  //lineDeviationLeft
  //lineDeviationRight
  //lineLost
}


// STATE MACHINES -------------------------------------------------------------------------------------------------
//void driveMotors(int leftMotorDirection, int leftMotorSpeed, int rightMotorDirection, int rightMotorSpeed) {
//  ledcWrite(3, rightMotorSpeed);//set the speed to the speedpin
//  ledcWrite(0, leftMotorSpeed);
//  switch (leftMotorDirection) {
//    case 0:
//      ledcWrite(1, 0); //put both pins of the left motor off so the motor doesn't turn
//      ledcWrite(0, 0);
//      break;
//    case -1:
//      ledcWrite(1, 255); //if the motor doesn't turn correctly, replace 0 by 255 or vice versa
//      break;
//    case 1:
//      ledcWrite(1, 0); //if the motor doesn't turn correctly, replace 0 by 255 or vice versa
//      break;
//  }
//  switch (rightMotorDirection) {
//    case 0:
//      ledcWrite(2, 0); //put both pins of the right motor off so the motor doesn't turn
//      ledcWrite(3, 0);
//      break;
//    case -1:
//      ledcWrite(2, 0); //if the motor doesn't turn correctly, replace 0 by 255 or vice versa
//      break;
//    case 1:
//      ledcWrite(2, 255); //if the motor doesn't turn correctly, replace 0 by 255 or vice versa
//      break;
//  }
//}

void modusMenu(){
  if(modus != previousModus){
    Serial.println("Modus change!");

    switch(modus){
      case MANUAL:
        oledScrollText("manual modus");
        modusManual();
        break;
      case AUTO:
        oledScrollText("auto modus");
        modusAuto();
        break;
      case PATTERN:
        oledScrollText("pattern modus");
        modusPattern();
        break;
      default:
        oledScrollText("modus menu: select a modus");
        break;
    }
  }
  previousModus = modus;
}

void modusManual(){
  if (command != previousCommand) {
    Serial.print("Command: "); Serial.println(command);
    
    switch (command) {
      case FORWARD: // Drive forward
        //driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_FORWARD, drivingSpeed);
        oledScrollText("forward");
        break;
      case RIGHT: // Turn right around center point chassis
        //driveMotors(MOTOR_BACKWARDS, drivingSpeed, MOTOR_FORWARD, drivingSpeed);
        oledScrollText("right");
        break;
      case LEFT: // Turn left around center point chassis
        //driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_BACKWARDS, drivingSpeed);
        oledScrollText("left");
        break;
      default: // Stop driving
        //driveMotors(MOTOR_STOP, 0, MOTOR_STOP, 0);
        oledScrollText("stop");
        break;
    }
    previousCommand = command; //Another question on the assignment, why is this statement necessary
    //-> we will store the last command received from mqtt into an integer, so we can determine in the next run of the loop if we
    //received new data and if so, we will see which command it is and execute the needed code for that command
  }
}

void modusAuto(){
  readDistanceI2C();

  if(distance < MIN_DISTANCE){
    if(random(0,1)){
      //driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_BACKWARDS, drivingSpeed);
      oledScrollText("left");
      delay(TURN_DELAY);
    }
    else{
      //driveMotors(MOTOR_BACKWARDS, drivingSpeed, MOTOR_FORWARD, drivingSpeed);
      oledScrollText("right");
      delay(TURN_DELAY);
    }
  }
  else{
    //driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_FORWARD, drivingSpeed);
    oledScrollText("forward");
  }
}

void modusPattern(){
  readLinetrackerI2C();
  checkLinetrackerDeviations();

  if(lineDeviationLeft){
    //driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_BACKWARDS, drivingSpeed);
    oledScrollText("left");
    delay(TURN_DELAY);
  }
  else if(lineDeviationRight){
    //driveMotors(MOTOR_BACKWARDS, drivingSpeed, MOTOR_FORWARD, drivingSpeed);
    oledScrollText("right");
    delay(TURN_DELAY);
  }
  else if(lineLost){
    //driveMotors(MOTOR_STOP, 0, MOTOR_STOP, 0);
    oledScrollText("Line lost. Stopping and exiting modus.");
    modus = MENU;
  }
  else{
    //driveMotors(MOTOR_FORWARD, drivingSpeed, MOTOR_FORWARD, drivingSpeed);
    oledScrollText("forward");
  }
}


// SETUP ----------------------------------------------------------------------------------------------------------
void setup() {
  Wire.begin();

  Serial.begin(9600);

//    // init of the PWM Pins
//    for (int i = 0; i < PWM_CHANNEL_COUNT; i++) {
//      ledcSetup(MOTOR_CHANNELS[i], PWM_FREQUENCY, PWM_RESOLUTION);
//      ledcAttachPin(MOTOR_PINS[i], MOTOR_CHANNELS[i]);
//    }
//    driveMotors(MOTOR_STOP, 0, MOTOR_STOP, 0); //put every motor off since when the ESP starts up, the motors start spinning
//    //init of the LED Pins
//    for (int i = 0; i < LED_COUNT; i++) {
//      ledcSetup(LED_CHANNELS[i], PWM_FREQUENCY, PWM_RESOLUTION);
//      ledcAttachPin(LED_PINS[i], LED_CHANNELS[i]);
//    }
  
  oledSetup();

  setup_wifi();

  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(callback);
}


// INFINTE LOOP ----------------------------------------------------------------------------------------------------
void loop() {
  readLinetrackerI2C();

 // every loop checks if there is a connection with the MQTT server if not reconnect
  if (!client.connected()) reconnect();

  // every loop we will run the MQTT loop and trigger the callback function if neccesary
  client.loop();

  //convert the msg Array TO Integer
  //since we need an integer to compare to, we need to change the variable type, that's where atio comes into play
  if(topic == "modus") modus = atoi(msg);
  if(topic == "cmd") command = atoi(msg);

  modusMenu();
}
