#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){

    int clientsocket;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char data[512];
    FILE *file;

    clientsocket=socket(AF_INET,SOCK_STREAM,0);
    printf("Socket created successfully\n");

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(8000);
    serveraddr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);

    len=sizeof(serveraddr);

    printf("Connecting to server\n");
    connect(clientsocket,(struct sockaddr*)&serveraddr,len);
    printf("Connected successfully");

    file=fopen("output.txt","w+");
    printf("Writing to output file\n");
    while(read(clientsocket,data,sizeof(data))!=0){
        fprintf(file,"%s", data);             //fprintf syntax
    }

    printf("File contents are:\n");
    rewind(file);
    while(fgets(data,sizeof(data),file)!=NULL){
        printf("%s",data);                                
    }

    fclose(file);
    close(clientsocket);

}