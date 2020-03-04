.globl _start
_start:
	MOV  R0, #0x10
	MOV  R2, #10
	MOV  R1, R2 
	MOV  R0, R0
	SUB  R0,R1,R2
	ADD  R0, R1, R2   
	ADD  R3,R2,R1,LSL #2
	swi 0x00900001

.end


