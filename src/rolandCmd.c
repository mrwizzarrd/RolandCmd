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


//=============================================================================
//  Utility Functions (soon to be util.c and util.h)
//=============================================================================

/**
 * @brief clears new line buffer from scanf
 * 
 * @details reads and discards all characters in input stream until a newline or end of file (EOF) is found. This prevents leftover input from affecting subsequent reads
 * 
*/
void clearInputBuffer(void){
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
	return count;
}
//=============================================================================
//  ERROR HANDLING (Soon to be in err.c and err.h)
//=============================================================================


/**
 * 
 * @typedef ErrorCode
 * @enum ErrorCode
 * 
 * 
 * @brief Links an error name to a specific value for readability
 * 
 * 
 * @details Each error type is grouped into categories:
 * 	-100s: Invalid input errors
 * 	-200s: Arithmatic Errors
 * 	-300s: Type Errors
 *  -400s: User Errors
 * 	-500s: Memory and Array Errors
 *  -600s: Access and Permission Errors
 * 	-1000+: Custom or undefined errors
 * 
 * 
**/
typedef enum ErrorCode{

	/** 
	 * @brief Invalid argument
	 * @details Used when a function receives an invalid parameter or unexpected input value.
	 */


	INVALID_ARGUMENT = 101,


	/** 
	 * @brief Invalid command
	 * @details Triggered when the user enters an unsupported or unknown command.
	 */


	INVALID_COMMAND = 102,


	/** 
	 * @brief Invalid syntax
	 * @details Used when a function receives an invalid parameter or unexpected input value.
	 */


	INVALID_SYNTAX = 103,


	/** 
	 * @brief Invalid credentials
	 * @details Used when authentication fails due to incorrect login information.
	 */


	INVALID_CREDENTIALS = 104,

	/** 
	 * @brief Division by zero error
	 * @details Triggers when a division by zero will occur
	 */


	DIVIDE_BY_ZERO = 201,

	/**
	 * @brief Type mismatch
	 * @details Indecates operation recieved incompatible data types 
	**/


	TYPE_MISMATCH = 301,


	/**
	 * @brief User not found
	 * @details Used an inputted username is not found in system 
	**/


	USER_NOT_FOUND = 401,


	/**
	 * @brief Array Out Of Bounds
	 * @details Thrown when accessing memory outside of array bounds
	**/


	ARRAY_OUT_OF_BOUNDS = 501,


	/**
	 * @brief Dev Mode Required
	 * @details triggered when current user tries to run a command (like 'err') that requires dev mode
	**/


	DEV_MODE_REQUIRED = 621,


	/**
	 * @brief Custom Error
	 * @details Thrown when it's a one time possibility, uses the custom error message input
	**/


	CUSTOM_ERR = 1023,

} ErrorCode;

/**
 * 
 * @brief Displays an error message to the console if an error is thrown
 * 
 * @details The function takes an error code and compares it to a code defined in the 'ErrorCode' enum, and displays a message depending on which error it is
 * 
 * @param an ErrorCode and a string for a custom error message
 * 
 * @note if CUSTOM_ERR is thown the CustomErrMsg argument cannot be empty, otherwise it is fine to leave it as an empty string
 * 
 * 	**/
void ThrowError(ErrorCode err, char *CustomErrMsg){
	int customMsg = 0;
	if(strlen(CustomErrMsg) > 0){
		customMsg = 1;
	}
	switch(err){
	case INVALID_ARGUMENT:
		printf("ERROR: Invalid Argument\n");
		if(customMsg){
			printf("Additional info:\n\t%s\n", CustomErrMsg);
		}
		break;
	case INVALID_COMMAND:
		printf("ERROR: Invalid Command\n");
		if(customMsg){
			printf("Additional info:\n\t%s\n", CustomErrMsg);
		}
		break;
	case INVALID_SYNTAX:
		printf("ERROR: Invalid Command Syntax\n");
		if(customMsg){
			printf("Additional info:\n\t%s\n", CustomErrMsg);
		}
		break;
	case INVALID_CREDENTIALS:
		printf("ERROR: INVALID LOGIN CREDENTIALS\n");
		if(customMsg){
			printf("Additional info:\n\t%s\n", CustomErrMsg);
		}
		break;
	case DIVIDE_BY_ZERO:
		printf("ERROR: Cannot divide by zero\n");
		if(customMsg){
			printf("Additional info:\n\t%s\n", CustomErrMsg);
		}
		break;
	case TYPE_MISMATCH:
		printf("ERROR: Type mismatch\n");
		if(customMsg){
			printf("Additional info:\n\t%s\n", CustomErrMsg);
		}
		break;
	case ARRAY_OUT_OF_BOUNDS:
		printf("ERROR: Array out of Bounds\n");
		if(customMsg){
			printf("Additional info:\n\t%s\n", CustomErrMsg);
		}
		break;
	case DEV_MODE_REQUIRED:
		printf("ERROR: Developer mode not enabled, please enable developer mode\n");
		if(customMsg){
			printf("Additional info:\n\t%s\n", CustomErrMsg);
		}
		break;
	case CUSTOM_ERR:
		if(customMsg){
			printf("ERROR: %s\n", CustomErrMsg);
		} else{
			ThrowError(CUSTOM_ERR, "CUSTOM ERROR HANDLER MISSING ERROR MESSAGE\n");
		}
		break;
	default:
		printf("ERROR: THROWN ERROR NOT FOUND\n");
	}
}

