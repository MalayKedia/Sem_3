#include <stdio.h>
#include <stdlib.h>

int recurse(int m, int n) {
  if ((m <= 0) || (n <= 0)) { return 0; }
  if ((n%2) == 0) { return 1+recurse(m,n/2); }
  else { return recurse(m-1, n)+m; }
} // End recurse()

int main() {
  int m, n;
  scanf("%d", &m);
  scanf("%d", &n);
  printf("%d", recurse(m, n));
  return 0;
} // End main()
