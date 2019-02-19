#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "schema.h"
#include "hash_table.c"


schema * new_schema(int date) {
	schema * sc = malloc(sizeof(schema));
	if (sc == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		return NULL;
	}
	sc->encryption = malloc(sizeof(hash_table));
	if (sc->encryption == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		free(sc);
		return NULL;
	}
	sc->decryption = malloc(sizeof(hash_table));
	if (sc->decryption == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		free(sc->encryption);
		free(sc);
		return NULL;
	}
	sc->date = date;
	sc->date_parent = -1;
	return sc;
}

// Recibe un esquema recien creado y define su encriptacion y decriptacion
// Pregunta al usuario si quiere hacer merge en caso de que sea posible
int build_schema(list_t * list, schema * sc, char * encrypted, char * decripted) {
	if (strlen(encrypted) != strlen(decripted)) {
		fprintf(stderr, "%s\n", err_message_dif_len);
		return 0;
	}
	while (encrypted) {
		hash_table_insert(sc->encription, *decripted, *encrypted);
		hash_table_insert(sc->decription, *encrypted, *decripted);
		encrypted++;
		decripted++;
	}
	list_it * it = iterator(list);
	int is_prev_compatible : 1 = 0;
	int is_next_compatible : 1 = 0;
	if (it->next->key == sc->date) {
		// Vemos si este esquema es compatible con su sucesor
		it_next(it);
		schema * next = (schema *) it->next->value;
		is_next_compatible = is_schema_compatible(sc, next);
	} else {
		// Vemos si este esquema es compatible con su predecesor
		while (it->next->next != NULL && it->next->next->key != sc->date) {
			it_next(it);
		}
		schema * prev = (schema *) it->next->value;
		is_prev_compatible = is_schema_compatible(prev, sc);
		// Vemos si este esquema es compatible con su sucesor
		it_next(it);
		it_next(it);
		schema * next = (schema *) it->next->value;
		if (next != NULL) {
			is_next_compatible = is_schema_compatible(sc, next);
		}
	}
	
	if (is_prev_compatible) {
		while () {
			printf("El esquema agregado es compatible con el esquema anterior de fecha %s.\n Desea unificar ambos esquemas en uno solo?", schema_print_date(prev));
		}
	}
	if (is_next_compatible) {

	}
	return 1;
}

int is_schema_compatible(schema * prev, schema * next) {

}

schema * schema_get_parent(list_t * list, int date) {
	schema * sc = (schema *) list_get(list, date);
	while (sc != NULL && sc->parent_date != -1) {
		sc = (schema *) list_get(list, sc->parent_date);
	}
	return sc;
}

char * encrypt(list_t * list, int date, char * message) {
	schema * sc = schema_get_parent(list, date);
	if (sc == NULL) {
		fprintf(stderr, "%s\n", err_knf);
		return NULL;
	}
	return translate(message, sc->encryption);
}

char * decrypt(list_t * list, int date, char * message) {
	schema * sc = schema_get_parent(list, date);
	if (sc == NULL) {
		fprintf(stderr, "%s\n", err_knf);
		return NULL;
	}
	return translate(message, sc->decryption);
}

char * translate(char * message, hash_table * translate_to) {
	char * result = "";
	while (message != NULL) {
		char * c = *message;
		if (*c == ' ' || *c == '\t') {
			result = result + (*c);
		} else {
			c = hash_table_search(translate_to, c);
			if (c == NULL) {
				result = result + "#";
			} else {
				result = result + (*c);
			}
		}
		message++;
	}
	return result;
}
int merge(schema * dest, schema * source) {
	source->date_parent = dest->date;
}
void schema_print(schema * sc);
int schema_remove(schema *sc);