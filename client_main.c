#define CANTIDAD_ARGUMENTOS 7
#define SOBRAN_ARGUMENTOS "SOBRAN ARGUMENTOS"
#define FALTAN_ARGUMENTOS "FALTAN ARGUMENTOS"
#define POSICION_PUERTO 2
#define POSICION_HOST 1
#define POSICION_METODO 3
#define POSICION_KEY 4
#define POSICION_ARCHIVO 6
#define TAMANIO_HOST 15
#define TAMANIO_PUERTO 10
#define TAMANIO_METODO 10
#define TAMANIO_KEY 30
#define TAMANIO_NOMBRE_ARCHIVO 150
#define ERROR -1

//#include "file_reader.h"
#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(int argc, char const *argv[]) {
  char const puerto[TAMANIO_PUERTO],metodo[TAMANIO_METODO],key[TAMANIO_KEY],host[TAMANIO_HOST],archivo[TAMANIO_NOMBRE_ARCHIVO];//cambiar este nombre ;
  socket_t client;
  if(argc != CANTIDAD_ARGUMENTOS){
    printf("ERROR: %s",argc < CANTIDAD_ARGUMENTOS? FALTAN_ARGUMENTOS:SOBRAN_ARGUMENTOS);
    return 0;
  }
  lector_de_texto_t lector;
  lector_de_texto_init(&lector,archivo);

  strncpy((char*)host,argv[POSICION_HOST],TAMANIO_HOST);
  strncpy((char*)puerto,argv[POSICION_PUERTO],TAMANIO_PUERTO);
  strncpy((char*)metodo,argv[POSICION_METODO] + 9,TAMANIO_METODO);
  strncpy((char*)key,argv[POSICION_KEY] + 6,TAMANIO_KEY);//ver que onda por el largo
  strncpy((char*)archivo,argv[POSICION_ARCHIVO],TAMANIO_NOMBRE_ARCHIVO);//ver que onda por el largo

  if(socket_connect(&client,host,puerto) == ERROR){
    printf("l:%s\n",strerror(errno));
    return ERROR;
  }
  char buffer[10] = "hola";
  size_t length = 5;
  size_t total_bytes_left = length;
  ssize_t bytes_enviados = 0;
  while(total_bytes_left > 0 && bytes_enviados != ERROR){
    bytes_enviados = socket_send(&client,buffer,total_bytes_left);
    if(bytes_enviados != ERROR){
      total_bytes_left = total_bytes_left - (size_t)bytes_enviados;
    }
  }
  socket_shutdown(&client,SHUT_WR);
  socket_uninit(&client);


  return 0;
}
//./client 127.0.0.1 8080 --method=rc4 --key=queso < __client_stdin__
