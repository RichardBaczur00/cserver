#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int sock;
    struct sockaddr_in server;
    char message[400], *server_reply;
    server_reply = (char*) calloc(400, sizeof(char));

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        fprintf(stderr, "socket function failed");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Socket created successfully\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    int status;

    if ((status = connect(sock, (struct sockaddr *)&server, sizeof(server))) < 0) {
        fprintf(stderr, "Connection failed... status code: %d", status);
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Connected\n");

    char* connection_request = "GET;http://localhost:8080/connect;text;connect";

    send(sock, connection_request, strlen(connection_request), 0);

    if (recv(sock, server_reply, 100, 0) < 0) {
        fprintf(stderr, "Receiving failed");
    }

    fprintf(stdout, "Server message: %s\n", server_reply);

    while (1) {
        free(server_reply);
        server_reply = (char*) calloc(400, sizeof(char));

        printf("Enter message: ");
        scanf("%s", message);

        if (send(sock, message, strlen(message), 0) < 0) {
            fprintf(stderr, "Sending failed");
            exit(EXIT_FAILURE);
        }

        if (recv(sock, server_reply, 100, 0) < 0) {
            fprintf(stderr, "Receiving failed");
            break;
        }

        fprintf(stdout, "Server reply: %s\n", server_reply);
        fflush(stdout);
        memset(server_reply, 0, strlen(server_reply));
    }
    
    close(sock);
    exit(EXIT_SUCCESS);
}