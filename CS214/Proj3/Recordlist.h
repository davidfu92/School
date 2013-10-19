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
	struct Record *rec = l->list;
	struct Record *temp;
	while(rec != NULL) {
		temp = rec;
		rec = rec->next;
		free(temp);
	}
};

void sortList(struct Record *r) {

};
#endif
