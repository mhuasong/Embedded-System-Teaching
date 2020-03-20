/**** bitmap2charmap.c: run as a.out font.bin > font ****/
#include <stdio.h>
main(int argc, char *argv[ ])
{
	int i, n; u8 buf[16];
	FILE *fp = fopen(argv[1], "r"); // fopen file for READ
	while((n = fread(buf, 1, 16, fp)){ // read 16 bytes
		for (i=0; i<n; i++) // write each byte as 2 hex
			printf("0x%2x ", buf[i]);
	}
	printf("\n");
}