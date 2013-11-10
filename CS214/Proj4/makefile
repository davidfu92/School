all:
	make clean
	gcc search.c -o search
	make object
	make library
	make index
object:
	gcc -c Hashmap.c
	gcc -c indexer/sorted-list.c indexer/Hashmap.c
library:
	ar -cvq indexer/libs1.a indexer/*.o
	ar -cvq libs2.a *.o
clean:
	rm search indexer/index indexer/sorted-list.o *.a indexer/*.a
index:
	gcc indexer/index.c -o index libs1.a
