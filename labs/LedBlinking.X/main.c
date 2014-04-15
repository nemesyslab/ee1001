/* 
 * File:   main.c
 * Author: mustafa
 *
 * Created on 15 Nisan 2014 Sal?, 02:33
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

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

int main() {

  TRISA = 0;           // set direction to be output
  TRISB = 0;           // set direction to be output
  TRISC = 0;           // set direction to be output
  TRISD = 0;           // set direction to be output
  TRISE = 0;           // set direction to be output

  do {
    PORTA = 0x00;       // Turn OFF LEDs on PORTA
    PORTB = 0x00;       // Turn OFF LEDs on PORTB
    PORTC = 0x00;       // Turn OFF LEDs on PORTC
    PORTD = 0x00;       // Turn OFF LEDs on PORTD
    PORTE = 0x00;       // Turn OFF LEDs on PORTE
    __delay_ms(1000);    // 1 second delay

    PORTA = 0xFF;       // Turn ON LEDs on PORTA
    PORTB = 0xFF;       // Turn ON LEDs on PORTB
    PORTC = 0xFF;       // Turn ON LEDs on PORTC
    PORTD = 0xFF;       // Turn ON LEDs on PORTD
    PORTE = 0xFF;       // Turn ON LEDs on PORTE
    __delay_ms(1000);    // 1 second delay
  } while(1);          // Endless loop

    return (EXIT_SUCCESS);
}

