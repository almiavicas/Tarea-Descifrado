#include <stdio.h>
#include "hash_table.c"
#include "ordered_list.c"

typedef struct {
	// Id of the parent schema
	int parent_date;
	// Id of the schema as a date
	int date;
	// schema that links decrypted characters to encrypted characters
	hash_table * encryption;
	// schema that links encrypted characters to decrypted characters
	hash_table * decryption;
} schema;

schema * new_schema(int date);
int build_schema(list_t * list, schema * sc, char * encrypted, char * decripted);
int is_schema_compatible(schema * prev, schema * next);
schema * schema_get_parent(list_t * list, int date);
char * translate(char * message, hash_table * translate_to);
char * encrypt(list_t * list, int date, char * message);
char * decrypt(list_t * list, int date, char * message);
int merge(schema * dest, schema * source);
void schema_print(schema * sc);
int schema_remove(schema *sc);
int is_character_valid(char * c);