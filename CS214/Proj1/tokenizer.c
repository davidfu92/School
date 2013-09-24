/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	char *token;
	struct TokenizerT_ *next;
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
	TokenizerT *tk = malloc(sizeof(TokenizerT));
	TokenizerT *t = tk;
	tk->token =  calloc(100, sizeof(char));  // create 100 token word  buffer
	int word = 0;
	char *temp = separators;
	char sep = ' ';
	char input = *ts;
	if(input == '\0') {
		free(tk->token);
		free(tk);
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
				t->token = realloc(t->token, sizeof(char)*(++word));
				t->token[word] = '\0';
				word = 0;
				TokenizerT *n = malloc(sizeof(TokenizerT));
				t->next = n;
				t = t->next;
				t->token = calloc(100, sizeof(char));
			break;
			}
			sep = *(++temp);
		}
		if(sep == '\0') {
			temp = separators;
			t->token[word] = input;
			word++;
		}
		input = *(++ts);
	}
	if((input == '\0') && (word != 0)) {
				t->token = realloc(t->token, sizeof(char)*(++word));
				t->token[word] = '\0';
	}
	t->next = NULL;
	return tk;
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
	if(tk->next != NULL) {
		printf("word %s", tk->token);
		return tk->token;
	}
	return NULL;
}

/*
 * printToken reconfigure the character string from
 *  TKGetNextToken and takes the escape value and convert them
 * to their Hex value in the form 0x?? and prints them
 */
void printToken(char *output) {
	char c = *output;
	while(c != '\0') {
		if(c == '\\'){
			c=*(++output);
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
				case '"' : printf("[0x22]");
					break;
				DEFAULT : printf("%c",c);
			}
		} else {
			printf("%c", c);
		}
		c=*(++output);
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
	TokenizerT *t = TKCreate(argv[1], argv[2]);
	TokenizerT *tt = t;
	int size = 0;
	while(TKGetNextToken(tt) != NULL) {
		printf("word %s\n",TKGetNextToken(tt));
		tt = tt->next;
	}
  return 0;
}
