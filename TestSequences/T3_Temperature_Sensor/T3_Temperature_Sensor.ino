/*********************************************************************************************************
*  Tick Tock Shield Basic Test Sequence 3: Temperature Sensor
*
*  This lesson will show you how to use Temperature Sensor
*  
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
