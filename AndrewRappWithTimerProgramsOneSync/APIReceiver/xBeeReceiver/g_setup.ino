void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(dataLed,  OUTPUT);
  
  // start serial
  Serial.begin(9600);
  Serial1.begin(38400);
  pinMode(resetPin, INPUT_PULLUP);
  xbee.begin(Serial1);
  
  attachInterrupt(digitalPinToInterrupt(resetPin), resetClock, RISING);
  //flashLed(statusLed, 3, 50);
}
