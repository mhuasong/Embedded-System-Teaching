all:
	arm-linux-gcc ex2.s -o  ex2 -nostdlib -g

run: all
	sudo qemu-arm  -g 1024 ex2  &
	sleep 3
	ddd --debugger arm-linux-gdb ex2


clean:
	rm -rf *.o ex2
