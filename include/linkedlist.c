#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "linkedlist.h"

// Initialize an empty list
void initList(List * list){
	//*list_pointer = (List*)malloc(sizeof(List));
	list->head = NULL;
	list->tail = NULL;
}

// Create node containing item, return reference of it.
Node* createNode(void* item){
	Node* n = (Node *)malloc(sizeof(Node));

	if(n == NULL){
		return NULL;
	}

	n->item = item;
	n->next = NULL;

	return n;
}

// Insert new item at the end of list.
int insertAtTail(List * list, void* item){
	Node* newNode = createNode((void*)item);	
	if(newNode == NULL){
		return 1;
	}
	// Sets to head and tail if list is empty
	if(list->head == NULL){
		list->head = (Node*) newNode;
		list->tail = (Node*) newNode;
	}
	else{
		list->tail->next = (Node*) newNode;
		list->tail = list->tail->next
	}
	return 0;
}

// Insert item at start of the list.
int insertAtHead(List * list, void* item){
	Node* newNode = createNode(item);
	if(newNode == NULL){
		return 1;
	}
	// Sets to head and tail if list is empty
	if(list->head == NULL){
		list->head = (Node*) newNode;
		list->tail = (Node*) newNode;
	}else{
		newNode->next = (Node*) list->head;
		list->head = (Node*) newNode;
	}
	return 0;
}

// Insert item at a specified index.
int insertAtIndex(List * list, int index, void* item){
	// Program fails the index being searched for is bigger than the size of the array
	if(index > size(list)){
		printf("Error: index is greater than list size");
		exit(99);
	}
	// Inserts at head if index is 0
	if(index == 0){
		insertAtHead(list, item);
		return 0;
	}
	// Inserts at tail if index is size
	if(index == size(list)){
		insertAtTail(list, item);
		return 0;
	}

	// Inserts node at given index and sets its next to what was previously in that index
	Node* newNode = createNode(item);
	if(newNode == NULL){
		return 1;
	}
	Node* prevNode = (Node*)nodeAtIndex(list, index-1);
	Node* nextNode;
	nextNode = (Node*)prevNode->next;
	prevNode->next = (Node*) newNode;
	newNode->next = (Node*) nextNode;
	return 0;
}

// Remove item from the end of list and return a reference to it
void* removeTail(List * list){
	//Returns NULL if list is empty
	if(list->head- == NULL){
		return NULL;
	}else{
		Node* rmNode = list->tail;
		void* val = (void*)rmNode->item;
		Node* prevNode = (Node*)nodeAtIndex(list, size(list)-2);
		free(rmNode);
		list->tail = prevNode;
		list->tail->next = NULL;
		return val;
	}
}

// Remove item from start of list and return a reference to it
void* removeHead(List* list){
	//Returns NULL if list is empty
	if(list->head == NULL){
		return NULL;
	}else{
		Node* temp = (Node*)list->head;
		void* val = temp->item;
		list->head = temp->next;
		free(temp);
		return val;
	}
}

// Insert item at a specified index and return a reference to it
void* removeAtIndex(List* list_pointer, int index){
	//Returns NULL if index is not in list
	if(index >= size(list_pointer)){
		return NULL;
	// Removes head if index is 0
	}if(index == 0){
		return removeHead(list_pointer);
	// Removes tail if index is size
	}if(index == size(list_pointer)-1){
		return removeTail(list_pointer);
	}else{
		void* val = (void*) itemAtIndex(list_pointer, index);
		Node* rmNode = (Node*) nodeAtIndex(list_pointer, index);
		Node* prevNode = (Node*) nodeAtIndex(list_pointer, index-1);
		prevNode->next = (Node*) nodeAtIndex(list_pointer, index+1);
		free(rmNode);
		return val;
	}
}

// Return node at index
Node* nodeAtIndex(List* list, int index){
	//Returns NULL if index is not in list
	if(index >= size(list)){
		return NULL;
	}
	int i = 0;
	Node* temp = (Node*)list->head;
	// Iterate through list until index is reached
	while(i < index && temp->next != NULL){
		temp = (Node*) temp->next;
		i++;
	}
	return temp;
}

// Return item at index
void* itemAtIndex(List* list, int index){
	// Uses nodeAtIndex then returns its value
	Node* n = (Node*)nodeAtIndex(list, index);
	void* val = (void*)(n->item);
	return val;
}

// Return true if the list contains the given item at least once, false otherwise.
bool contains(List* list, void* item){
	// Returns NULL if list is empty
	if(list->head->item == NULL){
		return 0;
	}
	// Iterates through list until item is found
	while(list->head != NULL){
		if(list->head->item == item){
			return 1;
		}
		list->head = (Node*) list->head->next;
	}
	return 0;
}

// Returns the size of the list, measured in nodes.
int size(List* list_pointer){
	// Returns NULL if list is empty
	if(list_pointer->head->item == NULL){
		return 0;
	}
	int i = 0;
	Node* temp = (Node*)list_pointer->head;
	// Iterates through list counting each node
	while(temp->next != NULL){
		temp = (Node*)temp->next;
		i++;
	}
	return i+1;
}

//prints the list
void printList(List* list) {
	Node* node;

  	// Handle an empty node. Just print a message.
	if(list->head == NULL) {
		printf("\nEmpty List");
		return;
	}
	
  	// Start with the head.
	node = (Node*) list->head;

	while(node != NULL) {
		printf("[ %x ]", node->item);

		// Move to the next node
		node = (Node*) node->next;

		if(node != NULL) {
			printf("-->");
		}

	}
	printf("\n\n");

}

// Frees the list
void freeList(List* list_pointer){
	Node* temp = (Node*) list_pointer->head;
	// Iterates through each node and frees them
	while (temp != NULL){
		Node* toFree = temp;
		temp = (Node*)temp->next;
		free(toFree);
	}
}

// Stevens-style wrapper for malloc()
void *Malloc(size_t size) {
  void *ptr = NULL; 
  if ((ptr = malloc(size)) == NULL) { 
    fprintf(stderr, "Could not allocated space for %ld bytes - %s", size, strerror(errno));
    exit(errno);
  }
  return ptr;
}

// Stevens-style wrapper for free()
void *Free(void *ptr){
	if (ptr == NULL){
		fprintf(stderr, "Error, pointer is null \n");
		exit(255);
	}
	free(ptr);
	return 0;
}
