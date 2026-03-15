#include "loaders.h"
#include "42CC4.h"
#include "buffers.h"
#include "camera.h"
#include "cd.h"
#include "checkpoint.h"
#include "collision.h"
#include "common.h"
#include "cutscene.h"
#include "cyclorama.h"
#include "dragon.h"
#include "environment.h"
#include "gamepad.h"
#include "gamestates/draw.h"
#include "graphics.h"
#include "math.h"
#include "memory.h"
#include "moby_helpers.h"
#include "music.h"
#include "overlay_pointers.h"
#include "renderers.h"
#include "save_file.h"
#include "special_surfaces.h"
#include "specular_and_metal.h"
#include "spu.h"
#include "spyro.h"
#include "titlescreen.h"
#include "variables.h"
#include "wad.h"

/// @brief Loads in a new sound table
/// @param pData The data to load
/// @param pPatchAddressesInTable Whether to patch the addresses in the table
void SetNewSoundTable(char *pData, int pPatchAddressesInTable) {
  int soundCount;

  // You have to do this weird sliding char pointer
  // to get it to match

  g_Spu.m_SoundTable = (SoundTable *)pData;
  pData += sizeof(SoundTable);

  soundCount = *(int *)(pData);
  pData += sizeof(int);

  g_Spu.m_SoundDefinitions = (SoundDefinition *)(pData);

  if (pPatchAddressesInTable) {
    while (--soundCount >= 0) {
      // SPU memory has samples starting at 0x1010
      g_Spu.m_SoundDefinitions[soundCount].m_Addr += 0x1010;
    }
  }
}

#define READ_I32(x) *(int *)x, x += 4
#define READ_COMPONENT_HEADER(x) componentStart = (char *)x
#define COMPONENT_ADVANCE(x, y) x += y
#define COMPONENT_START(x) READ_COMPONENT_HEADER(x), COMPONENT_ADVANCE(x, 4)
#define COMPONENT_END(x) x = ((char *)componentStart + *(int *)componentStart)

// TODO: Creates warnings, but I haven't been able to figure out a cleaner
// solution that still matches
#define PATCH_POINTER_RELATIVE_TO_COMPONENT(dest)                              \
  PATCH_POINTER(*(int *)dest, componentStart + 4), dest += 4

/// @brief Loads the level data
/// (We used to refer to this as scene data)
/// @param pData The data to load
/// @param pCutscene Whether it's level data for a cutscene, which is missing
/// collision and occlusion data
/// @return The end of the level data
void *LoadLevelData(char *pData, int pCutscene) {
  char *componentStart;
  int i;
  int j;

  COMPONENT_START(pData); // Texture data

  g_Environment.m_TextureCount = READ_I32(pData);

  g_Environment.m_LQTexturePointer = pData;

  COMPONENT_ADVANCE(pData, 16 * g_Environment.m_TextureCount);

  g_Environment.m_HQTexturePointer = pData;

  COMPONENT_END(pData); //! Texture data

  COMPONENT_START(pData); // Environment data

  g_Environment.m_SectorCount = READ_I32(pData);
  g_Environment.m_SectorPointer = (void **)pData;

  // Fix up sector pointers from relative to absolute
  for (i = 0; i < g_Environment.m_SectorCount; ++i) {
    PATCH_POINTER_RELATIVE_TO_COMPONENT(pData);
  }

  COMPONENT_END(pData); //! Environment data

  if (!pCutscene) {
    READ_COMPONENT_HEADER(pData); // Occlusion data

    // Check if there's more than 4 bytes of data
    // In practice, when occlusion data is missing, the game uses 0
    // HOWEVER, sometimes occlusion data IS missing, but it still
    // generated this component, just with counts of 0. (Terrace Village)
    if (*(int *)componentStart > 4) {
      COMPONENT_ADVANCE(pData, 4); // Component size
      COMPONENT_ADVANCE(pData, 4); // Size of the environment portion
      g_Environment.m_OcclusionGroupCount = READ_I32(pData);
      g_Environment.m_OcclusionGroups = (void *)pData;

      // Fix up environment occlusion group pointers
      for (i = 0; i < g_Environment.m_OcclusionGroupCount; ++i) {
        PATCH_POINTER_RELATIVE_TO_COMPONENT(pData);
      }

      // Jump past the environment block to reach the cyclorama occlusion data
      pData = *(int *)(componentStart + 4) + 4 + componentStart;
      g_NewCyclorama.m_OcclusionGroupsCount = READ_I32(pData);
      g_NewCyclorama.m_OcclusionGroups = pData;

      // Fix up cyclorama occlusion group pointers
      for (i = 0; i < g_NewCyclorama.m_OcclusionGroupsCount; i++) {
        PATCH_POINTER(*(int *)pData,
                      componentStart + *(int *)(componentStart + 4) + 4);
        pData += 4;
      }

    } else {
      g_Environment.m_OcclusionGroupCount = 0;
      g_Environment.m_OcclusionGroups = nullptr;
      g_NewCyclorama.m_OcclusionGroups = nullptr;
    }

    COMPONENT_END(pData); //! Occlusion data
  }

  if (!pCutscene) {
    COMPONENT_START(pData); // Special surface data
    g_Environment.m_SurfaceCount = READ_I32(pData);
    g_Environment.m_SurfaceData = (SpecialSurface **)pData;

    // Fix up special surface pointers
    for (i = 0; i < g_Environment.m_SurfaceCount; ++i) {
      PATCH_POINTER_RELATIVE_TO_COMPONENT(pData);
    }
    COMPONENT_END(pData); //! Special surface data
  }

  if (!pCutscene) {
    COMPONENT_START(pData); // Collision data
    g_Environment.m_TerrainCollision = (TerrainCollision *)pData;

    // Fix up all internal TerrainCollision pointers
    PATCH_POINTER(g_Environment.m_TerrainCollision->m_BlockTree, pData);
    PATCH_POINTER(g_Environment.m_TerrainCollision->m_Blocks, pData);
    PATCH_POINTER(g_Environment.m_TerrainCollision->m_Triangles, pData);
    PATCH_POINTER(
        g_Environment.m_TerrainCollision->m_TriangleOcclusionAssignment, pData);
    PATCH_POINTER(g_Environment.m_TerrainCollision->m_Flags, pData);

    COMPONENT_END(pData); //! Collision data
  }

  COMPONENT_START(pData); // Cyclorama

  g_NewCyclorama.m_BackgroundColor.r = pData[0];
  g_NewCyclorama.m_BackgroundColor.g = pData[1];
  g_NewCyclorama.m_BackgroundColor.b = pData[2];
  COMPONENT_ADVANCE(pData, 4);

  g_NewCyclorama.m_SectorCount = READ_I32(pData);
  g_NewCyclorama.m_Sectors = (void *)pData;

  // Fix up cyclorama sector pointers
  for (i = 0; i < g_NewCyclorama.m_SectorCount; ++i) {
    PATCH_POINTER_RELATIVE_TO_COMPONENT(pData);
  }

  COMPONENT_END(pData); //! Cyclorama

  if (pCutscene) // Exit early if we're in a cutscene
    return (int *)pData;

  g_PortalCount = READ_I32(pData);

  for (i = 0; i < g_PortalCount; ++i) {
    // This code is so weird
    g_Portals[i] = (Portal *)pData;

    pData = (char *)(&g_Portals[i]->m_Points[g_Portals[i]->m_PointCount - 1]);
    g_Portals[i]->m_Skybox = (void *)pData;

    // Yeah that size is just.. wrong
    COMPONENT_ADVANCE(pData, sizeof(Cyclorama));

    COMPONENT_START(pData); // Cyclorama inside of portal
    g_Portals[i]->m_Skybox->copyBgColor = READ_I32(pData);
    g_Portals[i]->m_Skybox->copySectorCount = READ_I32(pData);
    g_Portals[i]->m_Skybox->copySectors = (void *)pData;

    for (j = 0; j < g_Portals[i]->m_Skybox->copySectorCount; ++j) {
      PATCH_POINTER_RELATIVE_TO_COMPONENT(pData);
    }

    COMPONENT_END(pData); //! Cyclorama inside of portal
  }

  COMPONENT_START(pData); // Particle textures

  // The read is the particle count
  for (i = READ_I32(pData); i > 0; i--) {
    D_80076278[*(short *)pData] = (ParticleTexture *)pData;
    pData = pData + *(short *)(pData + 2) + 4;
  }

  COMPONENT_END(pData); //! Particle textures

  READ_COMPONENT_HEADER(pData); // Sound table

  g_Spu.m_SoundTableSize = READ_I32(pData);
  SetNewSoundTable(pData, 1);

  // Necessary for match. Doesn't emit any assembly.
  // Could there have been an alignment macro here?
  // alternatively, use pData++, pData--;
  pData = (char *)(((int)pData + 3) & ~3);

  COMPONENT_END(pData); //! Sound table

  return (int *)pData;
}

