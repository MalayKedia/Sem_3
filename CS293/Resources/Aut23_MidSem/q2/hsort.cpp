#include <vector>
using std::vector;

class heap{
    public:
    int sz;
    int* a;
};

void swap(vector<int>& a, int i1, int i2){
    int temp = a[i1];
    a[i1] = a[i2];
    a[i2] = temp;
}

int p(int i){
    if(i > 0){
        return (i-1)/2;
    } else{
        return -1;
    }
}

int lef(int i,int n){
    if(2*i + 1 < n){
        return (2*i+1);
    }else{
        return -1;
    }
}

int rig(int i,int n){
    if(2*i + 2 < n){
        return (2*i+2);
    }else{
        return -1;
    }
}

void heapify(vector<int>& v, int i, int n,int left){
    int im = i;
    int l = left + lef(i - left,n);
    int r = left + rig(i-left,n);
    if( l == -1 && r == -1) return;
    if(l != -1 && r != -1){
        if(v[l] < v[r]) im = r;
        else im = l;

        if(v[im] < v[i]) im = i;

    } else if (r == -1){
        if(v[l] > v[i]) im = l;
    }

    if(im == i) return;
    swap(v,im,i);
    heapify(v,im,n,left);
}
void build(vector<int>& v, int n,int left){
    int i = n -1;
    while( i >= 0){
        heapify(v,i,n,left);
        i--;
    }
}

void deletemax(vector<int>& v,int& n,int left){
swap(v,left,n-1);
n = n -1;
heapify(v,left,n,left);
}

// implement heapsort - perhaps using a heap class
void hsort(vector<int>& v, int left, int right) {
int n = right - left + 1;
build(v,n,left);
while(n > 0){
    deletemax(v,n,left);
}
}
