
  #include <SimpleZigBeeRadio.h>
  #include <SoftwareSerial.h>

  SimpleZigBeeRadio xbee = SimpleZigBeeRadio();

  SimpleZigBeeAddress addrOne = SimpleZigBeeAddress();
  uint32_t msb64 = 0x0013a200;
  uint32_t lsb64 = 0x40a8bb63;
  SimpleZigBeeAddress addrTwo = SimpleZigBeeAddress( msb64, lsb64 );
  uint16_t addr16 = 0xf3a9;
  SimpleZigBeeAddress addrThree = SimpleZigBeeAddress( msb64, lsb64, addr16 );

  SoftwareSerial xbeeSerial(10, 11); 

  SimpleZigBeePacket zbp = SimpleZigBeePacket();
  SimpleZigBeePacket zbpTwo = SimpleZigBeePacket(40);

  int val = 0;

  unsigned long time = 0;
  unsigned long last_sent = 0;

  uint8_t exFrame[] = { 0x10,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xfe,0x00,0x00,0xff };
  
  void setup() {
    // Start the serial ports ...
    Serial.begin( 9600 );
    while( !Serial ){;}  // Wait for serial port (for Leonardo only).
    xbeeSerial.begin( 38400 );
    // ... and set the serial port for the XBee radio.
    xbee.setSerial( xbeeSerial );
    // Set a non-zero frame id to receive Status and Response packets.
    xbee.setAcknowledgement(true);
}
    
  
  void loop() {
    // If data is waiting in the XBee serial port ...
    if( xbee.available() ){
        // ... read the data.
        xbee.read();
        // If a complete message is available, display the contents
        if( xbee.isComplete() ){
            Serial.print("\nIncoming Message: ");
            printPacket( xbee.getIncomingPacketObject() );
        }
    }
    delay(10); // Small delay for stability
}
  
  // Function for printing the complete contents of a packet
  void printPacket(SimpleZigBeePacket & p){
    Serial.print( START, HEX );
    Serial.print(' ');
    Serial.print( p.getLengthMSB(), HEX );
    Serial.print(' ');
    Serial.print( p.getLengthLSB(), HEX );
    Serial.print(' ');
    // Frame Type and Frame ID are stored in Frame Data
    uint8_t checksum = 0;
    for( int i=0; i<p.getFrameLength(); i++){
      Serial.print( p.getFrameData(i), HEX );
                Serial.print(' ');
      checksum += p.getFrameData(i); 
    }
    // Calculate checksum based on summation of frame bytes
    checksum = 0xff - checksum;
    Serial.print(checksum, HEX );
    Serial.println();
  }
