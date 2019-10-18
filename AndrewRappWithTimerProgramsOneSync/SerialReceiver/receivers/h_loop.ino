// the loop routine runs over and over again forever:
void loop() {
  int sth = Serial1.available();
  if (sth > 0) {  // chyba czeka blokująco
    koniec = 0;
    table[numberOfBytes] = sth;
    Serial1.read();
    Serial1.read();
    Serial1.read();
    numberOfBytes++;
  } else if (koniec == 0) {
    myClockMillis = millis() - prevClockMillis;
    myClockMillis = myClockMillis - numberOfBytes;
    Serial.println(myClockMillis);
    koniec = 1;
    for(int l = 0 ; l < numberOfBytes ; l++){
       Serial.println(table[l]);
    }
    numberOfBytes = 0;
  }
  delay(1);
}
