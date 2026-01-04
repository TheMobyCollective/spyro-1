#ifndef __MOBY_LISTS_H
#define __MOBY_LISTS_H

#include "moby.h"

/// @brief Populates a buffer with a list of Mobys that have to be updated
void func_80051FEC(void);

/// @brief Populates a buffer with a list of Mobys that have to be rendered
void func_800521C0(void);

/// @brief Updates the Mobys' animations
void func_800522C0(Moby **pMobyList, u_int pSpeedDiv);

#endif // __MOBY_LISTS_H
