#include "DMD3.h"
#include <Wire.h>
#include "RTClib.h"
#include "Digit.h"

#define OE 9
RTC_DS3231 rtc;
DMD3 display(2, 1);

Digit digit5(&display, &display, 0, 3, 0, 7, 1);
Digit digit4(&display, &display, 0, 3, 7, 7, 1);
Digit digit3(&display, &display, 0, 3, 16, 7, 1);
Digit digit2(&display, &display, 0, 3, 23, 7, 1);
Digit digit1(&display, &display, 0, 3, 32, 7, 1);
Digit digit0(&display, &display, 0, 3, 39, 7, 1);
//Digit digit0(&display, &display, byte awal, pixel per segment, koordinat x, koordinat y, 1(warna));
//animation speed setting in Digit.h-->animSpeed

byte prevmm, prevhh, hh, mm, ss;
byte prevss = 0;
char buf[30];

char dotw[7][7] = {"MINGGU", "SENIN", "SELASA", "RABU", "KAMIS", "JUMAT", "SABTU"};
char months[13][10] = {"", "JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI", "JUNI", "JULY", "AGUSTUS", "SEPTEMBER", "OKTOBER", "NOVEMBER", "DESEMBER"};

int x = 0;
int width = display.width();
unsigned long biyen = 0;
const long jeda = 200;


void scan() {
  display.refresh(); // update display
  Timer1.setPwmDuty(OE, 20); //set kecerahan berdasarkan nilai pwm
}


void setup() {
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan);
  Timer1.pwm(OE, 20);
  display.setDoubleBuffer(1);
  //display.setFont(SmallCap4x6);
  Wire.begin();
  rtc.begin();
  DateTime now = rtc.now();
  prevhh = now.hour() - 1;
  prevmm = now.minute() - 1;
  prevss = now.second();
}

void loop() {
  DateTime now = rtc.now();
  hh = now.hour();
  mm = now.minute();
  ss = now.second();
  sprintf(buf, "%08s,%02u-%09s-%04u ", dotw[now.dayOfTheWeek()], now.day(), months[now.month()], now.year());
  int msgWidth = display.textWidth(buf);
  int fullScroll = msgWidth + width + 1;

  unsigned long siki = millis();
  if (siki - biyen >= jeda) {
    biyen = siki;
    x++;
    display.drawText(width - x, 10, buf);
    display.swapBuffersAndCopy();
   
    if (x == fullScroll) {
      x = 0;
    }
  }

  if (ss == prevss) {
    digit5.Draw(hh / 10);
    digit4.Draw(hh % 10);
    digit3.Draw(mm / 10);
    digit2.Draw(mm % 10);
    digit1.Draw(ss / 10);
    digit0.Draw(ss % 10);

    display.drawLine(14, 2, 14, 3, 1);
    display.drawLine(14, 6, 14, 7, 1);
    display.drawLine(30, 2, 30, 3, 1);
    display.drawLine(30, 6, 30, 7, 1);
    display.swapBuffersAndCopy();
  }
  if (ss != prevss) {
    int s0 = ss % 10;
    int s1 = ss / 10;
    int m0 = mm % 10;
    int m1 = mm / 10;
    int h0 = hh % 10;
    int h1 = hh / 10;
    if (s0 != digit0.Value()) {
      digit0.Morph(s0);
    }
    if (s1 != digit1.Value()) {
      digit1.Morph(s1);
    }
    if (m0 != digit2.Value()) {
      digit2.Morph(m0);

    }
    if (m1 != digit3.Value()) {
      digit3.Morph(m1);
    }
    if (h0 != digit4.Value()) {
      digit4.Morph(h0);
    }
    if (h1 != digit5.Value()) {
      digit5.Morph(h1);
    }


  }
  prevss = ss;
  prevmm = mm;
  prevhh = hh;
  display.swapBuffers();
  display.drawLine(14, 2, 14, 3, 0);
  display.drawLine(14, 6, 14, 7, 0);
  display.drawLine(30, 2, 30, 3, 0);
  display.drawLine(30, 6, 30, 7, 0);


}

