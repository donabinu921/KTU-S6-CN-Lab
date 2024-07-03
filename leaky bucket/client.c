#include <netinet/in.h>  // For sockaddr_in and other network related structures
#include <stdio.h>       // For standard I/O functions like printf, scanf
#include <stdlib.h>      // For standard library functions like exit
#include <sys/socket.h>  // For socket functions and structures
#include <sys/time.h>    // For setting socket timeout
#include <time.h>        // For time functions
#include <unistd.h>      // For close function

int main() {
    int clientsocket;
    struct sockaddr_in serveraddr;
    socklen_t len;
    struct timeval tv;
    char q[32];  // Queue for buffering
    int head = 0, tail = 0;
    char c, chr = 'a';
    time_t prev_time;

    clientsocket = socket(AF_INET, SOCK_STREAM, 0);  // Create a socket with IPv4, stream socket, and default protocol
    printf("Socket successfully created..\n");

    // Initialize server address structure
    serveraddr.sin_family = AF_INET;  // Set address family to IPv4
    serveraddr.sin_port = htons(8000);  // Set port number to 8000, converting to network byte order
    serveraddr.sin_addr.s_addr = INADDR_ANY;  // Set IP address to any available interface

    len = sizeof(serveraddr);  // Set len to the size of the server address structure
    connect(clientsocket, (struct sockaddr *)&serveraddr, len);  // Connect to the server
    printf("Socket connected...\n");

    // Setting timeout for read
    tv.tv_sec = 50;  // 50ms
    tv.tv_usec = 0;
    setsockopt(clientsocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv));

    // Client side processing... Implementing Leaky Bucket
    prev_time = time(NULL);  // Initialize previous time

    while (chr != '\0') {
        if (read(clientsocket, &c, 1) > 0) {  // Read data from the server
            q[head++] = c;  // Add character to the queue
        }

        // if 1s has elapsed
        if (time(NULL) - prev_time >= 1) {
            prev_time = time(NULL);  // Update previous time

            // if queue not empty, pop
            if (head != tail) {
                chr = q[tail++];  // Remove character from the queue
                if (chr != '\0') {
                    printf("Received [%c]\n", chr);  // Print the character
                }
            }
        }
    }

    // Close the socket
    close(clientsocket);  // Close the client socket
}
