#include "client_lector_de_texto.h"
#define TAMANIO_MENSAJE 10

int lector_de_texto_init(lector_de_texto_t* lector){
  lector->file_pointer = stdin;
  return 0;
}

void lector_de_texto_uninit(lector_de_texto_t* lector){
		fclose(lector->file_pointer);
}

int lector_de_texto_iterar(lector_de_texto_t* lector,
                          int (*lector_de_texto_callback)(char *chunk,
                          size_t chunk_size,
                          void *callback_ctx),void *callback_ctx){
  char buffer[TAMANIO_MENSAJE];
  int resultado = 0;
  while (!feof(lector->file_pointer) && resultado != ERROR){
    size_t leido = fread((void*)buffer,1,TAMANIO_MENSAJE,lector->file_pointer);
    resultado = lector_de_texto_callback(buffer,leido,callback_ctx);
  }
  return (resultado == ERROR?ERROR:EXITO);
}
