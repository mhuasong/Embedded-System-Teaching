all:
	arm-linux-gcc test.s -o  mytest -nostdlib -g

run: all
	sudo qemu-arm  -g 1024 mytest  &
	sleep 3
	ddd --debugger arm-linux-gdb mytest


clean:
	rm -rf *.o mytest
