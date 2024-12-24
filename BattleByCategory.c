/*
 * BattleByCategory.c
 *
 *  Created on: Dec 21, 2021
 *      Author: ise
 */

#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"

struct battle_s{
	Linkedlist categories;
	int numofcategories;
	int capacity;
	copyFunction copyElement;
	freeFunction freeElement;
	printFunction printElement;
	equalFunction compareElement;
	getCategoryFunction getCategory;
	getAttackFunction getAttack;
};

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement){
	Battle newBattle = (Battle)malloc(sizeof(struct battle_s));
	if(newBattle == NULL){
		return NULL;
	}
	newBattle->categories = createLinkedList(copyHeap,freeHeap,compareHeap,printHeap2); // will receive heap functions
	if(newBattle->categories == NULL){
		free(newBattle);
		newBattle = NULL;
		return newBattle;
	}
	char* token;
	token = strtok(categories, ",");
	while(token!=NULL){
		MaxHeap newheap = CreateHeap(capacity, token, copyElement, freeElement, equalElement, printElement); // will receive function of the object we enter
		if(newheap==NULL){
			destroyList(newBattle->categories);
			free(newBattle->categories);//maybe we should call to destroy Battle.
			free(newBattle);
			newBattle=NULL;
			return newBattle;
		}
		appendNode(newBattle->categories, newheap);
		destroyHeap(newheap);
		token = strtok(NULL, ",");
	}
	newBattle->numofcategories = numberOfCategories;
	newBattle->capacity = capacity;
	newBattle->copyElement;
	newBattle->freeElement; // what function to give? of the list?
	newBattle->compareElement;
	newBattle->printElement;
	newBattle->getCategory = getCategory;
	newBattle->getAttack = getAttack;
	return newBattle;
}

status destroyBattleByCategory(Battle b){
	destroyList(b->categories);
	free(b);
	b=NULL;
	return success;
}
status insertObject(Battle b, element elem){ // need to do. need to use searchbykey in list?
	if(elem == NULL){
		return failuere;
	}
	insertToHeap(searchByKeyInList(b->categories, b->getCategory(elem)), elem); // need to check;
	return success;
}

void displayObjectsByCategories(Battle b){
	displayList(b->categories);
}

element removeMaxByCategory(Battle b,char* category){
	// first we need to search the category //maybe I can search by heap id
	return PopMaxHeap((MaxHeap)searchByKeyInList(b->categories, category));
}

int getNumberOfObjectsInCategory(Battle b,char* category){
	return getHeapCurrentSize((MaxHeap)searchByKeyInList(b->categories, category));
}
element fight(Battle b,element elem){
	int* elem1attack = (int*)malloc(sizeof(int));
	if(elem1attack == NULL){
		return NULL;
	}
	int* elem2attack = (int*)malloc(sizeof(int));
	if(elem2attack == NULL){
		return NULL;
	}
	element strongestpoke = NULL;
	*elem1attack = 999;
	*elem2attack = 0;
	int currentmax = -999;
	element currentnode = getHead(b->categories);
	int i;
	for(i=0;i<b->numofcategories;i++){
		if(TopMaxHeap(getVaule(currentnode)) == NULL){
			currentnode = nextNode(currentnode);
			continue;
		}
		int tmp = b->getAttack(elem,TopMaxHeap(getVaule(currentnode)),elem1attack, elem2attack);
		if(currentmax < tmp){
			currentmax = tmp;
			strongestpoke = TopMaxHeap(getVaule(currentnode));
		}
		currentnode = nextNode(currentnode);
		//		currentheap =return NULL;
	}
	free(elem1attack);
	free(elem2attack);
	elem1attack = NULL;
	elem2attack = NULL;
	// dont forget to free the two ints;
	return strongestpoke;
}


