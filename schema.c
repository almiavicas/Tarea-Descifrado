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
	sc->encryption = ht_new();
	if (sc->encryption == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		free(sc);
		return NULL;
	}
	sc->decryption = ht_new();
	if (sc->decryption == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		free(sc->encryption);
		free(sc);
		return NULL;
	}
	sc->date = date;
	sc->parent_date = -1;
	return sc;
}

// Recibe un esquema recien creado y define su encriptacion y decriptacion
// Pregunta al usuario si quiere hacer merge en caso de que sea posible
int build_schema(list_t * list, schema * sc, char * encrypted, char * decrypted) {
	if (strlen(encrypted) != strlen(decrypted)) {
		fprintf(stderr, "%s\n", err_message_dif_len);
		return 0;
	}
	char * enc_c = malloc(sizeof(char));
	char * dec_c = malloc(sizeof(char));
	int len = strlen(encrypted);
	while (len--) {
		enc_c[0] = encrypted[0];
		dec_c[0] = decrypted[0];
		hash_table_insert(sc->encryption, dec_c, enc_c);
		hash_table_insert(sc->decryption, enc_c, dec_c);
		encrypted++;
		decrypted++;
	}


	list_it * it = iterator(list);
	int is_prev_compatible = 0;
	int is_next_compatible = 0;
	schema * prev;
	schema * next;
	if (it->next != NULL && it->next->key == sc->date) {
		// Vemos si este esquema es compatible con su sucesor
		it_next(it);
		if (it->next == NULL) {
			return 1;
		}
		next = (schema *) it->next->value;
		is_next_compatible = is_schema_compatible(sc, next);
	} else {
		// Vemos si este esquema es compatible con su predecesor
		if (it->next == NULL) {
			// No hay mas nadie en la lista, no hay que verificar merge
			return 1;
		}
		while (it->next->next != NULL && it->next->next->key != sc->date) {
			it_next(it);
		}
		prev = (schema *) it->next->value;
		is_prev_compatible = is_schema_compatible(prev, sc);
		// Vemos si este esquema es compatible con su sucesor
		it_next(it);
		it_next(it);
		if (it->next != NULL) {
			next = (schema *) it->next->value;
			is_next_compatible = is_schema_compatible(sc, next);
		}
	}
	char * ans = malloc(sizeof(char));
	char * si = malloc(sizeof(char));
	si = "si";
	char * no = malloc(sizeof(char));
	no = "no";
	char * aux;
	if (is_prev_compatible) {
		aux = schema_print_date(prev->date);
		while (1) {
			printf("El esquema agregado es compatible con el esquema anterior de fecha %s.\n Desea unificar ambos esquemas en uno solo? (responda s/n): ", aux);
			scanf("%s", ans);
			if (strcmp(si, ans) == 0 || strcmp(no, ans) == 0) {
				if (strcmp(si, ans) == 0) {
					merge(list, prev, sc);
				}
				break;
			}
			else {
				printf("Debe ingresar \"si\" o \"no\"\n");
			}
		}
	}
	if (is_next_compatible) {
		aux = schema_print_date(next->date);
		while (1) {
			printf("El esquema agregado es compatible con el esquema siguiente de fecha %s.\n Desea unificar ambos esquemas en uno solo? (responda si/no): ", aux);
			scanf("%s", ans);
			if (strcmp(si, ans) == 0 || strcmp(no, ans) == 0) {
				if (strcmp(si, ans) == 0) {
					merge(list, next, sc);
				}
				break;
			}
			else {
				printf("Debe ingresar \"si\" o \"no\"\n");
			}
		}
	}
	free(enc_c);
	free(dec_c);
	free(ans);
	free(aux);
	return 1;
}

int is_schema_compatible(schema * prev, schema * next) {
	char * keys = hash_table_keys(next->encryption);

	//printf("Obtiene claves\n");
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
		return err_knf;
	}
	return translate(message, sc->encryption);
}

char * decrypt(list_t * list, int date, char * message) {
	schema * sc = schema_get_parent(list, date);
	if (sc == NULL) {
		fprintf(stderr, "%s\n", err_knf);
		return err_knf;
	}
	return translate(message, sc->decryption);
}

char* translate(char * message, hash_table * translate_to) {
	char * space = " ";
	char * numeral = "#";
	char * final;
	char * retornar = malloc(10000000);
	while (message != NULL) {
		char c = message[0];
		char *pChar = &c;
		if(c == 0){
			return retornar;
		}
		if ((int)c == 32 || c == '\t') {
			strcat(retornar, space);
		} else {
			final = hash_table_search(translate_to, pChar);
			if (c == '\0') {
				strcat(retornar, numeral);
				return retornar;
			} else {
				strcat(retornar,final);
			}
		}
		message++;
	}
}



int merge(list_t * list, schema * dest, schema * source) {
	if (dest->parent_date != -1) {
		printf("Parent date: %d\n", dest->parent_date);
		printf("Parent date: %d\n", source->parent_date);
		dest = list_get(list, dest->parent_date);
		return merge(list, dest, source);
	}
	else {

		source->parent_date = dest->date;
		// Keys returned here are the 

		char * keys = hash_table_keys(source->encryption);
		char * value;
		while (*keys != '\0') {
			value = hash_table_search(source->encryption, keys);
			if (value == NULL) {
				fprintf(stderr, "%s\n", err_knf);
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
	// Date format: yyyy/mm/dd
	char * year = malloc(sizeof(char));
	char * month = malloc(sizeof(char));
	char * day = malloc(sizeof(char));
	char * aux = malloc(sizeof(char));

	*day = '0' + (date % 10);
	date /= 10;
	*aux = '0' + (date % 10);
	strcat(aux, day);
	*day = *aux;
	date /= 10;

	*month = '0' + (date % 10);
	date /= 10;
	*aux = '0' + (date % 10);
	strcat(aux, month);
	*month = *aux;
	date /= 10;

	*year = '0' + (date % 10);
	date /= 10;
	*aux = '0' + (date % 10);
	strcat(aux, year);
	*year = *aux;
	date /= 10;
	*aux = '0' + (date % 10);
	strcat(aux, year);
	*year = *aux;
	date /= 10;
	*aux = '0' + (date % 10);
	strcat(aux, year);
	*year = *aux;

	strcat(aux, "/");
	strcat(aux, month);
	strcat(aux, "/");
	strcat(aux, day);
	free(year);
	free(month);
	free(day);
	return aux;
}

void schema_print(schema * sc) {

	if (sc == NULL){
		return;
	}
	printf("Schema pointer %p of date %d:\n\tParent date: %d\n\tEncryption:\n\t", sc, sc->date, sc->parent_date);

	char * keys = hash_table_keys(sc->encryption);
	char * value;
	printf("\t%s ", keys);

	printf("\n\t");

	keys = hash_table_keys_values(sc->encryption);
	printf("\t%s ", keys);

	
	printf("\n\tDecryption:\n\t");
	keys = hash_table_keys(sc->decryption);
	printf("\t%s\n\t", keys);
	keys = hash_table_keys_values(sc->decryption);
	printf("\t%s\n ", keys);
}

void schema_remove(schema *sc) {
	if (sc ==NULL){
		return ;
	}
	free(sc->encryption);
	free(sc->decryption);
	free(sc);
}
