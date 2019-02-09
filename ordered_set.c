#include <stdio.h>
#include "ordered_set.h"

err_mem = "no available memory";

struct ordered_set * new_ordered_set(int size) {
	struct ordered_set *set = malloc(sizeof(struct ordered_set) * size);
	if (set == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		perror("Error: ");
		return NULL;
	}
	set->is_empty = is_empty;
	set->get = get;
	set->resize = resize;
	set->insert = insert;
	set->compare = compare;
	return set;
}

int is_empty(void);
void * get(int key);
void resize(int size);
void insert(int key, void * value);
int compare(int key1, int key2);


