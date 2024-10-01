#include <stdio.h>
#include <stdlib.h>

int recurse(int m, int n) {
  if ((m <= 0) || (n <= 0)) { return 0; }
  if ((m%2) == 0) { return 1+recurse(m/2,n); }
  else { return recurse(m, n-1)+n; }
} // End recurse()

int main() {
  int m, n;
  scanf("%d", &m);
  scanf("%d", &n);
  printf("%d", recurse(m, n));
  return 0;
} // End main()
