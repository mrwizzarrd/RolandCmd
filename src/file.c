/**
 * @file file.h
 * 
 * @brief file handler
 *
 * 
 * @author Roland Vermiglio
**/

#include <stdio.h>
#include "file.h"


/**
 * @brief creates new file 
 * 
 * @details checks if file exists, if it does throws FILE_EXISTS error, otherwise it creates file
 * 
 * @param filename Name of file to create
 *  
**/
void createFile(const char *filename){
	FILE* check = fopen(filename, "r");
	if(check){
		ThrowError(FILE_EXISTS, "");
		fclose(check);
		return -1;
	}
	FILE* file = fopen(filename, "w");

	if(file == NULL){
		return -2;
	}
	}
	fclose(filename);
	return 0;
}


/**
 * @brief creates new file 
 * 
 * @details checks if file exists, if it doesn't throws FILE_NOT_FOUND error, otherwise it deletes file
 * 
 * @param string for filename
 *  
**/
int deleteFile(char *filename){
	return remove(filename) == 0;
}