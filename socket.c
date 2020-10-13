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
    resultados++;
  }
  if(self->fd == -1){
      return -1;
  }
    return 0;
}
/*
int socket_bind_and_listen(socket_t* self, const char* host, const char* service){

  int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
  int listen(int sockfd, int backlog);

}
*/

  //socket(int domain, int type, int protocol
