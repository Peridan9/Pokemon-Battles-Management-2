/*
 * Defs.h
 *
 *  Created on: Nov 24, 2021
 *      Author: ise
 */

#ifndef DEFS_H_
#define DEFS_H_

typedef enum
{
	SUCCESS,
	MEMORY_PROBLEM,
	CLEARED,
	EMPTY_LIST
}Error_p;

//typedef enum e_bool{false,true}bool;
typedef enum e_status{success,failuere}status;
typedef void* element;
typedef element(*copyFunction)(element);
typedef status(*freeFunction)(element);
typedef status(*printFunction)(element);
typedef int(*equalFunction)(element, element);
typedef char*(*getCategoryFunction)(element);
typedef int(*getAttackFunction)(element firstElem, element secondElem, int* attackFirst, int* attackSecond);

#endif /* DEFS_H_ */
