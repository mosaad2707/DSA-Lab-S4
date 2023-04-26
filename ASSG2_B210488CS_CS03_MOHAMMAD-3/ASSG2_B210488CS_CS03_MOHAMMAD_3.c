#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

int main(){
    int m,c1,c2,key;
    scanf("%d",&m);
    int arr1[m],arr2[m];
    int freq1[1000000]={0},freq2[1000000]={0};
    for(int i=0;i<m;i++){
        scanf("%d",&arr1[i]);
        freq1[arr1[i]]++;
    }

    for(int i=0;i<m;i++){
        scanf("%d",&arr2[i]);
        freq2[arr2[i]]++;
    }
    for(int i=0;i<1000000;i++){
        if(freq1[i]!=freq2[i]){
            printf("0\n");
            return 0;
        }
    }
    printf("1\n");
    return 0;
        
 }

