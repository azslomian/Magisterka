
#include <Wire.h>

char dataFromTimeServer[10]; // char array to hold I2C data from TimeServer
unsigned long timeFromTimeServer = 0;  // unsigned long to hold time from TimeServer

unsigned long currentSyncedTime = 0;

const int buttonPin = 10;

void setup() {
 Serial.begin(9600);
 Serial.print("SYNCING...");
 syncTime(); // Sync time with TimeServer
 
 digitalWrite(buttonPin,HIGH);  // enable pull up resitor
 attachInterrupt(buttonPin, buttonPress, FALLING);  // register interrup on FALLING state
}


void loop() {
if(currentSyncedTime!=0){
  Serial.println(currentSyncedTime);
  currentSyncedTime=0;
}
}
// Run when falling
void buttonPress(){
 // Record timestamp in reference frame of TimeServer
 currentSyncedTime = timeFromTimeServer + micros();
}

// Method to read timestamp from central TimeServer over I2C
void syncTime(){
 Wire.begin();  // Initialize I2c
 
 Wire.requestFrom(0x50, 10);  // Request 10 bytes
 int index = 0;  // index of char array
 while(Wire.available())   // while more bytes avail
 { 
   char c = Wire.read();    // receive a byte as character
   dataFromTimeServer[index++] = c;  // store byte in char array
   
 }
 timeFromTimeServer = atol(dataFromTimeServer);  // convert char array to unsigned long
 
}
