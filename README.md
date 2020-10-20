# TP1-Taller  
Nombre: Maria Sol Fontenla.  
Padrón: 103870.  
Link al repositorio:https://github.com/solfonte/TP1-Taller.  

## Descripción general del trabajo realizado  
Para el desarrollo del trabajo práctico, se implementaron tanto el emisor y el receptor. Para la comunicación de estas dos partes, se utilizan los métodos de clave simétrica Cesar, Vigenere y RC4.  

**implementacion del emisor o cliente**
El cliente recibe la clave y el método a utilizar, además del archivo a cifrar por entrada estándar. A medida que se itera sobre el archivo recibido, un TDA cryptosocket que recibe lo leído del archivo, combina las tareas de cifrado de clave y envío del mensaje a través de un socket. Cuando el cliente ya envió todo el mensaje, este finaliza la conexión cerrando el socket de su parte.  

**implementación del receptor o servidor**  
El servidor recibe la clave y el método a utilizar. Mediante la conexión entre los sockets del cliente y el servidor, el servidor recibe la cadena cifrada y la descifra mediante un cryptosocket, pero en este caso el cryptosocket descifra e imprime por salida estándar la cadena descifrada.  

**decisiones de implementación y comentarios adicionales**  
-sobre la implementacion del TDA encriptador: este es un encriptador generico que sabe interpretar que metodo se debe utilizar. Este encapsula la eleccion del metodo a la hora de cifrar/descifrar. Se implemento de esta manera para poder separar los tres metodos de encriptacion en TDAs distintos y asi poder crear la estructura cryptosocket, que no necesita saber que metodo se utiliza para encriptar. De todas formas, no fue la eleccion mas optima a la hora de encriptar ya que este chequea para cada encriptacion, que metodo debe utilizar.  
-sobre la declaración de los métodos cesar, vigenere y rc4 en el main del receptor y en el main del cliente: se implementó de esta manera para poder utilizar el stack y no el heap, ya que no se que metodo se va a ingresar por parámetros (dadas las tres posibilidades), y de esta forma declarando los puedo elegir cual utilizar sin la necesidad de reservar memoria dinámica. 
-se eligió arbitrariamente que el tamaño de la clave a utilizar tenga un máximo de 150.  
-para el caso del envío del mensaje cifrado, se decidió que el envío del mensaje a través del socket se realice dentro del cryptosocket ya que este última cifra y luego se envía el mensaje. Pero para el caso de recibir el mensaje cifrado a través del socket, se decidió que este reciba un puntero a una función para así ir desencriptando a medida que llega el mensaje. O sea, para el caso del socket_send se cifra y luego se envía, y para el caso del socket_receive es al revez: se recibe y después se desencripta.  
-se mantuvo el menor acoplamiento posible entre los TDA socket,cryptosocket y los distintos encriptadores.  
-para el caso del servidor, como la función getaddrinfo solo devuelve un resultado posible para finalizar la conexión, no fue necesario iterar sobre cada resultado.  

**Diagrama de clases general**  
![Alt Text](clasesTP1.png)
