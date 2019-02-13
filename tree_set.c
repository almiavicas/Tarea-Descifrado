#include <stdio.h>
#include <stdlib.h> // Included to use malloc
#include "tree_set.h"

char err_mem[] = "not enought memory";
char err_emp[] = "set is empty";
char err_knf[] = "key not found";
char err_ful[] = "set is full";
char err_rep[] = "element key is repeated";

struct tree_set * new_tree_set() {
	struct tree_set *set = malloc(sizeof(struct tree_set));
	if (set == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		perror("Error: ");
		return NULL;
	}
	set->null = malloc(sizeof(struct key_value));
	if (set->null == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		perror("Error: ");
		free(set);
		return NULL;
	}
	set->null->color = BLACK;
	set->null->parent = set->null;
	set->null->left = set->null;
	set->null->right = set->null;
	// printf("null ");
	// node_info(set->null);
	set->root = set->null;
	set->size = 0;
	set->is_empty = &is_empty;
	set->get = &get;
	set->insert = &insert;
	set->remove = &rb_remove;

	return set;
}

static int is_empty(struct tree_set *set) {
	return set->size == 0;
}

static void * get(struct tree_set *set, int key) {
	if (is_empty(set)) {
		fprintf(stderr, "%s\n", err_emp);
		return NULL;
	}
	struct key_value * x = set->root;
	while (x != set->null) {
		// node_info(x);
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

static int insert(struct tree_set * set, int key, void * value) {
	struct key_value * node = malloc(sizeof(struct key_value));
	if (node == NULL) {
		fprintf(stderr, "%s\n", err_mem);
		return 0;
	}
	node->key = key;
	node->value = value;
	struct key_value * y = set->null;
	struct key_value * x = set->root;
	while (x != set->null) {
		y = x;
		if (key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	node->parent = y;
	if (node->parent == set->null) {
		set->root = node;
	}
	else if (key < y->key) {
		y->left = node;
	}
	else {
		y->right = node;
	}
	node->left = set->null;
	node->right = set->null;
	node->color = RED;
	set->size++;
	insert_fixup(set, node);
	// node_info(node);
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
	set->root->color = BLACK;
}

static int rb_remove(struct tree_set * set, int key) {
	if (is_empty(set)) {
		fprintf(stderr, "%s\n", err_emp);
		return 0;
	}
	struct key_value * z = set->root;
	while (z != set->null && z->key != key) {
		if (z->key < key) {
			z = z->right;
		}
		else {
			z = z->left;
		}
	}
	if (z->key != key) {
		fprintf(stderr, "%s: %d\n", err_knf, key);
		return 0;
	}
	int original_color = z->color;
	struct key_value * x;
	if (z->left == set->null) {
		x = z->right;
		transplant(set, z, z->right);
	}
	else if (z->right == set->null) {
		x = z->left;
		transplant(set, z, z->left);
	}
	else {
		struct key_value * y = minimum(set, z->right);
		original_color = y->color;
		x = y->right;

		if (y->parent == z) {
			x->parent = y;
		}
		else {
			transplant(set, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(set, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (original_color == BLACK) {
		rb_remove_fixup(set, x);
	}
}

static void rb_remove_fixup(struct tree_set * set, struct key_value * x) {
	while (x != set->root && x->color == BLACK) {
		if (x == x->parent->left) {
			struct key_value * w = x->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate(set, x->parent);
				w = x->parent->right;
			}

			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					right_rotate(set, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				left_rotate(set, x->parent);
				x = set->root;
			}
		}
		else {
			struct key_value * w = x->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				right_rotate(set, x->parent);
				w = x->parent->left;
			}

			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					left_rotate(set, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				right_rotate(set, x->parent);
				x = set->root;
			}
		}
	}
	x->color = BLACK;
}

static void transplant(struct tree_set * set, struct key_value * u, struct key_value * v) {
	if (u->parent == set->null) {
		set->root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

static struct key_value * minimum(struct tree_set * set, struct key_value * node) {
	struct key_value * x = node;
	while (x != set->null) {
		node = x;
		x = x->left;
	}
	return node;
}

static struct key_value * maximum(struct tree_set * set, struct key_value * node) {
	struct key_value * x = node;
	while (x != set->null) {
		node = x;
		x = x->right;
	}
	return node;
}

static void left_rotate(struct tree_set *set, struct key_value * node) {
	struct key_value * y = node->right;
	node->right = y->left;
	if (y->left != set->null) {
		y->left->parent = node;
	}
	y->parent = node->parent;
	if (node->parent == set->null) {
		set->root = y;
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
	if (y->right != set->null) {
		y->left->parent = node;
	}
	y->parent = node->parent;
	if (node->parent == set->null) {
		set->root = y;
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

static void tree_info(struct tree_set * set) {
	struct key_value * node = set->root;
	recursive_node_info(set, node);
}

static void recursive_node_info(struct tree_set * set, struct key_value * node) {
	if (node != set->null) {
		node_info(node);
		recursive_node_info(set, node->left);
		recursive_node_info(set, node->right);
	}
}

static void node_info(struct key_value * node) {
	printf("node info: \n\tnode pointer: %p\n\tnode key: %d\n\tnode value pointer: %p\n\tnode parent: %p\n\tnode left: %p\n\tnode right: %p\n", node, node->key, node->value, node->parent, node->left, node->right);
}