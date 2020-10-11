#define CANTIDAD_ARGUMENTOS_SERVIDOR 4
#define SOBRAN_ARGUMENTOS "SOBRAN ARGUMENTOS"
#define FALTAN_ARGUMENTOS "FALTAN ARGUMENTOS"
#define POSICION_PUERTO 0

int int main(int argc, char const *argv[]) {
  if(argc != CANTIDAD_ARGUMENTOS){
    printf("ERROR: %s",argc < CANTIDAD_ARGUMENTOS? FALTAN_ARGUMENTOS:SOBRAN_ARGUMENTOS);
    return 0;
  }
  int puerto = *(int*)argv[POSICION_PUERTO];
  char* metodo = (char*)(argv[POSICION_METODO] + 9);
  void* key = argv[POSICION_KEY] + 6;

  return 0;
}
