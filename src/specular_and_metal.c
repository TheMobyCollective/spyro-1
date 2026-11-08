#include "common.h"

#include "math.h"
#include "specular_and_metal.h"

// Creates a scaled version of the camera matrix and inverts the z axis
// Used for getting the texture coordinates for the metal texture
void MetalBuildMatrix(void) {
  Vector3D
      temp; // Vector rotated by the camera matrix to build the metal matrix

  // Matrix top row: [4096, 0, 0] * Camera matrix
  VecNull(&temp);
  temp.x = 4096;
  VecRotateByCam(&temp, &temp); // [4096, 0, 0] * Camera matrix
  VecToShortVec((Vector3D16 *)g_RenderEffects.m_MetalMatrix.m[0], &temp);

  // Matrix middle row: [0, 4096, 0] * Camera matrix
  VecNull(&temp);
  temp.y = 4096;
  VecRotateByCam(&temp, &temp); // [0, 4096, 0] * Camera matrix
  VecToShortVec((Vector3D16 *)g_RenderEffects.m_MetalMatrix.m[1], &temp);

  // Matrix bottom row: [0, 0, -4096] * Camera matrix
  VecNull(&temp);
  temp.z = -4096;
  VecRotateByCam(&temp, &temp); // [0, 0, -4096] * Camera matrix
  VecToShortVec((Vector3D16 *)g_RenderEffects.m_MetalMatrix.m[2], &temp);
};

/// @brief Resets the specular lights to their defaults after they have been
/// rotated
void SpecularReset(void) {
  setXYZ(&g_RenderEffects.m_SpecularLightDirection, -2517, -2458, -2848);
  setXYZ(&g_RenderEffects.m_SpecularLightDirectionMoby, -2517, -2458, -2848);
};

/// @brief Updates the rotation of the specular light, used on menus for example
/// @param deltaTime How much time has passed since the processed last frame
void SpecularUpdate(int deltaTime) {
  g_RenderEffects.m_SpecularTime =
      (g_RenderEffects.m_SpecularTime + deltaTime) & 0xff;

  // We have to do bitshifts to match, we also have to pretend sine and cosine
  // are two separate tables otherwise the compiler inserts a random scope for
  // no reason
  setXYZ(&g_RenderEffects.m_SpecularLightDirection,
         FIXED_MUL(COSINE_8(g_RenderEffects.m_SpecularTime), 3966),
         FIXED_MUL(SINE_8(g_RenderEffects.m_SpecularTime), 6345), -1024);
}
