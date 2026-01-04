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
void VecRotateByCam(Vector3D *pIn, Vector3D *pOut);

/// @brief Nulls a vector
void VecNull(Vector3D *pVec);

/// @brief Copies a vector
void VecCopy(Vector3D *pOut, Vector3D *pIn);

/// @brief Adds two vectors together
void VecAdd(Vector3D *pOut, Vector3D *pIn1, Vector3D *pIn2);

/// @brief Subtracts two vectors, giving you the difference
void VecSub(Vector3D *pOut, Vector3D *pIn1, Vector3D *pIn2);

/// @brief Converts a vector to a short vector
void VecToShortVec(Vector3D16 *pOut, Vector3D *pVec);

/// @brief Scales a vector to a desired length
/// @param pVec The vector, modified in place
/// @param pCurrentLength The current length
/// @param pTargetLength The desired new length
void VecScaleToLength(Vector3D *pVec, int pCurrentLength, int pTargetLength);

/// @brief Normalizes a vector, then multiplies it by a distance
void func_80017330(Vector3D *pVec, int pNormalizedDistance);

/// @brief Calculates the magnitude of a vector
/// @param pVec The vector to calculate the magnitude of
/// @param pIncludeZAxis Whether to include the Z axis in the calculation
/// @return The magnitude of the provided vector
int VecMagnitude(Vector3D *pVec, int pIncludeZAxis);

#endif // !__VECTOR_H
