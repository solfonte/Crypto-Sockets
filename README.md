# TP1-Taller  
Nombre: Maria Sol Fontenla.  
Padrón: 103870.  
Link al repositorio:https://github.com/solfonte/TP1-Taller.  

## Descripción general del trabajo realizado  
Para el desarrollo del trabajo práctico, se implementaron tanto el emisor y el receptor. Para la comunicación de estas dos partes, se utilizan los métodos de clave simétrica Cesar, Vigenere y RC4. Para llevar a cabo el trabajo practico, se recurrio a las paginas de manual de socket y las clases dadas por el curso.  

**implementacion del emisor o cliente**
El cliente recibe la clave y el método a utilizar, además del archivo a cifrar por entrada estándar. A medida que se itera sobre el archivo recibido, un TDA cryptosocket que recibe lo leído del archivo, combina las tareas de cifrado de clave y envío del mensaje a través de un socket. Cuando el cliente ya envió todo el mensaje, este finaliza la conexión cerrando el socket de su parte.  

**implementación del receptor o servidor**  
El servidor recibe la clave y el método a utilizar. Mediante la conexión entre los sockets del cliente y el servidor, el servidor recibe la cadena cifrada y la descifra mediante un cryptosocket, pero en este caso el cryptosocket descifra e imprime por salida estándar la cadena descifrada.  

**explicación general sobre los TDAs implementados**
TDA socket: este tda encapsula los chequeos y métodos relacionados con sockets. Realiza las iteraciones necesarias para cada método.  
TDA cryptosocket: encapsula la logica de encriptacion y envio/recepcion de mensajes mediante los metodos de enviar_mensaje y recibir_mensaje.Es un tda que combina las dos partes esenciales del trabajo práctico. Este recibe un encriptador_t, el cual sabe que metodo se está utilizando.  
TDA encriptador: este tda encapsula los distintos métodos específicos que puede utilizar el cryptosocket para cifrar/descifrar los mensajes. Cuando se le pide que encripte un mensaje, este conoce el método y decide a cual pedirle que se encargue de la tarea.  
TDAs encriptador_cesar,encriptador_rc4,encriptador_vigenere: cada uno de estos sockets sabe de qué manera debe cifrar/descifrar los mensajes. Realizan los métodos cesar, rc4 y vigenere respectivamente.  
TDA lector_de_texto: este tda se encarga de leer el archivo por stdin, y luego de guardar lo leido, se lo envía como parámetro a una función que recibe por parámetros.  

**decisiones de implementación y comentarios adicionales**  
-sobre la implementación del TDA encriptador: este es un encriptador genérico que sabe interpretar qué método se debe utilizar. Este encapsula la elección del método a la hora de cifrar/descifrar. Se implementó de esta manera para poder separar los tres métodos de encriptacion en TDAs distintos y así poder crear la estructura cryptosocket, que no necesita saber qué método se utiliza para encriptar. De todas formas, no fue la elección más óptima a la hora de encriptar ya que este chequea para cada encriptación, que metodo debe utilizar.Se intento que el TDA encriptador_t funcionara como una interfaz.  
-sobre la declaración de los métodos cesar, vigenere y rc4 en el main del receptor y en el main del cliente: se implementó de esta manera para poder utilizar el stack y no el heap, ya que no se que metodo se va a ingresar por parámetros (dadas las tres posibilidades), y de esta forma declarando los puedo elegir cual utilizar sin la necesidad de reservar memoria dinámica. 
-se eligió arbitrariamente que el tamaño de la clave a utilizar tenga un máximo de 150.  
-para el caso del envío del mensaje cifrado, se decidió que el envío del mensaje a través del socket se realice dentro del cryptosocket ya que este última cifra y luego se envía el mensaje. Pero para el caso de recibir el mensaje cifrado a través del socket, se decidió que este reciba un puntero a una función para así ir desencriptando a medida que llega el mensaje. O sea, para el caso del socket_send se cifra y luego se envía, y para el caso del socket_receive es al revez: se recibe y después se desencripta.  
-se mantuvo el menor acoplamiento posible entre los TDA socket,cryptosocket y los distintos encriptadores.  
-para el caso del servidor, como la función getaddrinfo solo devuelve un resultado posible para finalizar la conexión, no fue necesario iterar sobre cada resultado.    
**Diagrama de clases general**  
![Alt Text](clasesTP1.png)
