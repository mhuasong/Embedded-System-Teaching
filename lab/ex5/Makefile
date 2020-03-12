all:
	arm-linux-gcc test2.s -o  test2 -nostdlib -g

run: all
	sudo qemu-arm  -g 1024 test2  &
	sleep 3
	ddd --debugger arm-linux-gdb test2


clean:
	rm -rf *.o test2