/// @brief Patches the pointers inside of Spyro's model
// Has some cool code added after July
void PatchInSpyroAnimations(void *data) {
  int animation_index;
  int j;
  int frame_data_size;
  int anim_len;
  int lower;
  int upper;
  int past_frame_data;
  SpyroAnimationFrame *frame;

  // This got added after July, it sets all level animations to null
  for (j = 0; j < 46 /*?*/; ++j) {
    if ((u_int)SPYRO_MODEL->m_Animations[j] <
            (u_int)g_Buffers.m_SharedAnimations ||
        (int)SPYRO_MODEL->m_Animations[j] == -1) {
      SPYRO_MODEL->m_Animations[j] = nullptr;
    }
  }

  // data format here is:
  //   - 4 byte animation_index
  //   - 4 byte animation_length
  //   - AnimationHeader of animation_length bytes

  for (animation_index = *(int *)data; animation_index >= 0;
       animation_index = *(int *)data) {
    data = ((char *)data + 4);
    anim_len = *(int *)data;

    data = ((char *)data + 4);
    SPYRO_MODEL->m_Animations[animation_index] = data;

    PATCH_POINTER(SPYRO_MODEL->m_Animations[animation_index]->m_Faces,
                  SPYRO_MODEL->m_Data);
    PATCH_POINTER(SPYRO_MODEL->m_Animations[animation_index]->m_Colors,
                  SPYRO_MODEL->m_Data);

    frame_data_size = SPYRO_MODEL->m_Animations[animation_index]->m_NumFrames *
                      sizeof(SpyroAnimationFrame);
    past_frame_data =
        (int)((AnimationHeader *)data)->m_Frames + frame_data_size;

    PATCH_POINTER(
        SPYRO_MODEL->m_Animations[animation_index]->m_AnimationVertices,
        past_frame_data);

    frame = (SpyroAnimationFrame *)SPYRO_MODEL->m_Animations[animation_index]
                ->m_Frames;
    for (j = 0; j < SPYRO_MODEL->m_Animations[animation_index]->m_NumFrames;
         ++j) {
      lower = ((int)((frame->m.m_Data & 0x001FFFFF) + past_frame_data) >> 1) &
              0x1FFFFF;
      upper = (frame->m.m_Data & 0xFFE00000);
      frame->m.m_Data = upper + lower;

      ++frame;
    }

    data = (char *)data + anim_len;
  }
}

/// @brief Patches the pointers inside of a Moby's model
Model *PatchMobyModelPointers(Model *pModel) {
  int i;
  int k;
  int lower;
  u_int *p;
  Model *m = pModel;

  if (m->m_NumAnimations < 0) {
    PATCH_POINTER2(((SimpleModel *)m)->m_Verts, m);
    PATCH_POINTER2(((SimpleModel *)m)->m_Colors, m);
    PATCH_POINTER2(((SimpleModel *)m)->m_Faces, m);
    return (Model *)((u_int)pModel & 0x7FFFFFFF); // Unset the top bit to
                                                  // indicate it's a SimpleModel
  }

  for (i = 0; i < 8; ++i) {
    if (m->m_CollisionModels[i] != 0) {
      // The top bit is unset, because it's used to indicate mesh collision
      // models So we want to take the top bit from m->m_CollisionModels[i]
      // rather than pModel
      PATCH_POINTER(m->m_CollisionModels[i], (u_int)m & 0x7FFFFFFF);
    }
  }

  PATCH_POINTER(m->m_Data, pModel);

  for (i = 0; i < m->m_NumAnimations; ++i) {
    if ((int)m->m_Animations[i] == -1) {
      continue;
    }

    PATCH_POINTER(m->m_Animations[i], pModel);
    PATCH_POINTER(m->m_Animations[i]->m_Faces, m->m_Data);
    PATCH_POINTER(m->m_Animations[i]->m_Colors, m->m_Data);

    if (m->m_Animations[i]->m_LpFaces != 0) {
      PATCH_POINTER(m->m_Animations[i]->m_LpFaces, m->m_Data);
      PATCH_POINTER(m->m_Animations[i]->m_LpColors, m->m_Data);
    }

    // Used for Spyro's model in PETE.WAD
    if (m->m_Animations[i]->m_IsSpyroAnimation != 0) {
      PATCH_POINTER(m->m_Animations[i]->m_AnimationVertices, m->m_Data);
      p = (u_int *)&(m->m_Animations[i]->m_Frames[0]);
      for (k = 0; k < m->m_Animations[i]->m_NumFrames; ++k, ++p) {
        lower = *p & 0x1fffff;
        *p = *p & 0xffe00000;
        lower = ((int)(lower + (u_int)m->m_Data) >> 1) & 0x1fffff;
        *p = *p + lower;
      }
    } else {
      p = (u_int *)&(m->m_Animations[i]->m_Frames[0]);
      for (k = 0; k < m->m_Animations[i]->m_NumFrames; ++k, ++p) {
        // TODO: This breaks 8MB, which sucks, consider fixing with a FIX_BUGS
        // define. Which would mean changing the renderer to use an offset
        // instead of a pointer.
        *p += (u_int)m->m_Data & 0x1fffff;
        ++p;
        if ((*p & 0xffff) != 0) {
          *p += (((int)m->m_Data - (int)p + 4) >> 2) & 0xffff;
        }
      }
    }
  }

  return pModel;
}

extern int D_80075698; // No read XREFs, only written here

typedef struct {
  Vector3D m_StartingPosition;
  Vector3D8 m_StartingRotation;
  Tiledef m_FlameTexture;
  Tiledef m_ShadowTexture;
  Tiledef m_UnusedTexture;
  Tiledef m_OrbAndEggSprite[10];
  Tiledef m_SuperFlameTexture;
  Tiledef m_SpecularMetalTexture;
} LevelSceneHeader;

