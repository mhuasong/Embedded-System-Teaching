/*
 *  armboot - Startup Code for ARM926EJS CPU-core
 *
 *  Copyright (c) 2020  WUST
 *
 *  Copyright (c) 2020	Huasong Min <mhuasong@wust.edu.cn>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the IRIS of 
 * WUST, Wuhan University of Sci&Tech,947 Heping Road,qinshan, Wuhan,
 * 430081 China
 */

#include <stdint.h>

void __aeabi_unwind_cpp_pr0 (void) {}
void __aeabi_unwind_cpp_pr1 (void) {}

typedef volatile struct {
	uint32_t DR;
	uint32_t RSR_ECR;
	uint8_t reserved1[0x10];
	const uint32_t FR;
	uint8_t reserved2[0x4];
	uint32_t LPR;
	uint32_t IBRD;
	uint32_t FBRD;
	uint32_t LCR_H;
	uint32_t CR;
	uint32_t IFLS;
	uint32_t IMSC;
	const uint32_t RIS;
	const uint32_t MIS;
	uint32_t ICR;
	uint32_t DMACR;
}pl011_T;

enum {
	RXFE = 0x10,
	TXFF = 0x20,
};

pl011_T * const UART0 = (pl011_T *)0x101f1000;
pl011_T * const UART1 = (pl011_T *)0x101f2000;
pl011_T * const UART2 = (pl011_T *)0x101f3000;

static inline char upperchar(char c) {
	if((c >= 'a') && (c <= 'z')) {
	return c - 'a' + 'A';
	} else {
 	return c;
	}
}

static void uart_echo(pl011_T *uart) {
	if ((uart->FR & RXFE) == 0) {
	while(uart->FR & TXFF);
	uart->DR = upperchar(uart->DR);
	}
}

unsigned char getc(pl011_T *uart){
	if ((uart->FR & RXFE) == 0) {
	while(uart->FR & TXFF);
	//uart->DR = upperchar(uart->DR);
	return uart->DR;
	}
}

void softreset(void){
        /*Syscall exit*/
        asm(
	"mov %r0, $0\n"
        "mov %r7, $1\n"
        "swi $0\n"
	);
}

/* qemu-system-arm -M versatilepb -serial stdio -semihosting -kernel test.bin*/
void shutdown(void){
	register int reg0 asm("r0");
	register int reg1 asm("r1");

	reg0 = 0x18;    // angel_SWIreason_ReportException
	reg1 = 0x20026; // ADP_Stopped_ApplicationExit

	asm("svc 0x00123456");  // make semihosting call
}

void menu(void){
	print_uart0("*****************MENU**************************\n");
	print_uart0("***1-press'a' for Checked up and good to go!***\n");
	print_uart0("***2-press'b' for Orders sir!               ***\n");
	print_uart0("***3-press'r' for Reset!                    ***\n");
	print_uart0("***4-press'q' for SHUTDOWN!                 ***\n");
	print_uart0("***********************************************\n\n");
}
void main_loop (void)
{
	unsigned char cmd;

	menu();

	for(;;) {
		cmd = getc(UART0);
	if(cmd<0x80 && cmd>0x60){
		switch(cmd){
			case 0x61:
			print_uart0("Checked up and good to go!\n");
			break;
			case 0x62:
			print_uart0("Orders sir!\n");
			break;
			case 0x71:
			shutdown(); 
			break;
			case 0x72:
			softreset(); 
			break;
			default:
			print_uart0("Command unknown!\n");
			print_uart0("Please press 'a' 'b' 'r' or 'q'!\n");
			break;
			}
		print_uart0("\n");
		menu();
		print_uart0("\n");
		}
	}
}


