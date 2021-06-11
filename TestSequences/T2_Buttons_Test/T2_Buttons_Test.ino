/*********************************************************************************************************
*  Tick Tock Shield Test Sequence 2: Buttons Test
*
*  This lesson will show you how to use buttons on device and library calls for 
*  them. Also provided an example for debounce handling.
*  
*
*  Author: dnaumov
*  2021-06-08
*  
*  
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
