#ifndef __MATH_H
#define __MATH_H

#include <sys/types.h>

#include <libgte.h>
#include <vector.h>

#define FIXED_MUL(x, y) (((x) * (y)) >> 12)

// This is horrible (since they intersect)
// but that's the only way it will match in some files
extern short D_8006CBF8[256];
extern short D_8006CC78[256];

#define SINE_8(x) D_8006CBF8[(x)]
#define COSINE_8(x) D_8006CC78[(x)]

// @brief VRAM size per cutscene
extern int D_8006EE5C[4];

extern short D_8006F3A0[8][2]; // Dragon fragments offset

// TODO: When the we've used it in more places, check if maybe we have to
// change the type to char
// (it matches as char in func_8003838C atleast, then it doesn't need casting)

/// @brief Also an atan2 function, but less precise
int Atan2Fast(int pY, int pX);

/// @brief Atan2 function
/// @param pY The Y coordinate
/// @param pX The X coordinate
/// @param output16Bit Whether to output a 16-bit value rather than a 8-bit one
int Atan2(int pY, int pX, int output16Bit);

/// @brief Get the sine of an angle
/// @param angle
/// @return The sine of the specified angle
int Sin(int pAngle);

/// @brief Get the cosine of an angle
/// @param angle
/// @return The cosine of the specified angle
int Cos(int pAngle);

/// @brief Uses Newton's method to find a more precise value
/// @param pIn The input vector
/// @param pInitialGuess The initial guess for the root
/// @param pIncludeZAxis Whether to include the Z axis in the calculation
/// @return A more precise value for the magnitude of the vector
int VecRefineMagnitude(Vector3D *pIn, int pInitialGuess, int pIncludeZAxis);

/// @brief Turns a 8bit rotation vector into a matrix
/// @param pRotation The rotation vector
/// @param pOut The output matrix
/// @param pIn Optional input, output is multiplied by this matrix
void RotVec8ToMatrix(Vector3D8 *pRotation, MATRIX *pOut, MATRIX *pIn);

/// @brief Rotates a vector by a matrix
/// @param pMatrix The matrix
/// @param pVector The vector
/// @param pOut The output vector
void VecRotateByMatrix(MATRIX *pMatrix, Vector3D *pVector, Vector3D *pOut);

/// @brief Shift all vector elements left
void VecShiftLeft(Vector3D *pVec, int pNumBits);

/// @brief Shift all vector elements right
void VecShiftRight(Vector3D *pVec, int pNumBits);

/// @brief Use the GTE to multiply each element by a fixed value
void VecMult(Vector3D *pOut, Vector3D *pIn, int pVal);

/// @brief Subtracts two 12 bit angles
/// @param pAngle1
/// @param pAngle2
/// @return 12 bit value
int func_80017928(int pAngle1, int pAngle2);

/// @brief Subtracts two angles
/// @param pAngle1
/// @param pAngle2
/// @return 8 bit value
int func_80017908(int pAngle1, int pAngle2);

/// @brief Steps an angle towards a target angle
/// @param pTargetAngle The target angle
/// @param pAngle The starting angle
/// @param pSpeed The step speed
/// @param pMinStep The minimum step size, snaps to target if within this range
/// @return The new angle
int func_800179F0(int pTargetAngle, int pAngle, int pSpeed, int pMinStep);

/// @brief Returns the octagonal distance between two angles
/// This function is a lot faster than using square roots
int OctDistance(Vector3D *pPos1, Vector3D *pPos2);

/// @brief Projects a vector onto the screen
void func_80017AA4(Vector3D *, Vector3D *);

/// @brief Unpacks a collision triangle
void ColTriUnpack(int pIndex, Vector3D *pOut);

#endif // !__MATH_H