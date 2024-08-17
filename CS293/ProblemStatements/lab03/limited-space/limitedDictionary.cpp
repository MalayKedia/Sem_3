#include "limitedDictionary.h"
#include "dictionary.cpp"

LimitedDictionary::LimitedDictionary(int capacity, Policy policy){
    if(capacity < 1){
        throw std::runtime_error("Cannot create dictionary with capacity less than 1");
    }
    else{
        // Initialize the Limited Dictionary

        // YOUR CODE HERE
    }
}

void LimitedDictionary::evict_fifo(){
    // Implement the FIFO eviction scheme


    // YOUR CODE HERE


    // Make sure to flush the evicted key into std::cerr for testing
    // Modify this part
    std::string evicted_key = "";
    std::cerr << "evicted: " << evicted_key << std::endl;
}

void LimitedDictionary::insert_fifo(struct Entry e){
    // Implement the FIFO insertion scheme


    // YOUR CODE HERE


    // Make sure to flush the inserted key into std::cerr for testing
    // Don't delete this line
    std::cerr << "inserted: " << e.key << std::endl;
}


void LimitedDictionary::init_lru(){
    // Initialize variables for LRU scheme


    // YOUR CODE HERE
}

void LimitedDictionary::evict_lru(){
    // Implement the LRU eviction scheme


    // YOUR CODE HERE


    // Make sure to flush the evicted key into std::cerr for testing
    // Modify this part
    std::string evicted_key = "";
    std::cerr << "evicted: " << evicted_key << std::endl;
}

void LimitedDictionary::insert_lru(struct Entry e){
    // Implement the LRU insertion scheme


    // YOUR CODE HERE


    // Make sure to flush the inserted key into std::cerr for testing
    // Don't delete this line
    std::cerr << "inserted: " << e.key << std::endl;
}


bool LimitedDictionary::put(struct Entry e) {
    // Overload the put function from original Dictionary


    // YOUR CODE HERE
    return 0;
}

bool LimitedDictionary::remove(std::string key){
    // Overload the remove function from original Dictionary


    // YOUR CODE HERE
    return 0;
}

struct Entry* LimitedDictionary::get(std::string key){
    // Overload the get function from original Dictionary

    
    // YOUR CODE HERE
    return NULL;
}
