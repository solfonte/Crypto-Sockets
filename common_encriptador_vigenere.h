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
}vigenere_t;

int vigenere_init(vigenere_t* encriptador,void*key);
int vigenere_encriptar(vigenere_t* encriptador,
                        char* cadena,size_t tamanio,int modo);
#endif
