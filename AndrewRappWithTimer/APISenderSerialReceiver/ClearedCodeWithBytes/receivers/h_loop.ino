// the loop routine runs over and over again forever:
void loop() {

  if (Serial1.available() > 0) {  // chyba czeka blokująco
    if(koniec == 1){
      myClockMillis = millis() - prevClockMillis;
      Serial.println();
      Serial.println(myClockMillis);
    }
    koniec = 0;
    inByte = Serial1.read();
    Serial.print(inByte);
    Serial.print(", ");
  } else if (koniec == 0) {
    myClockMillis = millis() - prevClockMillis;
    Serial.println();
    Serial.println(myClockMillis);
    koniec = 1;
    Serial.println("hahaha");
    Serial.println();
    
    tone (sound, 5000, 500);  // dzwiek
    digitalWrite(led, HIGH); delay(500); digitalWrite(led, LOW);
  }

  switch (inByte) {
    case 'a':
      Serial.println(inByte);
      break;
    case 'b':
      digitalWrite(3, HIGH);
      break;
    case 'l':
      Serial.println("W lewo");
      break;
    case 'p':
      Serial.println("W prawo");
      break;
    default:
      // turn all the LEDs off:
      for (int thisPin = 2; thisPin < 3; thisPin++) {
        digitalWrite(thisPin, LOW);
      }
  }

  delay(1);
}
