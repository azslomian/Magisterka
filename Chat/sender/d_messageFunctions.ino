void clearPayload(uint8_t* payload, int sizeOfMessage){
   for(int k = sizeOfMessage + 15; k < 100; k++){
      payload[k] = 0;
   }
}

void clearMessage(){
   for(int k = 0; k < 100; k++){
      message[k] = 0;
   }
}

void clearPayloadMessage(){
  for(int k = 0; k < 100; k++){
      payload[k] = 0;
   }
}

void getMessageFromSerialMonitor(){
    String messageString = Serial.readString();
    int j = 0;
    int sizeOfMessage = messageString.length();
    char messageChar[100];
    messageString.toCharArray(messageChar, 100);
    for(j = 0; j < sizeOfMessage; j++){
      payload[j] = uint8_t(messageChar[j]);
    }
    addTimeStampToMessage(j);
    clearPayload(payload, sizeOfMessage);
}
