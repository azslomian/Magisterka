long previousResult = 999999;
long timeTreshold = 300;
long syncCountTreshold = 20;
long syncCounter = 0;
long hasResponseTime = 0;

void getMeanTime(){
  payload[0] = 0;
  meanResponseTime = 0;
  for(int k = 0; k < 10; k++){
    //addTimeStampToMessage(1);
    sendMessage();
    meanResponseTime += resultTime; 
    Serial.println(meanResponseTime / k);
  }
  meanResponseTime = meanResponseTime / 10;
  Serial.println(meanResponseTime);
}

void sync(){
  payload[0] = 0;
  meanResponseTime = 0;
  for(int k = 0; k < 10; k++){
    addTimeStampToMessage(1);
    sendSyncMessage();
    meanResponseTime += resultTime; 
    Serial.println(meanResponseTime / k);
  }
  meanResponseTime = meanResponseTime / 10;
  Serial.println(meanResponseTime);
}

void addTimeStampToMessage(int indexOfMessage){
  char buf[16];
  long val;
  indexOfMessage+2;
  long actualTimeToSend = millis();
  //println(actualTimeToSend);
  ltoa(actualTimeToSend, buf, 10);
  payload[indexOfMessage] = uint8_t('$');
  for(int k = 0; k < sizeof(buf); k++){
    if(uint8_t(buf[k]) > 48 && uint8_t(buf[k]) < 58){
      payload[indexOfMessage+1] = uint8_t(buf[k]);
      indexOfMessage++;
    }
  }
  payload[indexOfMessage+1] = uint8_t('$');
}

void sendSyncMessage(){
  while(hasResponseTime != 1){
    zbTxU = ZBTxRequest(addrU, payload, sizeof(payload));
    sendingTime = millis();
    //addTimeStampToMessage(0);
    xbee.send(zbTxU);
    ControlResp();
    responseTime = millis();
    resultTime = responseTime - sendingTime;
    Serial.println(syncCounter);
    if(abs((resultTime - previousResult) < timeTreshold)){
      syncCounter++;
    } else{
      syncCounter = 0;
    }
    
    if(syncCounter > syncCountTreshold){
      Serial.println("Synch completed successfully");
      hasResponseTime = 1;
    }
    previousResult = resultTime;
    Serial.println(resultTime);
    delay(500);
  }
}

void addOffsetToMessage(int indexOfMessage){
  char buf[16];
  long val;
  ltoa(millis(), buf, 10);
  for(int k = 0; k < sizeof(buf); k++){
    if(uint8_t(buf[k]) > 47 && uint8_t(buf[k]) < 58){
      payload[indexOfMessage] = uint8_t(buf[k]);
      indexOfMessage++;
    }
    payload[indexOfMessage] = uint8_t('$');
  }
}

void getOffset(int indexOfMessage){
  char buf[16];
  long val;
  ltoa(millis(), buf, 10);
  for(int k = 0; k < sizeof(buf); k++){
    if(uint8_t(buf[k]) > 48 && uint8_t(buf[k]) < 58){
      payload[indexOfMessage] = uint8_t(buf[k]);
      indexOfMessage++;
    }
  }
}
