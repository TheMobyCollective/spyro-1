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
  Vector3D normal;
  int offset;
} Plane;

typedef struct {
  int x, y;
} Vector2D;

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

/// @brief Converts a short vector to a vector, scaling elements up by 4
void func_80017C24(Vector3D *pOut, Vector3D16 *pIn);

/// @brief Converts a short vector to a vector
void func_80017C4C(Vector3D *pOut, Vector3D16 *pIn);

/// @brief Converts a vector to a short vector, scaling elements down by 4
void func_80017BFC(Vector3D16 *pOut, Vector3D *pVec);

/// @brief Adds two short vectors together
void func_80017C84(Vector3D16 *pOut, Vector3D16 *pIn1, Vector3D16 *pIn2);

int func_80017428(Vector3D *pIn, Vector3D *pNormal, Vector3D *pOut);

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

int func_80017D7C(Vector3D *, Vector3D *, Vector3D *, int);

#endif // !__VECTOR_H
