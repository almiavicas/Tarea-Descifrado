#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

typedef element item;

// Funcion para inicializar los elementos de la tabla de hash
// Const char* k: Apuntador de clave
// Const char* v: Apuntador de valor
static element* ht_new_element(const char* k, const char* v) {
    element* i = malloc(sizeof(element)); // Reservo espacio en la memoria
    i->key = strdup(k); //Guardo una copia en la memoria que acabamos de reservar
    i->value = strdup(v);
    return i; // Se retorna el elemento
}

// Funcion para nicializar nueva tabla de hash
hash_table* ht_new() {
    hash_table* ht = malloc(sizeof(hash_table)); // Reservo espacio en la memoria
    ht->size = 512; // Va a tener tama;o 512.
    ht->count = 0; // Por ahora no tiene elementos
    ht->items = calloc((size_t)ht->size, sizeof(element*)); // Lleno todo con 0
    return ht; // Se retorna la tabla de hash
}


// Funcion para eliminar elementos de la tabla
static void ht_del_element(element* i) {
    free(i->key); //Se libera la clave, luego el valor y por ultimo el elemento
    free(i->value);
    free(i);
}


// Funcion para eliminar una tabla. Se elimina elemento por elemento y luego libero la memoria
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


// Funcion de hash para almacenar un caracter en la tabla. Char *s es el caracter y m es 28.
static int ht_hash(const char* s) {
    return s[0];
}

// Doble hash para la colisiones. En este caso, n es 28 y count es el numero de intentos.
static int ht_get_hash(const char* s, const int n, const int count) {
    const int hash_a = ht_hash(s);
    const int hash_b = ht_hash(s);
    //printf("%d %c\n", hash_a, hash_a);
    return (hash_a + (count * (hash_b + 1))) % n;
}

// Insertar un elemento en la tabla de hash
// ht: Tabla de hash
// Key: Clave
// Value: Valor
void hash_table_insert(hash_table* ht, const char* key, const char* value) {
    // Check if the key is alredy added in the table

    int a = (int)key[0];
    if (0<=a && a <= 32) {
        // fprintf(stderr, "%s%d\n", "Caracter invalido 1: ", a);
        return;
    }
    if(97<=a && a<= 122){
        // fprintf(stderr, "%s%d\n", "Caracter invalido 2: ", a);
        return;
    }
   

    element* item = ht_new_element(key, value); //Inicializo el elemento con su valor y clave
    //printf("..\n");
    int position = ht_get_hash(item->key, ht->size, 0); // Colisiones
 
    element* cur_item = ht->items[position]; // Obtiene la posicion del elemento de la estructura a la que apunta la HT.

    //printf("este es %i\n", cur_item);
    int i = 1;
    // General
    while (cur_item != NULL) {
        //printf("%c", cur_item);
        return;
  
    } 
    ht->count++;
    ht->items[position] = item;
}

// Buscar un elemento en la tabla
// ht: Hash Table
// Key: Clave.. UNA
char* hash_table_search(hash_table* ht, const char *key) {
    //printf("entro");
    char* numeral = "#";
    char* ejemplo ="";
    int position = ht_get_hash(key, ht->size, 0);
    //printf("entro");
    //printf("count>%i\n", ht->count);
    element* item = ht->items[position];
    //printf("%p\n", item);
    
    //printf("item referenciado\n");
    int i = 1;
    //printf("key: %c\n", key);
    // Verficamos si la clave del elemento coincide con al clave que estamos buscando.
    if (ht->items[position]==NULL){
        return numeral;
    }
    return item->value;
    
    /*
    while (item != NULL) {

        //printf("item referenciado\n");
        if (strcmp(item->key, key) == 0) {

            return item->value;
        }

        position = ht_get_hash(key, ht->size, i);

        item = ht->items[position];

        i++;
    } 
    printf("entro");
    //printf("item referenciado\n");
    return item->value;
    // decia retunr null
    */
}

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