void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  Serial1.begin(38400);
  xbee.setSerial(Serial1);
  Serial.begin(9600);
  pinMode(resetPin, OUTPUT); 
  digitalWrite(resetPin, HIGH);
  prevMillis = millis();
  delay(1000);
  digitalWrite(resetPin, LOW);
}
