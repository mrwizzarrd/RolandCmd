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
 * @brief adds element to string array
 * 
 * @details if the array is full it reallocates the array, doubling the memory usage, 
 * if there's a sting larger than the max string allowed it also reallocates all elements to have that much memory 
 * 
 * @param arr:
 * @param element:
 * 
 * @return Status code: -3: Memory Error 0: Success 
**/

int AddString(DynamicStringArray* arr, char* element){
	if(arr->ArrayCapacity == arr->size){
		arr->ArrayCapacity *= 2;
		char **temp = realloc(arr->data, arr->ArrayCapacity * sizeof(char*));

		if(!temp){
			return -3;
		}

		arr->data = temp;

		for(size_t i = arr->size; i < arr->ArrayCapacity; i++){
			arr->data[i] = NULL;
		}
	}

	if(strlen(element) >= arr->maxStringLength){
		arr->maxStringLength *= 2;
		for(size_t i = 0; i < arr->ArrayCapacity; i++){

			char *newStr = realloc(arr->data[i], arr->maxStringLength * sizeof(char));
			arr->data[i] = newStr;

			if(!newStr){
				return -3;
			}
		}
	}
	arr->data[arr->size] = malloc(arr->maxStringLength);
    if(!arr->data[arr->size]){
		return -3;
	}
	
	strcpy(arr->data[arr->size], element);
	arr->size++;
    arr->data[arr->size] = NULL;

	return 0;
}

/**
 * @brief frees the array
 * 
 * @details frees every element and the array to the system's memory
 * 
 * @param arr: DynamicStringArray object to be freed
 *  
**/

void FreeStringArray(DynamicStringArray* arr){
	for(size_t i = 0; i < arr->ArrayCapacity; i++){
		free(arr->data[i]);
	}
	free(arr->data);
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

	//printf("Args FOUND: %d\n", count);
	return count;
}