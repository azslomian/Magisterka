void loop() {   
  while(millis() < 100000){
    Serial.println(millis());
    delay(1000);
  }
  if (Serial.available() > 0) {
    inByte = Serial.read();
    int i=0;
    switch (inByte) {
      case 'l': 
        for(int i = 0; i < 20; i++){
        Serial1.write( messageForSerialSend, sizeof(messageForSerialSend));
        ControlResp();
        Serial.println(millis());
        delay (2000);
        digitalWrite(resetPin, LOW);
        }
        break;
        
      default:
        break;
      }
  }
  delay(10);
}
