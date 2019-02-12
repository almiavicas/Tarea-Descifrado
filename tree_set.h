/** Ordered set with insert operations */

char err_mem[];
char err_emp[];
char err_knf[];
char err_ful[];
char err_rep[];

/** Represents an item inside the set */
struct key_value {
	int key;
	void * value;
};

struct ordered_set {
	struct key_value * begin;
	struct key_value * end;
	int item_size;
	int size;
	int (*is_empty) (struct ordered_set *set);
	void *(*get) (struct ordered_set *set, int key);
	void (*resize) (struct ordered_set *set, int size);
	int (*insert) (struct ordered_set *set, int key, void (*value));
};

struct ordered_set * new_ordered_set(int item_size, int size);

static int is_empty(struct ordered_set *set);
static void * get(struct ordered_set *set, int key);
static void resize(struct ordered_set *set, int size);
static int insert(struct ordered_set *set, int key, void * value);