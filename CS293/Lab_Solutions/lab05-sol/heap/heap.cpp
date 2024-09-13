#include <iostream>

/*
In this exercise, we will implement heap as discussed in the class.
We need to implement the following functions.


ONLY THIS FILE MUST BE MODIFIED FOR SUBMISSION

You may edit main.cpp for writing more test cases.
But your code must continue to work with the original main.cpp


THERE IS ONLY ONE TEST CASE ONLY FOR YOUR UNDERSTANDING.

-- You may need to generate more random tests to get your tests right
*/


#include "heap.h"

int Heap::parent(int i) {
  return (i-1) >> 1;
}

int Heap::left(int i) {
  return (i << 1) + 1;
}

int Heap::right(int i) {
  return (i << 1) + 2;
}

int Heap::max() {
  return store[0];
}

void Heap::swap(int i, int j) {
  int v = store[i];
  store[i] = store[j];
  store[j] = v;
  swap_count += 1;
}

void Heap::insert(int v) {
  auto i = size();
  append(v);
  while( i > 0 && store[parent(i)] < store[i] ) {
    swap( i, parent(i) );
    i = parent(i);
  }
}

void Heap::heapify(int i) {
  if( i >= size() ) return;
  auto l = left(i);
  auto r = right(i);
  auto largest = i;
  if( l < size() ) {
    largest = ( store[l] > store[i] ) ? l : i;
  }
  if( r < size() ) {
    largest = ( store[r] > store[largest] ) ? r : largest;
  }
  if( i == largest ) return;
  swap(i,largest);
  heapify(largest);
}


void Heap::deleteMax() {
  swap( 0, size()-1 );
  removeLast();
  heapify(0);
}

void Heap::buildHeap() {
  for( int i = size() -1; i >= 0; i-- ) {
    heapify(i);
  }
}

void Heap::heapSort() {
  buildHeap();
  while( size() > 0 ) {
    deleteMax();
  }
}


