// Example usage of the bsearch 
#include <cstdlib>
#include <cstdio>

int check(const void *key, const void *elem) {
  int k = (int)key;
  int e = (int)elem;
  printf("Comparing %d with %d\n", k, e);

  if (k == e) return 0;
  if (k < e) return -1;
  return 1;
}

int main() {
  int found = (int)bsearch((const void *)10, 0, 100, 1, &check);

  printf("I found: %d\n", found);
  
  return 0;
}
