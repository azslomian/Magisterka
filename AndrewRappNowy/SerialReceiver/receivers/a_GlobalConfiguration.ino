#include <XBee.h>
#include <Printers.h>

XBee xbee = XBee();

uint8_t payload[] = { 0, 0 };
uint8_t messageForSerialSend[] = {126, 0, 14, 144, 0, 125, 51, 162, 0, 64, 167, 57, 237, 139, 32, 1, 0, 0, 1}; 

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


XBeeAddress64 addrU = addrU10;   //to configure
ZBTxRequest zbTxU;
ZBTxStatusResponse txStatus = ZBTxStatusResponse();


volatile int output = LOW; 
unsigned long myClockMillis=0;   
unsigned long prevClockMillis=0; 
int resetPin = 2;  // Only pins 2 and 3 are available for interrupts 
int numberOfBytes = 0;
int isFirstByte = 0;
int table[150];
int myBufferMessage[150]; 

int pin5 = 0;
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
