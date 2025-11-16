/**
 * @file file.h
 * 
 * @brief file handler
 * 
 * @author Roland Vermiglio
**/

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdbool.h>
#include "util.h"


/**
 * @brief creates new file 
 * 
 * @details checks if file exists, if it does throws FILE_EXISTS error, otherwise it creates file
 * 
 * @param string for filename
 *  
**/
int createFile(const char *filename);


/**
 * @brief creates new file 
 * 
 * @details checks if file exists, if it doesn't throws FILE_NOT_FOUND error, otherwise it deletes file
 * 
 * @param string for filename
 *  
**/
int deleteFile(char *filename);

/**
 * @brief writes content to file
 * 
 * @details checks if file exists, if it does throws FILE_EXISTS error, otherwise it writes to file
 * 
 * @param filename Name of file to write to
 * @param content content to write to file
 * @param newline 
 * 
 * @return int 0 = success, -1 = file not found, -2 = error opening file
 *  
**/

int writeToFile(char *filename, char *content, bool newline);


/**
 * @brief reads content from file
 *
 * 
 * @details checks if file exists, if it does throws FILE_EXISTS error, otherwise it reads file
 * 
 * @param filename Name of file to read from
 * 
 * @return a dynamic string holding error content or file info 
 * 
 * 
**/

DynamicString *readFile(char *filename);

#endif