#include "common_encriptador_rc4.h"
#include <string.h>

/*el procedimiento realiza un swap entre dos posiciones
 del stream recibido por parametro*/
static void swap(unsigned char *stream, unsigned int i, unsigned int j) {
    unsigned char temp = stream[i];
    stream[i] = stream[j];
    stream[j] = temp;
}
/*el procedimiento realiza la operacion KSA del
metodo rc4*/
static void ksa(unsigned char *key, size_t key_length,unsigned char* vector_s) {
    unsigned int i,j;
    for (i = 0; i < TAMANIO_VECTOR_S; i++)
        vector_s[i] = (unsigned char)i;

    for (i = j = 0; i < TAMANIO_VECTOR_S; i++) {
        j = (j + key[i % key_length] + vector_s[i]) % TAMANIO_VECTOR_S;
        swap(vector_s, i, j);
    }
}

/*la funcion realiza la operacion PRGA del
metodo rc4*/
static unsigned char prga(unsigned char* vector_s,
                          unsigned int* x,unsigned int* y) {
    *x = (*x + 1) % TAMANIO_VECTOR_S;
    *y = (*y + vector_s[*x]) % TAMANIO_VECTOR_S;

    swap(vector_s, *x, *y);

    return vector_s[(vector_s[*x] + vector_s[*y]) % TAMANIO_VECTOR_S];
}

int rc4_encriptar(rc4_t* encriptador,char* cadena,size_t tamanio){
  int i = 0;
  unsigned char* cadena_aux = (unsigned char*)cadena;
  while (i < tamanio){
    cadena_aux[i] = (unsigned char)(cadena_aux[i] ^ prga(encriptador->vector_s,
                    &(encriptador->x),&(encriptador->y)));
    i++;
  }
    return EXITO;
}

int rc4_init(rc4_t* encriptador,void*key){
  ksa((unsigned char*)key,strlen((char*)key),encriptador->vector_s);
  encriptador->x = 0;
  encriptador->y = 0;

  return EXITO;
}

int rc4_uninit(rc4_t* rc4){
  return EXITO;
}
