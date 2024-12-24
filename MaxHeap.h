/*
 * MaxHeap.h
 *
 *  Created on: Dec 14, 2021
 *      Author: ise
 */

#ifndef MAXHEAP_H_
#define MAXHEAP_H_

#include<stdlib.h>
#include<stdio.h>
#include "Defs.h"
#include <string.h>

typedef struct MaxHeap_t *MaxHeap;

MaxHeap CreateHeap(int maxsize, char* heapname, copyFunction copyf, freeFunction freef, equalFunction equalf, printFunction printf);
status destroyHeap(MaxHeap heap);
status insertToHeap(MaxHeap heap, element elem);
status printHeap(MaxHeap heap);
element PopMaxHeap(MaxHeap heap);
element TopMaxHeap(MaxHeap heap);
char* getHeapId(MaxHeap heap);
int getHeapCurrentSize(MaxHeap heap);
element copyHeap(element elem);
status freeHeap(element elem);
int compareHeap(element elem1, element elem2);
status printHeap2(element elem);

#endif /* MAXHEAP_H_ */
