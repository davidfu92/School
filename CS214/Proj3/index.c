#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "Hashmap.c"
#include "sorted-list.h"

int compareString(void *p1, void *p2)
{
	char *s1 = ((struct List*)p1)->word;
	char *s2 = ((struct List*)p2)->word;

	return strcmp(s1, s2);
}
void printToFile(FILE *output, Map tokens) {
	int s =0,five = 1;
//	SortedListPtr sortedlist = SLCreate(compareString);
	for(s; s<tokens->size; s++) {
		if(tokens->table[s].key != 0) {
			//SLInsert(sortedlist, tokens->table[s].rList);
						struct Record *r = (tokens->table[s].rList)->list;
						fprintf(output,"%s %s\n","<list> ", (tokens->table[s].rList)->word);
						while(r != NULL) {
						fprintf(output,"%s %d ", r->file,r->count);
						five++;
						r = r->next;
						if(five % 5 == 0) {
						fprintf(output,"\n%s\n","</list>");
						fprintf(output,"%s %s\n","<list> ",(tokens->table[s].rList)->word);
						}
						}
						fprintf(output,"\n%s\n","</list>");
		}
	}
/*	struct Node *n = sortedlist->root;
	while(n != NULL) {
		fprintf(output,"%s %s\n","<list> ", ((struct List*)(n->value))->word);
		struct Record *r = ((struct List*)(n->value))->list;
		while(r != NULL) {
			fprintf(output,"%s %d ", r->file,r->count);
			five++;
			r = r->next;
			if(five % 5 == 0) {
				fprintf(output,"%s\n","</list>");
				fprintf(output,"%s %s\n","<list> ",((struct List*)(n->value))->word);
			}
		}
		fprintf(output,"%s\n","</list>"); 
		n = n->next;
	} */

}
void openDir(DIR *dir,Map tokens,char *path) {
	struct dirent* dir_loop;
	FILE *allf;
	DIR *subdir;
	while ((dir_loop = readdir (dir)) != NULL) {
		if(strcmp(dir_loop->d_name, "..") != 0 && strcmp(dir_loop->d_name, ".") !=  0) {
			char *loc = calloc(100, sizeof(char));
			strcat(strcat(strcat(loc , path), "/"), dir_loop->d_name);
			//printf ("%s\n", loc);
			allf = fopen(loc, "r");
			subdir = opendir(loc);
			if(subdir != NULL){
				openDir(subdir, tokens,loc);
				closedir(subdir);
			} else if(allf != NULL) {
				char c = fgetc(allf);
				char *w=calloc(100, sizeof(char));
				int spot = 0;
				while(c != EOF) {
					if(isalpha(c) || isdigit(c)) {
						w[spot]= c;
						spot++;
						//printf("%c", c);
					} else {
						if(spot>0) {
							w = realloc(w, sizeof(char)*(++spot));
							w[spot] = '\0';
							spot =0;
							//printf("word: %s\n", w);
							hashmapInsert(tokens,loc,w,hash(w));
							w = calloc(100, sizeof(char));
						}
					}
					c = fgetc(allf);
				}
				if(spot>0) {
					w = realloc(w, sizeof(char)*(++spot));
					w[spot] = '\0';
					spot =0;
					printf("word: %s\n", w);
					hashmapInsert(tokens,loc,w,hash(w));
				}
			}
			if(allf != NULL)
				fclose(allf);
		}
	}
}
int main(int argc, char **argv) {	
	if(argc != 3){
		fprintf(stderr,"Error: invalid number of arguments\n");
		return -1;
	}
	Map tokens = hashmapCreate(7919);
	struct dirent* dir_file;
	DIR *dir = NULL;
	FILE *index = fopen(argv[1], "r");
	if(index != NULL) {
		printf("FILE Already exist do you want to overwrite it y/n: ");
		char ch;
		scanf("%c", &ch);
		if(ch == 'y') {
			index = fopen(argv[1], "w");
		} else {
			printf("You choose to not overwite file\n");
		}
	} else {
		index = fopen(argv[1], "w");
		rewind(index);
	}
	FILE *input = NULL;
	dir = opendir(argv[2]);
	input= fopen(argv[2], "r");
	if(dir != NULL) {
		openDir(dir, tokens,argv[2]);
		//	while ((dir_file = readdir (dir)) != NULL) {
		//		printf ("%s\n", dir_file->d_name);
		//	}
	} else if(input != NULL) {
		char c = fgetc(input);
		char *w=calloc(100, sizeof(char));
		int spot = 0;
		while(c != EOF) {
			if(isalpha(c) || isdigit(c)) {
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
			hashmapInsert(tokens,argv[2],w,hash(w));
		}
	} else {
		fprintf(stderr, "Erorr invalid FILE or DIRECTORY\n");
	}
	printToFile(index, tokens);
	if(index != NULL)
		fclose(index);
	if(input != NULL)
		fclose(input);
	if(dir != NULL)
		closedir(dir);
	//destroyHashmap(tokens);
	return 0;
}

