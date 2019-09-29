void resetClock()           
{
     myClockMillis = millis() - prevClockMillis;                                             
     Serial.println(myClockMillis);
     prevClockMillis = millis();
}
