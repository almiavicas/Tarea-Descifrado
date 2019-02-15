#include <stdio.h>

char err_mem[];
char err_emp[];
char err_knf[];
char err_ful[];
char err_rep[];

struct item {
	int key;
	void * value;
	struct item * next;
};

struct ordered_list {
	struct item * begin;
	int size;
};

struct list_iterator {
	struct item * next;
};

struct ordered_list * new_ordered_list(void);
void * list_get(struct ordered_list * l, int key);
int list_insert(struct ordered_list * l, int key, void * value);
int list_remove(struct ordered_list * l, int key);
int list_is_empty(struct ordered_list * l);

struct list_iterator * iterator(struct ordered_list * l);
void * it_next(struct list_iterator * it);
int it_has_next(struct list_iterator * it);

void item_info(struct item * it);