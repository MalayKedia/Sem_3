
/*
Whenever tail reaches the end, we check if the head is at the start or not.
If not, it means that there is still some space left and the Question requires us to NOT increase array size unless
the number of elements > array size
Hence in such case, we'll linearly shift the elements back so that head becomes 0.
This can be more expensive in terms of time but we don't waste extra space unneccessarily.
*/

#include <stdlib.h>
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
    return size() == 0;
}

template <typename T> bool DynamicQueue<T> :: isFull()
{
  // return tail == N;
  return size() == N;
}

template <typename T> void DynamicQueue<T> :: grow() {
  if(isFull()) {
    unsigned int old_size = N;
    N = nextSize();
    T* new_queue = new T[N];

    for(int i=0;i<old_size;i++) {
      new_queue[i] = A[i];
    }
    delete[] A;
    A = new_queue;
  } else
    return;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
    return tail - head;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
    if(tail == N)
    {
      if(head > 0)
      {
        for(int i=head; i<tail; i++)
          A[i-head]=A[i];
        tail-=head;
        head=0;
      }
      else
        grow();
    }

    A[tail] = x;
    tail ++;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x) {
    if(isEmpty())
      return false;
    *x = A[head];
    head ++;
    return true;
}
