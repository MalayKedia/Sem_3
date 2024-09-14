#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>

#include "queue.h"
#ifdef LINEAR
#include "linearQueue.cpp"
#endif

#ifdef CIRCULAR
#include "circularQueue.cpp"
#endif

using namespace std;
using namespace std::chrono;

void do_insert_delete(DynamicQueue<int>&, int, long&, long&);

int main() {
  try {
    DynamicQueue<int> myQueue; // Queue of integers
    long num_ins = 0, num_del = 0;
    int total_num_ops = 10000;
    int points_to_plot = 100;
    for (int i = 0; i < points_to_plot; i++) {
      auto start = std::chrono::high_resolution_clock::now();
      do_insert_delete(myQueue, total_num_ops, num_ins, num_del);
      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<microseconds>(stop - start);
      cout << (num_ins + num_del) << " " << duration.count() << endl;
    }
    return 0;
  }
  catch (exception const& ex) {
    cerr << "Exception " << ex.what() << endl;
    return -1;
  }
}

void do_insert_delete(DynamicQueue<int>& q, int N, long& num_ins, long& num_del)
{
  int element;
  int modulus = 100;
  int thresh_for_del = 20;

  // Simple insertion deletion strategy: delete one element after every thresh_for_del steps
  
  srand(time(0));
  
  for (int i=0; i < N; i++) {
    if ((i > 0) && (i % thresh_for_del == 0)) {
      // Delete element from queue
      if (q.QDelete(&element)) {
	// Don't count deletions from empty queue
	num_del++;
      }
    }
    else {
      // Insert random element in queue
      element = rand() % modulus;
      q.QInsert(element);
      num_ins++;
    }
  }

  return;
}
