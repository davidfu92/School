#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "Hashmap.c"

void search() {
	while(1) {
		char *input = calloc(500, sizeof(char));
		printf("Enter Your Search: \n");
		scanf("%[^\n]", input);
		char c = *(input++);
		int first = 0;
		char *w = calloc(100, sizeof(char));
		int spot = 0;
		int type = 0;
		while(c != '\0') {
			printf("1");
			if(c != ' ') {
				w[spot]= c;
				spot++;
			} else {
				if(spot>0) {
					w = realloc(w, sizeof(char)*(++spot));
					w[spot] = '\0';
					printf("%s \n",w);
					spot = 0;
					if(first == 0 ) {
						first = 1;
						if(strcmp(w,"sa") == 0) {
							type = 1;
							continue;
						} else if(strcmp(w,"so") == 0) {
							printf("type2");
							type = 2;
							continue;
						}else if(strcmp(w,"q:") == 0) {
							exit(0);
						} else {
							printf("Wrong Input Format \n");
							break;
						}
						free(w);
					}
				}
			}
			c = *(input++);
		}
		if(spot>0) {
			w = realloc(w, sizeof(char)*(++spot));
			w[spot] = '\0';
			spot =0;
			printf("%s \n",w);
			free(w);
		}
		free(input);
		printf("why");
		break;
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
			if((!isdigit(c)) && (c != ' ') && (c != '<') && (c != '>') && (c != '\n')) {
				w[spot]= c;
				spot++;
				//printf("%c", c);
			} else {
				if(spot>0) {
					w = realloc(w, sizeof(char)*(++spot));
					w[spot] = '\0';
					spot =0;
					if(strcmp(w,"list") == 0) {
						next = 1;
						free(w);
					}
					if((next == 0) && (strcmp(w,"/list") != 0) && (strcmp(w,in) != 0)) {
						//		printf("word: %s file: %s\n", in,w);
						hashmapInsert(tokens,w,in,hash(in));
					} else if(next == 1) {
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
			printf("word: %s\n", w);
		}
	} else {
		fprintf(stderr, "Erorr invalid FILE Input\n");
	}
	if(index != NULL)
		fclose(index);
	int s =0;
	for(s; s<(tokens->size); s++) {
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
	}
	search();
	return 0;
}

