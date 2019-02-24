#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schema.c"


void print(){
	printf("\t1. Registrar nuevos mensajes cifrados y sus descifrados. \n");
	printf("\t2. Descrifrar mensajes \n");
    printf("\t3. Cifrar mensajes. \n");
    printf("\t4. Mostrar un esquema de cifrado. \n");
    printf("\t5. Borrar un esquema de cifrado debido a un error \n");
}

int main() {
	list_t * list;
	list = new_ordered_list();
	printf("¡Bienvenido! Seleccione una opción: \n");
	while(1){

		int option;

	    print();
	    scanf("%i",&option);
	    getchar();

	    // Registrar nuevos mensajes cifrados y sus descifrados ////////////////////////////////
	    if(option == 1)
	    {
	    	char * message1 = malloc(100000);
	    	char * message2 = malloc(100000);
	    	int fecha;

	        printf("Inserte el mensaje cifrado: ");
	        scanf("%[^\n]",message1);
    		getchar();

	        printf("Inserte el mensaje descifrado: ");
	        scanf("%[^\n]",message2);
    		getchar();

    		printf("Inserte la fecha en formato yyyy/mm/dd");
    		scanf("%d",&fecha);

    		printf("%i\n", fecha);
	        printf("%s\n", message1);
	        printf("%s\n", message2);

	        // Procesamiento de datos
	        schema * sc = new_schema(fecha);
	        list_insert(list, fecha, sc);
	        int schema_built = build_schema(list, sc, message1, message2);
	        if (schema_built) {
	        	printf("Se inserto el esquema en la lista de esquemas\n");
	        }
	        else {
	        	printf("Ocurrio un error al crear el esquema\n");
	        }

	    }
	    // Descifrar mensajes
	    else if(option == 2)
	    {
	    	char * message = malloc(100000);
	    	int fecha;
	    	char *message_;

	    	printf("Inserte el mensaje cifrado: ");
	        scanf("%[^\n]",message);
    		getchar();

    		printf("Inserte la fecha en formato yyyymmdd");
    		scanf("%d",&fecha);
    		printf("%i\n", fecha);

    		message_=decrypt(list,fecha,message);

			printf("%s\n", message_);
    		
  
	    }
	    // Cifrar mensajes
	    else if(option == 3)
	    {
	     	char * message = malloc(100000);
	    	int fecha;
	    	char *message_;

	    	printf("Inserte el mensaje cifrado: ");
	        scanf("%[^\n]",message);
    		getchar();

    		printf("Inserte la fecha en formato yyyymmdd");
    		scanf("%d",&fecha);
    		printf("%i\n", fecha);

    		message_=encrypt(list,fecha,message);

			printf("%s\n", message_);
   
	    }
	    // Mostrar un esquema cifrado
	    else if(option == 4){

			int fecha;
			printf("Inserte la fecha en formato yyyymmdd");
    		scanf("%d",&fecha);
    		printf("%i\n", fecha);
    		schema_print(schema_get_parent(list,fecha));
	    	
	    
	        
	    }
	    // Borrar un esquema cifrado debido a un error
	    else if(option == 5)
	    {
	    	int fecha;
			printf("Inserte la fecha en formato yyyymmdd");
    		scanf("%d",&fecha);
    		//printf("%i\n", fecha);
    		schema_remove(schema_get_parent(list,fecha));	
	    	   
	    }
	    // Error
	    else
	    {
	        printf("Error\n");
	    }
		
	}

}
