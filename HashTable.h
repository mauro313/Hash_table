#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include <stdbool.h>

typedef struct _hashElement{
  char* key;
  void* object;
  struct _hashElement* nextToIndex;
}HashElement_t;

typedef struct _hashTable{
  HashElement_t** Elements;
  int max_size;      
}HashTable_t;

HashElement_t* hashElement_new(char* key,void* object);

void hashElement_free(HashElement_t** elementToFree);

char* hashElement_getKey(HashElement_t* element);

void* hashElement_getObject(HashElement_t* element);

HashElement_t* hashElement_getNextToIndex(HashElement_t* element);

HashTable_t* hashTable_new(int maxSize);

void hashTable_free(HashTable_t** tableToFree);

bool hashTable_insert(HashTable_t* table,char* key,void* object);

void* hashTable_search(HashTable_t* table,char* key);

bool hashTable_delete(HashTable_t* table,char* key,void (*freeObject)(void**));

static unsigned long hash_function(HashTable_t* table,char* stringKey);

#include "HashTable.c"

#endif  //HASHTABLE_H_INCLUDED