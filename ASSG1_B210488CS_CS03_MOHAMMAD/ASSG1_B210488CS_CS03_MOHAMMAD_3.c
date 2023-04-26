#include <stdio.h>
#include <stdlib.h>
int count=0;
int mystrlen(char e[])
{
    int len = 0;
    for (int i = 0; e[i] != '\0'; i++)
    {
        len++;
    }
    return len - 1;
}

struct node
{
    long int key;
    struct node *right;
    struct node *left;
};

struct tree
{
    struct node *root;
};

struct node *create_node(long int k)
{
    struct node *x;
    x = (struct node *)malloc(sizeof(struct node));
    x->left = NULL;
    x->right = NULL;
    x->key = k;
    return x;
}

char * clearspace(char *string)
{
   
    int alpha = 0;
 
   
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != ' ')
        {
            string[alpha] = string[i];
            alpha++;
        }    
    }
   
 
    string[alpha] = '\0';
    return string;
}


struct node *BUILD_TREE(char e[], int *s)
{
    if (mystrlen(e) == 0 || mystrlen(e) == 4 || *s >= mystrlen(e))
        return NULL;

    long int n = 0;
    int sign;
    if(e[*s]=='-'){
        sign=-1;
        *s=*s+1;
    }
    else{
        sign=1;
    }
    while (*s < mystrlen(e) && e[*s] != '(' && e[*s] != ')')
    {
        long int num = (int)(e[*s] - 48);
        n = n * 10 + num;
        *s = *s + 1;
    }
    n=n*sign;
    struct node *root = NULL;
    if(n!=0){
    root = create_node(n);
    }

    if(e[*s-1]=='0' && n==0){
        int j=0;
        root=create_node(j);
    }
    char c = e[*s];
    if (*s < mystrlen(e) && c == '(')
    {
        *s = *s + 1;
        root->left = BUILD_TREE(e, s);
    }
    if (*s < mystrlen(e) && e[*s] == ')')
    {
        *s = *s + 1;
        return root;
    }
    if (*s < mystrlen(e) && e[*s] == '(')
    {
        *s = *s + 1;
        root->right = BUILD_TREE(e, s);
    }
    if (*s < mystrlen(e) && e[*s] == ')')
        *s = *s + 1;
    return root;
}

struct node *SEARCH(struct node *x, int k)
{
    if (x == NULL || x->key == k)
        return x;
    if (x->key < k)
        return SEARCH(x->right, k);
    else
        return SEARCH(x->left, k);
}

void level(struct node *x,int b){
    if(b==0){
        printf("%ld ",x->key);
    }
    if(x->left!=NULL){
    level(x->left,b-1);
    }
    if(x->right!=NULL){
    level(x->right,b-1);
    }
    return;
}
int j;
int hi(struct node *root,int x){
    if(root==NULL) return 0;
int sum=(root->key+hi(root->left,x)+hi(root->right,x));
if(sum==x) j++;
return sum;
}
int countSubtreesWithSumX(struct node* root,int x)
{

j=0;
hi(root,x);
return j;
}


int main()
{
    struct node *tree;
    int begin = 1;
    char e[1000];
   
    fgets(e, 1000, stdin);
    int a,b;
    scanf("%d",&a);
    if(mystrlen(e)==3){
    printf("NIL\n");
    return 0;
   
    }
    clearspace(e);
    tree = BUILD_TREE(e, &begin);
    int s=countSubtreesWithSumX(tree,a);
    printf("%d\n",s);
    return 0;
}

