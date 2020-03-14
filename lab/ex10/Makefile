all:
	arm-none-linux-gnueabi-as -mcpu=arm926ej-s -g start.S -o start.o 
	arm-none-linux-gnueabi-gcc -c -mcpu=arm926ej-s -g init.c -o init.o # -nostdlib
	arm-none-linux-gnueabi-ld -T map.lds init.o start.o -o test.elf
	arm-none-linux-gnueabi-objcopy -O binary test.elf test.bin
	
run: all
	qemu-system-arm -M versatilepb -m 128M -gdb tcp::1024 -serial stdio -kernel test.elf -S &
	sleep 3
	ddd --debugger arm-none-linux-gnueabi-gdb test.elf
	#qemu-system-arm -M versatilepb -serial stdio -kernel test.bin

clean:
	rm -rf *.o test.elf test.bin
