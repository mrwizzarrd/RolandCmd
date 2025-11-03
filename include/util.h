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