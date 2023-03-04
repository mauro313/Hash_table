#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"

/**
 * @brief create a new hash element.
 * 
 * @param key 
 * @param object 
 * @return HashElement_t* 
 */
HashElement_t* hashElement_new(char* key,void* object){
  HashElement_t* element_new = (HashElement_t*)malloc(sizeof(HashElement_t));
  if(element_new == NULL){
    printf("memory cannot be reserved for a new hashElement\n");
    exit(EXIT_FAILURE);  
  } 
  element_new->key = key;
  element_new->object = object;
  element_new->nextToIndex = NULL;
  return element_new;
}

/**
 * @brief free the memory of a hash element.
 * 
 * @param elementToFree 
 */
void hashElement_free(HashElement_t** elementToFree){
  if(elementToFree!=NULL && *elementToFree!=NULL){
    (*elementToFree)->nextToIndex = NULL;
    free(*elementToFree);
    *elementToFree = NULL;  
  }
}

/**
 * @brief get the key of a hash element.
 * 
 * @param element 
 * @return char* 
 */
char* hashElement_getKey(HashElement_t* element){
  if(element == NULL){
    printf("HashElement pinter is NULL(1)"); 
    exit(EXIT_FAILURE); 
  }
  return element->key;
}

/**
 * @brief get the element of a hash element.
 * 
 * @param element 
 * @return void* 
 */
void* hashElement_getObject(HashElement_t* element){
  if(element == NULL){
    printf("HashElement pointer is NULL(2)"); 
    exit(EXIT_FAILURE); 
  }
  return element->object;
}

/**
 * @brief get the next hash element of a hash element in case of collision.
 * 
 * @param element 
 * @return HashElement_t* 
 */
HashElement_t* hashElement_getNextToIndex(HashElement_t* element){
  if(element == NULL){
    printf("HashElement pointer is NULL(3)"); 
    exit(EXIT_FAILURE); 
  }
  return element->nextToIndex;
}

/**
 * @brief create a new hash table.
 * 
 * @param maxSize 
 * @return HashTable_t* 
 */
HashTable_t* hashTable_new(int maxSize){
  HashTable_t* table_new = (HashTable_t*)malloc(sizeof(HashTable_t));
  if(table_new == NULL){
    printf("memmory cannot be reserved for a new hash table\n");
    exit(EXIT_FAILURE);
  }    
  table_new->Elements = (HashElement_t**)malloc(maxSize*sizeof(HashElement_t*));
  if(table_new->Elements == NULL){
    printf("memory cannot be reserved for a HashElement array\n");
    free(table_new);
    exit(EXIT_FAILURE);   
  }
  for(int i=0;i<maxSize;i++){
    table_new->Elements[i] = NULL;          
  }
  table_new->max_size = maxSize;
  return table_new;                 
}

/**
 * @brief free the memory of a hash table.
 * 
 * @param tableToFree 
 */
void hashTable_free(HashTable_t** tableToFree){
  if(tableToFree!=NULL && *tableToFree!=NULL){
    free((*tableToFree)->Elements);
    (*tableToFree)->Elements = NULL;
    free(*tableToFree);
    *tableToFree = NULL;  
  }   
}

/**
 * @brief insert an element in a hash table.Return true if the element was added and false 
 * otherwise (the key already exists).
 * 
 * @param table 
 * @param key 
 * @param object 
 * @return true 
 * @return false 
 */
bool hashTable_insert(HashTable_t* table,char* key,void* object){
  if(table == NULL){
    printf("\nhash table is pointer NULL(1)\n");
    exit(EXIT_FAILURE);  
  }    
  unsigned int index = hash_function(table,key);
  bool inserted = false;
  if(table->Elements[index]==NULL){
    table->Elements[index] = hashElement_new(key,object); 
    inserted = true; 
  } 
  else{
    HashElement_t** auxiliar = &table->Elements[index];
    while(*auxiliar!=NULL && strcmp((*auxiliar)->key,key)!=0){
      auxiliar = &(*auxiliar)->nextToIndex;  
    }
    if(*auxiliar==NULL){
      *auxiliar = hashElement_new(key,object);
      inserted = true;
    }
  }
  return inserted;
}

/**
 * @brief search an element in a hash table using a key. Return the element if exists and NULL otherwise. 
 * 
 * @param table 
 * @param key 
 * @return void* 
 */
void* hashTable_search(HashTable_t* table,char* key){
  if(table == NULL){
    printf("\nhash table pointer is NULL(2)\n");
    exit(EXIT_FAILURE);    
  }  
  unsigned int index = hash_function(table,key);
  void* objectToReturn = NULL;
  if(table->Elements[index]!=NULL){
    HashElement_t* auxiliar = table->Elements[index];
    while(auxiliar!=NULL && strcmp(auxiliar->key,key)!=0){
      auxiliar = auxiliar->nextToIndex;  
    }
    if(auxiliar!=NULL){
      objectToReturn = auxiliar->object;  
    }
  }
  return objectToReturn;
}

/**
 * @brief delete an element with the selected key. Return true if it was deleted and false
 * otherwise (the key does not exist).
 * 
 * @param table 
 * @param key 
 * @return true 
 * @return false 
 */
bool hashTable_delete(HashTable_t* table,char* key,void (*freeObject)(void**)){
  if(table == NULL){
    printf("\nhash table pointer is NULL\n");
    exit(EXIT_FAILURE);
  }  
  unsigned int index = hash_function(table,key);
  bool wasDeleted = false;
  if(table->Elements[index]!=NULL){
    HashElement_t** auxiliar = &table->Elements[index];
    while(*auxiliar!=NULL && strcmp((*auxiliar)->key,key)!=0){
      auxiliar = &(*auxiliar)->nextToIndex;    
    }
    if(*auxiliar!=NULL){
      HashElement_t* toDelete = *auxiliar;
      if(*auxiliar == table->Elements[index]){
        table->Elements[index] = toDelete->nextToIndex;
      }
      else{
        *auxiliar = toDelete->nextToIndex;  
      }
      freeObject(&(toDelete)->object);
      hashElement_free(&toDelete); 
      wasDeleted = true; 
    }
  }
  return wasDeleted;
}

/**
 * @brief function that realizes the hash.
 * 
 * @param table 
 * @param stringKey 
 * @return unsigned long 
 */
static unsigned long hash_function(HashTable_t* table,char* stringKey){
  unsigned int addition = 0;
  for(int i=0;stringKey[i];i++){
    addition+=stringKey[i];  
  }
  return addition%(table->max_size);
}