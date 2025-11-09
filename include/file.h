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

#endif