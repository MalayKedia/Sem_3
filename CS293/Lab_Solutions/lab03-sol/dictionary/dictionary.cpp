#include "dictionary.h"

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry [N];
};

Dictionary::~Dictionary(){
    delete [] A;
};

#define factor 31
#define alpha 0.6180339887
#define TOMBSTONE (char*)0xabcdabcdabcdabcd

int Dictionary::hashValue(char key[]){

    // function should return fibonacci compression applied to the polynomial hash value
    // to prevent overflow in polynomial rolling hash, we will only store its fractional part

    // observe that {p * {alpha * x} + alpha * y} = {alpha * (p * x + y)} where x, y, p are integers and alpha is a float
    // Hence we have
    // {alpha * (a0 + a1 p^1 + a2 p^2 + ... + an p^n)} = {alpha * a0 + p * {alpha * (a1 + a2 p^1 + ... + an p^n-1)}}
    // which we can compute iteratively

    double fracHashValue = 0;
    for(int i = strlen(key) - 1; i >=0; i--){
    	fracHashValue *= factor;
    	fracHashValue += alpha*key[i];
    	fracHashValue -= int(fracHashValue);
    }
    return int(N*fracHashValue);
}

int Dictionary::findFreeIndex(char key[]){
    int hash = hashValue(key);
    // find free index
    for(int i = 0; i < N; i++){
        int index = (hash + i) % N;
        if(A[index].key == NULL){
            return index;
        }
    }
    return -1;
}

struct Entry* Dictionary::get(char key[]){
    int hash = hashValue(key);
    // find key
    for(int i = 0; i < N; i++){
        int index = (hash + i) % N;
        if(A[index].key != NULL && A[index].key != TOMBSTONE && 
                strcmp(A[index].key, key) == 0){
            return &A[index];
        }
    }
    return NULL;
}

bool Dictionary::put(Entry e) {
    int hash = hashValue(e.key);
    for (int i = 0; i < N; i++) {
        int index = (hash + i) % N;
        if (A[index].key == NULL || A[index].key == TOMBSTONE) {
            A[index] = e;
            return true;
        }
    }
    return false;
}

bool Dictionary::remove(char key[]){
    int hash = hashValue(key);
    // find key
    for(int i = 0; i < N; i++){
        int index = (hash + i) % N;
        if(A[index].key != NULL && strcmp(A[index].key, key) == 0){
            A[index].key = TOMBSTONE;
            return true;
        }
    }
    return false;
}
