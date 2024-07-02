//include header files, 1 extra
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
//main function
int main()
{
    //initialise variables
    int serversocket,clientsocket,port,number,fact;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char message[50];
    //create client socket and initialise server address to zero
    clientsocket=socket(AF_INET,SOCK_STREAM,0);
    bzero((char*)&serveraddr,sizeof(serveraddr));
    //assign family,port
    serveraddr.sin_family=AF_INET;
    printf("Enter the port number\n");
    scanf("%d",&port);
    serveraddr.sin_port=htons(port);
    //no s_addr and no bind
    len=sizeof(serveraddr);
    printf("waiting for the server connection\n");
    //connect to server
    connect(clientsocket,(struct sockaddr*)&serveraddr,len);
    printf("connected to the server\n");
    //receive msg from server
    recv(clientsocket,message,sizeof(message),0);
    printf("%s",message);
    scanf("%d",&number);
    //tell server what to do
    send(clientsocket,&number,sizeof(number),0);
    //receive result from server
    recv(clientsocket,&fact,sizeof(fact),0);
    printf("The factorial of the number is %d",fact);
    //close client socket
    close(clientsocket);
}
