
TEXT_BASE = 0x00010000 @0x33F80000

.set GPIO_BASE, 0x101E4000	@#define GPIO_BASE 0x101E4000
.set IODIR, 0x000 		@#define IODIR 0x000
.set IOSET, 0x004		@#define IOSET 0x004
.set IOCLR, 0x008		@#define IOCLR 0x008
.set IOPIN, 0x00C		@#define IOPIN 0x00C

/*
 *************************************************************************
 *
 * Jump vector table as in table 3.1 in [1]
 *
 *************************************************************************
 */


.globl _start
_start:
	b	reset
	b . /* Undefined */
	b . /* SWI */
	b . /* Prefetch Abort */
	b . /* Data Abort */
	b . /* reserved */
	b . /* IRQ */
	b . /* FIQ */

	.balignl 16,0xdeadbeef

/*
 *************************************************************************
 *
 * Startup Code (reset vector)
 *
 * do important init only if we don't start from memory!
 * setup Memory and board specific bits prior to relocation.
 * relocate armboot to ram
 * setup stack
 *
 *************************************************************************
 */

_TEXT_BASE:
	.word	TEXT_BASE

.globl _armboot_start
_armboot_start:
	.word _start

/*
 * These are defined in the board-specific linker script.
 */
.globl _bss_start
_bss_start:
	.word __bss_start

.globl _bss_end
_bss_end:
	.word _end

#ifdef CONFIG_USE_IRQ
/* IRQ stack memory (calculated at run-time) */
.globl IRQ_STACK_START
IRQ_STACK_START:
	.word	0x0badc0de

/* IRQ stack memory (calculated at run-time) */
.globl FIQ_STACK_START
FIQ_STACK_START:
	.word 0x0badc0de
#endif


/*
 * the actual reset code
 */

reset:
	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0,cpsr
	bic	r0,r0,#0x1f
	orr	r0,r0,#0xd3
	msr	cpsr,r0

	/*
	 * we do sys-critical inits only at reboot,
	 * not when booting from ram!
	 */
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	bl	cpu_init_crit
#endif

_light_led:			@only a demo added by Huasong min
	ldr r0, =GPIO_BASE	@R0存放GPIO0的IODIR寄存器地址
	ldr r1, =0x00FFFF00 	@装载32位立即数，即设置值
	str r1, [r0]		@IODIR=0x00FFFF00,IODIR地址为0x101E4000
	mov r1, #0x00F00000
	str r1, [r0,#IOSET]	@IOSET=0x00F00000,IOSET地址为0x101E4004

#ifndef CONFIG_SKIP_RELOCATE_UBOOT
relocate:				/* relocate U-Boot to RAM	    */
	adr	r0, _start		/* r0 <- current position of code   */
	ldr	r1, _TEXT_BASE		/* test if we run from flash or RAM */
	cmp     r0, r1                  /* don't reloc during debug         */
	beq     stack_setup

	ldr	r2, _armboot_start
	ldr	r3, _bss_start
	sub	r2, r3, r2		/* r2 <- size of armboot            */
	add	r2, r0, r2		/* r2 <- source end address         */

copy_loop:
	ldmia	r0!, {r3-r10}		/* copy from source address [r0]    */
	stmia	r1!, {r3-r10}		/* copy to   target address [r1]    */
	cmp	r0, r2			/* until source end addreee [r2]    */
	ble	copy_loop
#endif	/* CONFIG_SKIP_RELOCATE_UBOOT */

	/* Set up the stack						    */
stack_setup:
@	ldr	r0, _TEXT_BASE		/* upper 128 KiB: relocated uboot   */
@	sub	r0, r0, #384 << 10 /*#CFG_MALLOC_LEN*/	/* malloc area                      */
@	sub	r0, r0, #64 /*#CFG_GBL_DATA_SIZE*/ /* bdinfo                        */

@	sub	sp, r0, #12		/* leave 3 words for abort-stack    */

	ldr	sp, =stack_top		/*modified by Huasong Min */

clear_bss:
	ldr	r0, _bss_start		/* find start of bss segment        */
	ldr	r1, _bss_end		/* stop here                        */
	mov 	r2, #0x00000000		/* clear                            */

clbss_l:str	r2, [r0]		/* clear loop...                    */
	add	r0, r0, #4
	cmp	r0, r1
	ble	clbss_l

	ldr	pc, _start_armboot
	b .				/*added by Huasong Min */

_start_armboot:
	.word start_armboot


/*
 *************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 *************************************************************************
 */


cpu_init_crit:
	/*
	 * flush v4 I/D caches
	 */
	mov	r0, #0
	mcr	p15, 0, r0, c7, c7, 0	/* flush v3/v4 cache */
	mcr	p15, 0, r0, c8, c7, 0	/* flush v4 TLB */

	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002300	/* clear bits 13, 9:8 (--V- --RS) */
	bic	r0, r0, #0x00000087	/* clear bits 7, 2:0 (B--- -CAM) */
	orr	r0, r0, #0x00000002	/* set bit 2 (A) Align */
	orr	r0, r0, #0x00001000	/* set bit 12 (I) I-Cache */
	mcr	p15, 0, r0, c1, c0, 0

	/*
	 * Go setup Memory and board specific bits prior to relocation.
	 */
	mov	ip, lr		/* perserve link reg across call */
	bl	lowlevel_init	/* go setup pll,mux,memory */
	mov	lr, ip		/* restore link */
	mov	pc, lr		/* back to my caller */

