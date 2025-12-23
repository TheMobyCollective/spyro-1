#include "music.h"
#include "common.h"
#include "spu.h"

// TODO: Figure out what m_Flags's bits are used for

/// @brief Updates the CD music system
void CDMusicUpdate(void) {
  CdlLOC pos;
  CdlFILTER filter;
  int syncResult = CdSync(1, g_CdMusic.m_SyncData);

  if (g_CdMusic.m_PostCDCommand != 0) {
    switch ((u_int)g_CdMusic.m_PostCDCommand) {
    case CdlStop:
    case CdlPause:
      if (!(g_CdMusic.m_Flags & 0x200) && syncResult == CdlComplete) {
        g_CdMusic.m_Flags = 0x40;
        g_CdMusic.m_PostCDCommand = 0;
      }
      break;
    case CdlReadS:
      g_CdMusic.m_Flags = 0x10;
      g_CdMusic.m_PostCDCommand = 0;
      break;
    }
  } else if (g_CdMusic.m_Flags2 != 0) {
    func_800567F4(g_CdMusic.m_CurrentTrack, g_CdMusic.m_Flags2);
    g_CdMusic.m_Flags2 = 0;
  }

  // Handle track playing/looping
  if (g_CdMusic.m_Flags & 0x10) {
    switch (syncResult) {
    case CdlDiskError:
      // Error, restart track from the beginning
      CdIntToPos(g_CdMusic.m_MusicTable[g_CdMusic.m_CurrentTrack].start, &pos);
      CdControl(CdlReadS, (u_char *)&pos, nullptr);
      g_CdMusic.m_PostCDCommand = CdlReadS;
      g_CdMusic.m_TrackPosition =
          g_CdMusic.m_MusicTable[g_CdMusic.m_CurrentTrack].start;
      break;
    case CdlComplete:
      // Check if we've reached the end of the current track
      if (g_CdMusic.m_TrackPosition >
          (u_int)g_CdMusic.m_MusicTable[g_CdMusic.m_CurrentTrack].end) {

        // Track ended, check if we're ready to place an easter egg track
        if (D_800758C8 > (u_int)g_CdMusic.m_EasterEggTicks) {
          // Select a random track from the current level's easter egg table
          g_CdMusic.m_CurrentTrack =
              D_8006EF9C[D_8006F05C[g_LevelIndex][rand() % 3]];
          g_CdMusic.m_EasterEggTicks =
              D_800758C8 + (480 * 60); // Set new track in 8 minutes.
        }

        // Start playing the current track, which could be for looping or a new
        // track if the easter egg is triggered
        g_CdMusic.m_TrackPosition =
            g_CdMusic.m_MusicTable[g_CdMusic.m_CurrentTrack].start;

        CdIntToPos(g_CdMusic.m_TrackPosition, &pos);

        filter.file = 1;
        filter.chan = (u_int)g_CdMusic.m_CurrentTrack % 8;

        CdControlB(CdlSetfilter, (u_char *)&filter, nullptr);
        CdControl(CdlReadS, (u_char *)&pos, nullptr);
      } else {
        // Track still playing, update position
        if (CdLastCom() == CdlGetlocP) {
          // Extract position from sync data
          // (offset +5 contains CdlGetlocP result)
          int p = CdPosToInt((CdlLOC *)&g_CdMusic.m_SyncData[5]);
          if (p > 0)
            g_CdMusic.m_TrackPosition = p;
        }

        // Continue reading position
        CdControlF(CdlGetlocP, nullptr);
      }
      break;
    }
  }

  // Handle music volume fading
  if (g_Spu.m_MusicFadeTarget >= 0) {
    int val = g_Spu.m_CommonAttr.cd.volume.left + g_Spu.m_MusicFadeCurrent;

    if (g_Spu.m_MusicFadeCurrent < 0) {
      // Fading down
      if (val <= g_Spu.m_MusicFadeTarget) {
        // Fade complete, reached target volume
        if (g_Spu.m_MusicFadeTarget == 0) {
          // Faded to silence, execute pending CD commands
          switch ((u_int)g_CdMusic.m_PostCDCommand) {
          case CdlStop:
          case CdlPause:
            CdControl(g_CdMusic.m_PostCDCommand, nullptr, nullptr);
            g_CdMusic.m_Flags = 0x100;
            break;

          case CdlReadS:
            g_CdMusic.m_Flags = 0x10;
            break;
          }
        }

        // Set final volume and clear fade state
        g_Spu.m_MusicFadeCurrent = 0;
        g_Spu.m_CommonAttr.cd.volume.left = g_Spu.m_MusicFadeTarget;
        g_Spu.m_CommonAttr.cd.volume.right = g_Spu.m_MusicFadeTarget;
        g_Spu.m_MusicFadeTarget = -1;
      } else {
        // Continue fading down
        g_Spu.m_CommonAttr.cd.volume.left = val;
        g_Spu.m_CommonAttr.cd.volume.right = g_Spu.m_CommonAttr.cd.volume.left;
      }
    } else {
      // Fading up
      if (g_Spu.m_MusicFadeTarget <= val) {
        // Fade complete, reached target volume
        g_Spu.m_MusicFadeCurrent = 0;
        g_Spu.m_CommonAttr.cd.volume.left = g_Spu.m_MusicFadeTarget;
        g_Spu.m_CommonAttr.cd.volume.right = g_Spu.m_MusicFadeTarget;
        g_Spu.m_MusicFadeTarget = -1;
      } else {
        // Continue fading up
        g_Spu.m_CommonAttr.cd.volume.left = val;
        g_Spu.m_CommonAttr.cd.volume.right = g_Spu.m_CommonAttr.cd.volume.left;
      }
    }

    // Apply the volume changes to the SPU
    g_Spu.m_CommonAttr.mask = SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR;
    SpuSetCommonAttr(&g_Spu.m_CommonAttr);
  } else {
    // Dunno yet
    if (g_CdMusic.m_Flags & 0x200) {
      g_CdMusic.m_Flags = 0x100;
    }
  }
}
