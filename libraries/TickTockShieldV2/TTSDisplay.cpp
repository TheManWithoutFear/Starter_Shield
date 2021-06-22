/*
 * TTSDisplay.cpp
 * A library for the 4 digit display
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Frankie.Chu
 * Create Time: 9 April,2012
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "TTSDisplay.h"
#include <Arduino.h>
static int8_t TubeTab[] = {0x3f,0x06,0x5b,0x4f,
                           0x66,0x6d,0x7d,0x07,
                           0x7f,0x6f,0x77,0x7c,
                           0x39,0x5e,0x79,0x71};//0~9,A,b,C,d,E,F
TTSDisplay::TTSDisplay(uint8_t Clk, uint8_t Data)
{
  Clkpin = Clk;
  Datapin = Data;
  pinMode(Clkpin,OUTPUT);
  pinMode(Datapin,OUTPUT);
}
TTSDisplay::TTSDisplay()
{
  Clkpin = 7;
  Datapin = 8;
  pinMode(Clkpin,OUTPUT);
  pinMode(Datapin,OUTPUT);
}
void TTSDisplay::init(void)
{
  clearDisplay();
}

int TTSDisplay::writeByte(int8_t wr_data)
{
  uint8_t i,count1;
  for(i=0;i<8;i++)        //sent 8bit data
  {
    digitalWrite(Clkpin,LOW);
    if(wr_data & 0x01)digitalWrite(Datapin,HIGH);//LSB first
    else digitalWrite(Datapin,LOW);
    wr_data >>= 1;
    digitalWrite(Clkpin,HIGH);

  }
  digitalWrite(Clkpin,LOW); //wait for the ACK
  digitalWrite(Datapin,HIGH);
  digitalWrite(Clkpin,HIGH);
  pinMode(Datapin,INPUT);

  bitDelay();
  uint8_t ack = digitalRead(Datapin);
  if (ack == 0) 
  {
     pinMode(Datapin,OUTPUT);
     digitalWrite(Datapin,LOW);
  }
  bitDelay();
  pinMode(Datapin,OUTPUT);
  bitDelay();
  
  return ack;
}
//send start signal to TTSDisplay
void TTSDisplay::start(void)
{
  digitalWrite(Clkpin,HIGH);//send start signal to TTSDisplay
  digitalWrite(Datapin,HIGH);
  digitalWrite(Datapin,LOW);
  digitalWrite(Clkpin,LOW);
}
//End of transmission
void TTSDisplay::stop(void)
{
  digitalWrite(Clkpin,LOW);
  digitalWrite(Datapin,LOW);
  digitalWrite(Clkpin,HIGH);
  digitalWrite(Datapin,HIGH);
}
//display function.Write to full-screen.
void TTSDisplay::display(int8_t DispData[])
{
  int8_t SegData[4];
  uint8_t i;
  for(i = 0;i < 4;i ++)
  {
    SegData[i] = DispData[i];
    InternalData[i] = DispData[i];
  }
  coding(SegData);
  start();          //start signal sent to TTSDisplay from MCU
  writeByte(ADDR_AUTO);//
  stop();           //
  start();          //
  writeByte(Cmd_SetAddr);//
  for(i=0;i < 4;i ++)
  {
    writeByte(SegData[i]);        //
  }
  stop();           //
  start();          //
  writeByte(Cmd_DispCtrl);//
  stop();           //
}
//******************************************
void TTSDisplay::display(uint8_t BitAddr,int8_t DispData)
{
    InternalData[BitAddr] = DispData;
  int8_t SegData;
  SegData = coding(DispData);
  start();          //start signal sent to TTSDisplay from MCU
  writeByte(ADDR_FIXED);//
  stop();           //
  start();          //
  writeByte(BitAddr|0xc0);//
  writeByte(SegData);//
  stop();            //
  start();          //
  writeByte(Cmd_DispCtrl);//
  stop();           //
}

void TTSDisplay::clearDisplay(void)
{
  display(0x00,0x7f);
  display(0x01,0x7f);
  display(0x02,0x7f);
  display(0x03,0x7f);
}
//To take effect the next time it displays.
void TTSDisplay::set(uint8_t brightness,uint8_t SetData,uint8_t SetAddr)
{
  Cmd_SetData = SetData;
  Cmd_SetAddr = SetAddr;
  Cmd_DispCtrl = 0x88 + brightness;//Set the brightness and it takes effect the next time it displays.
}

//Whether to light the clock point ":".
//To take effect the next time it displays.
void TTSDisplay::point(boolean PointFlag)
{
  _PointFlag = PointFlag;
}
void TTSDisplay::coding(int8_t DispData[])
{
  uint8_t PointData;
  if(_PointFlag == POINT_ON)PointData = 0x80;
  else PointData = 0;
  for(uint8_t i = 0;i < 4;i ++)
  {
    if(DispData[i] == 0x7f)DispData[i] = 0x00;
    else DispData[i] = TubeTab[DispData[i]] + PointData;
  }
}
int8_t TTSDisplay::coding(int8_t DispData)
{
  uint8_t PointData;
  if(_PointFlag == POINT_ON)PointData = 0x80;
  else PointData = 0;
  if(DispData == 0x7f) DispData = 0x00 + PointData;//The bit digital tube off
  else DispData = TubeTab[DispData] + PointData;
  return DispData;
}
void TTSDisplay::bitDelay(void)
{
	delayMicroseconds(50);
}

void TTSDisplay::num(int dta)
{
    if(dta < 0 || dta > 9999) return;           // bad data
    
    //clear();
    
    point(false);
    if(dta < 10)
    {
        display(3, dta);
        display(2, 0x7f);
        display(1, 0x7f);
        display(0, 0x7f);
    }
    else if(dta < 100)
    {
        display(0, dta/10);
        display(1, dta%10);
        display(1, 0x7f);
        display(0, 0x7f);
    }
    else if(dta < 1000)
    {
        display(1, dta/100);
        display(2, (dta/10)%10);
        display(3, dta%10);
        display(0, 0x7f);
    }
    else
    {
        display(0, dta/1000);
        display(1, (dta/100)%10);
        display(2, (dta/10)%10);
        display(3, dta%10);
    }
}

void TTSDisplay::pointOn()
{
    _PointFlag = 1;
    
    //FOR OLD DISPLAY:
    // for(int i=0; i<4; i++)
    // {
    //     display(i, dtaDisplay[i]);
    // }

    //FOR NEW DISPLAY
    display(1, InternalData[1]);
}   

void TTSDisplay::pointOff()
{
    _PointFlag = 0;
    
    //FOR OLD DISPLAY:
    // for(int i=0; i<4; i++)
    // {
    //     display(i, dtaDisplay[i]);
    // }

    //FOR NEW DISPLAY
    display(1, InternalData[1]);
}

void TTSDisplay::time(uint8_t hour, uint8_t min)
{
    if(hour > 24 || hour < 0) return;           // bad data
    if(min > 60 || min < 0) return;             // bad data

    display(0, hour/10);
    display(1, hour%10);
    display(2, min/10);
    display(3, min%10);
}