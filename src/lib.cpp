#include <cmath>
#include <cstdio>
#include "../include/hashset.hpp"
extern "C" {
  #include "../include/linkedlist.h"
}
extern "C" {
  #include "linkedlist.c"
}

// Constructor
HashSet::HashSet(size_t size) {
  this->array = new LinkedList*[size];
  for(size_t i = 0; i < size; i++){
    this->array[i] = NULL;
  }
  this->size = size;
}

// Destructor
HashSet::~HashSet() {
  for(size_t i = 0; i < size; i++){
    delete this->array[i];
  }
  delete[] this->array;
}

// Generate a prehash for an item with a given size
unsigned long HashSet::prehash(int item) {
  unsigned long h = 5381;
  int c = item;
  int divisor = 1;
  int mod;
  while((item / divisor) != 0){
    divisor *= 10;
  }
  divisor /= 10;
  //parses each digit of item
  while(divisor != 0){
    c = item / divisor;
    h = ((h << 5) + h) + c;
    item %= divisor;
    divisor /= 10;
  }
  return h;
}

// Hash an unsigned long into an index that fits into a hash set
unsigned long HashSet::hash(int item) {
  unsigned long hashNum = prehash(item) % size;
  return hashNum;
}

// Insert item in the set. Return true if the item was inserted, false if it wasn't (i.e. it was already in the set)
// If the load factor exceeds 70 after insert, resize the table to hold twice the number of buckets.
bool HashSet::insert(int item) {
  if(contains(item)){
      return false;
  }
  unsigned long hashNum = hash(item);
  //initializes array linkedlist if first node
  if(this->array[hashNum] == NULL){
    this->array[hashNum] = new LinkedList();
  }
  insertAtTail(this->array[hashNum], (void*)item);
  int count = 0;
  for(size_t i = 0; i < size; i++){
    if(this->array[i] != NULL){
      count++;
    }
  }
  lf = ((double)count / size) * 100;
  if(lf >= 70){
    printf("Load factor exceeded\n");
  }
  return true;
}

// Remove an item from the set. Return true if it was removed, false if it wasn't (i.e. it wasn't in the set to begin with)
bool HashSet::remove(int item) {
  if(!contains(item)){
    return false;
  }
  for(size_t i = 0; i < size; i++){
    if(containsNode(this->array[i], (void*)item)){
      int rmIndex = 0;
      Node* temp = this->array[i]->head;
      while(temp != NULL){
        if(temp->item == (void*)item){
          removeAtIndex(this->array[i], rmIndex);
          return true;
        }
        temp = temp->next;
        rmIndex++;
      }
    }
  }
  return false;
}

// Return true if the item exists in the set, false otherwise
bool HashSet::contains(int item) {
  unsigned long hashNum = hash(item);
  if(containsNode(this->array[hashNum], (void*)item)){
    return true;
  }
  return false;
}


// Returns the number of items in the hash set
size_t HashSet::len() {
  int count = 0;
  for(size_t i = 0; i < size; i++){
    if(this->array[i] != NULL){
      int size = listSize(this->array[i]);
      count += size;
    }
  }
  return (size_t)count;
}

// Returns the number of empty buckets that can be filled before reallocating
size_t HashSet::capacity() {
  return floor(size*0.7);
}

// Print Table. You can do this in a way that helps you implement your hash set.
void HashSet::print() {
  printf("Hash Set:\n");
  for(size_t i = 0; i < size; i++){
    printf("\nList %d: \n\n\t", i); 
    printList(this->array[i]);
  }
}
