void loop() {   
  if (Serial.available() > 0) {
    inByte = Serial.read();
    switch (inByte) {
    case 'l':    
      for(int i = 0; i < 20; i++){
        myMillis = millis() - prevMillis;  
        xbee.send(zbTxU);
        ControlResp();
        Serial.println(myMillis);
      }
      break;
    
    default:
      break;
    }
  }
  delay(10);
}
