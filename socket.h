#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "socket.h"


typedef struct{
  int fd;
} socket_t;

int socket_init(socket_t* self,struct addrinfo* resultados);
int socket_uninit(socket_t* self);//shitdown y close
int socket_bind_and_listen(socket_t* self, const char* host, const char* service);
int socket_accept(socket_t* listener, socket_t* peer);
int socket_connect(socket_t* self, const char* host, const char* service);
size_t socket_send(socket_t* self, const char* buffer, size_t length);
size_t socket_receive(socket_t* self, char* buffer, size_t length);

#endif
