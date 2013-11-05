#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "Hashmap.c"
#include "sorted-list.h"

int main(int argc, char **argv) {	
	if(argc != 2){
		fprintf(stderr,"Error: invalid number of arguments\n");
		return -1;
	}
	Map tokens = hashmapCreate(7919);
	struct dirent* dir_file;
	DIR *dir = NULL;
	FILE *index = fopen(argv[1], "r");
	if(input != NULL) {
		char c = fgetc(input);
		char *w=calloc(100, sizeof(char));
		int spot = 0;
		int isW = 0;
		while(c != EOF) {
			if(isalpha(c) || isdigit(c) || (c == '.') || (c == '/')) {
				w[spot]= c;
				spot++;
				//printf("%c", c);
			} else {
				if(spot>0) {
					w = realloc(w, sizeof(char)*(++spot));
					w[spot] = '\0';
					spot =0;
					//printf("word: %s\n", w);
					hashmapInsert(tokens,argv[2],w,hash(w));
					w = calloc(100, sizeof(char));
				}
			}
			c = fgetc(input);
		}
		if(spot>0) {
			w = realloc(w, sizeof(char)*(++spot));
			w[spot] = '\0';
			spot =0;
			//printf("word: %s\n", w);
			if(strcmp(w,"list") == 0) {
				isW = 1;
			} else if(strcmp(w,"/list") == 0) {
				isW = 0;			
			} else if(atoi(w) == 0) {
				if(isW == 2) {
					
				} else if(isW == 1) {
					isW=2;
				}

			} else {

			}
		}
	} else {
		fprintf(stderr, "Erorr invalid FILE Input\n");
	}
	if(index != NULL)
		fclose(index);
	return 0;
}

