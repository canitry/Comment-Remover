/*
 * State handler routines for PA
 * one function for each state of the DFA
 *
 * Author: Sue-hyun Hong 
 */

#include <stdio.h>
#include "states.h"

/*
 * global flag set by state handlers if they see an error
 * 0 is no error
 * 1 is at least 1 error
 */
int saw_error = 0;


/*  replace this comment with your state handling functions below */
enum typestate startSt(int charInt){
	enum typestate result;

	switch(charInt){
	case '/':
		 result = CMNT;
		 break;
	case '\'':
		printf("%c", charInt);
		result = CHAR;
		break;
	case '\"':
		printf("%c", charInt);
		result = QUOTE;
		break;
	default:
		printf("%c", charInt);
		result = START;
		break;
	}

	return result;
}

enum typestate charSt(int charInt, int startline){
	printf("%c", charInt);
	switch(charInt){
	case '\n':
		fprintf(stderr, "Error: line %d: unterminated quote(\')\n", startline);
		saw_error=1;
		return START;
	case '\\':
		return CHAR_BSLSH;
	case '\'':
		return START;
	default:
		return CHAR;
	}
}

enum typestate charBslshSt(int charInt){
	printf("%c", charInt);
	return CHAR;
	//any special meaning of any char following / is ignored (including backslash and single quote)
}

enum typestate quoteSt(int charInt, int startline){
	printf("%c", charInt);
	switch(charInt){
	case '\n':
		fprintf(stderr, "Error: line %d: unterminated quote(\")\n", startline);
		saw_error=1;
		return START;
	case '\\':
		return QUOTE_BSLSH;
	case '"':
		return START;
	default:
		return QUOTE;
	}
}

enum typestate quoteBslshSt(int charInt){
	printf("%c", charInt);
	return QUOTE;
}

enum typestate cmntSt(int charInt){
	switch(charInt){
	case '*':
		printf(" ");
		return C_CMNT;
	case '/':
		printf(" ");
		return LN_CMNT;
	case '\"':
		printf("/\"");
		return QUOTE;
	case '\'':
		printf("/\'");
		return CHAR;
	default:
		printf("/%c", charInt);
		return START;
	}
}

enum typestate cCmntSt(int charInt){
	switch(charInt){
	case '\n':
		printf("\n");
		return C_CMNT;
	case '*':
		return C_CMNT_STAR;
	default:
		return C_CMNT;
	}
}

enum typestate cCmntStarSt(int charInt){
	switch(charInt){
	case '\n':
		printf("\n");
		return C_CMNT;
	case '*':
		return C_CMNT_STAR;
	case '/':
		return START;
	default:
		return C_CMNT;
	}
}

enum typestate lnCmntSt(int charInt){
	switch(charInt){
	case '\n':
		printf("\n");
		return START;
	default:
		return LN_CMNT;
	}
}
