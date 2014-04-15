/* 
 * File:   main.c
 * Author: mustafa
 *
 * Created on 15 Nisan 2014 Sal?, 02:55
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "HD44780.h"
#include "ow.h"

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

char currentTemp[10];

int ds_get_temp(void) {
    char temp_low;
    char temp_high;
    int temperature=0;

    ow_reset();
    __delay_us(300); //Delay100TCYx(30);
    ow_write_byte(0xCC);
    __delay_us(10); //Delay100TCYx(1);
    ow_write_byte(0x44);
    __delay_us(255); //Delay10KTCYx(255);
    __delay_us(255); //Delay10KTCYx(255);
    __delay_us(255); //Delay10KTCYx(255);
    ow_reset();
    __delay_us(300); //Delay100TCYx(30);
    ow_write_byte(0xCC);
    __delay_us(10); //Delay100TCYx(1);
    ow_write_byte(0xBE);
    __delay_us(10); //Delay100TCYx(1);
    temp_low = ow_read_byte();
    __delay_us(1); //Delay10TCYx(1);
    temp_high = ow_read_byte();
    ow_reset();
    temperature = temperature | temp_low;
    temperature = temperature | (temp_high << 8);
    return temperature;
}

int main() {

  CMCON = 0x07;
  ADCON1 = 0x0E;

  Lcd_Init();                                    // Initialize LCD
  Lcd_Cmd(LCD_CLEAR);                           // Clear LCD
  Lcd_Cmd(LCD_CURSOR_OFF);                      // Turn cursor off
  Lcd_Out(1, 1, " Temperature:   ");
  // Print degree character, 'C' for Centigrades
  Lcd_Chr(2,13,223);                             // Different LCD displays have different char code for degree
                                                 // If you see greek alpha letter try typing 178 instead of 223

  Lcd_Chr(2,14,'C');

    while(1){
        ow_reset();
        sprintf(currentTemp, "%d", ds_get_temp());
        Lcd_Out(2,2, currentTemp);
    }

    return (EXIT_SUCCESS);
}

