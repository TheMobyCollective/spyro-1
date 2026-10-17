#ifndef __COLLISION_H
#define __COLLISION_H

#include "moby.h"
#include "vector.h"

/// @brief Updates the camera's occlusion group based on the specified position
/// @param pos The position to check from
/// @return Whether it found a occlusion group
int func_8004DF24(Vector3D *pos);

// Checks for collision between two points
int ColTraceRay(Vector3D *point1, Vector3D *point2);

/// @brief Hitbox collision check
/// @param pPos Center
/// @param pSize The size of the box
/// @param pDamageOutput Damage to apply to Spyro if he's inside
/// @return Whether the hitbox was hit by Spyro
int ColSpyroInHitbox(Vector3D *pPos, int pSize, int pDamageOutput);

/// @brief Sphere collision check
/// @param pPos The center position of the sphere
/// @param pRadiusMobys Our radius VS mobys
/// @param pRadiusTerrain Our radius VS terrain
int ColSphere(Vector3D *pPos, int pRadiusMobys, int pRadiusTerrain);

/// @brief Check for Moby collision at the specified position
/// @param pPos The position to check
/// @param pRadius The collision radius
/// @param pReceivingDamage Pointer to store damage received (can be nullptr)
/// @param pApplyingDamage The damage to apply
/// @param pIgnoreMoby Moby to ignore during collision check
/// @param arg5 Bitmask of some kind
int ColMoby(Vector3D *pPos, int pRadius, int *pReceivingDamage,
            int pApplyingDamage, Moby *pIgnoreMoby, int arg5);

/// @brief Looks for the floor below the specified position
/// @param pos The position to check from
/// @param max The maximum distance to check
/// @return The floor position
int ColFindFloor(Vector3D *pos, int max);

#endif
