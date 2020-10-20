#ifndef __SOCKET_H__
#define __SOCKET_H__
#define ERROR -1
#define EXITO 0

#define _POSIX_C_SOURCE 200112L
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

typedef struct{
  int fd;
} socket_t;

/*la funcion inicializa el socket recibido por parametro*/
int socket_init(socket_t* self,struct addrinfo* resultados);

/*la funcion desinicializa el socket recibido por parametro*/
int socket_uninit(socket_t* self,int modo_de_shutdown);

/*la funcion realiza el bind y el listen para el socket
recibido por parametro (el cual se encuentra
desinicializado). Devuelve ERROR en caso de error
y EXITO en caso de realizar correctamente las operaciones*/
int socket_bind_and_listen(socket_t* self,
                            const char* host,
                            const char* service);

/*La funcion realiza el accept del socket recibido por parametro,
el cual debe estar inicializado. Devuelve ERROR en caso
de fallar y EIXITO si pudo aceptar*/
int socket_accept(socket_t* listener, socket_t* peer);

/*la funcion conecta el socket recibido por parametro (desinicializado)
y devuelve ERROR en el caso de fallar y EXITO si pudo conectar*/
int socket_connect(socket_t *self, const char *host, const char *service);

/*la funcion envia un mensaje a traves del socket recibido por
 parametro. Devuelve ERROR en caso de fallar y EXITO si
 pudo enviar correctamente*/
int socket_send(socket_t* self, const char* buffer, size_t length);

/*la funcion recibe un mensaje a traves del socket recibido por
 parametro. Devuelve ERROR en caso de fallar y EXITO si
 pudo recibir correctamente*/
int socket_receive(socket_t* self,
                  int (*socket_callback)(char* chunk,size_t tamanio,
                  void* callback_ctx),void*callback_ctx);
#endif
