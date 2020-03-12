#include <stdio.h>

struct T1{char c;short s; int x }t1={'a',0x1111,0x10101010};

typedef struct EXAMPLE{
        char c2[2];
        struct T1  s1[2];
}example;

void pausehere()
{
	printf("pause here\n");
}

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

int main(int argc, char **argv)
{
	if(checkCPUendian()==1)
		printf("little-endian\n");
	else
		printf("big-endian\n");

	struct T1 t2;
	//t1.c = 'a';
	//t1.s = 0x1111;
	//t1.x = 0x10101010;
	printf("t1 address: 0x%x\n",&t1);

	

	t2.c = 'b';
	t2.s = 0x2222;
	t2.x = 0x20202020;
	printf("t2 address: 0x%x\n",&t2);

	example ex;
	ex.c2[0]='c';
	ex.c2[1]='d';
	ex.s1[0] = t1;
	ex.s1[1] = t2;
	printf("ex address: 0x%x\n",&ex);
	
	pausehere();
	//printf("EXAMPLE: %c %c %c %d %d %c %d %d\n",ex.c2[0],ex.c2[1],ex.s1[0].c,ex.s1[0].s,ex.s1[0].x,ex.s1[1].c,ex.s1[1].s,ex.s1[1].x);

	return 0;
}
