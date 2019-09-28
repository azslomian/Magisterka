
  #include <SimpleZigBeeRadio.h>
  #include <SoftwareSerial.h>

  volatile int output = LOW; 
  unsigned long myMillis=0;   
  unsigned long prevMillis=0;   
  
  void setup() {
    Serial.begin( 9600 );
    pinMode(5,INPUT);
    attachInterrupt(digitalPinToInterrupt(5),buttonPressed1,RISING);  //  function for creating external interrupts at pin2 on Rising (LOW to HIGH)
  }

  void loop() {
     
  }

  void buttonPressed1()           //ISR function excutes when push button at pinD2 is pressed
  {
     myMillis = millis() - prevMillis;                                             
     Serial.println("Interrupt 1");
     Serial.println(myMillis);
     prevMillis = millis();
  }
