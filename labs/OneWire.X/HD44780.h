/* 
 * File:   HD44780.h
 * Author: mustafa
 *
 * Created on 15 Nisan 2014 Sal?, 01:57
 */

#ifndef HD44780_H
#define	HD44780_H

//******************************************
//  Library for control LCD HD44780        *
//  Mode Control 4 bits                    *
//  By Hector                              *
//  http://www.youtube.com/user/Hector8389 *
//******************************************

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _XTAL_FREQ 8000000 // Select your XTAL
#define CLOCK_FREQ  8000000

/////////////////////////////////////////////
//                                         //
// Configure your MCU. Any mode            //
// Pin Set digital mode. your code         //
//                                         //
/////////////////////////////////////////////

#define LCD_RD7     PORTBbits.RB3       // D7
#define TRISRD7     TRISBbits.TRISB3

#define LCD_RD6     PORTBbits.RB2       // D6
#define TRISRD6     TRISBbits.TRISB2

#define LCD_RD5     PORTBbits.RB1       // D5
#define TRISRD5     TRISBbits.TRISB1

#define LCD_RD4     PORTBbits.RB0       // D4
#define TRISRD4     TRISBbits.TRISB0

#define LCD_EN      PORTBbits.RB5       // EN
#define TRISEN      TRISBbits.TRISB5

#define LCD_RS      PORTBbits.RB4       // RS
#define TRISRS      TRISBbits.TRISB4

/////////////////////////////////////////////
//                                         //
// Available Lcd Commands                  //
//                                         //
/////////////////////////////////////////////

#define      LCD_FIRST_ROW           128
#define      LCD_SECOND_ROW          192
#define      LCD_THIRD_ROW           148
#define      LCD_FOURTH_ROW          212
#define      LCD_CLEAR               1
#define      LCD_RETURN_HOME         2
#define      LCD_CURSOR_OFF          12
#define      LCD_UNDERLINE_ON        14
#define      LCD_BLINK_CURSOR_ON     15
#define      LCD_MOVE_CURSOR_LEFT    16
#define      LCD_MOVE_CURSOR_RIGHT   20
#define      LCD_TURN_OFF            0
#define      LCD_TURN_ON             8
#define      LCD_SHIFT_LEFT          24
#define      LCD_SHIFT_RIGHT         28

void Lcd_Init(void);
void Lcd_Out(unsigned char y, unsigned char x, const char *buffer);
void Lcd_Out2(unsigned char y, unsigned char x, char *buffer);
void Lcd_Chr(unsigned char y, unsigned char x, char Chr);
void Lcd_Chr_CP(char Chr_CP);
void Lcd_Cmd(unsigned char Cmd);
void Delay_5us(void);
void Delay_5500us(void);

void Delay_5us(void){
__delay_us(5);
__delay_us(5);
}

void Delay_5500us(void){
__delay_us(5500);
}

void Lcd_Init(void){
unsigned char data;
TRISRD7 = 0; TRISRD6 = 0; TRISRD5 = 0; TRISRD4 = 0; TRISEN = 0; TRISRS = 0;
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 0; LCD_RD4 = 0; LCD_EN = 0; LCD_RS = 0;
Delay_5500us(); Delay_5500us(); Delay_5500us();
Delay_5500us(); Delay_5500us(); Delay_5500us();
for(data = 1; data < 4; data ++)
   {
    LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 1; LCD_EN = 0; LCD_RS = 0;
    LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 1; LCD_EN = 1; LCD_RS = 0;
    Delay_5us();
    LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 1; LCD_EN = 0; LCD_RS = 0;
    Delay_5500us();
   }
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 0; LCD_EN = 0; LCD_RS = 0;
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 0; LCD_EN = 1; LCD_RS = 0;
Delay_5us();
LCD_RD7 = 0; LCD_RD6 = 0; LCD_RD5 = 1; LCD_RD4 = 0; LCD_EN = 0; LCD_RS = 0;
Delay_5500us();
data = 40; Lcd_Cmd(data);
data = 16; Lcd_Cmd(data);
data = 1;  Lcd_Cmd(data);
data = 15; Lcd_Cmd(data);
}

void Lcd_Out(unsigned char y, unsigned char x, const char *buffer){
unsigned char data;
switch(y){
case 1: data = 127 + x; break;
case 2: data = 191 + x; break;
case 3: data = 147 + x; break;
case 4: data = 211 + x; break;
default: break;}
Lcd_Cmd(data);
while(*buffer)                // Write data to LCD up to null
     {
      Lcd_Chr_CP(*buffer);
      buffer++;               // Increment buffer
     }
return;
}

void Lcd_Out2(unsigned char y, unsigned char x, char *buffer){
unsigned char data;
switch(y){
case 1: data = 127 + x; break;
case 2: data = 191 + x; break;
case 3: data = 147 + x; break;
case 4: data = 211 + x; break;
default: break;}
Lcd_Cmd(data);
while(*buffer)                // Write data to LCD up to null
     {
      Lcd_Chr_CP(*buffer);
      buffer++;               // Increment buffer
     }
return;
}

void Lcd_Chr(unsigned char y, unsigned char x, char Chr){
unsigned char data;
switch(y){
case 1: data = 127 + x; break;
case 2: data = 191 + x; break;
case 3: data = 147 + x; break;
case 4: data = 211 + x; break;
default: break;}
Lcd_Cmd(data);
Lcd_Chr_CP(Chr);
}

void Lcd_Chr_CP(char Chr_CP){
LCD_EN = 0; LCD_RS = 1;
LCD_RD7 = (Chr_CP & 0b10000000)>>7; LCD_RD6 = (Chr_CP & 0b01000000)>>6;
LCD_RD5 = (Chr_CP & 0b00100000)>>5; LCD_RD4 = (Chr_CP & 0b00010000)>>4;
_delay(10);
LCD_EN = 1; Delay_5us(); LCD_EN = 0;
LCD_RD7 = (Chr_CP & 0b00001000)>>3; LCD_RD6 = (Chr_CP & 0b00000100)>>2;
LCD_RD5 = (Chr_CP & 0b00000010)>>1; LCD_RD4 = (Chr_CP & 0b00000001);
_delay(10);
LCD_EN = 1; Delay_5us(); LCD_EN = 0;
Delay_5us(); Delay_5500us();
}

void Lcd_Cmd(unsigned char Cmd){
LCD_EN = 0; LCD_RS = 0;
LCD_RD7 = (Cmd & 0b10000000)>>7; LCD_RD6 = (Cmd& 0b01000000)>>6;
LCD_RD5 = (Cmd & 0b00100000)>>5; LCD_RD4 = (Cmd & 0b00010000)>>4;
_delay(10);
LCD_EN = 1; Delay_5us(); LCD_EN = 0;
LCD_RD7 = (Cmd & 0b00001000)>>3; LCD_RD6 = (Cmd & 0b00000100)>>2;
LCD_RD5 = (Cmd & 0b00000010)>>1; LCD_RD4 = (Cmd & 0b00000001);
_delay(10);
LCD_EN = 1; Delay_5us(); LCD_EN = 0;
Delay_5500us();//Delay_5us();
}

#endif	/* HD44780_H */

