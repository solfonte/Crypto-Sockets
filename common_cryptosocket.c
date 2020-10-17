#include "common_cryptosocket.h"
#include <stdio.h>
#define TAMANIO_RESPUESTA 10


int cryptosocket_init(cryptosocket_t* cryptosocket,
                      socket_t* socket,encriptador_t* encriptador){
  cryptosocket->socket = socket;
  cryptosocket->encriptador = encriptador;
  return EXITO;
}

int _cryptosocket_enviar_mensaje(char *buffer,
                                size_t tamanio, void* callback_ctx){
  cryptosocket_t* cryptosocket = callback_ctx;
  encriptador_encriptar(cryptosocket->encriptador,buffer,CIFRAR);
  return socket_send(cryptosocket->socket,buffer,tamanio);
}

int _cryptosocket_recibir_mensaje(char *buffer,void* callback_ctx){
  cryptosocket_t* cryptosocket = callback_ctx;
  encriptador_encriptar(cryptosocket->encriptador,buffer,DESCIFRAR);
  //cryptosocket->encriptador->metodo/*(buffer,key_aux)*/;
  printf("%s",buffer);
  return EXITO;
}
