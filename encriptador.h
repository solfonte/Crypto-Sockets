#ifndef __ENCRIPTADORES_H__
#define __ENCRIPTADORES_H__
#define ERROR -1
#define EXITO 0
#define DESCIFRAR 2
#define CIFRAR 3

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

typedef struct {
  //encriptador_encriptar metodo;
  char* metodo;
  void* key;
}encriptador_t;

void encriptador_encriptar(encriptador_t* encriptador,char* buffer,int modo);
int encriptador_init(encriptador_t* encriptador,char* metodo,void*key);
int encriptador_cesar(char* cadena,void* key,int modo);
int encriptador_vigenere(char* cadena,void* key,int modo);
int encriptador_rc4(char* cadena,void* key);
#endif
