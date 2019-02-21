#include <stdio.h>

// Pares de clave y valor
// Key: Clave
// Value: Valor
typedef struct {
    char* key;
    char* value;
} element;

// Almacenamiento de punteros a elementos
// Size: Tamaño de la tabla de hash
// Count: Elementos en la tabla de hash
// Element: Apuntador a un apuntador de elementos
typedef struct {
    int size;
	int count;
    element** items;
} hash_table;

// Insertar un elemento
void hash_table_insert(hash_table* ht, const char* key, const char* value);

// Buscar un elemento
char* hash_table_search(hash_table* ht, const char* key);

// Eliminar un elemento
void hash_table_delete(hash_table* h, const char* key);

char * hash_table_keys(hash_table * ht);