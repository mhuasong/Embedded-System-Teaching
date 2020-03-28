#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

#define LCD_TFT
#ifdef LCD_TFT
#define RED_COLOR    0xf800
#define GREEN_COLOR  0x07e0
#define BLUE_COLOR   0x001f
#else
#define RED_COLOR    0xE0
#define GREEN_COLOR  0x1C
#define BLUE_COLOR   0x03
#endif

int WIDTH = 640;
int volatile *fbp; 

int show_bmp(char *path, int start_row, int start_col)
{

	FILE *fp; 
	char *p;
	int rc; 
	printf("into show_bmp function\n");  
	if(path == NULL)  
	{  
	printf("path Error,return\n");  
	return -1;  
	}  
	printf("path = %s\n", path);  
	fp = fopen( path, "rb" );  
	if(fp == NULL){  
	printf("load cursor file open failed\n");  
	return -1;  
	}  
	  
	/* file top */  
	//fseek(fp,0,SEEK_SET);  
	int size=0;
	/* 求解文件长度 */  
	fseek(fp,0,SEEK_SET);  
	fseek(fp,0,SEEK_END);  
	  
	size = ftell(fp);  
	printf("file length is %d\n",size);  
	  
	p = (char*)calloc(1,size);  
	if(p == NULL){  
	printf("load > malloc bmp out of memory!\n");  
	return -1;  
	}  
	/* 再移位到文件头部 */  
	fseek(fp,0,SEEK_SET);  

	rc = fread(p, size,1, fp);  
	if ( rc != 1)  
	{  
	printf("read header error!\n");  
	fclose( fp );  
	return( -2 );  
	}  
	
	int h, w, rsize, i, j;
	unsigned short pixel;
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
		r = r >> 3; g = g >>2; b= b >> 3;
		pixel = (r<<11) | (g<<5) | b; // pixel value
		*(((unsigned short *)fbp)+i*WIDTH + j) = pixel; // write to frame buffer
		//*((unsigned short int*)(fbp + +i*WIDTH + j)) = pixel;
		pp += 3; // advance pp to next pixel
		}
	p -= rsize; // to preceding row
	}
}

int main()
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    //char *fbp = 0;
    int x = 0, y = 0;
    long int location = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (!fbfd) {
        printf("Error: cannot open framebuffer device.\n");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
        printf("Error reading fixed information.\n");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
        printf("Error reading variable information.\n");
        exit(3);
    }

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    printf("%dx%d, %dbpp, screensize = %d\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel, screensize );

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                       fbfd, 0);
    if ((int)fbp == -1) {
        printf("Error: failed to map framebuffer device to memory.\n");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

    x = 100; y = 100;       // Where we are going to put the pixel

    if(vinfo.bits_per_pixel == 8)  // 8bpp only
    {
        // 8bpp framebuffer test
        printf("8bpp framebuffer test\n");
        printf("a byte in fbp is a pixel of LCD, just set the value of fbp to put color to LCD\n");
        printf("byte format:\n");
        printf("  bit:| 7  6  5 |  4  3  2 | 1  0 |\n");
        printf("      |  red    |   green  | blue |\n");

        // Red Screen
        printf("Red Screen\n");
        for(y = 0; y < 240; y++)
        {
            for(x = 0; x < 320; x++)
            {
                *(fbp + y * 320 + x) = RED_COLOR;
            }
        }
        sleep(2);

        // Green Screen
        printf("Green Screen\n");
        for(y = 0; y < 240; y++)
        {
            for(x = 0; x < 320; x++)
            {
                *(fbp + y * 320 + x) = GREEN_COLOR;
            }
        }
        sleep(2);

        // Blue Screen
        printf("Blue Screen\n");
        for(y = 0; y < 240; y++)
        {
            for(x = 0; x < 320; x++)
            {
                *(fbp + y * 320 + x) = BLUE_COLOR;
            }
        }
        sleep(2);

        // Grid Screen
        printf("Grid Screen\n");
        for(y = 0; y < 240; y++)
        {
            for(x = 0; x < 320; x++)
            {
                *(fbp + y * 320 + x) = x;
            }
        }
        sleep(2);

    }else if(vinfo.bits_per_pixel == 16)  // 16bpp only
    {
        // 16bpp framebuffer test
        printf("16bpp framebuffer test\n");
        printf("two byte in fbp is a pixel of LCD, just set the value of fbp to put color to LCD\n");
        printf("byte format:\n");
        printf("  bit:| 15 14 13 12 11 |  10  9  8  7  6  5 | 4  3  2  1  0 |\n");
        printf("      |      red       |       green        |      blue     |\n");
                                                                                                               
        // Red Screen
        printf("Red Screen\n");
        for(y = 0; y < 480; y++)
        {
            for(x = 0; x < 640; x++)
            {
                *(((unsigned short *)fbp) + y * 640 + x) = RED_COLOR;
            }
        }
        sleep(2);
                                                                                                               
        // Green Screen
        printf("Green Screen\n");
        for(y = 0; y < 480; y++)
        {
            for(x = 0; x < 640; x++)
            {
                *(((unsigned short *)fbp) + y * 640 + x) = GREEN_COLOR;
            }
        }
        sleep(2);

        // Blue Screen
        printf("Blue Screen\n");
        for(y = 0; y < 480; y++)
        {
            for(x = 0; x < 640; x++)
            {
                *(((unsigned short *)fbp) + y * 640 + x) = BLUE_COLOR;
            }
        }
        sleep(2);
                                                                                                               
        // Grid Screen
        printf("Grid Screen\n");
        for(y = 0; y < 480; y++)
        {
            for(x = 0; x < 640; x++)
            {
                *(((unsigned short *)fbp) + y * 640 + x) = x;
            }
        }
        sleep(2);
                                                                                                               
    }else
    {
        printf("8bpp && 16bpp only!!!\n");
    }
    
    sleep(2);
    show_bmp("./timg.bmp",0,0);
    munmap(fbp, screensize);
    close(fbfd);
    return 0;
}

