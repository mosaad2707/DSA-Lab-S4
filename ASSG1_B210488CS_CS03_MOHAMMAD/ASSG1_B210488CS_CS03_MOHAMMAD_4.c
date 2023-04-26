#include <stdio.h>
#include <stdlib.h>
int c;
struct node
{
    long int key;
    struct node *right;
    struct node *left;
    struct node *p;
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
    x->p = NULL;
    x->key = k;
    return x;
}

void INSERT(struct tree *t, struct node *n)
{
    long int k;
    scanf("%ld", &k);
    n = create_node(k);
    struct node *x = t->root;
    struct node *y = NULL; // both x and y are pointers (imp)
    while (x != NULL)
    {
        y = x;
        if (n->key <= x->key)
        {
            x = x->left;
        }
        else
            x = x->right;
    }
    n->p = y;
    if (y == NULL)
        t->root = n;
    else if (n->key < y->key)
        y->left = n;
    else
        y->right = n;
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

struct node *FIND_MIN(struct node *x)
{
    while (x->left != NULL)
    {
        x = x->left;
    }
    return x;
}

struct node *FIND_MAX(struct node *y)
{
    while (y->right != NULL)
    {
        y = y->right;
    }
    return y;
}

void PREORDER(struct node *t)
{
    if (t != NULL)
    {
        printf("%ld ", t->key);
        PREORDER(t->left);
        PREORDER(t->right);
    }
}

void POST(struct node *t)
{
    if (t != NULL)
    {

        POST(t->left);
        POST(t->right);
        printf("%ld ", t->key);
    }
}

void INORDER(struct node *t)
{
    if (t != NULL)
    {

        INORDER(t->left);
        printf("%ld ", t->key);
        INORDER(t->right);
    }
}

struct node *SUCCESSOR(struct node *x, long int k)
{
    if (SEARCH(x, k) == NULL)
    {
        return NULL;
    }
    if (x->right != NULL)
    {
        return FIND_MIN(x->right);
    }
    struct node *y = x->p;
    while (y != NULL && x == y->right)
    {
        x = y;
        y = y->p;
    }
    return y;
}

struct node *predecessor(struct node *x, long int k)
{
    if (SEARCH(x, k) == NULL)
    {
        return NULL;
    }

    if (x->left != NULL)
    {
        return FIND_MAX(x->left);
    }
    struct node *y = x->p;
    while (y != NULL && x == y->left)
    {
        x = y;
        y = y->p;
    }
    return y;
}

void TRANSPLANT(struct tree *t, struct node *x, struct node *y)
{
    if (x->p == NULL)
        t->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    if (y != NULL)
        y->p = x->p;
}

long int DELETE(struct tree *t, int k)
{
    struct node *x;
    x = t->root;
    x = SEARCH(x, k);
    if (x == NULL)
        return -1;
    else
    {
        if (x->left == NULL)
            TRANSPLANT(t, x, x->right);
        else if (x->right == NULL)
            TRANSPLANT(t, x, x->left);
        else
        {
            struct node *y = FIND_MIN(x->right);
            if (y->p != x)
            {
                TRANSPLANT(t, y, y->right);
                y->right = x->right;
                y->right->p = y;
            }
            TRANSPLANT(t, x, y);
            y->left = x->left;
            y->left->p = y;
        }
        return k;
    }
}

int glevel(struct node *x, int data, int level)
{
    if (x == NULL)
        return 0;

    if (x->key == data)
        return level;

    int c = glevel(x->left, data, level + 1);
    if (c != 0)
        return c;

    c = glevel(x->right, data, level + 1);
    return c;
}
int level(struct node *n, int data)
{
    return glevel(n, data, 1);
}

int main()
{
    struct tree *t;
    struct node *x;
    struct node *y;
    struct node *z;
    long int l;
    t = (struct tree *)malloc(sizeof(struct tree));
    t->root = NULL;
    char op;
    scanf("%c", &op);
    long int k;
    while (op != 'e')
    {

        switch (op)
        {
        case 'a':
            INSERT(t, x);
            break;
         case 'd':
        {
            scanf("%ld", &k);
            l = DELETE(t, k);
            if (l == -1)
            {
                printf("-1\n");
            }
            break;
        }    
        case 's':
        {
            int k;
            scanf("%d", &k);
            x = SEARCH(t->root, k);
            if (x == NULL)
            {
                printf("-1\n");
            }
            else
                printf("1\n");
        break;        
        }
        case 'l':
        {
            int k;
            scanf("%d", &k);
            if (level(t->root, k))
            {
                printf("%d\n", level(t->root, k));
            }
            else
                printf("-1\n");
            break;
        }
        case 'm':
        {
            y = FIND_MIN(t->root);
            printf("%ld\n", y->key);
            break;   
        }

        case 'x':
        {
            y = FIND_MAX(t->root);
            printf("%ld\n", y->key);
            break;
        }

        case 'u':
        {
            scanf("%ld", &k);
            y = SEARCH(t->root, k);
            z = SUCCESSOR(y, k);
            if (z == NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%ld\n", z->key);
            }
        }
        break;
        case 'r':
        {
            scanf("%ld", &k);
            y = SEARCH(t->root, k);
            z = predecessor(y, k);
            if (z == NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%ld\n", z->key);
            }
        }
        break;       
        case 'i':
            if (t->root == NULL)
            {
                printf("-1\n");
                break;
            }
            else
            {
                INORDER(t->root);
                printf("\n");
            }
            break;
        case 'p':
            if (t->root == NULL)
            {
                printf("-1\n");
                break;
            }
            else
            {
                PREORDER(t->root);
                printf("\n");
            }
            break;
        case 't':
            if (t->root == NULL)
            {
                printf("-1\n");
                break;
            }
            else
            {
                POST(t->root);
                printf("\n");
            }
            break;
        }

        scanf("%c", &op);
    }
}

