#include <stdio.h>
#include <stdlib.h>
#include "ordered_list.h"

typedef struct ordered_list list;

char err_mem[] = "not enought memory";
char err_emp[] = "set is empty";
char err_knf[] = "key not found";
char err_ful[] = "set is full";
char err_rep[] = "element key is repeated";

list * new_ordered_list() {
	list * l = malloc(sizeof(list));
	if (l == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		perror("Error :");
		return NULL;
	}
	l->size = 0;
	return l;
};

void * get(list * l, int key) {
	if (is_empty(l)) {
		fprintf(stderr, "%s\n", err_emp);
		return NULL;
	}
	struct item * it = l->begin;
	while (it != NULL) { 
		if (it->key == key) {
			return it->value;
		}
		it = it->next;
	}
	if (it == NULL) {
		fprintf(stderr, "%s: %d\n", err_knf, key);
		return NULL;
	}
	return it->value;
}

int insert(list * l, int key, void * value) {
	struct item * new_item = malloc(sizeof(struct item));
	if (new_item == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		return 0;
	}
	new_item->key = key;
	new_item->value = value;
	if (is_empty(l)) {
		l->begin = new_item;
	}
	else {
		if (key < l->begin->key) {
			new_item->next = l->begin;
			l->begin->prev = new_item;
			l->begin = new_item;
		}
		else {
			struct item * it = l->begin;
			while (it->key <= key && it->next != NULL) {
				if (it->key == key) {
					fprintf(stderr, "%s\n", err_rep);
					return 0;
				}
				it = it->next;
			}
			it->prev->next = new_item;
			new_item->prev = it->prev;
			it->prev = new_item;
			new_item->next = it;
		}
	}
	l->size++;
	return 1;
}

int l_remove(list * l, int key) {
	if (is_empty(l)) {
		fprintf(stderr, "%s\n", err_emp);
		return 0;
	}
	struct item * it = l->begin;
	while (it != NULL || it->key != key) {
		it = it->next;
	}
	if (it == NULL) {
		fprintf(stderr, "%s\n", err_knf);
		return 0;
	}
	if (it->prev != NULL) {
		it->prev->next = it->next;
	}
	if (it->next != NULL) {
		it->next->prev = it->prev;
	}
	free(it->value);
	free(it);
	l->size--;
	return 1;
}

int is_empty(list * l) {
	return l->size == 0;
}

struct item * iterator(list * l) {
	return l->begin;
}

void * next(struct item * it) {
	void * value = it->value;
	it = it->next;
	return value;
}

int has_next(struct item * it) {
	return it->next != NULL;
}