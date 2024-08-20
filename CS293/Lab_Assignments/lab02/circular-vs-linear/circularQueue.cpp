#include <stdlib.h>
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  return true; // dummy return
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  return true; // dummy return
}

template <typename T> void DynamicQueue<T> :: grow() {
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
  return 0; // dummy return
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x) {
  return true; // dummy return
}
