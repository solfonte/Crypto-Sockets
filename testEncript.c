#include "common_encriptador.h"
#include <stdio.h>
#include <string.h>


int main(){
  char cadena[] = "hola";
  char cadena2[] = "Secret message";
  char cadena3[] = "Pan";
  char key[] = "SecureKey";
  char key2[] = "queso";
  char cadenita[]  = "hola";
  printf("tamanio: %zu",strlen(cadenita));
  printf("cadena: %s\n",cadena);
  encriptador_cesar(cadena,4,"3",CIFRAR);
  printf("cifradaConCesar: %s\n",cadena);
  encriptador_cesar(cadena,4,"3",DESCIFRAR);
  printf("descifradaConCesar: %s\n",cadena);

  printf("cadena: %s\n",cadena2);
  encriptador_vigenere(cadena2,14,key,CIFRAR);
  printf("cifradaConVigenere: %s\n",cadena2);
  encriptador_vigenere(cadena2,14,key,DESCIFRAR);
  printf("descifradaConVigenere: %s\n",cadena2);
  printf("cadena: %s\n",cadena3);
  encriptador_rc4(cadena3,3,key2);
  printf("cifradaConRC4: %s\n",cadena3);
  encriptador_rc4(cadena3,3,key2);
  printf("descifradaConRC4: %s\n",cadena3);

  return 0;
}
