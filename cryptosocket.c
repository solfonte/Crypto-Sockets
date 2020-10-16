#include "cryptosocket.h"
#define TAMANIO_RESPUESTA 10


int cryptosocket_init(cryptosocket_t* cryptosocket,socket_t* socket,encriptador_t* encriptador){
  cryptosocket->socket = socket;
  cryptosocket->encriptador = encriptador;
  return EXITO;
}

int _cryptosocket_enviar_mensaje_encriptado(char *buffer, size_t tamanio, void* callback_ctx){
  cryptosocket_t* cryptosocket = callback_ctx;
  void* key_aux = cryptosocket->encriptador->key;
  cryptosocket->encriptador->metodo(buffer,key_aux);
  return socket_send(cryptosocket->socket,buffer,tamanio);
}

int _cryptosocket_recibir_mensaje_encriptado(cryptosocket_t* cryptosocket,char *buffer, size_t tamanio){
  void* key_aux = cryptosocket->encriptador->key;
  cryptosocket->encriptador->metodo(buffer,key_aux);
  return socket_receive(cryptosocket->socket,buffer,TAMANIO_RESPUESTA);
}
