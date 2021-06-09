/*********************************************************************************************************
*  Tick Tock Shield Basic Test Sequence 6: Display
*
*  This lesson will show you how to use Display driver TM1637.
*  
*  Author: dnaumov
*  2021-06-09
*  
*********************************************************************************************************/
#include <Streaming.h>
#include <TTSDisplay.h>
#include <Wire.h>

TTSDisplay display;

void setup()
{
    display.num(1234);
    delay(1000);
}

void loop()
{
    display.pointOn();
    delay(500);
    display.pointOff();
    delay(500);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
