#include "uart.h"
#include "defines.h"

UART uart[4];

int uart_init()
{
	int i;
	UART *up;
	for(i=0; i<4; i++){
		up = &uart[i];
		up->base = (char *)(ARM_VERSATILE_PL011_UART0 + i*0x1000);
		up->n = i;
	}
	uart[3].base = (char *)(ARM_VERSATILE_PL011_UART3);
}


char ugetc(UART *up)
{
	while(*(up->base + UFR) & RXFE);
	return *(up->base + UDR);
}

void uputc(UART *up, char c)
{
	while(*(up->base + UFR) & TXFF);
	*(up->base + UDR) = c;
}

void upgets(UART *up, char *s)
{
	while((*s = ugetc(up))!='\r'){
		uputc(up, *s);//echo the input from the UART back to the UART so user can see what he has just input
		s++;
	}
	*s = 0;
}

void uprints(UART *up, char *s)
{
	while(*s) //output the whole buffer to UART
	{
		uputc(up, *s++);
	}
}

char *ctable = "0123456789ABCDEF";

int urpx(UART *up,int x)
{
	char c;
	if (x){
		c = ctable[x % 16];
		urpx(up,x / 16);
	}
	uputc(up,c);
}

int uprintx(UART *up,int x)
{
	uputc(up,'0'); uputc(up,'x');
	if (x==0)
		uputc(up,'0');
	else
		urpx(up,x);
	uputc(up,' ');
}

int urpu(UART *up,int x)
{
	char c;
	if (x){
		c = ctable[x % 10];
		urpu(up,x / 10);
	}
	uputc(up,c);
}

int uprintu(UART *up,int x)
{
	if (x==0){
		uputc(up,' ');
		uputc(up,'0');
	}
	else
		urpu(up,x);
	uputc(up,' ');
}

int uprinti(UART *up,int x)
{
	if (x<0){
		uputc(up,'-');
		x = -x;
	}
	uprintu(up,x);
}

int uprintf(UART *up,char *fmt,...)
{
	int *ip;
	char *cp;
	cp = fmt;
	ip = (int *)&fmt + 1;

	while(*cp){
	if (*cp != '%'){
		uputc(up,*cp);
		if (*cp=='\n')uputc(up,'\r');
		cp++;
	continue;
	}
	cp++;
	switch(*cp){
		case 'c': uputc(up,(char)*ip);      break;
		case 's': uprints(up,(char *)*ip);  break;
		case 'd': uprinti(up,*ip);          break;
		case 'u': uprintu(up,*ip);          break;
		case 'x': uprintx(up,*ip);          break;
	}
	cp++; ip++;
	}
}


