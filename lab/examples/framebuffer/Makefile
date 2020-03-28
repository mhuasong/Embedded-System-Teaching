CC = arm-linux-gcc
LD = arm-linux-ld

EXEC = fbtest 
OBJS = fbtest.o

CFLAGS +=
LDFLAGS += 

all: $(EXEC)
	cp $(EXEC) /home/mhs/busybox-1.28.1/_install/home/examples

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS$(LDLIBS_$@))  -static


clean:
	-rm -f $(EXEC) *.elf *.gdb *.o

