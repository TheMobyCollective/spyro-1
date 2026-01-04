#ifndef __42CC4_H
#define __42CC4_H

#include "moby.h"

/// @brief Allocates a new Moby
/// @return A pointer to the newly allocated Moby
Moby *func_800524C4(void);

/// @brief Frees a Moby
/// @param pMoby The Moby to free
void func_80052568(Moby *pMoby);

/// @brief Updates a Moby's collision
/// @param pMoby The Moby to update
void func_800526A8(Moby *pMoby);

/// @brief Sets that a moby is a shaded moby with no collision
/// @param pMoby The Moby :)
void func_800529CC(Moby *pMoby);

enum MobyPropUpdateFlags {
  // Update the collision data based on frame data
  UPDATE_PROP_COLLISION = 1 << 0,
  // Updates which collision chain this Moby is in
  UPDATE_PROP_CHAIN = 1 << 1,
  // Updates a Moby's rotation matrix
  UPDATE_PROP_ROTMATRIX = 1 << 2,
};

/// @brief Update's various properties of a Moby
/// @param pMoby The Moby to update
/// @param pFlags The flags to update, see MobyPropUpdateFlags
void func_800529E4(Moby *pMoby, int pFlags);

/// @brief Updates a Moby's shadow
/// @param pMoby The Moby to update
void func_800533D0(Moby *pMoby);

/// @brief Creates the death sparks and poofs
void func_800530C0(Moby *pMoby, int pSomething);

#endif
