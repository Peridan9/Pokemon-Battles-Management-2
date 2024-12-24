/*
 * LinkedList.c
 *
 *  Created on: Dec 14, 2021
 *      Author: ise
 */

#include<stdlib.h>
#include "LinkedList.h"

struct Node {
	element value;
	struct Node *next;
};
struct Linkedlist_t {
	struct Node *head;
	copyFunction copyElement;
	freeFunction freeElement;
	printFunction printElement;
	equalFunction compareElement;
};

Linkedlist createLinkedList(copyFunction copyf, freeFunction freef, equalFunction equalf, printFunction printf){
	Linkedlist list = (Linkedlist)malloc(sizeof(struct Linkedlist_t));
	if(list == NULL){
		return NULL;
	}
//	list->head = (Element)malloc(sizeof(Element));
//	if(list->head == NULL){
//		free(list);
//		return NULL;
//	}
	list->head = NULL;
	list->copyElement = copyf;
	list->freeElement = freef;
	list->printElement = printf;
	list->compareElement = equalf;
	return list;
}

status appendNode(Linkedlist list, element val){
	struct Node *newnode = (struct Node*)malloc(sizeof(val));
	if(newnode == NULL){
		return failuere;
	}
	newnode->value = list->copyElement(val);
	newnode->next = NULL;
	if(list->head == NULL){
		list->head = newnode;
		return success;
	}
	struct Node *currentnode;
	currentnode = list->head;
	while(currentnode->next != NULL){
		currentnode = currentnode->next;
	}
	currentnode->next = newnode;
	return success;

}
void destroyList(Linkedlist list){
	struct Node *currentnode = list->head;
	struct Node *nextnode;
//	if(currentnode == NULL){
//		list->freeElement(currentnode); // might have a problem
//		free(list);
//		return;
//	}
	while(currentnode != NULL){
		nextnode = currentnode->next;
		list->freeElement(currentnode->value);
		free(currentnode);
		currentnode = nextnode;
	}
	free(list);
	list=NULL;
}
status displayList(Linkedlist list){
	struct Node *currentnode = list->head;
	struct Node *nextnode;
	while(currentnode != NULL){
		nextnode = currentnode->next;
		list->printElement(currentnode->value);
		currentnode = nextnode;
	}
	return success;
}
status deleteNode(Linkedlist list, element val){
	struct Node *currentnode = list->head;
	struct Node *previousnode = list->head;
	// if the head is the node to delete
	if(list->compareElement(currentnode->value, val) == 0){ // how to fix?
		list->head = list->head->next;
		list->freeElement(currentnode->value);
		free(currentnode);
	}
	currentnode = currentnode->next;
	while(currentnode != NULL){
		if(list->compareElement(currentnode->value, val) == 0){ // how to fix?
			previousnode->next = currentnode->next;
			list->freeElement(currentnode->value);
			free(currentnode);
			return success;
		}
		previousnode = previousnode->next;
		currentnode = currentnode->next;
	}
	return failuere;
}

element searchByKeyInList(Linkedlist list, element key){
	struct Node *nodetosearch = list->head;
	while(nodetosearch!=NULL){
		if(list->compareElement(nodetosearch->value, key) == 0){
			return nodetosearch->value;
		}
		nodetosearch = nodetosearch->next;
	}
	return NULL;


}

element nextNode(element elem){
	struct Node* nextnode = (struct Node*)elem;
	if(nextnode->next == NULL){
		return NULL;
	}
	return nextnode->next;
}

element getVaule(element elem){
	struct Node* node = (struct Node*)elem;
	return node->value;
}

element getHead(Linkedlist list){
	return list->head;
}



















