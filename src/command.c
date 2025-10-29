//command.c

//all of the commands for the CLI program

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


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

/**
 * 
 * @brief "help" Command
 * 
 * @details If there are no arguments, the command displays the different help pages, if there is a valid argument (the help page number)
 * the command displays the specific page requested
 * 
 * @param a pointer to an array of strings that are parsed command arguments, and an integer which is the size of the array
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
			ThrowError(INVALID_SYNTAX, "");
		}
}


/**
 * 
 * @brief "add" Command
 * 
 * @details Takes all the valid arguments and prints the sum of all the numbers, accepts as many arguments as the program will allow
 * 
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
 * 
 * TODO: Make it accept floating point numbers
 * 
 * 	**/

void sum(char **args, int size){
	int sum = 0;

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
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
 * 
 * TODO: Make it accept floating point numbers
 * 
 * 	**/

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
		ThrowError(INVALID_SYNTAX, "");
	}
}


/**
 * 
 * @brief "square" Command
 * 
 * @details accepts only one argument and prints the square of that number
 * 
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
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
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
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
 * @brief "exit" Command
 * 
 * @details Prints "Exiting Command line" and sleeps for 750 milliceconds
 * 
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
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
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
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
 * 
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
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
 * 
 * @brief "err" Command
 * 
 * @details if the current user is a developer it throws the given error code, or if there is no arguments it just prints "err", otherwise it throws the error DEV_MODE_REQUIRED
 * 
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
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
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
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


Command commands[10] = {
	{"help", help, 0},
	{"add", sum, 0},
	{"subtract", subtract, 0},
	{"square", square, 0},
	{"exit", cmdexit, 0},
	{"clear", clearConsole, 0},
	{"cube", cube, 0},
	{"pow", power, 0},
	{"devmode", enableDev, 0},
	{"err", err, 1},
};


int numOfCmds = sizeof(commands) / sizeof(commands[0]);