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
void destroyList(struct FileName *f) {
	struct FileName *temp = f->next;
	while(f->name != NULL) {
		free(f->name);
		free(f);
		f = temp;
		temp = temp->next;
	}
	free(f);
}
void rehash(Map hmap) {

}
void hashmapInsert(Map hmap, char *file, char *word, unsigned long key)
{
	long index, i;
	index = key % hmap->size;
	if(hmap->table[index].key == 0) {
		hmap->table[index].nList = malloc(sizeof(struct FileName));
		hmap->table[index].key = key;
		hmap->table[index].word = word;
		(hmap->table[index].nList)->name = file;
		(hmap->table[index].nList)->next = malloc(sizeof(struct FileName));
		(hmap->table[index].nList)->next->name = NULL;
		return;
	}
	if(hmap->table[index].key == key) {
		struct FileName *n = hmap->table[index].nList;
		while(n->name != NULL) {
			n = n->next;
		}
		n->name = file;
		n->next = malloc(sizeof(struct FileName));
		n->next->name = NULL;
	}
}
struct HElement *hashmapGet(Map hmap, unsigned long key, char *word) {
	long index, i;
	index = key % hmap->size;
	if(hmap->table[index].key == key) {
		if(strcmp(hmap->table[index].word,word) != 0) {
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
			destroyList(hmap->table[s].nList);
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
struct List *and(struct List *one, struct List *two) {
	struct List *l= malloc(sizeof(struct List));
	l->list = malloc(sizeof(struct FileName));
	struct FileName *root = l->list;
	struct FileName *first = one->list;
	struct FileName *second = two->list;
	while(first->name != NULL) {
		while(second->name != NULL) {
			if(strcmp(first->name,second->name) == 0) {
				if(root->name == NULL)
					root->name = first->name;
				root->next = malloc(sizeof(struct FileName));
				root = root->next;
			}
			second = second->next;
		}
		second = two->list;
		first = first->next;
	}
	return l;
}
struct List * or(struct List *one, struct List *two) {
	struct List *l= malloc(sizeof(struct List));
	l->list = malloc(sizeof(struct FileName));
	struct FileName *root = l->list;
	struct FileName *first = one->list;
	struct FileName *second = two->list;
	while(first->name != NULL) {
		int add = 0;
		while(root->name != NULL) {
			if(strcmp(first->name,root->name) == 0) {
				add = 1;
			}
			root = root->next;
		}
		if(add == 0) {
			root->name = first->name;
			root->next = malloc(sizeof(struct FileName));
		}
		root = l->list;
		first = first->next;
	}
	while(second->name != NULL) {
		int add = 0;
		while(root->name != NULL) {
			if(strcmp(second->name,root->name) == 0) {
				add = 1;
			}
			root = root->next;
		}
		if(add == 0) {
			root->name = second->name;
			root->next = malloc(sizeof(struct FileName));
		}
		root = l->list;
		second = second->next;
	}
	return l;
}
