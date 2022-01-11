/*
display.h - Video Remoto en Tiempo Real. Display routines.
v1.0

Copyright © 2020-2022 Francisco Rafael Reyes Carmona.
All rights reserved.
rafael.reyes.carmona@gmail.com
_______________________________________________________________________
|                                                                     |
|  No part of this work may be distributed, reproduced, copied,       |
|  stored in a retrieval system, or transcribed in any form or        |
|  by any means, electronic or mechanical, beyond the terms of the    |
|  License.                                                           |
|                                                                     |
|  This code is distributed "as is" without warranty of any kind,     |
|  including warranties of merchantability, fitness for a particular  |
|  purpose, or fitness for a particular purpose.                      |
|                                                                     |
|  The author shall not be liable for any damages of any kind arising |
|  out of the use, including loss of business or loss of data.        |
|_____________________________________________________________________|

  This file is part of VRTR Project.

  VRTR Project is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  VRTR Project is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with VRTR Project.  If not, see <https://www.gnu.org/licenses/>.

*/

#include <U8x8lib.h>
#include <U8g2lib.h>

#include "logostart.h"

#if defined(SDD1306_128X64)
  #define SCREEN_WIDTH 128 // OLED display width, in pixels
  #define SCREEN_HEIGHT 64 // OLED display height, in pixels
  #define display_offset 0
  // Crea el objeto u8g2 para pantalla OLED 0.96" 128x64 px.
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);
#elif defined(SH1106_128X64)
  #define SCREEN_WIDTH 128 // OLED display width, in pixels
  #define SCREEN_HEIGHT 64 // OLED display height, in pixels
  #define display_offset 0
  // Crea el objeto u8g2 para pantalla OLED 1.30" 128x64 px.
  U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);
#elif defined(HX1230_96X68)
  #include <SPI.h>
  #define LCD_DIN 11
  #define LCD_CLK 13
  #define LCD_RST 5
  #define LCD_CS  12
  #define LCD_BL  6
  #define SCREEN_WIDTH 96 // OLED display width, in pixels
  #define SCREEN_HEIGHT 68 // OLED display height, in pixels
  #define display_offset 32
  U8G2_HX1230_96X68_1_3W_HW_SPI u8g2(U8G2_R0, /* clock=*/ LCD_CLK, /* data=*/ LCD_DIN, /* cs=*/ LCD_CS, /* reset=*/ LCD_RST);
#endif

void drawlogo(void) {
  u8g2.firstPage();  
  do {  // graphic commands to redraw the complete screen should be placed here  
#if defined(SDD1306_128X64) || defined(SH1106_128X64)
    u8g2.setFont(u8g2_font_helvR10_tf);
    u8g2.setCursor(20,0);
#elif defined(HX1230_96X68)
    //u8g2.setFont(u8g2_font_logisoso16_tf);
    u8g2.setFont(u8g2_font_t0_13b_mf);    
    u8g2.setCursor(10,0);
#endif
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.print(F("VRTR Project"));

#if defined(SDD1306_128X64) || defined(SH1106_128X64)
    u8g2.drawXBMP( 31, 16, 64, 48, LogoStart);
#elif defined(HX1230_96X68)
    u8g2.drawXBMP( 16, 18, 64, 48, LogoStart);
#endif
  } while( u8g2.nextPage() );
}

void drawlowbat(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g2.firstPage();  
  do {
#if defined(SDD1306_128X64) || defined(SH1106_128X64)
    u8g2.setFont(u8g2_font_helvR10_tf);
    u8g2.setCursor(5,0);
#elif defined(HX1230_96X68)
    //u8g2.setFont(u8g2_font_logisoso16_tf);
    u8g2.setFont(u8g2_font_t0_13b_mf);    
    u8g2.setCursor(0,0);
#endif
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.print(F("LOW BATTERY!!!"));
#if defined(SDD1306_128X64) || defined(SH1106_128X64)
    u8g2.drawXBMP( 36, 16, 56, 48, IconLowBattery);
#elif defined(HX1230_96X68)
    u8g2.drawXBMP( 20, 18, 56, 48, IconLowBattery);
#endif  
    
  } while( u8g2.nextPage() );
}
void mesg(const char* text) {
  uint8_t h;
  u8g2_uint_t c, d, l;
  u8g2.firstPage();
  do  {
#if defined(SDD1306_128X64) || defined(SH1106_128X64)
    u8g2.setFont(u8g2_font_helvR10_tf);
#elif defined(HX1230_96X68)
    //u8g2.setFont(u8g2_font_logisoso16_tf);
    u8g2.setFont(u8g2_font_t0_13b_mf);    
#endif
//    h = u8g2.getAscent()-u8g2.getDescent();
    h = u8g2.getMaxCharHeight();
    l = u8g2.getStrWidth(text);
    d = ((SCREEN_WIDTH - l) / 2) - 1;
    c = ((SCREEN_HEIGHT - h) / 2) - 1;

    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setCursor(d, c);
    u8g2.print(text);
    u8g2.drawFrame(d - 5, c - 5, l + 8, h + 8);
  } while( u8g2.nextPage() );
}

