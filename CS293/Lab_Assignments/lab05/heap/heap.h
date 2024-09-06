#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <bits/stdc++.h>

using namespace std;

class Heap
{
public:
  // global root for the entire tree
  std::vector<int> store;
  unsigned sz = 0;
  int swap_count = 0;
  // Constructor
  Heap() {};

  // store utilities
  int  size();        // returns the size of store
  void reset();       // clears the store
  void removeLast();  // removes the last element in store
  void append(int k); // appends key in store
  void printStore(unsigned len);

  // heap Navigation
  int parent(int);
  int left(int);
  int right(int);

  // Heap interface
  void swap(int i, int j);
  int max();          // read max
  void insert(int k); // insert key in heap
  void heapify(int i);// heapify a node
  void deleteMax();   // deletes max
  void buildHeap();   // builds heap
  void heapSort();    // sorts conentens of heap and does not physically delete
                      // the content

  void print(int i=0, const string& prefix="", bool isLeft=false);

};

inline int Heap::size() {
  return sz;
}

inline void Heap::reset() {
  store.clear();
  sz = 0;
}

inline void Heap::removeLast() {
  sz = sz - 1;
}

inline void Heap::append(int k) {
  if( sz == store.size() )
    store.push_back(k); // expand if more storage is needed!
  else
    store[sz] = k;
  sz = sz + 1;
}

inline void Heap::printStore(unsigned len)
{
  len = len > store.size()? store.size() : len;
  for( unsigned i = 0; i < len; i++ ) {
    cout << store[i] << " ";
  }
  cout << endl;
}

inline void Heap::print(int i, const string& prefix, bool isLeft)
{
    if( size() > i && i >= 0 )
    {
        cout << prefix << (isLeft ? "|--" : "|__" ) << store[i] << endl;
        // enter the next tree level - left and right branch
        print( left(i), prefix + (isLeft ? "│   " : "    "), true);
        print( right(i), prefix + (isLeft ? "│   " : "    "), false);
    }
}

