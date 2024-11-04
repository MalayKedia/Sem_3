#include <stdio.h>
int f(int x);
int h(int x);
int g(int x);

int f(int x) {
	if (x > 0) return g( f(x-1)+h(x-2) );
	else return 1;
} 

int h(int x) {
	if (x > 0) return g( f(x-2)+h(x-2) );
	else return 1;
} 

// Note: We will use a slightly DIFFERENT g() during the actual exam, and a further different one during evaluation
int g(int n) { 
	return n;
}

// Note: We will use a slightly DIFFERENT main() during the actual exam, and a further different one during evaluation
int main() {
	int a=5; // Use a global data variable for this in MIPS32 code
	printf("%d\n",f(a));
}

