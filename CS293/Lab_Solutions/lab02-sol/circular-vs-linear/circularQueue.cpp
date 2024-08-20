#include <stdlib.h>
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  return size() == 0; // If size = 0, empty
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  return size() == N; // If size = N, full
}

template <typename T> void DynamicQueue<T> :: grow() {
  if(isFull()) {
    unsigned int old = N;
    N = nextSize();
    T* p = new T[N]; // new array of larger size
    int i = 0, j = 0, count;
    for( i=0, j=head, count=1; count <= old; i++, j=(j+1)%old, count++) {
      p[i] = A[j]; // Copying element by element into new array
    }
    head = 0; // Setting head at 0
    tail = i; // Setting tail at N + 1
    delete[] A; // Freeing up older array
    A=p;
  } else
    return;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
    if (tail == -1)
      return N; // Return N if tail is dummy value
    else
      return (tail-head+N)%N;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
    if(isFull())
      grow();

    A[tail] = x;
    tail = (tail+1) % N;

    if( tail == head ) // If N, set tail at -1 to resolve ambiguity
      tail = -1;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x)
{
    if(isEmpty())
      return false;
    *x = A[head];

    if(tail == -1) // Queue no longer has N elements, hence "normal" use of tail
      tail = head;

    head = (head+1)%N;
    return true;
}
