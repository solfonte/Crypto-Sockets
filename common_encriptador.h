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
}encriptador_t;

void encriptador_encriptar(encriptador_t* encriptador,
                          char* buffer,size_t tamanio,int modo);
int encriptador_init(encriptador_t* encriptador,void* encriptador_metodo,
                    char* metodo,void*key);
#endif
