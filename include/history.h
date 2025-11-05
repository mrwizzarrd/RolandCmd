#ifndef HISTORY_H
#define HISTORY_H
#include <stddef.h>

/**
 * @typedef
 * @struct
 * 
 * @brief Defines the CommandHistory object
 * 
 * @details CommandHistory is a dynamic string array with properties:
 * usage- how many current elements are in the array
 * capacity- the max number of elements the array can hold
 * max_command_length- the maximum length of a string in the array
 * history_data- the actual array of data
 * 
**/

typedef struct{
	size_t capacity;
	size_t usage;
	size_t max_command_length;
	char **history_data;
} CommandHistory;


/**
 * 
 * @brief creates an instance of the CommandHistory object using dynamic memory
 * 
 * @param An initial size for the command
 * 
 * @return A Dynamic String array that can hold as many elements as the initial size allows for
 * 
 * @details creates a dynamic string array using memory allocation, using an 
 * initial input for the initial size of the array, will be implemented to show the command history  
 * 
**/

CommandHistory *CreateCommandHistory(size_t initial_capacity);



/**
 * 
 * @brief adds an element to the command history
 * 
 * @param The command history object and the element to be added
 * 
 * @details if the usage of the array (how many elements are in it) is equal to the capacity of the array,
 * more memory will be allocated for the array, same thing if the size of a command string
 * is bigger than the number of bytes allocated to that element, more memory will be allocated for the elements  
 * 
**/

void addHistory(CommandHistory *cmdHist, char *element);

extern CommandHistory *CmdHistory;


/**
 * @details initializes the command history object at runtime
**/
void InitHistory(void);

#endif