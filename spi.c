#include <GPM8F2202.h>
#include "spi.h"
#include "ver.h"
#include "xstring.h"

void spi_Recv(){

	uint8 i;
	uint8 Temp[CMD_BUFF_LEN] = {0};

	
	Reg_write16(0x34, 0, 0x80); 			//reset 2.4G FIFO point
	//Reg_write16(0x07, 0x00, 0xB0);		//enable RX mode
	Reg_write16(0x07, (gReg7_high & 0xfe), (gReg7_low | 0x80));  	//enter RX mode
	//while(!PKT);
	while(PKT == 0);  
 	SPICS = 0;
	spi_write(0x32 | REG_RD);
	spi_read();
	for(i=0; i<=CMD_BUFF_LEN; i++){
		Temp[i] = spi_read();
	}
	
	SPICS = 1;

	Reg_write16(0x07, (gReg7_high & 0xfe), (gReg7_low & 0x7f));
	//Reg_write16(0x07, 0x00, 0x30);  		//disable RX mode

	xmemcpy(Spi_rxBuff, Temp, CMD_BUFF_LEN);
	spi_rx_complete = 1;
}

void Reg_write16(uint8 addr, uint8 v1, uint8 v2){


	SPICS = 0;
	
	spi_write(addr);
	spi_write(v1);
	spi_write(v2);

	pdelay(3);
	SPICS = 1;
	
	if(addr < 0x20){
//		Wait_mSec(35);			// RF register DBUS propergation time
  	 	Wait_mSec(10);
	}
	return;
}

uint16 Reg_read16(uint8 addr)
{
	uint16 value =0;
	SPICS = 0;
	
	spi_write(addr | REG_RD);
	
	value = spi_read();
	value <<= 8;
	pdelay(3);
	value |= spi_read();

	pdelay(3);
	SPICS = 1;

	return value;
}

void spi_write(uint8 spi_bValue){
	
 	uint8 i;
	
	SPICS = 0; 
	pdelay(10);
 	
	for(i=0; i<8; i++){ 
		
		SPICLK = 1;   
		pdelay(10);
		if((spi_bValue&0x80)==0x80){
			SPIMOSI = 1;
		}else{ 	
			SPIMOSI = 0; 
		}
		pdelay(10);
		SPICLK = 0;
		pdelay(10);
		spi_bValue = (spi_bValue<<1);  
	}  
}  

uint8 spi_read()  
{  
	uint8 i, spi_bValue;  
	
	SPICS = 0; 
	SPICS = 0;
	
	for(i=0; i<8; i++)  
	{                                  
		SPICLK = 1;  
		pdelay(10);
		
		spi_bValue <<= 1;  
		SPICLK = 0; 
		pdelay(10);
			
		if(SPIMISO == 1){

			spi_bValue ++;	
		}  
		
	}  

	SPICLK = 0;

	return spi_bValue;  
} 



//获取寄存器 7 的值
uint16 GetReg7FromChip(void)
{
	uint16 temp;

	temp = Reg_read16(0x07);
	gReg7_high = (uint8)((temp&0xff00)>>8);
	gReg7_low = (uint8)(temp&0x00ff);

	return temp;
}
/*
void spi_Send(uint8 *ptr, uint8 bytes) //only tx loop
{
	uint8 i;
	
 	Reg_write16(0x34,0x80,0x00);												//清空邋FIFO	
	pdelay(3);
	spi_write(0x32);															//Fill data to FIFO;
	spi_write(CMD_BUFF_LEN);
	for(i=0; i<(bytes); i++)													//发送数据
	{	
		spi_write(*ptr++);
	}
	
	SPICS = 1;
	pdelay(3);
	
 	//Reg_write16(0x07,0x01,0x30); 			//使能TX
 	Reg_write16(0x07, (gReg7_high|0x01), gReg7_low&0x7f);					//使能TX
 	
 	//while(P3&0x80 == 0);
	pdelay(3);
	//Reg_write16(0x07,0x00,0x30);												//disable TX	
	Reg_write16(0x07, (gReg7_high&0xfe), gReg7_low&0x7f);   				//TX Disable
}
*/

