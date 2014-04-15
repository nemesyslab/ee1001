#define KS0108_SCREEN_WIDTH           128
#define KS0108_SCREEN_HEIGHT           64


#define DISPLAY_SET_Y                 0x40
#define DISPLAY_SET_X                 0xB8
#define DISPLAY_START_LINE            0xC0 // start address
#define DISPLAY_ON_CMD                0x3E
#define ON                            0x01 // 0x3E | 0x01 = 0x3F care este ON
#define OFF                           0x00 // 0x3E | 0x00 = 0x3E care este OFF
#define DISPLAY_STATUS_BUSY           0x80 // valoare flag busy

void GLCD_Initalize(void);
void GLCD_WriteData(unsigned char);
void GLCD_WriteCommand(unsigned char, unsigned char);
void GLCD_ClearScreen(void);
void GLCD_GoTo(unsigned char, unsigned char);
void GLCD_WriteString(char *);
void GLCD_WriteChar(char );
unsigned char GLCD_ReadData(void);
void GLCD_Bitmap(const unsigned char *, unsigned char, unsigned char, unsigned char, unsigned char);
void GLCD_SetPixel(unsigned char x, unsigned char y, unsigned char color);
