#include <stdio.h>
#include <stdlib.h>
#include "tree_set.c"

struct person {
	int age;
	char * name;
};

void person_info(struct person * p) {
	printf("\tperson pointer: %p\n\tperson age: %d\n\tperson name: %s\n", p, p->age, p->name);
}

struct tree_set * c;
struct person *person1;
struct person *person2;
struct person *person3;

int main()
{
	/* code */
	printf("begin\n");
	person1 = malloc(sizeof(struct person));
	if (person1 == NULL) {
		fprintf(stderr, "cant create person 1\n");
		perror("error: ");
		return 0;
	}
	person2 = malloc(sizeof(struct person));
	if (person1 == NULL) {
		fprintf(stderr, "cant create person 2\n");
		perror("error: ");
		return 0;
	}
	person3 = malloc(sizeof(struct person));
	if (person1 == NULL) {
		fprintf(stderr, "cant create person 3\n");
		perror("error: ");
		return 0;
	}
	c = new_tree_set();
	if (c == NULL) {
		fprintf(stderr, "cant create tree_set\n");
		perror("Error: ");
		return 0;
	}
	printf("Structures created\n");
	person1->age = 10;
	person1->name = "alejandro";
	person2->age = 20;
	person2->name = "alvaro";
	person3->age = 15;
	person3->name = "enrique";
	int inserted;
	inserted = c->insert(c, person1->age, person1);
	if (!inserted) {
		fprintf(stderr, "Failed to insert person 1\n");
		return 0;
	}
	// printf("current status of the tree: \n");
	// tree_info(c);
	c->insert(c, person2->age, person2);
	if (!inserted) {
		fprintf(stderr, "Failed to insert person 2\n");
		return 0;
	}
	// printf("current status of the tree: \n");
	// tree_info(c);
	c->insert(c, person3->age, person3);
	if (!inserted) {
		fprintf(stderr, "Failed to insert person 3\n");
		return 0;
	}
	printf("People inserted in tree_set\n");
	printf("current status of the tree: \n");
	tree_info(c);
	struct person * p;
	printf("getting person 1. its real info is:\n");
	person_info(person1);
	p = (struct person *) c->get(c, 10);
	if (p == NULL) {
		fprintf(stderr, "failed to get person\n");
		return 0;
	}
	printf("%s, %d\n", p->name, p->age);
	printf("%p\n", p);
	printf("getting person 2. its real info is:\n");
	person_info(person2);
	p = (struct person *) c->get(c, 15);
	printf("%s, %d\n", p->name, p->age);
	printf("%p\n", p);
	printf("getting person 3. its real info is:\n");
	person_info(person3);
	p = (struct person *) c->get(c, 20);
	printf("%s, %d\n", p->name, p->age);
	printf("%p\n", p);
	return 0;
}