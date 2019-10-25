void loop() {   
  if (Serial.available() > 0) {
    inByte = Serial.read();
    int i=0;
    switch (inByte) {
      case 'l': 
        for(int i = 0; i < 20; i++){
          myMillis = millis() - prevMillis; 
          Serial1.write( messageForSerialSend, sizeof(messageForSerialSend));
          ControlResp();
          //delay(10);
          Serial.println(myMillis);
        }
        break;
        
      default:
        break;
      }
  }
  delay(1);
}
