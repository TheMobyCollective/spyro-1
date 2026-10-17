#ifndef __42CC4_H
#define __42CC4_H

#include "moby.h"

/// @brief Allocates a new Moby
/// @return A pointer to the newly allocated Moby
Moby *MobyAlloc(void);

/// @brief Frees a Moby
/// @param pMoby The Moby to free
void MobyFree(Moby *pMoby);

/// @brief Updates a Moby's collision
/// @param pMoby The Moby to update
void MobyUpdateCollision(Moby *pMoby);

/// @brief Sets that a moby is a shaded moby with no collision
/// @param pMoby The Moby :)
void MobySetShaded(Moby *pMoby);

/// @brief Gets the position of a vertex in a Moby's animated mesh
/// @param pMoby Moby :)
/// @param pVertexIdx Index of the vertex
/// @param pOutVector Output vector
void MobyGetAnimatedVertex(Moby *pMoby, int pVertexIdx, Vector3D *pOutVector);

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
void MobyUpdateShadow(Moby *pMoby);

/// @brief Creates the death sparks and poofs
/// @param pMoby The Moby :)
/// @param pSize The size of the smoke particle
void func_800530C0(Moby *pMoby, int pSize);

#endif
