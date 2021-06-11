/*********************************************************************************************************
*  Tick Tock Shield Basic Test Sequence 6: RTC Test
*
*  This lesson will show you how to communicate with DS1307 - real time clock IC.
*  
*  Author: dnaumov
*  2021-06-09
*  
*********************************************************************************************************/
#include <Wire.h>
#include <TTSTime.h>
#include <Streaming.h>

TTSTime time;

int hour;
int min;
int sec;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    cout << "Welcome to RTC test." << endl;
    
    
    time.setTime(12, 59, 55);
}

void loop()
{
    cout << time.getHour() << " : " << time.getMin() << " : " << time.getSec() << endl;
    
    delay(1000);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
