#include <string.h>
#include <stdio.h>
#include "common_encriptador.h"
#include <stdlib.h>

#define TAMANIO_VECTOR_S 256


void encriptador_encriptar(encriptador_t* encriptador,char* buffer
                          ,size_t tamanio,int modo){
  void* metodo_particular = encriptador->encriptador_particular;
  if (strcmp(encriptador->metodo,"cesar") == 0){
    cesar_encriptar((cesar_t*)metodo_particular,buffer,
                      tamanio,modo);
  }else if (strcmp(encriptador->metodo,"vigenere") == 0){
    vigenere_encriptar((vigenere_t*)metodo_particular,
                          buffer,tamanio,modo);
  }else if (strcmp(encriptador->metodo,"rc4") == 0){
    rc4_encriptar((rc4_t*)metodo_particular,buffer,tamanio);
  }else{
    printf("No se pudo encriptar, el metodo no es valido\n");
  }
}
int encriptador_init(encriptador_t* encriptador,cesar_t* cesar,
                    vigenere_t* vigenere,rc4_t* rc4,
                    char* metodo,void*key){
  int resultado = EXITO;
  if (strcmp(metodo,"cesar") == 0){
    cesar_init(cesar,key);
    encriptador-> encriptador_particular = cesar;
  }else if (strcmp(metodo,"vigenere") == 0){
    vigenere_init(vigenere,key);
    encriptador-> encriptador_particular = vigenere;
  }else if (strcmp(metodo,"rc4") == 0){
    rc4_init(rc4,key);
    encriptador-> encriptador_particular = rc4;
  }else{
    printf("no existe el metodo introducido\n");
    resultado = ERROR;
  }
  encriptador->metodo = metodo;
  return resultado;
}

int encriptador_uninit(encriptador_t* encriptador,cesar_t* cesar,
                      vigenere_t* vigenere,rc4_t* rc4){
  if (strcmp(encriptador->metodo,"cesar") == 0){
    cesar_uninit(cesar);
  }else if (strcmp(encriptador->metodo,"vigenere") == 0){
    vigenere_uninit(vigenere);
  }else if (strcmp(encriptador->metodo,"rc4") == 0){
    rc4_uninit(rc4);
  }
  return EXITO;
}
