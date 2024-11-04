#include <stdio.h>

int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
int n = 12;
int product = 1;

int main() {
	int i = 0;
	while(i < n) {
		product *= a[i];
		i++;
	}
	printf("%x\n",product);
}

