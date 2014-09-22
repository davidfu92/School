all:
	gcc producer.c -o produce
	make object
	make library
object:
	gcc -c Hashmap.c
	gcc -c Queue.c
library:
	ar -cvq library.a *.o
clean:
	rm produce library.a *.o *.a
multi:
	gcc multi.c -o multi
