void resetClock()           
{
     //myClockMillis = millis() - prevClockMillis;                                             
     Serial.println("przerwanie");
     prevClockMillis = millis();
}
