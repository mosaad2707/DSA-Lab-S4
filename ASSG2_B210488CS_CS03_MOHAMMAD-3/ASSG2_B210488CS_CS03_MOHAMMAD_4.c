#include <stdio.h>
#include <stdlib.h>

#define MAX_TABLE_SIZE 100

// int bigPrime(int m){
//     int ans,flag,n=2;
//     while(n<m){
//         flag=0;
//         for(int i=2;i<(n/2);i++){
//             if(n%i==0){
//                 flag=1;
//             }
//         }
//         if (flag==0){
//             ans=n;
//         }
//         n++;
//     }
//     return ans;
// }

int isPrime(int n) {
	if(n < 2) return 0;
	for(int i = 2; i*i <= n; ++i) if(n%i == 0) return 0;
	return 1;
}

void clear_table(int table[], int table_size)
{
    for (int i = 0; i<table_size; i++)
    {
        table[i] = -1;
    }
}
int linprob(int val, int table_size, int table[])
{
    int loc = val % table_size;
    int i = 0, c = 0;
    while (table[loc] != -1 )
    {
        i++;
        c++;
        loc = (val + i) % table_size;
    }
    printf("%d ", loc);
    table[loc] = val;
    return c;
}

int quadprob(int val, int table_size, int table[])
{
    int loc = val % table_size;
    int i = 0, c = 0;
    while (table[loc] != -1 )
    {
        i++;
        c++;
        loc = (val + i * i) % table_size;
        if(i>=table_size){
            break;
        }
    }
    if(i>=table_size){
        printf("E ");
    }
    else
        printf("%d ", loc);
    table[loc] = val;
    return c;
}

int doubhash(int val, int table_size, int table[])
{
    int loc = val % table_size;
    int h1=loc;
    int i = 1, c = 0;
    int R;
    // int R = bigPrime(table_size);
    for(int i = table_size-1; i >= 2; --i) {
			if(isPrime(i)) {
				R = i;
				break;
			}
		}
    int h2 = R - (val % R);

    while (table[loc] != -1 )
    {   
        
        loc = (h1+ (i * h2)) % table_size;
        i++;
        c++;
    }
    printf("%d ", loc);
    table[loc] = val;
    return c;
}

int main()
{
    int table_size, val[MAX_TABLE_SIZE], table[MAX_TABLE_SIZE];
    int i, c;
    scanf("%d\n", &table_size);
    clear_table(table, table_size);
    char str[1000];
    int arr[1000]={0};
    fgets(str,1000,stdin);
    int m=0,num;
    int o=0;
    while(str[m]!='\n'){
        num=0;
       while(str[m]!=' ' && str[m]!='\n'){
        num=10*num+(str[m]-'0');
        m++;
       }
       arr[o]=num;
       o++;
       if(str[m]=='\n'){
        break;
       }
       m++;
    }
    int u=o;
    c = 0;
    for (i = 0; i < u; i++)
    {
        c += linprob(arr[i], table_size, table);
    }

    printf("\n%d\n", c);

    clear_table(table, table_size);
    c = 0;
    for (i = 0; i < u; i++)
    {
        c += quadprob(arr[i], table_size, table);
    }

    printf("\n%d\n", c);

    clear_table(table, table_size);
    c = 0;
    for (i = 0; i < u; i++)
    {
        c += doubhash(arr[i], table_size, table);
    }

    printf("\n%d\n", c);

    return 0;
}

