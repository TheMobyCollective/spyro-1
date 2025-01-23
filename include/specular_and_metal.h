#ifndef __SPECULAR_AND_METAL_H
#define __SPECULAR_AND_METAL_H

#include "matrix.h"
#include "vector.h"

typedef struct {
  /// @brief The direction of the light that shines on specular surfaces
  Vector3D m_specularLightDirection;

  /// @brief The direction of the light that shines on specular surfaces (For
  /// shiny mobys)
  Vector3D m_specularLightDirectionMoby;

  /// @brief The matrix used to rotate the vertex normals of metal surfaces
  SHORTMATRIX m_metalmatrix;

  /// @brief The timer used to animate the specular light on menus
  int m_specularTime;
} SpecularAndMetal;

// Specular and metal variables
extern SpecularAndMetal D_800770C8;

/// @brief Resets the specular light direction
void SpecularReset(void);

/// @brief Updates the specular light direction
void SpecularUpdate(int deltaTime);

#endif // !__SPECULAR_AND_METAL_H