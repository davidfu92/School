#include	"my_malloc.h"
#include	<unistd.h>
#include	<stdio.h>
#include	<string.h>
#include	<errno.h>

// Using BKR Full-Scale malloc as Reference
struct Node *list = malloc(sizeof(struct Node));
void *new_malloc(unsigned int size) {
	static struct MemBlock *root = 0;
	static struct MemBlock *last = 0;
	struct MemBlock *p;
	struct MemBlock *succ;
	p = root;
	while (p != 0) {
		if (p->size < size) {
			p = p->succ;					// too small
		}
		else if (!p->isfree) { 
			p = p->succ;					// in use
		}
		else if (p->size < (size + sizeof(struct MemBlock))) {
			p->isfree = 0;			// too small to chop up
			struct Node *n = list;
			while(n != NULL)
				n = n->next;
			n = malloc(sizeof(struct Node));
			n->value = (int)((char *)p + sizeof(struct MemBlock));
			return (char *)p + sizeof(struct MemBlock);
		}
		else {
			succ = (struct MemBlock *)((char *)p + sizeof(struct MemBlock) + size);
			succ->prev = p;
			succ->succ = p->succ;
			if(p->succ != 0)					//begin add
				p->succ->prev = succ;			//end add
			p->succ = succ;
			succ->size = p->size - sizeof(struct MemBlock) - size;
			succ->isfree = 1;
			p->size = size;
			p->isfree = 0;
			last = (p == last) ? succ : last;
			return (char *)p + sizeof(struct MemBlock);
		}
	}
	if ((p = (struct MemBlock *) sbrk(sizeof(struct MemBlock) + size)) == (void *)-1) {
		return 0;
	}
	else if (last == 0) {				// first block created
		printf("Creating first memory block of  size %d\n", size);
		p->prev = 0;
		p->succ = 0;
		p->size = size;
		p->isfree = 0;
		root = last = p;
		return (char *)p + sizeof(struct MemBlock);
	}
	else {						// other blocks appended
		printf("Adding a new block of size %d\n", size);
		p->prev = last;
		p->succ = last->succ;
		p->size = size;
		p->isfree = 0;
		last->succ = p;
		last = p;
		return (char *)p + sizeof(struct MemBlock);
	}
	return 0;
}

void new_free(void *p) {
	struct MemBlock *ptr;
	struct MemBlock *pred;
	struct MemBlock *succ;
	ptr = (struct MemBlock *)((char *)p - sizeof(struct MemBlock));
	if(ptr == NULL)
		printf("empty");
	if ((pred = ptr->prev) != 0 && pred->isfree)
	{
		pred->size += sizeof(struct MemBlock) + ptr->size;	// merge with predecessor

		pred->succ = ptr->succ;
		//begin added
		ptr->isfree=1;
		pred->succ = ptr->succ;
		if(ptr->succ != 0)
			ptr->succ->prev = pred;
		//end added
		printf("freeing memeory block %#x and moving prev block to connect new size is %d.\n", p, pred->size);
	}
	else
	{
		printf("freeing memeory block %#x.\n", p);
		ptr->isfree = 1;
		pred = ptr;
	}
	if ((succ = ptr->succ) != 0 && succ->isfree)
	{
		pred->size += sizeof(struct MemBlock) + succ->size;	// merge with successor
		pred->succ = succ->succ;
		//begin added
		pred->isfree = 1;

		if(succ->succ != 0)
			succ->succ->prev=pred;
		//end added
		printf("freeing block %#x and moving next block to connect thus new size is %d.\n", p, pred->size);

	}
}
