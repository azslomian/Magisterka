void loop() {   
  // break down 10-bit reading into two bytes and place in payload
  pin5 = analogRead(5);
  
  if (Serial.available() > 0) {
    inByte = Serial.read();
    int i=0;
    switch (inByte) {
      case 'l': 
        for(int i = 0; i < 1000; i++){
        prevMillis = millis();
        digitalWrite(resetPin, HIGH);
        Serial1.write( messageForSerialSend, sizeof(messageForSerialSend));
        ControlResp();
        myMillis = millis() - prevMillis;
        Serial.println(myMillis);
        delay (150);
        digitalWrite(resetPin, LOW);
        }
        break;
        
      default:
        break;
      }
  }
  delay(10);
}
