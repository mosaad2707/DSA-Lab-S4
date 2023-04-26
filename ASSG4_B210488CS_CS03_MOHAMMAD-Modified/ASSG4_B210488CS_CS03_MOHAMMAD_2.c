#include<stdio.h>
#include<stdlib.h>

struct node{
    int k;
    int dis;
    char color;
    struct node* pred;
};

struct qnode{
    struct node* k;
    struct qnode* next;
};
typedef struct qnode* qnode;

struct queue{
    struct qnode* head;
    struct qnode* tail;
};
typedef struct queue* queue;

void enqueue(queue q,struct node* x){
    qnode z=(qnode)malloc(sizeof(struct qnode));
    z->k=x;
    z->next=NULL;
    if (q->head==NULL){
        q->head=z;
        q->tail=z;
        return;
    }
    q->tail->next=z;
    q->tail=z;
}



struct node* dequeue(queue q){
    qnode x=q->head;
    q->head=x->next;
    x->next=NULL;
    // printf("%d deq",x->k->k);
    printf("%d ",x->k->k);
    return x->k; 
}

struct node *createnode(int k){
    struct node *x=(struct node*)malloc(sizeof(struct node));
    x->k=k;
    x->dis=0;
    x->color='W';
    x->pred=NULL;
    return x;

}

void BFS(int **array,struct node *s,int n){
    struct queue *Q=(struct queue *)malloc(sizeof(struct queue));
    struct node *u;
    struct node* val[n];
    for(int i=0;i<n;i++){
        val[i]=createnode(i);
    }
    enqueue(Q,val[0]);
    int count=0;
    while(Q->head!=NULL){
        u=dequeue(Q);

        int i=u->k;
        int j=1;
        while(array[i][j]!=-1){
            struct node* v=val[array[i][j]];
            if(v->color=='W'){
                v->color='G';
                v->dis=u->dis+1;
                v->pred=u;
                enqueue(Q,v);
                // printf("\nenqued %d\n",v->k);
            }
            j++;
        }
        u->color='B';
        // printf("%d coloured B\n",u->k);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    n=n;
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
	if(n==1){
	printf("0\n");
	return 0;
	}
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         printf("%d ",arr[i][j]);
    //     }
    //     printf("\n");
    // }

    struct node *start;
    start=createnode(arr[0][0]);
    BFS(arr,start,n);
    printf("\n");
    return 0;
}

