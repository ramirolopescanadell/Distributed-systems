#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h> // Include this header for TCP_NODELAY
#include <netdb.h>
#include <math.h>
#include <sys/time.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    struct timeval start, end;
    double potencia = atof(argv[3]);
    int size = pow(10, potencia);
    fprintf(stderr, "CLIENTE\n");
    char buffer[size];
    if (argc < 4) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    // TOMA EL NUMERO DE PUERTO DE LOS ARGUMENTOS
    portno = atoi(argv[2]);

    // CREA EL FILE DESCRIPTOR DEL SOCKET PARA LA CONEXION
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET - FAMILIA DEL PROTOCOLO - IPV4 PROTOCOLS INTERNET
    // SOCK_STREAM - TIPO DE SOCKET

    if (sockfd < 0)
        error("ERROR opening socket");

    // Set socket options for send buffer and receive buffer size
    int buffer_size = size;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &buffer_size, sizeof(buffer_size)) < 0)
        error("ERROR setting receive buffer size");
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &buffer_size, sizeof(buffer_size)) < 0)
        error("ERROR setting send buffer size");

    // Set TCP_NODELAY option to disable Nagle's algorithm
    int flag = 1;
    if (setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int)) < 0)
        error("ERROR setting TCP_NODELAY option");

    // TOMA LA DIRECCION DEL SERVER DE LOS ARGUMENTOS
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    // COPIA LA DIRECCION IP Y EL PUERTO DEL SERVIDOR A LA ESTRUCTURA DEL SOCKET
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);

    // DESCRIPTOR - DIRECCION - TAMAÑO DIRECCION
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    bzero(buffer, size);
    for (int i = 0; i < size; i++) {
        buffer[i] = 'b';
    }

    // fgets(buffer,size -1,stdin);
    // ENVIA UN MENSAJE AL SOCKET
    gettimeofday(&start, NULL);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    bzero(buffer, size);

    // ESPERA RECIBIR UNA RESPUESTA
    n = read(sockfd, buffer, size - 1);
    if (n < 0)
        error("ERROR reading from socket");

    close(sockfd); // Close the socket when done
    gettimeofday(&end, NULL);
  
  long seconds = (end.tv_sec - start.tv_sec);
  long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
  int p = potencia;
  printf("Ejecutando un buffer de 10 a la  %d caracteres. El tiempo fue: %ld segundos y %ld microsegundos\n", p, seconds, micros);
  return 0;
}
