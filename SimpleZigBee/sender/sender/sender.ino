
  #include <SimpleZigBeeRadio.h>
  #include <SoftwareSerial.h>

  SimpleZigBeeRadio xbee = SimpleZigBeeRadio();


  SoftwareSerial xbeeSerial(10, 11); 

  SimpleZigBeePacket zbp = SimpleZigBeePacket();
  SimpleZigBeePacket zbpTwo = SimpleZigBeePacket(40);

  int val = 0;

  unsigned long time = 0;
  unsigned long last_sent = 0;
//7E 00 10 10 01 00 7D 33 A2 00 40 A7 3A 7D 33 FF FE 00 00 30 30 A8
  //uint8_t exFrame[] = { 0x10,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xfe,0x00,0x00,0xff };
  uint8_t exFrame[] = { 0x10, 0x01, 0x00, 0x7D, 0x33, 0xA2, 0x00, 0x40, 0xA7, 0x3A, 0x7D, 0x33, 0xFF, 0xFE, 0x00, 0x00, 0x30, 0x30 };
  
  
  void setup() {
    Serial.begin( 9600 );
    xbeeSerial.begin( 38400 );
    xbee.setSerial( xbeeSerial );
    //xbee.setAcknowledgement(true);
    zbp.setFrameData(0, exFrame, sizeof(exFrame));
    //zbp.setFrameData( zbp.getFrameLength()-2, val >> 8 & 0xff );
    
//    Serial.println( "Send command to leave network (CB4)" );
//    xbee.prepareATCommand('CB',4);
//    xbee.send();
//    delay(10000);
  }

//  void setup() {
//    Serial.begin( 9600 );
//    while( !Serial ){;}// Wait to connect. Needed for Leonardo only
//    zbp.setFrameType(ZIGBEE_TRANSMIT_REQUEST); // Same as zbp.setFrameType(0x10)
//    zbp.setFrameID(0x01);
//    
//    SimpleZigBeeAddress coorAddr = SimpleZigBeeAddress(0x00000000,0x00000000,0xfffe);
//    zbp.setAddress(coorAddr);
//    zbp.setAddress(0x00000000,0x00000000,0xfffe);
//    zbp.setTXRequestBroadcastRadius(0x00);
//    zbp.setTXRequestOption(0x00);

    // Finally, set the payload.
//    uint8_t exPayload[] = { 0xa1,0xa2,0xa3 };
//    zbp.setTXRequestPayload( exPayload, sizeof(exPayload) ); // Same as zbp.setPayload( exPayload, 3 );
//    
//    // Now that the TX packet is complete, 
//    // we will display the contents to the serial port.
//    printPacket(zbp);
 // }
  
  void loop() {
    while( xbee.available() ){
        xbee.read();
        if( xbee.isComplete() ){
            Serial.print("\nIncoming Message: ");
            printPacket( xbee.getIncomingPacketObject() );
        }
    }
    time = millis();
    if( time > (last_sent+5000) ){
        last_sent = time;
        //zbp.setFrameData( zbp.getFrameLength()-2, val >> 8 & 0xff );
        //zbp.setFrameData( zbp.getFrameLength()-1, val & 0xff );
        Serial.print("\nSend Message: ");
        printPacket( zbp );
        xbee.send( zbp );
        //val = (val + 10)%500; // Increase val by 10 (start over at 500)
    }
    delay(10); // Small delay for stability
    // That's it! The router is ready to go.
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
