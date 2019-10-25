// continuously reads packets, looking for ZB Receive or Modem Status
void loop() {
  xbee.readPacket();
  getResponse();
}

void getResponse(){
  if (xbee.getResponse().isAvailable()) {
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        getPacket();
      } else if (xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE) {
        ControlAssociation();
      } else {
        // not something we were expecting
        Serial.println("not something we were expecting");
        flashLed(errorLed, 1, 25);    
      }
    } else if (xbee.getResponse().isError()) {
      ControlResponseError();
    }
}

void ControlAssociation(){
    xbee.getResponse().getModemStatusResponse(msr);
    // the local XBee sends this response on certain events, like association/dissociation
    Serial.println("we have got response");
    if (msr.getStatus() == ASSOCIATED) {
      Serial.println("yay this is great.");
    } else if (msr.getStatus() == DISASSOCIATED) {
      Serial.println("this is awful.. flash led to show our discontent");
    } else {
      Serial.println("another status");
    }
}

void ControlResponseError(){
  Serial.println("Error reading packet.  Error code: ");
  Serial.println(xbee.getResponse().getErrorCode());
}

void getPacket(){
  // got a zb rx packet
  myClockMillis = millis() - prevClockMillis;
  Serial.println(myClockMillis);
  // now fill our zb rx class
  xbee.getResponse().getZBRxResponse(rx);
  //Serial.println(rx.getOption());
  //Serial.println(ZB_PACKET_ACKNOWLEDGED);
  
  ControlACK(); 
  // set dataLed PWM to value of the first byte in the data
  //Serial.print(rx.getData(0));
  //nalogWrite(dataLed, rx.getData(0));
}

void ControlACK(){
   if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) {
      // the sender got an ACK
      //Serial.println("the sender got an ACK");
      //flashLed(statusLed, 10, 10);
  } else {
      // we got it (obviously) but sender didn't get an ACK
      //Serial.println("we got it (obviously) but sender didn't get an ACK");
      //flashLed(errorLed, 2, 20);
  }
}
