// the loop routine runs over and over again forever:
void loop() {
  if (Serial1.available() > 0) {  // chyba czeka blokująco
    koniec = 0;
    inByte = Serial1.read();
    //Serial.print(inByte);
    //Serial.print(", ");
  } else if (koniec == 0) {
    myClockMillis = millis() - prevClockMillis;
    Serial.println(myClockMillis);
    koniec = 1;
  }
  delay(1);
}
