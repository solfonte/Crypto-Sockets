#define CANTIDAD_ARGUMENTOS 4
#define SOBRAN_ARGUMENTOS "SOBRAN ARGUMENTOS"
#define FALTAN_ARGUMENTOS "FALTAN ARGUMENTOS"
#define POSICION_PUERTO 1
#define POSICION_METODO 2
#define POSICION_KEY 3
#define TAMANIO_PUERTO 10
#define TAMANIO_METODO 10
#define TAMANIO_KEY 30
#define ERROR -1
#include <stdio.h>
#include <stdlib.h>
/*#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>*/
#include <string.h>
#include "socket.h"




int main(int argc, char const *argv[]) {
  char const puerto[TAMANIO_PUERTO],metodo[TAMANIO_METODO],key[TAMANIO_KEY];
  struct addrinfo hints;
  struct addrinfo *resultados/*, *ptr*/;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;

  socket_t socket_aceptador/*,peer*/;
//  inicializar_hints(&hints);
  if(argc != CANTIDAD_ARGUMENTOS){
    printf("ERROR: %s",(argc < CANTIDAD_ARGUMENTOS? FALTAN_ARGUMENTOS:SOBRAN_ARGUMENTOS));
    return ERROR;
  }
  strncpy((char*)puerto,argv[POSICION_PUERTO],TAMANIO_PUERTO);
  strncpy((char*)metodo,argv[POSICION_METODO] + 9,TAMANIO_METODO);
  strncpy((char*)key,argv[POSICION_KEY] + 6,TAMANIO_KEY);//ver que onda por el largo

  //pasar a strcpy capaz
/*  if(validar_argumentos(argc,argv,puerto,metodo,key) == ERROR){
    return 0;
  }*/
  int local = getaddrinfo(0,/*puerto*/"8080", &hints,&resultados);
  int resultado = socket_init(&socket_aceptador,resultados);
  freeaddrinfo(resultados);
  if(resultado == ERROR){
    printf("Fallo");//mejorar este mensaje
  }
  printf("s:%i\n",socket_aceptador.fd);
  printf("l:%i\n",local);

  //socket_bind_and_listen(&socket_aceptador, const char* host, const char* service);


  printf("puerto: %i\n",atoi(puerto));
  printf("metodo: %s\n",metodo);
  printf("key: %i\n",atoi(key));
  return 0;
}
