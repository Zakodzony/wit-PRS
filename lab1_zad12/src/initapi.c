#include <stdlib.h>
#include <time.h>

void initRand()
{
  time_t seed;
  seed = time(NULL);
  srand( seed );
  return;
}

