#ifndef MY_MALLOC_H
#define MY_MALLOC_H

struct MemBlock {
	struct MemBlock *prev, *succ;
	int size, isfree;

};
struct Node {
	int value;
	struct Node *next;
	struct node *prev;
}
#endif
