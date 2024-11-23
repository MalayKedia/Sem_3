#ifndef HEAP_H
#define HEAP_H

#include "leftistHeap.h"
#include <iostream>
#include <iomanip>
#include <vector>

// ************************************************************
// DO NOT CHANGE ANYTHING IN THIS FILE

class HeapPrinter
{
public:
    void printHeap(const LeftistHeap &heap) const;

private:
    void printHeap(const LeftistNode *node, const std::string &prefix, bool isLeft) const;
};

#endif
