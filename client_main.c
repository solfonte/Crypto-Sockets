#define CANTIDAD_ARGUMENTOS 7
#define SOBRAN_ARGUMENTOS "SOBRAN ARGUMENTOS"
#define FALTAN_ARGUMENTOS "FALTAN ARGUMENTOS"
#define POSICION_IP 1
#define POSICION_PUERTO 2
#define POSICION_METODO 3
#define POSICION_KEY 4
#define POSICION_ARCHIVO 6

#include <stdio.h>
#include <stdlib.h>
/*
int main(int argc, char const *argv[]) {
  if(argc != CANTIDAD_ARGUMENTOS){
    printf("ERROR: %s",argc < CANTIDAD_ARGUMENTOS? FALTAN_ARGUMENTOS:SOBRAN_ARGUMENTOS);
    return 0;
  }
  int puerto = atoi(argv[POSICION_IP]);
  char const* metodo = argv[POSICION_METODO] + 9;
  char const* key = argv[POSICION_KEY] + 6;
  printf("puerto: %i\n",puerto);
  printf("metodo: %s\n",metodo);
  printf("key: %i\n",atoi(key));
  return 0;*/
}
//./client 127.0.0.1 8080 --method=rc4 --key=queso < __client_stdin__
