#include <netinet/in.h>  // Includes definitions for internet domain addresses
#include <stdio.h>       // Includes standard input/output functions
#include <stdlib.h>      // Includes standard library functions like exit
#include <sys/socket.h>  // Includes definitions for socket functions
#include <unistd.h>      // Includes standard symbolic constants and types (e.g., close function)

// Main function to send file input.txt to client
int main() {
    int serversocket, clientsocket;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    FILE *file;
    char data[512];

    // Create a socket using the TCP protocol
    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket successfully created..\n");  // Print success message

    // Initialize server address structure
    serveraddr.sin_family = AF_INET;  // Set the address family to IPv4
    serveraddr.sin_port = htons(8000);  // Set the server port number, converting to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // Set the server address to localhost, converting to network byte order

    // Bind the socket to the server address
    bind(serversocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Socket successfully binded..\n");  // Print success message

    // Listen for incoming connections
    listen(serversocket, 255);
    printf("Server listening..\n");  // Print success message

    // Accept an incoming connection
    len = sizeof(clientaddr);  // Length of the client address structure
    clientsocket = accept(serversocket, (struct sockaddr *)&clientaddr, &len);

    // File transfer logic
    file = fopen("input.txt", "r");  // Open the file for reading
    printf("Sending file to client...\n");  // Print message indicating file transfer
    while (fgets(data, sizeof(data), file) != NULL) {  // Read data from the file into the buffer
        write(clientsocket, data, sizeof(data));  // Send data to the client
    }
    printf("File sent to client...\n");  // Print success message

    fclose(file);  // Close the file
    close(serversocket);  // Close the server socket
}
