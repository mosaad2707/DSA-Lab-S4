#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#define TABLE_SIZE 4

typedef struct
{
    char name[100];
    char roll[9];
    int age;

} student;

struct node
{
    char name[100];
    char roll[9];
    int age;
    struct node *next;
};
unsigned int hash(char *name,int age)
{
    int n = strlen(name);
    unsigned int hv = 0;
    for (int i = 0; i <=n; i++)
    {
        hv=hv+name[i];
    }
    hv=hv+age;
    return hv % TABLE_SIZE;
}

struct node *head[TABLE_SIZE] = {NULL}, *c;

void insert(char scan_name[], char scan_roll[], int scan_age)
{
    int j;
    j = hash(scan_name,scan_age);
    struct node *new1 = (struct node *)malloc(sizeof(struct node));
    new1->age = scan_age;
    int a = strlen(scan_name);
    for (int i = 0; i < a; i++)
    {
        new1->name[i] = scan_name[i];
    }
    for (int i = 0; i < 9; i++)
    {
        new1->roll[i] = scan_roll[i];
    }
    new1->next = NULL;
    if (head[j] == NULL)
    {
        head[j] = new1;
    }
    else
    {
        c = head[j];
        while (c->next != NULL)
        {
            c = c->next;
        }
        c->next = new1;
    }
}

void print_student(int j)
{
    int count = 0;
    if (head[j] == NULL)
    {
        printf("0\n");
        return;
    }
    else
    {
        c = head[j];
        while (c != NULL)
        {
            count++;
            c = c->next;
        }
        c = head[j];
        printf("%d ",count);
        while (c != NULL)
        {
            printf("%s ", c->name);
            c = c->next;
        }
        printf("\n");
    }
}

void check(int j, char br[])
{   char a,b;
    a=toupper(br[0]);
    b=toupper(br[1]);
    int count = 0;
    if (head[j] == NULL)
    {
        printf("-1\n");
        return;
    }
    else
    {
        c = head[j];
        while (c != NULL)
        {
            if (toupper(c->roll[7]) == a && toupper(c->roll[8])==b)
            {
                printf("%s ", c->name);
                count++;
            }
            c = c->next;
        }
        if (count == 0)
        {
            printf("-1");
        }
        printf("\n");
    }
}

int main()
{
    int n;
    student s[1000];
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%s %s %d",s[i].name,s[i].roll,&s[i].age);
    }
    for(int i=0;i<n;i++)
    {
        insert(s[i].name, s[i].roll, s[i].age);
    }
    char op[1];
    while (1)
    {
        scanf("%s", op);
        if (op[0] == 'c')
        {
            int u;
            scanf("%d", &u);
            print_student(u);
        }
        else if (op[0] >= '0' && op[0] <= '3')
        {
            char br[2];
            scanf("%s", br);
            int k = atoi(op);
            check(k, br);
        }
        if(op[0]=='e')
        {
            break;
        }
    }
    return 0;
   
}

// for(int i=0;i<n;i++){
    //     scanf("%s %s %d\n",s[i].name,s[i].roll,&s[i].age);
    // }
    // for(int i=0;i<n;i++)
    // {
    //     insert(s[i].name, s[i].roll, s[i].age);
    // }
    // char op;
    // while (1)
    // {
    //     scanf("\n%c ", &op);
    //     if (op == 'c')
    //     {
    //         int u;
    //         scanf("%d", &u);
    //         print_student(u);
    //     }
    //     else if (op >= '0' && op <= '3')
    //     {
    //         char br[2];
    //         scanf("%s", br);
    //         int k = atoi(&op);
    //         check(k, br);
    //     }
    //     else
    //     {
    //         return 0;
    //     }
    // }
