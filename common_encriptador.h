#ifndef __ENCRIPTADORES_H__
#define __ENCRIPTADORES_H__
#define ERROR -1
#define EXITO 0
#define DESCIFRAR 2
#define CIFRAR 3

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "common_encriptador_cesar.h"
#include "common_encriptador_vigenere.h"
#include "common_encriptador_rc4.h"


typedef struct {
  void* encriptador_particular;
  char* metodo;
  /*char* metodo;
  void* key;
  void* key_donde_me_quede;
  unsigned int x;
  unsigned int y;
  unsigned char vector_s[256];*/
}encriptador_t;

void encriptador_encriptar(encriptador_t* encriptador,
                          char* buffer,size_t tamanio,int modo);
int encriptador_init(encriptador_t* encriptador,void* encriptador_metodo,
                    char* metodo,void*key);/*
int encriptador_cesar(encriptador_t* encriptador,char* cadena,size_t tamanio,int modo);
int encriptador_vigenere(encriptador_t* encriptador,char* cadena,size_t tamanio,int modo);
int encriptador_rc4(encriptador_t* encriptador,char* cadena,size_t tamanio);*/
#endif
