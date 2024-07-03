#include <netinet/in.h>  // For sockaddr_in and other network related structures
#include <stdio.h>       // For standard I/O functions like printf, scanf
#include <stdlib.h>      // For standard library functions like exit
#include <sys/socket.h>  // For socket functions and structures
#include <unistd.h>      // For close function

int main() {
    int serversocket, clientsocket;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    char msg[32];
    int i = 0;

    serversocket = socket(AF_INET, SOCK_STREAM, 0);  // Create a socket with IPv4, stream socket, and default protocol
    printf("Socket successfully created..\n");

    // Initialize server address structure
    serveraddr.sin_family = AF_INET;  // Set address family to IPv4
    serveraddr.sin_port = htons(8000);  // Set port number to 8000, converting to network byte order
    serveraddr.sin_addr.s_addr = INADDR_ANY;  // Set IP address to any available interface

    bind(serversocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));  // Bind the socket to the specified address and port
    printf("Socket successfully binded..\n");

    listen(serversocket, 255);  // Set the socket to listen for incoming connections with a backlog queue of 255
    printf("Server listening..\n");

    len = sizeof(clientaddr);  // Set len to the size of the client address structure
    clientsocket = accept(serversocket, (struct sockaddr *)&clientaddr, &len);  // Accept an incoming connection from a client
    printf("Server accepted the client...\n");

    // Server side processing...
    printf("Enter a message: ");  // Prompt the user to enter a message
    scanf("%s", msg);  // Read the message from the user

    while (msg[i] != '\0') {  // Loop through each character of the message
        write(clientsocket, &msg[i++], 1);  // Write each character to the client, one at a time
    }

    write(clientsocket, "\0", 1);  // Send a null terminator to indicate the end of the message

    // Close the sockets
    close(clientsocket);  // Close the client socket
    close(serversocket);  // Close the server socket
}
