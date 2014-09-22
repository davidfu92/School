#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hashmap.h"
/* this should be prime */
#define TABLE_STARTSIZE 1021
//const int mapsize[] = [1000,200,300,400,500];
Map hashmapCreate(int startsize) {
	Map hmap = malloc(sizeof(struct Hashmap));
	hmap->table = calloc(startsize, sizeof(struct HElement));
	hmap->size = startsize;
	return hmap;
}
void hashmapInsert(Map hmap, void *element, unsigned long key) {
	int index;
	index = key % hmap->size;
	if(hmap->table[index].key == 0) {
		hmap->table[index].key = key;
		hmap->table[index].element = element;
		return;
	}
}
struct HElement *hashmapGet(Map hmap, unsigned long key) {
	long index, i;
	index = key % hmap->size;
	if(hmap->table[index].key == key) {
		return &(hmap->table[index]);
	}
	return NULL;
}

void destroyHashmap(Map hmap)
{
	int s = hmap->size;
	for(s; s>0; s--) {
		if(hmap->table[s].key != 0)
			free(hmap->table[s].element);
	}
	free(hmap->table);
	free(hmap);
}

unsigned long hash(char *word)
{
	unsigned long hash = 5381;
	char *t = word;
	char c;
	c = *t;
	while (c != '\0') {
		hash = (hash * 29 + hash) + (int)c; /* hash * 29 + c */
		c=*(++t);
	}
	return hash;
}