/// @brief Loads the level's scene
void LoadLevelScene(int pAnimationsAndSparx) {
  char *data;
  int i;
  int j;
  Vector3D v;
  char *sceneBase;
  char *componentStart;
  int index, bit;
  uint pendingDrops;

  KillSoundsAndMusic(0); // stop all sounds
  SpecularReset();

  data = sceneBase = (char *)g_Buffers.m_LevelScene;

  g_LevelTicks = 0;
  g_GameTick = 0;
  g_IsSpyroHidden = 0;
  g_TracerCount = 0;

  if (g_LevelId == 64) {
    g_KeyFlag = 0;
  }

  D_80075698 = 0;

  // Beast Makers Home and Misty Bog
  if (g_LevelId == 40 || g_LevelId == 42) {
    // The Environment renderer doesn't like it when it
    // has to draw the LOD of a sector that doesn't have one,
    // so it's disabled here explicitly.
    g_SkipLowPolyWorld = 1;
  } else {
    g_SkipLowPolyWorld = 0;
  }

  PadReset(&g_Pad);

  if (!g_IsFlightLevel) { // is not flight level
    D_8007580C = g_Spyro.m_health;
  }

  if (g_Checkpoint.m_StoodOnCheckpoint) {
    VecCopy(&g_Spyro.m_Position, &g_Checkpoint.m_StartingPosition);
    g_Spyro.m_bodyRotation.z = g_Checkpoint.m_StartingRotation >> 4;
  } else if (g_PortalLevelId == 0) {
    setXYZ(&g_Checkpoint.m_StartingPosition,
           ((LevelSceneHeader *)data)->m_StartingPosition.x,
           ((LevelSceneHeader *)data)->m_StartingPosition.y,
           ((LevelSceneHeader *)data)->m_StartingPosition.z);

    g_Checkpoint.m_StartingRotation =
        ((LevelSceneHeader *)data)->m_StartingRotation.z;

    if (g_HasLevelTransition == 0 && g_Gamestate != 12) {
      if (g_Gamestate == 5 && (g_LevelId >= 40 && g_LevelId < 60) &&
          D_8006F218[g_PreviousLevelId - 18].x != 0) {
        VecCopy(&g_Spyro.m_Position, &D_8006F218[g_PreviousLevelId - 18]);
        g_Spyro.m_bodyRotation.z = D_8006F2A8[g_PreviousLevelId - 18];
      } else {
        VecCopy(&g_Spyro.m_Position, &g_Checkpoint.m_StartingPosition);
        g_Spyro.m_bodyRotation.z = g_Checkpoint.m_StartingRotation;
      }
    }
  }

  g_Spyro.m_health = D_8007580C;

  if (g_Gamestate != 12) {
    // reset spyro
    func_8004AC24(0);
    g_Spyro.m_noGamepadUpdateFrames = 12;
  }

  if (g_LevelId % 10 == 5) {
    g_IsFlightLevel = 1; // is flight level
    g_Spyro.m_flyingAbility = 1;
    D_800758C0 = g_Checkpoint.m_StartingPosition.z;
    g_Spyro.m_highestFlightPoint = g_Checkpoint.m_StartingPosition.z;

    // change spyro state
    func_8003EA68(32);

    if (g_HasLevelTransition == 0) {
      g_Spyro.m_walkingState = 0;
      g_Spyro.m_bodyRotation.x = 0;
      g_Spyro.m_bodyRotation.y = 0;
      g_Spyro.m_Physics.m_SpeedAngle.m_RotY = 0;
      g_Spyro.m_Physics.m_SpeedAngle.m_RotX = 0;
      D_80075960 = 0;
      D_800758A0 = 0;
      D_80075700 = 0;
      g_Spyro.m_Position.z = g_Spyro.m_Position.z + -1024;
    }

  } else {
    g_IsFlightLevel = 0; // is not flight level
    g_Spyro.m_flyingAbility = 0;

    if (g_HasLevelTransition != 0) {
      g_Checkpoint.m_StartingPosition.z += D_8006EDB4[g_LevelIndex];
      g_Checkpoint.m_StartingPosition.x -=
          ((u_short)COSINE_8(g_Checkpoint.m_StartingRotation) << 16) >> 18;
      g_Checkpoint.m_StartingPosition.y -=
          ((u_short)SINE_8(g_Checkpoint.m_StartingRotation) << 16) >> 18;
    }
  }

  // Skip over the starting position and rotation
  COMPONENT_ADVANCE(data, OFFSET(LevelSceneHeader, m_FlameTexture));

  if (g_LevelId == 64) {
    D_800758C0 = 16000;
    D_80075678 = 17976;
  }

  g_Fade = 0;

  if (g_HasLevelTransition == 0 && g_Gamestate != 12) {
    D_80078668 = D_8006C934;

    g_Camera.m_Focus = &g_Spyro.m_Position;
    g_Camera.m_State = 0;
    g_Camera.unk_0xC0 = 0;
    D_80078668.m_Coords.radius = 1536;
    g_Camera.m_SphericalPreset = &D_80078668;
    g_Camera.m_FocusRotation = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

    // reset some camera stuff
    func_80034358();
    g_Fade = 32; // fade
  }

  if (g_Gamestate != 12) {
    g_Gamestate = 0;
    g_StateSwitch = 1;
    g_ScreenBorderEnabled = 0;
    D_800756C0 = 0;
  }

  // Clear the Spyro's flame and set the texture
  Memset(&g_SpyroFlame, 0, sizeof(g_SpyroFlame));

  g_SpyroFlame.m_FlameTexture.uv0 = ((Tiledef *)data)->uv0;
  g_SpyroFlame.m_FlameTexture.uv1 = ((Tiledef *)data)->uv1;
  COMPONENT_ADVANCE(data, sizeof(Tiledef));

  // Clear Spyro's shadow, and.. set the Moby shadow texture
  Memset(&D_8007AA10, 0, sizeof(D_8007AA10));

  g_MobyShadows.shadow.uv0 = ((Tiledef *)data)->uv0;
  g_MobyShadows.shadow.uv1 = ((Tiledef *)data)->uv1;
  COMPONENT_ADVANCE(data, sizeof(Tiledef));

  // This skips over the unused sprite (((Tiledef *)data)[0])
  // which isn't stored anywhere apparently
  // Anyway.. Store the orb sprite
  g_Hud.m_OrbAndEggSprite[0].uv0 = ((Tiledef *)data)[1].uv0;
  g_Hud.m_OrbAndEggSprite[0].uv1 = ((Tiledef *)data)[1].uv1;

  // And the egg rotation spries
  for (i = 0; i < 9; i++) {
    g_Hud.m_OrbAndEggSprite[1 + i].uv0 = ((Tiledef *)data)[2 + i].uv0;
    g_Hud.m_OrbAndEggSprite[1 + i].uv1 = ((Tiledef *)data)[2 + i].uv1;
  }

  COMPONENT_ADVANCE(data, sizeof(Tiledef) *
                              (1 /* Unused sprite */ + 1 /* Orb sprite */ +
                               9 /* Egg rotation sprites */));

  g_SpyroFlame.m_SuperFlameTexture.uv0 = ((Tiledef *)data)->uv0;
  g_SpyroFlame.m_SuperFlameTexture.uv1 = ((Tiledef *)data)->uv1;
  COMPONENT_ADVANCE(data, sizeof(Tiledef));

  D_800756F0.uv0 = ((Tiledef *)data)->uv0;
  D_800756F0.uv1 = ((Tiledef *)data)->uv1;
  COMPONENT_ADVANCE(data, sizeof(Tiledef));

  COMPONENT_START(data); // Texture animations
  g_EnvironmentAnimations.m_TextureAnimationCount = READ_I32(data);
  g_EnvironmentAnimations.m_TextureAnimations = data;
  for (i = 0; i < g_EnvironmentAnimations.m_TextureAnimationCount; i++) {
    PATCH_POINTER_RELATIVE_TO_COMPONENT(data);
  }
  COMPONENT_END(data); //! Texture animations

  COMPONENT_START(data); // Scrolling textures
  g_EnvironmentAnimations.m_ScrollingTextureCount = READ_I32(data);
  g_EnvironmentAnimations.m_ScrollingTextures = data;
  for (i = 0; i < g_EnvironmentAnimations.m_ScrollingTextureCount; i++) {
    PATCH_POINTER_RELATIVE_TO_COMPONENT(data);
  }
  COMPONENT_END(data); //! Scrolling textures

  COMPONENT_START(data); // High poly animations
  g_EnvironmentAnimations.m_HighPolyAnimationCount = READ_I32(data);
  g_EnvironmentAnimations.m_HighPolyAnimations = data;
  for (i = 0; i < g_EnvironmentAnimations.m_HighPolyAnimationCount; i++) {
    PATCH_POINTER_RELATIVE_TO_COMPONENT(data);
  }
  COMPONENT_END(data); //! High poly animations

  COMPONENT_START(data); // Low poly animations
  g_EnvironmentAnimations.m_LowPolyAnimationCount = READ_I32(data);
  g_EnvironmentAnimations.m_LowPolyAnimations = data;
  for (i = 0; i < g_EnvironmentAnimations.m_LowPolyAnimationCount; i++) {
    PATCH_POINTER_RELATIVE_TO_COMPONENT(data);
  }
  COMPONENT_END(data); //! Low poly animations

  COMPONENT_START(data); // Collision animations
  g_EnvironmentAnimations.m_CollisionAnimationCount = READ_I32(data);
  g_EnvironmentAnimations.m_CollisionAnimations = data;
  for (i = 0; i < g_EnvironmentAnimations.m_CollisionAnimationCount; i++) {
    PATCH_POINTER_RELATIVE_TO_COMPONENT(data);
  }
  COMPONENT_END(data); //! Collision animations

  COMPONENT_START(data); // High color animations
  g_EnvironmentAnimations.m_HighColorAnimationCount = READ_I32(data);
  g_EnvironmentAnimations.m_HighColorAnimations = data;
  for (i = 0; i < g_EnvironmentAnimations.m_HighColorAnimationCount; i++) {
    PATCH_POINTER_RELATIVE_TO_COMPONENT(data);
  }
  COMPONENT_END(data); //! High color animations

  COMPONENT_START(data); // Low color animations
  g_EnvironmentAnimations.m_LowColorAnimationCount = READ_I32(data);
  g_EnvironmentAnimations.m_LowColorAnimations = data;
  for (i = 0; i < g_EnvironmentAnimations.m_LowColorAnimationCount; i++) {
    PATCH_POINTER_RELATIVE_TO_COMPONENT(data);
  }
  COMPONENT_END(data); //! Low color animations

  if (pAnimationsAndSparx) {
    // Initialize environment animations
    func_8002B4AC();
  } else {
    // Unset their counts
    g_EnvironmentAnimations.m_TextureAnimationCount = 0;
    g_EnvironmentAnimations.m_ScrollingTextureCount = 0;
    g_EnvironmentAnimations.m_CollisionAnimationCount = 0;
    g_EnvironmentAnimations.m_HighColorAnimationCount = 0;
    g_EnvironmentAnimations.m_LowColorAnimationCount = 0;
  }

  COMPONENT_START(data); // Level mobys
  i = READ_I32(data);
  g_LevelMobys = (Moby *)data;
  COMPONENT_END(data); //! Level mobys

  // Set the dynamic Moby pointers
  g_DynMobys = &g_LevelMobys[i];
  g_MobyAllocPtr = &g_LevelMobys[i];
  g_LevelMobys[i].m_State = 0xFF;

  // Set the dynamic Moby props pointers
  g_DynMobyCount = 0;
  g_DynMobySpaceEnd = data;
  g_PropsAllocPtr = data;
  *(data - 1) = 0xFF; // Terminate the props

  g_DynMobyMax =
      ((u_int)g_DynMobySpaceEnd - (u_int)g_DynMobys) /
      (sizeof(Moby) + 24 /* Every dynamic Moby gets 24 bytes of props space */);

  data = data + *(int *)data; // Skip past the Moby props data

  COMPONENT_START(data); // Moby pods
  g_MobyPodCount = READ_I32(data);
  g_MobyPods = (u_short **)data;
  for (i = g_MobyPodCount - 1; i >= 0; i--) {
    PATCH_POINTER2(g_MobyPods[i], componentStart);
  }
  COMPONENT_END(data); //! Moby pods

  COMPONENT_START(data); // Moby collision chain
  g_MobyCollisionChain = data;
  COMPONENT_END(data); //! Moby collision chain

  COMPONENT_START(data); // Moby pointers
  for (i = 0; i < *(int *)componentStart;) {
    int *ptr = (int *)(sceneBase + *(int *)data);
    i++;
    PATCH_POINTER2(ptr[0], sceneBase); // Yep.. Relative to sceneBase
    COMPONENT_ADVANCE(data, 4);
  }

  if (g_DemoMode) {
    // Seed rand to make demos consistent
    srand(1234);
    g_Spyro.m_Position.x = g_DemoStartPositions[g_DemoIndex][0];
    g_Spyro.m_Position.y = g_DemoStartPositions[g_DemoIndex][1];
    g_Spyro.m_Position.z = g_DemoStartPositions[g_DemoIndex][2];
    g_Spyro.m_bodyRotation.z = g_DemoStartPositions[g_DemoIndex][3];
    g_Spyro.m_Physics.m_SpeedAngle.m_RotZ = g_Spyro.m_bodyRotation.z << 4;
    D_80075784 = 1; // Enable the extra demo mode vsync

    if (g_DemoMode == DEMO_MODE_PLAY) {
      // Set the pointer for playback, which is at the end of the scene data
      g_DemoDataPtr = (int *)data;
    } else {
      // Set the pointer for recording (requires 8MB RAM)
      g_DemoDataPtr = (int *)0x80600000;
      Memset((void *)0x80600000, 0, 0x4000);
    }
  }

  pendingDrops = 0;

  // Iterate over all the level's Mobys
  // Initialize the shadow, and
  for (i = 0; g_LevelMobys[i].m_State != 0xff; i++) {

    // Check non-shaded marker
    if ((int)g_Models[g_LevelMobys[i].m_Class] < 0) {
      func_800526A8(&g_LevelMobys[i]); // Initialize normal Moby
    } else {
      func_800529CC(&g_LevelMobys[i]); // Initialize shaded Moby
    }

    VecCopy(&v, &g_LevelMobys[i].m_Position);
    v.z += 1024;                     // +1M
    func_8004D5EC(&v, 1024 * 64);    // 64M
    func_800533D0(&g_LevelMobys[i]); // Set shadow based on distance

    if ((g_LevelMobys[i].m_DroppedFlag & 0x7f) < 0x20) {
      index = i >> 5;
      bit = i & 0x1f;
      if (((g_Checkpoint.m_KilledMobysSaved[index] & (1 << bit)) == 0) ||
          ((D_80077908[g_LevelIndex][index] & (1 << bit)) == 0))
        pendingDrops |= 1 << (g_LevelMobys[i].m_DroppedFlag);
    }
  }

  // Iterate over all the level's Mobys again
  for (i = 0; g_LevelMobys[i].m_State != 0xff; i++) {
    index = (i >> 5);
    bit = (i & 0x1f);

    if ((D_80077908[g_LevelIndex][index] & (1 << bit)) != 0) {
      if ((g_Checkpoint.m_KilledMobysSaved[index] & (1 << bit)) == 0) {
        if ((g_LevelMobys[i].m_DroppedFlag & 0x7F) == 0x7D) {
          func_80052568(&g_LevelMobys[i]); // Free the Moby
        } else {
          g_LevelMobys[i].m_DropMoby = -1;
        }
      } else {
        int btemp;
        bit = (g_LevelMobys[i].m_DroppedFlag & 0x7F);

        if (bit < 32) {
          btemp = (pendingDrops & (1 << bit)) != 0;
        } else {
          btemp = bit == 0x7E;
        }

        if (btemp) {
          g_LevelMobys[i].m_DropMoby = -1;
        } else {
          func_80052568(&g_LevelMobys[i]); // Free the Moby
        }
      }
    }
  }

  // Make the killed bitmasks match
  for (i = 0; i < 8; i++) {
    g_Checkpoint.m_KilledMobys[i] = g_Checkpoint.m_KilledMobysSaved[i];
  }

  // Clear the zapped floors
  for (i = 0; i < 10; i++) {
    D_800777C0[i] = 0;
  }

  g_Particles = g_Buffers.m_ParticleSpaceStart;
  g_ParticleAllocPtr = g_Buffers.m_ParticleSpaceStart;

  g_Particles[0].m_Type = -1;       // Make the first particle a terminator
  *(int *)(&g_Particles[256]) = -1; // Terminate the last particle

  // Mark all glows and sparkles as dead to initialize them
  func_80058B68();

  if (pAnimationsAndSparx && !g_IsFlightLevel) {
    // Spawn Sparx
    g_Sparx = g_SpawnMoby(120, 0);
    HudReset(1);
  }

  // Start the level's music track
  SetMusicState(g_CdMusic.m_CurrentTrack, 1);
}

