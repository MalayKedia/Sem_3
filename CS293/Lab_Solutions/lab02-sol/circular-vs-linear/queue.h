#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

// You have learnt about queues in CS 213.  A queue stores an ordered sequence of elements, and allows
// two operations: insert (at tail of queue) and delete (from head of queue).
//
// In this lab, we will implement a queue of a generic type using an array in two different ways.

// In the first implementation, called linearQueue, consecutive elements in the queue are stored at
// array locations with consecutive indices.  Thus, the first element in linearQueue must always be at
// the array location with the smallest index (need not be 0) compared to other elements in linearQueue.
// As an example, if linearQueue is implemented using an array A of size 10, and if there are 3
// elements in the queue, the consecutive elements could be at locations A[3], A[4], A[5].

// In the second implementation, called circularQueue, consecutive elements in the queue are stored at
// array locations that are consecutive *modulo the array size*.  Thus, the first element in circularQueue
// may not always be at the array location with the smallest index compared to other elements in
// circularQueue.
// As an example, if circularQueue is implemented using an array A of size 10, and if there are 3
// elements in the queue, the consecutive elements could be at locations A[9], A[0], A[1].
//
// When the number of elements in the queue becomes larger than the array size, you have to grow the
// array size linearly, i.e. by a fixed increment.  You must not grow the array size under any other
// condition.  If needed, you can re-arrange the list elements in your array to ensure that you
// don't grow the array size unless the queue contains more elements than the array size.  Note that this
// will incur additional time/space overhead.  So think carefully about how you would like to implement this.
//
// Finally, we will compare the overall run-time for both the above implementations for a series of
// inserts and deletes from the implemented queues.
//
// Comparison graph: x-axis is number of operations (insert/delete), y-axis run-time;
// Expect to see different graphs depending on the sequence of inserts and deletes.
//
// Make sure to document your code properly using suitable comments
//
// This file contains the declaration of a template class DynamicQueue.
// You are required to provide implementations of the member functions for linearQueue and circularQueue in
// separate files named linearQueue.cpp and circularQueue.cpp.  
//
// Your code must compile using the provided make file.  We may change the way the function main in test.cpp
// inserts and deletes elements. test.cpp is provided to help you run your tests.  
//
//
// FILES
// DO NOT MODIFY this file, submit as-is
// Write the CPP code for the member functions for the two implementations in files
// linearQueue.cpp and circularQueue.cpp
// Your code will be evaluated by compiling and running test.c, where we may change the way inserts
// and deletes are done.

// While testing, you can change the constant values given below if you want

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

template <typename T> class DynamicQueue {
private:
  T *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+CONST_GROWTH; }
public:
  DynamicQueue() // default constructor
  {
    A = new T[INIT_SIZE];
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = tail = 0;
  } 
  ~DynamicQueue(){delete[] A;}; // default destructor
  
  bool isEmpty(); // is the queue empty?
  bool isFull(); // is the queue full?
  void grow(); // grow the queue to its next size 
  unsigned int size(); // return the current number of elements in the queue
  void QInsert(T x); // insert given element at tail of the queue; grow array size as necessary
  bool QDelete(T *x); // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
};

#endif
