#include <stdlib.h>
float getSRand()
{
  float randvalue;
  randvalue = ((float)rand() / (float)RAND_MAX);
  return randvalue;
}

int getRand(int max )
{
  int randvalue;
  randvalue = (int)((float)max * rand() / (RAND_MAX+1.0));
  return randvalue;
}

