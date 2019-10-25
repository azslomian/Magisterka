uint8_t masterTime;
uint8_t meanOneWayTime;
uint8_t previousSlaveTime;
long previousOffset = 999999;
uint8_t slaveTime;

uint8_t timeSyncThreshold = 20;
uint8_t myMillis;      // to find as a Real master time

int stabilityCounter = 0;
int stabilityThreshold = 20;

int isEndOfSync = 0;
int isFirstMessage = 1;

void syncTimer(char* message){
    if(isFirstMessage == 1){
       firstSync();
    } else{
      uint8_t timeDifference = slaveTime - previousSlaveTime;
      myMillis = myMillis + timeDifference;
      masterTime = masterTime + meanOneWayTime;
      checkIfSync();
      previousSlaveTime = slaveTime;
    } 
  } 

void firstSync(){
  isFirstMessage = 0;
  masterTime = getMasterTime();
  meanOneWayTime = getMeanOneWayTime();
  myMillis = masterTime + meanOneWayTime;
}

void checkIfSync(){
  long offset = masterTime - myMillis;
  if(abs(offset) < timeSyncThreshold){
        stabilityCounter++;
        if(stabilityCounter > stabilityThreshold){
            isEndOfSync = 1;
        }
   }
   previousOffset = min(offset, previousOffset);
}

uint8_t getMasterTime(){
  return 1;
}

uint8_t getMeanOneWayTime(){
  return 1;
}
