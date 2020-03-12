all:
	arm-linux-gcc test1.s -o  test1 -nostdlib -g

run: all
	sudo qemu-arm  -g 1024 test1  &
	sleep 3
	ddd --debugger arm-linux-gdb test1


clean:
	rm -rf *.o test1
