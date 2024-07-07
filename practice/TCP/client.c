#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){

    int clientsocket,port,number,fact;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char msg[50];

    clientsocket=socket(AF_INET,SOCK_STREAM,0);
    bzero((char*)&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family=AF_INET;
    printf("Enter the port number: ");
    scanf("%d",&port);
    serveraddr.sin_port=htons(port);
    
    len=sizeof(serveraddr);

    printf("Connecting to server");
    connect(clientsocket,(struct sockaddr*)&serveraddr,len);  //len or &len
    printf("Connection successful");

    recv(clientsocket,msg,sizeof(msg),0);                     //&msg no need
    printf("%s",msg);
    scanf("%d",&number);
    send(clientsocket,&number,sizeof(number),0);

    recv(clientsocket,&fact,sizeof(fact),0);
    printf("factorial is %d",fact);                           //forgot to print
    close(clientsocket);

}