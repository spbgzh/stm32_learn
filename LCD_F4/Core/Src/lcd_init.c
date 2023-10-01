#include "lcd_init.h"
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi1;
void LCD_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_SET);

  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_10, GPIO_PIN_SET);
}


void LCD_Writ_Bus(unsigned char *data, unsigned int size) 
{	
	LCD_CS_Clr();
	while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&hspi1, data, size, 0xff);
	LCD_CS_Set();	
}


void LCD_WR_DATA8(unsigned char data)
{
	LCD_Writ_Bus(&data,1);
}

void LCD_WR_DATA(unsigned int data)
{
	unsigned char da[2]= {0};
	da[0] = data >> 8;
	da[1] = data;
	LCD_Writ_Bus(da,2);
}


void LCD_WR_REG(unsigned char data)
{
	LCD_DC_Clr();
	LCD_Writ_Bus(&data,1);
	LCD_DC_Set();
}


void LCD_Address_Set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
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
	LCD_GPIO_Init();//��ʼ��GPIO
		LCD_RES_Set();
		HAL_Delay(10);	
		LCD_RES_Clr();//��λ
		HAL_Delay(10);
		LCD_RES_Set();
		HAL_Delay(120);
		LCD_BLK_Set();//�򿪱���

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







