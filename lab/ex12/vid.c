/************** vid.c file**********************/
int volatile *fb;
int WIDTH = 640; // default to VGA mode for 640x480

int fbuf_init(void)
{
  int x; int i;
  /**** for SVGA 800X600 these values are in ARM DUI02241 *********
  *(volatile unsigned int *)(0x1000001c) = 0x2CAC; // 800x600
  *(volatile unsigned int *)(0x10120000) = 0x1313A4C4;
  *(volatile unsigned int *)(0x10120004) = 0x0505F6F7;
  *(volatile unsigned int *)(0x10120008) = 0x071F1800;
  *(volatile unsigned int *)(0x10120010) = (6*1024*1024);  
  *(volatile unsigned int *)(0x10120018) = 0x82B;
  ***************************************************************/

  /********* for VGA 640x480 ************************/
  *(volatile unsigned int *)(0x1000001c) = 0x2C77;        // LCDCLK SYS_OSCCLK
  *(volatile unsigned int *)(0x10120000) = 0x3F1F3F9C;    // time0
  *(volatile unsigned int *)(0x10120004) = 0x090B61DF;    // time1
  *(volatile unsigned int *)(0x10120008) = 0x067F1800;    // time2
  *(volatile unsigned int *)(0x10120010) = (2*1024*1024); // panelBaseAddress
  *(volatile unsigned int *)(0x10120018) = 0x82B;         // control register
  /***************************************************************/
 
  /******** yet to figure out HOW TO use these palletes *************/
  fb = (int *)(2*1024*1024);  // at 2MB area; enough for VGA 640x480
  

  // for (x = 0; x < (800 * 600); ++x) // for one BAND
  /******** these will show 3 bands of BLUE, GREEN, RED *********/ 
  for (x = 0; x < (212*480); ++x)
  	fb[x] = 0x00FF0000;  //00BBGGRR
  for (x = 212*480+1; x < (424*480); ++x)
  	fb[x] = 0x0000FF00;  //00BBGGRR
  for (x = 424*480+1; x < (640*480); ++x)
  	fb[x] = 0x000000FF;  //00BBGGRR

}
