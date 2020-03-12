all:
	arm-linux-gcc -c  init.c -o init.o  -g -nostdlib
	arm-linux-gcc -c  startup.s -o startup.o -g
	arm-linux-gcc -c  sum.s -o sum.o -g
	#arm-linux-gcc -o  ctest init.o startup.o sum.o  -g
	arm-linux-ld -T map.lds init.o startup.o sum.o -o test.elf 
	
run: all
	sudo qemu-arm  -g 1234 test.elf   &
	sleep 3
	ddd --debugger arm-linux-gdb test.elf 

clean:
	rm -rf *.o test.elf 
