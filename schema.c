#include<stdio.h>

struct element {
    char *key;
    char *value;
    struct element *next;
};

typedef struct element myelement;

struct hashtable {
    int size;
    struct element **table;
};

typedef struct hashtable myhashtable;

myhashtable *newhashtable(int size){

}



int main() {
	return 0;
}