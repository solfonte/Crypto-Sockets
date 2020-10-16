#include "cryptosocket_encriptar.h"

int cryptosocket_init(cryptosocket_t* cryptosocket,int (*encriptador_callback)(char* buffer,void*key)){

}

int cryptosocket_cifrar(const char *buffer, size_t tamanio, void *callback_ctx){
  cryptosocket_t* cryptosocket = callback_ctx;
  int resultado_cifrar = cryptosocket->metodo((char*)buffer,cryptosocket->key);
  return (resultado_cifrar == ERROR? ERROR: socket_send(client,buffer,tamanio));


}
