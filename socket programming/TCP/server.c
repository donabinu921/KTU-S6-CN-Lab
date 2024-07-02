//include header files
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/socket.h>
//function to do required action
int factorial(int n)
{
    int fact=1;
    if(n==0||n==1)
    {
        return 1;
    }
    else
    {
        for(int i=1;i<=n;i++)
        {
            fact=fact*i;
        }
        return fact;
    }
    
}
//main function
int main()
{
    //initialise variables
    int serversocket,clientsocket,port,number,fact;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char message[50];
    struct serveraddr;
    //create socket and initialise server address to zero
    serversocket=socket(AF_INET,SOCK_STREAM,0);
    bzero((char*)&serveraddr,sizeof(serveraddr));
    //assign family,port
    serveraddr.sin_family=AF_INET;
    printf("Enter the port number\n");
    scanf("%d",&port);
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;
    //bind server socket and server address and initialise client address to zero
    bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    bzero((char*)&clientaddr,sizeof(clientaddr));
    len=sizeof(clientaddr);
    //listen for incoming clients
    listen(serversocket,5);
    printf("Waiting for client connection\n");
    //accept the connection
    clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&len);
    printf("\nclient connectivity received\n");
    //send message
    write(clientsocket,"ENTER A NUMBER",sizeof("ENTER A NUMBER"));
    //receive the number from client
    read(clientsocket,&number,sizeof(number));
    //find factorial
    fact=factorial(number);
    //send the result back to client
    write(clientsocket,&fact,sizeof(fact));
    //close client and server sockets
    close(clientsocket);
    close(serversocket);
}
