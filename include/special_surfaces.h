#ifndef __SPECIAL_SURFACES_H
#define __SPECIAL_SURFACES_H

#include <sys/types.h>

extern int D_800777C0[10]; // Zapped floors

typedef enum {
  SURFACE_TYPE_NONE = -1,
  SURFACE_TYPE_WATER = 0,
  SURFACE_TYPE_SPIDER = 2,
  SURFACE_TYPE_SUPERCHARGE = 4,
  SURFACE_TYPE_INVISIBLE_WALL = 5,
  SURFACE_TYPE_PORTAL = 6,
  SURFACE_TYPE_ELECTRIC_FLOOR = 7,
} SpecialSurfaceType;

// TODO: Name arg1

/// @brief Handles the effects of the special surfaces
void ApplySpecialSurfaceEffects(int surfaceIdx, u_int arg1);

/// @brief Checks if the surface is a special surface, and returns it's type.
int GetSurfaceType(void);

#endif // !__SPECIAL_SURFACES_H
