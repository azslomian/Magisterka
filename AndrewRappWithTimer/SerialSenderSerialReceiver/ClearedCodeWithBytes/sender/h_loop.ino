void loop() {   
  // break down 10-bit reading into two bytes and place in payload
  pin5 = analogRead(5);
  
  if (Serial.available() > 0) {
    inByte = Serial.read();
    int i=0;
    switch (inByte) {
    case 'l': 
      myMillis = millis() - prevMillis;
      Serial.println(myMillis);
      digitalWrite(resetPin, HIGH);
      digitalWrite(resetPin, LOW);
      Serial1.write( messageForSerialSend, sizeof(messageForSerialSend));
      ControlResp();
      Serial.println("W lewo");
      delay (10);
      prevMillis = millis();
      break;
    case 'p':    
      Serial.println("W prawo");
      while(i < sizeof(messageForSerialSend)){
        //Serial1.print(messageForSerialSend[i], BYTE);
        i++;
      }
      ControlResp();
      break;
    default:
      break;
    }
  }
  delay(1000);
}
