#include <cmath>
#include "partition.cpp"
#include "hsort.cpp"
#include "isort.cpp"
#include <vector>
using std::vector;

void quicksort(vector<int>& v, int l, int r,int& i){
  if(l < h){
    int j = l;
    partition(v,l,r,j);
    i = i + 1;
    quicksort(v,l,j,i);
    quicksort(v,j+1,r,i);
  }
}

// Implement introsort. It is like quicksort but clever enough to avoid worst case.
void introsort(vector<int>& v, int l, int r, int thresold) {
  // hsort(v,l,r);
  // return;
  int i = 0;
  if(l < h){
    int j = l;
    partition(v,l,r,j);
    i = i + 1;
    if( i < thresold){
      quicksort(v,l,j,i);
      quicksort(v,j+1,r,i);
    }else{
      hsort(v,l,j);
      hsort(v,j+1,r);
    }
  }
}

void introsort(vector<int>& v) {
  int thresold = 0; // Choose a thresold such the performance is best
  introsort(v, 0, v.size() - 1, thresold*std::log2(v.size())); // depth is logarithmic meaning worst case is nlogn
}
