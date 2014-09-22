#ifndef RECORDLIST_H
#define RECORDLIST_H
/*
 *  Defining the struct Record and Recordlist
 */
struct Record
{
	char *file;
	int count;
	struct Record *next,*prev;
};

struct List {
	char *word;
	struct Record *list;
};

void destroyList(struct List *l) {
	if(l != NULL) {
		struct Record *rec = l->list;
		struct Record *temp;
		while(rec != NULL) {
			temp = rec;
			rec = rec->next;
			free(temp->file);
			free(temp);
		}
	}
};

void sortList(struct Record *r) {
	if(r->prev != NULL) {
		if(r->count > r->prev->count) {
			struct Record *temp = r->prev;	
			if(r->prev->prev->next != NULL)
				r->prev->prev->next = r;
			if(r->prev->next != NULL)
				r->prev->next = r->next;
			if(r->prev->prev != NULL)
				r->prev->prev = r;
			if(r->next->prev != NULL)
				r->next->prev = temp;
			if(r->prev != NULL)
				r->prev = r;
			if(r->next != NULL)
				r->next = temp;
		}
	}
};
#endif
