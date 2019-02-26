#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

typedef element item;

/*
 Funcion para inicializar los elementos de la tabla de hash
 Parametros:
        Const char* k: Apuntador de clave
        Const char* v: Apuntador de valor
 Return: El elemento inicializado
*/
static element* ht_new_element(const char* k, const char* v) {
    element* i = malloc(sizeof(element)); 
    i->key = strdup(k); 
    i->value = strdup(v);
    return i;
}

/*
 Funcion para inicializar nueva tabla de hash
 Return: La tabla de hash
*/
hash_table* ht_new() {
    hash_table* ht = malloc(sizeof(hash_table));
    ht->size = 512;
    ht->count = 0; 
    ht->items = calloc((size_t)ht->size, sizeof(element*)); 
    return ht; 
}

/*
 Funcion para eliminar elementos de la tabla
 Parametros:
        Element i*: Item a ser eliminado
*/
static void ht_del_element(element* i) {
    free(i->key);
    free(i->value);
    free(i);
}

/*
 Funcion para eliminar una tabla de hash
 Parametros:
        hash_table* ht: La tabla de hash
*/
void ht_del_hash_table(hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        element* item = ht->items[i];
        if (item != NULL) {
            ht_del_element(item);
        }
    }
    free(ht->items);
    free(ht);
}

/*
 Funcion para almacenar un caracter en la tabla
 Parametros:
        Const char* s: Caracter
 Return: El primer char.
*/
static int ht_hash(const char* s) {
    return s[0];
}

/*
 Funcion para aplicar doble hash si hay colisiones.
 Parametros:
        Const char* s: Clave
        Const int n: Tamano de la tabla de hash
        Const int count: Numero de intentos para almacenar un elemento con clave repetida
 Return: Posicion donde va a ser almacenada
*/
static int ht_get_hash(const char* s, const int n, const int count) {
    const int hash_a = ht_hash(s);
    const int hash_b = ht_hash(s);
    return (hash_a + (count * (hash_b + 1))) % n;
}

/*
 Inserta un elemento en la tabla de hash
 Parametros:
        hash_table* ht: Tabla de hash
        const char* key: Clave del elemento
        const char* value: Valor del elemento
 Return: Elemento insertado en la tabla de hash
*/
void hash_table_insert(hash_table* ht, const char* key, const char* value) {
    int a = (int)key[0];
    if (0<=a && a <= 32) {
        return;
    }
    if(97<=a && a<= 122){
        return;
    }
    element* item = ht_new_element(key, value);
    int position = ht_get_hash(item->key, ht->size, 0); 
    element* cur_item = ht->items[position];
    int i = 1;
    while (cur_item != NULL) {
        return; 
    } 
    ht->count++;
    ht->items[position] = item;
}

/*
 Busca un elemento en la tabla de hash
 Parametros:
        hash_table* ht: Tabla de hash
        const char* key: Clave del elemento
 Return: Valor del elemento
*/
char* hash_table_search(hash_table* ht, const char *key) {
    char* numeral = "#";
    char* ejemplo ="";
    int position = ht_get_hash(key, ht->size, 0);
    element* item = ht->items[position];
    int i = 1;
    if (ht->items[position]==NULL){
        return numeral;
    }
    return item->value;
}

/*
 Busca las claves de una tabla de hash que contengan elementos
 Parametros:
        hash_table* ht: Tabla de hash
 Return: Claves
*/
char * hash_table_keys(hash_table * ht) {
    char * keys = malloc(sizeof(char));
    int i = 0;
    int count = ht->count;
    element ** items = ht->items;
    while (count > 0) {
        if (*items != NULL) {
            keys[i] = *(*items)->key;
            i++;
            count--;
        }
        items++;
    }
    keys[i] = '\0';
    return keys;
}

/*
 Busca el valor de las claves de una tabla de hash que contengan elementos
 Parametros:
        hash_table* ht: Tabla de hash
 Return: Claves
*/
char * hash_table_keys_values(hash_table * ht) {
    char * value = malloc(sizeof(char));
    int i = 0;
    int count = ht->count;
    element ** items = ht->items;
    while (count > 0) {
        if (*items != NULL) {
            value[i] = *(*items)->value;
            i++;
            count--;
        }
        items++;
    }
    value[i] = '\0';
    return value;
}