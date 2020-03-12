//#include <stdio.h>

extern unsigned char* cmsg;
extern unsigned int clen;

extern int sum(int a,int b);

void display()
{
        asm(
		"mov %r0, $1\n"     /*输出到stdout，stdout的设备描述符为1*/
        "ldr %r1, =cmsg\n"   /*buf=msg*/
        "ldr %r2, =clen\n"   /*count=len*/
        "mov %r7, $4\n"     /*syscall 4*/
        "swi $0\n"          /*invoke syscall*/
	);

}


int c_entry()
{

	if(3==sum(1,2))
		display();

	return 0;	
}
