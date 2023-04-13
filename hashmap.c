#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  long clave = hash(key,map->capacity);
  Pair *nuevoNodo = createPair(key,value);
  
  if (map->buckets[clave] != NULL) {
    for(long i = clave ; i < map->capacity + clave ; i++)  {
      long j = i % map->capacity;
      if (map->buckets[j] == NULL || map->buckets[j]->key == NULL) {
        map->buckets[j] = nuevoNodo;
        map->size++;
        map->current = j;
        break;
      }
    }
  } else {
    map->buckets[clave] = nuevoNodo;
    map->size++;
    map->current = clave;
  }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *mapa = NULL;
  mapa = (HashMap *) malloc(sizeof(HashMap));
  if (mapa == NULL) exit(EXIT_FAILURE);
  mapa->buckets = (Pair **) malloc(sizeof(Pair*) * capacity);
  if (mapa->buckets == NULL) exit(EXIT_FAILURE);

  mapa->size = 0;
  mapa->capacity = capacity;
  mapa->current = -1;
  
  return mapa;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   
  long clave = hash(key,map->capacity);

  if (map->buckets[clave] == NULL) return NULL;

 
  for (long i = clave ; i < map->capacity + clave ; i++) {
    long j = i % map->capacity;
    if (map->buckets[j] == NULL) return NULL;
      
    if (is_equal(map->buckets[j]->key,key) == 1) {
      map->current = j;
      return map->buckets[j];
    }
  }
  return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
