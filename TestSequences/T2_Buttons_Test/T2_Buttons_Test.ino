/*********************************************************************************************************
*  Tick Tock Shield Basic Lesson 8: Temperature Sensor
*
*  This lesson will show you how to use Temperature Sensor
*  And display the value in 7-SEG display
*
*  Author: dnaumov
*  2021-06-08
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

#include <TTSButton.h>

TTSButtonV2 keyDown(TTSK1,  "DOWN");                   // instantiate an object of button1
TTSButtonV2 keyUp(TTSK2,    "UP");                     // instantiate an object of button2
TTSButtonV2 keyMode(TTSK3,  "FUNC");                   // instantiate an object of button3

TTSButtonV2* all_keys[3];

void setup()
{
    all_keys[0] = &keyDown;
    all_keys[1] = &keyUp;
    all_keys[2] = &keyMode;
    
    Serial.begin(115200);
    Serial.println("Test sequence started. Press buttons and observe terminal");
}

void loop()
{
    for(int i = 0; i < 3; i++)
    {
      all_keys[i]->Handler();
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
