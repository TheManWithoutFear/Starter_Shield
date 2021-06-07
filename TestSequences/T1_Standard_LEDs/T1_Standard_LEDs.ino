/*********************************************************************************************************
*  Tick Tock Shield Basic Lesson 8: Temperature Sensor
*
*  This lesson will show you how to use Temperature Sensor
*  And display the value in 7-SEG display
*
*  Author: Loovee
*  2013-11-25
*  
*  you may use the following functon:
*  
*  temp.get()                                       // return value of temperature sensor
*
*  disp.display(int loca, int num);                 // control a  nixie tube
*  disp.num(int num);                               // display a number
*  disp.time(int hour, int min);                    // display time
*  disp.clear();                                    // clear display
*  disp.pointOn();                                  // display :
*  disp.pointOff();                                 // clear :
*********************************************************************************************************/

#include <TTSLed.h>

TTSLed led1(TTSLED1);                       // instantiate an object of led1
TTSLed led2(TTSLED2);                       // instantiate an object of led2
TTSLed led3(TTSLED3);                       // instantiate an object of led3
TTSLed led4(TTSLED4);                       // instantiate an object of led4

TTSLed* leds_ptr[4];

int delay_val = 500;

void setup()
{
    leds_ptr[0] = &led1;
    leds_ptr[1] = &led2;
    leds_ptr[2] = &led3;
    leds_ptr[3] = &led4;
}

void loop()
{
    for(int i = 0; i < 4; i++)
    {
      leds_ptr[i]->on();
      delay(delay_val);
      leds_ptr[i]->off();
      delay(delay_val);
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
