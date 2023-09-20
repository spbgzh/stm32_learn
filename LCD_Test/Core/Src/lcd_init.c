#include "lcd_init.h"
#include "stm32f1xx_hal.h"

void LCD_Writ_Bus(uint8_t dat) 
{	
	uint8_t i;
	for(i=0;i<8;i++)
	{			  
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		if(dat&0x80)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
		}
		else
		{
		   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
		}
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		dat<<=1;
	}	
}


void LCD_WR_DATA8(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}


void LCD_WR_DATA(uint16_t dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


void LCD_WR_REG(uint8_t dat)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);//DC
	LCD_Writ_Bus(dat);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);//DC
}


void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
}



void LCD_Init(void)
{
 		 

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);//RES
		HAL_Delay(10);	
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);//RES
		HAL_Delay(10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
		HAL_Delay(120);

		LCD_WR_REG(0x11);     
		HAL_Delay(120);                

		LCD_WR_REG(0x36);     
		if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
		else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
		else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
		else LCD_WR_DATA8(0xA0);

		LCD_WR_REG(0x3A);     
		LCD_WR_DATA8( 0x05);   //16BIT

		LCD_WR_REG(0xB2);     
		LCD_WR_DATA8( 0x05);   
		LCD_WR_DATA8( 0x05);   
		LCD_WR_DATA8( 0x00);   
		LCD_WR_DATA8( 0x33);   
		LCD_WR_DATA8( 0x33);   

		LCD_WR_REG(0xB7);     
		LCD_WR_DATA8( 0x35);   


		LCD_WR_REG(0xBB);     
		LCD_WR_DATA8( 0x21);   

		LCD_WR_REG(0xC0);     
		LCD_WR_DATA8( 0x2C);   

		LCD_WR_REG(0xC2);     
		LCD_WR_DATA8( 0x01);   

		LCD_WR_REG(0xC3);     
		LCD_WR_DATA8( 0x0B);   

		LCD_WR_REG(0xC4);     
		LCD_WR_DATA8( 0x20);   

		LCD_WR_REG(0xC6);     
		LCD_WR_DATA8( 0x0F);   //60HZ dot inversion

		LCD_WR_REG(0xD0);     
		LCD_WR_DATA8( 0xA7);   
		LCD_WR_DATA8( 0xA1); 

		LCD_WR_REG(0xD0);     
		LCD_WR_DATA8( 0xA4);   
		LCD_WR_DATA8( 0xA1);   
			

		LCD_WR_REG(0xD6);     
		LCD_WR_DATA8( 0xA1);   

		LCD_WR_REG(0xE0);     
		LCD_WR_DATA8( 0xD0);   
		LCD_WR_DATA8( 0x04);   
		LCD_WR_DATA8( 0x08);   
		LCD_WR_DATA8( 0x0A);   
		LCD_WR_DATA8( 0x09);   
		LCD_WR_DATA8( 0x05);   
		LCD_WR_DATA8( 0x2D);   
		LCD_WR_DATA8( 0x43);   
		LCD_WR_DATA8( 0x49);   
		LCD_WR_DATA8( 0x09);   
		LCD_WR_DATA8( 0x16);   
		LCD_WR_DATA8( 0x15);   
		LCD_WR_DATA8( 0x26);   
		LCD_WR_DATA8( 0x2B);   

		LCD_WR_REG(0xE1);     
		LCD_WR_DATA8( 0xD0);   
		LCD_WR_DATA8( 0x03);   
		LCD_WR_DATA8( 0x09);   
		LCD_WR_DATA8( 0x0A);   
		LCD_WR_DATA8( 0x0A);   
		LCD_WR_DATA8( 0x06);   
		LCD_WR_DATA8( 0x2E);   
		LCD_WR_DATA8( 0x44);   
		LCD_WR_DATA8( 0x40);   
		LCD_WR_DATA8( 0x3A);   
		LCD_WR_DATA8( 0x15);   
		LCD_WR_DATA8( 0x15);   
		LCD_WR_DATA8( 0x26);   
		LCD_WR_DATA8( 0x2A);   

		LCD_WR_REG(0x21);     

		LCD_WR_REG(0x29);     

		HAL_Delay(10);                	
}







