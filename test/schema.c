#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../schema.c"

int main() {
    hash_table* ht1 = ht_new(); //Cifrado
    hash_table* ht2 = ht_new(); //Descifrado

    char mensaje1[1000], mensaje2[1000];
    int i1,i2; // Aqui se almacena el tamano de cada texto

    printf("Escriba un mensaje Cifrado: ");
    fgets(mensaje1, 100, stdin); // Se guardan espacios + el caracter nulo
    printf("\n");
    for(i1 = 0; mensaje1[i1] != '\0'; ++i1);
    printf("Length of string: %d", i1);

    printf("Escriba un mensaje Descifrado: ");
    scanf("%s", mensaje2);
    printf("\n");
    for(i2 = 0; mensaje2[i2] != '\0'; ++i2);
    //printf("Length of string: %d", i2);
    /*
    for (int i = 0; i < i1; i++){
        int j = ht_hash((char)mensaje1[0],28);
        //hash_table_insert(ht1,mensaje1[i],ht_hash(mensaje1[i],28))
    }
    */
    

}