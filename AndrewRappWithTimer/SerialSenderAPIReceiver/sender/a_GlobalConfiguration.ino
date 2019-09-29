#include <XBee.h>

XBee xbee = XBee();

uint8_t payload[] = { 0, 0 };
//uint8_t messageForSerialSend[] = {126, 0, 14, 144, 0, 125, 51, 162, 0, 64, 167, 57, 237, 139, 32, 1, 0, 0, 1};   //from 10 to 11
//uint8_t messageForSerialSend[] = {126, 0, 14, 144, 0, 125, 51, 162, 0, 64, 159, 110, 114, 155, 6, 1, 0, 0, 89};    //from 11 to 10
//uint8_t messageForSerialSend[] = {126, 0, 14, 144, 0, 125, 51, 162, 0, 64, 167, 58, 125, 51, 215, 27, 1, 0, 0, 147};    //from 9 to 10 
//uint8_t messageForSerialSend[] = {126, 0, 14, 144, 0, 125, 51, 162, 0, 64, 167, 57, 237, 139, 32, 1, 0, 0, 1};   //from 10 to 9
//uint8_t messageForSerialSend[] = {126, 0, 19, 162, 0, 64, 167, 58, 19, 64, 167, 58, 125, 51, 215, 27, 1, 0, 0, 147}; // address to 9
//long sum = 162 + 0 + 0 + 0 + 0 + 0 + 0 + 0xFF + 0xFF + 0xFF + 0xFE + 0 + 0x00 + 0 + 0 + 0; 
//long result = 0xFF - (sum & 0xFF);
//uint8_t messageForSerialSend[] = {0x7E, 0, 0x10, 162, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFE, 0, 0x00, 0, 0, 0, result};
uint8_t messageForSerialSend[] = {0x7E, 0x00, 0x10, 0x10, 0x01, 0x00, 0x7D, 0x33, 0xA2, 0x00, 0x40, 0xA7, 0x3A, 0x7D, 0x33, 0xFF, 0xFE, 0x00, 0x00, 0x30, 0x30, 0xA8};

//7E 00 10 10 01 00 7D 33 A2 00 40 A7 3A 7D 33 FF FE 00 00 30 30 A8
//7E 00 12 10 01 00 7D 33 A2 00 40 A7 3A 7D 33 FF FE 00 00 30 30 6E

//00 13 A2 00 40 A7 3A 13

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

int AP=2;  //1 , 2
int BaudRateXBee = 38400;
int SerialMonitorBaudRate = 9600;
int sizeOfFrame = 16;

XBeeAddress64 addrU = addrU09;   //to configure
ZBTxRequest zbTxU = ZBTxRequest(addrU, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int statusLed = 13;
int errorLed = 13;
int inByte = 0;
int endOfMessage = 0;
int i = 0;
int g = 0;
char message[100];
unsigned long sendingTime;
unsigned long responseTime;
long resultTime;
unsigned long meanResponseTime = 0;



//SyncTime
unsigned long  arduino_time;
unsigned long clock_sync_complete;
unsigned long srm_time;
unsigned long sync_diff_time;
unsigned long run_table_start_time;
bool rjc_ready = false;
bool route_complete = false;
bool WAIT_FOR_CLOCK_SYNC = false;
int ID_NUMBER;
int run_table_row_count;
float run_table_rows[100][2];
