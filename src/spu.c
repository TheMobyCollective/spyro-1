#include "spu.h"
#include "camera.h"
#include "cd.h"
#include "common.h"
#include "math.h"
#include "memory.h"
#include "moby.h"
#include "music.h"
#include "spyro.h"
#include "variables.h"

// Mixed sounds and music stuff

// SPU Initialization
void SpuInitialize() {
  int pad[2]; // wtf
  SpuVoiceAttr voiceAttr;

  SpuInit();

  g_Spu.m_CommonAttr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR |
                            SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR;
  g_Spu.unk_0x320 = 0x3fff;

  g_Spu.m_SoundVolume = 0x1000;
  g_Spu.m_CommonAttr.mvol.left = 0x3ccc;
  g_Spu.m_CommonAttr.mvol.right = 0x3ccc;

  g_Spu.m_MusicVolume = 0x5000;
  g_Spu.m_CommonAttr.cd.volume.left = (short)g_Spu.m_MusicVolume;
  g_Spu.m_CommonAttr.cd.volume.right = (short)g_Spu.m_MusicVolume;

  g_Spu.m_MusicFadeTarget = -1;

  SpuSetCommonAttr(&g_Spu.m_CommonAttr);

  voiceAttr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_PITCH |
                   SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_SMODE |
                   SPU_VOICE_ADSR_RMODE | SPU_VOICE_ADSR_AR |
                   SPU_VOICE_ADSR_DR | SPU_VOICE_ADSR_SR | SPU_VOICE_ADSR_RR |
                   SPU_VOICE_ADSR_SL;

  voiceAttr.volume.left = 0x2fff;
  voiceAttr.volume.right = 0x2fff;
  voiceAttr.pitch = 1024;
  voiceAttr.a_mode = SPU_VOICE_LINEARIncN;
  voiceAttr.s_mode = SPU_VOICE_LINEARIncN;
  voiceAttr.r_mode = SPU_VOICE_LINEARDecN;
  voiceAttr.voice = SPU_ALLCH;
  voiceAttr.ar = 0;
  voiceAttr.dr = 0;
  voiceAttr.sr = 0;
  voiceAttr.rr = 0;
  voiceAttr.sl = 15;

  SpuSetVoiceAttr(&voiceAttr);
  SpuSetKey(SPU_OFF, SPU_ALLCH);
  SpuSetTransferMode(SPU_TRANSFER_BY_DMA);

  Memset(g_Spu.m_ActiveSounds, 0, sizeof(g_Spu.m_ActiveSounds));

  g_Spu.m_AudioMono = 0;
}

// Play sound
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/spu", PlaySound);

// Stop sound
void StopSound(u_int pVoice, u_int pType) {
  pVoice &= 0x7F; // Mask out the top bit

  if (pVoice < 24) {
    g_Spu.m_StopVoice |= 1 << pVoice;

    if (pType == 2 || pType == 4) {
      // Yep.. I tried to make this use a pointer to the sound instead but
      // couldn't get it to match

      if (g_Spu.m_ActiveSounds[pVoice].m_SoundRefPtr != nullptr) {
        *g_Spu.m_ActiveSounds[pVoice].m_SoundRefPtr = 127;
      }

      g_Spu.m_ActiveSounds[pVoice].m_Flags = 0x40;
      g_Spu.m_ActiveSounds[pVoice].m_SoundRefPtr = nullptr;
      g_Spu.m_ActiveSounds[pVoice].m_Moby = nullptr;
      g_Spu.m_ActiveSounds[pVoice].m_SoundId = 0xff;
    }
  }
}

// Stop all sounds by Moby
void func_800562A4(Moby *pMoby, u_int pType) {
  int i;
  int toStop;

  toStop = 0;

  for (i = 0; i < 24; i++) {
    if (g_Spu.m_ActiveSounds[i].m_Moby == pMoby &&
        (pType == 1 ||
         (pType == 2 && (g_Spu.m_ActiveSounds[i].m_Flags & 0x100)))) {
      toStop |= 1 << i;

      if (g_Spu.m_ActiveSounds[i].m_SoundRefPtr != nullptr) {
        *g_Spu.m_ActiveSounds[i].m_SoundRefPtr = 127;
      }

      g_Spu.m_ActiveSounds[i].m_SoundRefPtr = nullptr;
      g_Spu.m_ActiveSounds[i].m_Flags = 0x40;
      g_Spu.m_ActiveSounds[i].m_Moby = nullptr;
      g_Spu.m_ActiveSounds[i].m_PitchIncrease = 0;
      g_Spu.m_ActiveSounds[i].m_SoundId = 0xff;
    }
  }

  g_Spu.m_StopVoice |= toStop;
}

// Update sounds
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/spu", func_8005637C);

