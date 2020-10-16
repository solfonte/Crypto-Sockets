#ifndef __CRYPTOSOCKET_H__
#define __CRYPTOSOCKET_H__

#include "common_socket.h"
#include "common_encriptador.h"

#define ERROR -1
#define EXITO 0

typedef struct {
  socket_t* socket;
  encriptador_t* encriptador;
}cryptosocket_t;

int cryptosocket_init(cryptosocket_t* cryptosocket,
                      socket_t* socket,encriptador_t* encriptador);

int _cryptosocket_enviar_mensaje(char* buffer,
                                size_t tamanio, void *callback_ctx);

int _cryptosocket_recibir_mensaje(char *buffer,void* cryptosocket);

#endif
