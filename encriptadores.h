#ifndef __ENCRIPTADORES_H__
#define __ENCRIPTADORES_H__

/*precondiciones: la funcion recibe una cadena inicializada
postcondiciones: la funcion encripta la cadena recibida por parametros por cifrado de cesar.
devuelve EXITO en caso de encriptar correctamente y ERROR en caso de no poder*/
int cifrado_de_cesar(char*cadena,int key);
int descifrado_de_cesar(char*cadena,int key);


#endif /*__ENCRIPTADORES_H__*/
