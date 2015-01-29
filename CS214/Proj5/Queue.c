#include "Queue.h"

Queue createQueue(char *cat) {
	Queue qu = calloc(1, sizeof(struct Queue));
	qu->cat = cat;
	qu->ord = NULL;
}
Order getOrder(Queue list) {
	if(list->ord == NULL) {
		return NULL;
	} else {
			Order o = list->ord;
			list->ord = o->next;
		return o;
	}
}
int insertOrder(Queue q, Order ord) {
	Order temp = q->ord;
	while(temp->next != NULL) {
		temp=temp->next;
	}
	temp->next = ord;
}