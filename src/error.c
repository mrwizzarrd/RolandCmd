#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
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
	case MEMORY_ALLOCATION_FAILED:
		printf("ERROR: Memory Allocation Failed\n");
		if(customMsg){
			printf("Additional info:\n\t%s\n", CustomErrMsg);
		}

	default:
		printf("ERROR: THROWN ERROR NOT FOUND\n");
	}
}




