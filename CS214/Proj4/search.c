#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "Hashmap.c"

void search(Map tokens) {
	while(1) {
		struct List *output = calloc(1, sizeof(struct List));
		output->list = calloc(1, sizeof(struct FileName));
		char *input = calloc(500, sizeof(char));
		printf("Enter Your Search: \n");
		fgets(input, 500, stdin);
		char *temp = input;
		char c = *(temp++);
		int first = 0;
		char *w = calloc(100, sizeof(char));
		int spot = 0;
		int type = 0;
		while(c != '\0') {
			//printf("1");
			if((c != ' ') && (c != '\n')) {
				w[spot]= c;
				spot++;
			} else {
				if(spot>0) {
					w = realloc(w, sizeof(char)*(++spot));
					w[spot] = '\0';
					//printf("%s \n",w);
					spot = 0;
					if(first == 0 ) {
						first = 1;
						if(strcmp(w,"sa") == 0) {
							type = 1;
							continue;
						} else if(strcmp(w,"so") == 0) {
							type = 2;
							continue;
						}else if(strcmp(w,"q:") == 0) {
							exit(0);
						} else {
							printf("Wrong Input Format \n");
							break;
						}
						free(w);
					} else if(first == 1) {
						first = 2;
						struct HElement *he = hashmapGet(tokens,hash(w),w);
						if(he != NULL)
							output->list = he->nList;
						else
							output->list = NULL;

					} else {
						struct HElement *he = hashmapGet(tokens,hash(w),w);
						struct FileName *temp =output->list;
						if(type == 1) {
							if(he != NULL)
								output->list = and(temp,he->nList);
							else
								output->list = and(temp,NULL);
						} else if(type == 2) {
							if(he != NULL)
								output->list = or(temp,he->nList);
							else
								output->list = or(temp,NULL);
						}
					}
					free(w);
					w = calloc(100, sizeof(char));
				}
			}
			c = *(temp++);
		}
		if(spot>0) {
			w = realloc(w, sizeof(char)*(++spot));
			w[spot] = '\0';
			spot = 0;
			printf("%s \n",w);
			if(first == 0 ) {
				first = 1;
				if(strcmp(w,"sa") == 0) {
					type = 1;
					printf("No Search Terms \n");
					continue;
				} else if(strcmp(w,"so") == 0) {
					type = 2;
					printf("No Search Terms \n");
					continue;
				}else if(strcmp(w,"q:") == 0) {
					exit(0);
				} else {
					printf("Wrong Input Format \n");
				}
				free(w);
			} else if(first == 1) {
				first = 2;
				struct HElement *he = hashmapGet(tokens,hash(w),w);
				if(he != NULL)
					output->list = he->nList;
				else
					output->list = NULL;	

			} else {
				struct HElement *he = hashmapGet(tokens,hash(w),w);
				struct FileName *temp =output->list;
				if(type == 1) {
					if(he != NULL)
						output->list = and(temp,he->nList);
					else
						output->list = and(temp,NULL);
				} else if(type == 2) {
					if(he != NULL)
						output->list = or(temp,he->nList);
					else	
						output->list = or(temp,NULL);
				}
			}
		}
		struct FileName *fn=output->list;
		if(fn != NULL)
			while(fn->name != NULL) {
				if(fn != NULL)
				printf("File : %s\n",fn->name);
				fn = fn->next;
			}
		free(input);
	}
}
int main(int argc, char **argv) {	
	if(argc != 2){
		fprintf(stderr,"Error: invalid number of arguments\n");
		return -1;
	}
	Map tokens = hashmapCreate(7919);
	FILE *index = fopen(argv[1], "r");
	if(index != NULL) {
		char c = fgetc(index);
		char *w=calloc(30, sizeof(char));
		int spot = 0;
		int next = 0;
		char *in;
		while(c != EOF) {
			if((c != ' ') && (c != '<') && (c != '>') && (c != '\n')) {
				w[spot]= c;
				spot++;
				//printf("%c", c);
			} else {
				if(spot>0) {
					w = realloc(w, sizeof(char)*(++spot));
					w[spot] = '\0';
					spot = 0;
					if(strcmp(w,"list") == 0) {
						next = 1;
						free(w);
					}
					if((next == 0) && (strcmp(w,"/list") != 0) && (strcmp(w,in) != 0)) {
						//printf("word: %s file: %s\n", in,w);
						if(atoi(w) == 0)
							hashmapInsert(tokens,w,in,hash(in));
					} else if(next == 1){
						in = w;
						next = 0;
					}
					if(strcmp(w,"/list") == 0)
						free(w);	
					//free(w);
					w = calloc(30, sizeof(char));
				}
			}
			c = fgetc(index);
		}
		if(spot>0) {
			w = realloc(w, sizeof(char)*(++spot));
			w[spot] = '\0';
			spot =0;
			//printf("word: %s\n", w);
		}
	} else {
		fprintf(stderr, "Erorr invalid FILE Input\n");
		return -1;
	}
	if(index != NULL)
		fclose(index);
	int s =0;
/*	for(s; s<(tokens->size); s++) {
		if(tokens->table[s].key != 0) {
			if(tokens->table[s].nList != NULL) {
				struct FileName *f = tokens->table[s].nList;
				printf("Word: %s ", tokens->table[s].word);
				while(f->next != NULL) {
					printf("File: %s,", f->name);
					f = f->next;
				}
				printf("\n");
			}
		}
	} */
	search(tokens);
	return 0;
}