//=============================================================================
//  USER HANDLING (soon to be usr.c and usr.h)
//=============================================================================



/**
 * @typedef
 * @struct
 * 
 * @brief Defines Data Components of a user
 * 
 * @details The components are
 * Username: a string of characters that acts as tag that is specific to that user for login
 * Password: A string of characters used to unlock the user account
 * Dev: a boolean integer that referrs to access to certian commands 
 * Admin: a boolean integer that refers to system admin commands **CURRENTLY NO IMPLEMENTATIONS, THINKING ABOUT POSSIBLE FUTURE IMPLEMTNETATIONS**
 * 
 * TODO: List users in a file instead of source code
 * 
 * 
 * The default user is: loggedOut, which has no password, and is not a dev nor an admin
 * 
**/
typedef struct user{
	char username[10];
	char password[20];
	int Dev;
	int admin;
} user;

user Users[3] = {
	{"loggedOut", "", 0, 0},
	{"rverm", "testPassword", 1, 1},
	{"eli", "test123", 0, 1}
};

user CurrentUser = {"loggedOut", "", 0, 0};

int userNum = 2;


/**
 * 
 * @brief changes CurrentUser if login is successful
 * 
 * @details The function first takes a username as input, checks if the username exists, if it does it asks for a password:
 * If any of these fail the function calls ThrowError() with the INVALID_CREDENTIALS or INVALID_USER error codes
 * 
 * 	**/

int login(){
	printf("USERNAME: ");
	char username[15];
	scanf("%s", username);
	clearInputBuffer();
	for(int i = 0; i < userNum; i++){
		if(strcmp(username, Users[i].username) == 0){
			char password[20];
			printf("Enter password for user %s: ", username);
			scanf("%s", password);
			clearInputBuffer();
			if(strcmp(password, Users[i].password) == 0){
				strcpy(CurrentUser.username, Users[i].username);
				strcpy(CurrentUser.password, Users[i].password);
				CurrentUser.Dev = Users[i].Dev;
				return 0;
			} else{
				ThrowError(INVALID_CREDENTIALS, "");
				return -1;
			}
		}
	}
	ThrowError(USER_NOT_FOUND, "");
	return -1;
}

//=============================================================================
//  Command Implementations (soon to be command.h and command.c) 
//=============================================================================


/**
 * @typedef
 * @struct
 * 
 * @brief Defines Data Components of a Command
 * 
 * @details The components are
 * name: The name of the Command (Also what the user types on the interface)
 * *func: A pointer to the function that executes the code for the command
 * requiresDev: a boolean integer whose value represents if the command requires the durrent user to have DevMode access 
 * 
 * Each Command is then later stored in an array for easy access
 * 
**/
typedef struct Command{
	const char *name;
	void (*func)(char ** args, int size);
	const int requiresDev;
} Command;


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

//=============================================================================
//  Command Parsing (soon to be parser.h and parser.c) 
//=============================================================================

/**
 * TODO: Document this section on Sunday 10/26
**/

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

int getCmdIndex(char *cmd){
	for(int i = 0; i < numOfCmds; i++){
		if(strcmp(commands[i].name, cmd) == 0){
			return i;
		}
	}
	return -1;
}

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

	int arg_i = 0;
	for (int j = 1; commandParsed[j] != NULL; j++) {
	    args[arg_i++] = commandParsed[j];
	}
	args[arg_i] = NULL;

	if (commandParsed[0] == NULL) {
	    *commandIndex = -1;
	    return;
	}

	if(compareCommand(commandParsed[0]) != 1){
		ThrowError(INVALID_COMMAND, "");
		*commandIndex = -1;	
	} 	else{
		*commandIndex = getCmdIndex(commandParsed[0]);
	}
}



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