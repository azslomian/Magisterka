
  #include <SimpleZigBeeRadio.h>
  #include <SoftwareSerial.h>

  volatile int output = LOW; 
  unsigned long myMillis=0;   
  unsigned long prevMillis=0; 
  int pin = 2;  // Only pins 2 and 3 are available for interrupts 
  
  void setup() {
    Serial.begin( 9600 );
    pinMode(pin,INPUT); 
    attachInterrupt(digitalPinToInterrupt(pin), buttonPressed, RISING);  //  function for creating external interrupts at pin2 on Rising (LOW to HIGH)
  }

  void loop() {

  }

  void buttonPressed()           //ISR function excutes when push button at pinD2 is pressed
  {
     myMillis = millis() - prevMillis;                                             
     Serial.println("Interrupt 1");
     Serial.println(myMillis);
     prevMillis = millis();
  }
