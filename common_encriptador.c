#include <string.h>
#include <stdio.h>
#include "common_encriptador.h"
#include <stdlib.h>

#define TAMANIO_VECTOR_S 256


void encriptador_encriptar(encriptador_t* encriptador,char* buffer
                          ,size_t tamanio,int modo){
  void* metodo_particular = encriptador->encriptador_particular;
  if (strcmp(encriptador->metodo,"cesar") == 0){
    encriptador_cesar((encriptador_cesar_t*)metodo_particular,buffer,
                      tamanio,modo);
  }else if (strcmp(encriptador->metodo,"vigenere") == 0){
    encriptador_vigenere((encriptador_vigenere_t*)metodo_particular,
                          buffer,tamanio,modo);
  }else if (strcmp(encriptador->metodo,"rc4") == 0){
    encriptador_rc4((encriptador_rc4_t*)metodo_particular,buffer,tamanio);
  }
}
int encriptador_init(encriptador_t* encriptador,void* encriptador_metodo,
                    char* metodo,void*key){
  encriptador->metodo = metodo;
  encriptador-> encriptador_particular = encriptador_metodo;
  return EXITO;
}
