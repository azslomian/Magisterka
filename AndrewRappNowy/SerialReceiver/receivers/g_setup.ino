void setup() {
  // initialize the digital pin as an output.
  Serial.begin(9600);
  Serial1.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(led, OUTPUT);
  pinMode(sound, OUTPUT);
  
  pinMode(resetPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(resetPin), resetClock, RISING);
  //delay(15000);
  detachInterrupt(digitalPinToInterrupt(resetPin));
}
