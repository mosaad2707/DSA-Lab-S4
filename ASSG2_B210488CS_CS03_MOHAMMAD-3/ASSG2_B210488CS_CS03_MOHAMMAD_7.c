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

void fun(node root, int K, int *count, int arr[])
{
if (root == NULL)
return;
fun(root->right, K, count, arr);
if (root->key > K)
{
    arr[*count] = root->key;
    (*count)++;
}
fun(root->left, K, count, arr);
}

int main()
{
char op;
int K, value, count = 0, arr[1000];
struct node *root = NULL;

while (1)
{
    scanf("%s", &op);
    if (op == 'e')
        break;

    switch (op)
    {
        case 'i':
            scanf("%d", &value);
            root = insert(root, value);
            break;

        case 'c':
            scanf("%d", &K);
            count = 0;
            fun(root, K, &count, arr);
            printf("%d\n", count);
            if(count==0){
                break;
            }
            for (int i = count-1; i >=0; i--)
                printf("%d ", arr[i]);
            printf("\n");
            break;
    }
}

return 0;
}
