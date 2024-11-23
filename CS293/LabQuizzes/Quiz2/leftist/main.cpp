#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "heap.h"
#include <cassert>

using namespace std;

// ************************************************************
// DO NOT CHANGE ANYTHING IN THIS FILE

// This file contains functions that check your implementation of your LeftistHeap class functions
// It also contains interactiveMode function which you must go through and use for debugging

bool checkMinHeap(const LeftistNode *node)
{
    if (node == nullptr)
        return true;
    bool leftOk = (node->left == nullptr) || (node->left->key >= node->key);
    bool rightOk = (node->right == nullptr) || (node->right->key >= node->key);
    if (!leftOk || !rightOk)
    {
        cout << "Heap property violated at node with key " << node->key << endl;
    }
    return leftOk && rightOk && checkMinHeap(node->left) && checkMinHeap(node->right);
}

int getNullPathLength(const LeftistNode *node)
{
    if (node == nullptr) return -1;
    else return node->npl;
}

bool checkNPLProperty(const LeftistNode *node)
{
    if (node == nullptr)
        return true;

    int leftNPL = getNullPathLength(node->left);
    int rightNPL = getNullPathLength(node->right);
    if (leftNPL < rightNPL)
    {
        cout << "NPL violation at node with key " << node->key << endl;
        return false;
    }
    return checkNPLProperty(node->left) && checkNPLProperty(node->right) && (node->npl == min(leftNPL, rightNPL) + 1);
}

bool testLeftistHeap(const LeftistHeap &heap)
{
    const LeftistNode *root = heap.getRoot();
    if (root == nullptr)
        return true;

    bool isMinHeap = checkMinHeap(root);

    bool validNPL = checkNPLProperty(root);

    return isMinHeap && validNPL;
}

