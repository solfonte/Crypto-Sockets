#ifndef __ENCRIPTADOR_CESAR_H__
#define __ENCRIPTADOR_CESAR_H__
#define ERROR -1
#define EXITO 0
#define DESCIFRAR 2
#define CIFRAR 3

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

typedef struct {
  void* key;
}cesar_t;

/*la funcion inicializa la estructura de cesar*/
int cesar_init(cesar_t* encriptador,void*key);

/*la funcion encripta segun el modo recibido por parametro (DESCIFRAR O CIFRAR)
mediante el metodo cesar la cadena recibida por parametro*/
int cesar_encriptar(cesar_t* encriptador,char* cadena,
                      size_t tamanio,int modo);
/*la funcion desinicializa la estructura cesar_t*/
int cesar_uninit(cesar_t* cesar);

#endif
