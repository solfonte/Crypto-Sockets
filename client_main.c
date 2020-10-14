#define CANTIDAD_ARGUMENTOS 7
#define SOBRAN_ARGUMENTOS "SOBRAN ARGUMENTOS"
#define FALTAN_ARGUMENTOS "FALTAN ARGUMENTOS"
#define POSICION_PUERTO 2
#define POSICION_HOST 1
#define POSICION_METODO 3
#define POSICION_KEY 4
#define POSICION_ARCHIVO 6
#define TAMANIO_HOST 15

#include "file_reader.h"
#include "socket.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  char const* metodo,puerto,key,host;
  socket_t client;
  if(argc != CANTIDAD_ARGUMENTOS){
    printf("ERROR: %s",argc < CANTIDAD_ARGUMENTOS? FALTAN_ARGUMENTOS:SOBRAN_ARGUMENTOS);
    return 0;
  }/*
  file_reader_t file_reader;
  file_reader_init(&file_reader);
  socket_t socket;
  socket_init(&socket);
*/
  strncpy((char*)host,argv[POSICION_HOST],TAMANIO_HOST);
  strncpy((char*)puerto,argv[POSICION_PUERTO],TAMANIO_PUERTO);
  strncpy((char*)metodo,argv[POSICION_METODO] + 9,TAMANIO_METODO);
  strncpy((char*)key,argv[POSICION_KEY] + 6,TAMANIO_KEY);//ver que onda por el largo
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  int resultado = socket_connect(&client,host,puerto);
  //int local = getaddrinfo(host,puerto, &hints,&resultados);
  if(local < 0){
    printf("l:%s\n",strerror(errno));
    return ERROR;
  }
/*
  file_reader_init(&file_reader);
  socket_uninit(&socket);
*/
  return 0;
}
//./client 127.0.0.1 8080 --method=rc4 --key=queso < __client_stdin__