/// @brief Reload the current level's scene data
void func_800144C8(void) {
  // Extremely likely to be an unused string buffer
  char _pad[32];

  // Stop sounds
  KillSoundsAndMusic(0);

  // Reload scene from disc
  CDLoadSync(g_CdState.m_WadSector, g_Buffers.m_LevelScene,
             g_Buffers.m_LevelSceneSize,
             g_Buffers.m_LevelSceneOffset +
                 g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset,
             600);

  // Call load scene
  LoadLevelScene(1);

  // set default state (32 if flight level, 0 otherwise)
  if (g_IsFlightLevel) {
    func_8003FDC8(32);
  } else {
    func_8003FDC8(0);
  }

  // reset health
  g_Spyro.m_health = 3;
}

/// @brief Load a cutscene (titlescreen, intro, outro)
void LoadCutscene(void) {
  RECT r;
  int i;
  int j;
  int dataSize;

  // Wait for the CD subsystem to finish loading
  CDLoadTime();

  if (g_CdState.m_IsReading != 0 || CdSync(1, 0) != CdlComplete ||
      (g_CdMusic.m_Flags & 0x40) == 0)
    return;

  if (g_LoadStage == 0) {

    // Load the level header from disc
    CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_CopyBuf, 2048,
                g_WadHeader.m_CutsceneData[g_CutsceneIdx].m_Offset, 600);

    g_LoadStage = 1;

  } else if (g_LoadStage == 1) {

    // Copy the level header to the global struct
    Memcpy(&g_LevelHeader, g_Buffers.m_CopyBuf, sizeof(g_LevelHeader));

    // Load the VRAM for the cutscene from disc
    CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_CopyBuf,
                D_8006EE5C[g_CutsceneIdx],
                g_LevelHeader.m_VramSramOffset +
                    g_WadHeader.m_CutsceneData[g_CutsceneIdx].m_Offset,
                600);

    g_LoadStage = 2;

  } else if (g_LoadStage == 2) {

    // Load the cutscene VRAM from the buffer into VRAM
    // The shift for is dividing by 1024, because every line is 1024 bytes
    setRECT(&r, 512, 0, 512, D_8006EE5C[g_CutsceneIdx] >> 10);
    LoadImage(&r, g_Buffers.m_CopyBuf);

    g_LoadStage = 3;

  } else if (g_LoadStage == 3) {

    // Load SRAM from disc, which is placed after VRAM
    CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_CopyBuf,
                g_LevelHeader.m_VramSramSize - 0x80000,
                g_LevelHeader.m_VramSramOffset +
                    g_WadHeader.m_CutsceneData[g_CutsceneIdx].m_Offset +
                    0x80000,
                600);

    g_LoadStage = 4;

  } else if (g_LoadStage == 4) {

    SpuSetTransferStartAddr(0x1010);

    // This size isn't accurate, it should be
    // g_LevelHeader.m_VramSramSize - 0x80000
    SpuWrite(g_Buffers.m_CopyBuf, 0x80000 - 0x1010);

    // Wait for the transfer to finish, synchronously sadly
    while (!SpuIsTransferCompleted(SPU_TRANSFER_PEEK))
      ;

    // Load the level data from disc
    CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf,
                g_LevelHeader.m_DataSize,
                g_LevelHeader.m_DataOffset +
                    g_WadHeader.m_CutsceneData[g_CutsceneIdx].m_Offset,
                600);

    g_LoadStage = 5;

  } else if (g_LoadStage == 5) {

    // Initialize the level data
    g_Buffers.m_ModelData = LoadLevelData(g_Buffers.m_DiscCopyBuf, 1);

    // Switch to the new skybox
    g_Cyclorama = g_NewCyclorama;

    if (g_CutsceneIdx == Cutscene_Intro) {

      dataSize = g_LevelHeader.m_ModelDataSize - 0x60000;
      g_LoadStage = 6;

    } else {

      dataSize = g_LevelHeader.m_ModelDataSize;
      g_LoadStage = 8;
    }

    CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_ModelData, dataSize,
                g_LevelHeader.m_ModelDataOffset +
                    g_WadHeader.m_CutsceneData[g_CutsceneIdx].m_Offset,
                600);

  } else if (g_LoadStage == 6) {

    g_LoadStage = 7;

  } else if (g_LoadStage == 7) {

    CDLoadAsync(
        g_CdState.m_WadSector,
        (char *)g_Buffers.m_ModelData + g_LevelHeader.m_ModelDataSize - 0x60000,
        0x60000,
        g_LevelHeader.m_ModelDataOffset + g_LevelHeader.m_ModelDataSize -
            0x60000 + g_WadHeader.m_CutsceneData[g_CutsceneIdx].m_Offset,
        600);

    g_LoadStage = 8;

  } else if (g_LoadStage == 8) {

    // Go over the models and patch the pointers
    for (i = 0; g_LevelHeader.m_ModelOffsets[i] > 0; ++i) {
      g_Models[1 + i] =
          PatchMobyModelPointers((Model *)((char *)g_Buffers.m_ModelData +
                                           (g_LevelHeader.m_ModelOffsets[i] -
                                            g_LevelHeader.m_ModelDataOffset)));
    }

    g_Buffers.m_LevelScene =
        (char *)g_Buffers.m_ModelData + g_LevelHeader.m_ModelDataSize;
    g_Buffers.m_LevelSceneSize = g_LevelHeader.m_SceneSize;
    g_Buffers.m_LevelSceneOffset = g_LevelHeader.m_SceneOffset;

    // Load the level scene from disc
    CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_LevelScene,
                g_Buffers.m_LevelSceneSize,
                g_LevelHeader.m_SceneOffset +
                    g_WadHeader.m_CutsceneData[g_CutsceneIdx].m_Offset,
                600);

    g_LoadStage = 9;

  } else if (g_LoadStage == 9) {

    // The scene is actually the cutscene data
    g_CutsceneLayout = g_Buffers.m_LevelScene;

    // While in WAD it's an offset, now we turn it into a pointer
    PATCH_POINTER(g_CutsceneLayout->m_CameraData, g_CutsceneLayout);

    // Ditto for the Moby data
    for (j = 0; j < g_CutsceneLayout->m_MobyCount; ++j) {
      PATCH_POINTER(g_CutsceneLayout->m_MobyData[j], g_Buffers.m_LevelScene);
    }

    // Set the Moby pointer to the empty space after the cutscene data
    g_LevelMobys =
        (Moby *)((char *)g_Buffers.m_LevelScene + g_Buffers.m_LevelSceneSize);

    for (j = 0; j < g_CutsceneLayout->m_MobyCount; ++j) {
      func_8003A720(&g_LevelMobys[j]);

      // Set the class and render radius, the class is sequential in cutscenes
      g_LevelMobys[j].m_Class = j + 1;
      g_LevelMobys[j].m_RenderRadius = 32;
    }

    // Terminate the moby list
    g_LevelMobys[g_CutsceneLayout->m_MobyCount].m_State = 0xFF;
    g_LoadStage = 10;
  }
}

