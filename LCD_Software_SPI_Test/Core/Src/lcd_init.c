#include "lcd_init.h"
#include "stm32f1xx_hal.h"


void LCD_GPIO_Init(void)
{
 GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
//SCL SDA
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5|GPIO_PIN_7, GPIO_PIN_SET);
//CS 
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
//RES
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_SET);
//DC BLK
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_11, GPIO_PIN_SET);
}
void LCD_Writ_Bus(unsigned char dat) 
{	
	unsigned char i;
	LCD_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		LCD_SCLK_Clr();
		if(dat&0x80)
		{
		   LCD_MOSI_Set();
		}
		else
		{
		   LCD_MOSI_Clr();
		}
		LCD_SCLK_Set();
		dat<<=1;
	}	
  LCD_CS_Set();	
}


void LCD_WR_DATA8(unsigned char dat)
{
	LCD_Writ_Bus(dat);
}

void LCD_WR_DATA(unsigned int dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


void LCD_WR_REG(unsigned char dat)
{
	LCD_DC_Clr();//д����
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//д����
}


void LCD_Address_Set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+20);
		LCD_WR_DATA(y2+20);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+20);
		LCD_WR_DATA(y2+20);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+20);
		LCD_WR_DATA(x2+20);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+20);
		LCD_WR_DATA(x2+20);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
}
void LCD_Init(void)
{
	LCD_GPIO_Init();
	LCD_RES_Set();
	HAL_Delay(10);
	LCD_RES_Clr();//��λ
	HAL_Delay(10);
	LCD_RES_Set();
	HAL_Delay(120);
	
	LCD_BLK_Set();//�򿪱���
	
	LCD_WR_REG(0xfd);//private_access
	LCD_WR_DATA8(0x06);
	LCD_WR_DATA8(0x08);

	LCD_WR_REG(0x61);//add
	LCD_WR_DATA8(0x07);//
	LCD_WR_DATA8(0x04);//

	LCD_WR_REG(0x62);//bias setting
	LCD_WR_DATA8(0x00);//00
	LCD_WR_DATA8(0x44);//44
	LCD_WR_DATA8(0x45);//40  47

	LCD_WR_REG(0x63);//
	LCD_WR_DATA8(0x41);//
	LCD_WR_DATA8(0x07);//
	LCD_WR_DATA8(0x12);//
	LCD_WR_DATA8(0x12);//

	LCD_WR_REG(0x64);//
	LCD_WR_DATA8(0x37);//
	//VSP
	LCD_WR_REG(0x65);//Pump1=4.7MHz //PUMP1 VSP
	LCD_WR_DATA8(0x09);//D6-5:pump1_clk[1:0] clamp 28 2b
	LCD_WR_DATA8(0x10);//6.26
	LCD_WR_DATA8(0x21);
	//VSN
	LCD_WR_REG(0x66); //pump=2 AVCL
	LCD_WR_DATA8(0x09); //clamp 08 0b 09
	LCD_WR_DATA8(0x10); //10
	LCD_WR_DATA8(0x21);
	//add source_neg_time
	LCD_WR_REG(0x67);//pump_sel
	LCD_WR_DATA8(0x20);//21 20
	LCD_WR_DATA8(0x40);

	//gamma vap/van
	LCD_WR_REG(0x68);//gamma vap/van
	LCD_WR_DATA8(0x90);//
	LCD_WR_DATA8(0x4c);//
	LCD_WR_DATA8(0x7C);//VCOM  
	LCD_WR_DATA8(0x66);//

	LCD_WR_REG(0xb1);//frame rate
	LCD_WR_DATA8(0x0F);//0x0f fr_h[5:0] 0F
	LCD_WR_DATA8(0x02);//0x02 fr_v[4:0] 02
	LCD_WR_DATA8(0x01);//0x04 fr_div[2:0] 04

	LCD_WR_REG(0xB4);
	LCD_WR_DATA8(0x01); //01:1dot 00:column
	////porch
	LCD_WR_REG(0xB5);
	LCD_WR_DATA8(0x02);//0x02 vfp[6:0]
	LCD_WR_DATA8(0x02);//0x02 vbp[6:0]
	LCD_WR_DATA8(0x0a);//0x0A hfp[6:0]
	LCD_WR_DATA8(0x14);//0x14 hbp[6:0]

	LCD_WR_REG(0xB6);
	LCD_WR_DATA8(0x04);//
	LCD_WR_DATA8(0x01);//
	LCD_WR_DATA8(0x9f);//
	LCD_WR_DATA8(0x00);//
	LCD_WR_DATA8(0x02);//
	////gamme sel
	LCD_WR_REG(0xdf);//
	LCD_WR_DATA8(0x11);//gofc_gamma_en_sel=1
	////gamma_test1 A1#_wangly
	//3030b_gamma_new_
	//GAMMA---------------------------------/////////////

	//GAMMA---------------------------------/////////////
	LCD_WR_REG(0xE2);	
	LCD_WR_DATA8(0x13);//vrp0[5:0]	V0 13
	LCD_WR_DATA8(0x00);//vrp1[5:0]	V1 
	LCD_WR_DATA8(0x00);//vrp2[5:0]	V2 
	LCD_WR_DATA8(0x30);//vrp3[5:0]	V61 
	LCD_WR_DATA8(0x33);//vrp4[5:0]	V62 
	LCD_WR_DATA8(0x3f);//vrp5[5:0]	V63

	LCD_WR_REG(0xE5);	
	LCD_WR_DATA8(0x3f);//vrn0[5:0]	V63
	LCD_WR_DATA8(0x33);//vrn1[5:0]	V62	
	LCD_WR_DATA8(0x30);//vrn2[5:0]	V61 
	LCD_WR_DATA8(0x00);//vrn3[5:0]	V2 
	LCD_WR_DATA8(0x00);//vrn4[5:0]	V1 
	LCD_WR_DATA8(0x13);//vrn5[5:0]  V0 13

	LCD_WR_REG(0xE1);	
	LCD_WR_DATA8(0x00);//prp0[6:0]	V15
	LCD_WR_DATA8(0x57);//prp1[6:0]	V51 

	LCD_WR_REG(0xE4);	
	LCD_WR_DATA8(0x58);//prn0[6:0]	V51 
	LCD_WR_DATA8(0x00);//prn1[6:0]  V15

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0x01);//pkp0[4:0]	V3 
	LCD_WR_DATA8(0x03);//pkp1[4:0]	V7  
	LCD_WR_DATA8(0x0d);//pkp2[4:0]	V21
	LCD_WR_DATA8(0x0e);//pkp3[4:0]	V29 
	LCD_WR_DATA8(0x0e);//pkp4[4:0]	V37 
	LCD_WR_DATA8(0x0c);//pkp5[4:0]	V45 
	LCD_WR_DATA8(0x15);//pkp6[4:0]	V56 
	LCD_WR_DATA8(0x19);//pkp7[4:0]	V60 

	LCD_WR_REG(0xE3);	
	LCD_WR_DATA8(0x1a);//pkn0[4:0]	V60 
	LCD_WR_DATA8(0x16);//pkn1[4:0]	V56 
	LCD_WR_DATA8(0x0C);//pkn2[4:0]	V45 
	LCD_WR_DATA8(0x0f);//pkn3[4:0]	V37 
	LCD_WR_DATA8(0x0e);//pkn4[4:0]	V29 
	LCD_WR_DATA8(0x0d);//pkn5[4:0]	V21 
	LCD_WR_DATA8(0x02);//pkn6[4:0]	V7  
	LCD_WR_DATA8(0x01);//pkn7[4:0]	V3 
	//GAMMA---------------------------------/////////////

	//source
	LCD_WR_REG(0xE6);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0xff);//SC_EN_START[7:0] f0

	LCD_WR_REG(0xE7);
	LCD_WR_DATA8(0x01);//CS_START[3:0] 01
	LCD_WR_DATA8(0x04);//scdt_inv_sel cs_vp_en
	LCD_WR_DATA8(0x03);//CS1_WIDTH[7:0] 12
	LCD_WR_DATA8(0x03);//CS2_WIDTH[7:0] 12
	LCD_WR_DATA8(0x00);//PREC_START[7:0] 06
	LCD_WR_DATA8(0x12);//PREC_WIDTH[7:0] 12

	LCD_WR_REG(0xE8); //source
	LCD_WR_DATA8(0x00); //VCMP_OUT_EN 81-
	LCD_WR_DATA8(0x70); //chopper_sel[6:4]
	LCD_WR_DATA8(0x00); //gchopper_sel[6:4] 60
	////gate
	LCD_WR_REG(0xEc);
	LCD_WR_DATA8(0x52);//52

	LCD_WR_REG(0xF1);
	LCD_WR_DATA8(0x01);//te_pol tem_extend 00 01 03
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x02);


	LCD_WR_REG(0xF6);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x00);//
	LCD_WR_DATA8(0x00);//40 3��2ͨ��

	LCD_WR_REG(0xfd);
	LCD_WR_DATA8(0xfa);
	LCD_WR_DATA8(0xfc);

	LCD_WR_REG(0x3a);
	LCD_WR_DATA8(0x05);//

	LCD_WR_REG(0x35);
	LCD_WR_DATA8(0x00);

	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x08);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC8);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x78);
	else LCD_WR_DATA8(0xA8);


	LCD_WR_REG(0x21); 

	LCD_WR_REG(0x11); // exit sleep
	HAL_Delay(200);
	LCD_WR_REG(0x29); // display on
	HAL_Delay(10); 
} 







