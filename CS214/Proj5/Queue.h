#ifndef QUEUE_H
#define QUEUE_H
/** queue structure */
struct Order {
	char *name;
	int ID;
	double price;
	struct Order *next;
};
struct Queue {
	struct Order *ord;
	char *cat;
};
typedef struct Queue* Queue;
typedef struct Order* Order;
/** Creates a new queue of give category. */
Queue createQueue(char *cat);
/** Gets the first order in the queue. */
Order getOrder();
/** insert order to top of the queue */
int insertOrder(Queue q, Order ord);
#endif
