void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(dataLed,  OUTPUT);
  
  // start serial
  Serial.begin(9600);
  Serial1.begin(38400);
  xbee.begin(Serial1);
  attachInterrupt(digitalPinToInterrupt(resetPin), resetClock, RISING);
  
  //flashLed(statusLed, 3, 50);
}
