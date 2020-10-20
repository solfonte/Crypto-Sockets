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
  encriptador_cesar_t cesar;
  encriptador_vigenere_t vigenere;
  encriptador_rc4_t rc4;

  datos_cliente_init(argv,host,puerto,metodo,key);
  encriptador_init(&encriptador,&cesar,&vigenere,&rc4,metodo,key);
  lector_de_texto_init(&lector);
  int res_connect = socket_connect(&client,host,puerto);
  if (res_connect == ERROR){
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
  //cryptosocket_uninit(&cryptosocket,&client,&encriptador);
  socket_uninit(&client,SHUT_WR);
  lector_de_texto_uninit(&lector);
  //encriptador_uninit(&encriptador,&cesar,&vigenere,&rc4);
  return 0;
}
