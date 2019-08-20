#include <XBee.h>

XBee xbee = XBee();

uint8_t payload[] = { 0, 0 };

// SH + SL Address of receiving XBee
XBeeAddress64 addrU02 = XBeeAddress64(0x0013a200, 0x408B681D);
XBeeAddress64 addrU03 = XBeeAddress64(0x0013a200, 0x409F6E7F);
ZBTxRequest zbTxU02 = ZBTxRequest(addrU02, payload, sizeof(payload));
ZBTxRequest zbTxU03 = ZBTxRequest(addrU03, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int pin5 = 0;
int statusLed = 13;
int errorLed = 13;
int inByte = 0;

void flashLed(int pin, int times, int wait) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(wait);
    digitalWrite(pin, LOW);

    if (i + 1 < times) {
      delay(wait);
    }
  }
}

void ControlResp () {
  // after sending a tx request, we expect a status response
  // wait up to half second for the status response
  if (xbee.readPacket(500)) {  //zwraca true, jesli pakiet przyszedl, wpisuje go do bufora, nadpisuje poprzedni
    // got a response!

    // should be a znet tx status            	
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);

      // get the delivery status, the fifth byte
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
        flashLed(statusLed, 5, 200);
        Serial.print("Success.");  
      } else {
        // the remote XBee did not receive our packet. is it powered on?
        flashLed(errorLed, 3, 200);
        Serial.print("Error 3.");  
      }
    }
  } else if (xbee.getResponse().isError()) {
      Serial.print("Error reading packet.  Error code: ");  
      Serial.println(xbee.getResponse().getErrorCode());
  } else {
    // local XBee did not provide a timely TX Status Response -- should not happen
    flashLed(errorLed, 2, 200);
    Serial.print("Error 4.");  
  }
}

void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  Serial1.begin(9600);
  xbee.setSerial(Serial1);
  Serial.begin(9600);
}

void loop() {   
  // break down 10-bit reading into two bytes and place in payload
  pin5 = analogRead(5);
  payload[0] = pin5 >> 8 & 0xff;
  payload[1] = pin5 & 0xff;
  
  if (Serial.available() > 0) {
    inByte = Serial.read();
    switch (inByte) {
    case 'l':    
      Serial.println("W lewo");
      xbee.send(zbTxU03);
      ControlResp();
      delay (1000);
      xbee.send(zbTxU02);
      ControlResp();
      break;
    case 'p':    
      Serial.println("W prawo");
      xbee.send(zbTxU02);
      ControlResp();
      delay (1000);
      xbee.send(zbTxU03);
      ControlResp();
      break;
    default:
      break;
    }
  }
  delay(100);
}

