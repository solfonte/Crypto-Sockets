#define CANTIDAD_ARGUMENTOS 4
#define SOBRAN_ARGUMENTOS "SOBRAN ARGUMENTOS"
#define FALTAN_ARGUMENTOS "FALTAN ARGUMENTOS"
#define POSICION_PUERTO 1
#define POSICION_METODO 2
#define POSICION_KEY 3
#include <stdio.h>
#include <stdlib.h>


int validar_argumentos(int puerto,const char* metodo,const char key){
  if(argc != CANTIDAD_ARGUMENTOS){
    printf("ERROR: %s",argc < CANTIDAD_ARGUMENTOS? FALTAN_ARGUMENTOS:SOBRAN_ARGUMENTOS);
    return ERROR;
  }
  puerto = /*atoi(*/argv[POSICION_PUERTO]/*)*/;
  metodo = argv[POSICION_METODO] + 9;
  key = argv[POSICION_KEY] + 6;
  //pasar a strcpy capaz
}
/*int*/void inicializar_hints(struct addrinfo* hints){
  memset(/*&*/hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
}

int main(int argc, char const *argv[]) {
  int puerto;
  char const* puerto,metodo,key;
  struct addrinfo hints;
  struct addrinfo *resultados/*, *ptr*/;
  addrinfo hints;
  socket_t socket_aceptador,peer;
  inicializar_hints(&hints);
  if(validar_argumentos(puerto,metodo,key) == ERROR){
    return 0;
  }
  int local = getaddrinfo(0,puerto, &hints,resultados);
  int resultado = socket_init(&socket_aceptador,&resultados);
  if(resultado == ERROR){
    printf("Fallo");//mejorar este mensaje
  }
  //socket_bind_and_listen(&socket_aceptador, const char* host, const char* service);



//  printf("puerto: %i\n",puerto);
//  printf("metodo: %s\n",metodo);
//  printf("key: %i\n",atoi(key));
  return 0;
}
