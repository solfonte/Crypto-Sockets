#define CANTIDAD_ARGUMENTOS 4
#define SOBRAN_ARGUMENTOS "SOBRAN ARGUMENTOS"
#define FALTAN_ARGUMENTOS "FALTAN ARGUMENTOS"
#define POSICION_PUERTO 1
#define POSICION_METODO 2
#define POSICION_KEY 3
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  if(argc != CANTIDAD_ARGUMENTOS){
    printf("ERROR: %s",argc < CANTIDAD_ARGUMENTOS? FALTAN_ARGUMENTOS:SOBRAN_ARGUMENTOS);
    return 0;
  }
  int puerto = atoi(argv[POSICION_PUERTO]);
  //paasar a strcnpy
  char const* metodo = argv[POSICION_METODO] + 9;
  char const* key = argv[POSICION_KEY] + 6;
  printf("puerto: %i\n",puerto);
  printf("metodo: %s\n",metodo);
  printf("key: %i\n",atoi(key));
  return 0;
}
