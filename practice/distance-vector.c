#include<stdio.h>

int costmatrix[20][20],n;

struct routers{
    int distance[20];
    int adjnode[20];     //initialising with data type
}node[20];               //semicolon

int readcostmatrix(){
    int i,j;
    printf("Enter the cost matrix:");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&costmatrix[i][j]);
            costmatrix[i][i]=0;
            node[i].distance[j]=costmatrix[i][j];
            node[i].adjnode[j]=j;                    //these 2 lines
        }
    }
}

int calcroutes(){
    int i,j,k;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                if(node[i].distance[j]>costmatrix[i][k]+node[k].distance[j]){        //condition
                    node[i].distance[j]=costmatrix[i][k]+node[k].distance[j];
                    node[i].adjnode[j]=k;
                }
            }
        }
    }
}

int displayroutes(){
    int i,j;
    for(i=0;i<n;i++){
        printf("Router %d:\n",i+1);
        for(j=0;j<n;j++){
            printf("Shortest path to node %d via %d is %d",j+1,node[i].adjnode[j]+1,node[i].distance[j]);
            //node[i].adjnode[j]+1
        }
        printf("\n");
    }
}

int main(){
    printf("Enter total number of nodes:");
    scanf("%d",&n);
    readcostmatrix();
    calcroutes();
    displayroutes();
    return 0;
}