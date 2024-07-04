#include <netinet/in.h>  // Includes definitions for internet domain addresses
#include <stdio.h>       // Includes standard input/output functions
#include <stdlib.h>      // Includes standard library functions like exit
#include <sys/time.h>    // Includes definitions for time values used with sockets
#include <sys/socket.h>  // Includes definitions for socket functions
#include <unistd.h>      // Includes standard symbolic constants and types (e.g., close function)

// Stop & Wait Server implementation in C. Run server first

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
    int serversocket;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    char msg[32];  // Buffer to hold the message to be sent
    struct timeval timeout;

    // Create a socket using the UDP protocol
    serversocket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Socket successfully created..\n");

    // Initialize server address structure
    serveraddr.sin_family = AF_INET;  // Set the address family to IPv4
    serveraddr.sin_port = htons(SERVER_PORT);  // Set the server port number, converting to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // Set the server address to localhost, converting to network byte order

    // Bind the socket to the server address
    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    len = sizeof(clientaddr);  // Length of the client address structure

    // Initialize client address structure
    clientaddr.sin_family = AF_INET;  // Set the address family to IPv4
    clientaddr.sin_port = htons(CLIENT_PORT);  // Set the client port number, converting to network byte order
    clientaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // Set the client address to localhost, converting to network byte order

    // For setting the socket to timeout after 1 second (waiting time)
    timeout.tv_sec = 1;  // Set the timeout seconds
    timeout.tv_usec = 0;  // Set the timeout microseconds
    setsockopt(serversocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));  // Set the socket option for receive timeout

    // Server side processing...
    printf("Enter a message: ");
    scanf("%s", msg);  // Read the message from the user

    int i = 0;  // Index for the message array
    Frame f;  // Frame to hold the data to be sent
    int frame_num = 0;  // Frame number to be sent

    while (msg[i] != '\0') {  // Loop until the end of the message
        f.data = msg[i];  // Set the frame data to the current character of the message
        f.type = DATA;  // Set the frame type to DATA
        f.no = frame_num;  // Set the frame number
        sendto(serversocket, &f, sizeof(f), 0, (struct sockaddr*)&clientaddr, len);  // Send the frame to the client
        printf("Sent frame [%d]\n", frame_num);

        // Receive acknowledgment from the client
        recvfrom(serversocket, &f, sizeof(f), 0, (struct sockaddr*)&clientaddr, &len); 
        printf("Received ack [%d]\n", frame_num);

        // Move to the next character in the message
        i++;
        // Increment the frame number
        frame_num++;
    }

    // Send finish frame to the client
    f.type = FIN;  // Set the frame type to FIN (finish)
    sendto(serversocket, &f, sizeof(f), 0, (struct sockaddr*)&clientaddr, len);  // Send the finish frame to the client

    // Close the socket
    close(serversocket);  // Close the server socket
}
