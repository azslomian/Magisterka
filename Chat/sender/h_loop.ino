void loop() {   
 if (Serial.available() > 0) {
    //inByte = Serial.read();
    getMessageFromSerialMonitor();
    Serial.println("w lewo");
    sendMessage();
    Serial.println(resultTime);
  }
  else{
      receiveMessage();
  }
  delay(100);
}

void receiveMessage(){
    if (Serial1.available() > 0) {  // chyba czeka blokująco (chociaz chyba jednak nie -> mozna cos wyslac w miedzy czasie)
      getMessageInChar();
    } else if (endOfMessage == 0) {
      getMessageInByte();
    }
}

void getMessageInByte(){
  endOfMessage = 1;
    for(int i = 0; i < g - 1; i++){
      Serial.print(message[i]);
      payload[i] = uint8_t(message[i]); // zoptymalizowac
    }
    Serial.println();
    clearMessage();
    //sendMessage();
    g = 0;
    i = 0;
}

void getMessageInChar() {
    endOfMessage = 0;
    inByte = Serial1.read();
    if(i > sizeOfFrame - 1){
      message[g] = (char)inByte; // sprawdzic czy trzeba rzutowac
      g++;
    }
    i++;
}


void sendMessage(){   // wyslac payload jako parametr
    zbTxU = ZBTxRequest(addrU, payload, sizeof(payload));
    sendingTime = millis();
    xbee.send(zbTxU);
    ControlResp();
    clearPayloadMessage();
    responseTime = millis();
    resultTime = responseTime - sendingTime;
}
