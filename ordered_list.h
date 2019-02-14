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
	struct item * prev;
};

struct ordered_list {
	struct item * begin;
	int size;
	void *(*get) (struct ordered_list * l, int key);
	int (*insert) (struct ordered_list * l, int key, void * value);
	int (*remove) (struct ordered_list * l, int key);
	int (*is_empty) (struct ordered_list * l);
	struct item *(*iterator) (struct ordered_list * l);
};

struct ordered_list * new_ordered_list(void);
void * get(struct ordered_list * l, int key);
int insert(struct ordered_list * l, int key, void * value);
int l_remove(struct ordered_list * l, int key);
int is_empty(struct ordered_list * l);

struct item * iterator(struct ordered_list * l);
void * next(struct item * it);
int has_next(struct item * it);