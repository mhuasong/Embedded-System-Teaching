all:
	arm-linux-gcc -o demo datademo.c -g -static

run: all
	sudo qemu-arm -g 1024 demo  &
	sleep 3
	ddd --debugger arm-linux-gdb demo


clean:
	rm -rf *.o demo
