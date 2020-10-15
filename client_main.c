#define CANTIDAD_ARGUMENTOS 6
#define SOBRAN_ARGUMENTOS "SOBRAN ARGUMENTOS"
#define FALTAN_ARGUMENTOS "FALTAN ARGUMENTOS"
#define POSICION_PUERTO 2
#define POSICION_HOST 1
#define POSICION_METODO 3
#define POSICION_KEY 4
#define POSICION_ARCHIVO 5
#define TAMANIO_HOST 15
#define TAMANIO_PUERTO 10
#define TAMANIO_METODO 10
#define TAMANIO_KEY 30
#define TAMANIO_NOMBRE_ARCHIVO 150
#define ERROR -1

#include "lector_de_texto.h"
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
  strncpy((char*)host,argv[POSICION_HOST],TAMANIO_HOST);
  strncpy((char*)puerto,argv[POSICION_PUERTO],TAMANIO_PUERTO);
  strncpy((char*)metodo,argv[POSICION_METODO] + 9,TAMANIO_METODO);
  strncpy((char*)key,argv[POSICION_KEY] + 6,TAMANIO_KEY);//ver que onda por el largo
  strncpy((char*)archivo,argv[POSICION_ARCHIVO],TAMANIO_NOMBRE_ARCHIVO);//ver que onda por el largo

  lector_de_texto_t lector;
  lector_de_texto_init(&lector,archivo);
  printf("archivo desde el lector: %s",archivo);

  if(socket_connect(&client,host,puerto) == ERROR){
    printf("l:%s\n",strerror(errno));
    return ERROR;
  }
  char buffer[200] = "hola";
  FILE* file = fopen(archivo,"r");
  size_t leidos = fread((void*)buffer,sizeof(char*),200,file);
  size_t total_bytes_left = leidos;
  ssize_t bytes_enviados = 0;

  printf("leo: %s y lei bytes:%lu\n",buffer,leidos);

  while(total_bytes_left > 0 && bytes_enviados != ERROR /*&& leidos > 0*/){
    //lector_de_texto_leer()
    bytes_enviados = socket_send(&client,buffer,total_bytes_left);
    printf("bytes enviadoss: %lu\n",bytes_enviados);

    if(bytes_enviados != ERROR){
      leidos = fread((void*)buffer,sizeof(char*),10,file);
      printf("bytes leidos devuelta: %lu\n",bytes_enviados);
      total_bytes_left = total_bytes_left - (size_t)bytes_enviados + leidos;
    }
  }
  fclose(file);


  socket_shutdown(&client,SHUT_WR);
  socket_uninit(&client);
  lector_de_texto_uninit(&lector);

  return 0;
}
//./client 127.0.0.1 8080 --method=rc4 --key=queso < __client_stdin__
