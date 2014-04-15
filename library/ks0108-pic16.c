#include <xc.h>

// PORTD is a data port
#define KS0108_DATA_PORT        PORTD
// TRISD data port direction
#define KS0108_DATA_DIR         TRISD
#define KS0108_DATA_PIN         PORTD
// PORTB display command
#define KS0108_CTRL_PORT        PORTB
// control port direction
#define KS0108_CTRL_DIR         TRISB
// Pin RS
#define KS0108_RS               0x04
// Pin RW
#define KS0108_RW               0x08
// Pin EN
#define KS0108_EN               0x10
// Pin RST
#define KS0108_RST              0x20
// CS1
#define KS0108_CS1              0x01
// CS2
#define KS0108_CS2              0x02
// rev.
#define KS0108_CS3              (1 << 0)
// busy flag
#define DISPLAY_STATUS_BUSY 0x80

extern unsigned char screen_x, screen_y;

// Functie NOP
void GLCD_Delay(void) {
     asm("nop");
}


void GLCD_InitalizePorts(void) {
     // RST, CS1, CS2 1 logic
     KS0108_CTRL_PORT |= (KS0108_CS1 | KS0108_CS2 | KS0108_CS3 | KS0108_RST);
     // cs1, cs2, rst, rs, rw, en sunt iesiri
     KS0108_CTRL_DIR &= ~(KS0108_CS1 | KS0108_CS2 | KS0108_RST | KS0108_RS | KS0108_RW | KS0108_EN);
}


void GLCD_EnableController(unsigned char controller) {

     switch(controller){
        case 0 : KS0108_CTRL_PORT &= ~KS0108_CS1; break;
        case 1 : KS0108_CTRL_PORT &= ~KS0108_CS2; break;
        case 2 : KS0108_CTRL_PORT &= ~KS0108_CS3; break;
     }
}


void GLCD_DisableController(unsigned char controller) {
     switch(controller){
        case 0 : KS0108_CTRL_PORT |= KS0108_CS1; break;
        case 1 : KS0108_CTRL_PORT |= KS0108_CS2; break;
        case 2 : KS0108_CTRL_PORT |= KS0108_CS3; break;
     }
}


unsigned char GLCD_ReadStatus(unsigned char controller) {

unsigned char status;

     KS0108_DATA_DIR = 0xFF;
     KS0108_CTRL_PORT |= KS0108_RW;
     KS0108_CTRL_PORT &= ~KS0108_RS;
     GLCD_EnableController(controller);
     KS0108_CTRL_PORT |= KS0108_EN;
     GLCD_Delay();
     status = KS0108_DATA_PIN;
     KS0108_CTRL_PORT &= ~KS0108_EN;
     GLCD_DisableController(controller);
     return status;
}


void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller) {

     while(GLCD_ReadStatus(controller)&DISPLAY_STATUS_BUSY);
        KS0108_DATA_DIR = 0x00;
     KS0108_CTRL_PORT &= ~(KS0108_RW | KS0108_RS);
     GLCD_EnableController(controller);
     KS0108_DATA_PORT = commandToWrite;
     KS0108_CTRL_PORT |= KS0108_EN;
     GLCD_Delay();
     KS0108_CTRL_PORT &= ~KS0108_EN;
     GLCD_DisableController(controller);
}


unsigned char GLCD_ReadData(void) {

     unsigned char date;
     while(GLCD_ReadStatus(screen_x / 64)&DISPLAY_STATUS_BUSY);
        KS0108_DATA_DIR = 0xFF;
     KS0108_CTRL_PORT |= (KS0108_RW | KS0108_RS);
     GLCD_EnableController(screen_x / 64);
     //GLCD_Delay();
     KS0108_CTRL_PORT |= KS0108_EN;
     GLCD_Delay();
     date = KS0108_DATA_PIN;
     KS0108_CTRL_PORT &= ~KS0108_EN;
     GLCD_DisableController(screen_x / 64);
     screen_x++;
     return date;
}


void GLCD_WriteData(unsigned char dataToWrite) {

     while(GLCD_ReadStatus(screen_x / 64)&DISPLAY_STATUS_BUSY);
        KS0108_DATA_DIR = 0x00;
     KS0108_CTRL_PORT &= ~KS0108_RW;
     KS0108_CTRL_PORT |= KS0108_RS;
     KS0108_DATA_PORT = dataToWrite;
     GLCD_EnableController(screen_x / 64);
     KS0108_CTRL_PORT |= KS0108_EN;
     GLCD_Delay();
     KS0108_CTRL_PORT &= ~KS0108_EN;
     GLCD_DisableController(screen_x / 64);
     screen_x++;
}