/// @brief Loads a dragon cutscene
void LoadDragonCutscene(void) {

  // Extremely likely to be an unused string buffer
  char _pad[40];

  int i;

  // Used in stage 0
  int modelSpaceLeft;

  // Used in stage 2
  void *buf;
  int lenToRead;

  // Used in stage 3
  int x;

  // Wait for the CD subsystem to finish loading
  CDLoadTime();

  if (g_CdState.m_IsReading != 0 || CdSync(1, 0) != CdlComplete ||
      (g_CdMusic.m_Flags & 0x40) == 0)
    return;

  switch (g_DragonCutscene.m_Stage) {
  case 0: // Prepare to load dragon cutscene data, compute lengths and overflow

    // Compute space of the original model buffer
    // (up to Moby class 250, the Crystal Dragon, which is always the last one)
    modelSpaceLeft = (int)g_Models[250] - (int)g_Buffers.m_ModelData;

    // Full read if it fits
    if (g_LevelHeader.m_Dragons[g_DragonCutscene.m_CutsceneIdx].m_Length <=
        modelSpaceLeft) {
      g_DragonCutscene.m_LoadLength =
          g_LevelHeader.m_Dragons[g_DragonCutscene.m_CutsceneIdx].m_Length;
      g_DragonCutscene.m_HasOverflow = 0;
    } else {
      // Otherwise read only a multiple of 2048 bytes
      g_DragonCutscene.m_LoadLength = (u_int)(modelSpaceLeft / 2048) * 2048;
      g_DragonCutscene.m_HasOverflow = 1;
    }

    // In practice, overflow is: The models and camera data fit
    // but not in combination with SPU data

    // Load the entire dragon cutscene data from disc
    CDLoadAsync(
        g_CdState.m_WadSector, g_Buffers.m_ModelData,
        g_DragonCutscene.m_LoadLength,
        g_LevelHeader.m_Dragons[g_DragonCutscene.m_CutsceneIdx].m_Offset +
            g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset,
        600);

    g_DragonCutscene.m_Stage++;
    break;

  case 1: // Copy header, initialize models if no overflow, else start overflow
          // process

    Memcpy(&g_DragonCutscene.m_Header, g_Buffers.m_ModelData,
           sizeof(g_DragonCutscene.m_Header));

    // If there is no overflow, everything is already loaded
    if (!g_DragonCutscene.m_HasOverflow) {

      // Set camera data pointer and node count
      g_DragonCutscene.unk_0x48 =
          (char *)g_Buffers.m_ModelData +
          g_DragonCutscene.m_Header.m_CameraData.m_Offset;

      g_DragonCutscene.unk_0x4C =
          g_DragonCutscene.m_Header.m_CameraData.m_Length / 24;

      // Patch Dragon & Spyro models into temporary classes 510 and 511
      g_Models[510] = PatchMobyModelPointers(
          (Model *)((char *)g_Buffers.m_ModelData +
                    g_DragonCutscene.m_Header.m_DragonModel.m_Offset));

      g_Models[511] = PatchMobyModelPointers(
          (Model *)((char *)g_Buffers.m_ModelData +
                    g_DragonCutscene.m_Header.m_SpyroModel.m_Offset));

      g_DragonCutscene.m_BlocksRead = 0;

    } else {

      // First load SPU data into SPU RAM, synchronously...
      SpuSetTransferStartAddr(0x80000 -
                              g_DragonCutscene.m_Header.m_SpuData.m_Length);
      SpuWrite((void *)((int)g_Buffers.m_ModelData +
                        g_DragonCutscene.m_Header.m_SpuData.m_Offset),
               g_DragonCutscene.m_Header.m_SpuData.m_Length);

      while (!SpuIsTransferCompleted(0))
        ;

      // Shift already-loaded data to the front of buffer
      Memcpy(g_Buffers.m_ModelData,
             (char *)g_Buffers.m_ModelData +
                 g_DragonCutscene.m_Header.m_DragonModel.m_Offset,
             g_DragonCutscene.m_LoadLength -
                 g_DragonCutscene.m_Header.m_DragonModel.m_Offset);

      // Load remaining part of dragon data
      CDLoadAsync(
          g_CdState.m_WadSector,
          (char *)g_Buffers.m_ModelData + g_DragonCutscene.m_LoadLength -
              g_DragonCutscene.m_Header.m_DragonModel.m_Offset,
          g_LevelHeader.m_Dragons[g_DragonCutscene.m_CutsceneIdx].m_Length -
              g_DragonCutscene.m_LoadLength,
          g_LevelHeader.m_Dragons[g_DragonCutscene.m_CutsceneIdx].m_Offset +
              g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset +
              g_DragonCutscene.m_LoadLength,
          600);
    }

    g_DragonCutscene.m_Stage++;
    break;

  case 2: // Load SPU if no overflow, else set up pointers after overflow load

    // State 1 is the moment you touch the dragon
    // State 2 is when Spyro is in position
    if (g_DragonCutscene.m_State < 2) {
      return;
    }

    // If no overflow, start loading SPU data block by block
    // replacing the data in SPU RAM, while reading the original into main
    // memory..?
    if (!g_DragonCutscene.m_HasOverflow) {

      SpuSetTransferStartAddr(0x80000 -
                              g_DragonCutscene.m_Header.m_SpuData.m_Length +
                              (g_DragonCutscene.m_BlocksRead * 0x8000));

      if (g_CurDB == &g_DB[0]) {
        buf = g_DB[1].m_PolyBuf;
      } else {
        buf = g_DB[0].m_PolyBuf;
      }

      // Determine length to read, if last block, it can be less than 0x8000
      // otherwise always 0x8000 bytes
      if (g_DragonCutscene.m_Header.m_SpuData.m_Length <
          g_DragonCutscene.m_BlocksRead * 0x8000 + 0x8000) {
        lenToRead = g_DragonCutscene.m_Header.m_SpuData.m_Length % 0x8000;
      } else {
        lenToRead = 0x8000;
      }

      // Read original SPU data block into buffer
      SpuRead(buf, lenToRead);

      // ... synchronously
      while (!SpuIsTransferCompleted(0))
        ;

      SpuSetTransferStartAddr(0x80000 -
                              g_DragonCutscene.m_Header.m_SpuData.m_Length +
                              (g_DragonCutscene.m_BlocksRead * 0x8000));

      // Write new SPU data block into SPU RAM
      SpuWrite((char *)g_Buffers.m_ModelData +
                   g_DragonCutscene.m_Header.m_SpuData.m_Offset +
                   g_DragonCutscene.m_BlocksRead * 0x8000,
               lenToRead);

      // ... synchronously
      while (!SpuIsTransferCompleted(0))
        ;

      // Copy the SPU data block back into main memory
      Memcpy((char *)g_Buffers.m_ModelData +
                 g_DragonCutscene.m_Header.m_SpuData.m_Offset +
                 g_DragonCutscene.m_BlocksRead * 0x8000,
             buf, lenToRead);

      g_DragonCutscene.m_BlocksRead += 1;

      // All SPU data loaded?
      if (g_DragonCutscene.m_BlocksRead * 0x8000 >=
          g_DragonCutscene.m_Header.m_SpuData.m_Length)
        g_DragonCutscene.m_Stage++;

      break;
    }

    // If there is an overflow, all data is now loaded, so set up pointers

    // What in the fuck?! Needed for matching
    // g_Buffers.m_ModelData + g_DragonCutscene.m_Header.m_CameraData.m_Offset
    // - g_DragonCutscene.m_Header.m_DragonModel.m_Offset Would be equivalent
    g_DragonCutscene.unk_0x48 =
        (((char *)g_Buffers.m_ModelData -
          g_DragonCutscene.m_Header.m_DragonModel.m_Offset) +
         g_DragonCutscene.m_Header.m_CameraData.m_Offset +
         g_DragonCutscene.m_Header.m_DragonModel.m_Offset) -
        g_DragonCutscene.m_Header.m_DragonModel.m_Offset;

    g_DragonCutscene.unk_0x4C =
        g_DragonCutscene.m_Header.m_CameraData.m_Length / 24;

    g_Models[510] = PatchMobyModelPointers((Model *)g_Buffers.m_ModelData);
    g_Models[511] = PatchMobyModelPointers(
        (Model *)((char *)g_Buffers.m_ModelData +
                  g_DragonCutscene.m_Header.m_SpyroModel.m_Offset -
                  g_DragonCutscene.m_Header.m_DragonModel.m_Offset));
    g_DragonCutscene.m_Stage++;

    break;
  case 3: // Wait for cutscene to end, then load overflow SPU data if needed

    // Wait for the cutscene to end first
    if (g_DragonCutscene.m_State < 6) {
      return;
    }

    // If there was an overflow, load the SPU data back in now
    // from disc
    if (g_DragonCutscene.m_HasOverflow == 1) {
      x = ((g_DragonCutscene.m_Header.m_SpuData.m_Length + 0x180f) / 2048) *
          2048;
      g_DragonCutscene.m_LoadLength = x;

      if (0x100000 - g_LevelHeader.m_VramSramSize < x) {
        x = g_DragonCutscene.m_LoadLength - 0x100000;

        CDLoadAsync(g_CdState.m_WadSector, (char *)g_Buffers.m_ModelData,
                    g_LevelHeader.m_VramSramSize + x,
                    g_LevelHeader.m_VramSramOffset +
                        g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset -
                        x,
                    600);
      } else {

        // Remove the overflow flag, everything fits now
        g_DragonCutscene.m_HasOverflow = 0;
      }
    }

    g_DragonCutscene.m_Stage++;
    break;

  case 4: // Start loading the original model data back in
          // Transfer the SPU data back too (if overflowed)

    if (g_DragonCutscene.m_HasOverflow == 1) {
      SpuSetTransferStartAddr(0x81010 - g_DragonCutscene.m_LoadLength);
      SpuWrite((char *)g_Buffers.m_ModelData,
               g_LevelHeader.m_VramSramSize - 0x100000 +
                   g_DragonCutscene.m_LoadLength);
      while (!SpuIsTransferCompleted(0))
        ;
    }

    // Load the original model data back in from disc
    CDLoadAsync(g_CdState.m_WadSector, (char *)g_Buffers.m_ModelData,
                g_LevelHeader.m_ModelDataSize,
                g_LevelHeader.m_ModelDataOffset +
                    g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset,
                600);

    g_DragonCutscene.m_Stage++;
    break;
  case 5: // Patch the model pointers back in and finish

    PatchInSpyroAnimations(
        (char *)g_Buffers.m_ModelData +
        (g_LevelHeader.m_ModelOffsets[0] - g_LevelHeader.m_ModelDataOffset));

    for (i = 0; i < 512; ++i) {
      if (((int)g_Models[i] & 0xffffff) <
          ((int)g_Buffers.m_SharedAnimations & 0xffffff)) {
        g_Models[i] = nullptr;
      }
    }

    for (i = 1; i < 64; ++i) {
      if (g_LevelHeader.m_ModelOffsets[i] < 1) {
        break;
      }

      g_Models[g_LevelHeader.m_ModelIndices[i]] =
          PatchMobyModelPointers((Model *)((char *)g_Buffers.m_ModelData +
                                           (g_LevelHeader.m_ModelOffsets[i] -
                                            g_LevelHeader.m_ModelDataOffset)));
    }

    g_DragonCutscene.m_Stage++;
    break;
  }
}

