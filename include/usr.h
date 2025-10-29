#ifndef USR_H
#define USR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "error.h"


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


/**
 * 
 * @brief changes CurrentUser if login is successful
 * 
 * @details The function first takes a username as input, checks if the username exists, if it does it asks for a password:
 * If any of these fail the function calls ThrowError() with the INVALID_CREDENTIALS or INVALID_USER error codes
 * 
 * 	**/

int login();

#endif

