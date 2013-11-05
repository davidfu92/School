#include <stdio.h>
#include <stdlib.h>
#include "Hashmap.h"
#include "Recordlist.h"
/* this should be prime */
#define TABLE_STARTSIZE 1021
//const int mapsize[] = [1000,200,300,400,500];
Map hashmapCreate(int startsize)
{
	Map hmap = malloc(sizeof(struct Hashmap));
	hmap->table = calloc(startsize, sizeof(struct HElement));
	hmap->size = startsize;
	return hmap;
}
void rehash(Map hmap) {

}
void hashmapInsert(Map hmap, char *file, char *word, unsigned long key)
{
	long index, i;
	index = key % hmap->size;
	if(hmap->table[index].key == 0) {
		hmap->table[index].rList = malloc(sizeof(star *hashmapRemove(Map hmap, unsigned long key);                               | 30     }
					 26 char *hashmapRemove(Map hmap, unsigned long key);                               | 30     }
					 uct FileName));
		hmap->table[index].key = key;
		(hmap->table[index].rList)->name = file;
		(hmap->table[index].rList)->word =f(hmap->table[index].key == key) {
		   	word;
		(hmap->table[index].rList)->next = NULL;
		(hmap->table[index].word) = word;
		return;
	}
	if(hmap->table[index].key == key) {
		
	}
}
struct HElement *hashmapGet(Map hmap, unsigned long key, char *word) {
	long index, i;
	index = key % hmap->size;
	if(hmap->table[index].key == key) {
		struct List *rl = ((hmap->table[index]).rList);
		if(strcmp(rl->word,word) != 0) {
			return &(hmap->table[index]);
		}
	}
	return NULL;
}

void destroyHashmap(Map hmap)
{
	int s = hmap->size;
	for(s; s>0; s--) {
		if(hmap->table[s].key != 0)
		destroyList(hmap->table[s].rList);
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
