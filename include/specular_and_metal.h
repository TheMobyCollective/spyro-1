#ifndef __SPECULAR_AND_METAL_H
#define __SPECULAR_AND_METAL_H

#include "common.h"
#include "matrix.h"
#include "vector.h"

typedef struct {
  /// @brief The direction of the light that shines on specular surfaces
  Vector3D m_SpecularLightDirection;

  /// @brief The direction of the light that shines on specular surfaces (For
  /// shiny mobys)
  Vector3D m_SpecularLightDirectionMoby;

  /// @brief The matrix used to rotate the vertex normals of metal surfaces
  SHORTMATRIX m_MetalMatrix;

  /// @brief The timer used to animate the specular light on menus
  int m_SpecularTime;
} SpecularAndMetal;

// Specular and metal variables
extern SpecularAndMetal g_RenderEffects;

extern Tiledef D_800756F0; // Metal texture

/// @brief Resets the specular light direction
void SpecularReset(void);

/// @brief Updates the specular light direction
void SpecularUpdate(int deltaTime);

void MetalBuildMatrix(void);

#endif // !__SPECULAR_AND_METAL_H
