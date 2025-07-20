#ifndef __RENDERERS_H
#define __RENDERERS_H

#include "matrix.h"

// Various renderers

// func_80022A2C

// r_particles:
void func_800573C8(void);

// r_cyclorama:

/// @brief: Renders the cyclorama / sky
void func_8004EBA8(int pOcclusionGroup, SHORTMATRIX *pViewMatrix,
                   SHORTMATRIX *pProjectionMatrix);

// r_moby:

/// @brief: Initializes the moby renderer, performs culling
void func_8001F158(void);

/// @brief: Renders regular mobys
void func_8001F798(void);

/// @brief: Initializes the shiny moby renderer, performs culling
void func_800208FC(void);

/// @brief: Renders shaded mobys, no queueing needed
void func_80022A2C(void);

// r_pete:

/// @brief: Renders Spyro's model
void func_80023AC4(void);

// r_environment:

/// @brief: Renders the world
void func_800258F0(int pOcclusionGroup);

// r_flame:

/// @brief: Renders Spyro's flame
void func_80058D64(void);

// r_shadows:

/// @brief: Renders Spyro's shadow
void func_80059A48(void);

/// @brief: Renders the shadows of mobys
void func_80059F8C(void);

#endif