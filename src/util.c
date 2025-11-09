#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief creates a dynamic string array
 * 
 * @details allocates a lot of memory lol, I'll update these docs later probably
 * 
 * @param initialCapacity: initial array capacity
 * @param initialStringCapacity: initial string element capacity
 * 
*/
DynamicStringArray CreateDynamicArray(size_t initialCapacity, size_t initialStringCapacity){
	DynamicStringArray arr;

	arr.size = 0;
	arr.ArrayCapacity = initialCapacity;
	arr.maxStringLength = initialStringCapacity;

	arr.data = malloc(initialCapacity * sizeof(char*));

	for(size_t i = 0; i < initialCapacity; i++){
		arr.data[i] = calloc(initialStringCapacity, sizeof(char));
	}

	return arr;
}


/**
 * @brief clears new line buffer from scanf
 * 
 * @details reads and discards all characters in input stream until a newline or end of file (EOF) is found. This prevents leftover input from affecting subsequent reads
 * 
*/
void clearInputBuffer(){
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
*	@brief Clears console screen.
*
*	@details Moves cursor to top left and clears all text in terminal using ANSI escape codes.
*
*	@note Works on terminals that suppoer ANSI escape sequences.
**/
void clearTerminal(void){
	printf("\e[1;1H\e[2J");
}


/**
 * 
 * @brief Returns the number of arguments in an array of strings
 * 
 * @details until it has found the NULL terminator of the array it increments the 'count' variable by 1 for each element that isn't NULL
 * 
 * @param an array of strings (in the context of arguements)
 * 
 * @return the number of elements found before the function reached the NULL terminator
 * 
 * 	**/
int countArgs(char **args){
	int count = 0;
	while(args[count] != NULL){
		count++;
	}
	return count;
}