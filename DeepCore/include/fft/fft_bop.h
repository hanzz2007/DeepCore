﻿#ifndef __fft_bop_h__
#define __fft_bop_h__

static unsigned int g_iBFS[256]=
{
    0, 0, 
	1, 1, 
	2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};

__forceinline unsigned int __popc( unsigned int n )
{
	unsigned int m=n;
	m=m-((m>>1)&0x55555555);
	m=(m&0x33333333)+((m>>2)&0x33333333);
	m=(m+(m>>4))&0x0f0f0f0f;
	m=m+(m>> 8);
	m=m+(m>>16);
	return m&0x3f;
}
__forceinline int __bffs( unsigned int n )
{
	int p, s;
	s=(n<256)?0:(n<65536?8:(n<0x00ff0000?16:24));
	p=s+g_iBFS[(n>>s)&0xff];
	return p;
}
__forceinline int fft_get_exec_size( unsigned int n )
{
	int p=__bffs(n);
	if(p<0) return 0;
	return (1<<(p+(__popc(n)>1)));
}

#endif