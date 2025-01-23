#include "common.h"
#include "spu.h"
#include "spyro.h"

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
  g_Spu.m_CommonAttr.cd.volume.left = g_Spu.m_MusicVolume;
  g_Spu.m_CommonAttr.cd.volume.right = g_Spu.m_MusicVolume;

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
INCLUDE_ASM_REORDER_HACK("asm/nonmatchings/spu", func_800567F4);

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
          g_Spu.m_ActiveSounds[i & 0x7f].m_Moby->m_soundChannel = 0x7f;
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
  u_int volumeScale, angle, mirroredAngle, leftAttenuation, rightAttenuation;

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
  pVolumeOut->left = (int)(mirroredAngle * (short)leftAttenuation) >> 7;

  rightAttenuation = pVolumeIn->right - ((volumeScale * pVolumeIn->right) >> 8);
  pVolumeOut->right = (int)(angle * (short)rightAttenuation) >> 7;

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
    // This is fucking rediculous
    pVolumeOut->right = pVolumeOut->left =
        (u_int)(pVolumeOut->right + pVolumeOut->left) / 2;
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

      // Tried turinary operator, but it didn't match
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

  SpuGetAllKeysStatus(keysStatus);

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
