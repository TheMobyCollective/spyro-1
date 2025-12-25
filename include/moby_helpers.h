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

/**
 * @brief Moves a moby along a 3D path with rotation toward waypoints
 * @param pMoby The moby to move along the path
 * @param pPath Path data containing waypoint nodes
 * @param threshold Distance to consider a waypoint reached
 * @param maxSpeed Maximum movement speed per frame
 * @param bounds Collision bounds radius (0 to skip collision checks)
 * @param turnRate Maximum angle change per frame (8-bit angle units)
 * @param angleLimit If angle to waypoint exceeds this, movement stops
 * @param pVelocity Optional velocity accumulator for smoothing (NULL to skip)
 * @return 0 if still following path, (newNodeIndex + 0x100) when waypoint
 * reached
 */
int MoveMobyAlongPath(Moby *pMoby, PathData *pPath, int threshold, int maxSpeed,
                      int bounds, int turnRate, int angleLimit,
                      Vector3D *pVelocity);

/// @brief Initialize a Moby
void func_8003A720(Moby *pMoby);

// Vector interpolation curve lookup tables
// Each table contains pairs of weights (w1, w2) where w1 + w2 = 1024
// Used for smooth interpolation between two vectors along a curve

/// @brief Linear interpolation weights (1 pair for 2 steps)
extern short D_80075280[];
/// @brief Interpolation curve weights (4 pairs for 5 steps)
extern short D_8006CBA4[];
/// @brief Interpolation curve weights (6 pairs for 7 steps)
extern short D_8006CBB4[];
/// @brief Interpolation curve weights (8 pairs for 9 steps)
extern short D_8006CBCC[];

/// @brief Spawns a sparkle particle attached to a moby
/// @param pMoby The moby to attach the sparkle to
/// @param pOffset The offset vector to rotate by the moby's rotation matrix
/// @return The slot index, or -1 if no slot available
int SpawnMobySparkle(Moby *pMoby, Vector3D *pOffset);

/// @brief Persist a collected gem to checkpoint / global collected mask
void func_8003B854(int pGemValue, Moby *pMoby);

/// @brief Collect an item (gem, key, ...)
void CollectItem(Moby *pMoby);

/// @brief Create portal text
void func_8003C358(Moby *pMoby, int pIsLevelName);

/// @brief Flight level active object slots (4 slots, negative = empty)
extern int g_FlightObjectiveActiveSlots[4];

/// @brief Flight level objective counters
extern int g_FlightObjectiveCounters[4];

#endif