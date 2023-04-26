#include<stdio.h>
#include<stdlib.h>

int time = 0;

struct node{
    int k;
    int dis;
    int f;
    char color;
    struct node* pred;
};

struct node *createnode(int k){
    struct node *x=(struct node*)malloc(sizeof(struct node));
    x->k=k;
    x->dis=0;
    x->f=0;
    x->color='W';
    x->pred=NULL;
    return x;
}

void DFS_VISIT(int **arr, struct node *u, struct node *val[]){
    time=time+1;
    u->dis=time;
    u->color='G';
    printf("%d ",u->k);
    int j=1;
    int i=u->k;
    while(arr[i][j]!=-1){
        struct node *v=val[arr[i][j]];
        if(v->color=='W'){
            v->pred=u;
            DFS_VISIT(arr,v,val);
        }
        j=j+1;
    }
    u->color='B';
    time=time+1;
    u->f=time;
}

void DFS(int **arr, int n){
    struct node* val[n];
    for(int i=0;i<n;i++){
        val[i]=createnode(i);
    }
    int i=0,j=0;
    while(i<n){
        struct node *u=val[arr[i][j]];
        if(u->color=='W'){
            DFS_VISIT(arr,u,val);
        }
        j=j+1;
        if(arr[i][j]==-1){
            i=i+1;
            j=0;
        }
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
    
    if(n==1){
	printf("0\n");
	return 0;
	}

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d%c",&arr[i][j],&c);
            if(c=='\n'){
                 arr[i][j+1]=-1; // add -1 at the end of each row
                break;
            }
        }
    }

    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         printf("%d ",arr[i][j]);
    //     }
    //     printf("\n");
    // }
    DFS(arr,n);
return 0;
}

