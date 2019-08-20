void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  Serial1.begin(38400);
  xbee.setSerial(Serial1);
  Serial.begin(9600);
  //payload[0] = 0;
  //payload[1] = 'w';
  //payload[2] = 'a';
  //sendSyncMessage(); 
  //getMeanTime();
}
