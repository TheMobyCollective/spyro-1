#include "loaders.h"
#include "buffers.h"
#include "camera.h"
#include "cd.h"
#include "checkpoint.h"
#include "common.h"
#include "cyclorama.h"
#include "graphics.h"
#include "math.h"
#include "memory.h"
#include "moby_helpers.h"
#include "music.h"
#include "save_file.h"
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

  // This got added after July, it sets all level animations to null
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
                 g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset,
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
  int dataSize;

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
    D_800785D8.m_ModelData = (void *)func_80012D58(D_800785D8.m_DiscCopyBuf, 1);

    // Switch to the new skybox
    g_Cyclorama = g_NewCyclorama;

    if (D_8007566C == Cutscene_Intro) {

      dataSize = g_LevelHeader.m_ModelDataSize - 0x60000;
      g_LoadStage = 6;

    } else {

      dataSize = g_LevelHeader.m_ModelDataSize;
      g_LoadStage = 8;
    }

    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_ModelData, dataSize,
                g_LevelHeader.m_ModelDataOffset +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset,
                600);

  } else if (g_LoadStage == 6) {

    g_LoadStage = 7;

  } else if (g_LoadStage == 7) {

    CDLoadAsync(g_CdState.m_WadSector,
                (char *)D_800785D8.m_ModelData + g_LevelHeader.m_ModelDataSize -
                    0x60000,
                0x60000,
                g_LevelHeader.m_ModelDataOffset +
                    g_LevelHeader.m_ModelDataSize - 0x60000 +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset,
                600);

    g_LoadStage = 8;

  } else if (g_LoadStage == 8) {

    // Go over the models and patch the pointers
    for (i = 0; g_LevelHeader.m_ModelOffsets[i] > 0; ++i) {
      g_Models[1 + i] =
          PatchMobyModelPointers((Model *)((char *)D_800785D8.m_ModelData +
                                           (g_LevelHeader.m_ModelOffsets[i] -
                                            g_LevelHeader.m_ModelDataOffset)));
    }

    D_800785D8.m_LevelLayout =
        (char *)D_800785D8.m_ModelData + g_LevelHeader.m_ModelDataSize;
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

// Only used here (see usage below)
extern int D_80075670; // Unused [0]
extern int D_80075674; // Unused [1]
extern int D_8007577C; // Unused
extern int D_80075850; // Unused [0]
extern int D_80075854; // Unused [1]
extern int D_80075870; // Unused [0]
extern int D_80075874; // Unused [1]

// Set up level overlay pointers
extern void func_8005A470(void);

/// @brief "Load level" runs through the load stages
void func_80015370(int pArg) {
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

    func_80056B28(0); // stop all sounds/music

    if (D_8007576C >= 0) {

      // The portal one has a bunch of duplicate values that aren't used by the
      // game as far as I could tell, so the component size is at + 0x14
      portalCycloramaComponent = g_Portals[D_8007576C]->m_Skybox;
      pointerOffsetOld = &portalCycloramaComponent[5];

      cycloramaSize = portalCycloramaComponent[5] + 1024;
      dest = (int *)((char *)D_800785D8.m_LowerPolyBuffer - cycloramaSize);
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
      dest = (int *)((char *)D_800785D8.m_LowerPolyBuffer - cycloramaSize);
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
    dest = (int *)((char *)D_800785D8.m_LowerPolyBuffer - cycloramaSize -
                   g_Spu.m_SoundTableSize);
    Memcpy(dest, g_Spu.m_SoundTable, g_Spu.m_SoundTableSize);
    func_80012CF0((char *)dest, 0); // Reinitialize the table with the new base

    g_Camera.m_OcclusionGroup = -1;

    g_LoadStage = 2;
    break;

  case 1: // Remove the Cyclorama immediately and start loading (leftover)

    // stop all sounds/music, let voices keep playing
    func_80056B28(0);

    g_Cyclorama.m_SectorCount = 0;
    g_Camera.m_OcclusionGroup = -1;

    g_LoadStage++;
    // No break, just moves onto the next stage right away

  case 2: // Load level overlay, update indices

    g_LevelId = g_NextLevelId; // Set the current level

    func_8005A470(); // Set overlay pointers

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

    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_DiscCopyBuf, 0x800,
                g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset, 600);

    g_LoadStage++;
    break;

  case 4: // Place header and start loading VRAM

    Memcpy(&g_LevelHeader, D_800785D8.m_DiscCopyBuf, sizeof(g_LevelHeader));

    // Load the 512x512 VRAM image
    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_DiscCopyBuf, 512 * 512 * 2,
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

    LoadImage(&rc, (void *)((char *)D_800785D8.m_DiscCopyBuf +
                            D_8007576C * (512 * 256 * 2)));

    D_8007576C++;

    if (D_8007576C == 2) { // If we transfered the second (final) part, move on

      g_LoadStage++;

      // Load the entirety of SPU data
      CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_DiscCopyBuf,
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
    SpuWrite(D_800785D8.m_DiscCopyBuf, 0x80000 - 0x1010);

    g_LoadStage++;
    break;

  case 7: // Wait for the SPU DMA transfer to complete, then move on

    if (!SpuIsTransferCompleted(0))
      break;

    g_LoadStage++;
    break;

  case 8: // Load scene data from Disc

    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_DiscCopyBuf,
                g_LevelHeader.m_SceneSize,
                g_LevelHeader.m_SceneOffset +
                    g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset,
                600);

    g_LoadStage++;
    break;

  case 9: // Initialize scene data

    D_800785D8.m_ModelData = (void *)func_80012D58(D_800785D8.m_DiscCopyBuf,
                                                   0); // process scene data

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
    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_ModelData,
                g_LevelHeader.m_ModelDataSize,
                g_LevelHeader.m_ModelDataOffset +
                    g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset,
                600);

    g_LoadStage++;
    break;

  case 10: // Initialize model pointers

#define MODEL_OFFSET(idx)                                                      \
  (g_LevelHeader.m_ModelOffsets[idx] - g_LevelHeader.m_ModelDataOffset +       \
   (char *)D_800785D8.m_ModelData)

    if (pArg) {
      // Patch in Spyro's Level animations
      func_80013230(MODEL_OFFSET(0));
    }

    // Clear stale Moby model pointers
    for (i = 0; i < MODEL_COUNT; ++i) {
      if (((int)g_Models[i] & 0xffffff) <
          ((int)D_800785D8.m_SharedAnimations & 0xffffff)) {
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

    D_800785D8.m_LevelLayout =
        (char *)D_800785D8.m_ModelData + g_LevelHeader.m_ModelDataSize;
    D_800785D8.m_LevelLayoutSize = g_LevelHeader.m_LayoutSize;
    D_800785D8.m_LevelLayoutOffset = g_LevelHeader.m_LayoutOffset;

#if 0
    // There used to be a printf here that said:
    printf("Level %d:  Memory Available: %ld\n", g_LevelId,
           ((int)D_800785D8.m_LowerPolyBuffer - (int)D_800785D8.m_LevelLayout) -
               g_LevelHeader.m_LayoutSize);

    // Which was originally placed in the final load stage (in tabloid)
    // but got moved here because it was probably more useful here
#endif

    g_LoadStage++;
    break;

  case 11: // Load level layout data

    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_LevelLayout,
                D_800785D8.m_LevelLayoutSize,
                D_800785D8.m_LevelLayoutOffset +
                    g_WadHeader.m_LevelEntry[g_LevelIndex].m_Data.m_Offset,
                600);

    g_LoadStage++;
    break;

  case 12: // Wait for camera to center on Spyro during level transition
    if (!D_800756D0) { // No transition, just increment
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
  // Initialize the layout, which was copied from Disc earlier
  case 13:

    // Set the Easter Egg timer depending on whether this level
    // has been visited before

    if (!g_VisitedFlags.m_Levels[g_LevelIndex])
      g_CdMusic.m_EasterEggTicks = 12 * 60 * 60; // 12 Minutes
    else
      g_CdMusic.m_EasterEggTicks = 8 * 60 * 60; // 8 Minutes

    g_CdMusic.m_CurrentTrack =
        D_8006EF9C[g_LevelIndex]; // Set currently playing track

    g_VisitedFlags.m_Levels[g_LevelIndex] = 1; // Mark this level as visited

    Memset(&g_Checkpoint, 0, sizeof(CheckpointData)); // Clear checkpoint data

    D_8007587C = g_LevelGemCount[g_LevelIndex]; // prev gem count for this level

    D_80075830 = 0; // Key flag
    D_800756C8 =
        0; // Counter used for the collected gems shown in the transition

    func_8001364C(pArg); // Initialize the Level Layout

    if (D_800756D0) { // Has level transition

      if (D_80075690) { // Is flying level

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
              PortalPathMobyData *pathData;
              int rotZ;

              rotZ = g_Spyro.m_bodyRotation.z;
              pathData = D_80075828[g_Portals[i]->m_PathMoby].m_Props;

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
          if (g_Camera.m_0xD8 == &D_8006CA84) {

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

    } else {            // no level transition
      if (D_80075690) { // flight level
        g_Spyro.m_walkingState = 0;
      } else {

        if (g_Gamestate != GS_Balloonist) { // Skip if balloon transition
          func_8003EA68(0);                 // Set Spyro state to 0 (idle)
        }
      }
    }

    g_Cyclorama = g_NewCyclorama;
    D_800756D0 = 0;      // Has level transition
    g_PortalLevelId = 0; // Portal level id

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