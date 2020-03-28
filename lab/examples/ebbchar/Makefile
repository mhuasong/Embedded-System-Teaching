obj-m +=ebbchar.o

CC = arm-none-linux-gnueabi-gcc
LD = arm-none-linux-gnueabi-ld
EXEC = testebbchar
OBJS = testebbchar.o

CFLAGS +=
LDFLAGS += 

all:	
	make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- -C /home/mhs/linux-3.2/ M=$(PWD) modules
	$(CC) $(LDFLAGS) -o $(EXEC) $(EXEC).c $(LDLIBS$(LDLIBS_$@))  -static
	cp $(EXEC) /home/mhs/busybox-1.28.1/_install/home/examples/	
	cp ebbchar.ko /home/mhs/busybox-1.28.1/_install/home/examples/

clean:
	make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- -C /home/mhs/linux-3.2/ M=$(PWD) clean
	-rm -f $(EXEC)

