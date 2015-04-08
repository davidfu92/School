#Sample Makefile. You can make changes to this file according to your need
# The executable must be named proxy

CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -lpthread

OBJS = proxy.o csapp.o

all: proxy

proxy: $(OBJS)

csapp.o: csapp.c
	$(CC) $(CFLAGS) -c csapp.c

proxy.o: proxy.c
	$(CC) $(CFLAGS) -c proxy.c

thread:
	$(CC) -w $(CFLAGS) proxy_multithread.c -o thread $(LDFLAGS) csapp.o
proc:
	$(CC) -w $(CFLAGS) proxy_multiproc.c -o proc $(LDFLAGS) csapp.o
clean:
	rm -f *~ *.o proxy 

