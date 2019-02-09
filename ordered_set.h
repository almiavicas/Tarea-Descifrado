struct ordered_set {
	void * begin;
	void * end;
	int size;
	int isEmpty(void);
	void * at(int p);
	void resize(int size);
};
ordered_set new_ordered_set(int size);