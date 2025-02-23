#include "buffers.h"
#include "cd.h"
#include "common.h"
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
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/loaders", func_80012D58);

/// @brief Patches the pointers inside of Spyro's model
// Has some cool code added after July
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/loaders", func_80013230);

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
             D_800785D8.m_LevelLayoutOffset + WAD_OFFSET(m_LevelEntry[D_80075964 * 2]),
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
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/loaders", func_80014564);

/// @brief Loads a dragon cutscene
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/loaders", func_80014B70);

/// @brief "Load level" runs through the load stages
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/loaders", func_80015370);