// Only used here (see usage below)
extern int D_80075670; // Unused [0]
extern int D_80075674; // Unused [1]
extern int D_8007577C; // Unused
extern int D_80075850; // Unused [0]
extern int D_80075854; // Unused [1]
extern int D_80075870; // Unused [0]
extern int D_80075874; // Unused [1]

// Set up level overlay pointers
extern void SetOverlayPointers(void);

/// @brief Runs through load stages to load a level
void LoadLevel(int pArg) {
  RECT rc;

  // Extremely likely to be an unused string buffer
  char _pad[32];

  int i, j;

  // Used in stage 0
  int *pointerOffsetNew;
  int *pointerOffsetOld;
  int *dest;
  int *portalCycloramaComponent;
  int cycloramaSize;

  // Wait for the CD subsystem to finish loading if the load stage is over 1
  if (g_LoadStage > 1) {
    CDLoadTime();
    if (g_CdState.m_IsReading != 0 || CdSync(1, 0) != CdlComplete ||
        (g_CdMusic.m_Flags & 0x40) == 0)
      return;
  }

  switch (g_LoadStage) {

  case 0: // Copy the Cyclorama temporarily into free memory

    KillSoundsAndMusic(0); // stop all sounds/music

    if (D_8007576C >= 0) {

      // The portal one has a bunch of duplicate values that aren't used by the
      // game as far as I could tell, so the component size is at + 0x14
      portalCycloramaComponent = (int *)g_Portals[D_8007576C]->m_Skybox;
      pointerOffsetOld = &portalCycloramaComponent[5];

      cycloramaSize = portalCycloramaComponent[5] + 1024;
      dest = (int *)((char *)g_Buffers.m_LowerPolyBuffer - cycloramaSize);
      Memcpy(dest, portalCycloramaComponent, cycloramaSize);

      dest += 5; // Skip over the extra bytes

      pointerOffsetNew = dest++;

      *((int *)&g_Cyclorama.m_BackgroundColor) = *dest++;
      g_Cyclorama.m_SectorCount = *dest++;
      g_Cyclorama.m_Sectors = (void **)dest;

      // Patch the cyclorama sector pointer into their new place
      for (j = 0; j < g_Cyclorama.m_SectorCount; ++j) {
        *dest++ = (int)pointerOffsetNew + *dest - (int)pointerOffsetOld;
      }

    } else {

      portalCycloramaComponent = ((int *)g_Cyclorama.m_Sectors - 3);
      pointerOffsetOld = portalCycloramaComponent;

      cycloramaSize = *portalCycloramaComponent + 1024;
      dest = (int *)((char *)g_Buffers.m_LowerPolyBuffer - cycloramaSize);
      Memcpy(dest, portalCycloramaComponent, cycloramaSize);

      pointerOffsetNew = dest++;

      dest++; // Doesn't alter the color..?

      g_Cyclorama.m_SectorCount = *dest++;
      g_Cyclorama.m_Sectors = (void **)dest;

      // Patch the cyclorama sector pointer into their new place
      for (j = 0; j < g_Cyclorama.m_SectorCount; ++j) {
        *dest++ = (int)pointerOffsetNew + *dest - (int)pointerOffsetOld;
      }
    }

    // Copy the Sound Table over too, to preserve it during the Level Transition
    dest = (int *)((char *)g_Buffers.m_LowerPolyBuffer - cycloramaSize -
                   g_Spu.m_SoundTableSize);
    Memcpy(dest, g_Spu.m_SoundTable, g_Spu.m_SoundTableSize);
    SetNewSoundTable((char *)dest,
                     0); // Reinitialize the table with the new base

    g_Camera.m_OcclusionGroup = -1;

    g_LoadStage = 2;
    break;

  case 1: // Remove the Cyclorama immediately and start loading (leftover)

    // stop all sounds/music, let voices keep playing
    KillSoundsAndMusic(0);

    g_Cyclorama.m_SectorCount = 0;
    g_Camera.m_OcclusionGroup = -1;

    g_LoadStage++;
    // No break, just moves onto the next stage right away

  case 2: // Load level overlay, update indices

    g_LevelId = g_NextLevelId; // Set the current level

    SetOverlayPointers(); // Set overlay pointers

    g_PreviousLevelIndex = g_LevelIndex; // Last absolute level ID, used by the
                                         // transition I believe
    g_Homeworld = (g_LevelId / 10) - 1;  // Homeworld ID, used by Flight levels
    g_LevelIndex =
        (g_Homeworld * 6) + (g_LevelId % 10); // Current absolute level ID

    if (pArg) {
      // Load the level's overlay from Disc
      CDLoadAsync(g_CdState.m_WadSector, g_OverlaySpacePointer,
                  g_WadHeader.m_LevelEntry[g_LevelIndex].m_Overlay.m_Length,
                  g_WadHeader.m_LevelEntry[g_LevelIndex].m_Overlay.m_Offset,
                  600);
    }

    g_LoadStage++;
    break;

  case 3: // Load the level header from Disc

    CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf, 0x800,
                g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset, 600);

    g_LoadStage++;
    break;

  case 4: // Place header and start loading VRAM

    Memcpy(&g_LevelHeader, g_Buffers.m_DiscCopyBuf, sizeof(g_LevelHeader));

    // Load the 512x512 VRAM image
    CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf, 512 * 512 * 2,
                g_LevelHeader.m_VramSramOffset +
                    g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset,
                600);

    // Used as VRAM index now, reset it
    D_8007576C = 0;

    g_LoadStage++;
    break;

  case 5: // Transfer VRAM data in chunks of 512x256 (Normal levels have two)

    // D_8007576C now used as which part of VRAM we're transfering

    setRECT(&rc, 512, D_8007576C * 256, 512, 256);

    LoadImage(&rc, (void *)((char *)g_Buffers.m_DiscCopyBuf +
                            D_8007576C * (512 * 256 * 2)));

    D_8007576C++;

    if (D_8007576C == 2) { // If we transfered the second (final) part, move on

      g_LoadStage++;

      // Load the entirety of SPU data
      CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf,
                  g_LevelHeader.m_VramSramSize - (512 * 512 * 2),
                  g_LevelHeader.m_VramSramOffset +
                      g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset +
                      (512 * 512 * 2),
                  600);
    }

    break;

  case 6: // Transfer the SPU data to SPU RAM

    // Usable SPU RAM starts at 0x1010
    SpuSetTransferStartAddr(0x1010);

    // Size is wrong, should be g_LevelHeader.m_VramSramSize - 0x80000
    SpuWrite(g_Buffers.m_DiscCopyBuf, 0x80000 - 0x1010);

    g_LoadStage++;
    break;

  case 7: // Wait for the SPU DMA transfer to complete, then move on

    if (!SpuIsTransferCompleted(0))
      break;

    g_LoadStage++;
    break;

  case 8: // Load level data from Disc

    CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_DiscCopyBuf,
                g_LevelHeader.m_DataSize,
                g_LevelHeader.m_DataOffset +
                    g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset,
                600);

    g_LoadStage++;
    break;

  case 9: // Initialize level data

    // process level data, the return is a pointer to after the level data
    // where we can then load the model data to
    g_Buffers.m_ModelData = LoadLevelData(g_Buffers.m_DiscCopyBuf, 0);

    if (g_Cyclorama.m_SectorCount != 0 && g_Gamestate != GS_GameOver &&
        g_Gamestate != GS_Balloonist) {

      // Afaik, this is an unused optimization
      // that used to be more relevant before E3, when there were still
      // portals inside of the level

      if (g_PortalLevelId) { // Is Portal transition
        for (i = 0; i < g_PortalCount; i++) {
          Cyclorama *skybox;
          if (g_Portals[i]->m_LevelId == g_PortalLevelId) { // Portal level ID
            // This appears to be... broken
            // The format of that pointer got changed at some point,
            // i'm guessing. But hey, it matches :D
            skybox = (Cyclorama *)g_Portals[i]->m_Skybox;
            g_Cyclorama = *skybox;

            // I think, this would be more correct:
            // skybox = g_Portals[i]->m_Skybox;
            // *(int*)(&g_Cyclorama.m_BackgroundColor) =
            // *((int*)&skybox->m_BackgroundColor); g_Cyclorama.m_SectorCount =
            // skybox->m_SectorCount; g_Cyclorama.m_Sectors = skybox->m_Sectors;
            break;
          }
        }

      } else {
        g_Cyclorama = g_NewCyclorama;
      }
    }

    // Load model data
    CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_ModelData,
                g_LevelHeader.m_ModelDataSize,
                g_LevelHeader.m_ModelDataOffset +
                    g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset,
                600);

    g_LoadStage++;
    break;

  case 10: // Initialize model pointers

