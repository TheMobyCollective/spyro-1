#include "common.h"

#include "environment.h"

/// @brief Handles the effects of the special surfaces
INCLUDE_ASM("asm/nonmatchings/special_surfaces", func_80056F64);

/// @brief Checks if the surface is a special surface, and returns it's type.
int func_80057380(void) {
  int idx = D_80075718 & 63;

  if (idx != 63) // If the flag is 63, it means we're not touching a surface
    return g_Environment.m_SurfaceData[idx]->m_Type;

  return -1;
}