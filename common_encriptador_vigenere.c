#include "common_encriptador_vigenere.h"
#include <stdio.h>

int encriptador_vigenere_init(encriptador_vigenere_t* encriptador,void*key){
  encriptador->key = key;
  encriptador->key_donde_me_quede = key;
  return EXITO;
}

int encriptador_vigenere(encriptador_vigenere_t* encriptador,
                        char* cadena,size_t tamanio,int modo){
  int i = 0;
  int j = 0;
  unsigned char* cadena_aux = (unsigned char*)cadena;
  unsigned char* key_aux = encriptador->key_donde_me_quede;
  while (i < tamanio){
    if (modo == CIFRAR){
      cadena_aux[i] = (unsigned char)(cadena_aux[i] + key_aux[j]);
    }else{
      cadena_aux[i] = (unsigned char)(cadena_aux[i] - key_aux[j]);
    }
    j++;
    i++;
    if (key_aux[j] == '\0'){
      j = 0;
      key_aux = encriptador->key;
    }
  }
  encriptador->key_donde_me_quede = &key_aux[j];
  return EXITO;
}
