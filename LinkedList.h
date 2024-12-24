/*
 * LinkedList.h
 *
 *  Created on: Dec 14, 2021
 *      Author: ise
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include<stdlib.h>
#include<stdio.h>
#include "Defs.h"

//typedef void* Element;
//typedef Element (*CopyFunction)(Element);
//typedef void (*FreeFunction)(Element);
//typedef void (*CompareFunction)(Element);
//typedef void (*PrintFunction)(Element);
typedef struct Linkedlist_t *Linkedlist;

// create linkedlist returns a pointer to the struct
Linkedlist createLinkedList(copyFunction copyf, freeFunction freef, equalFunction equalf, printFunction printf);

// destory list returns nothing
void destroyList(Linkedlist list);

// adding a node at the end of the list returns enum
status appendNode(Linkedlist list, element element);

// deleting a node from the list which contains element
status deleteNode(Linkedlist list, element element);

// printing all the elements in the list
status displayList(Linkedlist list);

// searching a element by the key we give and return the all element
element searchByKeyInList(Linkedlist list, element key);

element nextNode(element elem);
element getVaule(element elem);
element getHead(Linkedlist list);

#endif /* LINKEDLIST_H_ */
