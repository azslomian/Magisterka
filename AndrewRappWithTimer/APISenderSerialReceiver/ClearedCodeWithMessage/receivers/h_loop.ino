// the loop routine runs over and over again forever:
void loop() {

  if (Serial1.available() > 0) {  // chyba czeka blokująco
    koniec = 0;
    inByte = Serial1.read();
    if(i > 15){
      message[g] = (char)inByte;
      g++;
    }
    i++;
  } else if (koniec == 0) {
    koniec = 1;
    Serial.println("hahaha");
    int arraySize = sizeof(message)/sizeof(message[0]); 
    for(int i = 0; i < 3; i++){
      Serial.print(message[i]);
      payload[i] = uint8_t(message[i]); 
      Serial.print(payload[i]);
    }
    Serial.println();
    ZBTxRequest zbTxU = ZBTxRequest(addrU, payload, sizeof(payload));
    xbee.send(zbTxU);
    ControlResp();
    
   
    // time = millis();
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

  delay(10);
}
