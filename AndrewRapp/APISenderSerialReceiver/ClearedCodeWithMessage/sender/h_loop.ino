void loop() {   
  // break down 10-bit reading into two bytes and place in payload
  pin5 = analogRead(5);
  payload[0] = pin5 >> 8 & 0xff;
  payload[1] = pin5 & 0xff;
  
  if (Serial.available() > 0) {
    inByte = Serial.read();
    switch (inByte) {
    case 'l':    
      Serial.println("W lewo");
      xbee.send(zbTxU);
      ControlResp();
      delay (1000);
      xbee.send(zbTxU);
      ControlResp();
      break;
    case 'p':    
      Serial.println("W prawo");
      xbee.send(zbTxU);
      ControlResp();
      delay (1000);
      xbee.send(zbTxU);
      ControlResp();
      break;
    default:
      break;
    }
  }
  delay(100);
}
