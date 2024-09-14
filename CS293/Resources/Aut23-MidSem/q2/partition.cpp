#include <vector>

void swap(int* a, int i1, int i2){
    int temp = a[i1];
    a[i1] = a[i2];
    a[i2] = temp;
}

// implement the partition function. The argument pivot is initially the index of the pivot element, it must be updated to the index of the pivot element after partitioning.
void partition(std::vector<int> &v, int left, int right, int &pivot) {
    int n = (left + right)/2;
    int i = left, j = right;
    while(i < j){
        do{
            i++;
        } while(a[i] <= pivot);

        do{
            j--;
        }while(a[j]>pivot);

        if(i<j){
            swap(a[i],a[j]);
        }
    }
    swap(a,left,j);
    pivot = j;
}