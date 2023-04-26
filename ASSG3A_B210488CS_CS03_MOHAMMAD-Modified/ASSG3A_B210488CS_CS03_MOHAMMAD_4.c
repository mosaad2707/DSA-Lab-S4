// PQ using linked list , wrote it as an array first

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node
{
    int key;
    struct node *next;
};

struct PQ
{
    struct node *head;
};

struct node *create_node(int k)
{
    struct node *x = (struct node *)malloc(sizeof(struct node));
    x->key = k;
    x->next = NULL;
    return x;
}
void insert(struct PQ *q, int k)
{
    struct node *x = create_node(k);
    if (q->head == NULL)
    {
        q->head = x;
    }
    else
    {
        struct node *prev = NULL;
        struct node *curr = q->head;

        while (curr != NULL && k >= curr->key)
        {
            prev = curr;
            curr = curr->next;
        }

        if (prev != NULL)
        {
            x->next = prev->next;
            prev->next = x;
           
        }
        else
        {
            x->next = q->head;
            q->head = x;
        }
    }
}

int extract(struct PQ *q)
{
    if (q->head == NULL)
    {
        return 0;
    }
    int min = q->head->key;
    struct node *temp = q->head;
    q->head = q->head->next;
    free(temp);
    return min;
}

int main()
{
    int n;
    scanf("%d", &n);
    /*on declaring the PQ as *q and later referencing the q->head as null it leads to a seg fault
    not sure why but on the same time just passing it as an address and treating it normally overruns the case*/

    struct PQ q;   //*q fails
    q.head = NULL; // q->head fails
    int arr[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        insert(&q, arr[i]);
    }

    int cost = 0;
    while (q.head != NULL && q.head->next != NULL)
    {
        int a = extract(&q);
        int b = extract(&q);
        int sum = a + b;
        insert(&q, sum);
        cost =cost + sum;
    }

    printf("%d\n", cost);

    return 0;
}

// struct heap_size
// {
//     long int *Q;
//     int heap;
// };
// int GET_NEXT_PROCESS(struct heap_size *h);
// void MIN_HEAPIFY(struct heap_size *h, int i);
// void INSERT_PROCESS(struct heap_size *h, int k);
// void HEAP_DECREASE_KEY(struct heap_size *h, int i, int k);
// int EXTRACT_NEXT_PROCESS(struct heap_size *h);
// void DISPLAY_QUEUE(struct heap_size *h);
// int GET_NEXT_PROCESS(struct heap_size *h);

// void MIN_HEAPIFY(struct heap_size *h, int i)
// {
//     int l, r, min, temp;
//     l = 2 * i + 1;
//     r = 2 * i + 2;
//     min = i;

//     if (l < h->heap && h->Q[l] < h->Q[min])
//         min = l;

//     if (r < h->heap && h->Q[r] < h->Q[min])
//         min = r;

//     if (min != i)
//     {
//         temp = h->Q[i];
//         h->Q[i] = h->Q[min];
//         h->Q[min] = temp;
//         MIN_HEAPIFY(h, min);
//     }
// }

// void INSERT_PROCESS(struct heap_size *h, int k)
// {
//     (h->heap)++;
//     HEAP_DECREASE_KEY(h, h->heap - 1, k);
// }

// void HEAP_DECREASE_KEY(struct heap_size *h, int i, int k)
// {
//     int temp;
//     h->Q[i] = k;
//     while (i >= 0 && h->Q[(i - 1) / 2] > h->Q[i])
//     {
//         temp = h->Q[i];
//         h->Q[i] = h->Q[(i - 1) / 2];
//         h->Q[(i - 1) / 2] = temp;
//         i = (i - 1) / 2;
//     }
// }

// int EXTRACT_NEXT_PROCESS(struct heap_size *h)
// {
//     int max;
//     if (h->heap > 0)
//     {
//         max = h->Q[0];
//         h->Q[0] = h->Q[h->heap - 1];
//         (h->heap)--;
//         MIN_HEAPIFY(h, 0);
//         return max;
//     }
//     else
//         return -1;
// }

// void DISPLAY_QUEUE(struct heap_size *h){
//    for(int i = 0; i < h->heap; i++){
//     printf("%ld ",h->Q[i]);

//    }
//    printf("\n");
// }

// int main()
// {
//     int i, k,l,m;
//     struct heap_size *h;
//     h = (struct heap_size *)malloc(sizeof(struct heap_size));
//     h->heap = 0;
//     h->Q = (long int*)malloc(100000 * sizeof(*(h->Q)));
//     {
//         int k;
//         scanf("%d",&k);
//         int arr[k];
//         for(int i=0;i<k;i++){
//             scanf("%d",&arr[i]);
//             INSERT_PROCESS(h,arr[i]);
//         }
//         int l;

//         int sum[k-1];
//         for(int i=0;i<k-1;i++){
//             int m1,m2;
//             m1=EXTRACT_NEXT_PROCESS(h);
//             m2=EXTRACT_NEXT_PROCESS(h);
//             sum[i]=m1+m2;
//             INSERT_PROCESS(h,sum[i]);

//         }
//         int calc=0;
//         for(int i=0;i<k-1;i++){
//             calc=calc+sum[i];
//         }
//         printf("%d\n",calc);
//         return 0;
//     }
// }
