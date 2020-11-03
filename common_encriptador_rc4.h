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

/*la funncion inicializa la estructura de rc4*/
int rc4_init(rc4_t* encriptador,void*key);

/*la funcion encripta mediante el metodo rc4 la cadena recibida por parametro*/
int rc4_encriptar(rc4_t* encriptador,char* cadena,size_t tamanio);

/*la funcion desinicializa la estructura rc4_t*/
int rc4_uninit(rc4_t* rc4);

#endif
