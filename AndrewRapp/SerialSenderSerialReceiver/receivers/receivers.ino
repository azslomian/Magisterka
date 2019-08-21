#include <Printers.h>
#include <XBee.h>

/*
  Po odebraniu znaku z Serial1 (Xbee): mrugniecie dioda, dźwięk, odeslanie znaku na Serial (serial monitor)
*/

// Pin 13 has an LED connected on most Arduino boards.
int en_sound = 4;
int sound = 5;
int led = 13;
int inByte = 0;         // incoming serial byte
int koniec = 0;
unsigned long time;
char message[100];
int i = 0;
int g = 0;
uint8_t payload[100];


XBee xbee = XBee();

uint8_t payload1[] = { 0, 0 };

XBeeAddress64 addrU02 = XBeeAddress64(0x0013a200, 0x409F6E72);    // xbee 11
XBeeAddress64 addrU03 = XBeeAddress64(0x0013a200, 0x409F6E72);
//ZBTxRequest zbTxU02 = ZBTxRequest(addrU02, payload, sizeof(payload));
//ZBTxRequest zbTxU03 = ZBTxRequest(addrU03, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  Serial.begin(9600);
  Serial1.begin(38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(led, OUTPUT);
  pinMode(sound, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  if (Serial1.available() > 0) {  // chyba czeka blokująco
    koniec = 0;
    inByte = Serial1.read();
    if(i > 15){
      message[g] = (char)inByte;
      g++;
    }
    i++;
  } else if (koniec == 0) {
    koniec = 1;
    Serial.println("hahaha");
    int arraySize = sizeof(message)/sizeof(message[0]); 
    for(int i = 0; i < 3; i++){
      Serial.print(message[i]);
      payload[i] = uint8_t(message[i]); 
      Serial.print(payload[i]);
    }
    Serial.println();
    ZBTxRequest zbTxU03 = ZBTxRequest(addrU02, payload, sizeof(payload));
    xbee.send(zbTxU03);
    ControlResp();
    
   
    // time = millis();
    tone (sound, 5000, 500);  // dzwiek
    digitalWrite(led, HIGH); delay(500); digitalWrite(led, LOW);
  }

  switch (inByte) {
    case 'a':
      Serial.println(inByte);
      break;
    case 'b':
      digitalWrite(3, HIGH);
      break;
    case 'l':
      Serial.println("W lewo");
      break;
    case 'p':
      Serial.println("W prawo");
      break;
    default:
      // turn all the LEDs off:
      for (int thisPin = 2; thisPin < 3; thisPin++) {
        digitalWrite(thisPin, LOW);
      }
  }

  delay(10);
}


void ControlResp () {
  // after sending a tx request, we expect a status response
  // wait up to half second for the status response
  if (xbee.readPacket(500)) {  //zwraca true, jesli pakiet przyszedl, wpisuje go do bufora, nadpisuje poprzedni            
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        Serial.print("Success.");  
      } else {
        Serial.print("Error 3.");  
      }
    }
  } else if (xbee.getResponse().isError()) {
      Serial.print("Error reading packet.  Error code: ");  
      Serial.println(xbee.getResponse().getErrorCode());
  } else {
    Serial.print("Error 4.");  
  }
}
