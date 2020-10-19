#include "common_encriptador_cesar.h"
#include <stdlib.h>


int encriptador_cesar_init(encriptador_cesar_t* encriptador,void*key){
    encriptador->key = key;
    return EXITO;
}


int encriptador_cesar(encriptador_cesar_t* encriptador,char* cadena,
                      size_t tamanio,int modo){
  int i = 0;
  unsigned char* cadena_aux = (unsigned char*)cadena;
  int key_aux = atoi((char*)encriptador ->key);
  while (i < tamanio){
    if (modo == CIFRAR){
      cadena_aux[i] = (unsigned char)(cadena_aux[i] + key_aux);
    }else{
      cadena_aux[i] = (unsigned char)(cadena_aux[i] - key_aux);
    }
    i++;
  }
  return EXITO;
}
