#include <stdio.h>
#include <stdlib.h>
#include "../ordered_list.c"

struct person {
	int age;
	char * name;
};

void person_info(struct person * p) {
	printf("\tperson pointer: %p\n\tperson age: %d\n\tperson name: %s\n", p, p->age, p->name);
}

list * l;
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
	l = new_ordered_list();
	if (l == NULL) {
		fprintf(stderr, "cant create list\n");
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
	inserted = insert(l, person1->age, person1);
	if (!inserted) {
		fprintf(stderr, "Failed to insert person 1\n");
		return 0;
	}
	insert(l, person2->age, person2);
	if (!inserted) {
		fprintf(stderr, "Failed to insert person 2\n");
		return 0;
	}
	insert(l, person3->age, person3);
	if (!inserted) {
		fprintf(stderr, "Failed to insert person 3\n");
		return 0;
	}
	printf("People inserted in ordered_list\n");
	struct person * p;
	printf("getting person 1. its real info is:\n");
	person_info(person1);
	p = (struct person *) get(l, 10);
	if (p == NULL) {
		fprintf(stderr, "failed to get person\n");
		return 0;
	}
	printf("%s, %d\n", p->name, p->age);
	printf("%p\n", p);
	printf("getting person 2. its real info is:\n");
	person_info(person2);
	p = (struct person *) get(l, 15);
	printf("%s, %d\n", p->name, p->age);
	printf("%p\n", p);
	printf("getting person 3. its real info is:\n");
	person_info(person3);
	p = (struct person *) get(l, 20);
	printf("%s, %d\n", p->name, p->age);
	printf("%p\n", p);
	printf("\n##### Testing iterators #####");
	struct item * it = iterator(l);
	while (has_next(it)) { 
		p = (struct person *) next(it);
		printf("%s, %d\n", p->name, p->age);
		printf("%p\n", p);
	}
	return 0;
}