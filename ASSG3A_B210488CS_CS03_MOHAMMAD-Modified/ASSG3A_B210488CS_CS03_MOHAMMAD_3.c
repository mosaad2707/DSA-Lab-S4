#include <stdio.h>
#include<stdlib.h>
#include<limits.h>

struct heap_size
{
    long int *Q;
    int heap;
};
int GET_NEXT_PROCESS(struct heap_size *h);
void MIN_HEAPIFY(struct heap_size *h, int i);
void INSERT_PROCESS(struct heap_size *h, int k);
void HEAP_DECREASE_KEY(struct heap_size *h, int i, int k);
int EXTRACT_NEXT_PROCESS(struct heap_size *h);
void DISPLAY_QUEUE(struct heap_size *h);
int GET_NEXT_PROCESS(struct heap_size *h);


void MAX_HEAPIFY(struct heap_size *h, int i)
{
    int l, r, max, temp;
    l = 2 * i + 1;
    r = 2 * i + 2;
    max = i;

    if (l < h->heap && h->Q[l] > h->Q[max])
        max = l;

    if (r < h->heap && h->Q[r] > h->Q[max])
        max = r;

    if (max != i)
    {
        temp = h->Q[i];
        h->Q[i] = h->Q[max];
        h->Q[max] = temp;
        MAX_HEAPIFY(h, max);
    }
}

void INSERT_PROCESS(struct heap_size *h, int k)
{
    (h->heap)++;
    HEAP_DECREASE_KEY(h, h->heap - 1, k);
}

void HEAP_DECREASE_KEY(struct heap_size *h, int i, int k)
{
    int temp;
    h->Q[i] = k;
    while (i >= 0 && h->Q[(i - 1) / 2] < h->Q[i])
    {
        temp = h->Q[i];
        h->Q[i] = h->Q[(i - 1) / 2];
        h->Q[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int EXTRACT_NEXT_PROCESS(struct heap_size *h)
{
    int max;
    if (h->heap > 0)
    {
        max = h->Q[0];
        h->Q[0] = h->Q[h->heap - 1];
        (h->heap)--;
        MAX_HEAPIFY(h, 0);
        return max;
    }
    else
        return -1;
}

void DISPLAY_QUEUE(struct heap_size *h){
   for(int i = 0; i < h->heap; i++){
    printf("%ld ",h->Q[i]);

   }
   printf("\n");
}

int main()
{
    int i, k,l,m;
    struct heap_size *h;
    h = (struct heap_size *)malloc(sizeof(struct heap_size));
    h->heap = 0;
    h->Q = (long int*)malloc(100000 * sizeof(*(h->Q)));
    int t;
    scanf("%d", &t);
    while(t--){
        int k;
        scanf("%d",&k);
        int arr[k];
        for(int i=0;i<k;i++){
            scanf("%d",&arr[i]);
            INSERT_PROCESS(h,arr[i]);
        }
        int l;
        scanf("%d",&l);
        while(l--){
            printf("%d ", EXTRACT_NEXT_PROCESS(h));
        }
        printf("\n");
        int j=k-l;
        while(j--){
        EXTRACT_NEXT_PROCESS(h);
        }
    }
}

