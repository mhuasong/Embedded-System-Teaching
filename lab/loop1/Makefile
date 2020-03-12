all:
	arm-linux-gcc loop1.s -o  loop1 -nostdlib -g

run: all
	sudo qemu-arm -g 1024 loop1  &
	sleep 3
	ddd --debugger arm-linux-gdb loop1


clean:
	rm -rf *.o loop1
