/*********************************************************************************************************
*  Tick Tock Shield Basic Test Sequence 6: Extended LEDs
*
*  This lesson will show you how to use I2C driver PCF8574T.
*  
*  Author: dnaumov
*  2021-06-09
*  
*********************************************************************************************************/
#include <TTSExtension.h>
#include <TTSTime.h>
#include <Streaming.h>
#include <Wire.h>

TTSExtension PCF1;

TTSTime time;

int hour;
int min;
int sec;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    PCF1.setValue(0);
    time.setTime(12, 59, 55);
}

void loop()
{
    for(int i = 0; i < 16; i++){
      uint16_t mask = 1 << i;
      PCF1.setValue(mask);
      delay(70);
    }


  cout << time.getHour() << " : " << time.getMin() << " : " << time.getSec() << endl;

}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
