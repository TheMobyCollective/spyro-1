#ifndef __SPECIAL_SURFACES_H
#define __SPECIAL_SURFACES_H

#include <sys/types.h>

extern int D_800777C0[10]; // Zapped floors

// TODO: Name arg1

/// @brief Handles the effects of the special surfaces
void ApplySpecialSurfaceEffects(int surfaceIdx, u_int arg1);

/// @brief Checks if the surface is a special surface, and returns it's type.
int func_80057380(void);

#endif // !__SPECIAL_SURFACES_H
