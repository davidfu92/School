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
		hmap->table[index].rList = malloc(sizeof(struct List));
		hmap->table[index].key = key;
		(hmap->table[index].rList)->list = malloc(sizeof(struct Record));
		(hmap->table[index].rList)->word = word;
		(hmap->table[index].rList)->list->file = file;
		(hmap->table[index].rList)->list->count = 1;
		(hmap->table[index].rList)->list->next = NULL;
		(hmap->table[index].rList)->list->prev = NULL;
		return ;
	}
	if(hmap->table[index].key == key) {
		struct List *rl = (hmap->table[index]).rList;
		if(strcmp(rl->word,word) != 0) {
			rehash(hmap);
			hashmapInsert(hmap, file,word,key);
			return;
		}
		struct Record *r = rl->list;
		while(1) {
			if(strcasecmp(r->file, file) == 0) {
				r->count = r->count + 1;
				sortList(r);
				return;
			}
			if(r->next == NULL) {
				r->next = malloc(sizeof(struct Record));
				r->next->file=file;
				r->next->count = 1;
				r->next->next = NULL;
				r->next->prev = r;
				return;
			}
			r = r->next;
		}
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
