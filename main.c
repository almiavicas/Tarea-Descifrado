#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "schema.c"
#include "hash_table.c"
//#include "ordered_list.c"

void print(){
	printf("1. Registrar nuevos mensajes cifrados y sus descifrados. \n");
	printf("2. Descrifrar mensajes \n");
    printf("3. Cifrar mensajes. \n");
    printf("4. Mostrar un esquema de cifrado. \n");
    printf("5. Borrar un esquema de cifrado debido a un error \n");
}


int main() {

	printf("¡Bienvenido! Seleccione una opción: \n");
	while(1){

		int option;

	    print();
	    scanf("%i",&option);
	    getchar();

	    // Registrar nuevos mensajes cifrados y sus descifrados
	    if(option == 1)
	    {
	    	char message1[100];
	    	char message2[100];

	        printf("Inserte el mensaje cifrado: ");
	        scanf("%[^\n]",message1);
    		getchar();

	        printf("Inserte el mensaje descifrado: ");
	        scanf("%[^\n]",message2);
    		getchar();

	        //printf("%s\n", message1);
	        //printf("%s\n", message2);

	    }
	    // Descifrar mensajes
	    else if(option == 2)
	    {
	    	char message[100];
	    	int fecha;

	    	printf("Inserte el mensaje cifrado: ");
	        scanf("%[^\n]",message);
    		getchar();

    		printf("Inserte la fecha en formato DDMMAAAA: ");
	        scanf("%d",&fecha);
    		getchar();
    		
  
	    }
	    // Cifrar mensajes
	    else if(option == 3)
	    {
	     	char message[100];
	    	int fecha;  

	    	printf("Inserte el mensaje cifrado: ");
	        scanf("%[^\n]",message);
    		getchar();

    		printf("Inserte la fecha en formato DDMMAAAA: ");
	        scanf("%d",&fecha);
    		getchar();
   
	    }
	    // Mostrar un esquema cifrado
	    else if(option == 4)
	    {
	        
	    }
	    // Borrar un esquema cifrado debido a un error
	    else if(option == 5)
	    {
	    	   
	    }
	    // Error
	    else
	    {
	        printf("Error\n");
	    }
		
	}

}
