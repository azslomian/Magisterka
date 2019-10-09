void loop() {   
  // break down 10-bit reading into two bytes and place in payload
  pin5 = analogRead(5);
  
  if (Serial.available() > 0) {
    inByte = Serial.read();
    int i=0;
    switch (inByte) {
      case 'l': 
        for(int i = 0; i < 20; i++){
          myMillis = millis() - prevMillis; 
          Serial1.write( messageForSerialSend, sizeof(messageForSerialSend));
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
