#ifndef __MOBY_HELPERS_H__
#define __MOBY_HELPERS_H__

#include "moby.h"

/// @brief Function that ticks a timer
/// @param pTimer The timer to update
/// @param pTimerType The type of timer, equal to the size of the type
/// @return non-0 if the timer has elapsed
int func_80037F90(void *pTimer, int pTimerType);

/// @brief Adds two angles together
/// @param p1 Angle 1
/// @param p2 Angle 2
/// @return The sum of the two angles
int func_80038074(int p1, int p2);

/// @brief Normalizes the difference between two angles to -128 to 128
/// @param p1 Angle 1
/// @param p2 Angle 2
/// @return The normalized difference
int func_800381BC(int p1, int p2);

/// @brief Plays a sound from a Moby
void func_8003851C(Moby *pMoby, int pSoundIndex, u_char *pChannel);

/// @brief Initialize a Moby
void func_8003A720(Moby *pMoby);

#endif