OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm") /*指定输出可执行文件elf格式，32位ARM指令，小端模式*/
/*OUTPUT_FORMAT("elf32-arm", "elf32-arm", "elf32-arm")*/
OUTPUT_ARCH(arm)	/*指定体系结构为ARM*/
ENTRY(_start)	/*指定输出可执行文件的起始入口为_start*/
SEARCH_DIR("=/usr/local/lib"); SEARCH_DIR("=/lib"); SEARCH_DIR("=/usr/lib");
SECTIONS
{
	. = 0x10000;	/*定位当前地址为0x10000地址*/

	. = ALIGN(4);
	.text      :
	{
	  start.o	(.text)	/*第一个代码段来自目标文件start.o*/
	  *(.text)	/*其他代码段*/
	}

	. = ALIGN(4);
	.rodata : { *(.rodata) }	/*指定只读数据段*/

	. = ALIGN(4);

	.data	:				/*指定读写数据段*/
	{
	_binary_image1_start = .;
	  huanghelou.o	(.data)		/* include image1.o as a data section */
	_binary_image2_start = .;
	  wust.o	(.data)		/* include image1.o as a data section */	  
	  *(.data)	 
	} 	

	. = ALIGN(4);	/*指定bss段 静态内存分配*/
	__bss_start = .;	
	.bss : { *(.bss) }

	. = ALIGN(8);	/*以八字节对齐*/
	. = . + 0x1000; /* 4kB of stack memory */
	stack_top = .;	/*指定栈顶指针地址*/
	_end = .;
}
