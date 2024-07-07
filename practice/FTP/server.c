#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){

    int serversocket,clientsocket;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char data[512];
    FILE *file;

    serversocket=socket(AF_INET,SOCK_STREAM,0);
    printf("Socket created successfully\n");

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(8000);
    serveraddr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);

    bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    printf("Socket binded successfully\n");
    len=sizeof(clientaddr);

    listen(serversocket,255);              //listen
    printf("Socket listening\n");

    printf("Waiting for client connection\n");
    clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&len);
    printf("Connected successfully\n");

    file=fopen("input.txt","r");
    while(fgets(data,sizeof(data),file)!=NULL){
        write(clientsocket,data,sizeof(data));
    }
    printf("File read successfully\n");

    fclose(file);
    close(clientsocket);
    close(serversocket);

}