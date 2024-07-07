#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){

    int serversocket,clientsocket,port,number,fact;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char msg[50];

    clientsocket=socket(AF_INET,SOCK_DGRAM,0);
    bzero((char*)&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family=AF_INET;
    printf("Enter the port number: ");
    scanf("%d",&port);
    serveraddr.sin_port=htons(port);

    len=sizeof(serveraddr);       

    printf("Waiting for connection\n");
    connect(clientsocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));  //forgot connect
    printf("Connected\n");

    // recvfrom(clientsocket,&msg,sizeof(msg),0,(struct sockaddr*)&serveraddr,&len);
    printf("Enter number:");
    scanf("%d",&number);
    sendto(clientsocket,&number,sizeof(number),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    recvfrom(clientsocket,&fact,sizeof(fact),0,(struct sockaddr*)&serveraddr,&len);
    printf("Factorial is %d",fact);

    close(clientsocket);
}