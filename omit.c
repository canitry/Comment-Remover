/*
 * CSE Programming assignment 3 
 * Author: Sue-Hyun Hong
 *
 * What this program does:
 *      remove c comments from a source file and write to stdout
 *      comments are replaced with a single space
 *      handles single and double quoted sequences
 *      all newlines are preserved
 *
 * error handling:
 *      prints starting line for unterminated comments or quote sequences
 *      to stderr
 *
 * return either:
 *      EXIT_SUCCESS if no errors
 *      EXIT_FAILURE if errors
 *      
 */

#include <stdio.h>
#include <stdlib.h>
#include "states.h"
#define CNT 1   /* start count lines in input at CNT */

int
main(void)
{
    int c;              /* input char  */
    int linecnt = CNT;  /* counts line in input */
    int startline = CNT;/* starting line number for comment/quote */

    enum typestate state = START;  /* initial state of DFA */

    /*
     * process char at a time until EOF
     */

        /* replace this comment with your main loop code */
	while ((c=getchar()) != EOF) {
		switch(state) {
		case START:
			state = startSt(c);
			startline=linecnt;
			break;
		case CHAR:
			state = charSt(c, startline);
			break;
		case CHAR_BSLSH:
			state = charBslshSt(c);
			break;
		case QUOTE:
			state = quoteSt(c, startline);
			break;
		case QUOTE_BSLSH:
			state = quoteBslshSt(c);
			break;
		case CMNT:
			state = cmntSt(c);
			break;
		case C_CMNT:
			state = cCmntSt(c);
			break;
		case C_CMNT_STAR:
			state = cCmntStarSt(c);
			break;
		case LN_CMNT:
			state = lnCmntSt(c);
			break;
		default:
			fprintf(stderr, "Error DFA state not handled\n");
			return EXIT_FAILURE;
		}
		
		if (c== '\n')
			linecnt++;
	}
    /*
     * All done. No explicit end state used here.
     * Check for error conditions based on the state we ended in
     */
	if (saw_error !=0){
		return EXIT_FAILURE;
	} else if ((state == CHAR)||(state == CHAR_BSLSH)){
		fprintf(stderr, "Error: line %d: unterminated quote(\')\n", startline);
		return EXIT_FAILURE;
	} else if ((state == QUOTE) || (state == QUOTE_BSLSH)){
		fprintf(stderr, "Error: line %d: unterminated quote(\")\n", startline);
		return EXIT_FAILURE;
	} else if ((state == C_CMNT) || (state == C_CMNT_STAR) || (state == LN_CMNT)){
		fprintf(stderr, "Error: line %d: unterminated comment\n", startline);
		return EXIT_FAILURE;
	} else {
		return EXIT_SUCCESS;
	}
}
