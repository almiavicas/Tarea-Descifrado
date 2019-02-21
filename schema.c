#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schema.h"


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
int build_schema(list_t * list, schema * sc, char * encrypted, char * decrypted) {
	if (strlen(encrypted) != strlen(decrypted)) {
		fprintf(stderr, "%s\n", err_message_dif_len);
		return 0;
	}
	while (encrypted) {
		hash_table_insert(sc->encryption, *decrypted, *encrypted);
		hash_table_insert(sc->decryption, *encrypted, *decrypted);
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
	char * ans;
	if (is_prev_compatible) {
		while (1) {
			printf("El esquema agregado es compatible con el esquema anterior de fecha %s.\n Desea unificar ambos esquemas en uno solo? (responda si/no): ", schema_print_date(prev));
			scanf("%s", ans);
			if (ans != "si" && ans != "no") {
				printf("Debe ingresar \"si\" o \"no\"\n");
			}
			else {
				if (ans == "si") {
					merge(list, prev, sc);
				}
				break;
			}
		}
	}
	if (is_next_compatible) {
		while (1) {
			printf("El esquema agregado es compatible con el esquema siguiente de fecha %s.\n Desea unificar ambos esquemas en uno solo? (responda si/no): ", schema_print_date(prev));
			scanf("%s", ans);
			if (ans != "si" && ans != "no") {
				printf("Debe ingresar \"si\" o \"no\"\n");
			}
			else {
				if (ans == "si") {
					merge(list, sc, next);
				}
				break;
			}
		}
	}
	return 1;
}

int is_schema_compatible(schema * prev, schema * next) {
	char * keys = hash_table_keys(next->encryption);
	char * prev_value;
	char * next_value;
	while (*keys != '\0') {
		prev_value = hash_table_search(prev->encryption, keys);
		if (prev_value != NULL) {
			next_value = hash_table_search(next->encryption, keys);
			if (* prev_value != * next_value) {
				return 0;
			}
		}
		keys++;
	}
	return 1;
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

int merge(list_t * list, schema * dest, schema * source) {
	if (dest->date_parent != -1) {
		dest = get(list, dest->date_parent);
		return merge(list, dest, source);
	}
	else {
		source->date_parent = dest->date;
		// Keys returned here are the 
		char * keys = hash_table_keys(source->encryption);
		char * value;
		while (*keys != '\0') {
			value = hash_table_search(source->encryption, *keys);
			if (value == NULL) {
				fprintf(err, "%s\n", err_knf);
				return 0;
			}
			hash_table_insert(dest->encryption, keys, value);
			hash_table_insert(dest->decryption, value, keys);
			keys++;
		}
		return 1;
	}
}

char * schema_print_date(int date) {

}

void schema_print(schema * sc) {
	printf("Schema of date %s:\n\tParent date: %s\n\t Encryption:\n\t", schema_print_date(sc->date), schema_print_date(sc->parent_date));
	char * keys = hash_table_keys(sc->encryption);
	char * value;
	while (*keys != '\0') {
		printf("%s ", keys);
		keys++;
	}
	printf("\n\t");
	keys = hash_table_keys(sc->encryption);
	while (*keys != '\0') {
		value = hash_table_search(sc->encryption, keys);
		printf("%s ", value);
		keys++;
	}
	printf("\nDecryption:\n\t");
	keys = hash_table_keys(sc->decryption);
	while (*keys != '\0') {
		printf("%s ", keys);
		keys++;
	}
	printf("\n\t");
	keys = hash_table_keys(sc->decryption);
	while (*keys != '\0') {
		value = hash_table_search(sc->decryption, keys);
		printf("%s ", value);
		keys++;
	}
}
int schema_remove(schema *sc) {
	free(sc->encryption);
	free(sc->decryption);
	free(sc);
}
