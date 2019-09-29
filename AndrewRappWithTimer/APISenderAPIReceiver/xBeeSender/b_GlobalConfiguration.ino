/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 *
 * This file is part of XBee-Arduino.
 *
 * XBee-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XBee-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <XBee.h>

/*
This example is for Series 2 XBee
 Sends a ZB TX request with the value of analogRead(pin5) and checks the status response for success
*/

// create the XBee object
XBee xbee = XBee();

uint8_t payload[] = { 0, 0 };

// SH + SL Address of receiving XBee
XBeeAddress64 addrU02 = XBeeAddress64(0x0013a200, 0x40A739F0);  
XBeeAddress64 addrU03 = XBeeAddress64(0x0013a200, 0x409F6E7F);
XBeeAddress64 addrU04 = XBeeAddress64(0x0013a200, 0x409F378E);  
XBeeAddress64 addrU05 = XBeeAddress64(0x0013a200, 0x40A73A0B);
XBeeAddress64 addrU06 = XBeeAddress64(0x0013a200, 0x40982DCA);   
XBeeAddress64 addrU07 = XBeeAddress64(0x0013a200, 0x40AD19DE);
XBeeAddress64 addrU08 = XBeeAddress64(0x0013a200, 0x409F6EA2);    
XBeeAddress64 addrU09 = XBeeAddress64(0x0013a200, 0x40A73A13);
XBeeAddress64 addrU10 = XBeeAddress64(0x0013a200, 0x40A739ED);    
XBeeAddress64 addrU11 = XBeeAddress64(0x0013a200, 0x409F6E72);
XBeeAddress64 addrU12 = XBeeAddress64(0x0013a200, 0x40AD19ED);    
XBeeAddress64 addrU13 = XBeeAddress64(0x0013a200, 0x40AD19F8);


// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = addrU09;
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int pin5 = 0;

unsigned long myMillis=0;   
unsigned long prevMillis=0;
int statusLed = 13;
int errorLed = 13;
int resetPin = 3;

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




void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(resetPin, OUTPUT); 
 
  Serial.begin(9600);
  Serial1.begin(38400);
  xbee.setSerial(Serial1);

}

void loop() {   
  // break down 10-bit reading into two bytes and place in payload
  //pin5 = analogRead(5);
  //payload[0] = pin5 >> 8 & 0xff;
  //payload[1] = pin5 & 0xff;

  prevMillis = millis();
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);  
  xbee.send(zbTx);
  myMillis = millis() - prevMillis;
  Serial.println(myMillis);
 

  // flash TX indicator
  //flashLed(statusLed, 1, 100);

  // after sending a tx request, we expect a status response
  // wait up to half second for the status response
  if (xbee.readPacket(500)) {
    // got a response!
    Serial.println("wow");
    // should be a znet tx status              
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);

      // get the delivery status, the fifth byte
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        // success.  time to celebrate
        flashLed(statusLed, 5, 50);
      } else {
        // the remote XBee did not receive our packet. is it powered on?
        flashLed(errorLed, 3, 500);
      }
    }
  } else if (xbee.getResponse().isError()) {
    Serial.println("Error reading packet.  Error code: ");
    Serial.println(xbee.getResponse().getErrorCode());
    //nss.print("Error reading packet.  Error code: ");  
    //nss.println(xbee.getResponse().getErrorCode());
  } else {
    // local XBee did not provide a timely TX Status Response -- should not happen
    Serial.println("should not happen");
    flashLed(errorLed, 2, 50);
  }

  delay(10);
}
