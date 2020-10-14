
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>//sacar despues
#include "socket.h"

#define ERROR -1
#define EXITO 0

int socket_init(socket_t* self,struct addrinfo* resultados){
  self->fd = socket(resultados->ai_family, resultados->ai_socktype, resultados->ai_protocol);
  return (self->fd > 0?EXITO:ERROR);
}

int socket_bind_and_listen(socket_t* self, const char* host, const char* service){
    int resultado_socket,resultado_bind,val = 1;
    struct addrinfo hints;
    struct addrinfo* resultados;// enrealidad seria para iterar
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    int local = getaddrinfo(NULL,service, &hints,&resultados);
    if(local < 0){
      printf("locaaal:%i\n",local);
      return ERROR;
    }
  struct addrinfo *ptr = resultados;// enrealidad seria para iterar
//deberia aclarar que en este caso no hace falta hacer iteraciones
  resultado_socket = socket_init(self,ptr);
  printf("s:%i",resultado_socket);
  if(resultado_socket >= 0){
    setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    resultado_bind =  bind(self->fd, ptr->ai_addr,ptr->ai_addrlen);
    printf("l:%i\n",resultado_bind);
    if(resultado_bind == ERROR){
      socket_shutdown(self,SHUT_RD);
      socket_uninit(self);
    }
  }
  freeaddrinfo(resultados);
  int resultado_listen = listen(self->fd, 10/*ver cuantas deberian ser,cpaz una sola es*/);
  printf("listen: %i\n", resultado_listen);
  return EXITO;

}

int socket_uninit(socket_t* self){
  return close(self->fd);
}

int socket_accept(socket_t* listener,socket_t*peer){
    peer->fd = accept(listener->fd, NULL, NULL);
    if(peer->fd == -1) return ERROR;
  return EXITO; //peer->fd;, capaz deberia devolver el peer
}

int socket_shutdown(socket_t* self,int modo){
  return shutdown(self->fd,modo);
}

int socket_connect(socket_t *self, const char *host, const char *service){
  bool conecte = false;
  int resultado_socket;
  struct addrinfo hints;
  struct addrinfo* resultados,*ptr;
  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  if(getaddrinfo(host,service, &hints,&resultados) < 0){
    return ERROR;
  }
  ptr = resultados;
  while(ptr != NULL && !conecte){
    resultado_socket = socket_init(self,ptr);
    if(resultado_socket != ERROR && connect(self->fd,ptr->ai_addr,ptr->ai_addrlen) != ERROR){
      conecte = true;
    }
    ptr = ptr->ai_next;
  //  conecte = true;
  }
  return (self->fd != ERROR? EXITO:ERROR);
}

ssize_t socket_send(socket_t* self, const char* buffer, size_t length){
  ssize_t resultado = send(self->fd,buffer,length,MSG_NOSIGNAL);
  return (resultado == -1? ERROR:resultado);
  //send(sockfd, buf, len, flags);
}

ssize_t socket_receive(socket_t* self, char* buffer, size_t length){
  return recv(self->fd,buffer,length,0);//ver tema flags
  //recv(int sockfd, void *buf, size_t len, int flags);
}
