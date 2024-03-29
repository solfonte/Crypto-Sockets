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
#include "common_cryptosocket.h"

/*la funcion desinicializa los datos recibidos
 por parametro*/
int datos_servidor_uninit(char* puerto,
                        char* metodo,char* key){
  return 0;
}

/*la funcion inicializa los datos recibidos por parametro*/
int datos_servidor_init(char const *datos[],char* puerto,
                        char* metodo,char* key){
  strncpy(puerto,datos[POSICION_PUERTO],TAMANIO_PUERTO);
  strncpy(metodo,datos[POSICION_METODO] + 9,TAMANIO_METODO);
  strncpy(key,datos[POSICION_KEY] + 6,TAMANIO_KEY);
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
  cesar_t cesar;
  vigenere_t vigenere;
  rc4_t rc4;

  datos_servidor_init(argv,puerto,metodo,key);
  int res_init = encriptador_init(&encriptador,&cesar,
                                  &vigenere,&rc4,metodo,key);
  if (res_init == ERROR){
    return 0;
  }
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
  socket_receive(&peer,cryptosocket_recibir_mensaje,&cryptosocket);
  cryptosocket_uninit(&cryptosocket);
  socket_uninit(&peer,SHUT_RD);
  socket_uninit(&socket_aceptador,SHUT_RD);
  encriptador_uninit(&encriptador,&cesar,&vigenere,&rc4);
  datos_servidor_uninit(puerto,metodo,key);
  return 0;
}
