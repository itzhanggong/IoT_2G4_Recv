#include <GPM8F2202.h>
#include "parsecmd.h"
#include "xstring.h"

/*-----------------------------------
 *pwm = 0;关
 *pwm = 1-100;从最亮到最暗。
 *------------------------------------*/
void _parse_cmd(){
 
	uint8 cs1, i, cs2 = 0;
	uint8 cmd2g4 = 0;
	uint8 addr[3] = {0};

	cs1=_hexToByte(&Spi_rxBuff[14],2);

	for(i=0;i<14;i++){
		cs2+=Spi_rxBuff[i];
	}

	if(cs1!=cs2){
		return ;
	}

	cmd2g4 = _hexToByte(&Spi_rxBuff[8], 2);
	addr[0] = _hexToByte(&Spi_rxBuff[2], 2);
	addr[1] = _hexToByte(&Spi_rxBuff[4], 2);
	addr[2] = _hexToByte(&Spi_rxBuff[6], 2);

	if(cmd2g4 == 0x00){								//对码						
		/*if(Timer_T2)
			{
													//地址写flash
			}*/
	}else if(cmd2g4 == 0x01){
		CC2 = 0xAABB + 55;
		CC3	= 0xFFFF - 55;					 		//开
	}else if(cmd2g4 == 0x02){
		CC2 = CC3 = 0xFFFF - 55;						//关
	}else if(cmd2g4 == 0x03){
									   				//长按开
	}else if(cmd2g4 == 0x04){
					 								//长按关
	}else if(cmd2g4 == 0x05){
		if((0xAABB+55) <= CC2 <= (0xFFFF-55)){				 		//亮度+
			CC2 -= 55;
		}
	}else if(cmd2g4 == 0x06){
		if((0xAABB+55) <= CC2 <= (0xFFFF-55)){						//亮度-
			CC2 += 55;
		}
	}else if(cmd2g4 == 0x07){
		if((0xAABB+55) <= CC3 <= (0xFFFF-55)){				 		//色温+
			CC3 -= 55;
		}
	}else if(cmd2g4 == 0x08){
	   if((0xAABB+55) <= CC3 <= (0xFFFF-55)){						//色温-
			CC3 += 55;						  	
		}
	}else if(cmd2g4 == 0x09){								
		CC2 = 0xAABB + 55;											//正白
		CC3	= 0xFFFF - 55;
	}else if(cmd2g4 == 0x0A){
		CC2 = 0xC727;												//暖白
		CC3 = 0xC727;						
	}else if(cmd2g4 == 0x0B){
		CC2 = 0xD55D;												//中性
		CC3 = 0xD55D;
	}else if(cmd2g4 == 0x0C){
		CC2 = 0xE393;					   							//小夜灯 
		CC3 = 0xE393;
	}						 	

	
	return;

}

uint8 _hexToByte(char *cp, uint8 len)
{
	uint8 i,n,temp=0;

	if(xstrlen(cp)<len)
	{
		return 0;
	}

	for(i=0;i<len;i++)
	{
		if(cp[i]>='A'&&cp[i]<='F')
			n=cp[i]-'A'+10;
		else if(cp[i]>='a'&&cp[i]<='f')
			n=cp[i]-'a'+10;
		else
			n=cp[i]-'0';

		temp=temp*16+n;
	}

	return temp;
}


