/*
  TTSExtension.cpp

  Author:dnaumov
  2021-06-10
 
  The MIT License (MIT)
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/


#include "TTSExtension.h"

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define LOW_ADDR     0x20
#define HIGH_ADDR    0x21

void TTSExtension::setValue(uint16_t new_value)
{
    uint16_t temp = ~new_value;
     uint8_t low_value = lowByte(temp);
     uint8_t high_value = highByte(temp);

    Wire.beginTransmission(LOW_ADDR);
    Wire.write(low_value);
    Wire.endTransmission(true);

    Wire.beginTransmission(HIGH_ADDR);
    Wire.write(high_value);
    Wire.endTransmission(true);
}

void TTSExtension::on()
{
  light_alarm = true;
  light_state = true;
  blink_cnt = 2000;
//  setValue(0xFFFF);
}

void TTSExtension::off()
{
  light_alarm = false;
  light_state = false;
  blink_cnt = 0;
  setValue(0);
}

void TTSExtension::handler()
{
  if(blink_cnt == 0){
    blink_cnt = 2000;
    if(light_alarm){
        if(light_state){
            light_state = false;
            setValue(0);
        }else{
            light_state = true;
            setValue(0xFFFF);
        }
    }
  }
  blink_cnt--;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/