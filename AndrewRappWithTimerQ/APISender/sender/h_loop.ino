void loop() {   
  if (Serial.available() > 0) {
    inByte = Serial.read();
    switch (inByte) {
    case 'l':
      for(int h = 0; h < 10000; h++){
        Serial.print("Proba ");
        Serial.print(h);
        Serial.println();
        for(int i = 0; i < 20; i++){
          myMillis = millis() - prevMillis;  
          xbee.send(zbTxU);
          ControlResp();
          Serial.println(myMillis);
          //delay(1000);
        }
        delay(10000); 
      }
      break;
    
    default:
      break;
    }
  }
  delay(10);
}
