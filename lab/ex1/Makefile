all:
	arm-linux-gcc ex1.s -o  ex1 -nostdlib -g

run: all
	sudo qemu-arm  -S -g 1024 ex1  &
	sleep 3
	ddd --debugger arm-linux-gdb ex1


clean:
	rm -rf *.o ex1
