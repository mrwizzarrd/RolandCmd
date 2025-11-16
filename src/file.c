/**
 * @file file.c
 * 
 * @brief file handler
 *
 * 
 * @author Roland Vermiglio
**/

#include <stdio.h>
#include "file.h"
#include <stdbool.h>
#include "error.h"

/**
 * @brief Checks if file exists
 * 
 * @details checks if file exists if it does returns true, otherwise returns false
 * 
 * @param filename Name of file to locate
 * 
 * @return  true = file found, false = file not found
 *  
**/

bool fileFound(char *filename){
	FILE* file = fopen(filename, "r");

	if(file){
		fclose(file);
		return true;
	} else{
		return false;
	}
}



/**
 * @brief creates new file 
 * 
 * @details checks if file exists, if it does throws FILE_EXISTS error, otherwise it creates file
 * 
 * @param filename Name of file to create
 * 
 * @return int 0 = success, -1 = file already exists, -2 = error creating file
 *  
**/
int createFile(const char *filename){
	FILE* check = fopen(filename, "r");
	if(check){
		fclose(check);
		return -1;
	}
	FILE* file = fopen(filename, "w");

	if(file == NULL){
		return -2;
	}
	fclose(file);
	return 0;
}


/**
 * @brief creates new file 
 * 
 * @details checks if file exists, if it doesn't throws FILE_NOT_FOUND error, otherwise it deletes file
 * 
 * @param string for filename
 * 
 * @return if file not found: -1, otherwise 1 if file was not successfully removed or 0 if it was
 *  
**/
int deleteFile(char *filename){
	if(!fileFound(filename)){
		return -1;
	}
	return remove(filename) == 0;
}


/**
 * @brief creates new file 
 * 
 * @details checks if file exists, if it does throws FILE_EXISTS error, otherwise it creates file
 * 
 * @param filename Name of file to write to
 * @param content content to write to file
 * @param newline 
 * 
 * @return int 0 = success, -1 = file not found, -2 = error opening file
 *  
**/

int writeToFile(char *filename, char *content, bool newline){
	bool Found = fileFound(filename);

	if(!Found){
		return -1;
	}
	FILE* file = fopen(filename, "a");
	if(!file){
		return -2;
	}
	if(newline){
		fprintf(file, "\n");
	}
	fprintf(file, "%s", content);
	fclose(file);
	return 0;
}


/**
 * @brief reads content from file
 *
 * 
 * @details checks if file exists, if it does throws FILE_EXISTS error, otherwise it reads file
 * 
 * @param filename Name of file to read from
 * 
 * @return int 0 = success, -1 = file not found, -2 = error opening file
 * 
 * 
**/

DynamicString *readFile(char *filename){

		bool Found = fileFound(filename);

		if(!Found){
			return NewDynamicString(25, "ERROR: -1");
		}
		FILE* file = fopen(filename, "r");

		if(!file){
			return NewDynamicString(25, "ERROR: -2");
		}

		//gets file size
		fseek(file, 0, SEEK_END);
		long fileSize = ftell(file);
		rewind(file);

		char *buffer = malloc(fileSize + 1);
		if(!buffer){
			return NewDynamicString(25, "ERROR: -2");
		}

		size_t bytesRead = fread(buffer, 1, fileSize, file);
		buffer[bytesRead] = '\0';

		fclose(file);
		DynamicString *returnContent = NewDynamicString(strlen(buffer)+5, buffer);

		free(buffer);
		return returnContent;
}

