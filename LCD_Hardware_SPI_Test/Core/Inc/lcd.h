#ifndef __LCD_H
#define __LCD_H		

void EnterSleep(void);
void ExitSleep(void);
void LCD_Clear(unsigned int color);
void LCD_Fill(unsigned int xsta,unsigned int ysta,unsigned int xend,unsigned int yend,unsigned int color);
void LCD_DrawPoint(unsigned int x,unsigned int y,unsigned int color);
void LCD_DrawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color);
void LCD_DrawRectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,unsigned int color);
void Draw_Circle(unsigned int x0,unsigned int y0,unsigned char r,unsigned int color);

void LCD_ShowChar(unsigned int x,unsigned int y,unsigned char num,unsigned int fc,unsigned int bc,unsigned char sizey,unsigned char mode);
void LCD_ShowString(unsigned int x,unsigned int y,const unsigned char *p,unsigned int fc,unsigned int bc,unsigned char sizey,unsigned char mode);
unsigned long mypow(unsigned char m,unsigned char n);
void LCD_ShowIntNum(unsigned int x,unsigned int y,unsigned int num,unsigned char len,unsigned int fc,unsigned int bc,unsigned char sizey);
void LCD_ShowFloatNum1(unsigned int x,unsigned int y,float num,unsigned char len,unsigned int fc,unsigned int bc,unsigned char sizey);


#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 
#define BRRED 			 0XFC07
#define GRAY  			 0X8430 
#define DARKBLUE      	 0X01CF	
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458 
#define LIGHTGREEN     	 0X841F
#define LGRAY 			 0XC618 
#define LGRAYBLUE        0XA651
#define LBBLUE           0X2B12 

#endif





