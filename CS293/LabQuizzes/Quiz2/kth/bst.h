#ifndef K_SMALLEST_LARGEST_H
#define K_SMALLEST_LARGEST_H

// ************************************************************
// DO NOT CHANGE ANYTHING IN THIS FILE

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
    ~Node() {
        if (left) delete left;
        if (right) delete right;
    }
};

// Function to print BST
void printBST(Node* root);

// Function to find the k-th smallest element in a BST
int findKthSmallest(Node* root, int k);

// Function to find the k-th largest element in a BST
int findKthLargest(Node* root, int k);


#endif // K_SMALLEST_LARGEST_H
