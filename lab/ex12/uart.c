#include "uart.h"
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
