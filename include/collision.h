#ifndef __COLLISION_H
#define __COLLISION_H

#include "moby.h"
#include "vector.h"

/// @brief Updates the camera's occlusion group based on the specified position
/// @param pos The position to check from
/// @return Whether it found a occlusion group
int func_8004DF24(Vector3D *pos);

// Checks for collision between two points
int func_8004AE38(Vector3D *point1, Vector3D *point2);

/// @brief Sphere collision check
/// @param pPos The center position of the sphere
/// @param pRadiusMobys Our radius VS mobys
/// @param pRadiusTerrain Our radius VS terrain
int func_8004BE4C(Vector3D *pPos, int pRadiusMobys, int pRadiusTerrain);

/// @brief Check for Moby collision at the specified position
/// @param pPos The position to check
/// @param pRadius The collision radius
/// @param pReceivingDamage Pointer to store damage received (can be nullptr)
/// @param pApplyingDamage The damage to apply
/// @param pIgnoreMoby Moby to ignore during collision check
/// @param arg5 Bitmask of some kind
int func_8004E3C8(Vector3D *pPos, int pRadius, int *pReceivingDamage,
                  int pApplyingDamage, Moby *pIgnoreMoby, int arg5);

/// @brief Looks for the floor below the specified position
/// @param pos The position to check from
/// @param max The maximum distance to check
/// @return The floor position
int func_8004D5EC(Vector3D *pos, int max);

#endif
