all:
	arm-linux-gcc loop2.s -o  loop2 -nostdlib -g

run: all
	sudo qemu-arm -g 1024 loop2  &
	sleep 3
	ddd --debugger arm-linux-gdb loop2


clean:
	rm -rf *.o loop2
