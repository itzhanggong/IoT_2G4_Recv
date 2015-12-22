#ifndef SPI_H_H_
#define	SPI_H_H_

#include <GPM8F2202.h>
#include "ver.h"

extern void spi_Send(uint8 *ptr,uint8 bytes);
extern void spi_Recv();
extern void pdelay (char t);
extern uint16 Reg_read16(uint8 addr);
extern uint8 spi_read();
extern uint16 GetReg7FromChip();
extern void Reg_write16(uint8 addr, uint8 v1, uint8 v2);
extern void spi_write(uint8 spi_bValue);


#endif
