#include<stdio.h>
#include<stdlib.h>


struct Node{
    int k;
    struct Node* left;
    struct Node* right;
};

struct BinaryTree{
    struct Node* root;
};

// struct node
// {
//     long int key;
//     struct node *right;
//     struct node *left;
// };

// struct tree
// {
//     struct node *root;
// };

// struct node *create_node(long int k)
// {
//     struct node *x;
//     x = (struct node *)malloc(sizeof(struct node));
//     x->left = NULL;
//     x->right = NULL;
//     x->key = k;
//     return x;
// }

// char * clearspace(char *string)
// {
    
//     int alpha = 0;
 
   
//     for (int i = 0; string[i] != '\0'; i++)
//     {
//         if (string[i] != ' ')
//         {
//             string[alpha] = string[i];
//             alpha++;
//         }    
//     }
    
  
//     string[alpha] = '\0';
//     return string;
// }


// struct node *BUILD_TREE(char e[], int *s)
// {
//     if (mystrlen(e) == 0 || mystrlen(e) == 4 || *s >= mystrlen(e))
//         return NULL;

//     long int n = 0;
//     int sign;
//     if(e[*s]=='-'){
//         sign=-1;
//         *s=*s+1;
//     }
//     else{
//         sign=1;
//     }
//     while (*s < mystrlen(e) && e[*s] != '(' && e[*s] != ')')
//     {
//         long int num = (int)(e[*s] - 48);
//         n = n * 10 + num;
//         *s = *s + 1;
//     }
//     n=n*sign;
//     struct node *root = NULL;
//     if(n!=0){
//     root = create_node(n);
//     }

//     if(e[*s-1]=='0' && n==0){
//         int j=0;
//         root=create_node(j);
//     }
//     char c = e[*s];
//     if (*s < mystrlen(e) && c == '(')
//     {
//         *s = *s + 1;
//         root->left = BUILD_TREE(e, s);
//     }
//     if (*s < mystrlen(e) && e[*s] == ')')
//     {
//         *s = *s + 1;
//         return root;
//     }
//     if (*s < mystrlen(e) && e[*s] == '(')
//     {
//         *s = *s + 1;
//         root->right = BUILD_TREE(e, s);
//     }
//     if (*s < mystrlen(e) && e[*s] == ')')
//         *s = *s + 1;
//     return root;
// }

// struct node *SEARCH(struct node *x, int k)
// {
//     if (x == NULL || x->key == k)
//         return x;
//     if (x->key < k)
//         return SEARCH(x->right, k);
//     else
//         return SEARCH(x->left, k);
// }


struct Node* BUILD_TREE(char* str)
{ 
    int key, temp, i;
    char k[1000];
    
    str += 2; 
    
    if(*str == ')')
    {
        return NULL;
    }
    
   
    i = 0;
    while((*str >= '0' && *str <= '9') || *str == '-') 
    {
        k[i++] = *str;
        str++;
    }
    k[i] = '\0'; 

    key = atoi(k); 

    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); 
    node->k = key; 
    
    str++; 
    node->left = BUILD_TREE(str); 

    str++; 

   
    temp = 1;
    while(temp != 0)
    {
        if(*str == '(')
            temp++;
        if(*str == ')')
            temp--;
        str++;
    }

    str++; 
    node->right = BUILD_TREE(str); 

    return node;
  
}


void PRINT(struct Node* root){
    if(root == NULL)
        return;
    PRINT(root->left);
    PRINT(root->right);
    printf("%d ", root->k);
}

struct Node *SEARCH(struct Node *x, int j)
{
    if (x == NULL || x->k == j)
        return x;
    if (x->k < j)
        return SEARCH(x->right, j);
    else
        return SEARCH(x->left, j);
}

int main(){
    
    char* str  = (char*)malloc(1000 * sizeof(char));
    scanf("%[^\n]s", str); 
    int a,b,count=0;
    scanf("%d %d",&a,&b);
    struct BinaryTree* bt = (struct BinaryTree*)malloc(sizeof(struct BinaryTree));
    bt->root = BUILD_TREE(str); 
    while(a<=b){
        struct Node* l=SEARCH(bt->root,a);
        if(l!=NULL){
            printf("%d ",l->k);
        }
        a++;
    }
    printf("\n");    
    return 0;
}
