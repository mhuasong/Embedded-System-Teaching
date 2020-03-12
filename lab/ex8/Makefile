all:
	arm-linux-gcc -o candasm CandAsm.c -g -static

run: all
	sudo qemu-arm -g 1024 candasm  &
	sleep 3
	ddd --debugger arm-linux-gdb candasm


clean:
	rm -rf *.o candasm
