/* 
 * File:   ow.h
 * Author: mustafa
 *
 * Created on March 7, 2014, 2:00 PM
 */

#ifndef OW_H
#define	OW_H

#define _XTAL_FREQ 8000000

#define OW_LAT  TRISEbits.TRISE2
#define OW_PIN  PORTEbits.RE2
#define OW_TRIS  PORTEbits.RE2

#define OUTPUT 0
#define INPUT 1

unsigned char ow_reset(void)
{
    short device_found=0;
    // DQ High
    OW_TRIS=INPUT;
    // DQ Low
    OW_LAT=0;
    OW_TRIS=OUTPUT;
    // delay 480us
    __delay_us(480); //Delay100TCYx(48);
    // DQ High
    OW_TRIS=INPUT;
    // Wait for the sensors to respond
    __delay_us(60);//Delay100TCYx(6);
    // Determine is a device has responded
    device_found = !OW_PIN;
    return device_found;
}

void ow_write_byte(unsigned char data)
{
    char i;
    for (i=0;i<8;i++)
    {
        // DQ Low
        OW_LAT=0;
        OW_TRIS=OUTPUT;
        // Keep it low for 10us to start the WRITE
        __delay_us(10);//Delay10TCYx(10);
        // Keep low i.e. keep output mode and low if WRITE0
        // or release line i.e. make input to take it high if WRITE1
        OW_TRIS = data & 0x01;
        __delay_us(50);//Delay10TCYx(50);
        // Release the line. Total of 60us
        OW_TRIS=INPUT;
        // Some recovery time between the bits 2us
        __delay_us(2);//Delay10TCYx(2);
        data =data >>1;
    }
}

char ow_read_byte(void)
{
    char data=0;
    char i;
    for (i=0;i<8;i++)
    {
        // DQ Low. Initiate READ
        OW_LAT=0;
        OW_TRIS=OUTPUT;
        __delay_us(2); //Delay10TCYx(2);
        // DQ High. Release
        OW_TRIS=INPUT;
        // Wait for total of 10 us since READ initiation
        __delay_us(8); //Delay10TCYx(8);
        // Read the bit and place it in the data at the right position
        data = (OW_PIN << i) | data;
        // Additional time to complete the minimum 60 us READ cycle
        __delay_us(50);//Delay10TCYx(50);
    }
    return data;
}

#endif	/* OW_H */

