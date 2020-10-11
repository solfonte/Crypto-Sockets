#include <string.h>
#include <stdlib.h>
#define N 3

int encriptado_de_cesar(char*cadena){
  //itero cadena
  int longitud_cadena = strlen(cadena) - 1;
  int contador = 0;
  char* cadena_aux = malloc(longitud_cadena * sizeof(char*));
  strncpy(cadena_aux,cadena,longitud_cadena);
  while(contador <longitud_cadena){

    char caracter = cadena_aux[contador];
    unsigned int caracter_en_ascii_cifrado = (unsigned int)caracter + N;
    caracter = (char)(caracter_en_ascii_cifrado % 256);
    strcpy(cadena_aux[contador],&caracter);
  }
  free(cadena_aux);
  return 1;
  //al final a esa cadena nueva la copio a la cadena recibida por parametro
}
