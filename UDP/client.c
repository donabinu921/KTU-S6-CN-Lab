#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>

int main()
{
    int serversocket,clientsocket,port,number,fact;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char message[50];

    clientsocket=socket(AF_INET,SOCK_DGRAM,0);
    bzero((char*)&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family=AF_INET;
    printf("Enter the port number\n");
    scanf("%d",&port);
    serveraddr.sin_port=htons(port);

    len=sizeof(serveraddr);

    printf("Waiting for server connection\n");
    connect(clientsocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    printf("connected to the server\n");

    printf("Enter the number\n");
    scanf("%d",&number);
    sendto(clientsocket,&number,sizeof(number),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    recvfrom(clientsocket,&fact,sizeof(fact),0,(struct sockaddr*)&serveraddr,&len);
    printf("The factorial of the number is %d\n",fact);

    close(clientsocket);

}