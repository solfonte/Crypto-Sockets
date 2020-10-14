#ifndef __LECTOR_DE_TEXTO_H__
#define __LECTOR_DE_TEXTO_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct{
  FILE* file_pointer;
}lector_de_texto_t;

lector_de_texto_init(lector_de_texto_t* lector,const char* archivo);

#endif
