#include "lector_de_texto.h"
#define ERROR -1
#define EXITO 0

int lector_de_texto_init(lector_de_texto_t* lector,const char* archivo){
  lector->file_pointer = fopen(archivo,"rd");
  return (lector->file_pointer == NULL?ERROR:EXITO);
}
void lector_de_texto_uninit(lector_de_texto_t* lector){
		fclose(lector->file_pointer);
  /*  if(!stdin){
      fclose()
    }*/
}/*
int lector_de_texto_leer(lector_de_texto_t* lector,(*lector_de_texto_callback)(const char *chunk, size_t chunk_size, void *callback_ctx)){
  char buffer[150];
  size_t leido = fread((void*)buffer,sizeof(char*),150,lector->file_pointer);
  while(leido > 0){
    lector_de_texto_callback(buffer,150,);
    //bytes_enviados = socket_send(&client,buffer,total_bytes_left);
    //if(bytes_enviados != ERROR){
    //  total_bytes_left = total_bytes_left - (size_t)bytes_enviados;
    //}
  }*/
//}
