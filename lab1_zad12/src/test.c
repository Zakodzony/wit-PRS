#include <stdio.h>
#include "randapi.h"
#define ITERATIONS	1000000L

int main()
{
  long  i;
  long  isum;
  float fsum;

  initRand();

  isum = 0L;
  for (i = 0 ; i < ITERATIONS ;i++) {
    isum += getRand(10);
  }
  printf( "getRand() Average %d\n", (int)(isum / ITERATIONS) );

  fsum = 0.0;
  for (i = 0 ; i < ITERATIONS ; i++) {
    fsum += getSRand();
  }

  printf( "getSRand() Average %f\n", (fsum / (float)ITERATIONS) );

  return 0;
}
