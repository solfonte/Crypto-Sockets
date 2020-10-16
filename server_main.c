#define CANTIDAD_ARGUMENTOS 4
#define SOBRAN_ARGUMENTOS "SOBRAN ARGUMENTOS"
#define FALTAN_ARGUMENTOS "FALTAN ARGUMENTOS"
#define POSICION_PUERTO 1
#define POSICION_METODO 2
#define POSICION_KEY 3
#define TAMANIO_PUERTO 10
#define TAMANIO_METODO 10
#define TAMANIO_KEY 150
#define TAMANIO_RESPUESTA 10
#define ERROR -1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>//sacar despues
#include "cryptosocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int datos_servidor_init(char const *datos[],char* puerto,char* metodo,char* key){
  strncpy(puerto,datos[POSICION_PUERTO],TAMANIO_PUERTO);
  strncpy(metodo,datos[POSICION_METODO] + 9,TAMANIO_METODO);
  strncpy(key,datos[POSICION_KEY] + 6,TAMANIO_KEY);//ver que onda por el largo y chequear estso errores
  return EXITO;
}



int main(int argc, char const *argv[]) {
  if(argc != CANTIDAD_ARGUMENTOS){
    printf("ERROR: %s",(argc < CANTIDAD_ARGUMENTOS? FALTAN_ARGUMENTOS:SOBRAN_ARGUMENTOS));
    return ERROR;
  }
  char puerto[TAMANIO_PUERTO],metodo[TAMANIO_METODO],key[TAMANIO_KEY];
  char buffer[TAMANIO_RESPUESTA];//capaz no hace falta esto aca, sino adentro de recv directamente
  socket_t socket_aceptador,peer;
  int resultado;
  encriptador_t encriptador;
  cryptosocket_t cryptosocket;

  //verificar devolucion
  datos_servidor_init(argv,puerto,metodo,key);
  encriptador_init(&encriptador,encriptador_cesar_descifrar,(void*)key);

  resultado = socket_bind_and_listen(&socket_aceptador, INADDR_ANY,puerto);
  if(resultado == ERROR){
    printf("No se pudo crear el servidor\n");
    return 0;
  }
  resultado = socket_accept(&socket_aceptador,&peer);
  if(resultado == ERROR){
    socket_uninit(&socket_aceptador,SHUT_RD);
    printf("No se pudo conectar con el cliente\n");
    return 0;
  }
  cryptosocket_init(&cryptosocket,&peer,&encriptador);
//  socket_receive(&peer,buffer,TAMANIO_RESPUESTA);
  _cryptosocket_recibir_mensaje_encriptado(&cryptosocket,buffer,TAMANIO_RESPUESTA);
  socket_uninit(&peer,SHUT_RD);
  socket_uninit(&socket_aceptador,SHUT_RD);
  return 0;
}
