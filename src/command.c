//command.c

//all of the commands for the CLI program

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "error.h"
#include "util.h"
#include "usr.h"
#include "command.h"
#include "history.h"
#include "file.h"
 

char *helpPages[8] = {
	"------Page Guide------",
	"1- Help Command",
	"2- Math Commands",
	"3- Utilities",
	"4- File System Commands",
	"5- Fun Commands",
	"Run the command 'help <page number>' for more info",
	NULL
};

/**
 * 
 * @brief "help" Command
 * 
 * @details If there are no arguments, the command displays the different help pages, if there is a valid argument (the help page number)
 * the command displays the specific page requested
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * 	**/

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
				printf("pow <int> <int>- Computes the power of a base\n");
				printf("factorial <int>- Computes the factorial of a value\n");
				printf("fib <int>- Computes values of the fibonacci sqtuence up to a specific index\n");
				break;
			case 3:
				printf("exit- exits console\n");
				printf("clear- clears console\n");
				printf("history- prints the entire history of the session\n");
				break;
			case 4:
				printf("COMING SOON\n");
				break;
			case 5:
				printf("COMING SOON\n");
			default:
				ThrowError(INVALID_ARGUMENT, "");
		}

	} else if(args[1] == NULL){

		for(int i = 0; helpPages[i] != NULL; i++){
			printf("%s\n", helpPages[i]);
		} 
	} else{
			ThrowError(INVALID_SYNTAX, "");
		}
}


/**
 * 
 * @brief "add" Command
 * 
 * @details Takes all the valid arguments and prints the sum of all the numbers, accepts as many arguments as the program will allow
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * TODO: Make it accept floating point numbers
 * 
 * 	**/

void sum(char **args, int size){
	int sum = 0;

	printf("arg1: %s\n", args[0]);

	for(int i = 0; i < size; i++){
		sum += atoi(args[i]);
	}

	printf("%d\n", sum);
}


/**
 * 
 * @brief "subtract" command
 * 
 * @details accepts only 2 arguments, and returns the difference between the two
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * TODO: Make it accept floating point numbers
 * 
 * 	**/

void subtract(char **args, int size){
	int count = countArgs(args);
	if(count == 2){
		int difference = atoi(args[0]) - atoi(args[1]);
		printf("%d\n", difference);
	} else{
		ThrowError(INVALID_SYNTAX, "");
	}
}


/**
 * 
 * @brief "square" Command
 * 
 * @details accepts only one argument and prints the square of that number
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * TODO: Make it accept floating point numbers
 * 
 * 	**/

void square(char **args, int size){
	if(countArgs(args) == 1){
		int square = atoi(args[0]) * atoi(args[0]);
		printf("%d\n", square);
	} else{
		ThrowError(INVALID_SYNTAX, "");
	}
}


/**
 * 
 * @brief "cube" Command
 * 
 * @details accepts only one argument and prints the cube of that number
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * 	**/
void cube(char **args, int size){
	if(countArgs(args) == 1){
		int square = atoi(args[0]) * atoi(args[0]) * atoi(args[0]);
		printf("%d\n", square);
	} else{
		ThrowError(INVALID_SYNTAX, "");
	}
}

/**
 * 
 * @brief "factorial" Command
 * 
 * @details accepts only one argument and prints the factorial of that number
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * 	**/
void factorial(char **args, int size){
	if(countArgs(args) != 1){
		ThrowError(INVALID_SYNTAX, "");
	} else{
		int result = 1;
		int value = atoi(args[0]);

		for(int i = value; i > 1; i--){
			result *= i;
		}
		printf("%d! = %d\n", value, result);
	}
}

/**
 * 
 * @brief "fibonacci" Command
 * 
 * @details accepts only one argument and prints the numbers in the fibonacci sequence up to that index
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * 	**/

void fibonacci(char **args, int size){
	if(countArgs(args) == 1 && atoi(args[0])){
		int fibnm2 = 0; 
		printf("%d ", fibnm2);
		int fibnm1 = 1;
		printf("%d ", fibnm1);
		int fibn;

		for(int i = 2; i < atoi(args[0]) + 1; i++){
			fibn = fibnm1 + fibnm2;
			fibnm2 = fibnm1;
			fibnm1 = fibn;

			printf("%d ", fibn);

			if(i % 5 == 0){
				printf("\n");
			}

		}
	} else if(countArgs(args) != 1){
		ThrowError(INVALID_ARGUMENT, "fibonacci command only accepts one argument");
	} else if(!atoi(args[0])){
		ThrowError(INVALID_ARGUMENT, "fibonacci command only handles integer values");
	} else{
		ThrowError(INVALID_SYNTAX, "");
	}
}

/**
 * 
 * @brief "exit" Command
 * 
 * @details Prints "Exiting Command line" and sleeps for 750 milliceconds
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * 	**/

