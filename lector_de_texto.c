#include "lector_de_texto.h"
#define TAMANIO_MENSAJE 10

int lector_de_texto_init(lector_de_texto_t* lector,const char* archivo){
  lector->file_pointer = fopen(archivo,"rd");
  return (lector->file_pointer == NULL?ERROR:EXITO);
}

void lector_de_texto_uninit(lector_de_texto_t* lector){
		fclose(lector->file_pointer);
  /*  if(!stdin){
      fclose()
    }*/
}

int lector_de_texto_iterar(lector_de_texto_t* lector,int (*lector_de_texto_callback)(const char *chunk, size_t chunk_size, void *callback_ctx),void *callback_ctx){
  char buffer[TAMANIO_MENSAJE];
  int resultado = 0;
  while(!feof(lector->file_pointer) && resultado != ERROR){
    size_t leido = fread((void*)buffer,1,TAMANIO_MENSAJE,lector->file_pointer);
    resultado = lector_de_texto_callback(buffer,leido,callback_ctx);
  }
  return (resultado == ERROR?ERROR:EXITO);
}
