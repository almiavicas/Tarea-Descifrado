#include <stdio.h>
#include <stdlib.h>
#include "ordered_set.c"


struct regis {
	char * name;
	int age;
};

char *name;
int age;
struct ordered_set * set;

int main()
{
	/* code */
	set = new_ordered_set(sizeof(struct regis), 3);
	name = "alvaro";
	set->insert(set, 12, name);
	name = "enrique";
	set->insert(set, 15, name);
	name = "gustavo";
	set->insert(set, 10, name);
	name = (char *) set->get(set, 10);
	printf("%s %p\n", name, name);
	name = (char *) set->get(set, 12);
	printf("%s %p\n", name, name);
	name = (char *) set->get(set, 15);
	printf("%s %p\n", name, name);
	return 0;
}