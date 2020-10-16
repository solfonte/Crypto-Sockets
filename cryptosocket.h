#ifndef __CRYPTOSOCKET_H__
#define __CRYPTOSOCKET_H__

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "socket.h"
#include "encriptadores.h"
#define ERROR -1
#define EXITO 0

typedef int (*encriptador_encriptar) (char* cadena,void* key);

typedef struct {
  socket_t* socket;
  encriptador_encriptar* metodo;
  void* key;
}
int cryptosocket_init(cryptosocket_t* cryptosocket,int (*encriptador_callback)(char* buffer,void*key));

int cryptosocket_cifrar(const char *buffer, size_t tamanio, void *callback_ctx);

int cryptosocket_init(cryptosocket_t* cryptosocket,int (*encriptador_callback)(char* buffer,void*key));


#endif
