/* 
 * File:   main.c
 * Author: mustafa
 *
 * Created on 15 Nisan 2014 Sal?, 01:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "HD44780.h"

#define _XTAL_FREQ 8000000
#define CLOCK_FREQ  8000000

/*
 * 
 */
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

unsigned char ch;
unsigned int adc_rd;
char *text;
long tlong;

void ADCInit(void){
     ADCON0 = 0x11;
     ADCON1 = 0x80;
}

int main() {
  INTCON = 0;                              // disable all interrupts
  CMCON = 0x07;

  TRISA  = 0x04;

  ADCInit();

  Lcd_Init();
  Lcd_Cmd(LCD_CURSOR_OFF);                 // send command to LCD (cursor off)
  Lcd_Cmd(LCD_CLEAR);                      // send command  to LCD (clear LCD)

  text = "mikroElektronika";               // assign text to string
  Lcd_Out(1,1,text);                       // print string a on LCD, 1st row, 1st column
  text = "LCD example";                    // assign text to string
  Lcd_Out(2,1,text);                       // print string a on LCD, 2nd row, 1st column

  __delay_ms(2000);
  text  = "voltage:";                      // assign text to string
  while (1) {
    ADCON0bits.GO = 1;
    while(ADCON0bits.nDONE) continue;

    adc_rd  = (ADRESH<<8) + ADRESL;                 // get ADC value from 2nd channel
    Lcd_Out(2,1,text);                     // print string a on LCD, 2nd row, 1st column

    tlong = (long)adc_rd * 5000;           // covert adc reading to milivolts
    tlong = tlong / 1021;                  // 0..1023 -> 0-5000mV

    ch     = tlong / 1000;                 // extract volts digit
    Lcd_Chr(2,9,48+ch);                    // write ASCII digit at 2nd row, 9th column
    Lcd_Chr_CP('.');

    ch    = (tlong / 100) % 10;            // extract 0.1 volts digit
    Lcd_Chr_CP(48+ch);                     // write ASCII digit at cursor point

    ch    = (tlong / 10) % 10;             // extract 0.01 volts digit
    Lcd_Chr_CP(48+ch);                     // write ASCII digit at cursor point

    Lcd_Chr_CP('V');

    __delay_ms(1);
  }

    return (EXIT_SUCCESS);
}

