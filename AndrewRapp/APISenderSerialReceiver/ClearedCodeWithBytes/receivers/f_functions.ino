void ControlResp () {
  // after sending a tx request, we expect a status response
  // wait up to half second for the status response
  if (xbee.readPacket(500)) {  //zwraca true, jesli pakiet przyszedl, wpisuje go do bufora, nadpisuje poprzedni            
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        Serial.print("Success.");  
      } else {
        Serial.print("Error 3.");  
      }
    }
  } else if (xbee.getResponse().isError()) {
      Serial.print("Error reading packet.  Error code: ");  
      Serial.println(xbee.getResponse().getErrorCode());
  } else {
    Serial.print("Error 4.");  
  }
}