#define MODEL_OFFSET(idx)                                                      \
  (g_LevelHeader.m_ModelOffsets[idx] - g_LevelHeader.m_ModelDataOffset +       \
   (char *)g_Buffers.m_ModelData)

    if (pArg) {
      // Patch in Spyro's Level animations
      PatchInSpyroAnimations(MODEL_OFFSET(0));
    }

    // Clear stale Moby model pointers
    for (i = 0; i < MODEL_COUNT; ++i) {
      if (((int)g_Models[i] & 0xffffff) <
          ((int)g_Buffers.m_SharedAnimations & 0xffffff)) {
        g_Models[i] = nullptr;
      }
    }

    // Patch model pointers for this level, and put them in the model list
    for (i = 1; i < 64; ++i) {
      // Break early on the last model
      if (g_LevelHeader.m_ModelOffsets[i] <= 0)
        break;

      g_Models[g_LevelHeader.m_ModelIndices[i]] =
          PatchMobyModelPointers((Model *)MODEL_OFFSET(i));
    }

#undef MODEL_OFFSET

    g_Buffers.m_LevelScene =
        (char *)g_Buffers.m_ModelData + g_LevelHeader.m_ModelDataSize;
    g_Buffers.m_LevelSceneSize = g_LevelHeader.m_SceneSize;
    g_Buffers.m_LevelSceneOffset = g_LevelHeader.m_SceneOffset;

#if 0
    // There used to be a printf here that said:
    printf("Level %d:  Memory Available: %ld\n", g_LevelId,
           ((int)g_Buffers.m_LowerPolyBuffer - (int)g_Buffers.m_LevelLayout) -
               g_LevelHeader.m_SceneSize);

    // Which was originally placed in the final load stage (in tabloid)
    // but got moved here because it was probably more useful here
