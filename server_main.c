#define CANTIDAD_ARG 4
#define SOBRAN_ARG "SOBRAN ARGUMENTOS"
#define FALTAN_ARG "FALTAN ARGUMENTOS"
#define POSICION_PUERTO 1
#define POSICION_METODO 2
#define POSICION_KEY 3
#define TAMANIO_PUERTO 10
#define TAMANIO_METODO 10
#define TAMANIO_KEY 150
#define TAMANIO_RESPUESTA 10
#define ERROR -1
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>//sacar despues
#include "common_cryptosocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int datos_servidor_init(char const *datos[],char* puerto,
                        char* metodo,char* key){
  strncpy(puerto,datos[POSICION_PUERTO],TAMANIO_PUERTO);
  strncpy(metodo,datos[POSICION_METODO] + 9,TAMANIO_METODO);
  strncpy(key,datos[POSICION_KEY] + 6,TAMANIO_KEY);
  //ver que onda por el largo y chequear estso errores
  return EXITO;
}

int main(int argc, char const *argv[]) {
  if (argc != CANTIDAD_ARG){
    printf("ERROR: %s",(argc < CANTIDAD_ARG? FALTAN_ARG:SOBRAN_ARG));
    return ERROR;
  }
  char puerto[TAMANIO_PUERTO],metodo[TAMANIO_METODO],key[TAMANIO_KEY];
  socket_t socket_aceptador,peer;
  int resultado;
  encriptador_t encriptador;
  cryptosocket_t cryptosocket;

  //verificar devolucion
  datos_servidor_init(argv,puerto,metodo,key);
  encriptador_init(&encriptador,metodo,(void*)key);

  resultado = socket_bind_and_listen(&socket_aceptador, INADDR_ANY,puerto);
  if (resultado == ERROR){
    printf("No se pudo crear el servidor\n");
    return 0;
  }
  resultado = socket_accept(&socket_aceptador,&peer);
  if (resultado == ERROR){
    socket_uninit(&socket_aceptador,SHUT_RD);
    printf("No se pudo conectar con el cliente\n");
    return 0;
  }
  cryptosocket_init(&cryptosocket,&peer,&encriptador);
  //socket_receive(&peer,buffer,TAMANIO_RESPUESTA);
  socket_receive(&peer,_cryptosocket_recibir_mensaje,&cryptosocket);

  socket_uninit(&peer,SHUT_RD);
  socket_uninit(&socket_aceptador,SHUT_RD);
  return 0;
}
