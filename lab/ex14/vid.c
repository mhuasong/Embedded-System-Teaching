#include "font0"  // NOTE: font0 is NOT a bitmap but  char fonts0={ char map }

#define BLUE   0x00FF0000
#define GREEN  0x0000FF00
#define RED    0x000000FF
#define WHITE  0x00FFFFFF
#define CYAN   0x00FFFF00
#define YELLOW 0x0000FFFF

char *tab = "0123456789ABCDEF";
int color = 0x00000000;
unsigned char cursor;
int volatile *fb;
unsigned char *font;
int row, col, scrow_row = 4;

int volatile *fb;
int WIDTH = 640; // default to VGA mode for 640x480
extern char _binary_hzk16_start;

int fb_init(void)
{
	int x; int i;
	/**** for SVGA 800X600 these values are in ARM DUI02241 *********
	*(volatile unsigned int *)(0x1000001c) = 0x2CAC; // 800x600
	*(volatile unsigned int *)(0x10120000) = 0x1313A4C4;
	*(volatile unsigned int *)(0x10120004) = 0x0505F6F7;
	*(volatile unsigned int *)(0x10120008) = 0x071F1800;
	*(volatile unsigned int *)(0x10120010) = (1*1024*1024);  
	*(volatile unsigned t *)(0x10120018) = 0x82B;
	***************************************************************/

	/********* for VGA 640x480 ************************/
	*(volatile unsigned int *)(0x1000001c) = 0x2C77;        // LCDCLK SYS_OSCCLK
	*(volatile unsigned int *)(0x10120000) = 0x3F1F3F9C;    // time0
	*(volatile unsigned int *)(0x10120004) = 0x090B61DF;    // time1
	*(volatile unsigned int *)(0x10120008) = 0x067F1800;    // time2
	*(volatile unsigned int *)(0x10120010) = (8*1024*1024); // panelBaseAddress
	*(volatile unsigned int *)(0x10120018) = 0x82B;         // control register
  
	/****** at 0x200-0x3FC are LCDpalletes of 128 words ***************
	unsigned int *inten = (unsigned int *)(0x10120200);
	for (i=0; i<128; i++){
		inten[i]=0x8F008F00;
	}
	******** yet to figure out HOW TO use these palletes *************/
	
	fb = (int *)(8*1024*1024);  // at 1MB area; enough for 800x600 SVGA
	font = fonts0;              // use fonts0 for char bit patterns 

	/******** these will show 3 bands of BLUE, GREEN, RED ********* 
	for (x = 0; x < (212*480); ++x)
	fb[x] = 0x00FF0000;  //00BBGGRR
	for (x = 212*480+1; x < (424*480); ++x)
	fb[x] = 0x0000FF00;  //00BBGGRR
	for (x = 424*480+1; x < (640*480); ++x)
	fb[x] = 0x000000FF;  //00BBGGRR
	************* used only during intial testing ****************/

	// for 640x480 VGA mode display
	for (x=0; x<640*480; x++)
		fb[x] = 0x00000000;    // clean screen; all pixels are BLACK
	cursor = 127; // cursor bit map in font0 at 127
}

void clr_scr()
{
	int x;
	// for 640x480 VGA mode display
	for (x=0; x<640*480; x++)
		fb[x] = 0x00000000;    // clean screen; all pixels are BLACK
}

void set_color(int u_color)
{
	color = u_color;
}

int get_color()
{
	return color;
}

int clr_pix(int x, int y)
{
	int pix = y*640 + x;
	fb[pix] = 0x00000000;	//clean a pixel at point(x,y) we defined BLACK is default color
}

int set_pix(int x, int y)
{
	int pix = y*640 + x;
	fb[pix] = color;
}

int draw_char(unsigned char c, int x, int y)
{
	int r, bit;
	unsigned char *caddress, byte;

	caddress = font + c*16;
	//  printf("c=%x %c caddr=%x\n", c, c, caddress);

	for (r=0; r<16; r++){
		byte = *(caddress + r);

	for (bit=0; bit<8; bit++){
		if (byte & (1<<bit))
		set_pix(x+bit, y+r);
	}
	}
}

int	clr_char(unsigned char c, int x, int y)
{
	int row, bit;
	unsigned char *caddress, byte;

	caddress = font + c*16;
	//  printf("c=%x %c caddr=%x\n", c, c, caddress);

	for (row=0; row<16; row++){
	byte = *(caddress + row);

	for (bit=0; bit<8; bit++){
	if (byte & (1<<bit))
		clr_pix(x+bit, y+row);
	}
	}
}

int draw_string(char *s, int x, int y)
{
	while(*s){
		draw_char(*s, x, y);
	x+=8;
	s++;
	}
}

int scroll()
{
	int i;
	for (i=scrow_row*16*640; i<640*480-640*16; i++){
		fb[i] = fb[i+ 640*16];
	} 
}

int kprt_char(char c, int ro, int co)
{
	int x, y;
	x = co*8;
	y = ro*16;
	//printf("c=%x [%d%d] (%d%d)\n", c, ro,co,x,y);
	draw_char(c, x, y);
   
}

