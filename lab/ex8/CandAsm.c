#include <stdio.h>

//return 1 : little-endian
//       0 : big-endian
int checkCPUendian()
{
    union {
        unsigned int a;
        unsigned char b; 
    } c;

    c.a = 1;
    return (c.b == 1); 
}
void init()
{
	asm(
	/*
	 * set the cpu to SVC32 mode
	 */
	"mrs	r0,cpsr\n"
	"bic	r0,r0,#0x1f\n"
	"orr	r0,r0,#0xd3\n"
	"msr	cpsr,r0\n"
	);
	asm volatile(
	"mov r1, #0x80\n"                                        
	"mcr p15, 0, r1, c1, c0, 0\n"  
	:::"r1"  //:::"r1" 向GCC声明：我对r1作了改动

	);
}

int main(int argc, char **argv)
{
	init();
	if(checkCPUendian()==1)
		printf("little-endian\n");
	else
		printf("big-endian\n");

	return 0;
}

