#include <string.h>
#include <stdio.h>
#include "encriptadores.h"
#include <stdlib.h>
#define EXITO 1

//hay mucho codigo repetido en los cifrados de cesar
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

int cifrado_de_vigenere(char* cadena,char* key){
  unsigned char* cadena_aux = (unsigned char*)cadena;
  unsigned char* key_aux = (unsigned char*)key;
  while(*cadena_aux != '\0'){
    *cadena_aux = (unsigned char)(*cadena_aux + *key_aux) % 256;
    printf("|%i|",(int)*cadena_aux);
    cadena_aux++;
    key_aux++;
    if(*key_aux == '\0'){
      key_aux = (unsigned char*)key;
    }
  }
  printf("\n");
  return EXITO;
}

int descifrado_de_vigenere(char* cadena,char* key){
  unsigned char* cadena_aux = (unsigned char*)cadena;
  unsigned char* key_aux = (unsigned char*)key;
  while(*cadena_aux != '\0'){
    *cadena_aux = (unsigned char)(*cadena_aux - *key_aux) % 256;
    cadena_aux++;
    key_aux++;
    if(*key_aux == '\0'){
      key_aux = (unsigned char*)key;
    }
  }
  return EXITO;
}
