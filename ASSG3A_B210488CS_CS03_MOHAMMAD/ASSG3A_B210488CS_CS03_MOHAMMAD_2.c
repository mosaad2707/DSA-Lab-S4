#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
int GET_NEXT_PROCESS(struct heap_size *h)
{
    if (h->heap > 0)
        return h->Q[0];
    else
        return -1;
}
void MIN_HEAPIFY(struct heap_size *h, int i)
{
    int l, r, min, temp;
    l = 2 * i + 1;
    r = 2 * i + 2;
    min = i;

    if (l < h->heap && h->Q[l] < h->Q[min])
        min = l;

    if (r < h->heap && h->Q[r] < h->Q[min])
        min = r;

    if (min != i)
    {
        temp = h->Q[i];
        h->Q[i] = h->Q[min];
        h->Q[min] = temp;
        MIN_HEAPIFY(h, min);
    }
}
void MIN_HEAPIFYI(struct heap_size *h, int i)
{
    int l, r, min, temp;
    l = 2 * i + 1;
    r = 2 * i + 2;
    min = i;

    if (l < h->heap && h->Q[l] < h->Q[min])
        min = l;

    if (r < h->heap && h->Q[r] < h->Q[min])
        min = r;

    if (min != i)
    {
        temp = h->Q[i];
        h->Q[i] = h->Q[min];
        h->Q[min] = temp;
        MIN_HEAPIFYI(h, (i - 1) / 2);
    }
}

void DELETEINF(struct heap_size *h, int k)
{
    int inf = -99999;
    int i;
    for (i = 0; i < h->heap; i++)
    {
        if (h->Q[i] == k)
        {
            h->Q[i] = -9999;
        }
    }
    MIN_HEAPIFYI(h, (i - 2) / 2);
    EXTRACT_NEXT_PROCESS(h);
}

int search(struct heap_size *h, int k)
{
    for (int i = 0; i < h->heap; i++)
    {
        if (h->Q[i] == k)
        {
            return 1;
        }
    }
    return 0;
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
    while (i >= 0 && h->Q[(i - 1) / 2] > h->Q[i])
    {
        temp = h->Q[i];
        h->Q[i] = h->Q[(i - 1) / 2];
        h->Q[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int EXTRACT_NEXT_PROCESS(struct heap_size *h)
{
    int min;
    if (h->heap > 0)
    {
        min = h->Q[0];
        h->Q[0] = h->Q[h->heap - 1];
        (h->heap)--;
        MIN_HEAPIFY(h, 0);
        return min;
    }
    else
        return -1;
}

void CHANGE_PRIORITY(struct heap_size *h, int k, int x)
{
    for (int i = 0; i < h->heap; i++)
    {
        if (h->Q[i] == k)
        {
            h->Q[i] = x;
        }
    }
    MIN_HEAPIFY(h, 0);
}

void DISPLAY_QUEUE(struct heap_size *h)
{
    for (int i = 0; i < h->heap; i++)
    {
        printf("%ld ", h->Q[i]);
    }
    printf("\n");
}

void DELETE(struct heap_size *h, int k)
{
    int inf = 9999999;
    CHANGE_PRIORITY(h, k, inf);
    (h->heap)--;
}

int main()
{
    int i, k, l, m;
    struct heap_size *h;
    h = (struct heap_size *)malloc(sizeof(struct heap_size));
    h->heap = 0;
    h->Q = (long int *)malloc(100000 * sizeof(*(h->Q)));
    char op;
    scanf("%c", &op);
    while (op != 'e')
    {
        switch (op)
        {
        case 'i':
            scanf("%d", &k);
            INSERT_PROCESS(h, k);
            break;
        case 'd':
            scanf("%d", &k);
            if (search(h, k) == 1)
            {
                DELETEINF(h, k);
                printf("%d\n", k);
            }
            else
            {
                printf("-1\n");
            }
            break;
        case 'p':
            DISPLAY_QUEUE(h);
            break;
        case 'x':
            EXTRACT_NEXT_PROCESS(h);
            DISPLAY_QUEUE(h);
            break;
        case 'r':
            scanf("%d %d", &l, &m);
            if (m > l)
            {
                printf("-1\n");
                break;
            }
            else
            {
                CHANGE_PRIORITY(h, l, m);
                printf("%d\n", m);
            }
            break;
        case 'g':
            printf("%d\n", GET_NEXT_PROCESS(h));
            break;
        }
        scanf("%c", &op);
    }
    return 0;
}

