all:
	arm-linux-gcc ex6.s -o  ex6 -nostdlib -g

run: all
	sudo qemu-arm  -g 1024 ex6  &
	sleep 3
	ddd --debugger arm-linux-gdb ex6


clean:
	rm -rf *.o ex6
