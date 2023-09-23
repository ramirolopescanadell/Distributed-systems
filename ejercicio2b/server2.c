#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h> // Include this header for TCP_NODELAY
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno, clilen;
    double potencia = atof(argv[2]);
    int size = pow(10, potencia);
    char buffer[size];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    fprintf(stderr, "SERVIDOR\n");
    if (argc < 3) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    // CREATES A SOCKET FILE DESCRIPTOR FOR THE CONNECTION
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET - INTERNET PROTOCOL FAMILY
    // SOCK_STREAM - SOCKET TYPE

    if (sockfd < 0)
        error("ERROR opening socket");

    // Set TCP_NODELAY option to disable Nagle's algorithm
    int flag = 1;
    if (setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int)) < 0)
        error("ERROR setting TCP_NODELAY option");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    // ASSIGNS THE PORT PROVIDED AS AN ARGUMENT
    // BINDS TO THE IP WHERE IT LISTENS (ANY IP)
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // BINDS THE FILE DESCRIPTOR TO THE ADDRESS AND PORT
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // SETS THE NUMBER OF CONNECTIONS THAT CAN BE WAITING WHILE HANDLING A CONNECTION
    listen(sockfd, 5);

    // BLOCKS TO WAIT FOR A CONNECTION
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *)&cli_addr,
                       &clilen);

    // RETURNS A NEW DESCRIPTOR FOR COMMUNICATIONS
    if (newsockfd < 0)
        error("ERROR on accept");
    bzero(buffer, size);

    // READS THE MESSAGE FROM THE CLIENT
    n = read(newsockfd, buffer, size);
    int totalBytesRead = n;
    while (totalBytesRead < size) {
        n = read(newsockfd, buffer + totalBytesRead, size - totalBytesRead);
        if (n < 0) {
            error("ERROR reading from socket");
            break;
        } else if (n == 0) {
            break;
        }
        totalBytesRead += n;
    }

    // RESPONDS TO THE CLIENT
    n = write(newsockfd, "I got your message", 18);
    if (n < 0)
        error("ERROR writing to socket");

    close(newsockfd); // Close the client socket when done
    close(sockfd);    // Close the server socket when done
    return 0;
}
