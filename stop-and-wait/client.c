#include <netinet/in.h>  // Includes definitions for internet domain addresses
#include <stdio.h>       // Includes standard input/output functions
#include <stdlib.h>      // Includes standard library functions like exit
#include <sys/socket.h>  // Includes definitions for socket functions
#include <unistd.h>      // Includes standard symbolic constants and types (e.g., close function)

// Stop & Wait Client implementation in C. Run server first

#define SERVER_PORT 6000  // Define the server port number
#define CLIENT_PORT 8000  // Define the client port number
#define DATA 0            // Define the data frame type
#define ACK 1             // Define the acknowledgment frame type
#define FIN 2             // Define the finish frame type

typedef struct Frame {  // Define a frame structure to hold data, type, and frame number
    char data;          // Data to be sent
    int type;           // Type of frame (DATA, ACK, FIN)
    int no;             // Frame number
} Frame;

int main()
{
    int clientsocket;
    struct sockaddr_in clientaddr, serveraddr;
    socklen_t len;

    // Create a socket using the UDP protocol
    clientsocket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Socket successfully created..\n");

    // Initialize client address structure
    clientaddr.sin_family = AF_INET;  // Set the address family to IPv4
    clientaddr.sin_port = htons(CLIENT_PORT);  // Set the client port number, converting to network byte order
    clientaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // Set the client address to localhost, converting to network byte order

    // Bind the socket to the client address
    bind(clientsocket, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    len = sizeof(clientaddr);  // Length of the client address structure

    // Initialize server address structure
    serveraddr.sin_family = AF_INET;  // Set the address family to IPv4
    serveraddr.sin_port = htons(SERVER_PORT);  // Set the server port number, converting to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // Set the server address to localhost, converting to network byte order

    // Client side processing...
    Frame f;
    while (f.type != FIN) {  // Loop until a finish frame is received
        recvfrom(clientsocket, &f, sizeof(f), 0, (struct sockaddr*)&serveraddr, &len);  // Receive a frame from the server
        if (f.type != FIN) {  // If the frame is not a finish frame
            printf("Received [%c]. Sending ACK\n", f.data);  // Print received data and indicate sending acknowledgment

            f.type = ACK;  // Set the frame type to ACK (acknowledgment)
            sendto(clientsocket, &f, sizeof(f), 0, (struct sockaddr*)&serveraddr, len);  // Send the acknowledgment frame to the server
        }
    }
    
    // Close the socket
    close(clientsocket);  // Close the client socket
}