int erase_kprt_char(char c, int ro, int co)
{
	int x, y;
	x = co*8;
	y = ro*16;
	//printf("c=%x [%d%d] (%d%d)\n", c, ro,co,x,y);
	clr_char(c, x, y);
}

int erasechar()
{ 
	// erase char at (row,col)
	int r, bit, x, y;
	unsigned char *caddress, byte;

	x = col*8;
	y = row*16;
 
	//printf("ERASE: row=%d col=%d x=%d y=%d\n",row,col,x,y);

	for (r=0; r<16; r++){
		for (bit=0; bit<8; bit++){
			clr_pix(x+bit, y+r);
		}
	}
} 

int clr_cursor()
{
	erase_kprt_char(cursor, row, col);
}

int put_cursor(unsigned char c)
{
	kprt_char(c, row, col);
}

int kputc(char c)
{
	clr_cursor();
	if (c=='\r'){
		col=0;
		//printf("row=%d col=%d\n", row, col);
		put_cursor(cursor);
	return;
	}
	if (c=='\n'){
		row++;
		if (row>=25){
			row = 24;
			scroll();
		}
	//printf("row=%d col=%d\n", row, col);
	put_cursor(cursor);
	return;
	}
	if (c=='\b'){
		if (col>0){
			col--;
			erasechar();
			put_cursor(cursor);
		}
	return;
	}
	// c is ordinary char
	kprt_char(c, row, col);
	col++;
	if (col>=80){
		col = 0;
		row++;
		if (row >= 25){
			row = 24;
			scroll();
		}
	}
	put_cursor(cursor); 
	//printf("row=%d col=%d\n", row, col);
}

int kprints(char *s)
{
	while(*s){
		kputc(*s);
	s++;
	}
}

int krpx(int x)
{
	char c;
	if (x){
		c = tab[x % 16];
		krpx(x / 16);
	}
	kputc(c);
}

int kprintx(int x)
{
	kputc('0'); 
	kputc('x');
	if (x==0)
		kputc('0');
	else
		krpx(x);
	kputc(' ');
}

int krpu(int x)
{
	char c;
	if (x){
		c = tab[x % 10];
		krpu(x / 10);
	}
	kputc(c);
}

int kprintu(int x)
{
	if (x==0){
		kputc(' ');
		kputc('0');
	}
	else
		krpu(x);
	kputc(' ');
}

int kprinti(int x)
{
	if (x<0){
		kputc('-');
		x = -x;
	}
	kprintu(x);
}

int kprintf(char *fmt,...)
{
	int *ip;
	char *cp;
	cp = fmt;
	ip = (int *)&fmt + 1;

	while(*cp){
		if (*cp != '%'){
			kputc(*cp);
			if (*cp=='\n')
				kputc('\r');
		cp++;
		continue;
		}
	cp++;
	switch(*cp){
		case 'c': kputc((char)*ip);      break;
		case 's': kprints((char *)*ip);  break;
		case 'd': kprinti(*ip);          break;
		case 'u': kprintu(*ip);          break;
		case 'x': kprintx(*ip);          break;
		}
	cp++; ip++;
	}
}

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

void lcd_put_pixel(int x, int y, int u_color)
{
	int c;
	c = get_color();
	set_color(u_color);
	set_pix(x,y);
	set_color(c);
}

/*		LCD显示单个汉字
 *		x : 屏幕x轴的坐标
 *		y : 屏幕y轴的坐标
 *		word : 需要显示的汉字字符编码（两个字节）
 *		scale: 显示比例
 */
void lcd_show_single_chinese(int x, int y, unsigned char* word, int scale)
{
	//汉字库hzk16的起初地址
	volatile unsigned char *addr = &_binary_hzk16_start;
	//一个汉字占32位数据
	unsigned char buffer[32];
	//一个汉字的点阵是16*16
	unsigned char val[256];
	unsigned int offset,i,j,k,len;
	/* 计算偏移地址 */
	offset = (94*(unsigned int)(word[0]-0xa0-1)+(word[1]-0xa0-1))*32;
	addr += offset;//首地址+偏移地址
	//拷贝32个字节数据到buffer数组
	for(i=0; i<32; i++,addr++)
	{
	buffer[i] = *addr;
	}

	/* 按顺序取出32个字节字模中的每一个二进制位，共256位，这个0或1放到val数组 */

	len = 0;
	for(k=0; k<16; k++)
	{
		for(j=0; j<2; j++)
		{
		    for(i=0; i<8; i++)
			{
				val[len++] = buffer[k*2+j]&(0x80 >> i);
			}
		}
	}

	/* 根据val数组里面的0或1点阵来设置对应坐标点象素的颜色 */
	len = 0;
	for (j = y; j < y+16; j++)
	{
		for (i = x; i < x+16; i++)
		{
		/* 根据点阵的某位决定是否描颜色 */
		if (val[len++])
		lcd_put_pixel(scale*i, scale*j, color);
		}
	}

}

//LCD打印多个中文字符串
void fb_print_chinese(int x, int y, unsigned char* word, int scale)
{
	int i = 0;
	
	while(word[i])
	{    
	lcd_show_single_chinese(x,y,&(word[i]),scale);
	i+=2;	//一个汉字占两个字节
	x+=16;	//一个汉字显示16x16，下一个字开始横坐标要加16
	}
}
