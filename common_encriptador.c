#include <string.h>
#include <stdio.h>
#include "common_encriptador.h"
#include <stdlib.h>

#define TAMANIO_VECTOR_S 256


void encriptador_encriptar(encriptador_t* encriptador,char* buffer
                          ,size_t tamanio,int modo){
  void* metodo_particular = encriptador->encriptador_particular;
  if (strcmp(encriptador->metodo,"cesar") == 0){
    encriptador_cesar((encriptador_cesar_t*)metodo_particular,buffer,tamanio,modo);
  }else if (strcmp(encriptador->metodo,"vigenere") == 0){
    encriptador_vigenere((encriptador_vigenere_t*)metodo_particular,buffer,tamanio,modo);
  }else if (strcmp(encriptador->metodo,"rc4") == 0){
    encriptador_rc4((encriptador_rc4_t*)metodo_particular,buffer,tamanio);
  }
}
int encriptador_init(encriptador_t* encriptador,void* encriptador_metodo,char* metodo,void*key){
  encriptador->metodo = metodo;
  encriptador->metodo = encriptador_metodo;
  return EXITO;
}

/*

int encriptador_cesar(encriptador_t* encriptador,char* cadena,size_t tamanio,int modo){
  int i = 0;
  unsigned char* cadena_aux = (unsigned char*)cadena;
  int key_aux = atoi((char*)encriptador ->key);
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

int encriptador_vigenere(encriptador_t* encriptador,char* cadena,size_t tamanio,int modo){
  int i = 0;
  int j = 0;
  unsigned char* cadena_aux = (unsigned char*)cadena;
  unsigned char* key_aux = encriptador->key_donde_me_quede;
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
      key_aux = encriptador->key;
    }
  }
  encriptador->key_donde_me_quede = ((unsigned char*)encriptador->key + j);
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

int encriptador_rc4(encriptador_t* encriptador,char* cadena,size_t tamanio){
  int i = 0;
  //char* key_aux = encriptador->key;
  //unsigned char vector_s[TAMANIO_VECTOR_S];
  unsigned char* cadena_aux = (unsigned char*)cadena;
  //ksa((unsigned char*)key_aux,strlen(key_aux),vector_s);
  while (i < tamanio){
    cadena_aux[i] = (unsigned char)(cadena_aux[i] ^ prga(encriptador->vector_s,&(encriptador->x),&(encriptador->y)));
    i++;
  }
    return EXITO;
}

int encriptador_init(encriptador_t* encriptador,char* metodo,void*key){

  encriptador->metodo = metodo;
  encriptador->key = key;
  encriptador->key_donde_me_quede = key;
  ksa((unsigned char*)key,strlen((char*)key),encriptador->vector_s);
  encriptador->x = 0;
  encriptador->y = 0;

  return EXITO;
}
*/
