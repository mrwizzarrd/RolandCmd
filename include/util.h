#ifndef UTIL_H
#define UTIL_H

//#define _POSIX_C_SOURCE 199309L

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
	#include <windows.h>
	#define sleep_ms(ms) Sleep(ms)
#else
	#include <unistd.h>
	static inline void sleep_ms(int ms){
		struct timespec ts;
		ts.tv_sec = ms / 1000;
		ts.tv_nsec = (ms % 1000) * 1000000;
	    nanosleep(&ts, NULL);
	}
#endif


//time to refactor 25 functions of legacy code that uses static arrays
//fml
/** 
 * @typedef
 * @struct DynamicStringArray that has 3 properties:
 * size_t size: the current number of elements in the array
 * size_t maxStringLength: the max amount of characters in the string
 * size_t ArrayCapacity: The max elements in array
 * char **data: the actual data of the array
 *  
**/

typedef struct {
	size_t size;
	size_t maxStringLength;
	size_t ArrayCapacity;
	char **data;
} DynamicStringArray;


/**
 * @brief creates a dynamic string array
 * 
 * @details allocates a lot of memory lol, I'll update these docs later probably
 * 
 * @param initialCapacity
 * @param initialStringCapacity
 * 
*/
DynamicStringArray CreateDynamicArray(size_t initialCapacity, size_t initialStringCapacity);



/**
 * @brief clears new line buffer from scanf
 * 
 * @details reads and discards all characters in input stream until a newline or end of file (EOF) is found. This prevents leftover input from affecting subsequent reads
 * 
*/
void clearInputBuffer(void);

/**
*	@brief Clears console screen.
*
*	@details Moves cursor to top left and clears all text in terminal using ANSI escape codes.
*
*	@note Works on terminals that suppoer ANSI escape sequences.
**/
void clearTerminal(void);

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
int countArgs(char **args);

#endif