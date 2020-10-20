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

/*la funcion inicializa el cryptosocket*/
int cryptosocket_init(cryptosocket_t* cryptosocket,
                      socket_t* socket,encriptador_t* encriptador);

/*la funcion envia un mensaje a traves de un socket luego de
encriptar. Devuelve ERROR si no pudo y EXITO si pudo*/
int _cryptosocket_enviar_mensaje(char* buffer,
                                size_t tamanio, void *callback_ctx);

/*la funcion recibe un mensaje a traves de un socket
 y lo desencripta. Devuelve ERROR si no pudo y EXITO si pudo*/
int _cryptosocket_recibir_mensaje(char *buffer,
                                size_t tamanio,void* callback_ctx);
/*la funcion desinicializa la estructura de cryptosocket
recibida por parametro*/
int cryptosocket_uninit(cryptosocket_t* cryptosocket);


#endif
