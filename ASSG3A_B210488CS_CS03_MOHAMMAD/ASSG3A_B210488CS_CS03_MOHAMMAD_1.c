// Red black tree 
// Mosaad 26-03-2023 0609

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct node
{
    int key;
    struct node *left;
    struct node *right;
    char c;
};

struct node *createNode(int key)
{
    struct node *x = (struct node *)malloc(sizeof(struct node));
    x->key = key;
    x->c = 'R'; // A function is defined to create a new node with a given key,
    // initialize it with color R (red) and set the left and right pointers to NULL.
    return x;
}

void print(struct node *x)
{
    printf("( ");
    if (x != NULL)
    {
        printf("%d ", x->key);
        printf("%c ", x->c);
        print(x->left);
        print(x->right);
    }
    printf(") ");
    // prints the required output
}

// struct node *leftrotate(struct node *x,int k){
//     struct node* p;
//     struct node* n=search(x,k);
//     p=n->right;
//     n->right=p->left;
//     p->left=n;
//     return p;
// }

// struct node* rightrotate(struct node* x ,int k){
//     struct node* p;
//     struct node*n=search(x,k);
//     p=n->left;
//     n->left=p->right;
//     p->right=n;
//     return p;
// }

struct node *LR(struct node *n)
{
    struct node *p = n->right;
    n->right = p->left;
    p->left = n;
    return p;
}

struct node *RR(struct node *n)
{
    // no search needed like avl coz pointer returnds to found node already
    // similar case for above also
    struct node *p = n->left;
    n->left = p->right;
    p->right = n;
    return p;
}

char color(struct node *x)
{
    if (x == NULL)
    {
        return 'B'; // imp null node is autmoatically returned a black node
    }
    return x->c;
}

// Every node is either red or black.
// The root node is always black.
// Every leaf node is black.
// If a node is red, then both its children are black.
// Every simple path from a node to a descendant leaf contains the same number of black nodes.

struct node *insert(struct node *root, struct node *x)
{
    int key = x->key;
    if (root == NULL)
    {
        return x;
    }
    if (key > root->key)
    {
        root->right = insert(root->right, x);
        if (color(root->right) == 'R')//check if the right child is Red , proceed according to rules given above
        {
            if ((color(root->right->right) == 'R') || color(root->right->left) == 'R')
            {
                if (color(root->left) == 'B')
                {
                    if (color(root->right->right) == 'R')
                    {
                        struct node *y = LR(root);
                        y->c = 'B';
                        y->left->c = 'R';
                        return y;
                    }
                    else
                    {
                        root->right = RR(root->right);
                        struct node *y = LR(root);
                        y->c = 'B';
                        y->left->c = 'R';
                        return y;
                    }
                }
                else if (color(root->left) == 'R')
                {
                    root->left->c = 'B';
                    root->right->c = 'B';
                    root->c = 'R';
                }
            }
        }
    }
    else
    {
        root->left = insert(root->left, x);
        if (root->left->c == 'R')//check if the right child is left , proceed according to rules given above,almost symmetrical
        {
            if ((color(root->left->left) == 'R') || color(root->left->right) == 'R')
            {
                if (color(root->right) == 'B')
                {
                    if (color(root->left->left) == 'R')
                    {
                        struct node *y = RR(root);
                        y->c = 'B';
                        y->right->c = 'R';
                        return y;
                    }
                    else
                    {
                        root->left = LR(root->left);
                        struct node *y = RR(root);
                        y->c = 'B';
                        y->right->c = 'R';
                        return y;
                    }
                }
                else if (color(root->right) == 'R')
                {
                    root->right->c = 'B';
                    root->left->c = 'B';
                    root->c = 'R';
                }
            }
        }
    }
    return root;
}

struct node *insertRB(struct node *root, int key)//required for calling root first
{
    struct node *x = createNode(key);
    root = insert(root, x);
    root->c = 'B';//making the root black , condition 1
    print(root);//calling the print function , almost doone
    printf("\n");//done
    return root;
}

int main()
{
    int d;
    struct node *root = (struct node *)malloc(sizeof(struct node));
    root = NULL;

    //    char c='c';
    //     while(c!='t'){
    //         scanf("%d",&d);
    //         root=insertRB(root,d);    
    //         scanf("%c",&c);
    //     }
    //     return 0;

    // This code fails when the first case might be t and is printing an extra output
    // Unlikely but better to take precaution

    while (1)
    {
        d = 0;
        char *s = (char *)malloc(20 * sizeof(char));
        scanf("%s", s);
        if (s[0] == 't')
        {
            return 0;
        }
        d = atoi(s);//digit by digit can also be extracted but easier approach
        root = insertRB(root, d);
    }
    return 0;

}
