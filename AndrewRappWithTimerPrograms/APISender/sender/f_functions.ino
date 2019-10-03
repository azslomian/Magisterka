void flashLed(int pin, int times, int wait) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(wait);
    digitalWrite(pin, LOW);

    if (i + 1 < times) {
      delay(wait);
    }
  }
}

void ControlResp () {
  // after sending a tx request, we expect a status response
  // wait up to half second for the status response
  if (xbee.readPacket(5000)) {  //zwraca true, jesli pakiet przyszedl, wpisuje go do bufora, nadpisuje poprzedni
    // got a response!

    // should be a znet tx status              
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);

      // get the delivery status, the fifth byte
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
        flashLed(statusLed, 5, 200);
        Serial.print("Success.");  
      } else {
        // the remote XBee did not receive our packet. is it powered on?
        flashLed(errorLed, 3, 200);
        Serial.print("Error 3.");  
      }
    }
  } else if (xbee.getResponse().isError()) {
      Serial.print("Error reading packet.  Error code: ");  
      Serial.println(xbee.getResponse().getErrorCode());
  } else {
    // local XBee did not provide a timely TX Status Response -- should not happen
    flashLed(errorLed, 2, 200);
    Serial.print("Error 4.");  
  }
}
