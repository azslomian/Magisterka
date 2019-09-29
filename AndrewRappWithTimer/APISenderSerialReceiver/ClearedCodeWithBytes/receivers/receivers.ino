
/*
  Po odebraniu znaku z Serial1 (Xbee): mrugniecie dioda, dźwięk, odeslanie znaku na Serial (serial monitor)
*/

// Pin 13 has an LED connected on most Arduino boards.
int en_sound = 4;
int sound = 5;
int led = 13;        // incoming serial byte
int koniec = 0;



// the setup routine runs once when you press reset:
