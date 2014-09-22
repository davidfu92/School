#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.c"
#include "Hashmap.c"
#include <pthread.h>

pthread_mutex_t locks[37];
pthread_t threads[37];

Map makeQueueList(char *categories) {
	Map queuelist = hashmapCreate(37);
	FILE *data = fopen(categories, "r");
	int spot = 0;
	char *w=calloc(30, sizeof(char));
	if(data != NULL) {
		char c = fgetc(data);
		while(c != EOF) {
			if(c != '\n') {
				w[spot]= c;
				spot++;
			} else {
				if(spot>0) {
					w = realloc(w, sizeof(char)*(++spot));
					w[spot] = '\0';
					spot = 0;
					printf("word: %s\n", w);
					hashmapInsert(queuelist, createQueue(categories),hash(categories));
				}
				w = calloc(30, sizeof(char));
			}
			c = fgetc(data);
		}
	} else {
		fprintf(stderr, "Error: Invalid Category File\n");
	}	
	if(spot>0) {
		w = realloc(w, sizeof(char)*(++spot));
		w[spot] = '\0';
		spot = 0;

		hashmapInsert(queuelist, createQueue(categories),hash(categories));
		printf("word: %s\n", w);
	}
	if(data != NULL)
		fclose(data);
	return queuelist;
}

void enterPeople(char *people) {
	int spot = 0;
	char *w=calloc(200, sizeof(char));
	FILE *data = fopen(people, "r");
	if(data != NULL) {
		char c = fgetc(data);
		while(c != EOF) {
			if((c != '\n') && (c != '|') && (c != '"')) {
				w[spot]= c;
				spot++;
			} else {
				if(spot>0) {
					w = realloc(w, sizeof(char)*(++spot));
					w[spot] = '\0';
					spot = 0;
					if(strcmp(w," ") != 0)
						printf("word: %s\n", w);
				}
				w = calloc(30, sizeof(char));
			}
			c = fgetc(data);
		}
	} else {
		fprintf(stderr, "Error: invalid Order File");
	}
}
void processOrder(struct Order *or) {

}

int main(int argc, char **argv) {	
	if(argc != 4) {
		fprintf(stderr,"Error: invalid number of arguments\n");
		return -1;
	}
	Map database;
	database = makeQueueList(argv[3]);
	enterPeople(argv[1]);
	processOrder(argv[2]);
	return 0;
}