// Set music state
void func_800567F4(int pSong, int pFlags) {

  // Uhhh, not sure why they made cdFlags 8 bytes long
  u_char cdFlags[8];
  CdlLOC loc;
  CdlFILTER filter;

  // Locked, so exit
  if (g_CdMusic.m_Flags & 0x80)
    return;

  switch (pFlags) {

  // PLAY SONG
  case 1:
    // 0x40 not set and Music volume not 0
    if (g_CdMusic.m_Flags & 0x40 && D_80075748 != 0) {

      // Turn on filter, enable realtime (no retry) and set double speed
      // Effectively, 8 audio channels
      cdFlags[0] = CdlModeSF | CdlModeRT | CdlModeSpeed;
      CdControlB(CdlSetmode, cdFlags, nullptr);

      // Set up the filter
      filter.file = 1;
      filter.chan = pSong % 8;

      CdControlB(CdlSetfilter, (u_char *)&filter, nullptr);

      // Convert track start sector and attempt to begin streaming.
      CdIntToPos(g_CdMusic.m_MusicTable[pSong].start, &loc);
      if (CdControlB(CdlReadS, (u_char *)&loc, nullptr)) {

        // Begin fade-in sequence
        g_CdMusic.m_PostCDCommand = 0;
        g_CdMusic.m_Flags2 = 0;
        g_CdMusic.m_Flags = 0x10;

        g_Spu.m_MusicFadeTarget = g_Spu.m_MusicVolume;
        g_Spu.m_MusicFadeCurrent =
            (g_Spu.m_MusicVolume - g_Spu.m_CommonAttr.cd.volume.left) >> 3;

        break;
      }

      // If the read command didn't return OK immediately, store flags
      g_CdMusic.m_Flags2 = pFlags;
      break;
    } else {
      if (g_CdMusic.m_Flags2 != 0 || g_CdMusic.m_PostCDCommand != 0) {
        if (g_CdMusic.m_Flags2 != 1) {
          g_CdMusic.m_Flags2 = 1;
        }
      }
      break;
    }
    break;

  // STOP / FADE OUT
  case 2:
  case 4:
    // If currently in fade-in, handle fade-out
    if (g_CdMusic.m_Flags & 0x10) {
      if (g_Spu.m_CommonAttr.cd.volume.left != 0) {
        // Begin fade out
        g_Spu.m_MusicFadeCurrent = -g_Spu.m_CommonAttr.cd.volume.left >> 3;
        g_CdMusic.m_PostCDCommand = 9;
        g_Spu.m_MusicFadeTarget = 0;
        g_CdMusic.m_Flags = 0x200;
        break;
      }

      // Volume already 0, mark as silent
      g_CdMusic.m_Flags = 0x40;
      break;
    }

    if (g_CdMusic.m_Flags2 != 0 || g_CdMusic.m_PostCDCommand != 0) {
      if (g_CdMusic.m_Flags2 != 4 && g_CdMusic.m_Flags2 != 2) {
        g_CdMusic.m_Flags2 = 2;
      }
    }
    break;

  // RESUME TRACK
  case 8:

    // Same preconditions as play
    if ((g_CdMusic.m_Flags & 0x40) && (D_80075748 != 0)) {

      // This matches play
      cdFlags[0] = CdlModeSF | CdlModeRT | CdlModeSpeed;
      CdControlB(CdlSetmode, cdFlags, nullptr);

      // Set up the filter
      filter.file = 1;
      filter.chan = pSong % 8;

      CdControlB(CdlSetfilter, (u_char *)&filter, nullptr);

      // Resume from previous stored track position
      CdIntToPos(g_CdMusic.m_TrackPosition, &loc);
      if (CdControlB(CdlReadS, (u_char *)&loc, nullptr)) {
        // Fade the music back in
        g_CdMusic.m_PostCDCommand = 0;
        g_CdMusic.m_Flags2 = 0;
        g_CdMusic.m_Flags = 0x10;

        g_Spu.m_MusicFadeTarget = g_Spu.m_MusicVolume;
        g_Spu.m_MusicFadeCurrent =
            (g_Spu.m_MusicVolume - g_Spu.m_CommonAttr.cd.volume.left) >> 3;

        break;
      }

      g_CdMusic.m_Flags2 = pFlags;
      break;
    }

    if (g_CdMusic.m_Flags2 != 0 || g_CdMusic.m_PostCDCommand != 0) {
      if (g_CdMusic.m_Flags2 != 8) {
        g_CdMusic.m_Flags2 = 8;
      }
    }
    break;
  }
}

