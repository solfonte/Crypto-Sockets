#include <string.h>
#include <stdio.h>
#include "common_encriptador.h"
#include <stdlib.h>

#define TAMANIO_VECTOR_S 256


void encriptador_encriptar(encriptador_t* encriptador,char* buffer,int modo){
  if(strcmp(encriptador->metodo,"cesar") == 0){
    encriptador_cesar(buffer,encriptador->key,modo);
  }else if(strcmp(encriptador->metodo,"vigenere") == 0){
    encriptador_vigenere(buffer,encriptador->key,modo);
  }else if(strcmp(encriptador->metodo,"rc4") == 0){
    encriptador_rc4(buffer,encriptador->key);
  }
}

int encriptador_init(encriptador_t* encriptador,char* metodo,void*key){
  encriptador->metodo = metodo;
  encriptador->key = key;
  return EXITO;
}

int encriptador_cesar(char* cadena,void* key,int modo){
  unsigned char* cadena_aux = (unsigned char*)cadena;
  int key_aux = atoi((char*)key);
  while(*cadena_aux != '\0'){
    if(modo == CIFRAR){
      *cadena_aux = (unsigned char)(*cadena_aux + key_aux);
    }else{
      *cadena_aux = (unsigned char)(*cadena_aux - key_aux);
    }
    cadena_aux++;
  }
  return EXITO;
}

int encriptador_vigenere(char* cadena,void* key,int modo){
  unsigned char* cadena_aux = (unsigned char*)cadena;
  unsigned char* key_aux = (unsigned char*)key;
  while(*cadena_aux != '\0'){
    if(modo == CIFRAR){
      *cadena_aux = (unsigned char)(*cadena_aux + *key_aux);
    }else{
      *cadena_aux = (unsigned char)(*cadena_aux - *key_aux);
    }
    printf("|%i|",(int)*cadena_aux);
    cadena_aux++;
    key_aux++;
    if(*key_aux == '\0'){
      key_aux = (unsigned char*)key;
    }
  }
  printf("\n");
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

static unsigned char rc4_output(unsigned char* vector_s) {
  unsigned int i = 0,j = 0;

    i = (i + 1) % TAMANIO_VECTOR_S;
    j = (j + vector_s[i]) % TAMANIO_VECTOR_S;

    swap(vector_s, i, j);

    return vector_s[(vector_s[i] + vector_s[j]) % TAMANIO_VECTOR_S];
}

int encriptador_rc4(char* cadena,void* key){
  char* key_aux = (char*)key;
  unsigned char vector_s[TAMANIO_VECTOR_S];
  unsigned char* cadena_aux = (unsigned char*)cadena;
  ksa((unsigned char*)key_aux,strlen(key_aux),vector_s);
  while(*cadena_aux != '\0'){
    *cadena_aux = (unsigned char)(*cadena_aux ^ rc4_output(vector_s));
  //  printf("|%x|",(int)*cadena_aux);
    cadena_aux = cadena_aux + 1;
  }
    return EXITO;
}
