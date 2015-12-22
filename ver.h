#ifndef __VER_H_H__
#define __VER_H_H__


//define------------------------------------------
typedef unsigned char 		uint8;
typedef unsigned short		uint16;
typedef unsigned int 		uint32;

typedef char				int8;
typedef short				int16;
typedef int					int32;

#define RX_BUF_LENTH		18
#define CMD_BUFF_LEN		16
#define MCU_VER 			"#CCSOCKET1.007075#\n"
#define MCU_VER_LENGTH		19
#define MACK				"#55000000000000AA#\n"
#define MACK_LENGTH			19

#define xWatchdogSet		{TA=0xAA;TA=0x55;EWT=1;}
#define xWatchdogClr		{TA=0xAA;TA=0x55;RWT=1;}

#define SEND_ACK 			uart_send(MACK,MACK_LENGTH)
#define SEND_VER 			uart_send(MCU_VER,MCU_VER_LENGTH)

#define MT7681_RESET 		P0_4
#define POWER_LED			P0_0
#define	SPICLK	 			P3_3 		// SPI CLK
#define	SPIMOSI	   			P3_4 
#define	SPIMISO				P3_5   
#define	SPICS	 			P0_3  		// SPI NSS 
#define	RFRST				P0_1 		// RFRST='0' means reset the frame chip
#define	PKT					P0_2 		// PKT
#define RF_GAP				35
#define	REG_RD				0x80
#define	REG_WR				0x7F

#define PWM1				P0_4
#define PWM2 				P0_5
//------------------------------------------------

//uart--------------------------------------------
/*extern uint8 	rx_buff[RX_BUF_LENTH];
extern uint8 	pre_cmd_buff[CMD_BUFF_LEN];
extern uint8 	cmd_buff[CMD_BUFF_LEN];
extern uint8 	rx_index;
extern uint8 	rx_timout;
extern bit 		rx_complete;
extern bit 		cmd_flag;
extern uint8 	rx_SBUFF;*/
//------------------------------------------------

//timer-------------------------------------------
extern uint16	 mt7681_wdt;
extern uint16 	 Timer_Delay1;
extern uint8 	timer0_xbase;
extern void		Wait_mSec(uint16 x);
//------------------------------------------------
	  
extern uint8 spi_rx_complete;
extern uint8 Spi_rxBuff[CMD_BUFF_LEN];

//2.4G--------------------------------------------------
extern volatile uint8 	gReg7_high;
extern volatile uint8 	gReg7_low;				// 寄存器7读写暂存变量
extern unsigned char 	Auto_Ack_Select;		// 自动应答开关
//----------------------------------------------------

#endif
