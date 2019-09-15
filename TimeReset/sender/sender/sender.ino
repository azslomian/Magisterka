
  #include <SimpleZigBeeRadio.h>
  #include <SoftwareSerial.h>

  unsigned long myMillis=0;   
  unsigned long prevMillis=0;   
  
  void setup() {
    Serial.begin( 9600 );
    pinMode(3,OUTPUT); 
  }

  void loop() {
    myMillis = millis() - prevMillis;
    Serial.println(myMillis);
    digitalWrite(3, HIGH); 
    digitalWrite(3, LOW);
    prevMillis = millis();
    
    delay(1000);            // waits for a second
    delay(1000);            // waits for a second
    
    delay(100); 
  }
