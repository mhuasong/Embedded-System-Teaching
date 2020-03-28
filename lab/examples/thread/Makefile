CC = arm-linux-gcc
LD = arm-linux-ld
EXEC = thread 
OBJS = thread.o 

CFLAGS +=
LDFLAGS += -lpthread

all: $(EXEC) $(EXEC1)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS$(LDLIBS_$@)) -static -lpthread
	@cp $(EXEC) /home/mhs/busybox-1.28.1/_install/home/examples

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o

