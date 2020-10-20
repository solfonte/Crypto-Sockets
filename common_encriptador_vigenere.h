#ifndef __ENCRIPTADOR_VIGENERE_H__
#define __ENCRIPTADOR_VIGENERE_H__
#define ERROR -1
#define EXITO 0
#define DESCIFRAR 2
#define CIFRAR 3

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

typedef struct {
  void* key;
  void* key_donde_me_quede;
}encriptador_vigenere_t;

/*la funcion inicializa la estructura de vigenere*/
int encriptador_vigenere_init(encriptador_vigenere_t* encriptador,void*key);

/*la funcion encripta segun el modo recibido por parametro (DESCIFRAR O CIFRAR)
mediante el metodo vigenere la cadena recibida por parametro*/
int encriptador_vigenere(encriptador_vigenere_t* encriptador,
                        char* cadena,size_t tamanio,int modo);
#endif
