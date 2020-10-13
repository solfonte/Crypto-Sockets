#include "socket.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#define ERROR -1
#define EXITO 1

int socket_init(socket_t* self,struct addrinfo* resultados){
  bool creado = false;
  while(resultados != NULL && !creado){
    self->fd = socket(resultados->ai_family, resultados->ai_socktype, resultados->ai_protocol);
    if(self->fd != -1){
      creado = true;
    }
  }
  if(self->fd == -1){
      return -1;
  }
    return 0;
}

  //socket(int domain, int type, int protocol
