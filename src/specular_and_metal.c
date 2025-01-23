#include "common.h"

#include "math.h"
#include "specular_and_metal.h"

// Creates a scaled version of the camera matrix and inverts the z axis
// Used for getting the texture coordinates for the metal texture
void func_80058BD8(void) {
  Vector3D
      temp; // Vector rotated by the camera matrix to build the metal matrix

  // Matrix top row: [4096, 0, 0] * Camera matrix
  VecNull(&temp);
  temp.x = 4096;
  func_80017110(&temp, &temp); // [4096, 0, 0] * Camera matrix
  func_80017C68((Vector3D16 *)D_800770C8.m_metalmatrix.m[0], &temp);

  // Matrix middle row: [0, 4096, 0] * Camera matrix
  VecNull(&temp);
  temp.y = 4096;
  func_80017110(&temp, &temp); // [0, 4096, 0] * Camera matrix
  func_80017C68((Vector3D16 *)D_800770C8.m_metalmatrix.m[1], &temp);

  // Matrix bottom row: [0, 0, -4096] * Camera matrix
  VecNull(&temp);
  temp.z = -4096;
  func_80017110(&temp, &temp); // [0, 0, -4096] * Camera matrix
  func_80017C68((Vector3D16 *)D_800770C8.m_metalmatrix.m[2], &temp);
};

/// @brief Resets the specular lights to their defaults after they have been
/// rotated
void SpecularReset(void) {
  setXYZ(&D_800770C8.m_specularLightDirection, -2517, -2458, -2848);
  setXYZ(&D_800770C8.m_specularLightDirectionMoby, -2517, -2458, -2848);
};

/// @brief Updates the rotation of the specular light, used on menus for example
/// @param deltaTime How much time has passed since the processed last frame
void SpecularUpdate(int deltaTime) {
  D_800770C8.m_specularTime = (D_800770C8.m_specularTime + deltaTime) & 0xff;

  // We have to do bitshifts to match, we also have to pretend sine and cosine
  // are two seperate tables otherwise the compiler inserts a random scope for
  // no reason
  setXYZ(&D_800770C8.m_specularLightDirection,
         COSINE_8(D_800770C8.m_specularTime) * 1983 >> 11,
         SINE_8(D_800770C8.m_specularTime) * 6345 >> 12, -1024);
}