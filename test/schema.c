#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schema.h"

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
    ht->size = 28; // Va a tener tama;o 28.
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
static int ht_hash(const char* s, const int m) {
    int hash = 0;
    int letter_as_int = (int)s[0]; // Transforma un caracter a ASCII

    // De la A a la Z
    if(65<= letter_as_int <= 90){
        hash = letter_as_int - 65;
    }

    // Caso ,
    if(letter_as_int == 44){
        printf("Error!\n");
        hash = 26;
        printf("Hash final: %i\n", hash);
    }

    // Caso !
    if(letter_as_int == 33){
        hash = 27;
    }

    return hash;
}

// Doble hash para la colisiones. En este caso, n es 28 y count es el numero de intentos.
static int ht_get_hash(const char* s, const int n, const int count) {
    const int hash_a = ht_hash(s,n);
    const int hash_b = ht_hash(s,n);
    return (hash_a + (count * (hash_b + 1))) % n;
}

// Insertar un elemento en la tabla de hash
// ht: Tabla de hash
// Key: Clave
// Value: Valor
void hash_table_insert(hash_table* ht, const char* key, const char* value) {
    element* item = ht_new_element(key, value); //Inicializo el elemento con su valor y clave
    int position = ht_get_hash(item->key, ht->size, 0); // Colisiones
    element* cur_item = ht->items[position]; // Obtiene la posicion del elemento de la estructura a la que apunta la HT.
    int i = 1;
    // General
    while (cur_item != NULL) {
        position = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[position];
        i++;
    } 
    ht->count++;
    ht->items[position] = item;
}

// Buscar un elemento en la tabla
// ht: Hash Table
// Key: Clave
char* hash_table_search(hash_table* ht, const char* key) {
    int position = ht_get_hash(key, ht->size, 0);
    element* item = ht->items[position];
    int i = 1;
    // Verficamos si la clave del elemento coincide con al clave que estamos buscando.
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
        position = ht_get_hash(key, ht->size, i);
        item = ht->items[position];
        i++;
    } 
    return NULL;
}


int main() {
    hash_table* ht = ht_new();
    ht_del_hash_table(ht);
}