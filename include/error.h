#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
	 * @brief Memory Allocation Failed
	 * @details Thrown when allocation of dynamic memory fails (malloc/realloc)
	**/


	MEMORY_ALLOCATION_FAILED = 502,


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

void ThrowError(ErrorCode err, char *CustomErrMsg);




#endif
