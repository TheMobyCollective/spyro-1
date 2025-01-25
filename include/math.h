#ifndef __MATH_H
#define __MATH_H

#include <sys/types.h>

#include <libgte.h>
#include <vector.h>

#define FIXED_MUL(x, y) (((x) * (y)) >> 12)

// This is horrible, but that's the only way it will match in some files
extern short D_8006CBF8[256];
extern short D_8006CC78[256];

#define SINE_8(x) D_8006CBF8[(x)]
#define COSINE_8(x) D_8006CC78[(x)]

/// @brief Atan2 function
/// @param pY The Y coordinate
/// @param pX The X coordinate
/// @param output16Bit Whether to output a 16-bit value rather than a 8-bit one
int func_80016AB4(int pY, int pX, int output16Bit);

/// @brief Get the sine of an angle
/// @param angle
/// @return The sine of the specified angle
int Sin(int pAngle);

/// @brief Get the cosine of an angle
/// @param angle
/// @return The cosine of the specified angle
int Cos(int pAngle);

/// @brief Turns a 8bit rotation vector into a matrix
/// @param pRotation The rotation vector
/// @param pOut The output matrix
/// @param pIn Optional input, output is multiplied by this matrix
void func_80016D2C(Vector3D8 *pRotation, MATRIX *pOut, MATRIX *pIn);

/// @brief Rotates a vector by a matrix
/// @param pMatrix The matrix
/// @param pVector The vector
/// @param pOut The output vector
void func_80017048(MATRIX *pMatrix, Vector3D *pVector, Vector3D *pOut);

/// @brief Subtracts two angles
/// @param pAngle1
/// @param pAngle2
/// @return 8 bit value
int func_80017908(int pAngle1, int pAngle2);

/// @brief Returns the octangenal distance between two angles
/// This function is a lot faster than using square roots
int OctDistance(Vector3D *pPos1, Vector3D *pPos2);

/// @brief Projects a vector onto the screen
void func_80017AA4(Vector3D *, Vector3D *);

/// @brief Unpacks a collision triangle
void ColTriUnpack(int pIndex, Vector3D *pOut);

#endif // !__MATH_H