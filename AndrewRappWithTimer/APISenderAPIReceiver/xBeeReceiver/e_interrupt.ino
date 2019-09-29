void resetClock()           
{
     myClockMillis = millis() - prevClockMillis;                                             
     Serial.println("Interrupt 1");
     Serial.println(myClockMillis);
     prevClockMillis = millis();
}
