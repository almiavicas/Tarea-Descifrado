#include <stdio.h>
#include <stdlib.h> // Included to use malloc
#include "ordered_set.h"

char err_mem[] = "not enought memory";
char err_emp[] = "set is empty";
char err_knf[] = "key not found";
char err_ful[] = "set is full";
char err_rep[] = "element key is repeated";

struct ordered_set * new_ordered_set(int item_size, int size) {
	struct ordered_set *set = malloc(sizeof(struct ordered_set));
	if (set == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		perror("Error: ");
		return NULL;
	}
	set->begin = malloc(sizeof(struct key_value) * size);
	if (set->begin == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		perror("Error: ");
		return NULL;	
	}
	set->end = set->begin;
	set->size = size;
	set->item_size = item_size;
	set->is_empty = &is_empty;
	set->get = &get;
	set->resize = &resize;
	set->insert = &insert;
	return set;
}

static int is_empty(struct ordered_set *set) {
	return set->begin == set->end;
}

static void * get(struct ordered_set *set, int key) {
	if (is_empty(set)) {
		fprintf(stderr, "%s\n", err_emp);
		return NULL;
	}
	struct key_value * left = set->begin;
	struct key_value * right = set->end;
	struct key_value * mid;
	while (left < right) {
		int dist = right - left;
		mid = left + (dist / 2);
		if (mid->key < key) {
			left = mid + 1;
		}
		else if (mid->key > key) {
			right = mid;
		}
		else break;
	}
	if (mid == NULL || mid->key != key) {
		fprintf(stderr, "%s: %d\n", err_knf, key);
		return NULL;
	}
	return mid->value;
}

static void resize(struct ordered_set * set, int size) {
	struct key_value * new_begin = malloc(sizeof(struct key_value) * size);
	if (new_begin == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		return;
	}
	struct key_value * it = new_begin;
	struct key_value * old_begin = set->begin;
	while ((old_begin < set->end) && (it - new_begin < size)) {
		it->key = old_begin->key;
		it->value = old_begin->value;
		it++;
		old_begin++;
	}
	free(set->begin);
	set->begin = new_begin;
	set->end = it;
	set->size = size;
}

static int insert(struct ordered_set * set, int key, void * value) {
	if (set->end - set->begin == set->size) {
		fprintf(stderr, "%s\n", err_ful);
		return 0;
	}
	struct key_value *left = set->begin;
	struct key_value *mid = left;
	struct key_value *right = set->end;
	while (left < right) {
		int dist = right - left;
		mid = left + (dist / 2);
		if (mid->key < key) {
			left = mid + 1;
		}
		else if (mid->key > key) {
			right = mid;
		}
		else break;
	}
	if (mid->key == key) {
		fprintf(stderr, "%s\n", err_rep);
		return 0;
	}
	struct key_value *it = set->end;
	while (mid < it) {
		it--;
		(it+1)->key = it->key;
		(it+1)->value = it->value;
	}
	mid->key = key;
	mid->value = value;
	set->end++;
	return 1;
}


