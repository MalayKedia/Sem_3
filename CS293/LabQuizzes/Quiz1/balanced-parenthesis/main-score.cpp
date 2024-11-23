#include <bits/stdc++.h>
#include "./balanced.cpp"

using namespace std;

// DO NOT MODIFY THE MAIN FUNCTION
int main(){
    int n;
    cin>>n;

    vector<int> A(n);
    for(int i= 0;i<n;i++){
        cin>>A[i];
    }
    string s;
    cin>>s;
    
    cout<<score(A,n,s)<<endl;
    return 0;
}
