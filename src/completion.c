///
/// The file just contains a function to calculate the game completion
/// percentage. I decided to make it a bit nicer for people making modifications
/// to the totals.
///

#include "variables.h"

// The totals of each, in the game
#define GEM_TOTAL 12000
#define DRAGON_TOTAL 80
#define EGG_TOTAL 12

// How much they add to the percentage
#define GEM_PERCENTAGE 50
#define DRAGON_PERCENTAGE 40
#define EGG_PERCENTAGE 10

// Calculates the game progress seen in the inventory
int CalculateCompletion(void) {
  const int gemShare = (12000 * GEM_PERCENTAGE) / GEM_TOTAL;
  const int dragonShare = (12000 * DRAGON_PERCENTAGE) / DRAGON_TOTAL;
  const int eggShare = (12000 * EGG_PERCENTAGE) / EGG_TOTAL;

  int completion = ((g_GemTotal * gemShare) + (g_DragonTotal * dragonShare) +
                    (g_EggTotal * eggShare)) /
                   12000;

  // If the gem total is over 12000, the remaining 20% is calculated
  // differently, each gem counting for 0.01%. Because loot contains 2000 gems,
  // this totals up to 120%
  if (g_GemTotal > 12000) {
    completion = ((g_GemTotal - 12000) / 100) + 100;
  }

  return completion;
}

