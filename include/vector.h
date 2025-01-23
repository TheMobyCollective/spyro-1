#ifndef __VECTOR_H
#define __VECTOR_H

#include <sys/types.h>

typedef struct {
  int x, y, z;
} Vector3D;

typedef struct {
  u_char x, y, z;
} Vector3D8;

typedef struct {
  short x, y, z;
} Vector3D16;

typedef struct {
  int azimuth, elevation, radius;
} SphericalCoordinates;

#define setXYZ(a, _x, _y, _z) (a)->x = _x, (a)->y = _y, (a)->z = _z

/// @brief Rotates a vector by the camera matrix
void func_80017110(Vector3D *pIn, Vector3D *pOut);

/// @brief Nulls a vector
void VecNull(Vector3D *pVec);

/// @brief Copies a vector
void VecCopy(Vector3D *pOut, Vector3D *pIn);

/// @brief Adds two vectors together
void VecAdd(Vector3D *pOut, Vector3D *pIn1, Vector3D *pIn2);

/// @brief Subtracts two vectors, giving you the difference
void VecSub(Vector3D *pOut, Vector3D *pIn1, Vector3D *pIn2);

/// @brief Converts a vector to a short vector
void func_80017C68(Vector3D16 *pOut, Vector3D *pVec);

/// @brief Interpolates a vector to 0, I'm not 100% certain
void func_800175B8(Vector3D *pVec, int pFactor, int pDelta);

/// @brief Normalizes a vector, then multiplies it by a distance
void func_80017330(Vector3D *pVec, int pNormalizedDistance);

/// @brief Turns a difference vector into a distance
/// @param pVec The difference vector
/// @param pZIncluded Whether or not to include the Z axis in the distance
/// calculation
/// @return The distance of the difference vector
int func_800171FC(Vector3D *pVec, int pZIncluded);

#endif // !__VECTOR_H