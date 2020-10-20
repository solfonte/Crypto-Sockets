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

/*el procedimiento encripta la cadena recibida por parametros segun el
modo recibido por parametro*/
void encriptador_encriptar(encriptador_t* encriptador,
                          char* buffer,size_t tamanio,int modo);

/*la funcion inicializa la estructura encriptador_t
segun el metodo a utilizar*/
int encriptador_init(encriptador_t* encriptador,encriptador_cesar_t* cesar,
                    encriptador_vigenere_t* vigenere,encriptador_rc4_t* rc4,
                    char* metodo,void*key);
#endif
