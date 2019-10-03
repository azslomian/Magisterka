void loop() {   
  // break down 10-bit reading into two bytes and place in payload
  pin5 = analogRead(5);
  
  if (Serial.available() > 0) {
    inByte = Serial.read();
    switch (inByte) {
    case 'l':    
      for(int i = 0; i < 1000; i++){
        prevMillis = millis();
        digitalWrite(resetPin, HIGH);     
        xbee.send(zbTxU);
        ControlResp();
        myMillis = millis() - prevMillis;
        Serial.println(myMillis);
        delay(200);  // delay musi byc wiekszy niz czas przesylu pakietu 
        digitalWrite(resetPin, LOW);
      }
      break;
    
    default:
      break;
    }
  }
  delay(10);
}
