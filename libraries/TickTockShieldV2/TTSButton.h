/*
  TTSButton.h

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

#ifndef __TTSBUTTON_H__
#define __TTSBUTTON_H__

#include <Arduino.h>

#define TTSK1           9
#define TTSK2           10
#define TTSK3           11

class TTSButton{

private:

    int __pin;

public:

    TTSButton(int pin)
    {
        if(pin>11 || pin<9)return;
        
        __pin = pin;
        pinMode(__pin, INPUT);
        digitalWrite(__pin, HIGH);
    }
    
    char get()                         // return button state, HIGH or LOW, -1: pin err
    {
        if(__pin>11 || __pin<9)return -1;
        return (1 - digitalRead(__pin));
    }
    
    char pressed()                     // return HIGH when button is pressed, -1: pin err
    {
        if(__pin>11 || __pin<9)return -1;
        return get() ? HIGH : LOW;
    }
    
    char released()                    // return HIGH when button is released, -1: pin err
    {
        if(__pin>11 || __pin<9)return -1;
        return get() ? LOW : HIGH;
    }
    
};

class TTSButtonV2{
protected:
    String personal_name = "";
    TTSButton* pin_handler;

    int buttonState;             // the current reading from the input pin
    int lastButtonState;       // the previous reading from the input pin

    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
public:
    TTSButtonV2(int pin, String new_name)
    {
        pin_handler = new TTSButton(pin);

        personal_name = new_name;
        lastButtonState = LOW;
        lastDebounceTime = 0;
        debounceDelay = 50;
    }
    String GetName()
    {
        return personal_name;
    }

    void Handler()
    {
        int readedButtonState = pin_handler->get();

        if (readedButtonState != lastButtonState) {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > debounceDelay) {
            if (readedButtonState != buttonState) {
            buttonState = readedButtonState;

            // only toggle the LED if the new button state is HIGH
            if (buttonState == HIGH) {
                Serial.print("Pressed ");
                Serial.print(GetName());
                Serial.print("\n");
            }else{
                Serial.print("Released ");
                Serial.print(GetName());
                Serial.print("\n");
            }
            }
        }

        // save the reading. Next time through the loop, it'll be the lastButtonState:
        lastButtonState = readedButtonState;
    }
};

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/