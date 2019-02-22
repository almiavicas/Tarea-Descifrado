#include <stdlib.h>
#include <stdio.h>
#include "../schema.c"

schema * sc1;
schema * sc2;
list_t * list;
char * encrypted_message;
char * decrypted_message;



int main()
{
	/* code */
	list = new_ordered_list();
	encrypted_message = "TRYE FEWE";
	decrypted_message = "HOLA MAGA";

	int date = 20001010;
	sc1 = new_schema(date);
	printf("%p\n", sc1);
	list_insert(list, sc1->date, sc1);
	int succeed = build_schema(list, sc1, encrypted_message, decrypted_message);
	printf("%d\n", succeed);

	printf("date: %d\n", sc1->date);


	encrypted_message = "FEWE TRYE";
	decrypted_message = "MAGA HOLA";
	date = 20000505;
	sc2 = new_schema(date);
	printf("%p\n", sc2);
	list_insert(list, sc2->date, sc2);
	printf("date: %d\n", sc2->date);
	printf("date: %d\n", sc1->date);
	succeed = build_schema(list, sc2, encrypted_message, decrypted_message);

	printf("%d\n", succeed);

	date = 20000303;
	
	printf("Created schemas\n");

	char* message = "OLA MAMA";
	schema_print(sc1);
	encrypted_message = encrypt(list,20001010,message);
	printf("%s\n", encrypted_message);
	
	return 0;
}