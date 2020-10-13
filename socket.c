#include "socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int socket_init(socket_t* self,struct addrinfo* resultados){
  bool creado = false
  while(resultados != NULL && !creado){
    socket->fd = socket(resultados->ai_family, resultados->ai_socktype, reultados->ai_protocol);
    if(socket != -1){
      creado = true;
    }
    return (socket == -1? ERROR: EXITO)
  }

  //socket(int domain, int type, int protocol
}
