#include<bits/stdc++.h>
using namespace std;

const int N = 200000 + 7;
int A[N];
int block[N];
int n;

int main(){
    freopen("crossword.in", "r", stdin);
    scanf("%d", &n);
    int cnt = -1;
    for(int i = 0; i < n; i++){
        scanf("%d", &A[i]);
        if(i == 0 || A[i] < A[i - 1])
            cnt++;
        block[A[i]] = cnt;
    }
    int l = 1, r = n + 1;
    while(l + 1 < r && block[l] == block[l + 1])
        l++;
    while(l + 1 < r && block[r - 1] == block[r - 2])
        r--;
    block[r] = -87;

    vector<int>ans, tmp;
    int flag = 0, flag2 = 0;
    for(int i = l; i <= r; i++){
        if(i == l || block[i] < block[i - 1]){
            if(i > l && block[i] < block[i - 1]){
                if(block[tmp[0]] == 0 && block[i - 1] == cnt && flag == 0){
                    if(ans.empty() || flag2 == 1)
                        ans = tmp;
                }
            }
            tmp.clear();
            tmp.push_back(i);
            flag = 0;
            flag2 = 0;
        }
        else{
            tmp.push_back(i);
            if(block[i] == block[i - 1])
                flag2 = 1;
            if(block[i] > block[i - 1] + 1)
                flag = 1;
        }
    }
    printf("%d\n", (int)ans.size());
    for(int i = 0; i < (int)ans.size(); i++){
        printf("%d%c", ans[i], " \n"[i == (int)ans.size() - 1]);
    }
}
