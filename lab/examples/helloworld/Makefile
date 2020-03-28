CC = arm-linux-gcc
LD = arm-linux-ld
EXEC = helloworld
OBJS = helloworld.o

CFLAGS +=
LDFLAGS += 

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS$(LDLIBS_$@))  -static
	cp $(EXEC) /home/mhs/busybox-1.28.1/_install/home/examples

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o

