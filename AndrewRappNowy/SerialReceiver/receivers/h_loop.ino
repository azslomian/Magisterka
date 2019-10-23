// the loop routine runs over and over again forever:
void loop() {
  int sth = Serial1.available();
  if (sth > 0) {  // chyba czeka blokująco
    koniec = 0;
    table[numberOfBytes] = sth;
    myBufferMessage[numberOfBytes] = Serial1.read(); 
    numberOfBytes++;
  } else if (koniec == 0) {
    myClockMillis = millis() - prevClockMillis;
    myClockMillis = myClockMillis - numberOfBytes;
    Serial.println(myClockMillis);
    koniec = 1;
    for(int b = 0 ; b < numberOfBytes ; b++){
       Serial.println(table[b]);
    }
    Serial.println("Wiadomosc");
    for(int v = 0 ; v < numberOfBytes ; v++){
       Serial.println(myBufferMessage[v]);
    }
    numberOfBytes = 0;
  }
}
