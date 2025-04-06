#include "loaders.h"
#include "buffers.h"
#include "cd.h"
#include "common.h"
#include "cyclorama.h"
#include "graphics.h"
#include "math.h"
#include "memory.h"
#include "moby_helpers.h"
#include "music.h"
#include "spu.h"
#include "spyro.h"
#include "variables.h"
#include "wad.h"

/// @brief Loads in a new sound table
/// @param pData The data to load
/// @param pPatchAddressesInTable Whether to patch the addresses in the table
void func_80012CF0(char *pData, int pPatchAddressesInTable) {
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

/// @brief Loads the level scene, as we used to call it
/// @param pData The data to load
/// @param pCutscene Whether it's scene data for a cutscene, which is missing
/// collision and occlusion data
/// @return The end of the scene data
void *func_80012D58(void *pData, int pCutscene);
/// @brief Loads the level scene, as we used to call it
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/loaders", func_80012D58);

/// @brief Patches the pointers inside of Spyro's model
// Has some cool code added after July
void func_80013230(void *data) {
  int animation_index;
  int j;
  int frame_data_size;
  int anim_len;
  int lower;
  int upper;
  int past_frame_data;
  SpyroAnimationFrame *frame;

  for (j = 0; j < 46 /*?*/; ++j) {
    if ((u_int)SPYRO_MODEL->m_Animations[j] <
            (u_int)D_800785D8.m_SharedAnimations ||
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
    (char *)data += 4;
    anim_len = *(int *)data;

    (char *)data += 4;
    SPYRO_MODEL->m_Animations[animation_index] = data;

    PATCH_POINTER(SPYRO_MODEL->m_Animations[animation_index]->m_Faces,
                  SPYRO_MODEL->m_Data);
    PATCH_POINTER(SPYRO_MODEL->m_Animations[animation_index]->m_Colors,
                  SPYRO_MODEL->m_Data);

    frame_data_size = SPYRO_MODEL->m_Animations[animation_index]->m_NumFrames *
                      sizeof(SpyroAnimationFrame);
    past_frame_data =
        (int)((AnimationHeader *)data)->m_Frames + frame_data_size;
    PATCH_POINTER(SPYRO_MODEL->m_Animations[animation_index]->m_Unk2,
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

    // SKELETON: This flag is never set for Moby models, the render code
    // can't deal with the different format either
    if (m->m_Animations[i]->m_Unk1 != 0) {
      PATCH_POINTER(m->m_Animations[i]->m_Unk2, m->m_Data);
      p = (u_int *)&(m->m_Animations[i]->m_Frames[0]);
      for (k = 0; k < m->m_Animations[i]->m_NumFrames; ++k, ++p) {
        // this is all wonky, seems like it's a smaller AnimationFrame
        lower = *p & 0x1fffff;
        *p = *p & 0xffe00000;
        lower = ((int)(lower + (u_int)m->m_Data) >> 1) & 0x1fffff;
        *p = *p + lower;
      }
    } else {
      p = (u_int *)&(m->m_Animations[i]->m_Frames[0]);
      for (k = 0; k < m->m_Animations[i]->m_NumFrames; ++k, ++p) {
        // TODO: This breaks 8MB, which sucks
        // Maybe change the renderer to use an offset instead of a pointer
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

void func_8001364C(int pAnimationsAndSparx); /* Weird param, always 1 iirc */

/// @brief Loads the level's layout
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/loaders", func_8001364C);

/// @brief Reload the current level's layout
void func_800144C8(void) {
  char _pad[32]; // Might've been a buffer to store a string into!

  // Stop sounds
  func_80056B28(0);

  // Reload layout from disc
  CDLoadSync(g_CdState.m_WadSector, D_800785D8.m_LevelLayout,
             D_800785D8.m_LevelLayoutSize,
             D_800785D8.m_LevelLayoutOffset +
                 g_WadHeader.m_LevelEntry[D_80075964].m_Data.m_Offset,
             600);

  // Call load layout
  func_8001364C(1);

  // set default state (32 if flight level, 0 otherwise)
  if (D_80075690) {
    func_8003FDC8(32);
  } else {
    func_8003FDC8(0);
  }

  // reset health
  g_Spyro.m_health = 3;
}

/// @brief Loads the titlescreen
void func_80014564(void) {
  RECT r;
  int i;
  int j;
  int size_to_load;

  CDLoadTime();

  if (g_CdState.m_IsReading != 0 || CdSync(1, 0) != CdlComplete ||
      (g_CdMusic.m_Flags & 0x40) == 0)
    return;

  if (g_LoadStage == 0) {

    // Load the level header from disc
    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_CopyBuf, 2048,
                g_WadHeader.m_CutsceneData[D_8007566C].m_Offset, 600);

    g_LoadStage = 1;

  } else if (g_LoadStage == 1) {

    // Copy the level header to the global struct
    Memcpy(&g_LevelHeader, D_800785D8.m_CopyBuf, sizeof(g_LevelHeader));

    // Load the VRAM for the cutscene from disc
    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_CopyBuf,
                D_8006EE5C[D_8007566C],
                g_LevelHeader.m_VramSramOffset +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset,
                600);

    g_LoadStage = 2;

  } else if (g_LoadStage == 2) {

    // Load the cutscene VRAM from the buffer into VRAM
    // The shift for is dividing by 1024, because every line is 1024 bytes
    setRECT(&r, 512, 0, 512, D_8006EE5C[D_8007566C] >> 10);
    LoadImage(&r, D_800785D8.m_CopyBuf);

    g_LoadStage = 3;

  } else if (g_LoadStage == 3) {

    // Load SRAM from disc, which is placed after VRAM
    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_CopyBuf,
                g_LevelHeader.m_VramSramSize - 0x80000,
                g_LevelHeader.m_VramSramOffset +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset + 0x80000,
                600);

    g_LoadStage = 4;

  } else if (g_LoadStage == 4) {

    SpuSetTransferStartAddr(0x1010);

    // This size isn't accurate, it should be
    // g_LevelHeader.m_VramSramSize - 0x80000
    SpuWrite(D_800785D8.m_CopyBuf, 0x80000 - 0x1010);

    // Wait for the transfer to finish, synchronously sadly
    while (!SpuIsTransferCompleted(SPU_TRANSFER_PEEK))
      ;

    // Load the scene data from disc
    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_DiscCopyBuf,
                g_LevelHeader.m_SceneSize,
                g_LevelHeader.m_SceneOffset +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset,
                600);

    g_LoadStage = 5;

  } else if (g_LoadStage == 5) {

    // Initialize the scene data
    D_800785D8.m_EndOfSceneData =
        (void *)func_80012D58(D_800785D8.m_DiscCopyBuf, 1);

    // Switch to the new skybox
    g_Cyclorama = g_NewCyclorama;

    if (D_8007566C == Cutscene_Intro) {

      size_to_load = g_LevelHeader.m_ModelDataSize - 0x60000;
      g_LoadStage = 6;

    } else {

      size_to_load = g_LevelHeader.m_ModelDataSize;
      g_LoadStage = 8;
    }

    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_EndOfSceneData,
                size_to_load,
                g_LevelHeader.m_ModelDataOffset +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset,
                600);

  } else if (g_LoadStage == 6) {

    g_LoadStage = 7;

  } else if (g_LoadStage == 7) {

    CDLoadAsync(g_CdState.m_WadSector,
                (char *)D_800785D8.m_EndOfSceneData +
                    g_LevelHeader.m_ModelDataSize - 0x60000,
                0x60000,
                g_LevelHeader.m_ModelDataOffset +
                    g_LevelHeader.m_ModelDataSize - 0x60000 +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset,
                600);

    g_LoadStage = 8;

  } else if (g_LoadStage == 8) {

    // Go over the models and patch the pointers
    for (i = 0; g_LevelHeader.m_ModelOffsets[i] > 0; ++i) {
      D_80076378[1 + i] =
          PatchMobyModelPointers((Model *)((char *)D_800785D8.m_EndOfSceneData +
                                           (g_LevelHeader.m_ModelOffsets[i] -
                                            g_LevelHeader.m_ModelDataOffset)));
    }

    D_800785D8.m_LevelLayout =
        (char *)D_800785D8.m_EndOfSceneData + g_LevelHeader.m_ModelDataSize;
    D_800785D8.m_LevelLayoutSize = g_LevelHeader.m_LayoutSize;
    D_800785D8.m_LevelLayoutOffset = g_LevelHeader.m_LayoutOffset;

    // Load the level layout from disc
    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_LevelLayout,
                D_800785D8.m_LevelLayoutSize,
                g_LevelHeader.m_LayoutOffset +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset,
                600);

    g_LoadStage = 9;

  } else if (g_LoadStage == 9) {

    // The layout is actually the cutscene data
    D_80075680 = D_800785D8.m_LevelLayout;

    // While in WAD it's an offset, now we turn it into a pointer
    PATCH_POINTER(D_80075680->m_CameraData, D_80075680);

    // Ditto for the Moby data
    for (j = 0; j < D_80075680->m_MobyCount; ++j) {
      PATCH_POINTER(D_80075680->m_MobyData[j], D_800785D8.m_LevelLayout);
    }

    // Set the Moby pointer to the empty space after the cutscene data
    D_80075828 = (Moby *)((char *)D_800785D8.m_LevelLayout +
                          D_800785D8.m_LevelLayoutSize);

    for (j = 0; j < D_80075680->m_MobyCount; ++j) {
      func_8003A720(&D_80075828[j]);

      // Set the class and render radius, the class is sequential in cutscenes
      D_80075828[j].m_Class = j + 1;
      D_80075828[j].m_RenderRadius = 32;
    }

    // Terminate the moby list
    D_80075828[D_80075680->m_MobyCount].m_State = 0xFF;
    g_LoadStage = 10;
  }
}

/// @brief Loads a dragon cutscene
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/loaders", func_80014B70);

/// @brief "Load level" runs through the load stages
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/loaders", func_80015370);
