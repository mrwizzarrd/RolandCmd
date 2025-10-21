/*
* Filename: rolandCalc.c
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




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



/* Example output:

>help

List Of Commands:
help- Shows list of commands
add <int> <int>- Computes the sum of two integers
printf("subtract <int> <int>- Computes the difference of two integers\n");
square <int>- Computes the value of the square of an integer 
exit- Exits command line

*/

#ifdef _Win32
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



int devMode = 0;

//Binds command names to their respective function
typedef struct Command{
	const char *name;
	void (*func)(char ** args, int size);
	const int requiresDev;
} Command;

//=============================================================================
//  Utility Functions
//=============================================================================

void clearTerminal(void){
	printf("\e[1;1H\e[2J");
}

int countArgs(char **args){
	int count = 0;
	while(args[count] != NULL){
		count++;
	}
	return count;
}


/*
ERROR CODES
	
	-100 Errors: Invalids
		INVALID ARGUMENT- -101
		INVALID COMMAND- -102

	-200 Errors: Arithmatic Errors

	-300 Errors: Type Errors

	-400 Errors: Array Errors

	-500 Errors: Other


*/
void ThrowError(int errorCode){
	//coming soon

}



//=============================================================================
//  Command Implementations
//=============================================================================

char *helpPages[12] = {
	"------Page Guide------",
	"1- Help Command",
	"2- Math Commands",
	"3- Utilities",
	"4- COMING SOON (maybe)",
	"5- COMING SOON (maybe)",
	"6- COMING SOON (maybe)",
	"7- COMING SOON (maybe)",
	"8- COMING SOON (maybe)",
	"9- COMING SOON (maybe)",
	"10- COMING SOON (maybe)",
	"Run the command 'help <page number>' for more info"
};


void help(char **args, int size){
	if(args[0] != NULL && args[1] == NULL){
		int page = atoi(args[0]);
		switch(page){
			case 1:
				printf("help <int>- Shows list of commands on a certian page\n");
				printf("help- Shows complete list of commands\n");
				break;
			case 2:
				printf("add <int> <int>- Computes the sum of two integers\n");
				printf("subtract <int> <int>- Computes the difference of two integers\n");
				printf("square <int>- Computes the value of the square of an integer \n");
				printf("cube <int>- Computes the value of the cube of an integer \n");
				printf("pow <int> <int>- computes the power of a base\n");
				break;
			case 3:
				printf("exit- exits console\n");
				printf("clear- clears console\n");
				break;
			default:
				printf("Invalid Argument\n");
		}

	} else if(args[0] == NULL){

		for(int i = 0; helpPages[i] != NULL; i++){
			printf("%s\n", helpPages[i]);
		} 
	} else{
			printf("Invalid Command Syntax");
		}
}

void sum(char **args, int size){
	int sum = 0;

	for(int i = 0; i < size; i++){
		sum += atoi(args[i]);
	}

	printf("%d\n", sum);
}

void subtract(char **args, int size){
	int difference = atoi(args[0]);
	int count = 1;
	while(args[count] != NULL){
		difference -= atoi(args[count]);
		count++;
	}
	if(count == 2){
		printf("%d\n", difference);
	} else{
		printf("Invalid Command Syntax!\n");
	}
}

void square(char **args, int size){
	if(countArgs(args) == 1){
		int square = atoi(args[0]) * atoi(args[0]);
		printf("%d\n", square);
	} else{
		printf("Invalid Command Syntax!\n");
	}
}

void cube(char **args, int size){
	if(countArgs(args) == 1){
		int square = atoi(args[0]) * atoi(args[0]) * atoi(args[0]);
		printf("%d\n", square);
	} else{
		printf("Invalid Command Syntax!\n");
	}
}


void cmdexit(char **args, int size){
	printf("Exiting Command Line");
	sleep_ms(750);
}

void clearConsole(char **args, int size){
	printf("Test");
	if(countArgs(args) <= 0){
		clearTerminal();
	} else{
		printf("Invalid Command Syntax!\n");
	}
}

void power(char **args, int size){
	int base = atoi(args[0]);
	int exponent = atoi(args[1]);
	int result = 1;
	int count = 1;
	while(args[count] != NULL){
		count++;
	}
	if(count == 2){
		for(int i = 0; i < exponent; i++){
			result = result * base;
		}
		printf("%d\n", result);
	} else{
		printf("Invalid Command Syntax!\n");
	}
}

void err(char **args, int size){}

//char *commandNames[10] = {"help", "add", "subtract", "square", "exit", "clear", "cube", "pow", "err", "Terminator"};   Legacy Version 1 code
//void (*commandFuncs[10])(char **, int) = {help, sum, subtract, square, cmdexit, clearConsole, cube, power, err, arrayTerminator};

Command commands[9] = {
	{"help", help, 0},
	{"add", sum, 0},
	{"subtract", subtract, 0},
	{"square", square, 0},
	{"exit", cmdexit, 0},
	{"clear", clearConsole, 0},
	{"cube", cube, 0},
	{"pow", power, 0},
	{"err", err, 1},
};


int numOfCmds = sizeof(commands) / sizeof(commands[0]);

//-------Command Utility Functions--------------------------------------------------------------------

int compareCommand(char *cmd){
	int validCommand = 0;
	for(int i = 0; i < numOfCmds; i++){
		//printf("%s : %s\n", cmd, commandNames[i]);
		if(strcmp(cmd, commands[i].name) == 0){
			validCommand = 1;
			return validCommand;
		}
	}
	return validCommand;
}

int getCmdIndex(char *cmd){
	int index = 0;

	while(strcmp(commands[index].name, cmd) != 0){
        index++;
	}
	return index;
}

void parseCommand(char *command, int *commandIndex, char **args){
	char *commandParsed[20];
	char *token = strtok(command, " ");

	int index = 0;
	while(token != NULL && 20 > index){
		commandParsed[index] = token;
		token = strtok(NULL, " ");
		index++;
	}
	commandParsed[index] = NULL;

	//printf("%s\n", commandParsed[0]);

	for (int j = 1; commandParsed[j] != NULL; j++) {
        args[j - 1] = commandParsed[j];
    }

    args[index - 1] = NULL;

	if(compareCommand(commandParsed[0]) != 1){
		printf("Invalid Command! For Help Input 'help'\n");
		*commandIndex = getCmdIndex("err");
	} else{
		*commandIndex = getCmdIndex(commandParsed[0]);
	}

}



int main(void){
	char command[50];

	command[0] = '\0';

	while(1){
		int commandIndex;
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

		commands[commandIndex].func(args, argCount);

		if(strcmp(command, "exit") == 0){
			return 0;
		}
	}
}