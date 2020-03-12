all:
	arm-linux-gcc loop3.s -o  loop3 -nostdlib -g

run: all
	sudo qemu-arm -g 1024 loop3  &
	sleep 3
	ddd --debugger arm-linux-gdb loop3


clean:
	rm -rf *.o loop3
