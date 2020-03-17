#include "uart.h"
#include "mystring.h"
#include "vid.c" // LCD driver

extern UART uart[4];
UART *up;

void __aeabi_unwind_cpp_pr0 (void) {}
void __aeabi_unwind_cpp_pr1 (void) {}

extern char _binary_image1_start, _binary_image2_start;

#define WIDTH 640

int show_bmp(char *p, int start_row, int start_col)
{
	int h, w, pixel, rsize, i, j;
	unsigned char r, g, b;
	char *pp;
	int *q = (int *)(p+14); // skip over 14-byte file header
	w = *(q+1); // image width in pixels
	h = *(q+2); // image height in pixels
	p += 54; // p-> pixels in image
	//BMP images are upside down, each row is a multiple of 4 bytes
	rsize = 4*((3*w + 3)/4); // multiple of 4
	p += (h-1)*rsize; // last row of pixels
	for (i=start_row; i<start_row + h; i++){
	pp = p;
		for (j=start_col; j<start_col + w; j++){
		b = *pp; g = *(pp+1); r = *(pp+2); // BRG values
		pixel = (b<<16) | (g<<8) | r; // pixel value
		fb[i*WIDTH + j] = pixel; // write to frame buffer
		pp += 3; // advance pp to next pixel
		}
	p -= rsize; // to preceding row
	}
}


void softreset(void){
        /*Syscall exit*/
        asm(
	"mov %r0, $0\n"
        "mov %r7, $1\n"
        "swi $0\n"
	);
}

/* qemu-system-arm -M versatilepb -serial stdio -semihosting -kernel test.bin*/
void shutdown(void){
	register int reg0 asm("r0");
	register int reg1 asm("r1");

	reg0 = 0x18;    // angel_SWIreason_ReportException
	reg1 = 0x20026; // ADP_Stopped_ApplicationExit

	asm("svc 0x00123456");  // make semihosting call
}
void menu(void){
	uprints(up,"*****************MENU**************************\n");
	uprints(up,"***1-press'a' for Checked up and good to go!***\n");
	uprints(up,"***2-press'b' for Orders sir!               ***\n");
	uprints(up,"***3-press'r' for Reset!                    ***\n");
	uprints(up,"***4-press'q' for SHUTDOWN!                 ***\n");
	uprints(up,"***5-press'c' for Show Picture!             ***\n");
	uprints(up,"***********************************************\n\n");
}
void main_loop (void)
{
	unsigned char cmd;
	int i;
	char string[64];
	char *p;

	fbuf_init(); // default to VGA mode

	uart_init();
	up = &uart[0];
	uprints(up, "\n\rEnter lines from serial terminal 0\n\r");

	menu();

	for(;;) {
		//cmd = ugetc(up);
		upgets(up, string);
		cmd = string[my_strlen(string)-1];/*读取回车符前最后一个字符*/
		
	if(cmd<0x80 && cmd>0x60){
		switch(cmd){
			case 0x61:
			uprints(up,"\n\rChecked up and good to go!\n\r");
			break;
			case 0x62:
			uprints(up,"\n\rOrders sir!\n\r");
			break;
			case 0x71:
			shutdown(); 
			break;
			case 0x72:
			softreset(); 
			break;
			case 0x63:
			for(;;){
			i++;
			if(i%2==0)
			p = &_binary_image1_start;
			else
			p = &_binary_image2_start;
			show_bmp(p, 0, 0); // display image1 
			uprints(up,"\n\rEnter 'i' to stop show picture!\nOthers to change picture!\n\r");
			cmd = ugetc(up);
			if(cmd == 'i')break;
			}
			break;

			default:
			uprints(up,"\n\rCommand unknown!\n\r");
			uprints(up,"\n\rPlease press 'a' 'b' 'r' or 'q'!\n\r");
			break;
			}
		uprints(up,"\n\r");
		menu();
		uprints(up,"\n\r");
		}
	}
}


