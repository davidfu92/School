#ifndef SORTED_LIST_H
#define SORTED_LIST_H
/*
 * sorted-list.h
 */
#include <stdlib.h>
/*
 * Node type to make sorting a bit easier even though at the cost of twice the memory
 */
struct Node
{
	void *value;
	struct Node *next;
};
/*
 * Sorted list type.  You need to fill in the type as part of your implementation.
 */
struct SortedList
{
	struct Node *root;
	int (*comp)(void *, void *);

};

typedef struct SortedList* SortedListPtr;


/*
 * Iterator type for user to "walk" through the list item by item, from
 * beginning to end.  You need to fill in the type as part of your implementation.
 */
struct SortedListIterator
{
	struct Node *ptr;
};

typedef struct SortedListIterator* SortedListIteratorPtr;


/*
 * When your sorted list is used to store objects of some type, since the
 * type is opaque to you, you will need a comparator function to order
 * the objects in your sorted list.
 *
 * You can expect a comparator function to return -1 if the 1st object is
 * smaller, 0 if the two objects are equal, and 1 if the 2nd object is
 * smaller.
 *
 * Note that you are not expected to implement any comparator functions.
 * You will be given a comparator function when a new sorted list is
 * created.
 */

typedef int (*CompareFuncT)(void *, void *);


/*
 * SLCreate creates a new, empty sorted list.  The caller must provide
 * a comparator function that can be used to order objects that will be
 * kept in the list.
 * 
 * If the function succeeds, it returns a (non-NULL) SortedListT object.
 * Else, it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

SortedListPtr SLCreate(CompareFuncT cf) {
	SortedListPtr sList = malloc(sizeof(struct SortedList));
	sList->comp = cf;
	sList->root = malloc(sizeof(struct Node));
	sList->root->value = NULL;
	sList->root->next = NULL;
	return sList;
};

/*
 * SLDestroy destroys a list, freeing all dynamically allocated memory.
 *
 * You need to fill in this function as part of your implementation.
 */
void SLDestroy(SortedListPtr list) {
	struct Node *temp = list->root;
	while(temp != NULL) {
		list->root = list->root->next;
		free(temp);
		temp = list->root;
	}
	free(list);
};


/*
 * SLInsert inserts a given object into a sorted list, maintaining sorted
 * order of all objects in the list.  If the new object is equal to a subset
 * of existing objects in the list, then the subset can be kept in any
 * order.
 *
 * If the function succeeds, it returns 1.  Else, it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

int SLInsert(SortedListPtr list, void *newObj) {
	if(list->root->value == NULL) {
		list->root->value = newObj;
		return 1;
	}
	struct Node *n = malloc(sizeof(struct Node));
	n->value = newObj;
	struct Node *obj = list->root, *preobj = NULL;
	while(obj->value != NULL) {
		if(list->comp (newObj , obj->value) == -1) {
			if(obj->next == NULL) {
				obj->next = n;
				return 1;
			} else if(list->comp (newObj , obj->next->value) >= 0){
				obj->next = n;
				return 1;
			}
				
		} else {
			if(preobj == NULL) {
				n->next = obj;
				list->root = n;
				return 1;
			} else {
				preobj->next = n;
				n->next = obj;
				return 1;
			}
		}
	preobj = obj;
	obj = obj->next;

	}
	return 0;
};


/*
 * SLRemove removes a given object from a sorted list.  Sorted ordering
 * should be maintained.
 *
 * If the function succeeds, it returns 1.  Else, it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

int SLRemove(SortedListPtr list, void *newObj) {
	struct Node *obj = list->root, *preobj = NULL;
	while(obj->value != NULL) {
		if(list->comp (newObj , obj->value) == 0) {
			if(preobj == NULL) {
				list->root = list->root->next;
				free(obj);
			return 1;
			} else {
				preobj->next = obj->next;
				free(obj);
				return 1;
			}
		}
	obj = obj->next;
	}
	return 0;
};


/*
 * SLCreateIterator creates an iterator object that will allow the caller
 * to "walk" through the list from beginning to the end using SLNextItem.
 *
 * If the function succeeds, it returns a non-NULL SortedListIterT object.
 * Else, it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	SortedListIteratorPtr il = malloc(sizeof(struct SortedListIterator));
	il->ptr = list->root;
	return il;
};


/*
 * SLDestroyIterator destroys an iterator object that was created using
 * SLCreateIterator().  Note that this function should destroy the
 * iterator but should NOT affectt the original list used to create
 * the iterator in any way.
 *
 * You need to fill in this function as part of your implementation.
 */

void SLDestroyIterator(SortedListIteratorPtr iter) {
	free(iter);	
};


/*
 * SLNextItem returns the next object in the list encapsulated by the
 * given iterator.  It should return a NULL when the end of the list
 * has been reached.
 *
 * One complication you MUST consider/address is what happens if a
 * sorted list encapsulated within an iterator is modified while that
 * iterator is active.  For example, what if an iterator is "pointing"
 * to some object in the list as the next one to be returned but that
 * object is removed from the list using SLRemove() before SLNextItem()
 * is called.
 *
 * You need to fill in this function as part of your implementation.
 */

void *SLNextItem(SortedListIteratorPtr iter) {
	void *value = iter->ptr->value;
	iter->ptr = iter->ptr->next;
	return value;	
};

#endif
