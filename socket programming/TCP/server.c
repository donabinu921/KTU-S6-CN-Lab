#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/socket.h>
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
int main()
{
    int serversocket,clientsocket,port,number,fact;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char message[50];
    struct serveraddr;

    serversocket=socket(AF_INET,SOCK_STREAM,0);
    bzero((char*)&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family=AF_INET;
    printf("Enter the port number\n");
    scanf("%d",&port);

    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;
    bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    bzero((char*)&clientaddr,sizeof(clientaddr));
    len=sizeof(clientaddr);

    listen(serversocket,5);

    printf("Waiting for client connection\n");

    clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&len);
    printf("\nclient connectivity received\n");

    write(clientsocket,"ENTER A NUMBER",sizeof("ENTER A NUMBER"));
    read(clientsocket,&number,sizeof(number));
    
    fact=factorial(number);
     write(clientsocket,&fact,sizeof(fact));
    
   close(clientsocket);
   close(serversocket);
}