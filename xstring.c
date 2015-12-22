#include "xstring.h"
#include "ver.h"

uint8 xstrlen(uint8 *s)
{
	const char *sc;
	for(sc=s;*sc!='\0';++sc);
	return sc-s;
}

void *xmemcpy(void *dest, const void *src, uint8 count)
{
	char *tmp = dest;
	const char *s = src;
	while(count--)
		*tmp++ = *s++;
	return dest;
}

int xmemcmp(const void *cs, const void *ct, uint8 count)
{
	const unsigned char *su1, *su2;
	int res = 0;
	
	for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
	{
		if((res = *su1 - *su2) != 0)
			break;
	}
	return res;
}