#include <stdio.h>
#include <stdlib.h> // Included to use malloc
#include "tree_set.h"

char err_mem[] = "not enought memory";
char err_emp[] = "set is empty";
char err_knf[] = "key not found";
char err_ful[] = "set is full";
char err_rep[] = "element key is repeated";

struct tree_set * new_tree_set(int item_size, int max_size) {
	struct tree_set *set = malloc(sizeof(struct tree_set));
	if (set == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		perror("Error: ");
		return NULL;
	}
	int size = 2;
	while (size <= max_size) size <<= 1;
	size <<= 1; // Need an extra height to deal with insert_fixup
	set->begin = malloc(sizeof(struct key_value) * size);
	if (set->begin == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		perror("Error: ");
		free(set);
		return NULL;	
	}
	set->begin->color = BLACK; // begin is going to be used as the null node.
	set->begin->parent = set->begin;
	set->begin->left = set->begin + 1;
	set->begin->right = set->begin + 1;
	set->size = 0;
	set->item_size = item_size;
	set->max_size = size/2;
	set->is_empty = &is_empty;
	set->get = &get;
	set->insert = &insert;
	set->remove = &rb_remove;
	build_tree(set, set->begin + 1);
	return set;
}


static void build_tree(struct tree_set * set, struct key_value * node) {
	if (node == set->begin) return;
	int id = node - set->begin;
	node->parent = set->begin + id/2;
	node->left = set->begin + left_child(set, id);
	node->right = set->begin + right_child(set, id);
	build_tree(set, node->left);
	build_tree(set, node->right);
}

static int left_child(struct tree_set * set, int n) {
	n <<= 1;
	return n > set->max_size ? 0 : n;
}

static int right_child(struct tree_set * set, int n) {
	n = (n << 1) | 1;
	return n > set->max_size ? 0 : n;
}

static int is_empty(struct tree_set *set) {
	return set->size == 0;
}

static void * get(struct tree_set *set, int key) {
	if (is_empty(set)) {
		fprintf(stderr, "%s\n", err_emp);
		return NULL;
	}
	struct key_value * x = set->begin + 1;
	while (x != set->begin) {
		if (x->key == key) {
			return x->value;
		}
		else if (x->key < key) {
			x = x->right;
		}
		else {
			x = x->left;
		}
	}
	fprintf(stderr, "%s: %d\n", err_knf, key);
	return NULL;
}

static void resize(struct tree_set * set, int max_size) {
	int size = 2;
	while (size <=max_size) size <<=1;
	size<<=1; // Needed to deal with insert_fixup
	if (size/2 == set->max_size) return;
	struct key_value * new_begin = malloc(sizeof(struct key_value) * size);
	if (new_begin == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		return;
	}
	int old_size = set->max_size;
	set->max_size = size/2;
	struct key_value * it = new_begin;
	struct key_value * old_begin = set->begin;
	while (it-new_begin <= max_size && old_begin-set->begin <= old_size) {
		it->left = old_begin->left;
		it->right = old_begin->right;
		it->parent = old_begin->parent;
		it->key = old_begin->key;
		it->value = old_begin->value;
		it++;
		old_begin++;
	}
	free(set->begin);
	set->begin = new_begin;
}

static int insert(struct tree_set * set, int key, void * value) {
	struct key_value * y = set->begin; // null node
	struct key_value * x = y + 1; // root
	while (x != set->begin) {
		y = x;
		if (key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	if (y->parent == set->begin) {
		x = set->begin+1;
		x->key = key;
		x->value = value;
	}
	else if (key < y->key) {
		x = y->left;
		x->key = key;
		x->value = value;
	}
	else {
		x = y->right;
		x->key = key;
		x->value = value;
	}
	x->left = set->begin;
	x->right = set->begin;
	x->color = RED;
	insert_fixup(set, x);
	return 1;
}

static void insert_fixup(struct tree_set *set, struct key_value * node) {
	struct key_value * y;
	while (node->parent->color == RED) {
		if (node->parent == node->parent->parent->left) {
			y = node->parent->parent->right;
			if (y->color == RED) {
				node->parent->color = BLACK;
				y->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->right) {
					node = node->parent;
					left_rotate(set, node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				right_rotate(set, node->parent->parent);
			}
		}
		else {
			y = node->parent->parent->left;
			if (y->color == RED) {
				node->parent->color = BLACK;
				y->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->left) {
					node = node->parent;
					right_rotate(set, node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				left_rotate(set, node->parent->parent);
			}
		}
	}
	(set->begin + 1)->color = BLACK;
}

static int rb_remove(struct tree_set * set, int key) {

	return 0;
}

static void transplant(struct tree_set * set, struct key_value * u, struct key_value * v) {

}


static void left_rotate(struct tree_set *set, struct key_value * node) {
	struct key_value * y = node->right;
	node->right = y->left;
	if (y->left != set->begin) {
		y->left->parent = node;
	}
	y->parent = node->parent;
	if (node->parent == set->begin) {
		copy(y, set->begin+1);
	}
	else if (node == node->parent->left) {
		node->parent->left = y;
	}
	else {
		node->parent->right = y;
	}
	y->left = node;
	node->parent = y;
}

static void right_rotate(struct tree_set *set, struct key_value * node) {
	struct key_value * y = node->left;
	node->left = y->right;
	if (y->right != set->begin) {
		y->left->parent = node;
	}
	y->parent = node->parent;
	if (node->parent == set->begin) {
		copy(y, set->begin+1);
	}
	else if (node == node->parent->right) {
		node->parent->right = y;
	}
	else {
		node->parent->left = y;
	}
	y->right = node;
	node->parent = y;
}

static void copy(struct key_value * from, struct key_value * to) {
	to->parent = from->parent;
	to->left = from->left;
	to->right = from->right;
	to->key = from->key;
	to->value = from->value;
}