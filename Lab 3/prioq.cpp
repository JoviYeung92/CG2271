/*
 * prioq.cpp
 * 
 * An inefficient implementation of a minimum priority queue (using sorted linked list).
 * All operations may result in a time complexity of O(n).
 *
 * Created: 11/9/2013 3:18:05 PM
 *  Author: dcstanc
 */ 

#include <stdlib.h>
#include "prioq.h"

// This is a factory method to create an empty priority queue.
TPrioQueue *makeQueue() {
	TPrioQueue *ret = (TPrioQueue *) malloc(sizeof(TPrioQueue));
	
	if(ret != NULL) {
		ret->head = NULL;
		ret->itemCount = 0;	
	}
	
	return ret;
}

// Enqueue a new element into the priority queue.
void enq(TPrioQueue *queue, void *item, int priority) {
	TPrioQEntry *newEntry = (TPrioQEntry *) malloc(sizeof(TPrioQEntry));
	
	if (newEntry != NULL) {
		newEntry->item = item;
		newEntry->prio = priority;
		newEntry->prev = NULL;
		newEntry->next = NULL;
		
		// A standard sorted linked list insertion operation.
		if (queue->head == NULL) {
			queue->head=newEntry;
		} else {
			// Find insertion point.
			
			// First special case: Item at head has lower priority
			if(queue->head->prio > newEntry->prio) {
				// Insert item at the start of the queue.
				newEntry->next = queue->head;
				queue->head->prev = newEntry;
				queue->head = newEntry;
			} else {
				// Find your insertion point
				TPrioQEntry *trav = queue->head;
				
				while(trav->next != NULL && trav->prio < newEntry->prio) {
					trav = trav->next;
				}
				
				newEntry->prev = trav;
				newEntry->next = trav->next;
				if(trav->next != NULL) {
					trav->next->prev = newEntry;
				}
				
				trav->next = newEntry;
			}
		}
		
		queue->itemCount++;
	}	
}

// Dequeue an element from a priority queue (delete from the head of the linked list).
void *deq(TPrioQueue *queue) {
	// Return NULL if queue is empty
	if(queue->head == NULL) {
		return NULL;
	}
	
	void *ret = queue->head->item;
	TPrioQEntry *tmp = queue->head;
	
	if (queue->head->next != NULL) {
		queue->head->next->prev = NULL;
	}
	
	queue->head = queue->head->next;
	free(tmp);
	
	queue->itemCount--;
	
	return ret;
}

// Returns the 
int qlen(TPrioQueue *queue) {
	return queue->itemCount;
}
