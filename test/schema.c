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

	printf("Apuntador al esquema 1: %p\n", sc1);
	
	list_insert(list, sc1->date, sc1);


	int succeed = build_schema(list, sc1, encrypted_message, decrypted_message);


	printf("date del schema 1: %d\n", sc1->date);

	
	encrypted_message = "FEWE TRYE";
	decrypted_message = "MAGA HOLA";
	date = 20000505;
	
	sc2 = new_schema(date);
	printf("Apuntador al esquema 2: %p\n", sc2);
	
	list_insert(list, sc2->date, sc2);

	printf("date sc1: %d\n", sc2->date);
	printf("date sc2: %d\n", sc1->date);
	
	succeed = build_schema(list, sc2, encrypted_message, decrypted_message);

	
	date = 20000303;
	
	printf("Created schemas\n");

	char* message = "AAAAAA LO LOGRAMOSSS";
	printf("%s\n", message);
	schema_print(sc1);
	
	encrypted_message = encrypt(list,20001010,message);

	printf("%s\n", encrypted_message);
	
	decrypted_message = decrypt(list,20001010,message);

	printf("%s\n", decrypted_message);

	return 0;
}
