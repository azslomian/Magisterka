void loop() {   
//  while(stopLoop != 1 && millis() < 100000){
//    Serial.println(millis());
//    delay(1000);
//    if(Serial.available() > 0){
//      Serial.println("koniec");
//      stopLoop = 1;
//    }
//  } 
  
  if (Serial.available() > 0) {
    inByte = Serial.read();
    switch (inByte) {
    case 'l':    
      for(int i = 0; i < 1; i++){
        myMillis = millis() - prevMillis;  
        xbee.send(zbTxU);
        ControlResp();
        Serial.println(myMillis);
        //delay(1000);
      }
      break;
    
    default:
      break;
    }
  }
  delay(10);
}
