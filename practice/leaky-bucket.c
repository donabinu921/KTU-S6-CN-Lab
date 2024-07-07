#include<stdio.h>

int main(){

    int buck_size,incoming,outgoing,n,store=0;

    printf("Enter total number of incoming packets:");
    scanf("%d",&n);
    printf("Enter bucket size:");
    scanf("%d",&buck_size);
    printf("Enter outgoing rate:");
    scanf("%d",&outgoing);

    while(n!=0){
        printf("Enter incoming packet size:");
        scanf("%d",&incoming);
        printf("Incoming packet size is %d\n",incoming);

        if(incoming<=buck_size-store){
            store=store+incoming;
            printf("Bucket size %d out of %d\n",store,buck_size);
        }
        else{
            printf("Dropped %d packets out of %d\n",incoming-(buck_size-store),incoming);
            store=buck_size;
            printf("Bucket size %d out of %d\n",store,buck_size);
        }

        store=store-outgoing;
        if(store<0){
            store=0;
        }
        printf("Bucket after outgoing is %d out of %d\n",store,buck_size);

        n=n-1;

    }

}