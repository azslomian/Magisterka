#include <XBee.h>

XBee xbee = XBee();

uint8_t payload[] = { 46, 46, 56, 56, 56, 88, 88, 88,
0, 0, 0, 0, 0, 0, 0, 0,
46, 46, 56, 56, 56, 88, 88, 88,
46, 46, 56, 56, 56, 88, 88, 88,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
22, 22, 22, 2, 22, 0, 22, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
2, 9, 2, 5
};

//uint8_t payload[] = { 0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0, 0, 0
//};

//uint8_t payload[] = { 0, 0 };

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
XBeeAddress64 addrBroadcast = XBeeAddress64(0x00000000, 0x0000FFFF);
XBeeAddress64 addrUndefined = XBeeAddress64(0xFFFFFFFF, 0xFFFFFFFF);

uint16_t addrLogU09 = 0xFF0A;

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

//resetClock
 unsigned long myMillis=0;   
 unsigned long prevMillis=0; 
 unsigned long startTimeMillis=0; 
 unsigned long restTimerMillis=0; 
 int resetPin = 3;  
 int stopLoop = 0;

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
