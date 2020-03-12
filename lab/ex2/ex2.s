.globl _start
_start:

	MOV  R0,  R2, LSL  #3
	/* R2的值左移3位，结果放入R0，即R0＝R2×8 */
	ANDS  R1, R1,   R2,  LSL  R3
	/* R2的值左移R3位，然后与R1相“与” */
	/* 结果放入R1，并且影响标志位。*/
	SUB R11,  R12,  R3, ASR #5
	/* R12-R3÷32，然后存入R11。*/

	swi 0x00900001

.end


