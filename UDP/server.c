#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>

int factorial(int n)
{
   int fact=1;
    if(n==0||n==1)
    {
        return 1;
    }
    else{
        for(int i=1;i<=n;i++)
        {
            fact=fact*i;
        }
    }
    return fact;
}

int main()
{
    int serversocket,clientsocket,port,number,fact;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char message[50];

    serversocket=socket(AF_INET,SOCK_DGRAM,0);
    bzero((char*)&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family=AF_INET;
    printf("Enter the port number\n");
    scanf("%d",&port);
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;
    
    bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    bzero((char*)&clientaddr,sizeof(clientaddr));
    len=sizeof(clientaddr);

    printf("Sending message to the client\n");
    sendto(serversocket,"Enter the number",sizeof("Enter the number"),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
    recvfrom(serversocket,&number,sizeof(number),0,(struct sockaddr*)&clientaddr,&len);
    fact=factorial(number);
    sendto(serversocket,&fact,sizeof(fact),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));

    close(clientsocket);
    close(serversocket);
}