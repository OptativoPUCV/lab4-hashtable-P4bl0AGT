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


void insertMap(HashMap * map, char * key, void * value)
{
  Pair *pair = createPair(key, value);
  //conozco la posicion
  long pos = hash(key, map->capacity);
  //si la posicion esta ocupada metodo resolucion de colisiones
  while(map->buckets[pos % map->capacity] != NULL)
    pos++;
  //una vez se asegura que estamos en una pos null se inserta el elemento
  map->buckets[pos % map->capacity] = pair;
  (map->size)++;
  (map->current) = pos % map->capacity;

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity)
{
  HashMap *map = (HashMap *) malloc(sizeof(HashMap)); 
  map->buckets = (Pair **) malloc(sizeof(Pair *) *  capacity);
  for(long i = 0 ; i < capacity ; i++)
    map->buckets[i] = NULL;
  map->size = 0;
  map->capacity = capacity;
  map->current = -1;
  return map;
}

void eraseMap(HashMap * map,  char * key)
{    
  //long pos = hash(key, map->capacity);
  Pair *pair = searchMap(map, key);
  pair->key = "-1";

}

Pair * searchMap(HashMap * map,  char * key) {   
  
  long pos = hash(key, map->capacity);
  Pair *pair = map->buckets[pos % map->capacity];
  
  while( strcmp(pair->key, key) )
    {
      pos++;
      pair = map->buckets[pos % map->capacity];
      if(pair == NULL)
        return NULL;
    }
    map->current = pos % map->capacity;
    return pair;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
