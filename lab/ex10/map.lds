OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")	/*指定输出可执行文件elf格式，32位ARM指令，小端模式*/
OUTPUT_ARCH(arm)	/*指定体系结构为ARM*/
ENTRY(_Reset)	/*指定输出可执行文件的起始入口为_Reset*/

SECTIONS
{
 . = 0x10000;	/*定位当前地址为0x10000地址*/
 .start . : { start.o(.text) }	/*第一个代码段来自目标文件start.o*/
 .text : { *(.text) }	/*其他代码段*/
 .data : { *(.data) }	/*指定读写数据段*/
 .bss : { *(.bss COMMON) }	/*指定bss段 静态内存分配*/
 . = ALIGN(8);	/*以八字节对齐*/
 . = . + 0x1000; /* 4kB of stack memory */
 stack_top = .;	/*指定栈顶指针地址*/
}
