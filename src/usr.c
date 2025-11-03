#include "usr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

user Users[3] = {
	{"loggedOut", "", 0, 0},
	{"rverm", "testPassword", 1, 1},
	{"eli", "test123", 0, 1}
};

user CurrentUser = {"loggedOut", "", 0, 0};

int userNum = 3;


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