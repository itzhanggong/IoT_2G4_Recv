#ifndef x_STRING_H_H_
#define x_STRING_H_H_

#include "ver.h"

extern uint8 xstrlen(const char *s);
extern void *xmemcpy(void *dest, const void *src, uint8 count);
extern int xmemcmp(const void *cs, const void *ct, uint8 count);

#endif