void cmdexit(char **args, int size){
	printf("Exiting Command Line");
	sleep_ms(750);
}


/**
 * 
 * @brief "clear" Command
 * 
 * @details calls the clearTerminal() function if there are zero arguments in the args array
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * 	**/

void clearConsole(char **args, int size){
	//printf("Test");
	if(countArgs(args) <= 0){
		clearTerminal();
	} else{
		ThrowError(INVALID_SYNTAX, "");
	}
}


/**
 * 
 * @brief "pow" Command
 * 
 * @details only takes 2 arguments, an integer base and an integer exponent, and returns the result when the base is raised to the power of that exponent
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array@param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
 * 
 * 	**/

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
		ThrowError(INVALID_SYNTAX, "");
	}
}

/**
 * @brief "history" command
 * 
 * @details prints the entire history of the current session
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * TODO: allow for users to enter a max number of lines
 * 
**/

void history(char **args, int size){
	if(countArgs(args) != 0){
		ThrowError(INVALID_SYNTAX, "");
	} else{
		for (size_t i = 0; i < CmdHistory->usage; i++){
			printf("%s\n", CmdHistory->history_data[i]);
		}
	}
}

/**
 * @brief "mkfile" command
 * 
 * @details makes a new file
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
**/

void MakeFile(char **args, int size){
	if(countArgs(args) != 1){
		ThrowError(INVALID_SYNTAX, "");
	} else{
		char *filename = args[0];
		int success = createFile(filename);

		switch(success){
		case -1:
			ThrowError(FILE_ERROR, "");
		case -2:
			ThrowError(FILE_EXISTS, "");
		default:
			printf("File %s created successfully\n", filename);
		}
	}

}

/**
 * @brief "rmfile" command
 * 
 * @details removes a file
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
**/

void RemoveFile(char **args, int size){
	if(countArgs(args) != 1){
		ThrowError(INVALID_ARGUMENT, "");
		return;
	}

	int success = deleteFile(args[0]);

	switch (success)
	{
	case -1:
		ThrowError(FILE_NOT_FOUND, "");
		break;
	case 0:
		ThrowError(FILE_ERROR, "");
	
	default:
		printf("File %s deleted successfuly\n");
		break;
	}

}

/**
 * @brief "appline" command
 * 
 * @details appends content to a new line of a file
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
**/

void WriteLine(char **args, int size){
	
}


/**
 * 
 * @brief "err" Command
 * 
 * @details if the current user is a developer it throws the given error code, or if there is no arguments it just prints "err", otherwise it throws the error DEV_MODE_REQUIRED
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * 	**/

void err(char **args, int size){
	if(CurrentUser.Dev == 1){
		int error = atoi(args[0]);

		if(countArgs(args) > 1){
			ThrowError(INVALID_SYNTAX, "");
		} else if(countArgs(args) == 0){
			ThrowError(CUSTOM_ERR, "err");
		} else{
			ThrowError(error, "");
		}
	} else{
		ThrowError(DEV_MODE_REQUIRED, "");
	}
}


/**
 * 
 * @brief "devmode" Command
 * 
 * @details if the login() function is sucessful it checks if that user has dev access and if not it throws a custom error with message "USER NOT A DEVELOPER"
 * 
 * @param args a pointer to an array of strings that are parsed command arguments
 * @param size an integer which is the size of the array
 * 
 * 
 * TODO: Check if user "loggedOut" is the current user and only prompt a login if it is
 * 	**/

void enableDev(char **args, int size){
	if(countArgs(args) > 0){
		ThrowError(INVALID_SYNTAX, "");
	} else{
		int loginSuccess = login();
		if(loginSuccess == 0){
			if(CurrentUser.Dev != 1){
				ThrowError(CUSTOM_ERR, "USER NOT A DEVELOPER");
			}
		}
	}
}


//char *commandNames[10] = {"help", "add", "subtract", "square", "exit", "clear", "cube", "pow", "err", "Terminator"};   Legacy Version .5 code
//void (*commandFuncs[10])(char **, int) = {help, sum, subtract, square, cmdexit, clearConsole, cube, power, err, arrayTerminator};


Command commands[14] = {
	{"help", help, 0},
	{"add", sum, 0},
	{"subtract", subtract, 0},
	{"square", square, 0},
	{"exit", cmdexit, 0},
	{"clear", clearConsole, 0},
	{"cube", cube, 0},
	{"pow", power, 0},
	{"factorial", factorial, 0},
	{"fib", fibonacci, 0},
	{"history", history, 0},
	{"mkfile", MakeFile, 0},
	{"devmode", enableDev, 0},
	{"err", err, 1},
};


int numOfCmds = sizeof(commands) / sizeof(commands[0]);