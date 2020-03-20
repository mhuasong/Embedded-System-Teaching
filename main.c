#include "uart.h"
#include "mystring.h"
#include "vid.c" // LCD driver


//

extern UART uart[4];
UART *up;

void __aeabi_unwind_cpp_pr0 (void) {}
void __aeabi_unwind_cpp_pr1 (void) {}

extern char _binary_image1_start, _binary_image2_start;
extern char _binary_man1_start, _binary_man2_start, _binary_man3_start, _binary_man4_start, _binary_man5_start, _binary_man6_start, _binary_man7_start, _binary_man8_start;

static void delay(int nops)
{
	while(nops > 0)
	{
	asm ("nop");
	nops--;
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
	uprintf(up,"*****************MENU**************************\n");
	uprintf(up,"***1-press'a' for Checked up and good to go!***\n");
	uprintf(up,"***2-press'b' for Orders sir!               ***\n");
	uprintf(up,"***3-press'c' for Show Picture!             ***\n");
	uprintf(up,"***4-press'r' for Reset!                    ***\n");
	uprintf(up,"***5-press'q' for SHUTDOWN!                 ***\n");
	uprintf(up,"***6-press't' for Dailogue with robot!      ***\n");
	uprintf(up,"***********************************************\n\n");
}

int search_answer(char *que, char *ans)
{
	char *index1 = que;
	char *index2 = ans;
	
	
	if (my_strcmp(index1,"hello")==0)
	{
		my_strcpy("you are welcome!",index2);
		return 1;
	}
	if (my_strcmp(index1,"who are you")==0)
	{
		my_strcpy("I am wuster.",index2);
		return 1;
	}
	if (my_strcmp(index1,"what's up")==0)
	{
		my_strcpy("Not much just busy.",index2);
		return 1;
	}
	if (my_strcmp(index1,"who is Donald Trump")==0) 
	{
		my_strcpy("BRD, a joker!",index2);
		return 1;
	}
	return 0;

}

void robot_walking(){
	int i,j;
	char *p;
	for(j=0;j<119;j++){
		i++;
		switch(i){
		case 1:
		p = &_binary_man1_start;
		break;
		case 2:
		p = &_binary_man2_start;
		break;
		case 3:
		p = &_binary_man3_start;
		break;
		case 4:
		p = &_binary_man4_start;
		break;
		case 5:
		p = &_binary_man5_start;
		break;
		case 6:
		p = &_binary_man6_start;
		break;
		case 7:
		p = &_binary_man7_start;
		break;
		case 8:
		p = &_binary_man8_start;
		break;

		}
	show_bmp(p, 320, 180); // display image1 
	if(i>7)i=0;
	delay(5000);
	}
}


void main_loop (void)
{
	unsigned char cmd;
	int i,j,k,ret;
	char string[64],mtext[64],answer[64];
	char *p;

	fb_init(); // default to VGA mode

	uart_init();
	up = &uart[0];
	set_color(GREEN);
	uprintf(up, "\n\rEnter lines from serial terminal 0\n\r");
	menu();

	for(;;) {
		//cmd = ugetc(up);
		upgets(up, string);
		cmd = string[my_strlen(string)-1];/*读取回车符前最后一个字符*/
		
	if(cmd<0x80 && cmd>0x60){
		switch(cmd){
			case 0x61:
			uprintf(up,"\n\rChecked up and good to go!\n\r");
			break;
			case 0x62:
			uprintf(up,"\n\rOrders sir!\n\r");
			break;
			case 0x63:
			for(;;){
			i++;
			if(i%2==0)
			p = &_binary_image1_start;
			else
			p = &_binary_image2_start;
			show_bmp(p, 0, 0); // display image1 
			uprintf(up,"\n\rEnter 'i' to stop show picture!\nOthers to change picture!\n\r");
			cmd = ugetc(up);
			if(cmd == 'i')break;
			}
			break;


			case 0x71:
			shutdown(); 
			break;
			case 0x72:
			softreset(); 
			break;
			case 0x74:
			uprintf(up,"\n\r");
			while(1){
				robot_walking();
				set_color(GREEN);
				
				uprintf(up,"I : ");
				upgets(up, mtext);

				kprintf("You said : ");
				uprintf(up,"\n");
				set_color(RED);
				kprintf("%s\n", mtext);
				if(my_strcmp(mtext,"bye")==0){
					kprintf("Robot: bye-bye\n"); 
					uprintf(up,"Robot: bye-bye\n");
					break;
					}
				ret = search_answer(mtext,answer);
				if(ret){
					kprintf("Robot: %s\n", answer);
					uprintf(up,"Robot:%s\n",answer);
				}else{
					kprintf("Robot: %s\n", "haha");
					uprintf(up,"Robot:%s\n","haha");
				}
			}			 
			break;

			default:
			uprintf(up,"\n\rCommand unknown!\n\r");
			uprintf(up,"\n\rPlease press 'a' 'b' 'r' or 'q'!\n\r");
			break;
			}
		uprintf(up,"\n\r");
		menu();
		uprintf(up,"\n\r");
		}
	}
}


