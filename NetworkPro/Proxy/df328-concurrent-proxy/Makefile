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
	$(CC) $(CFLAGS) -c proxy_multithread.c
proc:
	$(CC) $(CFLAGS) -c proxy_multiproc.c
clean:
	rm -f *~ *.o proxy 

