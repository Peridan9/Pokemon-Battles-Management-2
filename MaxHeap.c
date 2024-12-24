/*
 * MaxHeap.c
 *
 *  Created on: Dec 14, 2021
 *      Author: ise
 */
#include<stdlib.h>
#include "MaxHeap.h"

struct MaxHeap_t {
	element* arrayHeap;
	char* heapname;
	int numberofelements;
	int heapsize;
	copyFunction copyElement;
	freeFunction freeElement;
	printFunction printElement;
	equalFunction compareElement;
};

MaxHeap CreateHeap(int maxsize, char* heapname, copyFunction copyf, freeFunction freef, equalFunction equalf, printFunction printf){
	if(maxsize <= 0){
		return NULL;
	}
	MaxHeap heap = (MaxHeap)malloc(sizeof(struct MaxHeap_t));
	if(heap == NULL){
		return NULL;
	}
	heap->arrayHeap = (element*)malloc(sizeof(element)*maxsize);
	if(heap->arrayHeap == NULL){
		free(heap);
		return NULL;
	}
	heap->heapname = (char*)malloc(sizeof(char)*strlen(heapname) + 1);
	strcpy(heap->heapname,heapname);
	heap->numberofelements = 0;
	heap->heapsize = maxsize;
	heap->copyElement = copyf;
	heap->freeElement = freef;
	heap->printElement = printf;
	heap->compareElement = equalf;
	return heap;
}
void swap(MaxHeap heap, int elem1, int elem2){
	element tmp = heap->arrayHeap[elem1];
	heap->arrayHeap[elem1] = heap->arrayHeap[elem2];
	heap->arrayHeap[elem2] = tmp;
}
void MaxHeapify(MaxHeap heap, int i){
	int lefti = (i*2 + 1);
	int righti = (i*2 + 2);
	int largest = i;
	if((lefti < heap->numberofelements) && heap->compareElement(heap->arrayHeap[lefti],heap->arrayHeap[largest]) == 1){
		largest = lefti;
	}
	if(righti < heap->numberofelements && heap->compareElement(heap->arrayHeap[righti],heap->arrayHeap[largest]) == 1){
		largest = righti;
	}
	if(largest != i){ // swap - maybe I should write a swap function
//		element tmp = heap->arrayHeap[i];
//		heap->arrayHeap[i] = heap->arrayHeap[largest];
//		heap->arrayHeap[largest] = tmp;
		swap(heap,i,largest);
		MaxHeapify(heap, largest);
	}
}
void heapIncrease(MaxHeap heap, int i, element elem){
	heap->arrayHeap[i] = heap->copyElement(elem);
	while(i > 0 && heap->compareElement(heap->arrayHeap[(i-1)/2],heap->arrayHeap[i]) == -1){
		swap(heap, (i-1)/2, i);
		i = (i-1)/2;
	}
}
status insertToHeap(MaxHeap heap, element elem){
	if((heap->numberofelements) < heap->heapsize){
		heapIncrease(heap,heap->numberofelements,elem);
		heap->numberofelements++;
		return success;
	}
	return failuere;
}

status printHeap(MaxHeap heap){ // to print the heap right we need to make a copy of it and then popmax till its empty;
	printf("%s:\n", getHeapId(heap));
	if(heap->numberofelements < 1){
		printf("No elements.\n\n");
	}
	int i;
	MaxHeap copy = (MaxHeap)copyHeap(heap);
	for(i=0;i<heap->numberofelements;i++){
		printf("%d. ",(i+1));
		heap->printElement(PopMaxHeap(copy));
	}
	destroyHeap(copy);
	return success;
}
element PopMaxHeap(MaxHeap heap){
	if(heap->numberofelements < 1){
		return NULL;
	}
	if(heap->numberofelements == 1){
		element max = heap->arrayHeap[0];

	}
	element max = heap->arrayHeap[0];
	heap->arrayHeap[0] = heap->arrayHeap[heap->numberofelements - 1];
	heap->arrayHeap[heap->numberofelements - 1] = NULL;
	heap->numberofelements--;
	MaxHeapify(heap, 0);
	return max;
}
element TopMaxHeap(MaxHeap heap){
	if(heap->numberofelements < 1){
		return NULL;
	}
	return heap->arrayHeap[0];
}
char* getHeapId(MaxHeap heap){
	return heap->heapname;
}
int getHeapCurrentSize(MaxHeap heap){
	return heap->numberofelements;
}

status destroyHeap(MaxHeap heap){
	int i;
	for(i=0;i<heap->numberofelements;i++){
		heap->freeElement(heap->arrayHeap[i]);
	}
	free(heap->heapname);
	free(heap->arrayHeap);
	free(heap);
	heap=NULL;
	return success;
}
//need to make copys of the elements and not use them directly

element copyHeap(element elem){
	if (elem == NULL){
		return NULL;
	}
	MaxHeap original = (MaxHeap)elem;
	MaxHeap copy = CreateHeap(original->heapsize, original->heapname, original->copyElement, original->freeElement, original->compareElement, original->printElement);
	if(copy!=NULL){
		int i;
		for(i=0;i<original->numberofelements;i++){
			copy->arrayHeap[i] = original->arrayHeap[i];
		}
		copy->numberofelements = original->numberofelements;
		return copy;
	}
	return NULL;
}

status freeHeap(element elem){
	return destroyHeap((MaxHeap)elem);
}

int compareHeap(element elem1, element elem2){
	MaxHeap tmpelem1 = (MaxHeap)elem1;
	char* name = (char*)elem2;
	return strcmp(getHeapId(tmpelem1),name);
}

status printHeap2(element elem){
	return printHeap((MaxHeap)elem);
}

