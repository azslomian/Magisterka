
  #include <SimpleZigBeeRadio.h>
  #include <SoftwareSerial.h>

  unsigned long myMillis=0;   
  unsigned long prevMillis=0; 
  int resetPin = 3;  
  
  void setup() {
    Serial.begin( 9600 );
    pinMode(resetPin, OUTPUT); 
  }

  void loop() {
    myMillis = millis() - prevMillis;
    Serial.println(myMillis);
    digitalWrite(resetPin, HIGH);
    prevMillis = millis();
    delay(1000);
    digitalWrite(resetPin, LOW);
    delay(599000);
    //delay(4000);
  }
