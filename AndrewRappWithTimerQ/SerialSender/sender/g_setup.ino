void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  Serial1.begin(115200);
  xbee.setSerial(Serial1);
  Serial.begin(9600);
  pinMode(resetPin, OUTPUT); 
  
  digitalWrite(resetPin, LOW);
  delay(2000);
  digitalWrite(resetPin, HIGH);  
  prevMillis = millis();
  delay(2000); 
  digitalWrite(resetPin, LOW);
}