// Stop all sounds, and stop music
void func_80056B28(int pSkipVoices) {
  int i;

  pSkipVoices ^= 0xFFFFFF;

  for (i = 0; i < 24; i++) {
    if (g_Spu.m_ActiveSounds[i].m_Flags & 0x83 && (pSkipVoices >> i) & 1) {
      int voiceIdx;
      int flags;

      g_Spu.m_StopVoice |= 1 << i;

      // i & 0x7f, WTF???

      flags = g_Spu.m_ActiveSounds[i & 0x7f].m_Flags & 0x1c;

      // Absolutely horrible (Why not use m_SoundRefPtr??)
      if (flags != 8) {
        // What the fuck
        if (flags < 9 && flags == 4) {
          // Spyro type beat
          if (g_Spu.m_ActiveSounds[i & 0x7f].m_Moby != nullptr)
            ((Spyro *)g_Spu.m_ActiveSounds[i & 0x7f].m_Moby)
                ->m_damageSoundChannel = 0x7f;
        }
      } else {
        // Moby type beat
        if (g_Spu.m_ActiveSounds[i & 0x7f].m_Moby != nullptr)
          g_Spu.m_ActiveSounds[i & 0x7f].m_Moby->m_SoundChannel = 0x7f;
      }

      g_Spu.m_ActiveSounds[i & 0x7f].m_Flags = 0x40;
      g_Spu.m_ActiveSounds[i & 0x7f].m_Moby = nullptr;
      g_Spu.m_ActiveSounds[i & 0x7f].m_SoundRefPtr = nullptr;
      g_Spu.m_ActiveSounds[i & 0x7f].m_SoundId = 0xff;
    }
  }

  // Don't start any voices if we just cleared them all
  g_Spu.m_PlayVoice = 0;

  // Stop music
  func_800567F4(0, 4 /* Stop immediately */);
}

// Stereo sound calculation
void func_80056C84(SpuVolume *pVolumeOut, u_int pDistance, u_char pAngleToSound,
                   u_int pMaxDistance, SpuVolume *pVolumeIn) {
  u_char pad[32]; // Wtf
  u_int volumeScale, leftAttenuation, rightAttenuation;
  int angle, mirroredAngle;

  if (pMaxDistance == 0)
    return;

  // Matching this was a pain in the ass
  if (pAngleToSound >= 64 && pAngleToSound < 192) {
    mirroredAngle = (u_char)(-pAngleToSound);
    angle = (u_char)(pAngleToSound);
  } else {
    mirroredAngle = (u_char)(pAngleToSound + 128);
    angle = (u_char)(128 - pAngleToSound);
  }

  volumeScale = (pDistance << 8) / pMaxDistance;

  // Calculate the attenuation
  // Then apply stereo panning based on angle
  // (I split this up for readability)
  leftAttenuation = pVolumeIn->left - ((volumeScale * pVolumeIn->left) >> 8);
  pVolumeOut->left = (short)((mirroredAngle * (short)leftAttenuation) >> 7);

  rightAttenuation = pVolumeIn->right - ((volumeScale * pVolumeIn->right) >> 8);
  pVolumeOut->right = (short)((angle * (short)rightAttenuation) >> 7);

  // Might be a clamp macro, but I couldn't find a matching one
  if (pVolumeOut->left < 0) {
    pVolumeOut->left = 0;
  } else if (pVolumeOut->left > 0x3fff) {
    pVolumeOut->left = 0x3fff;
  }

  if (pVolumeOut->right < 0) {
    pVolumeOut->right = 0;
  } else if (pVolumeOut->right > 0x3fff) {
    pVolumeOut->right = 0x3fff;
  }

  if (g_Spu.m_AudioMono) {
    // If we're on Mono, average the left and right channels
    // This is fucking ridiculous
    pVolumeOut->right = pVolumeOut->left =
        (short)((u_int)(pVolumeOut->right + pVolumeOut->left) / 2);
  }
}

// Is Moby playing a sound?
// (0: no, 1: yes, unknown flag 0x100 not set, 2: yes, flag 0x100 set)
int IsMobyPlayingSound(Moby *pMoby, u_int pSoundId) {
  int i;

  for (i = 0; i < 24; i++) {
    // For the first branch to match you have to put pMoby first
    if (pMoby == g_Spu.m_ActiveSounds[i].m_Moby &&
        g_Spu.m_ActiveSounds[i].m_SoundId == pSoundId) {

      // Tried ternary operator, but it didn't match
      if (g_Spu.m_ActiveSounds[i].m_Flags & 0x100)
        return 2;
      else
        return 1;
    }
  }

  return 0;
}

// Kills orphaned sounds
static void KillOrphans(void) {
  u_char keysStatus[24];
  int i;

  SpuGetAllKeysStatus((char *)keysStatus);

  for (i = 0; i < 24; i++) {
    if (keysStatus[i] == 1 && (g_Spu.m_ActiveSounds[i].m_Flags & 0xC1) == 0) {
#if 0 // Removed after PAL Review, not present in NTSC final
      printf("Found Orphaned Sound on voice %d.  I'm Killing it For you.\n", i);
#endif

      g_Spu.m_ActiveSounds[i].m_Flags = 0x40;
      g_Spu.m_StopVoice |= 1 << i;
    }
  }
}

// Updates SPU voices, but first calls the orphaned sounds check
void SpuUpdate(void) {
  if (D_8007572C % 64 == 0) {
    KillOrphans(); // Check for orphaned sounds
  }

  if (g_Spu.m_PlayVoice != 0) {
    SpuSetKey(SPU_ON, g_Spu.m_PlayVoice & 0xffffff);
    g_Spu.m_PlayVoice = 0;
  }

  if (g_Spu.m_StopVoice != 0) {
    SpuSetKey(SPU_OFF, g_Spu.m_StopVoice & 0xffffff);
    g_Spu.m_StopVoice = 0;
  }
}
