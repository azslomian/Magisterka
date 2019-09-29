void loop() {   
  // break down 10-bit reading into two bytes and place in payload
  pin5 = analogRead(5);
  
  if (Serial.available() > 0) {
    inByte = Serial.read();
    int i=0;
    switch (inByte) {
    case 'l': 
      Serial1.write( messageForSerialSend, sizeof(messageForSerialSend));
      ControlResp();
      //Serial1.print(messageForSerialSend);
      Serial.println("W lewo");
      delay (1000);
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
  delay(100);
}
