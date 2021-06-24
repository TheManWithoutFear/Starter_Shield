/*
  TTSBuzzer.h

  Author:Loovee
  2013-11-22
 
  The MIT License (MIT)
  Copyright (c) 2013 Seeed Technology Inc.

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

#ifndef __TTSBUZZER_H__
#define __TTSBUZZER_H__

#include <Arduino.h>

#define PINBUZZER               6           // pin of buzzer


class TTSBuzzer{

private:

    int __pin;
    bool alarming;                    // state of state, HIGH: on, LOW: off
    bool sound_state;                    // state of state, HIGH: on, LOW: off
public:

    TTSBuzzer()
    {
        __pin = PINBUZZER;
        alarming = false;
        pinMode(__pin, OUTPUT);
        analogWrite(__pin, 0);
        sound_state = false;
    }
    
    void on()                               // buzzer on
    {
        alarming = true;
        sound_state = true;
        analogWrite(__pin, 100);
    }
    
    void off()                              // buzzer off
    {
        alarming = false;
        sound_state = false;
        analogWrite(__pin, 0);
    }
    
    unsigned char state()                   // return state of buzzer, HIGH: on, LOW: off
    {
        return alarming;
    }
    void handler()
    {
        if(alarming){
            if(sound_state){
                sound_state = false;
                analogWrite(__pin, 0);
            }else{
                sound_state = true;
                analogWrite(__pin, 100);
            }
        }
    }  
};

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/