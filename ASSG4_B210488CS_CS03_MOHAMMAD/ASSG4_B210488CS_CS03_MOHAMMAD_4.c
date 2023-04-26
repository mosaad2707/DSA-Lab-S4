// Mosaad 060423; 1509

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
    int v;
    int w;
    struct node *next;
};

// This function creates a new edge/node in a graph with vertex v and weight 0.
// The edge is represented as a linked list node with a pointer to the next node in the list.
struct node *makeedge(int v)
{
    // Allocate memory for the new node
    struct node *x = (struct node *)malloc(sizeof(struct node));
    // Set the vertex and weight of the new node
    x->v = v;
    x->w = 0;
    x->next = NULL;
    return x;
}

// This function finds the minimum-weight edge to add to a minimum spanning tree in a graph, using the Prim's algorithm.
// It takes as input an adjacency list 'list', the number of vertices in the graph 'n', and an array 'visit' which tracks the visited vertices.
int findminforprim(struct node **list, int n, int visit[])
{
    struct node *y = NULL;
    int u, v;
    int travel = 999999; // initialize 'travel' variable to a large value as a sentinel value.

    // Iterate over all vertices in the graph.
    for (int i = 0; i < n; i++)
    {
        // If the vertex has been visited already, traverse its adjacency list.
        if (visit[i] == 1)
        {
            y = list[i];
            while (y != NULL)
            {
                // If the weight of the current edge is less than the current minimum and the destination vertex has not been visited,
                // update the minimum weight and the corresponding vertices.
                if (travel > y->w && visit[y->v] != 1)
                {
                    v = y->v;
                    travel = y->w;
                }
                y = y->next;
            }
        }
    }
    // Mark the destination vertex as visited.
    visit[v] = 1;
    return travel;
}

// This function implements the Prim's algorithm to find the minimum spanning tree of a graph.
// It takes as input an adjacency list 'list' and the number of vertices in the graph 'n'.
int prim(struct node **list, int n)
{
    int final = 0; // you forgot to initialize again lol
    int *visit = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        visit[i] = 0;
    }
    visit[0] = 1;
    // Iterate n-1 times to find the n-1 edges in the minimum spanning tree.
    for (int i = 0; i < n - 1; i++)
    {
        final += findminforprim(list, n, visit);
    }
    return final;
}

int findminforkrusk(struct node **list, int n, int *component)
{
    struct node *y = NULL;
    int u, v, travel = 100000;
    // list: a pointer to an array of struct node which represents the adjacency list of the graph.
    // n: an integer which represents the number of vertices in the graph.
    // component: a pointer to an integer array which represents the component to which each vertex belongs.
    for (int i = 0; i < n; i++)
    {
        y = list[i];
        while (y != NULL)
        {
            if (travel > y->w && component[i] != component[y->v])
            {
                u = i;
                v = y->v;
                travel = y->w;
            }
            y = y->next;
        }
    }
    // above The function first initializes y as a NULL pointer, u, v and travel to some arbitrary values. It then iterates through all the vertices of the graph
    //  and for each vertex i, it iterates through all its adjacent vertices and checks if the weight of the edge connecting i and its adjacent vertex is less than the current value of travel and if the adjacent vertex belongs to a different component than i. If these conditions are satisfied, then it updates u, v and travel with the values of i, the adjacent vertex and the weight of the edge connecting them, respectively.
    int d = component[v];
    for (int i = 0; i < n; i++)
    {
        if (component[i] == d)
        {
            component[i] = component[u];
        }
    }
    return travel;
}

int kruskal(struct node* *list, int n)
{
    int *component = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        component[i] = i;
    }
    int final = 0;
    // Loop through the list n-1 times to find the minimum edge for each component.
    for (int i = 0; i < n - 1; i++)
    {
        final += findminforkrusk(list, n, component);
    }
    return final;
}

int main()
{
    char c;
    int n, u, v;

    scanf("%c", &c);
    scanf("%d\n", &n);

    // Create an adjacency list for the graph and initialize it to NULL.
    char *str;
    struct node **list = (struct node **)malloc(n * sizeof(struct node));
    for (int i = 0; i < n; i++)
    {
        list[i] = NULL;
    }

    struct node *x;
    struct node *y;

    // Read in the edges of the graph from the user and create the adjacency list.
    for (int i = 0; i < n; i++)
    {
        // Read in a line of input from the user.
        str = (char *)malloc(10000 * sizeof(char));
        fgets(str, 10000, stdin);

        u = 0;
        v = 0;

        // Parse the line of input to get the edges of the graph.
        for (u = 0; u < strlen(str) - 1; u++)
        {
            if (str[u] == ' ')
            {
                if (v != i)
                {
                    // Create an edge between vertex i and vertex v with weight 0.
                    x = makeedge(v);
                    y = list[i];
                    if (y == NULL)
                    {
                        list[i] = x;
                    }
                    else
                    {
                        while (y->next != NULL)
                        {
                            y = y->next;
                        }
                        y->next = x;
                    }
                }
                v = 0;
            }
            else
            {
                v = v * 10 + str[u] - '0';
            }
        }

        // Create the edge for the last vertex in the line.
        if (v != i)
        {
            x = makeedge(v);
            y = list[i];
            if (y == NULL)
            {
                list[i] = x;
            }
            else
            {
                while (y->next != NULL)
                {
                    y = y->next;
                }
                y->next = x;
            }
        }
    }

    // Read in the weights for the edges of the graph from the user and update the adjacency list.
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &u);
        y = list[u];
        while (y != NULL)
        {
            scanf("%d", &v);
            y->w += v;
            y = y->next;
        }
    }
    // Compute the minimum spanning tree of the graph using Prim's algorithm and print the weight of the tree.
    switch (c)
    {
    case 'a':
        printf("%d\n", prim(list, n));
        break;
    case 'b':
        printf("%d\n", kruskal(list, n));
        break;
    }
    return 0;
}
/*Rather than using node alternately using matrix as input;
int main(){
    int n;
    scanf("%d",&n);
     int** arr=(int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        arr[i]=(int*)malloc(n*sizeof(int));
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            arr[i][j]=-1;
        }
    }
    char c;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d%c",&arr[i][j],&c);
            if(c=='\n'){
                arr[i][j+1]=-1; // add -1 at the end of each row
                break;
            }
        }
    }
    int **graph=(int **)malloc(n*sizeof(int *));
    for(int i=0;i<n;i++){
        graph[i]=(int*)malloc(n*sizeof(int));
    }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         printf("%d ",arr[i][j]);
    //     }
    //     printf("\n");
    // }
    int j=n;
    int a,b,k=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            graph[i][j]=-1;
        }
    }
    while(j--){
        scanf("%d%c",&a,&c);
        if(c=='\n'){
            continue;
        }
        // printf("\nA is  |n%d\n",a);
        for(int i=0;i<n;i++){
            scanf("%d%c",&b,&c);
            graph[a][arr[a][k]]=b;
            // printf("%d %d ",k,arr[a][k]);
            k++;
            if(c=='\n'){
                k=1;
                break;
            }

        }
    }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         printf("%d ",graph[i][j]);
    //     }
    //     printf("\n");
    // }
    int flag;
    int u,v;
    
    return 0;
}
*/



