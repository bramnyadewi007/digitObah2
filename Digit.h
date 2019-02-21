/*************************************************** 
  *
  *
  *
  *
  This is and additional library for using Morphing Digit on P10 dotmatrix display using DMD3 library. 
  DMD3 library original by Mr. Aziz Kurosaki.
  Morphing Digit original library Mr. Hari Wiguna , @HariFun/hwiguna on  https://github.com/hwiguna/HariFun_165_Morphing_Digits
  *
  *
  *
  *
  Ported and adjusted for p10 single color dmd,, by.Bram Ibe.  visit and support the webblog at https://arduinosoreang.blogspot.com
  and youtube channel bram ibe ....
  Thank u..
  All text above must be included in any redistribution  
 ****************************************************/


#ifndef DIGIT_H
#define DIGIT_H

#include <Arduino.h>

#include "Bitmap.h"
#include "DMD3.h"



class DMD3;
class Bitmap;

class Digit
{
  
  public:
    Digit(Bitmap* d, DMD3* f,byte value, int pixel, uint16_t xo, uint16_t yo, uint16_t color);
    void Draw(byte value);
    void Morph(byte newValue);
    byte Value();
    void DrawColon(uint16_t c);
    void swap();
	void clear();
	void swapcopy();
    void loop();
	
	
  private:
    DMD3* _disp;
    Bitmap* _display;
    byte _value;
    uint16_t _color;
    uint16_t xOffset;
    uint16_t yOffset;
	int segHeight;
	int segWidth;
    int animSpeed = 20;
    void drawPixel(uint16_t x, uint16_t y, uint16_t c);
    void drawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c);
    void drawLine(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t c);
    void drawSeg(byte seg);
	void Morph2();
    void Morph3();
    void Morph4();
    void Morph5();
    void Morph6();
    void Morph7();
    void Morph8();
    void Morph9();
    void Morph0();
    void Morph1();
	void repeat();
		
};

#endif
