//command.c

//Header definition foe all of the commands for the CLI program

#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "usr.h"
#include "error.h"
#include "util.h"

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


void help(char **args, int size);

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

void sum(char **args, int size);

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

void subtract(char **args, int size);

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

void square(char **args, int size);


/**
 * 
 * @brief "cube" Command
 * 
 * @details accepts only one argument and prints the cube of that number
 * 
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
 * 
 * 	**/

void cube(char **args, int size);

/**
 * 
 * @brief "exit" Command
 * 
 * @details Prints "Exiting Command line" and sleeps for 750 milliceconds
 * 
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
 * 
 * 	**/

void cmdexit(char **args, int size);


/**
 * 
 * @brief "clear" Command
 * 
 * @details calls the clearTerminal() function if there are zero arguments in the args array
 * 
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
 * 
 * 	**/

void clearConsole(char **args, int size);

/**
 * 
 * @brief "pow" Command
 * 
 * @details only takes 2 arguments, an integer base and an integer exponent, and returns the result when the base is raised to the power of that exponent
 * 
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
 * 
 * 	**/

void power(char **args, int size);

/**
 * @brief "history" command
 * 
 * @details prints the entire history of the current session
 * 
 * TODO: allow for users to enter a max number of lines
 * 
**/

void history(char **args, int size);


/**
 * 
 * @brief "err" Command
 * 
 * @details if the current user is a developer it throws the given error code, or if there is no arguments it just prints "err", otherwise it throws the error DEV_MODE_REQUIRED
 * 
 * @param a pointer to an array of strings that are command arguments, and an integer which is the size of the array
 * 
 * 	**/

void err(char **args, int size);


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
void enableDev(char **args, int size);


extern Command commands[];
extern int numOfCmds;

#endif



