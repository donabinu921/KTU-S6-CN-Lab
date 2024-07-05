#include <netinet/in.h>  // Includes definitions for internet domain addresses
#include <stdio.h>       // Includes standard input/output functions
#include <stdlib.h>      // Includes standard library functions like exit
#include <sys/socket.h>  // Includes definitions for socket functions
#include <unistd.h>      // Includes standard symbolic constants and types (e.g., close function)

// Main function to receive file from server and save it to output.txt
int main() {
    int clientsocket;
    struct sockaddr_in servaddr;
    socklen_t len;
    FILE *file;
    char data[512];

    // Create a socket using the TCP protocol
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket successfully created..\n");

    // Initialize server address structure
    servaddr.sin_family = AF_INET;  // Set the address family to IPv4
    servaddr.sin_port = htons(8000);  // Set the server port number, converting to network byte order
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // Set the server address to localhost, converting to network byte order

    // Connect to the server
    len = sizeof(servaddr);
    connect(clientsocket, (struct sockaddr *)&servaddr, len);
    printf("Client Connected...\n");

    // FTP Client Logic
    file = fopen("output.txt", "w+");  // Open the file for writing (create if doesn't exist)
    printf("Receiving file from server...\n");
    while (read(clientsocket, data, sizeof(data)) != 0) {  // Read data from the server into the buffer
        fprintf(file, "%s", data);  // Write data to the file
    }
    printf("File received from server...\n");

    // Display the received file contents
    printf("File Contents:\n");
    printf("--------------\n");
    rewind(file);  // Move the file pointer to the beginning of the file
    while (fgets(data, sizeof(data), file) != NULL) {  // Read data from the file into the buffer
        printf("%s", data);  // Print the file contents
    }
    printf("--------------\n");

    fclose(file);  // Close the file
    close(clientsocket);  // Close the client socket
}
