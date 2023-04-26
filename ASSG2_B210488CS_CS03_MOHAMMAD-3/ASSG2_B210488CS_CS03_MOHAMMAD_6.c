//This one is for median
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
int arr[10000];
int count=0;
struct node{
int key ;
struct node* left;
struct node* right;
int elements;
};
typedef struct node* node;//can be avoided , sometimes creates issue in debugging



int height(node x){
    if(x==NULL){
        return 0;
    }
    int hl=height(x->left);//recursively calls left subtree
    int hr=height(x->right);//recursively calls right subtree
    //a function max can also be defined for the below code
    if (hl>hr){
        return 1+hl;
    }
    return 1+hr;
}

node search(node X,int k){
    if (X==NULL){
        return NULL;//base case
    }
    if (X->key==k){
        return X;//returns pointer to the node to be searched
    }else if (X->key>k){
        return search(X->left,k);//recursively calls left subtree
    }else{
        return search(X->right,k);//recursively calls right subtree
    }

}

node create_node(int k){
    node x=(node)malloc(sizeof(struct node));
    x->key=k;
    x->left=NULL;
    x->right=NULL;
    x->elements=0;
    return x;
}
void BalFac(node X,int k){
    node x=search(X,k);
    if (x!=NULL){
        printf("%d\n",(height(x->left))-(height(x->right)));//prints the balance factor
    }else{
        printf("FALSE\n");
    }
}

node leftRotate(node X,int k){
    node n=search(X,k);//search
    node p=n->right;//temp node pointer [p]
    n->right=p->left;//assignment
    p->left=n;//assignment
    return p;
}

node rightRotate(node X,int k){//symmetrical as above
    node n=search(X,k);
    node p=n->left;
    n->left=p->right;
    p->right=n;
    return p;
}

node insert(node X,int k){
    if (X==NULL){
        return create_node(k);

    }
    if (k<X->key){
        X->left=insert(X->left,k);
    }else if(k>X->key){
        X->right=insert(X->right,k);
    }else{
        return X;
    }
    X->elements=height(X->right)+height(X->left);
    int bal=(height(X->left))-(height(X->right));
    if (bal>1){
        if (k > X->left->key){
            X->left=leftRotate(X->left,X->left->key);//zigzag case
        }
        return rightRotate(X,X->key);
    }
    if (bal<-1){
        if (k < X->right->key){
            X->right=rightRotate(X->right,X->right->key);//zigzag case
        }
        return leftRotate(X,X->key);
    }
    return X;
}
void getmedian(node X){
    if(X!=NULL){
        getmedian(X->left);
        arr[count++]=X->key;
        getmedian(X->right);
    }

}
int main(){
    node X=NULL;
    node x;
    int d;
    char c;
    while(1){
        scanf("%c",&c);
        switch(c){
            case 'i':
                scanf(" %d",&d);
                X=insert(X,d);
                break;   
            case 'g':
                count=0;
                getmedian(X);
                if(count%2==0){
                    printf("%d\n",arr[((count)/2)-1]);
                }
                else{
                    printf("%d\n",arr[(count+1)/2-1]);
                }
                break;    
            case 't':
                return 0;
                break;
        }
    }
}
