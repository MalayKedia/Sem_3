#include "leftistHeap.h"

// Initialize an instance of LeftistNode
LeftistNode::LeftistNode(int key, LeftistNode *lt, LeftistNode *rt, int np)
{
    // Write your code below this line ----------------------------------------------------------------
}

LeftistNode::~LeftistNode()
{
    // Write your code below this line ----------------------------------------------------------------
}

// Implement a default constructor for a empty LeftistHeap
LeftistHeap::LeftistHeap()
{
    // Write your code below this line ----------------------------------------------------------------
}

// Implement a destructor for LeftistHeap
// All nodes should be properly deleted to avoid memory leaks
LeftistHeap::~LeftistHeap()
{
    // Write your code below this line ----------------------------------------------------------------
}

void LeftistHeap::merge(LeftistHeap &rhs)
{
}

// Implement the merge function that takes roots of two LeftistHeaps and merges them into one returns the root of merged heap
LeftistNode *LeftistHeap::merge(LeftistNode *h1, LeftistNode *h2)
{
    // Write your code below this line ----------------------------------------------------------------
}

// Implement a function to swap the children of a node (Exchange the left and right children of the provided node)
// Ensure the left child becomes the right child and vice versa.
void LeftistHeap::swapChildren(LeftistNode *t)
{
    // Write your code below this line ----------------------------------------------------------------
}

// Implement a insertion function to insert a new key into the heap.
void LeftistHeap::insert(int &x)
{
    // Write your code below this line ----------------------------------------------------------------
}

// Implement this function to retrieve the smallest key in the heap.
int LeftistHeap::findMin() const
{
    // Write your code below this line ----------------------------------------------------------------
}

// Delete minimum function: Remove and return the smallest key from the heap.
void LeftistHeap::deleteMin(int &minItem)
{
    // Write your code below this line ----------------------------------------------------------------
}

// Check if the heap is empty
bool LeftistHeap::isEmpty() const
{
    // Write your code below this line ----------------------------------------------------------------
}

void LeftistHeap::makeEmpty()
{
}

// Implement a helper function for makeEmpty that delete all nodes starting from the given node.
void LeftistHeap::makeEmpty(LeftistNode *t)
{
    // Write your code below this line ----------------------------------------------------------------
}
