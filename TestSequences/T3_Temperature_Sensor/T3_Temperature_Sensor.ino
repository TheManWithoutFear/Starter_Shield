/*********************************************************************************************************
*  Tick Tock Shield Test Sequence 3: Temperature Sensor
*
*  This lesson will show you how to use Temperature Sensor
*  
*
*  Author: dnaumov
*  2021-06-08
*  
*
*********************************************************************************************************/

#include <TTSTemp.h>

TTSTemp temp;         // instantiate an object of temperature sensor
int delay_val = 500;

void setup()
{
    Serial.begin(115200);
    Serial.println("Test sequence started. Touch the temperature sensor -> see ");
}

void loop()
{
  int temperature = temp.get();
  Serial.print("Current temperature: ");
  Serial.print(temperature);
  Serial.print(" °C. \n");
  delay(delay_val);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
