#ifndef __COLLISION_H
#define __COLLISION_H

#include "vector.h"

/// @brief Updates the camera's occlusion group based on the specified position
/// @param pos The position to check from
/// @return Whether it found a occlusion group
int func_8004DF24(Vector3D *pos);

// Checks for collision between two points
int func_8004AE38(Vector3D *point1, Vector3D *point2);

/// @brief Looks for the floor below the specified position
/// @param pos The position to check from
/// @param max The maximum distance to check
/// @return The floor position
int func_8004D5EC(Vector3D *pos, int max);

#endif