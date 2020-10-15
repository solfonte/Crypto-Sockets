#define CANTIDAD_ARGUMENTOS 4
#define SOBRAN_ARGUMENTOS "SOBRAN ARGUMENTOS"
#define FALTAN_ARGUMENTOS "FALTAN ARGUMENTOS"
#define POSICION_PUERTO 1
#define POSICION_METODO 2
#define POSICION_KEY 3
#define TAMANIO_PUERTO 10
#define TAMANIO_METODO 10
#define TAMANIO_KEY 150
#define ERROR -1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>//sacar despues
#include "socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char const *argv[]) {
  if(argc != CANTIDAD_ARGUMENTOS){
    printf("ERROR: %s",(argc < CANTIDAD_ARGUMENTOS? FALTAN_ARGUMENTOS:SOBRAN_ARGUMENTOS));
    return ERROR;
  }
  char const puerto[TAMANIO_PUERTO],metodo[TAMANIO_METODO],key[TAMANIO_KEY];
  /*en otra funcion*/

  socket_t socket_aceptador,peer;
  strncpy((char*)puerto,argv[POSICION_PUERTO],TAMANIO_PUERTO);
  strncpy((char*)metodo,argv[POSICION_METODO] + 9,TAMANIO_METODO);
  strncpy((char*)key,argv[POSICION_KEY] + 6,TAMANIO_KEY);//ver que onda por el largo y chequear estso errores

  /*******************/

  socket_bind_and_listen(&socket_aceptador, INADDR_ANY,puerto);
  int resultado = socket_accept(&socket_aceptador,&peer);

  if(resultado == ERROR){
    socket_shutdown(&socket_aceptador,SHUT_RD);
    socket_uninit(&socket_aceptador);
    printf("ERROR: FALLO LA CONEXION\n");
  }
  printf("aceptar:%i \n",resultado);

  char buffer[10];
  ssize_t bytes_recibidos = socket_receive(&peer,buffer,10);
  while(bytes_recibidos > 0){
    printf("%s",buffer);
    bytes_recibidos = socket_receive(&peer,buffer,10);
  }
  //capaz mergear el shutdown y el uninit
  socket_shutdown(&peer,SHUT_RD);
  socket_uninit(&peer);
  socket_shutdown(&socket_aceptador,SHUT_RD);
  socket_uninit(&socket_aceptador);
//ssize_t recv(int sockfd, void *buf, size_t len, int flags);
  return 0;
}
