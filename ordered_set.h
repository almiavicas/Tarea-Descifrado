/** Ordered set with insert operations */

char[] err_mem;

struct ordered_set {
	int * begin;
	int * end;
	int size;
	void (*is_empty) (void);
	void (*get) (int key);
	void (*resize) (int size);
	void (*insert) (int key, void (*value));
	void (*compare) (int key1, int key2);

	/** Represents an item inside the set */
	struct item {
		int key;
		void * value;
	};
};

struct ordered_set * new_ordered_set(int size);

int is_empty(void);
void * get(int key);
void resize(int size);
void insert(int key, void * value);
int compare(int key1, int key2);
