all:
	make object
	make libary
	gcc index.c -o index libsl.a
object:
	gcc -c Hashmap.c
	gcc -c sorted-list.c
libary:
	ar -cvq libsl.a *.o