void split(const string &str, char separator, vector<string> &result)
{
    result.clear();
    size_t start = 0, end;
    while ((end = str.find(separator, start)) != string::npos)
    {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    result.push_back(str.substr(start));
}

void runTestCases()
{
    for (int i = 1; i <= 4; ++i)
    {
        string heap1File = "testcases/testcase" + to_string(i) + "_1.txt";
        string heap2File = "testcases/testcase" + to_string(i) + "_2.txt";
        string outputFile = "testcases/output" + to_string(i) + ".txt";

        ifstream infile1(heap1File);
        ifstream infile2(heap2File);

        if (!infile1 || !infile2)
        {
            cout << "Error opening test files for case " << i << endl;
            continue;
        }

        LeftistHeap heap1, heap2;
        int x;
        while (infile1 >> x)
        {
            heap1.insert(x);
            if (!testLeftistHeap(heap1))
            {
                cout << "Heap 1: Bad insertion current does not follow the rules of leftist heap" << endl;
                cout << "Test Case " << i << " failed!" << endl;
                return;
            }
        }
        while (infile2 >> x)
        {
            heap2.insert(x);
            if (!testLeftistHeap(heap2))
            {
                cout << "Heap 2: Bad insertion current state does not follow the rules of leftist heap" << endl;
                cout << "Test Case " << i << " failed!" << endl;
                return;
            }
        }

        heap1.merge(heap2);

        if (!testLeftistHeap(heap1))
        {
            cout << "Merged heap is not a valid Leftist Heap" << endl;
            cout << "Test Case " << i << " failed!" << endl;
            return;
        }

        // vector<int> expected;
        ifstream outfile(outputFile);
        while ( !heap1.isEmpty() ) {
            int minItem;
            heap1.deleteMin(minItem);
            if( outfile >> x ) {
              if( x != minItem ) {
                cout << "Mismatch in the content of the merged heap from the original heaps!"<<endl;
                cout << "Test Case " << i << " failed!" << endl;
                return;
              }
            }else{
              cout << "Too much content in the heap!" << endl;
              cout << "Test Case " << i << " failed!" << endl;
              return;
            }
            if (!testLeftistHeap(heap1))
            {
                cout << "Heap after deletion of a node is not a valid Leftist Heap" << endl;
                cout << "Test Case " << i << " failed!" << endl;
                return;
            }
        }

        cout << "Test Case " << i << " passed!" << endl;
    }
}

void interactiveMode()
{
    HeapPrinter printer;
    LeftistHeap heap1, heap2;
    string command;
    while (true)
    {
        cout << ">>> ";
        getline(cin, command);

        vector<string> args;
        split(command, ' ', args);

        if (args[0] == "LOAD")
        {
            if (!(heap1.getRoot() == nullptr) && !(heap2.getRoot() == nullptr))
            {
                cout << "Both heaps are full. Please empty one before loading." << endl;
            }
            else if (heap1.getRoot() == nullptr)
            {
                ifstream infile(args[1]);
                int x;
                int i = 0;
                while (infile >> x) {
                    heap1.insert(x);
                    i++;
                }
                cout << "Heap1 loaded with " << i << " nodes!"<< endl;
            }
            else if (heap2.getRoot() == nullptr)
            {
                ifstream infile(args[1]);
                int x;
                int i = 0;
                while (infile >> x) {
                    heap2.insert(x);
                    i++;
                }
                cout << "Heap2 loaded with " << i << " nodes!"<< endl;
            }
        }
        else if (args[0] == "MERGE")
        {
            heap1.merge(heap2);
            cout << "Heap2 merged to Heap1 and Heap2 is empty!" << endl;
        }
        else if (args[0] == "PRINT")
        {
            if (args.size() < 2)
            {
                cout << "Error: Please specify which heap to print (1 or 2)." << endl;
                continue;
            }

            int choice = stoi(args[1]);

            if (choice == 1)
                printer.printHeap(heap1);
            else if (choice == 2)
                printer.printHeap(heap2);
            else
                cout << "Invalid choice!" << endl;
        }
        else if (args[0] == "EMPTY")
        {
            if (args.size() < 2)
            {
                cout << "Error: Usage is EMPTY <heap number (1 or 2)>" << endl;
                continue;
            }

            int heapNumber = stoi(args[1]);

            if (heapNumber == 1)
            {
                heap1.makeEmpty();
                cout << "Heap1 emptied!" << endl;
            }
            else if (heapNumber == 2)
            {
                heap2.makeEmpty();
                cout << "Heap2 emptied!" << endl;
            }
            else
            {
                cout << "Invalid heap number! Use 1 or 2." << endl;
            }
        }
        else if (args[0] == "DELETEMIN")
        {
            int minItem;
            heap1.deleteMin(minItem);
            cout << "Deleted minimum element: " << minItem << endl;
        }
        else if (args[0] == "QUIT")
        {
            break;
        }
        else
        {
            cout << "Invalid command!" << endl;
        }
    }
}

void testDeleteMin()
{
    LeftistHeap heap;
    int values[] = {10, 20, 30, 5, 15};

    for (int value : values)
    {
        heap.insert(value);
    }

    int minValue;
    heap.deleteMin(minValue);
    assert(minValue == 5);
    heap.deleteMin(minValue);
    assert(minValue == 10);
    heap.deleteMin(minValue);
    assert(minValue == 15);
    heap.deleteMin(minValue);
    assert(minValue == 20);
    heap.deleteMin(minValue);
    assert(minValue == 30);

    assert(heap.isEmpty());
    std::cout << "Test Case 5 passed!" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Give mode of operation:\n 0 for testing test cases\n 1 for interactive mode\n";
        return 1;
    }

    char mode = argv[1][0];
    if (mode == '0')
    {
        runTestCases();
        testDeleteMin();
        std::cout << "All testcases passed!" << std::endl;
    }
    else if (mode == '1')
    {
        interactiveMode();
    }
    else
    {
        cout << "Invalid mode!" << endl;
    }

    return 0;
}
