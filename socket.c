#include "socket.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

#define ERROR -1
#define EXITO 0

int socket_init(socket_t* self,struct addrinfo* resultados){
  self->fd = socket(resultados->ai_family, resultados->ai_socktype, resultados->ai_protocol);
  return (self->fd > 0?EXITO:ERROR);

}
/*
static void inicializar_hints(struct addrinfo* hints){
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = 0;
}*/


int socket_bind_and_listen(socket_t* self, const char* host, const char* service,struct addrinfo *resultados){

  int resultado_socket,resultado_bind,val = 1;
  //bool conectado = false;
  struct addrinfo *ptr = resultados;
//deberia aclarar que en este caso no ace falta hacer iteraciones
  ptr = resultados;
  resultado_socket = socket_init(self,ptr);
  printf("s:%i",resultado_socket);
  if(resultado_socket >= 0){
    setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    resultado_bind =  bind(self->fd, ptr->ai_addr,ptr->ai_addrlen);
    printf("l:%i\n",resultado_bind);
    if(resultado_bind == ERROR){
      socket_uninit(self);
    }
  }
  /*
  while(ptr != NULL && !conectado){
    resultado_socket = socket_init(self,ptr);
    printf("s:%i",resultado_socket);
    if(resultado_socket >= 0){
      setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
      resultado_bind =  bind(self->fd, ptr->ai_addr,ptr->ai_addrlen);
      printf("l:%i\n",resultado_bind);
    }
    ptr++;
    if(resultado_bind == ERROR){
      socket_uninit(self);
    }
  }
*/
  //int listen(int sockfd, int backlog);

  freeaddrinfo(resultados);
  socket_uninit(self);
  return EXITO;
}
int socket_uninit(socket_t* self){
  close(self->fd);
  return EXITO;
}//shitdown y close


  //socket(int domain, int type, int protocol
