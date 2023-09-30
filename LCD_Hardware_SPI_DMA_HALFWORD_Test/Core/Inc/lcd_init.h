#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#define USE_HORIZONTAL 0

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 280

#else
#define LCD_W 280
#define LCD_H 240
#endif




#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0, GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0, GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1, GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1, GPIO_PIN_SET)
 		     
#define LCD_CS_Clr()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10, GPIO_PIN_RESET)//CS
#define LCD_CS_Set()   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10, GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11, GPIO_PIN_RESET)//BLK
#define LCD_BLK_Set()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11, GPIO_PIN_SET)



void LCD_GPIO_Init(void);
void LCD_Writ_Bus(unsigned char *data, unsigned int size);
void LCD_WR_DATA8(unsigned char dat);
void LCD_WR_DATA(unsigned int dat);
void LCD_WR_REG(unsigned char dat);
void LCD_Address_Set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void LCD_Init(void);
#endif




