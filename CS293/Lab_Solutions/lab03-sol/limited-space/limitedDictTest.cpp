#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include "limitedDictionary.cpp"
using namespace std;

#define rep(i,a,b) for(int i = a; i < b; i++)

bool add_to_dict(LimitedDictionary &dict, string key, int value){
    Entry e;
    e.key = key;
    e.value = value;
    return dict.put(e);
}

void small_fifo_add_test(){
    cout<<"Running small_fifo_add_test\n";

    LimitedDictionary dict(5, FIFO);

    rep(i,0,10){
        string key(1, 'a' + i);
        add_to_dict(dict, key, i);
    }

    cout<<"Test complete\n";
}

void small_lru_add_test(){
    cout<<"Running small_lru_add_test\n";

    LimitedDictionary dict(5, LRU);

    rep(i,0,5){
        string key(1, 'a' + i);
        add_to_dict(dict, key, i);
    }

    // Test for access
    dict.get("a");

    rep(i,5,10){
        string key(1, 'a' + i);
        add_to_dict(dict, key, i);
    }

    // Test for update
    add_to_dict(dict, "f", 100);

    rep(i,10,15){
        string key(1, 'a' + i);
        add_to_dict(dict, key, i);
    }

    cout<<"Test complete\n";
}

void small_remove_test(LimitedDictionary &dict){
    rep(i,0,5){
        string key(1, 'a' + i);
        add_to_dict(dict, key, i);
    }

    dict.remove("a");

    rep(i,5,10){
        string key(1, 'a' + i);
        add_to_dict(dict, key, i);
    }

    rep(i,5,10){
        string key(1, 'a' + i);
        dict.remove(key);
    }

    rep(i,10,15){
        string key(1, 'a' + i);
        add_to_dict(dict, key, i);
    }
}

void small_fifo_remove_test(){
    cout<<"Running small_fifo_remove_test\n";

    LimitedDictionary dict(5, FIFO);

    small_remove_test(dict);

    cout<<"Test complete\n";
}

void small_lru_remove_test(){
    cout<<"Running small_lru_remove_test\n";

    LimitedDictionary dict(5, LRU);

    small_remove_test(dict);

    cout<<"Test complete\n";
}

int main(){
    
    string mode;
    cin>>mode;

    if(mode == "fifo"){
        small_fifo_add_test();
        small_fifo_remove_test();
    }
    else if(mode == "lru"){
        small_lru_add_test();
        small_lru_remove_test();
    }
    else{
        cout<<"Invalid mode\n";
    }
    
    return 0;
}