#include <iostream>
#include <stdexcept>
#ifndef LEFTISTHEAP_H
#define LEFTISTHEAP_H
using namespace std;

// ************************************************************
// DO NOT CHANGE ANYTHING IN THIS FILE

class LeftistNode
{
public:
    int key;
    LeftistNode *left;
    LeftistNode *right;
    int npl;
    LeftistNode(int key, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np = 0);
    ~LeftistNode();
};

class LeftistHeap
{
public:
    LeftistHeap();
    ~LeftistHeap();                // Destructor
    bool isEmpty() const;          // Checks if heap is empty
    int findMin() const;           // Returns the minimum element
    void insert(int &x);           // Inserts a new element
    void deleteMin(int &minItem);  // Deletes and returns the minimum element
    void makeEmpty();              // Empties the heap
    void merge(LeftistHeap &rhs);  // Merges another heap into this one
    friend class HeapPrinter;
    LeftistNode *getRoot() const
    {
        return root;
    }

private:
    LeftistNode *root = nullptr;
    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2); // Merges two heaps
    void swapChildren(LeftistNode *t);                    // Swaps children to maintain heap properties
    void makeEmpty(LeftistNode *t);                       // Internal method to empty the heap
};

#endif // LEFTISTHEAP_H
