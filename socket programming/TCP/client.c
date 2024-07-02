#include<stdio.h>
#include<string.h>
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
    struct serveraddr;

    clientsocket=socket(AF_INET,SOCK_STREAM,0);
    bzero((char*)&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family=AF_INET;
    printf("Enter the port number\n");
    scanf("%d",&port);

    serveraddr.sin_port=htons(port);
    len=sizeof(serveraddr);
    printf("waiting for the server connection\n");
    connect(clientsocket,(struct sockaddr*)&serveraddr,len);

    printf("connected to the server\n");

    recv(clientsocket,message,sizeof(message),0);
    printf("%s",message);
    scanf("%d",&number);
    send(clientsocket,&number,sizeof(number),0);
    recv(clientsocket,&fact,sizeof(fact),0);
    printf("The factorial of the number is %d",fact);
    close(clientsocket);
}