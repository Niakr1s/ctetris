#include "rnd.h"

#include <stdlib.h>
#include <time.h>

void randomInit() { srand(time(0)); }

int randomZeroToMax(int max) {
  return (int)((double)max * rand() / (RAND_MAX + 1.0));
}
