#include "buffers.h"
#include "cd.h"
#include "common.h"
#include "cyclorama.h"
#include "graphics.h"
#include "loaders.h"
#include "math.h"
#include "memory.h"
#include "moby.h"
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
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/loaders", func_80013230);

Model *func_800133E0(Model *pModel);

/// @brief Patches the pointers inside of a Moby's model
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/loaders", func_800133E0);

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
    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_CopyBuf, 0x800,
                g_WadHeader.m_CutsceneData[D_8007566C].m_Offset, 600);
    g_LoadStage = 1;
  } else if (g_LoadStage == 1) {
    Memcpy(&g_LevelHeader, D_800785D8.m_CopyBuf, 0x1D0);
    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_CopyBuf,
                D_8006EE5C[D_8007566C],
                g_LevelHeader.m_VramSramOffset +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset,
                600);
    g_LoadStage = 2;
  } else if (g_LoadStage == 2) {
    setRECT(&r, 512, 0, 512, D_8006EE5C[D_8007566C] >> 10);
    LoadImage(&r, D_800785D8.m_CopyBuf);
    g_LoadStage = 3;
  } else if (g_LoadStage == 3) {
    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_CopyBuf,
                g_LevelHeader.m_VramSramSize - 0x80000,
                g_LevelHeader.m_VramSramOffset +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset + 0x80000,
                600);
    g_LoadStage = 4;
  } else if (g_LoadStage == 4) {

    SpuSetTransferStartAddr(0x1010);
    SpuWrite(D_800785D8.m_CopyBuf, 0x7EFF0);

    while (!SpuIsTransferCompleted(0))
      ;

    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_DiscCopyBuf,
                g_LevelHeader.m_SceneSize,
                g_LevelHeader.m_SceneOffset +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset,
                600);
    g_LoadStage = 5;
  } else if (g_LoadStage == 5) {
    D_800785D8.m_EndOfSceneData =
        (void *)func_80012D58(D_800785D8.m_DiscCopyBuf, 1);
    g_Cyclorama = g_NewCyclorama;
    if (D_8007566C == 1) {
      g_LoadStage = 6;
      size_to_load = g_LevelHeader.m_ModelDataSize - 0x60000;
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
    for (i = 0; g_LevelHeader.m_ModelOffsets[i] > 0; ++i) {
      D_80076378[1 + i] =
          func_800133E0((Model *)((char *)D_800785D8.m_EndOfSceneData +
                                  (g_LevelHeader.m_ModelOffsets[i] -
                                   g_LevelHeader.m_ModelDataOffset)));
    }
    D_800785D8.m_LevelLayout =
        (char *)D_800785D8.m_EndOfSceneData + g_LevelHeader.m_ModelDataSize;
    D_800785D8.m_LevelLayoutSize = g_LevelHeader.m_LayoutSize;
    D_800785D8.m_LevelLayoutOffset = g_LevelHeader.m_LayoutOffset;
    CDLoadAsync(g_CdState.m_WadSector, D_800785D8.m_LevelLayout,
                D_800785D8.m_LevelLayoutSize,
                g_LevelHeader.m_LayoutOffset +
                    g_WadHeader.m_CutsceneData[D_8007566C].m_Offset,
                600);
    g_LoadStage = 9;
  } else if (g_LoadStage == 9) {
    D_80075680 = D_800785D8.m_LevelLayout;

    // While in WAD it's an offset, now we turn it into a pointer
    D_80075680->m_CameraData =
        (CutsceneCameraData *)((char *)D_80075680 +
                               (u_int)D_80075680->m_CameraData);

    // Ditto for the Moby data
    for (j = 0; j < D_80075680->m_MobyCount; ++j) {
      D_80075680->m_MobyData[j] =
          (CutsceneMobyData *)((char *)D_800785D8.m_LevelLayout +
                               (u_int)D_80075680->m_MobyData[j]);
    }

    // Set the Moby pointer to the empty space after the cutscene data
    D_80075828 = (Moby *)((char *)D_800785D8.m_LevelLayout +
                          D_800785D8.m_LevelLayoutSize);

    for (j = 0; j < D_80075680->m_MobyCount; ++j) {
      func_8003A720(&D_80075828[j]);

      D_80075828[j].m_Class = j + 1;

      // SKELETON: func_8003A720 already sets this value to 32.
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
