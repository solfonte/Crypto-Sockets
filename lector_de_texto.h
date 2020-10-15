#ifndef __LECTOR_DE_TEXTO_H__
#define __LECTOR_DE_TEXTO_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct{
  FILE* file_pointer;
}lector_de_texto_t;
/*
typedef ssize_t (*lector_de_texto_callback)(const char *chunk, size_t chunk_size, void *callback_ctx);
*/
int lector_de_texto_init(lector_de_texto_t* lector,const char* archivo);

void lector_de_texto_uninit(lector_de_texto_t* lector);

int lector_de_texto_iterar(lector_de_texto_t* lector,int (*lector_de_texto_callback)(const char *chunk, size_t chunk_size, void *callback_ctx),void *callback_ctx);

#endif
