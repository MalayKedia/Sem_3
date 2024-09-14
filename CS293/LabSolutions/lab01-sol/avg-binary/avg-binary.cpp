#include <iostream>

// Consider the binary search algorithm presented in class. We are interested
// in determining the average execution time of the binary search. To
// accomplish this, let's conduct an experiment.

// Suppose we have an array of size 1024, which contains distinct elements
// arranged in non-increasing order. We have already analyzed the running
// time when the element being searched for is not present in the array.
// Now, let's assume that we are only searching for elements that we know
// exist in the array.

// Our goal is to experimentally calculate the average number of
// iterations required to search for all 1024 elements in the array.

// In the following,
//   -- Implement BinarySearch that can handle non-increasing array
//   -- Harness BinarySearch such that we can compute avarage number
//      of iterations


int BinarySearch ( int * S , int n , int e ) {
  int first = 0, last = n, mid = (first + last) / 2;
  int iteration = 0;
  while (first < last) {
    iteration++ ;
    if (S[mid] == e) {
      std::cout << "iteration = " << iteration << "\n";
      return iteration;
    }
    if (S[mid] < e) {
      last = mid;
    } else {
      first = mid + 1;
    }
    mid = (first + last) / 2;
  }
  return iteration;
}

int main() {
  int sz = 10;
  unsigned size = 1<<sz;
  int S[size];
  for( unsigned i = 0; i < size; i++ ) {
    S[i] = size-i;
  }
  unsigned sum = 0;
  for(auto i : S) {
    unsigned result = BinarySearch ( S , size , i );
    sum = result + sum;
  }
  std::cout << "Average: " << ((float)sum)/((float)size) << "\n";
  return 0;
}
