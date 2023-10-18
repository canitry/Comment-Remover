#ifndef STATES_H
#define STATES_H
/* 
 * Header file for PA3
 * Author: Sue-Hyun Hong 
 */

/*
 * Complete the type definition for DFA states, you do not need an end state
 */
enum typestate {START, 
	CHAR, 
	CHAR_BSLSH,
	QUOTE, 
	QUOTE_BSLSH,
	CMNT,
	C_CMNT, 
	C_CMNT_STAR,
	LN_CMNT};

enum typestate startSt(int);
enum typestate charSt(int, int);
enum typestate charBslshSt(int);
enum typestate quoteSt(int, int);
enum typestate quoteBslshSt(int);
enum typestate cmntSt(int);
enum typestate cCmntSt(int);
enum typestate cCmntStarSt(int);
enum typestate lnCmntSt(int);
/*
 *  function prototypes for each state handler of the DFA
 *  Hint you will have to pass the single quote and double quote states
 *       the input plus the starting line number to print the error message
 *       for unterminated literals that see a newline before the ending quote
 *       all other states just need to be passed the input
 */

/*
 * global variable set if a state handler sees an error
 * 0 is no error
 * 1 is at least one error
 */
extern int saw_error;

#endif
