/*********************************************************************************************************
*  Tick Tock Shield Test Sequence 1: Standard LEDs
*  
*  
*
*  Author: dnaumov
*  2021-06-07
*  
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

    Serial.begin(115200);
    Serial.println("Test sequence started. Observe standard LEDs blinking.");
}

void loop()
{
    for(int i = 0; i < 4; i++)
    {
      Serial.print("Turning LED №");
      int n = i + 1;
      Serial.print(n);
      Serial.print(" ON.\n");
      leds_ptr[i]->on();
      delay(delay_val);
      Serial.print("Turning LED №");
      Serial.print(n);
      Serial.print(" OFF.\n");
      leds_ptr[i]->off();
      delay(delay_val);
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
