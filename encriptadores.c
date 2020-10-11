#include <string.h>
#include <stdio.h>
#include "encriptadores.h"
#include <stdlib.h>
#define EXITO 1


int cifrado_de_cesar(char* cadena,int key){
  unsigned char* cadena_aux = (unsigned char*)cadena;
  while(*cadena_aux != '\0'){
    *cadena_aux = (unsigned char)(*cadena_aux + key) % 256;
    cadena_aux++;
  }
  return EXITO;
}

int descifrado_de_cesar(char*cadena,int key){
  unsigned char* cadena_aux = (unsigned char*)cadena;
  while(*cadena_aux != '\0'){
    *cadena_aux = (unsigned char)(*cadena_aux - key) % 256;
    cadena_aux++;
  }
  return EXITO;
}
