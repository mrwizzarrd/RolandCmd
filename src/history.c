#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"


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

CommandHistory *CreateCommandHistory(size_t initial_capacity){
	CommandHistory *history = malloc(sizeof(CommandHistory));

	if(!history){
		ThrowError(MEMORY_ALLOCATION_FAILED, "Allocation of Memory Failed");
		return NULL;
	}

	history->usage = 0;
	history->capacity = initial_capacity;
	history->history_data = malloc(initial_capacity * sizeof(char*));
	for(size_t i = 0; i < initial_capacity; i++){
		history->history_data[i] = malloc(50 * sizeof(char));
		if(!history->history_data[i]){
			ThrowError(MEMORY_ALLOCATION_FAILED, "Allocation of Command Buffer Failed");
		}
	}
	history->max_command_length = 50;
	return history;
}



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

void addHistory(CommandHistory *cmdHist, char *element){
	if(cmdHist->usage == cmdHist->capacity){
		cmdHist->capacity *= 2;
		void *temp = realloc(cmdHist->history_data, cmdHist->capacity * sizeof(char*));
		if(!temp){
			ThrowError(MEMORY_ALLOCATION_FAILED, "Rellocation of Memory Failed");
			return;
		}
		cmdHist->history_data = temp;
		for(size_t i = cmdHist->usage; i < cmdHist->capacity; i++){
			cmdHist->history_data[i] = malloc(cmdHist->max_command_length * sizeof(char));
		}
	}
	if(strlen(element) > cmdHist->max_command_length){
		cmdHist->max_command_length *= 2;
		for(size_t i = 0; i < cmdHist->capacity; i++){
			void *temp = realloc(cmdHist->history_data[i], cmdHist->max_command_length * sizeof(char));
			if(!temp){
				ThrowError(MEMORY_ALLOCATION_FAILED, "Reallocation of Command Buffer Failed");
				return;
			}
			cmdHist->history_data[i] = temp;
		}
	}
	strcpy(cmdHist->history_data[cmdHist->usage++], element);
//omg it would be so much easier to implement this in C++ with std::vector
}

CommandHistory *CmdHistory = NULL;

/**
 * @details initializes the command history object at runtime
**/
void InitHistory(void){
	CmdHistory = CreateCommandHistory(25);

	if(!CmdHistory){
		ThrowError(MEMORY_ALLOCATION_FAILED, "Failed to initialize command history");
	}
}
