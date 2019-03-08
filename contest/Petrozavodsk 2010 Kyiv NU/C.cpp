#include<bits/stdc++.h>
using namespace std;

vector<int>jmp;
vector<int>gr;

vector<int> itov(int i){
    vector<int>ans;
    while(i > 0){
        ans.push_back(i&1);
        i >>= 1;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
int vtoi(vector<int> V){
    int ans = 0;
    for(auto p : V)
        ans = ans * 2 + p;
    return ans;
}

int main(){
    jmp.push_back(1);
    jmp.push_back(2);
    jmp.push_back(3);
    gr.push_back(0);
    while(1){
        int n = (int)gr.size();
        vector<int>V = itov(n);
        vector<int>mygr;
        for(int i = 0; i < (int)V.size(); i++) if(V[i] == 1){
            for(auto j : jmp){
                vector<int>tmp = V;
                int now = i;
                while(now < (int)V.size()){
                    tmp[now] ^= 1;
                    mygr.push_back(gr[vtoi(tmp)]);
                    now += j;
                }
            }
        }
        sort(mygr.begin(), mygr.end());
        int idx = -1;
        for(int i = 0; i < (int)mygr.size(); i++){
            //printf(">> %d ", mygr[i]);
            if(mygr[i] == idx)
                continue;
            else if(mygr[i] == idx + 1)
                idx++;
            else
                break;
        }
        gr.push_back(++idx);
        if(idx >= 0){
            int tmp = (int)gr.size() - 1;
            while(tmp % 2 == 0)
                tmp >>= 1;
            if(tmp == 1){
                printf("%d\n", idx);
                char t;
                scanf("%c", &t);
            }
        }
    }
}
