/********************************************************************
Copyright 2010-2017 K.C. Wang, <kwang@eecs.wsu.edu>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/

// defines.h file

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define UART0_BASE_ADDR 0x101f1000
#define UART0_DR (*((volatile u32 *)(UART0_BASE_ADDR + 0x000)))
#define UART0_FR (*((volatile u32 *)(UART0_BASE_ADDR + 0x018)))
#define UART0_IMSC (*((volatile u32 *)(UART0_BASE_ADDR + 0x038)))

#define UART1_BASE_ADDR 0x101f2000
#define UART1_DR (*((volatile u32 *)(UART1_BASE_ADDR + 0x000)))
#define UART1_FR (*((volatile u32 *)(UART1_BASE_ADDR + 0x018)))
#define UART1_IMSC (*((volatile u32 *)(UART1_BASE_ADDR + 0x038)))

#define KBD_BASE_ADDR 0x10006000
#define KBD_CR (*((volatile u32 *)(KBD_BASE_ADDR + 0x000)))
#define KBD_DR (*((volatile u32 *)(KBD_BASE_ADDR + 0x008)))

#define TIMER0_BASE_ADDR 0x101E2000
#define TIMER0_LR (*((volatile u32 *)(UART0_BASE_ADDR + 0x000)))
#define TIMER0_BR (*((volatile u32 *)(UART0_BASE_ADDR + 0x032)))

#define VIC_BASE_ADDR 0x10140000
#define VIC_STATUS    (*((volatile u32 *)(VIC_BASE_ADDR + 0x000)))
#define VIC_INTENABLE (*((volatile u32 *)(VIC_BASE_ADDR + 0x010)))
#define VIC_VADDR     (*((volatile u32 *)(VIC_BASE_ADDR + 0x030)))

#define SIC_BASE_ADDR 0x10003000
#define SIC_STATUS    (*((volatile u32 *)(SIC_BASE_ADDR + 0x000)))
#define SIC_INTENABLE (*((volatile u32 *)(SIC_BASE_ADDR + 0x008)))
#define SIC_ENSET     (*((volatile u32 *)(SIC_BASE_ADDR + 0x008)))
#define SIC_PICENSET  (*((volatile u32 *)(SIC_BASE_ADDR + 0x020)))

#define LINES  4
#define N_SCAN 64

#define BLUE   0
#define GREEN  1
#define RED    2
#define WHITE  3
#define CYAN   4
#define YELLOW 5
