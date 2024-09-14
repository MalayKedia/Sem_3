#include "limitedDictionary.h"
#include "dictionary.cpp"

LimitedDictionary::LimitedDictionary(int capacity, Policy policy){
    if(capacity < 1){
        throw std::runtime_error("Cannot create dictionary with capacity less than 1");
    }
    else{
        size = 0;
        this->capacity = capacity;
        this->policy = policy;

        if(policy == LRU){
            init_lru();
        }
    }
}

void LimitedDictionary::evict_fifo(){
    while(Dictionary::get(q.front()) == NULL){
        q.pop();
        if(q.empty()) break;
    }

    std::cerr<<"evicted: "<<(q.front())<<"\n";
    Dictionary::remove(q.front());
    q.pop();
}

void LimitedDictionary::insert_fifo(struct Entry e){
    q.push(e.key);

    std::cerr << "inserted: " << e.key << std::endl;
}


void LimitedDictionary::init_lru(){
    head = new ListEntry;
    tail = new ListEntry;

    head->key = "";
    head->next = tail;
    head->prev = NULL;

    tail->key = "";
    tail->next = NULL;
    tail->prev = head;
}

void LimitedDictionary::evict_lru(){
    ListEntry* temp;
    while(Dictionary::get(head->next->key) == NULL){
        temp = head->next->next;
        delete head->next;
        head->next = temp;
        temp->prev = head;

        if(head->next == tail) break;
    }

    std::cerr<<"evicted: "<<(head->next->key)<<"\n";
    Dictionary::remove(head->next->key);
    ListEntry* new_first = head->next->next;
    delete head->next;
    head->next = new_first;
    new_first->prev = head;
}

void LimitedDictionary::insert_lru(struct Entry e){
    ListEntry* curr = head->next;
    while(curr != tail){
        if(curr->key == e.key){
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            tail->prev->next = curr;
            curr->prev = tail->prev;
            tail->prev = curr;
            curr->next = tail;

            return;
        }
        curr = curr->next;
    }

    ListEntry* new_entry = new ListEntry;
    new_entry->key = e.key;
    new_entry->next = tail;
    new_entry->prev = tail->prev;
    tail->prev->next = new_entry;
    tail->prev = new_entry;

    std::cerr << "inserted: " << e.key << std::endl;
}


bool LimitedDictionary::put(struct Entry e) {

    if(size == capacity) {
        if(policy == FIFO){
            evict_fifo();
            size--;
        }
        else{
            if(Dictionary::get(e.key) == NULL){
                evict_lru();
                size--;
            }
        }
    }

    if(Dictionary::get(e.key) == NULL) size++;

    if(policy == FIFO){
        insert_fifo(e);
    }
    else{
        insert_lru(e);
    }

    return Dictionary::put(e);
}

bool LimitedDictionary::remove(std::string key){
    if(Dictionary::remove(key)){
        size--;
        return true;
    }
    else return false;
}

struct Entry* LimitedDictionary::get(std::string key){
    struct Entry* e = Dictionary::get(key);

    if(e == NULL) return NULL;
    else{
        if(policy == LRU){
            insert_lru(*e);
        }
        return e;
    }
}