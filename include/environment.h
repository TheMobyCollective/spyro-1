#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <sys/types.h>

typedef struct {
  u_char m_Type;
  int m_Param1, m_Param2;
} SpecialSurface;

typedef struct {
  int m_TriangleCount;
  int m_FlagCount;
  u_short *m_BlockTree;
  u_short *m_Blocks;
  void *m_Triangles;
  u_char *m_TriangleOcclusionAssignment;
  u_char *m_Flags;
} TerrainCollision;

// Might possibly be part of Environment, but it appears above it
// And in assembly, g_Environment is usally used as the reference point
// and it doesn't seem sensible to offset it everytime, especially in a function
// uses both structs
typedef struct {
  // Animated textures are textures that take on the UVs of another texture
  // For example, Supercharge ramps
  int m_TextureAnimationCount;
  void *m_TextureAnimations;

  // Scrolling textures are textures who's UVs scroll by a certain amount every
  // frame For example, waterfalls
  int m_ScrollingTextureCount;
  void *m_ScrollingTextures;

  // These are animations on the environment geometry, like the moving platforms
  // Or torch-lit floors and walls
  int m_LowPolyAnimationCount;
  void *m_LowPolyAnimations;
  int m_LowColorAnimationCount;
  void *m_LowColorAnimations;
  int m_HighPolyAnimationCount;
  void *m_HighPolyAnimations;
  int m_HighColorAnimationCount;
  void *m_HighColorAnimations;

  // These are unused, they aren't referenced anywhere in the code
  int section7Count;
  void *section7;
  int section8Count;
  void *section8;

  // These are animations on the environment's collision, similar to above
  int m_CollisionAnimationCount;
  void *m_CollisionAnimations;
} EnvironmentAnimations;

extern EnvironmentAnimations D_80078560;

typedef struct {
  void *m_SectorPointer; // TODO: Type
  int m_SectorCount;
  void *m_OcclusionGroups; // TODO: Type
  int m_OcclusionGroupCount;
  SpecialSurface **m_SurfaceData;
  int m_SurfaceCount;
  void *m_LQTexturePointer; // TODO: Type
  void *m_HQTexturePointer; // TODO: Type
  int m_TextureCount;
  int m_LodDistance;
  int m_CullingDistance;
  TerrainCollision *m_TerrainCollision;
} Environment;

/// @brief: Create the environment
void func_8002B9CC(void);

/// @brief Initializes environment animations
void func_8002B4AC(void);

/// @brief Update environment animations
/// @param pDeltaTime Delta time in ticks (1/60th of a second)
void func_8002A6FC(int pDeltaTime);

extern Environment g_Environment;

extern int g_SurfaceBelowFlags; // Surface type flags from last height query

#endif
