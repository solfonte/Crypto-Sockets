#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common_socket.h"
#define TAMANIO_RESPUESTA 64
//capaz sacar TAMANIO_RESPUESTA

static void hints_innit(struct addrinfo* hints,
                        int ai_family,int ai_socktype,
                        int ai_flags){
  memset(hints,0,sizeof(struct addrinfo));
  hints->ai_family = ai_family;
  hints->ai_socktype = ai_socktype;
  hints->ai_flags = ai_flags;
}

int socket_init(socket_t* self,struct addrinfo* info){
  self->fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
  return (self->fd > 0?EXITO:ERROR);
}

int socket_bind_and_listen(socket_t* self,
                          const char* host,
                          const char* service){
  //capaz cambiar la estructura de resultados
  //por resultado y dividir bind con listen
  int resultado_bind,val = 1;
  struct addrinfo hints;
  struct addrinfo* resultados;
  hints_innit(&hints,AF_INET,SOCK_STREAM,AI_PASSIVE);
  if (getaddrinfo(NULL,service, &hints,&resultados) < 0){
    return ERROR;
  }
  if (socket_init(self,resultados) < 0){
    freeaddrinfo(resultados);
    return ERROR;
  }
  setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
  resultado_bind =  bind(self->fd, resultados->ai_addr,resultados->ai_addrlen);
  freeaddrinfo(resultados);
  if (resultado_bind == ERROR){
    socket_uninit(self,SHUT_RD);
    return ERROR;
  }
  int resultado_listen = listen(self->fd, 10/**/);
  return resultado_listen;
}

int socket_uninit(socket_t* self,int modo_de_shutdown){
  shutdown(self->fd,modo_de_shutdown);
  return close(self->fd);
}

int socket_accept(socket_t* listener,socket_t*peer){
    peer->fd = accept(listener->fd, NULL, NULL);
    return((peer->fd == -1)? ERROR:EXITO);
}

int socket_connect(socket_t *self, const char *host, const char *service){
  bool conecte = false;
  struct addrinfo hints;
  struct addrinfo* resultados,*ptr;
  hints_innit(&hints,AF_INET,SOCK_STREAM,0);
  if (getaddrinfo(host,service, &hints,&resultados) < 0){
    return ERROR;
  }
  ptr = resultados;
  while (ptr != NULL && !conecte){
    int res_skt = socket_init(self,ptr);
    if (res_skt != ERROR){
      int res_connect = connect(self->fd,ptr->ai_addr,ptr->ai_addrlen);
      conecte = (res_connect != ERROR?true:false);
    }
    ptr = ptr->ai_next;
  }
  freeaddrinfo(resultados);
  return (self->fd < 0? ERROR:EXITO);
}

int socket_send(socket_t* self, const char* buffer, size_t length){
  bool hubo_un_error = false, termine = false;
  ssize_t bytes_env = 0;
  while (!hubo_un_error && !termine){
    size_t tam_enviar = length - (size_t)bytes_env;
    ssize_t res_env = send(self->fd,&buffer[bytes_env],
                      tam_enviar,MSG_NOSIGNAL);
    if (res_env == ERROR){
      hubo_un_error = true;
    }else if (res_env == 0){
      termine = true;
    }else{
      bytes_env += res_env;
    }
  }
  return (bytes_env == ERROR? ERROR:EXITO);
}

int socket_receive(socket_t* self,
                  int (*socket_callback)(char* chunk,size_t tamanio,
                  void* callback_ctx),void*callback_ctx){
  ssize_t bytes_recv = 0;
  bool termine = false, hubo_error = false;
  char buffer[TAMANIO_RESPUESTA];
  size_t length = TAMANIO_RESPUESTA;
  while (!termine && !hubo_error){
    size_t tam_recv = length - (size_t)bytes_recv;
    ssize_t resultado_recv = recv(self->fd,&buffer[bytes_recv],tam_recv,0);
    bytes_recv = resultado_recv;
    if (resultado_recv == ERROR){
      hubo_error = true;
    }else if (resultado_recv == 0){
      termine = true;
    }else{
      socket_callback(buffer,(size_t)bytes_recv,callback_ctx);
      buffer[bytes_recv] = '\0';
      bytes_recv = 0;
    }
  }
  printf("\n");
  return EXITO;
}
