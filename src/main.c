/*
* Filename: main.c
* Author: Roland Vermiglio
* Created: Oct 2025
*
*
* Description:
* 	A cross platform command line interface and interpreter written in C
*	Supports built in math and utility commands, and a modular command dispatch
*	using structs and function pointers
*
* Usage:
* 	>help
*	>add 5 10
*   >clear
*	>exit
*
* Platform: 
* 	Supports Windows and Unix-like systems. 
*/



/* Example output:

>help

List Of Commands:
help- Shows list of commands
add <int> <int>- Computes the sum of two integers
printf("subtract <int> <int>- Computes the difference of two integers\n");
square <int>- Computes the value of the square of an integer 
exit- Exits command line

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "parser.h"
#include "usr.h"
#include "command.h"
#include "error.h"
#include "util.h"



int main(void){
	char command[50];

	command[0] = '\0';

	while(1){
		int commandIndex = -1;
		char *args[19];
		printf(">");
		fgets(command, sizeof(command), stdin);
		command[strcspn(command, "\n")] = '\0';

		//printf("%s\n", command);

		parseCommand(command, &commandIndex, args);

		//printf("command index: %d\n", commandIndex);

		int argCount = 0;
		while (args[argCount] != NULL){
    		argCount++;
		}

		if (commandIndex >= 0 && commandIndex < numOfCmds) {
    		commands[commandIndex].func(args, argCount);
		}

		if(strcmp(command, "exit") == 0){
			return 0;
		}
	}
}