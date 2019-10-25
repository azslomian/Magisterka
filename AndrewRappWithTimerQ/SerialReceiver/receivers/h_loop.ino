// the loop routine runs over and over again forever:
void loop() {
  int bytesInBuffer = Serial1.available();
  if (bytesInBuffer > 0) {  // chyba czeka blokująco
    koniec = 0;
    //table[numberOfBytes] = bytesInBuffer;
    for(int h = 0; h < bytesInBuffer; h++){
      Serial1.read();
    }
    numberOfBytes++;
  } else if (koniec == 0) {
    myClockMillis = millis() - prevClockMillis;
    myClockMillis = myClockMillis - numberOfBytes;
    Serial.println(myClockMillis);
    koniec = 1;
//    for(int l = 0 ; l < numberOfBytes ; l++){
//       Serial.println(table[l]);
//    }
    numberOfBytes = 0;
  }
  delay(1);
}
