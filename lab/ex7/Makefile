
all:mytest hello
CC = gcc
INSTDIR = $(HOME)/lab/install
mytest:main.o mytool1.o mytool2.o
	$(CC) -o mytest main.o mytool1.o mytool2.o
main.o:main.c mytool1.h mytool2.h
	$(CC) -c main.c
mytool1.o:mytool1.c mytool1.h
	$(CC) -c mytool1.c
mytool2.o:mytool2.c mytool2.h
	$(CC) -c mytool2.c
hello:helloworld.o
	$(CC) -o hello helloworld.c
clean:
	rm -rf *.o mytest hello
install: mytest
	@if [ -d $(INSTDIR) ]; \
	then \
	cp mytest $(INSTDIR) &&\
	chmod a+x $(INSTDIR)/mytest &&\
	chmod og-w $(INSTDIR)/mytest &&\
	echo "Installed in $(INSTDIR) success!";\
	else \
	echo "Sorry, $(INSTDIR) does not exist";false;\
	fi



