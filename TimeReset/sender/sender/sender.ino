
  #include <SimpleZigBeeRadio.h>
  #include <SoftwareSerial.h>

  unsigned long myMillis=0;   
  unsigned long prevMillis=0; 
  int pin = 3;  
  
  void setup() {
    Serial.begin( 9600 );
    pinMode(pin, OUTPUT); 
  }

  void loop() {
    myMillis = millis() - prevMillis;
    Serial.println(myMillis);
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    delay(1000);
   
    
    prevMillis = millis();
    
    delay(1000);            // waits for a second
    delay(1000);            // waits for a second
    
    delay(100); 
  }
