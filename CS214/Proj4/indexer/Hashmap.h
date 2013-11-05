#ifndef HASHMAP_H
#define HASHMAP_H
#include "Recordlist.h"
/** Hashmap structure */
struct HElement {
	struct List *rList;
	long key;
};
struct Hashmap {
	struct HElement *table;
	long size;	
};
typedef struct Hashmap* Map;

/** Creates a new hashmap near the given size. */
Map hashmapCreate(int startsize);

/** Inserts a new element into the hashmap. */
void hashmapInsert(Map hmap, char *file, char *word, unsigned long key);

/** Removes the storage for the element of the key and returns the element. */
char *hashmapRemove(Map hmap, unsigned long key);

/** Returns the element for the key. */
struct HElement *hashmapGet(Map hmap, unsigned long key, char *word);

/** Removes the hashmap structure. */
void destroyHashmp(Map hmap);

/** Rehashes hashmap*/
void rehash(Map hmap);
#endif
