/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	char **tokens;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {
	TokenizerT *token = malloc(sizeof(TokenizerT));
	token->tokens =  malloc(100*sizeof(char*));  // create 100 token buffer
	char *chararry =  calloc(100, sizeof(char)); // Creates a 100 character buffer and makes sure they are zero out
	int word = 0, arr = 0;
	char *temp = separators;
	char sep = ' ';
	char input = *ts;
	if(input == '\0') {
		free(token->tokens);
		free(chararry);
		free(token);
		return NULL;
	}
	while(input != '\0') {
		sep = *temp;
		while(sep != '\0') {
			if((input == sep) && (word == 0)) {
				temp = separators;
				break;
			}
			else if((input == sep) && (word>0)) {
				temp = separators;
				chararry = realloc(chararry, sizeof(char)*(word++));
				*(chararry+word) = '\0';
				word = 0;
				token->tokens[arr] = chararry;
				arr++;
				chararry = malloc(100*sizeof(char));
				break;
			}
			temp++;
		}
		if(sep == '\0') {
			temp = separators;
		}
		input = *(ts++);
	}
	token->tokens = realloc(token->tokens, sizeof(char*)*(arr++));
	token->tokens[arr] = NULL;
	return token;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {

  return NULL;
}

/*
 * printToken reconfigure the character string from
 *  TKGetNextToken and takes the escape value and convert them
 * to their Hex value in the form 0x?? and prints them
 */
void printToken(char *output) {
	char *il = output;
	char c = *il;
	while(c != '\0') {
		if(c == '\\'){
			c=*(il++);
			switch(c) {
				case 'n' : printf("[0x0a]");  
					break;
				case 'v' : printf("[0x0b]");
					break;
				case 'b' : printf("[0x08]");
					break;
				case 'r' : printf("[0x0d]");
					break;
				case 'f' : printf("[0x0c]");
					break;
				case 'a' : printf("[0x07]");
					break;
				DEFAULT : printf("%c",c);
			}
		} else {
			printf("%c", c);
		}
		il++;
		c=*il;
	}
	printf("\n");
}
/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	char list[] ="hello\nmate";
	char* points = list;
	printf("%s This is Arg1\n",argv[1]);
	printf("%s This is Arg2\n",argv[2]);
	char *pointer = argv[2];
	char c = ' ';
	while(c!='\0') {
		c = *pointer;
		pointer++;
		printf("%c\n", c);
	}
//	int x=0;
//	for(x; x<100; x++)
//	printf("%d.\ %c\\n",x,x);
  return 0;
}
