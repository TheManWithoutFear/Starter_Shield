/*********************************************************************************************************
*  Tick Tock Shield Test Sequence 4: Light Sensor
*
*  This lesson will show you how to use Light Sensor
*  
*
*  Author: dnaumov
*  2021-06-08
*  
*  
*********************************************************************************************************/

#include <TTSLight.h>

TTSLight light;          // instantiate an object of light sensor
int delay_val = 500;

void setup()
{
    Serial.begin(115200);
    Serial.println("Test sequence started. Expose and overshadow light sensor to the ambient light.");
    Serial.println("Check measurment results in terminal.");
    Serial.println("Min value is 0 units. Max value is 1023 units.");
    Serial.println(" ");
}

void loop()
{
  int light_level = light.get();
  Serial.print("Current light level: ");
  Serial.print(light_level);
  Serial.print(" units. \n");
  delay(delay_val);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
