#include "sorted-list.h"

/*
 * This method creates a basic root node of the linklist
 * and store the compareFuncT in a pointer
 */

SortedListPtr SLCreate(CompareFuncT cf) {
	SortedListPtr sList = (SortedListPtr) malloc(sizeof(struct SortedList));		// creates base
	sList->comp = cf;																// save comparator
	sList->root = malloc(sizeof(struct Node));										// create node
	sList->root->value = NULL;
	sList->root->next = NULL;
	return sList;																	// return
};

/*
 * Loops throught the list and free all the nodes in the sorted list.
 * After freeing all the node in the list it also frees the sortedlist
 */
void SLDestroy(SortedListPtr list) {
	struct Node *temp = list->root;													// creates temp
	while(temp != NULL) {															// loop through list
		list->root = list->root->next;
		free(temp);																	// free node
		temp = list->root;
	}
	free(list);																		// free sorted list
};


/*
 * SLInsert inserts a given object into a sorted list, maintaining sorted
 * order of all objects in the list.  If the new object is equal to a subset
 * of existing objects in the list, then the subset can be kept in any
 * order.
 *
 * If the function succeeds, it returns 1.  Else, it returns 0.
 *
 * This fucntion runs in O(n) time, the operation must compare the current value with all the
 * values in the list before insertion. The worst case is that the value being insersted is the
 * largest value meaing there will be n comparasion where n is the size of the list
 * in the best case the value is the smallest and there will be only 1 comparasion
 */

int SLInsert(SortedListPtr list, void *newObj) {
	if(list->root->value == NULL) {													// if empty list put value in root
		list->root->value = newObj;
		return 1;
	}
	struct Node *n = malloc(sizeof(struct Node));
	n->value = newObj;
	struct Node *obj = list->root, *preobj = NULL;
	while(obj->value != NULL) {														// loop through list to compare
		if(list->comp (newObj , obj->value) > 0) {									// if new object is smaller
			if(obj->next == NULL) {
				obj->next = n;														// put it to the end if at the end
				return 1;
			} else if(list->comp (newObj , obj->next->value) <= 0){					// else if bigger or equal than next one
				n->next = obj->next;
				obj->next = n;														// place in between
				return 1;
			}
				
		} else {																	// else if greater than or equal to
			if(preobj == NULL) {
				n->next = obj;
				list->root = n;														// set at root if beginning of list
				return 1;
			} else {
				preobj->next = n;
				n->next = obj;														// put it after the pre-obj and before this obj
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
 * This function is also O(n) time because it must check all the values in the list until it finds
 * the right one, where best case is first object and worst case is last object.
 */

int SLRemove(SortedListPtr list, void *newObj) {
	struct Node *obj = list->root, *preobj = NULL;
	while(obj->value != NULL) {														// loop through list
		if(list->comp (newObj , obj->value) == 0) {									// checks if value are equal
			if(preobj == NULL) {
				list->root = list->root->next;
				free(obj);
			return 1;
			} else {																// make sure not to lose root if first obj
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
 * The Iterator simply creates an extra reference pointer to the sorted list,
 * it is like an outsider overlooking the list, so it doesn't get affected by
 * the changes in the list
 */

SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
	SortedListIteratorPtr il = malloc(sizeof(struct SortedListIterator));			// simply creates an Iterator
	il->ptr = list->root;
	return il;
};


/*
 * SLDestroyIterator destroys an iterator object that was created using
 * SLCreateIterator().  Note that this function should destroy the
 * iterator but should NOT affectt the original list used to create
 * the iterator in any way.
 *
 * It simply free the memory being use by the iterator which effectively
 * destroys it
 */

void SLDestroyIterator(SortedListIteratorPtr iter) {
	free(iter);																		// frees the Iterator
};


/*
 * SLNextItem returns the next object in the list encapsulated by the
 * given iterator.  It should return a NULL when the end of the list
 * has been reached.
 *
 * Using an oversight pointer it merely points to the current element
 * when elements are added it simply relinks, as to when the value right after
 * is removed, its next value still points
 */

void *SLNextItem(SortedListIteratorPtr iter) {
	void *value = iter->ptr->next->value;											// returns next value
	return value;	
};
