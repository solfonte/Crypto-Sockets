#ifndef __ENCRIPTADORES_H__
#define __ENCRIPTADORES_H__
#define ERROR -1
#define EXITO 0
/*precondiciones: la funcion recibe una cadena inicializada
postcondiciones: la funcion encripta la cadena recibida por parametros por cifrado de cesar.
devuelve EXITO en caso de encriptar correctamente y ERROR en caso de no poder*/
int cifrado_de_cesar(char* cadena,void* key);
int descifrado_de_cesar(char* cadena,void* key);
int cifrado_de_vigenere(char* cadena,void* key);
int descifrado_de_vigenere(char* cadena,void* key);//seguro hay que castear a void las key en los sockets
int cifrado_de_rc4(char* cadena,void* key);
int descifrado_de_rc4(char* cadena,void* key);
//int descifrado_de_rc4(char* cadena,char* key);


#endif /*__ENCRIPTADORES_H__*/
