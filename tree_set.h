/** RED-BLACK tree set with insert operations */

#define BLACK 0
#define RED 1

char err_mem[];
char err_emp[];
char err_knf[];
char err_ful[];
char err_rep[];

/** Represents a node inside the tree */
struct key_value {
	int key;
	void * value;
	struct key_value * left;
	struct key_value * right;
	struct key_value * parent;
	unsigned int color : 1;
};

struct tree_set {
	struct key_value * begin;
	int item_size;
	int size;
	int max_size;
	int (*is_empty) (struct tree_set *set);
	void *(*get) (struct tree_set *set, int key);
	void (*resize) (struct tree_set *set, int size);
	int (*insert) (struct tree_set *set, int key, void (*value));
	int (*remove) (struct tree_set * set, int key);
};

struct tree_set * new_tree_set(int item_size, int size);

static void build_tree(struct tree_set * set, struct key_value * node);
static int left_child(struct tree_set * set, int n);
static int right_child(struct tree_set * set, int n);
static int is_empty(struct tree_set *set);
static void * get(struct tree_set *set, int key);
static int * keys(struct tree_set *set);
static void resize(struct tree_set *set, int size);
static int insert(struct tree_set *set, int key, void * value);
static void insert_fixup(struct tree_set *set, struct key_value * node);
static int rb_remove(struct tree_set * set, int key);
static void transplant(struct tree_set * set, struct key_value * u, struct key_value * v);
static void left_rotate(struct tree_set *set, struct key_value * node);
static void right_rotate(struct tree_set *set, struct key_value * node);
static void copy(struct key_value * from, struct key_value * to);