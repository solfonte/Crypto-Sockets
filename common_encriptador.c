#include <string.h>
#include <stdio.h>
#include "common_encriptador.h"
#include <stdlib.h>

#define TAMANIO_VECTOR_S 256


void encriptador_encriptar(encriptador_t* encriptador,char* buffer
                          ,size_t tamanio,int modo){
  if (strcmp(encriptador->metodo,"cesar") == 0){
    encriptador_cesar(buffer,tamanio,encriptador->key,modo);
  }else if (strcmp(encriptador->metodo,"vigenere") == 0){
    encriptador_vigenere(buffer,tamanio,encriptador->key,modo);
  }else if (strcmp(encriptador->metodo,"rc4") == 0){
    encriptador_rc4(buffer,tamanio,encriptador->key);
  }
}

int encriptador_init(encriptador_t* encriptador,char* metodo,void*key){
  encriptador->metodo = metodo;
  encriptador->key = key;
  return EXITO;
}

int encriptador_cesar(char* cadena,size_t tamanio,void* key,int modo){
  int i = 0;
  unsigned char* cadena_aux = (unsigned char*)cadena;
  int key_aux = atoi((char*)key);
  while (i < tamanio){
    if (modo == CIFRAR){
      cadena_aux[i] = (unsigned char)(cadena_aux[i] + key_aux);
    }else{
      cadena_aux[i] = (unsigned char)(cadena_aux[i] - key_aux);
    }
    i++;
  }
  return EXITO;
}

int encriptador_vigenere(char* cadena,size_t tamanio,void* key,int modo){
  int i = 0;
  int j = 0;
  unsigned char* cadena_aux = (unsigned char*)cadena;
  unsigned char* key_aux = key;

  while (i < tamanio){
    if (modo == CIFRAR){
      cadena_aux[i] = (unsigned char)(cadena_aux[i] + key_aux[j]);
    }else{
      cadena_aux[i] = (unsigned char)(cadena_aux[i] - key_aux[j]);
    }
    j++;
    i++;
    if (key_aux[j] == '\0'){
      j = 0;
    }
  }
  return EXITO;
}

static void swap(unsigned char *s, unsigned int i, unsigned int j) {
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

static void ksa(unsigned char *key, size_t key_length,unsigned char* vector_s) {
    unsigned int i,j;
    for (i = 0; i < TAMANIO_VECTOR_S; i++)
        vector_s[i] = (unsigned char)i;

    for (i = j = 0; i < TAMANIO_VECTOR_S; i++) {
        j = (j + key[i % key_length] + vector_s[i]) % TAMANIO_VECTOR_S;
        swap(vector_s, i, j);
    }
}

static unsigned char prga(unsigned char* vector_s,
                          unsigned int* x,unsigned int* y) {
    *x = (*x + 1) % TAMANIO_VECTOR_S;
    *y = (*y + vector_s[*x]) % TAMANIO_VECTOR_S;

    swap(vector_s, *x, *y);

    return vector_s[(vector_s[*x] + vector_s[*y]) % TAMANIO_VECTOR_S];
}

int encriptador_rc4(char* cadena,size_t tamanio,void* key){
  int i = 0;
  unsigned int x = 0;
  unsigned int y = 0;
  char* key_aux = key;
  unsigned char vector_s[TAMANIO_VECTOR_S];
  unsigned char* cadena_aux = (unsigned char*)cadena;
  ksa((unsigned char*)key_aux,strlen(key_aux),vector_s);
  while (i < tamanio){
    cadena_aux[i] = (unsigned char)(cadena_aux[i] ^ prga(vector_s,&x,&y));
    i++;
  }
    return EXITO;
}
