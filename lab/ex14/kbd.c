
#include "keymap2"
#include "mystring.h"

/********************************************************************************
//0    1    2    3    4    5    6    7     8    9    A    B    C    D    E    F
char ltab[] = {
  0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,  'q', '1',  0,    0,   0,  'z', 's', 'a', 'w', '2',  0,
  0,  'c', 'x', 'd', 'e', '4', '3',  0,    0,  ' ', 'v', 'f', 't', 'r', '5',  0,
  0,  'n', 'b', 'h', 'g', 'y', '6',  0,    0,   0,  'm', 'j', 'u', '7', '8',  0,
  0,  ',', 'k', 'i', 'o', '0', '9',  0,    0,  '.', '/', 'l', ';', 'p', '-',  0,
  0,   0,  '\'', 0,  '[', '=',  0,   0,    0,   0, '\r', ']',  0, '\\',  0,   0,
  0,   0,   0,   0,   0,   0,  '\b', 0,    0,   0,   0,   0,   0,   0,   0,   0
};

char utab[] = {
  0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,  'Q', '!',  0,    0,   0,  'Z', 'S', 'A', 'W', '@',  0,
  0,  'C', 'X', 'D', 'E', '$', '#',  0,    0,  ' ', 'V', 'F', 'T', 'R', '%',  0,
  0,  'N', 'B', 'H', 'G', 'Y', '^',  0,    0,   0,  'M', 'J', 'U', '&', '*',  0,
  0,  '<', 'K', 'I', 'O', ')', '(',  0,    0,  '>', '?', 'L', ':', 'P', '_',  0,
  0,   0,  '"',  0,  '{', '+',  0,   0,    0,   0,  '\r','}',  0,  '|',  0,   0,
  0,   0,   0,   0,   0,   0,  '\b', 0,    0,   0,   0,   0,   0,   0,   0,   0
};
**********************************************************************************/
// KBD registers from base address
#define KCNTL 0x00    
#define KSTAT 0x04
#define KDATA 0x08
#define KCLK  0x0C
#define KISTA 0x10

typedef struct kbd {
	char *base;
	char buf[128];
	int head, tail, data, room;
}KBD;

KBD kbd;

int kputc(char);

int shifted = 0; 
int release = 0;
int control = 0;

int kbd_init()
{
	KBD *kp = &kbd;
	kp->base = (char *)0x10006000;
	//*(kp->base + KCNTL) = 0x11;    // bit4=Enable   bit0=INT on
	*(kp->base + KCNTL) = 0x14;     // 00010100=INTenable, Enable
	*(kp->base + KCLK)  = 8;        // KBD internal clock setting 
	kp->head = kp->tail = 0;        //Index to buffer
	kp->data = 0; kp->room = 128;   // Counter

	release = 0;  // key release flag
	shifted = 0;  // shift key down flag
	control = 0;  // control key down flag
}

// kbd_handler() for scan code set 2

/*******************************************
  key press    =>        scanCode
  key release  =>   0xF0 scanCode
Example: 
 press   'a'   =>          0x1C
 release 'a'   =>   0xF0   0x1C
******************************************/

void kbd_handler()
{
	unsigned char scode, c;

	KBD *kp = &kbd;
	color = YELLOW;   // int color in vid.c file
	scode = *(kp->base + KDATA);  // get scan code from KDATA reg => clear IRQ

	//printf("scanCode = %x\n", scode);

	if (scode == 0xF0){       // key release 
	release = 1;           // set flag
	return;
	}

	if (scode == 0x12) { //L Shift is being pressed
	shifted = 1;
	}

	if (scode == 0x14) { //L Ctrl is being pressed
	control = 1;
	}

	if (scode == 0x12 && release == 1) { //L Shift is released
	shifted = 0;
	}

	if (scode == 0x14 && release == 1) { //L Ctrl is released
	control = 0;
	}

	if (release && scode){    // next scan code following key release
	release = 0;           // clear flag 
	return;
	}

	if (shifted && scode)            
	c = utab[scode]; //Lowercase
	else                  // ONLY IF YOU can catch LEFT or RIGHT shift key
	c = ltab[scode]; //Uppercase
	if (control && scode) {
	if (scode == 0x21)
	kprintf("PROGRAM IS TERMINATED\n");
	if (scode == 0x23) {
	c = 0x04;
	kprintf("FILE STREAMING IS TERMINATED\n");
	}
	} 

	//kprintf("c=%x %c\n", c, c);
	kprintf("%c",c);
	//if(c=='\r')kprintf("\n");

	kp->buf[kp->head++] = c;  // Enter key into CIRCULAR buf[]
	kp->head %= 128;
	kp->data++;
	kp->room--;
}

int kgetc()
{
	char c;
	KBD *kp = &kbd;
	//printf("%d in kgetc\n", running->pid); 

	while(kp->data == 0);

	disable_irq();
	c = kp->buf[kp->tail++];
	kp->tail %= 128;
	kp->data--; kp->room++;
	enable_irq();
	return c;
}

int kgets(char s[ ])
{
	char c;
	while( (c = kgetc()) != '\r'){
		if (c=='\b'){
		s--;
		continue;
		}
		*s++ = c;
	}
	*s = 0;
	return my_strlen(s);
}


