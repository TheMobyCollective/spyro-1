#include <rand.h>

#include "common.h"
#include "rand.h"

/// @brief returns a value between [pMin, pMax] both inclusive
int RandRange(int pMin, int pMax) {
  int random = rand();
  return (random % ((pMax - pMin) + 1)) + pMin;
}

/// @brief returns a value between [pMin, pMax] both inclusive, and randomly
/// makes them negative
int RandRangeSigned(int pMin, int pMax) {
  int random = rand();
  int value = (random % ((pMax - pMin) + 1)) + pMin;

  if ((random & 1)) {
    return value;
  } else {
    return -value;
  }
}