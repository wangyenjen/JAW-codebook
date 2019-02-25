#include<bits/stdc++.h>
using namespace std;

int idx = 0;

void push(int k){
    idx += k;
    cout << " " << idx;
}

void _044(){
    const int A[8] = {2, 3, 2, -3, -3, 2, 3, 2};
    for(int i = 0; i < 8; i++){
        push(A[i]);
    }
}
void _034(){
    const int A[7] = {2, 3, 2, -3, -3, 2, 3};
    for(int i = 0; i < 7; i++){
        push(A[i]);
    }
}
void _1n0(int n){
    if(n&1){
        for(int i = 0; i < (n + 1) / 2; i++)
            push(2);
        push(-1);
        for(int i = 0; i < (n - 1) / 2; i++)
            push(-2);
    }
    else{
        for(int i = 0; i < n / 2; i++)
            push(2);
        push(1);
        for(int i = 0; i < n / 2; i++)
            push(-2);
    }
}
void _203k(int k){
    for(int i = 0; i < k; i++)
        push(3);
    push(1);
    for(int i = 0; i < k; i++)
        push(-3);
    push(1);
    for(int i = 0; i < k; i++)
        push(3);
}
void _203k2(int k){
    for(int i = 0; i <= k; i++)
        push(3);
    push(-1);
    for(int i = 0; i < k; i++)
        push(-3);
    push(-1);
    for(int i = 0; i <= k; i++)
        push(3);
}
void _n00(int n){
    for(int i = 0; i < n; i++)
        push(1);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("jumping.in", "r", stdin);
    freopen("jumping.out", "w", stdout);

    int T;
    cin >> T;

    while (T--) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << "0";
        idx = 0;
        if(c % 3 == 0){
            _203k(c / 3);
            _n00(a - 3);
            _1n0(b);
        }
        else if(c % 3 == 2){
            _203k2(c / 3);
            _n00(a - 3);
            _1n0(b);
        }
        else{
            if(b == 3){
                _203k(c / 3 - 1);
                _n00(a - 2);
                _034();
            }
            else{
                _203k(c / 3 -1);
                _044();
                _n00(a - 3);
                _1n0(b - 4);
            }
        }
        cout << "\n";
    }
}
