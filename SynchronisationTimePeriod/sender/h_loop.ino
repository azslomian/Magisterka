void loop() {   
  if (Serial.available() > 0) {
    inByte = Serial.read();
    int i=0;
    switch (inByte) {
      case 'l': 
        for(int i = 0; i < 20; i++){
        prevMillis = millis();
        Serial1.write( messageForSerialSend, sizeof(messageForSerialSend));
        ControlResp();
        delay (200);
        }
        break;
        
      default:
        break;
      }
  }
  delay(10);
}
