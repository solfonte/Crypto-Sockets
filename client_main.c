#define CANTIDAD_ARG 5
#define SOBRAN_ARG "SOBRAN ARGUMENTOS"
#define FALTAN_ARG "FALTAN ARGUMENTOS"
#define POSICION_PUERTO 2
#define POSICION_HOST 1
#define POSICION_METODO 3
#define POSICION_KEY 4
#define POSICION_ARCHIVO 5
#define TAMANIO_HOST 15
#define TAMANIO_PUERTO 10
#define TAMANIO_METODO 10
#define TAMANIO_KEY 150
#include "common_cryptosocket.h"
#include "client_lector_de_texto.h"
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

void datos_cliente_uninit(char* host,char* puerto,
                          char* metodo,char* key){

}

int datos_cliente_init(char const* datos[],char* host,
                      char* puerto,char* metodo,char* key){
  strncpy(host,datos[POSICION_HOST],TAMANIO_HOST);
  strncpy(puerto,datos[POSICION_PUERTO],TAMANIO_PUERTO);
  strncpy(metodo,datos[POSICION_METODO] + 9,TAMANIO_METODO);
  strncpy(key,datos[POSICION_KEY] + 6,TAMANIO_KEY);
  return EXITO;
}

int main(int argc, char const *argv[]) {
  if (argc != CANTIDAD_ARG){
    printf("ERROR: %s",argc < CANTIDAD_ARG? FALTAN_ARG:SOBRAN_ARG);
    return 0;
  }

  char puerto[TAMANIO_PUERTO],metodo[TAMANIO_METODO];
  char key[TAMANIO_KEY],host[TAMANIO_HOST];
  socket_t client;
  lector_de_texto_t lector;
  cryptosocket_t cryptosocket;
  encriptador_t encriptador;
  cesar_t cesar;
  vigenere_t vigenere;
  rc4_t rc4;

  datos_cliente_init(argv,host,puerto,metodo,key);
  int res_init = encriptador_init(&encriptador,&cesar,&vigenere,&rc4,metodo,key);
  if(res_init == ERROR){
    datos_cliente_uninit(host,puerto,metodo,key);
    return 0;
  }
  lector_de_texto_init(&lector);
  int res_connect = socket_connect(&client,host,puerto);
  if (res_connect == -1){
    printf("No pudo conectarse al servidor. Error: %s\n",strerror(errno));
    socket_uninit(&client,SHUT_WR);
    return 0;
  }
  cryptosocket_init(&cryptosocket,&client,&encriptador);
  int res_iterar = lector_de_texto_iterar(&lector,_cryptosocket_enviar_mensaje,
                                          &cryptosocket);
  if (res_iterar == ERROR){
    printf("No se pudo enviar el mensaje correctamente\n");
  }
  socket_uninit(&client,SHUT_WR);
  lector_de_texto_uninit(&lector);

  return 0;
}
