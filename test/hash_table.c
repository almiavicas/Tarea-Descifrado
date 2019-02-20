#include <stdio.h>
#include <stdlib.h>
#include "../hash_table.c"

struct item {
	char * key;
	char * value;
};

hash_table *ht;
item *i1;
item *i2;
item *i3;

int main()
{
	/* code */
	ht = ht_new();
	i1 = malloc(sizeof(struct item));
	i2 = malloc(sizeof(struct item));
	i3 = malloc(sizeof(struct item));
	i1->key = "A";
	i1->value = "H";
	i2->key = "B";
	i2->value = "J";
	i3->key = "f";
	i3->value = "T";
	printf("Empieza a agregar a la tabla\n");
	hash_table_insert(ht, i1->key, i1->value);
	hash_table_insert(ht, i2->key, i2->value);
	hash_table_insert(ht, i3->key, i3->value);

	printf ("Termina de agregar a la tabla\n");

	char * c;
	c = hash_table_search(ht, i1->key);
	printf("%s -> %s\n", i1->key, c);
	c = hash_table_search(ht, i2->key);
	printf("%s -> %s\n", i2->key, c);
	// c = hash_table_search(ht, i3->key);
	// printf("%s -> %s\n", i3->key, c);
	return 0;
}