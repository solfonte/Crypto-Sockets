
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>//sacar despues
#include "socket.h"

#define ERROR -1
#define EXITO 0
#define TAMANIO_MENSAJE 10

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

int socket_send(socket_t* self, const char* buffer, size_t length){
  size_t bytes_no_enviados = length;
  ssize_t bytes_enviados = 0;
  while(bytes_no_enviados > 0 && bytes_enviados != ERROR){
      bytes_enviados = send(self->fd,&buffer[bytes_enviados],length - (size_t)bytes_enviados,MSG_NOSIGNAL);

      printf("mando:%s pero hasta %c\n",buffer,buffer[bytes_enviados - 1]);
      if(bytes_enviados != ERROR){
        bytes_no_enviados = bytes_no_enviados - (size_t)bytes_enviados;
      }
    }
//  ssize_t resultado = send(self->fd,buffer,length,MSG_NOSIGNAL);
  return (bytes_enviados == -1? ERROR:EXITO);
  //send(sockfd, buf, len, flags);
}

ssize_t socket_receive(socket_t* self, char* buffer, size_t length){

  ssize_t bytes_recibidos = 0;
  bool termine = false, fallo_rcv = false;
  ssize_t resultado = 0;
  while(!termine && !fallo_rcv){
    resultado = recv(self->fd,buffer,length - (size_t)bytes_recibidos - 1,0);
    bytes_recibidos = resultado;
    buffer[bytes_recibidos] = 0;
    //printf("recibo:%s pero hasta %c y bytes:%lu \n",buffer,buffer[bytes_recibidos - 1],resultado);
    printf("%s",buffer);

    if(resultado == -1){
      fallo_rcv = true;
    }
    if(bytes_recibidos == (size_t)length - 1){
      bytes_recibidos = 0;
    }
    if(resultado == 0){
      termine = true;
    }
  }
  printf("\n");
  return EXITO;
}
