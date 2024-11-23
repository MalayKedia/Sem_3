#include <bits/stdc++.h>
using namespace std;

// Function provided to calculate modulo inverse of a wrt a prime P if needed
long long modulo_inverse(long long a, long long P) {
  return a <= 1 ? a : P - (long long)(P/a) * modulo_inverse(P % a, P) % P;
}

long long cyclic_shifts(string s){
    // Complete this function
}

