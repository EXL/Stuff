#include <stdio.h>

int main (int argc, char *argv[])
{
  unsigned char *a;
  unsigned long b;
  unsigned int c;
  long d;
  int e;
  printf("%u, %u, %u, %u, %u, %u, %u\n", sizeof(a), sizeof(b), sizeof(c), sizeof(d), sizeof(e), (sizeof(void *)<<3), (sizeof(void *)));
  return 0;
}
