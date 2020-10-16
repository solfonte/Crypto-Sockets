#ifndef __ENCRIPTADORES_H__
#define __ENCRIPTADORES_H__
#define ERROR -1
#define EXITO 0
#define DESCIFRAR 2
#define CIFRAR 3

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
/*
typedef int (*encriptador_encriptar)(char* cadena,void* key);
*/
typedef struct {
  //encriptador_encriptar metodo;
  char* metodo;
  void* key;
}encriptador_t;

/*precondiciones: la funcion recibe una cadena inicializada
postcondiciones: la funcion encripta la cadena recibida por parametros por cifrado de cesar.
devuelve EXITO en caso de encriptar correctamente y ERROR en caso de no poder*/


//int encriptador_init(encriptador_t* encriptador,char* metodo/*int (*encriptador_encriptar)(char* buffer,void*key)*/,void*key);
/*
int encriptador_cesar_cifrar(char* cadena,void* key);
int encriptador_cesar_descifrar(char* cadena,void* key);
int encriptador_vigenere_cifrar(char* cadena,void* key);
int descifrado_de_vigenere(char* cadena,void* key);//seguro hay que castear a void las key en los sockets
int encriptador_rc4_cifrar(char* cadena,void* key);
int descifrado_de_rc4(char* cadena,void* key);
//int descifrado_de_rc4(char* cadena,char* key);*/

void encriptador_encriptar(encriptador_t* encriptador,char* buffer,int modo);
int encriptador_init(encriptador_t* encriptador,char* metodo/*int (*encriptador_encriptar)(char* buffer,void*key)*/,void*key);
int encriptador_cesar(char* cadena,void* key,int modo);
int encriptador_vigenere(char* cadena,void* key,int modo);
int encriptador_rc4(char* cadena,void* key);
#endif
