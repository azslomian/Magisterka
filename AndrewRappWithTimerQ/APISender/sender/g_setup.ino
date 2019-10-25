void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(resetPin, OUTPUT);
  Serial1.begin(115200);
  xbee.setSerial(Serial1);
  Serial.begin(9600);
  
  digitalWrite(resetPin, LOW);
  delay(2000);
  digitalWrite(resetPin, HIGH);  
  prevMillis = millis();
  delay(2000); 
  digitalWrite(resetPin, LOW);

  //zbTxU.setAddress16(addrLogU09);
  //zbTxU.setFrameId(0);
}
