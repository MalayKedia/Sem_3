#include <bits/stdc++.h>

using namespace std;

// void merge(int* a, int* b1, int* b2, int n1, int n2){
// 	int cb1 = 0;
// 	int cb2 = 0;
// 	int ca = 0;
// 	while(cb1 < n1 && cb2 < n2){
// 		if(b1[cb1] < b2[cb2]) a[ca++] = b1[cb1++];
// 		else if(b2[cb2] < b1[cb1]) a[ca++] = b2[cb2++];
// 		else{
// 			a[ca++] = b1[ca1++];
// 			a[ca++] = b2[cb2++];
// 		}
// 		while(cb1 < n1){a[ca++] = b1[cb1++];}
// 		while(cb2 < n2){a[ca++] = b2[cb2++];}
// 	}
// }

// void mergesort(int* a, int n){
// 	int b1[n/2];
// 	int b2[n-n/2];
// 	for(int i = 0; i < n/2; i++) b1[i] = a[i];
// 	for(int i = 0; i < n-n/2; i++) b2[i] = a[i+n/2];
// 	mergesort(b1,n/2);
// 	mergesort(b2,n-n/2);
// 	merge(a,b1,b2,n/2,n-n/2);
// }

// void binsech(int* a, int n, int q){
// 	if(q < a[0]) return 0;
// 	if(q > a[n-1]) return n-1;
// 	int first = 0;
// 	int last = n;
// 	int mid = (first+last)/2;
// }

void func(int* a, int n, int& i1, int& i2){
	i1 = 0,i2 = 0;
	// if(ign == 0){i1 = 1;i2 = 1;}
	for(int i = 0; i< n; i++){
		if(a[i1] > a[i]) i1 = i;
	}
	if(i1 == 0) i2 =1;
	for(int i =0; i<n; i++){
		if(i == i1) continue;
		if(a[i2] > a[i]) i2=i;
	}

	// cout << "i1 = " << i1 << endl;
	// cout <<"i2 = " << i2 << endl;
}

int func2(int* ar, int n){
	if(n == 2){
		int cost = ar[1] + ar[0];
		return cost;
	}
	int i1 = 0,i2 = 0;
	func(ar,n,i1,i2);
	int cost = ar[i1] + ar[i2];

	int* a = new int[n-1];
	a[0] = cost;
	int j = 1;
	for(int i = 0; i < n; i++){
		if(i != i1 && i != i2){
			a[j] = ar[i];
			// cout << a[j] << endl;
			j++;
		}
	}
	int fin_cost = func2(a,n-1);
	delete[] a;
	cost = cost + fin_cost;
	return cost;
}

// The main function that returns
// the minimum cost to connect n
// ropes of lengths stored in len[0..n-1]
int minCost(int len[], int n)
{
	int cost = 0; // Initialize result

        // Write your code here

	cost = func2(len,n);
	// cout << cost << endl;

	return cost;
}


