#include "dictionary.h"
#include <queue>

#ifndef LIMITEDDICTIONARY_H
#define LIMITEDDICTIONARY_H

enum Policy {FIFO, LRU};

struct ListEntry{
    std::string key;
    ListEntry* next;
    ListEntry* prev;
};

class LimitedDictionary : public Dictionary {
  private:
    int size;
    int capacity;

    Policy policy;

    // FIFO
    std::queue<std::string> q;
    
    void evict_fifo();
    void insert_fifo(struct Entry e);

    // LRU
    ListEntry* head;
    ListEntry* tail;

    void init_lru();
    void evict_lru();
    void insert_lru(struct Entry e);
     
  public:
    LimitedDictionary(int capacity, Policy policy);

    bool put(struct Entry e);
    bool remove(std::string key);
    struct Entry* get(std::string key);
};

#endif