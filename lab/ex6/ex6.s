.data
src: .int 0,1,2,3,4,5,6,7,8,9
dst: .int 9,8,7,6,5,4,3,2,1,0
.text
.globl _start
_start:

	LDR R0, =src
	LDR R1, =dst
	/*MOV SP, #0x400*/

	STMFD SP!, {R2-R11}
	LDMIA R0!, {R2-R11}
	STMIA R1!, {R2-R11}
	LDMFD SP!, {R2-R11}

brkpoint:
	swi 0x00900001

.end
