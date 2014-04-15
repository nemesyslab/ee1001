/* 
 * File:   ds1820.h
 * Author: mustafa
 *
 * Created on March 7, 2014, 1:45 PM
 */

#ifndef DS1820_H
#define	DS1820_H

#include "ow.h"

#define _XTAL_FREQ 8000000

char ds_present(void)
{
    return ow_reset();
}

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

#endif	/* DS1820_H */