void warning_mesg(const char* text) {
  
}

void drawiconant () {
  char ch_str[3];

  itoa(CHANNEL, ch_str, 10);

  u8g2.drawLine(2, 0, 5, 0);
  u8g2.drawLine(0, 2, 0, 5);
  u8g2.drawLine(7, 2, 7, 5);
  u8g2.drawLine(3, 2, 4, 2);
  u8g2.drawLine(2, 3, 2, 4);
  u8g2.drawLine(5, 3, 5, 4);
  u8g2.drawPixel(1, 1);
  u8g2.drawPixel(6, 1);
  u8g2.drawPixel(1, 6);
  u8g2.drawPixel(6, 6);
  u8g2.drawLine(3, 6, 3, 13);
  u8g2.drawLine(4, 6, 4, 13);
  u8g2.drawLine(1, 14, 6, 14);
  u8g2.drawLine(0, 15, 7, 15);
  
#if defined(SDD1306_128X64) || defined(SH1106_128X64)
  // Draw channel of transmision.
  u8g2.setCursor(17,3);
  u8g2.print(F("CH:"));
  /*
  u8g2.drawXBMP(12, 0, 5, 8, LT);
  u8g2.drawXBMP(12, 8, 5, 8, LL);
  u8g2.drawXBMP(17, 0, 5, 8, UB);
  u8g2.drawXBMP(17, 8, 5, 8, LB);

  u8g2.drawXBMP(27, 0, 5, 8, BLOCK);
  u8g2.drawXBMP(27, 8, 5, 8, BLOCK);
  u8g2.drawXBMP(32, 0, 5, 8, LB);
  //u8g2.drawXBMP(32, 8, 5, 8, UB);
  u8g2.drawXBMP(37, 0, 5, 8, BLOCK);
  u8g2.drawXBMP(37, 8, 5, 8, BLOCK);
  */
#endif
  switch (ch_str[0]) {
    case '1':
      u8g2.drawXBMP(52-display_offset, 0, 5, 8, UB);
      u8g2.drawXBMP(57-display_offset, 0, 5, 8, RT);
      u8g2.drawXBMP(57-display_offset, 8, 5, 8, BLOCK);
      break;
      
    case '2':
      u8g2.drawXBMP(52-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(52-display_offset, 8, 5, 8, LL);
      u8g2.drawXBMP(57-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(57-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(62-display_offset, 0, 5, 8, RT);
      u8g2.drawXBMP(62-display_offset, 8, 5, 8, LMB);
      break;
      
    case '3':
      u8g2.drawXBMP(52-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(52-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(57-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(57-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(62-display_offset, 0, 5, 8, RT);
      u8g2.drawXBMP(62-display_offset, 8, 5, 8, LR);
      break;
      
    case '4':
      u8g2.drawXBMP(52-display_offset, 0, 5, 8, LL);
      //u8g2.drawXBMP(52-display_offset, 8, 5, 8, LL);
      u8g2.drawXBMP(57-display_offset, 0, 5, 8, LB);
      //u8g.drawXBMP(57-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(62-display_offset, 0, 5, 8, RT);
      u8g2.drawXBMP(62-display_offset, 8, 5, 8, BLOCK);
      break;
      
    case '5':
      u8g2.drawXBMP(52-display_offset, 0, 5, 8, LT);
      u8g2.drawXBMP(52-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(57-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(57-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(62-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(62-display_offset, 8, 5, 8, LR);
      break;
      
    case '6':
      u8g2.drawXBMP(52-display_offset, 0, 5, 8, LT);
      u8g2.drawXBMP(52-display_offset, 8, 5, 8, LL);
      u8g2.drawXBMP(57-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(57-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(62-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(62-display_offset, 8, 5, 8, LR);
      break;

    default:
      u8g2.drawXBMP(52-display_offset, 0, 5, 8, LB);
      u8g2.drawXBMP(57-display_offset, 0, 5, 8, LB);
      u8g2.drawXBMP(62-display_offset, 0, 5, 8, LB);
  }
  
  switch (ch_str[1]) {
    case '1':
      u8g2.drawXBMP(72-display_offset, 0, 5, 8, UB);
      u8g2.drawXBMP(77-display_offset, 0, 5, 8, RT);
      u8g2.drawXBMP(77-display_offset, 8, 5, 8, BLOCK);
      break;
      
    case '2':
      u8g2.drawXBMP(72-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(72-display_offset, 8, 5, 8, LL);
      u8g2.drawXBMP(77-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(77-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(82-display_offset, 0, 5, 8, RT);
      u8g2.drawXBMP(82-display_offset, 8, 5, 8, LMB);
      break;
      
    case '3':
      u8g2.drawXBMP(72-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(72-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(77-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(77-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(82-display_offset, 0, 5, 8, RT);
      u8g2.drawXBMP(82-display_offset, 8, 5, 8, LR);
      break;
      
    case '4':
      u8g2.drawXBMP(72-display_offset, 0, 5, 8, LL);
      //u8g2.drawXBMP(72-display_offset, 8, 5, 8, LL);
      u8g2.drawXBMP(77-display_offset, 0, 5, 8, LB);
      //u8g2.drawXBMP(77-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(82-display_offset, 0, 5, 8, RT);
      u8g2.drawXBMP(82-display_offset, 8, 5, 8, BLOCK);
      break;
      
    case '5':
      u8g2.drawXBMP(72-display_offset, 0, 5, 8, LT);
      u8g2.drawXBMP(72-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(77-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(77-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(82-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(82-display_offset, 8, 5, 8, LR);
      break;
      
    case '6':
      u8g2.drawXBMP(72-display_offset, 0, 5, 8, LT);
      u8g2.drawXBMP(72-display_offset, 8, 5, 8, LL);
      u8g2.drawXBMP(77-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(77-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(82-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(82-display_offset, 8, 5, 8, LR);
      break;

    case '7':
      u8g2.drawXBMP(72-display_offset, 0, 5, 8, UB);
      //u8g2.drawXBMP(72-display_offset, 8, 5, 8, LL);
      u8g2.drawXBMP(77-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(77-display_offset, 8, 5, 8, BLOCK);
      u8g2.drawXBMP(82-display_offset, 0, 5, 8, RT);
      //u8g2.drawXBMP(82-display_offset, 8, 5, 8, UB);
      break;

    case '8':
      u8g2.drawXBMP(72-display_offset, 0, 5, 8, LT);
      u8g2.drawXBMP(72-display_offset, 8, 5, 8, LL);
      u8g2.drawXBMP(77-display_offset, 0, 5, 8, UMB);
      u8g2.drawXBMP(77-display_offset, 8, 5, 8, LMB);
      u8g2.drawXBMP(82-display_offset, 0, 5, 8, RT);
      u8g2.drawXBMP(82-display_offset, 8, 5, 8, LR);
      break;

    default:
      u8g2.drawXBMP(72-display_offset, 0, 5, 8, LB);
      u8g2.drawXBMP(77-display_offset, 0, 5, 8, LB);
      u8g2.drawXBMP(82-display_offset, 0, 5, 8, LB);
  }
}
void drawiconbatcharge() {
   
  u8g2.drawLine(93-display_offset, 0, 124-display_offset, 0);
  u8g2.drawLine(93-display_offset, 15, 124-display_offset, 15);
  u8g2.drawLine(93-display_offset, 1, 93-display_offset, 14);
  u8g2.drawLine(126-display_offset, 2, 126-display_offset, 13);
  u8g2.drawLine(127-display_offset, 6, 127-display_offset, 9);
  u8g2.drawPixel(125-display_offset, 1);
  u8g2.drawPixel(125-display_offset, 14);

  u8g2.drawXBMP(98-display_offset, 3, 24, 12, BAT_CHG);
}

void drawiconbat(byte percent) {
  char percent_str[3] = "ff";

  if (percent < 100) sprintf(percent_str, "%02d", percent);
  
  u8g2.drawLine(93-display_offset, 0, 124-display_offset, 0);
  u8g2.drawLine(93-display_offset, 15, 124-display_offset, 15);
  u8g2.drawLine(93-display_offset, 1, 93-display_offset, 14);
  u8g2.drawLine(126-display_offset, 2, 126-display_offset, 13);
  u8g2.drawLine(127-display_offset, 6, 127-display_offset, 9);
  u8g2.drawPixel(125-display_offset, 1);
  u8g2.drawPixel(125-display_offset, 14);

  word w = percent * 3 / 10;
  
  u8g2.drawHLine(95-display_offset, 2, w);
  u8g2.drawHLine(95-display_offset, 13, w);
  if (w > 28) u8g2.drawVLine(123-display_offset, 2, 12);
  if (w > 27) u8g2.drawVLine(122-display_offset, 2, 12);
  if (w > 2) u8g2.drawVLine(97-display_offset, 2, 12);
  if (w > 1) u8g2.drawVLine(96-display_offset, 2, 12);
  if (w > 0) u8g2.drawVLine(95-display_offset, 2, 12);

  switch(percent_str[0]) {
    case '0':
      //u8g.drawXBMP(99, 4, 6, 8, BAT_0);
      break;
    case '1':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_1);
      break;
    case '2':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_2);
      break;
    case '3':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_3);
      break;
    case '4':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_4);
      break;
    case '5':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_5);
      break;
    case '6':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_6);
      break;
    case '7':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_7);
      break;
    case '8':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_8);
      break;
    case '9':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_9);
      break;
  }

  switch(percent_str[1]) {
    case '0':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_0);
      break;
    case '1':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_1);
      break;
    case '2':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_2);
      break;
    case '3':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_3);
      break;
    case '4':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_4);
      break;
    case '5':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_5);
      break;
    case '6':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_6);
      break;
    case '7':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_7);
      break;
    case '8':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_8);
      break;
    case '9':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_9);
      break;
  }

  if (percent < 100) {
        u8g2.drawXBMP(115-display_offset, 4, 6, 8, PER);
      }
      else {
        u8g2.drawXBMP(98-display_offset, 4, 24, 8, FULL_BAT);
        u8g2.drawLine(98-display_offset, 3, 121-display_offset, 3);
        u8g2.drawLine(98-display_offset,12, 121-display_offset,12);
        u8g2.drawLine(121-display_offset,4, 121-display_offset,11);
        u8g2.drawLine(124-display_offset,3, 124-display_offset,12);
      }
}

void drawtemp() {
  u8g2.drawXBMP(120-display_offset, (SCREEN_HEIGHT*3/4), 8, 16, TERMO);
}

void printdata(float battery_value, float battery_amp_value, byte battery_percent, 
                float t_amb, float t_ts832) {
  char bat_str[10];
  char amp_str[10];
  char temp_str[18];
  char buf[6];

  //t_amb = 38.9;    // Declaraciones para realizar pruebas.
  //t_ts832 = 68.6;
  
  dtostrf(battery_value, 2, 2, bat_str);
  //sprintf(bat_str, "%02f",battery_value);
  strcat_P(bat_str, (const char*) F(" V."));
  
  dtostrf(battery_amp_value, 4, 0, amp_str);
  //sprintf(amp_str, "%04.0d", battery_amp_value);
  strcat_P(amp_str, (const char*) F(" mA."));
  
  dtostrf(t_amb, 2, 1, temp_str);
  dtostrf(t_ts832, 2, 1, buf);
#if defined(SDD1306_128X64) || defined(SH1106_128X64)
  strcat_P(temp_str,(const char*) F("\260C,"));
  strcat(temp_str, buf);
  strcat_P(temp_str, (const char*) F("\260C"));
#elif defined(HX1230_96X68)
  strcat_P(temp_str,(const char*) F("\260,"));
  strcat(temp_str, buf);
  strcat_P(temp_str, (const char*) F("\260"));
#endif
  u8g2.firstPage();
  do  {
#if defined(SDD1306_128X64) || defined(SH1106_128X64)
    u8g2.setFont(u8g2_font_helvR10_tf);
#elif defined(HX1230_96X68)
    //u8g2.setFont(u8g2_font_logisoso16_tf);
    u8g2.setFont(u8g2_font_t0_13b_mf);
#endif
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
#if defined(SDD1306_128X64) || defined(SH1106_128X64)
    u8g2.drawXBMP(0,18,24, 43, AmpVolt);
#endif
    u8g2.drawStr(45-display_offset,SCREEN_HEIGHT/4,bat_str);
    u8g2.drawXBMP(112-display_offset, (SCREEN_HEIGHT/4)+1, 16, 12, MINIBATPLUSMINUS);
    u8g2.drawStr(40-display_offset,SCREEN_HEIGHT/2,amp_str);
    u8g2.drawXBMP(120-display_offset, SCREEN_HEIGHT/2, 8, 12, (battery_amp_value > 0 ? MINIBAT : PLUG) );
    u8g2.drawStr((25-display_offset)<0 ? 0 : 25,SCREEN_HEIGHT*3/4,temp_str);
  
    if (battery_amp_value < 0) drawiconbatcharge(); 
    else drawiconbat(battery_percent);
    drawiconant();
    drawtemp();
  } while( u8g2.nextPage() );
}
