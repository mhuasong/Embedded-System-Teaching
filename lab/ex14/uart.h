#ifndef _UART_H_ 
#define _UART_H_ 


#define TXFE 0x80
#define TXFF 0x20
#define RXFE 0x10
#define RXFF 0x40
#define BUSY 0x08

#define UDR 0x00
#define UFR 0x18

#define ARM_VERSATILE_PL011_UART0 0x101F1000
#define ARM_VERSATILE_PL011_UART3 0x10009000

typedef volatile struct uart {
	char *base;
	int n;
}UART;

int	uart_init();
char	ugetc(UART *up);
void	uputc(UART *up, char c);
void	upgets(UART *up, char *s);
void	uprints(UART *up, char *s);
int	uprintf(UART *up,char *fmt,...);
#endif
