#include<bits/stdc++.h>
using namespace std;

int n, m;

int main(){
    freopen("continued.in", "r", stdin);
    freopen("continued.out", "w", stdout);
    scanf("%d%d", &n, &m);
    if(n % m == 0){
        printf("1\n");
        if(n < m)
            printf("0");
        else{
            for(int i = n - m; i >= 0; i--){
                if(i % m == n % m)
                    printf("1");
                else
                    printf("0");
            }
        }
        printf(" ");
        for(int i = 0; i < m; i++)
            printf("9");
        printf("\n");
    }
    else{
        printf("3\n");
        if(n < m)
           printf("0");
        else{ 
            for(int i = n - m; i >= 0; i--){
                if(i % m == n % m)
                    printf("1");
                else
                    printf("0");
            }
        }
        printf(" ");
        for(int i = 0; i < m - n % m; i++)
            printf("9");
        printf(" 1 ");
        for(int i = 0; i < n % m; i++)
            printf("9");
        printf("\n");
    }
}
