all:
	gcc search.c -o search
	make object
	make library
	make index
object:
	gcc -c Hashmap.c
library:
	ar -cvq libs2.a *.o
clean:
	rm search indexer/index indexer/*.o *.a indexer/*.a
index:
	gcc -c indexer/Hashmap.c -o indexer/Hashmap.o
	gcc -c indexer/sorted-list.c -o indexer/sorted-list.o
	ar -cvq indexer/libsl.a indexer/*.o
	gcc indexer/index.c -o indexer/index indexer/libsl.a
