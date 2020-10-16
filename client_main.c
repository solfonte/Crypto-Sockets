#define CANTIDAD_ARGUMENTOS 5
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
#include "common_cryptosocket.h"
#include "client_lector_de_texto.h"
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>//sacar despues


int datos_cliente_init(char const* datos[],char* host,char* puerto,char* metodo,char* key){
  //hacer chequeoss
  strncpy(host,datos[POSICION_HOST],TAMANIO_HOST);
  printf("host: %s\n",host);
  strncpy(puerto,datos[POSICION_PUERTO],TAMANIO_PUERTO);
  printf("puerto: %s\n",puerto);
  strncpy(metodo,datos[POSICION_METODO] + 9,TAMANIO_METODO);
  printf("metodo: %s\n",metodo);
  strncpy(key,datos[POSICION_KEY] + 6,TAMANIO_KEY);//ver que onda por el largo
  printf("key: %s\n",key);
  //strncpy(archivo,datos[POSICION_ARCHIVO],TAMANIO_NOMBRE_ARCHIVO);//ver que onda por el largo
  return EXITO;
}

//./client 127.0.0.1 8080 --method=rc4 --key=queso < __client_stdin__

int main(int argc, char const *argv[]) {
  if (argc != CANTIDAD_ARGUMENTOS){
    printf("ERROR: %s",argc < CANTIDAD_ARGUMENTOS? FALTAN_ARGUMENTOS:SOBRAN_ARGUMENTOS);
    return 0;
  }

  char puerto[TAMANIO_PUERTO],metodo[TAMANIO_METODO],key[TAMANIO_KEY],host[TAMANIO_HOST]/*,archivo[TAMANIO_NOMBRE_ARCHIVO]*/;//cambiar despues a stdin
  socket_t client;
  lector_de_texto_t lector;
  cryptosocket_t cryptosocket;
  encriptador_t encriptador;
  //verificar retorno
  datos_cliente_init(argv,host,puerto,metodo,key/*,archivo*/);
  lector_de_texto_init(&lector/*,archivo*/);
  encriptador_init(&encriptador,metodo,(void*)key);

  //lector_de_texto_init(&lector,stdin);
  if (socket_connect(&client,host,puerto) == ERROR){
    printf("No pudo conectarse al servidor. Error: %s\n",strerror(errno));
    socket_uninit(&client,SHUT_WR);
    return 0;
  }
  cryptosocket_init(&cryptosocket,&client,&encriptador);
  int resultado_iterar = lector_de_texto_iterar(&lector,_cryptosocket_enviar_mensaje_encriptado,&cryptosocket);
  if (resultado_iterar == ERROR){
    printf("No se pudo enviar el mensaje correctamente\n");
  }
  socket_uninit(&client,SHUT_WR);
  lector_de_texto_uninit(&lector);

  return 0;
}
