#include "heap.h"

// ************************************************************
// DO NOT CHANGE ANYTHING IN THIS FILE

void HeapPrinter::printHeap(const LeftistHeap &heap) const
{
    printHeap(heap.getRoot(), "", true);
}

// This function prints the HEAP using ASCII characters using the
// format:
//
//   root
//       |-- left child
//       \-- right child
//
// where the left and right heaps are printed recursively in
// the same format.
//
// You may use this for debugging purposes.
//
void HeapPrinter::printHeap(const LeftistNode *node, const std::string &prefix, bool isLeft) const
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|-- " : "\\-- ");
        std::cout << node->key << std::endl;

        std::string childPrefix = prefix + (isLeft ? "|   " : "    ");

        printHeap(node->left, childPrefix, true);
        printHeap(node->right, childPrefix, false);
    }
}