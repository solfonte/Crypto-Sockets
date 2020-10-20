# TP1-Taller  
Nombre: Maria Sol Fontenla.  
Padron: 103870.  
Link al repositorio:https://github.com/solfonte/TP1-Taller.  

## Descripcion general del trabajo realizado  
Para el desarrollo del trabajo practico, se implementaron tanto el emisor y el receptor. Para la comunicacion de estas dos partes, se utilizan los metodos de clave simetrica Cesar, Vigenere y RC4.  

**implementacion del emisor o cliente**
El cliente recibe la clave y el metodo a utilizar, ademas del archivo a cifrar por entrada estandar. A medida que se itera sobre el archivo recibido, un TDA cryptosocket que recibe lo leido del archivo, combina la tareas de cifrado de clave y envio del mensaje a traves de un socket. Cuando el cliente ya envio todo el mensaje, este finaliza la conexion cerrando el socket de su parte.  

**implementacion del receptor o servidor**  
El servidor recibe la clave y el metodo a utilizar. Mediante la conexion entre los sockets del cliente y el servidor, el servidor recibe la cadena cifrada y la descifra mediante un cryptosocket, pero en este caso el cryptosocket descifra e imprime por salida estandar la cadena descifrada.  

**decisiones de implementacion y comentarios adicionales**  
-sobre la implementacion del TDA encriptador: este es un encriptador generico que sabe interpretar que metodo se debe utilizar. Este encapsula la eleccion del metodo a la hora de cifrar/descifrar. Se implemento de esta manera para poder separar los tres metodos de encriptacion en TDAs distintos y asi poder crear la estructura cryptosocket, que no necesita saber que metodo se utiliza para encriptar. De todas formas, no fue la eleccion mas optima a la hora de encriptar ya que este chequea para cada encriptacion, que metodo debe utilizar.  
-sobre la declaracion de los metodos cesar, vigenere y rc4 en el main del receptor y en el main del cliente: se implemento de esta manera para poder utilizar el stack y no el heap, ya que no se que metodo se va a ingresar por parametros (dadas las tres posibilidades), y de esta forma declarandolos puedo elegir cual utilizar. En este caso se ocupa espacio de mas en el stack.  
-se eligio arbitrariamente que el tamanio de la clave a utilizar tenga un maximo de 150.  
-para el caso del envio del mensaje cifrado, se decidio que el envio del mensaje a traves del socket se realice dentro del cryptosocket ya que este ultimo cifra y luego se envia el mensaje. Pero para el caso de recibir el mensaje cifrado a traves del socket, se decidio que este reciba un puntero a una funcion para asi ir desencriptando a medida que llega el mensaje. O sea, para el caso del socket_send se cifra y luego se envia, y para el caso del socket_receive es al revez: se recibe y despues se desencripta.  
-se mantuvo el menor acoplamiento posible entre los TDA socket,cryptosocket y los distintos encriptadores.  
-para el caso del servidor, como la funcion getaddrinfo solo devuelve un resultado posible para finalizar la conexion, no fue necesario iterar sobre cada resultado.  
**Diagrama de clases general**  
![Alt Text](clasesTP1.png)
