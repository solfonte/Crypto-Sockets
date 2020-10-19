#ifndef __ENCRIPTADOR_RC4_H__
#define __ENCRIPTADOR_RC4_H__
#define ERROR -1
#define EXITO 0
#define DESCIFRAR 2
#define CIFRAR 3
#define TAMANIO_VECTOR_S 256

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

typedef struct {
  unsigned int x;
  unsigned int y;
  unsigned char vector_s[TAMANIO_VECTOR_S];
}rc4_t;

int rc4_init(rc4_t* encriptador,void*key);
int rc4_encriptar(rc4_t* encriptador,char* cadena,size_t tamanio);
#endif
