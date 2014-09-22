#ifndef HASHMAP_H
#define HASHMAP_H
/** Hashmap structure */
struct Customer {
	char *name;
	int ID, ZCode;
	double balence;
	char *address;
};
struct HElement {
	void *element;
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
void hashmapInsert(Map hmap, void *element, unsigned long key);

/** Removes the storage for the element of the key and returns the element. */
int *hashmapRemove(Map hmap, unsigned long key);

/** Returns the element for the key. */
struct HElement *hashmapGet(Map hmap, unsigned long key);

/** Removes the hashmap structure. */
void destroyHashmp(Map hmap);

/** Rehashes hashmap*/
void rehash(Map hmap);
#endif
