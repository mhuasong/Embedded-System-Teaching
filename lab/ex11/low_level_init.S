/*
 * Memory Setup stuff - taken from blob memsetup.S
 *
 * Copyright (C) 1999 2000 2001 Erik Mouw (J.A.K.Mouw@its.tudelft.nl) and
 *                     Jan-Derk Bakker (J.D.Bakker@its.tudelft.nl)
 *
 * Modified for the Samsung SMDK2410 by
 * (C) Copyright 2002
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
#include <config.h>
#include <version.h>
*/

/* some parameters for the board */

/*
 *
 * Taken from linux/arch/arm/boot/compressed/head-s3c2410.S
 *
 * Copyright (C) 2002 Samsung Electronics SW.LEE  <hitchcar@sec.samsung.com>
 *
 */
TEXT_BASE = 0x00010000 @0x33F80000 


BWSCON = 0x48000000

/* BWSCON */
DW8	=	 	(0x0)
DW16	=	 	(0x1)
DW32	=	 	(0x2)
WAIT	=	 	(0x1<<2)
UBLB	=	 	(0x1<<3)

B1_BWSCON	=  	(DW32)
B2_BWSCON	=  	(DW16)
B3_BWSCON	=  	(DW16 + WAIT + UBLB)
B4_BWSCON	=  	(DW16)
B5_BWSCON	=  	(DW16)
B6_BWSCON	=  	(DW32)
B7_BWSCON	=  	(DW32)

/* BANK0CON */
B0_Tacs		= 	0x0	/*  0clk */
B0_Tcos		= 	0x0	/*  0clk */
B0_Tacc		= 	0x7	/* 14clk */
B0_Tcoh		= 	0x0	/*  0clk */
B0_Tah		= 	0x0	/*  0clk */
B0_Tacp		= 	0x0
B0_PMC		= 	0x0	/* normal */

/* BANK1CON */
B1_Tacs		= 	0x0	/*  0clk */
B1_Tcos		= 	0x0	/*  0clk */
B1_Tacc		= 	0x7	/* 14clk */
B1_Tcoh		= 	0x0	/*  0clk */
B1_Tah		= 	0x0	/*  0clk */
B1_Tacp		= 	0x0
B1_PMC		= 	0x0

B2_Tacs		= 	0x0
B2_Tcos		= 	0x0
B2_Tacc		= 	0x7
B2_Tcoh		= 	0x0
B2_Tah		= 	0x0
B2_Tacp		= 	0x0
B2_PMC		= 	0x0

B3_Tacs		= 	0x0	/*  0clk */
B3_Tcos		= 	0x3	/*  4clk */
B3_Tacc		= 	0x7	/* 14clk */
B3_Tcoh		= 	0x1	/*  1clk */
B3_Tah		= 	0x0	/*  0clk */
B3_Tacp		= 	0x3     /*  6clk */
B3_PMC		= 	0x0	/* normal */

B4_Tacs		= 	0x0	/*  0clk */
B4_Tcos		= 	0x0	/*  0clk */
B4_Tacc		= 	0x7	/* 14clk */
B4_Tcoh		= 	0x0	/*  0clk */
B4_Tah		= 	0x0	/*  0clk */
B4_Tacp		= 	0x0
B4_PMC		= 	0x0	/* normal */

B5_Tacs		= 	0x0	/*  0clk */
B5_Tcos		= 	0x0	/*  0clk */
B5_Tacc		= 	0x7	/* 14clk */
B5_Tcoh		= 	0x0	/*  0clk */
B5_Tah		= 	0x0	/*  0clk */
B5_Tacp		= 	0x0
B5_PMC		= 	0x0	/* normal */

B6_MT		= 	0x3	/* SDRAM */
B6_Trcd	 	= 	0x1
B6_SCAN		= 	0x1	/* 9bit */

B7_MT		= 	0x3	/* SDRAM */
B7_Trcd		= 	0x1	/* 3clk */
B7_SCAN		= 	0x1	/* 9bit */

/* REFRESH parameter */
REFEN		= 	0x1	/* Refresh enable */
TREFMD		= 	0x0	/* CBR(CAS before RAS)/Auto refresh */
Trp		= 	0x0	/* 2clk */
Trc		= 	0x3	/* 7clk */
Tchr		= 	0x2	/* 3clk */
REFCNT		= 	1113	/* period=15.6us, HCLK=60Mhz, (2048+1-15.6*60) */
/**************************************/

_TEXT_BASE:
	.word	TEXT_BASE

.globl lowlevel_init
lowlevel_init:
	/* memory control configuration */
	/* make r0 relative the current location so that it */
	/* reads SMRDATA out of FLASH rather than memory ! */
	ldr     r0, =SMRDATA
	ldr	r1, _TEXT_BASE
	sub	r0, r0, r1
	ldr	r1, =BWSCON	/* Bus Width Status Controller */
	add     r2, r0, #13*4
0:
	ldr     r3, [r0], #4
	str     r3, [r1], #4
	cmp     r2, r0
	bne     0b

	/* everything is fine now */
	mov	pc, lr

	.ltorg
/* the literal pools origin */

SMRDATA:
    .word (0+(B1_BWSCON<<4)+(B2_BWSCON<<8)+(B3_BWSCON<<12)+(B4_BWSCON<<16)+(B5_BWSCON<<20)+(B6_BWSCON<<24)+(B7_BWSCON<<28))
    .word ((B0_Tacs<<13)+(B0_Tcos<<11)+(B0_Tacc<<8)+(B0_Tcoh<<6)+(B0_Tah<<4)+(B0_Tacp<<2)+(B0_PMC))
    .word ((B1_Tacs<<13)+(B1_Tcos<<11)+(B1_Tacc<<8)+(B1_Tcoh<<6)+(B1_Tah<<4)+(B1_Tacp<<2)+(B1_PMC))
    .word ((B2_Tacs<<13)+(B2_Tcos<<11)+(B2_Tacc<<8)+(B2_Tcoh<<6)+(B2_Tah<<4)+(B2_Tacp<<2)+(B2_PMC))
    .word ((B3_Tacs<<13)+(B3_Tcos<<11)+(B3_Tacc<<8)+(B3_Tcoh<<6)+(B3_Tah<<4)+(B3_Tacp<<2)+(B3_PMC))
    .word ((B4_Tacs<<13)+(B4_Tcos<<11)+(B4_Tacc<<8)+(B4_Tcoh<<6)+(B4_Tah<<4)+(B4_Tacp<<2)+(B4_PMC))
    .word ((B5_Tacs<<13)+(B5_Tcos<<11)+(B5_Tacc<<8)+(B5_Tcoh<<6)+(B5_Tah<<4)+(B5_Tacp<<2)+(B5_PMC))
    .word ((B6_MT<<15)+(B6_Trcd<<2)+(B6_SCAN))
    .word ((B7_MT<<15)+(B7_Trcd<<2)+(B7_SCAN))
    .word ((REFEN<<23)+(TREFMD<<22)+(Trp<<20)+(Trc<<18)+(Tchr<<16)+REFCNT)
    .word 0x32
    .word 0x30
    .word 0x30

