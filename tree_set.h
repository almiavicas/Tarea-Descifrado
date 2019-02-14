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
	struct key_value * null;
	struct key_value * root;
	int item_size;
	int size;
};

struct tree_set * new_tree_set(void);

static int is_empty(struct tree_set *set);
static int is_key(struct tree_set *set, int key);
static void * get(struct tree_set *set, int key);
static int * keys(struct tree_set *set);
static int insert(struct tree_set *set, int key, void * value);
static void insert_fixup(struct tree_set *set, struct key_value * node);
static int rb_remove(struct tree_set * set, int key);
static void rb_remove_fixup(struct tree_set * set, struct key_value * node);
static void transplant(struct tree_set * set, struct key_value * u, struct key_value * v);
static struct key_value * minimum(struct tree_set * set, struct key_value * node);
static struct key_value * maximum(struct tree_set * set, struct key_value * node);
static void left_rotate(struct tree_set *set, struct key_value * node);
static void right_rotate(struct tree_set *set, struct key_value * node);
static void tree_info(struct tree_set *set);
static void recursive_node_info(struct tree_set * set, struct key_value * node);
static void node_info(struct key_value * node);