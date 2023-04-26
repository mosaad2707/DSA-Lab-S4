//AVL TREES (imp) with comments
//Mosaad 15/02/2023

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>

struct node{
int key ;
struct node* left;
struct node* right;
};
typedef struct node* node;//can be avoided , sometimes creates issue in debugging

node create_node(int k){
    node x=(node)malloc(sizeof(struct node));
    x->key=k;
    x->left=NULL;
    x->right=NULL;
    return x;
}

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

node max(node x){
    node s=x;
    while(s->right!=NULL){
        s=s->right;
    }
    return s;
}

node delete(node X,int k){
    if(X==NULL){
        return X;
    }
    if (k<X->key){
        X->left=delete(X->left,k);
    }else if (k>X->key){
        X->right=delete(X->right,k);
    }else{
        if (X->left==NULL && X->right==NULL){
            free(X);
            return NULL;
        }else if (X->left ==NULL){
            node temp=X;
            X=X->right;
            free(temp);
        }else if(X->right==NULL){
            node temp=X;
            X=X->left;
            free(temp);
        }else{
            node predecessor=max(X->left);
            X->key=predecessor->key;
            X->left=delete(X->left,predecessor->key);
        }
    }
    if(X==NULL){
        return NULL;
    }
    int bal=(height(X->left))-(height(X->right));
    if (bal>1){
        if ((height(X->left->left))-(height(X->left->right))<0){
            X->left=leftRotate(X->left,X->left->key);
        }
        return rightRotate(X,X->key);
    }
    if (bal<-1){
        if ((height(X->right->left))-(height(X->right->right))>0){
            X->right=rightRotate(X->right,X->right->key);
        }
        return leftRotate(X,X->key);
    }
    return X;
}

void PRINT(node X){
    printf("( ");
    if (X!=NULL){
        printf("%d ",X->key);
        PRINT(X->left);
        PRINT(X->right);
    }
    printf(") ");
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
            case 'd':
                scanf(" %d",&d);
                x=search(X,d);
                if (x!=NULL){
                    printf("%d\n",x->key);
                }else{
                    printf("FALSE\n");
                }
                X=delete(X,d);
                break;
            case 's':
                scanf(" %d",&d);
                x=search(X,d);
                if (x!=NULL){
                    printf("TRUE\n");
                }else{
                    printf("FALSE\n");
                }
                break;
            case 'b':
                scanf(" %d",&d);
                BalFac(X,d);
                break;
            case 'p':
                PRINT(X);
                printf("\n");
                break;
            case 'e':
                return 0;
        }
    }
}
