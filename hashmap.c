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

int is_equal(void* key1, void* key2)
{
    if(key1==NULL || key2==NULL)
      return 0;
    if(strcmp((char*)key1,(char*)key2) == 0)
      return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value)
{
  //crear pareja
  Pair *pair = createPair(key, value);
  //conozco la posicion
  long pos = hash(key, map->capacity);
  //si la posicion esta ocupada metodo resolucion de colisiones
  while(map->buckets[pos] != NULL)
    pos = (pos + 1) % map->capacity ;
  //una vez se asegura que estamos en una pos null se inserta el elemento
  map->buckets[pos] = pair;
  (map->size)++;
  (map->current) = pos;

}

void enlarge(HashMap * map)
{
  enlarge_called = 1; //no borrar (testing purposes)
  Pair **oldBuckets = map->buckets;
  long oldCapacity = map->capacity;
  map->capacity = map->capacity * 2;
  map->buckets = (Pair **) malloc(sizeof(Pair *) * map->capacity);
  for(long pos = 0 ; pos < map->capacity ; pos++)
    map->buckets[pos] = NULL;
  map->size = 0;

  for (long pos= 0 ; pos < oldCapacity ; pos++)
  {
    if(oldBuckets[pos] != NULL)
      insertMap(map, oldBuckets[pos]->key, oldBuckets[pos]->value);
  }

}


HashMap * createMap(long capacity)
{
  HashMap *map = (HashMap *) malloc(sizeof(HashMap)); 
  map->buckets = (Pair **) malloc(sizeof(Pair *) *  capacity);
  for(long pos = 0 ; pos < capacity ; pos++)
    map->buckets[pos] = NULL;
  map->size = 0;
  map->capacity = capacity;
  map->current = -1;
  return map;
}

void eraseMap(HashMap * map,  char * key)
{    
  //long pos = hash(key, map->capacity);
  Pair *pair = searchMap(map, key);
  if(pair == NULL)
    return;
  pair->key = NULL;
  (map->size)--;

}

Pair * searchMap(HashMap * map,  char * key) {   
  
  long pos = hash(key, map->capacity);
  for(long i = pos ; i < map->capacity ; i++)
  {
    Pair *pair = map->buckets[i];
    if( pair != NULL && !strcmp(pair->key, key) )
    {
      map->current = i;
      return pair;
    }
  }
  return NULL;
  
  /*
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
    return pair;*/
}

Pair * firstMap(HashMap * map)
{
  for(long pos = 0 ; pos < map->capacity ; pos++)
  {
    Pair *pair = map->buckets[i];
    if(pair != NULL && pair->key != NULL)
    {
      map->current = pos;
      return pair;
    }
  }
  return NULL;
}

Pair * nextMap(HashMap * map)
{
  for(long pos = (map->current + 1) ; pos < map->capacity ; pos++)
  {
    Pair *pair = map->buckets[pos];
    if(pair != NULL && pair->key != NULL)
    {
      map->current = pos;
      return pair;
    }
  }
  return NULL;
}
