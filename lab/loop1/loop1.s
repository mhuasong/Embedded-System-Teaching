/*下面类似于
  For(i=0;i<10;i++)
	Dest[i]=src[i];
*/
.data
src: .int 0,1,2,3,4,5,6,7,8,9
dst: .int 9,8,7,6,5,4,3,2,1,0
.text
.globl _start
_start:
	mov r2, #10
	ldr r0, =src
	ldr r1, =dst
	;LDR R3, [R0]
	;STR R3,[R1]
	mov R4, #0	
	 
loop:
	LDR R3, [R0,R4]  /*基址加索引寻址：R0<-[R3]; R0=R0+4 */
	STR R3, [R1,R4]
	ADDS R4,R4,#4
	SUBS r2,r2,#1 
	BNE loop
	   

	swi 0x00900001

.end