#endif

    g_LoadStage++;
    break;

  case 11: // Load level scene data

    CDLoadAsync(g_CdState.m_WadSector, g_Buffers.m_LevelScene,
                g_Buffers.m_LevelSceneSize,
                g_Buffers.m_LevelSceneOffset +
                    g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset,
                600);

    g_LoadStage++;
    break;

  case 12: // Wait for camera to center on Spyro during level transition
    if (!g_HasLevelTransition) { // No transition, just increment
      g_LoadStage++;
      break;
    }

    if (D_80075910) { // Wait for the portal to stabilize
      break;
    }

    if (g_PortalLevelId) { // Portal transition
      int dist = g_Spyro.m_Physics.m_SpeedAngle.m_RotZ +
                     g_Camera.m_Simulation.m_Coords.azimuth &
                 0xfff;

      if (dist > 2048) {
        dist -= 4096;
      }

      if (ABS(dist) < 128) {
        g_LoadStage++;
      }

    } else { // Otherwise
      int dist = g_Spyro.m_bodyRotation.z - g_Spyro.m_portalAngle.z & 0xff;

      if (dist > 128)
        dist -= 256;

      if (ABS(dist) < 16) {
        g_LoadStage++;
      }
    }

    break;

  // Final initialization
  // Set up Spyro's position and camera based on entry type
  // Initialize the scene, which was copied from Disc earlier
  case 13:

    // Set the Easter Egg timer depending on whether this level
    // has been visited before

    if (!g_VisitedFlags[g_LevelIndex])
      g_CdMusic.m_EasterEggTicks = 12 * 60 * 60; // 12 Minutes
    else
      g_CdMusic.m_EasterEggTicks = 8 * 60 * 60; // 8 Minutes

    g_CdMusic.m_CurrentTrack =
        D_8006EF9C[g_LevelIndex]; // Set currently playing track

    g_VisitedFlags[g_LevelIndex] = 1; // Mark this level as visited

    Memset(&g_Checkpoint, 0, sizeof(CheckpointData)); // Clear checkpoint data

    D_8007587C = g_LevelGemCount[g_LevelIndex]; // prev gem count for this level

    g_KeyFlag = 0; // Key flag
    g_NGemsSinceLevelEntry =
        0; // Counter used for the collected gems shown in the transition

    LoadLevelScene(pArg); // Initialize the Level scene

    if (g_HasLevelTransition) { // Has level transition

      if (g_IsFlightLevel) { // Is flying level

        g_Spyro.m_walkingState = 10;

        func_80033F08(&g_Camera.m_Position);

        g_Camera.m_Simulation.m_Coords.azimuth +=
            g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

        VecCopy(&g_Spyro.m_Position, &g_Checkpoint.m_StartingPosition);
        g_Spyro.m_bodyRotation.z = g_Checkpoint.m_StartingRotation;

        g_Spyro.m_Physics.m_SpeedAngle.m_RotZ = g_Spyro.m_bodyRotation.z * 16;

        g_Camera.m_Sphere = g_Camera.m_Simulation;
        g_Camera.m_Sphere.m_Coords.azimuth += -g_Spyro.m_bodyRotation.z * 16;

        func_80034204(&g_Camera.m_Position);
        VecAdd(&g_Camera.m_Position, &g_Camera.m_Position, &g_Spyro.m_Position);
        func_800342F8(); // Updte camera rotation

        VecCopy(&D_8006EBCC.m_CameraPosition, &g_Camera.m_Position);
        func_80037714(&D_8006EBCC);

        g_Gamestate = GS_EntranceAnimation;

      } else {

        if (g_PortalLevelId) { // Portal transition

          // Go through all the portals until we find the one
          // we're exiting out of
          for (i = 0; i < g_PortalCount; i++) {
            if (g_Portals[i]->m_LevelId == g_PortalLevelId) {
              MobyPortalPathProps *pathData;
              int rotZ;

              rotZ = g_Spyro.m_bodyRotation.z;
              pathData = g_LevelMobys[g_Portals[i]->m_PathMoby].m_Props;

              func_8003EA68(15); // Set Spyro's state to glide
              g_Spyro.m_walkingState = 9;

              func_80033F08(&g_Camera.m_Position);

              g_Camera.m_Simulation.m_Coords.azimuth +=
                  g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;

              // Determine forward/backward portal direction
              // So we know how to rotate Spyro
              if (pathData->m_Sidedness) {
                VecCopy(&g_Spyro.m_Position,
                        &pathData->m_Path->m_Nodes[0].m_Position);
                VecCopy(&g_Spyro.m_portalEndPos,
                        &pathData->m_Path->m_Nodes[1].m_Position);

                g_Spyro.m_bodyRotation.z =
                    Atan2(pathData->m_Path->m_Nodes[1].m_Position.x -
                              pathData->m_Path->m_Nodes[0].m_Position.x,
                          pathData->m_Path->m_Nodes[1].m_Position.y -
                              pathData->m_Path->m_Nodes[0].m_Position.y,
                          0);
              } else {
                VecCopy(&g_Spyro.m_Position,
                        &pathData->m_Path->m_Nodes[1].m_Position);
                VecCopy(&g_Spyro.m_portalEndPos,
                        &pathData->m_Path->m_Nodes[0].m_Position);

                g_Spyro.m_bodyRotation.z =
                    Atan2(pathData->m_Path->m_Nodes[0].m_Position.x -
                              pathData->m_Path->m_Nodes[1].m_Position.x,
                          pathData->m_Path->m_Nodes[0].m_Position.y -
                              pathData->m_Path->m_Nodes[1].m_Position.y,
                          0);
              }

              // Instantly rotate Spyro and the camera
              g_Spyro.m_Physics.m_SpeedAngle.m_RotZ =
                  g_Spyro.m_bodyRotation.z * 16;

              g_Camera.m_Sphere = g_Camera.m_Simulation;
              g_Camera.m_Sphere.m_Coords.azimuth +=
                  -g_Spyro.m_bodyRotation.z * 16;

              func_80034204(&g_Camera.m_Position); // Sphere -> pos
              VecAdd(&g_Camera.m_Position, &g_Camera.m_Position,
                     &g_Spyro.m_Position);
              func_800342F8(); // Update camera rotation

              g_Spyro.m_sortingDepth = 127; // Sort Spyro over the portal

              // Align the portal rotation with the skybox that was visible
              // during the transition
              D_800758FC = 0;
              D_80075858 = (rotZ - g_Spyro.m_bodyRotation.z) * 16;

              break;
            }
          }

        } else {

          // Non-portal entrance
          func_8003EA68(0xF); // Set Spyro's state to glide

          func_80033F08(
              &g_Camera.m_Position); // Set spherical coords to match pos

          g_Camera.m_Simulation.m_Coords.azimuth +=
              g_Spyro.m_Physics.m_SpeedAngle.m_RotZ;
          g_Spyro.m_bodyRotation.z = g_Checkpoint.m_StartingRotation;
          g_Spyro.m_Physics.m_SpeedAngle.m_RotZ = g_Spyro.m_bodyRotation.z * 16;

          g_Camera.m_Sphere = g_Camera.m_Simulation;
          g_Camera.m_Sphere.m_Coords.azimuth += -g_Spyro.m_bodyRotation.z * 16;

          VecCopy(&g_Spyro.m_Position, &g_Checkpoint.m_StartingPosition);
          func_80034204(&g_Camera.m_Position);

          VecNull(&g_Spyro.m_Physics.m_TrueVelocity);

          // This is part of an array
          // This value is used by the entrance of High Caves, for example
          if (g_Camera.m_SphericalPreset == &D_8006CA84) {

            g_Spyro.m_Position.z -= 0x1600; // 5.5M

            g_Spyro.m_Position.x -=
                (COSINE_8(g_Spyro.m_bodyRotation.z) * 5 >> 1); // * 2.5

            g_Spyro.m_Position.y -=
                (SINE_8(g_Spyro.m_bodyRotation.z) * 5 >> 1); // * 2.5

            VecAdd(&g_Camera.m_Position, &g_Camera.m_Position,
                   &g_Spyro.m_Position);
            func_800342F8(); // Update Camera rotation
            g_Camera.unk_0xC0 = D_8006C588[g_Spyro.m_State];

            g_Gamestate = GS_Playing;
            g_Spyro.m_walkingState = 11;
            g_Spyro.m_sortingDepth = 4;
          } else {
            VecAdd(&g_Camera.m_Position, &g_Camera.m_Position,
                   &g_Spyro.m_Position);
            func_800342F8(); // Update Camera rotation
            VecCopy(&D_8006EBCC.m_CameraPosition, &g_Camera.m_Position);
            func_80037714(&D_8006EBCC);
            g_Spyro.m_walkingState = 10;
            g_Gamestate = GS_EntranceAnimation;
          }
        }
      }

    } else {                 // no level transition
      if (g_IsFlightLevel) { // flight level
        g_Spyro.m_walkingState = 0;
      } else {

        if (g_Gamestate != GS_Balloonist) { // Skip if balloon transition
          func_8003EA68(0);                 // Set Spyro state to 0 (idle)
        }
      }
    }

    g_Cyclorama = g_NewCyclorama;
    g_HasLevelTransition = 0; // Has level transition
    g_PortalLevelId = 0;      // Portal level id

    // SKELETON:
    // This is weird..
    // So this showed up sometime between Jun15 and Jul18.
    // And in Jul5 it's partially here, but only the
    // ones saved into the save file are there.

    // There's another build right in the middle of Jul5 and Jul18
    // that might give us some insight here
    // but it's not been released yet :)

    D_80075870 = 0; // Unused Var
    D_80075874 = 0; // Unused Var

    D_80075838 = 0; // Saved into save file, unused var 1
    D_8007583C = 0; // Saved into save file, unused var 2

    D_80075670 = 0; // Unused Var
    D_80075674 = 0; // Unused Var

    D_8007577C = 0; // Unused Var

    D_80075854 = 0; // Unused Var
    D_80075850 = 0; // Unused Var

    D_80075818 = -1; // Credits cheat return level ID

    g_LoadStage = -1;
    break;
  default:
    break;
  }
}
