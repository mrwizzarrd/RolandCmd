#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "error.h"
#include "util.h"
#include "command.h"
#include "usr.h"



/**
 * 
 * @brief Checks of the command is a valid command
 * 
 * @details if the command string cmd matches any of the command names in the commands array, then the validCommand boolean integer is set to 1
 * 
 * @param a pointer to an array of characters which is the comand inputted into the console
 * 
 * @return Two Outcomes:
 * 	Returns 1 if the command is a valid command name
 * 	Returns 0 if it is not a valid command name
 * 
 * 	**/
int compareCommand(char *cmd);

/**
 * 
 * @brief searches for the command index of a cetrian command object in the commands array 
 * 
 * @details iterates through the array to find the name of the command and at what index it is being stored at 
 * 
 * @param the string cmd
 * 
 * @return two outcomes:
 * 	an integer that regerrs to the command index if the command was found
 * 	-1 if no command was found
 * 
 * 	**/

int getCmdIndex(char *cmd);

/**
 * 
 * @brief seperates the command from its arguments
 * 
 * @details tokenizes the command by seperating by the space "add 4 5", becomes "add", "4", "5"
 * 	it then seperates the first string in the tokenizes command array and the rest become the args array (using the pointer parameter args)
 * 	then the function checks if there is a Command object that matches the name the user typed and sets the value that *command references to that index if it is found, otherwise it sets it to -1
 * 
 * @param takes three parameters
 * a pointer to the command string
 * a pointer to the command index integer
 * a pointer to the array of strings for arguments
 * 
 * 
 * 	**/

void parseCommand(char *command, int *commandIndex, char **args);

#endif