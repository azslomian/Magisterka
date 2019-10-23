void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(dataLed,  OUTPUT);
  
  // start serial
  Serial.begin(9600);
  Serial1.begin(115200);
  pinMode(resetPin, INPUT_PULLUP);
  xbee.begin(Serial1);
  
  //attachInterrupt(digitalPinToInterrupt(resetPin), resetClock, RISING);
    //delay(15000);
  //detachInterrupt(digitalPinToInterrupt(resetPin));
  //flashLed(statusLed, 3, 50);
}
