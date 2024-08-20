#include "dictionary.h"

Dictionary::Dictionary(){
    N = DICT_SIZE;
    A = new Entry[N];
    for(int i = 0; i < N; i++){
        Entry* e = new Entry;
        e->key = "";
        e->value = (int)NULL;
        A[i] = *e;
    }
};

#define factor 31
#define alpha 0.6180339887
#define TOMBSTONE "TOMBSTONE"

int Dictionary::hashValue(std::string key){

    // function should return fibonacci compression applied to the polynomial hash value
    // to prevent overflow in polynomial rolling hash, we will only store its fractional part

    // observe that {p * {alpha * x} + alpha * y} = {alpha * (p * x + y)} where x, y, p are integers and alpha is a float
    // Hence we have
    // {alpha * (a0 + a1 p^1 + a2 p^2 + ... + an p^n)} = {alpha * a0 + p * {alpha * (a1 + a2 p^1 + ... + an p^n-1)}}
    // which we can compute iteratively

    double fracHashValue = 0;
    for(int i = key.length() - 1; i >=0; i--){
    	fracHashValue *= factor;
    	fracHashValue += alpha*key[i];
    	fracHashValue -= int(fracHashValue);
    }
    return int(N*fracHashValue);
}

int Dictionary::findFreeIndex(std::string key){
    int hash = hashValue(key);
    
    for(int i = 0; i < N; i++){
        int index = (hash + i)%N;
        
        if(A[index].key == ""){
            return index;
        }
        else if(A[index].key == TOMBSTONE){
            return index;
        }
        else if(A[index].key == key){
            return index;
        }
    }
    return -1;
}

struct Entry* Dictionary::get(std::string key){
    int hash = hashValue(key);

    for(int i = 0; i < N; i++){
        int index = (hash + i)%N;

        if(A[index].key == ""){
            return NULL;
        }       

        if(A[index].key == key){
            return &A[index];
        } 
    }

    return NULL;
}

bool Dictionary::put(Entry e){
    int freeIndex = findFreeIndex(e.key);
    if(freeIndex == -1){
        return false;
    }
    else{
        A[freeIndex] = e;
        return true;
    }

}

bool Dictionary::remove(std::string key){
    Entry *e = get(key);
    if(!e){
        return false;
    }
    else{
        e->key = TOMBSTONE;
        e->value = (int)NULL;
        return true;
    }
}