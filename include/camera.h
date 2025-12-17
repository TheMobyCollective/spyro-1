#ifndef __CAMERA_H
#define __CAMERA_H

#include <matrix.h>
#include <sys/types.h>
#include <vector.h>

typedef struct {
  Vector3D m_SpyroPosition;
  Vector3D m_SpyroRotation;
  Vector3D m_CameraPosition;
  Vector3D m_CameraRotation;
  int unk_0x30; // Usually 1
  int unk_0x34; // Usually 0x2000
} LevelFlyInParameters;

// SKELETON: Weird shit array of three parameters that
// don't match any levels in the final game
extern LevelFlyInParameters D_8006EB24[3];

extern LevelFlyInParameters D_8006EBCC; // Used as temporary storage

typedef struct {
  SphericalCoordinates m_Coords;
  SphericalCoordinates m_Offset;
} SphericalCoordsOffset;

extern SphericalCoordsOffset D_8006CA84; // Dunno

typedef struct {
  SHORTMATRIX m_ProjectionMatrix; // Scaled for the aspect ratio
  SHORTMATRIX m_ViewMatrix; // Represents the camera's position and orientation
  Vector3D m_Position;      // Camera's position
  Vector3D m_DestinationPosition;
  int unk_0x40[3];       // Probably padding
  Vector3D16 m_Rotation; // Camera's rotation
  short unk_0x52;        // Padding
  int m_OcclusionGroup;  // Occlusion group
  u_int m_State;         // Camera state
  int unk_0x5C;          // Padding
  SphericalCoordsOffset m_LastSimulation;
  SphericalCoordsOffset m_Sphere;
  SphericalCoordsOffset m_Simulation;
  SphericalCoordsOffset unk_0xA8;
  int unk_0xC0; // Related to states
  int unk_0xC4; // Accumulator/counter used in camera smoothing/collision
  int m_SpyroOffCenterFrames;
  int unk_0xCC; // Flag: set to 1 when camera forced to destination
  Vector3D *m_Focus;
  int m_FocusRotation;
  SphericalCoordsOffset *m_SphericalPreset;
  int unk_0xDC;
  int unk_0xE0;
  int unk_0xE4;
  int unk_0xE8; // Result of func_80033F08: whether azimuth changed
  LevelFlyInParameters *unk_0xEC;
  int m_OnMovingPlatform;
  int unk_0xF4;
  int unk_0xF8;
  int unk_0xFC;
  Vector3D unk_0x100;
  int unk_0x10C;
} Camera;

extern int D_80075844; // New occlusion group

// Unused variables for screenshake effect
extern int D_8007590C;
extern int D_800756DC;
extern int D_80075848;

extern int D_80075914; // Active (2) / passive (82) camera

extern Camera g_Camera;

// static_assert(sizeof(Camera) == 0x110);

/// @brief Creates the Camera's view and projection matrices
void CameraUpdateMatrices(void);

/// @brief Something for updating spherical coordinates
int func_80033F08(Vector3D *pVec);

/// @brief: Converts the camera's spherical coordinates to cartesian coordinates
void func_80034204(Vector3D *pOut);

/// @brief Updates the camera's rotation based on it's spherical coordinates
void func_800342F8(void);

/// @brief Some camera reset stuff
void func_80034358(void);

/// @brief Sets the level fly-in parameters
/// @param param New level fly-in parameters
void func_80037714(LevelFlyInParameters *param);

/// @brief Update function used during the level transition
void func_80037A20(void);

/// @brief Camera update function
void func_80037BD4(void);

#endif // !__CAMERA_H