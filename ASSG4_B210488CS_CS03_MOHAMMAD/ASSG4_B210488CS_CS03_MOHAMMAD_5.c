#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <limits.h>
#include<string.h>

int distance(int d[],int visited[],int n){
    int min=999999;
    int ind;
    for(int k=0;k<n;k++){
        if( visited[k]==0 && d[k]<=min){
            min=d[k];
            ind=k;
        }
    }
    return ind;
}

// void djikstra1(int** graph, int u, int n){
//     int* visit=(int*)malloc(n*sizeof(int));
//     int* dist=(int*)malloc(n*sizeof(int));
//     for (int i=0;i<n;i++){
//         visit[i]=0;
//         dist[i]=10000000;
//     }
//     dist[u]=0;
//     int a;
//     for (int i=0;i<n;i++){
//         a=distance(dist,visit,n);
//         visit[a]=1;
//         for (int j=0;j<n;j++){
//             if(graph[a][j] && dist[j]>dist[a]+graph[a][j]){
//                 dist[j]=dist[a]+graph[a][j];
//             }
//         }
//     }
//     for (int i=0;i<n;i++){
//         if (dist[i]==10000000){
//             printf("INF ");
//         }else{
//             printf("%d ",dist[i]);
//         }
//     }
//     printf("\n");
// }


void djikstra1(int **graph,int start,int n){

    int d[n];
    int visited[n];
   for(int i=0;i<n;i++){
    d[i]=999999;
    visited[i]=0;
   }

   d[start]=0;

   for(int i=0;i<n-1;i++){
    int u=distance(d,visited,n);
    visited[u]=1;
    for(int v=0;v<n;v++){
        if(!visited[v] && graph[u][v]!=-1 && d[u]!=999999 && (d[u] + graph[u][v]) < d[v]){
            d[v] = d[u] + graph[u][v];
        }
    }
   }
   for (int i = 0; i < n; i++){
        if(d[i]!=999999){
        printf("%d ",d[i]);
        }
        else{
            printf("INF ");
        }

   }
   printf("\n");

}

void djikstra2(int **graph,int start,int end,int n){
    int d[n];
    int visited[n];
   for(int i=0;i<n;i++){
    d[i]=999999;
    visited[i]=0;
   }
   d[start]=0;
   for(int i=0;i<n-1;i++){
    int u=distance(d,visited,n);
    visited[u]=1;
    for(int v=0;v<n;v++){
        if(!visited[v] && graph[u][v]!=-1 && d[u]!=999999 && (d[u] + graph[u][v]) < d[v]){
            d[v] = d[u] + graph[u][v];
        }
    }
   }
   if(d[end]!=999999){
    printf("%d",d[end]);
   }
   else{
    printf("UNREACHABLE");
   }
   printf("\n");
}

int main(){
    int n;
    scanf("%d",&n);
     int** arr=(int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        arr[i]=(int*)malloc(n*sizeof(int));
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            arr[i][j]=-1;
        }
    }
    char c;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d%c",&arr[i][j],&c);
            if(c=='\n'){
                arr[i][j+1]=-1; // add -1 at the end of each row
                break;
            }
        }
    }
    int **graph=(int **)malloc(n*sizeof(int *));
    for(int i=0;i<n;i++){
        graph[i]=(int*)malloc(n*sizeof(int));
    }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         printf("%d ",arr[i][j]);
    //     }
    //     printf("\n");
    // }
    int j=n;
    int a,b,k=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            graph[i][j]=-1;
        }
    }
    while(j--){
        scanf("%d%c",&a,&c);
        if(c=='\n'){
            continue;
        }
        // printf("\nA is  |n%d\n",a);
        for(int i=0;i<n;i++){
            scanf("%d%c",&b,&c);
            graph[a][arr[a][k]]=b;
            // printf("%d %d ",k,arr[a][k]);
            k++;
            if(c=='\n'){
                k=1;
                break;
            }

        }
    }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         printf("%d ",graph[i][j]);
    //     }
    //     printf("\n");
    // }
    int flag;
    int u,v;
    while (1){
        char str[20];
        scanf("%s",str);
        if(strcmp(str,"apsp")==0){
            scanf("%d",&u);
            // printf("%d",u);
            flag=1;
            djikstra1(graph,u,n);
        }else if(strcmp(str,"sssp")==0){
            scanf("%d %d",&u,&v);
            djikstra2(graph,u,v,n);
        }else if(strcmp(str,"stop")==0){
            return 0;
        }
    }
    return 0;
}

