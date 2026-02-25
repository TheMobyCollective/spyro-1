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

int PlaySound(u_int pSoundId, Moby *pMoby, u_int pFlags, u_char *pSoundRefOut) {
  SpuVoiceAttr attr;
  Vector3D vec;
  int length;
  int maxDist;
  int i;
  int voice_slot = -1;
  int replacement_slot;
  int angle = g_Camera.m_Rotation.z;

  // Handle precondition checks depending on the flag
  switch (pFlags) {
  case 4:
    // Don't play if this moby is already playing this sound
    if (IsMobyPlayingSound(pMoby, pSoundId) == 2)
      return 0;
    break;

  case 8:
    // Don't play if this moby is already playing this sound
    if (IsMobyPlayingSound(pMoby, pSoundId) == 2)
      return 0;

    // Calculate distance from camera to sound source
    VecSub(&vec, &pMoby->m_Position, &g_Camera.m_Position);
    VecShiftRight(&vec, 4);
    length = VecMagnitude(&vec, 1) << 4;

    // Get max audible distance from moby, with fallback default
    maxDist = pMoby->m_SoundDistance << 10;
    if (maxDist == 0)
      maxDist = 0x4000;

    // Reject sound if source is out of range
    if (maxDist < length) {
      if (pSoundRefOut != 0)
        *pSoundRefOut = 0x7f;
      return 0x7f;
    }
    break;

  case 16:
  default:
    break;
  }

  // Find a free voice slot, also track replacement_slot
  // aaaand doing nothing with it.
  replacement_slot = 256;
  for (i = 0; i < 24; i++) {
    if ((g_Spu.m_ActiveSounds[i].m_Flags & (0x80 | 0x40 | 0x1)) == 0) {
      voice_slot = i;
      break;
    }
    if (g_Spu.m_ActiveSounds[i].unk_0xC <
        g_Spu.m_ActiveSounds[replacement_slot].unk_0xC) {
      replacement_slot = i;
    }
  }

  // No free voice slot available, bail out
  if (voice_slot < 0)
    return 0;

  if (voice_slot != 24) {
    // Initialize the active sound slot
    g_Spu.m_ActiveSounds[voice_slot].m_Flags = pFlags | 1;
    g_Spu.m_ActiveSounds[voice_slot].m_Moby = pMoby;
    g_Spu.m_ActiveSounds[voice_slot].m_SoundId = pSoundId;

    // Apply pitch override if set, otherwise use the sound definition's pitch
    if ((g_Spu.m_NextSoundOverrideFlags & 2) != 0) {
      g_Spu.m_NextSoundOverrideFlags &= ~2;
      g_Spu.m_ActiveSounds[voice_slot].m_Pitch = g_Spu.m_PitchOverride;
    } else {
      g_Spu.m_ActiveSounds[voice_slot].m_Pitch =
          g_Spu.m_SoundDefinitions[pSoundId].m_Pitch;
    }

    attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_PITCH |
                SPU_VOICE_WDSA | SPU_VOICE_LSAX;
    attr.voice = 1 << voice_slot;
    attr.addr = g_Spu.m_SoundDefinitions[pSoundId].m_Addr;
    attr.pitch = g_Spu.m_SoundDefinitions[pSoundId].m_Pitch;

    // Apply randomized pitch variance
    if (g_Spu.m_SoundDefinitions[pSoundId].m_PitchVariance != 0) {
      switch (g_Spu.m_SoundDefinitions[pSoundId].m_VarianceType) {
      case 0:
        // Centered variance
        attr.pitch -= g_Spu.m_SoundDefinitions[pSoundId].m_PitchMultiplier *
                      (g_Spu.m_SoundDefinitions[pSoundId].m_PitchVariance / 2);
        attr.pitch +=
            (rand() % g_Spu.m_SoundDefinitions[pSoundId].m_PitchVariance) *
            g_Spu.m_SoundDefinitions[pSoundId].m_PitchMultiplier;
        break;
      case 1:
        // Upward variance only
        attr.pitch +=
            (rand() % g_Spu.m_SoundDefinitions[pSoundId].m_PitchVariance) *
            g_Spu.m_SoundDefinitions[pSoundId].m_PitchMultiplier;
        break;
      case 2:
        // Downward variance only
        attr.pitch -=
            (rand() % g_Spu.m_SoundDefinitions[pSoundId].m_PitchVariance) *
            g_Spu.m_SoundDefinitions[pSoundId].m_PitchMultiplier;
        break;
      }
    }

    attr.loop_addr = g_Spu.m_SoundDefinitions[pSoundId].m_LoopAddr;

    // Set volume based on sound mode flags
    switch (g_Spu.m_ActiveSounds[i].m_Flags & (0x10 | 0x8 | 0x4)) {
    case 4:
    case 16:
      // Static/non-positional volume
      if ((g_Spu.m_NextSoundOverrideFlags & 1) != 0) {
        // Apply volume override
        g_Spu.m_NextSoundOverrideFlags &= ~1;
        g_Spu.m_ActiveSounds[voice_slot].m_Volume.left =
            g_Spu.m_VolumeOverride.left;
        g_Spu.m_ActiveSounds[voice_slot].m_Volume.right =
            g_Spu.m_VolumeOverride.left;
        attr.volume.left = g_Spu.m_VolumeOverride.left;
        attr.volume.right = g_Spu.m_VolumeOverride.right;
        g_Spu.m_ActiveSounds[i].m_StereoVolume.right =
            g_Spu.m_VolumeOverride.right;
        g_Spu.m_ActiveSounds[i].m_StereoVolume.left =
            g_Spu.m_VolumeOverride.left;
      } else {
        // Default static volume
        g_Spu.m_ActiveSounds[voice_slot].m_Volume.left = 0x2000;
        g_Spu.m_ActiveSounds[voice_slot].m_Volume.right = 0x2000;
        attr.volume.right = 0x2000;
        attr.volume.left = 0x2000;
        g_Spu.m_ActiveSounds[i].m_StereoVolume.right = 0x2000;
        g_Spu.m_ActiveSounds[i].m_StereoVolume.left = 0x2000;
      }
      break;

    case 8:
      // 3D positional audio
      if ((g_Spu.m_NextSoundOverrideFlags & 1) != 0) {
        // Apply volume override
        g_Spu.m_NextSoundOverrideFlags &= ~1;
        g_Spu.m_ActiveSounds[voice_slot].m_Volume.left =
            g_Spu.m_VolumeOverride.left;
        g_Spu.m_ActiveSounds[voice_slot].m_Volume.right =
            g_Spu.m_VolumeOverride.right;
        attr.volume.right = g_Spu.m_VolumeOverride.right;
        attr.volume.left = g_Spu.m_VolumeOverride.left;
      } else {
        // Default positional volume
        g_Spu.m_ActiveSounds[voice_slot].m_Volume.left = 0x3CCC;
        g_Spu.m_ActiveSounds[voice_slot].m_Volume.right = 0x3CCC;
        attr.volume.right = 0x3CCC;
        attr.volume.left = 0x3CCC;
      }

      // Calculate stereo panning based on angle between camera and sound source
      func_80056C84(
          &attr.volume, length,
          func_80017908(
              g_Camera.m_Rotation.z >> 4,
              (char)Atan2(
                  g_Camera.m_Position.x -
                      g_Spu.m_ActiveSounds[voice_slot].m_Moby->m_Position.x,
                  g_Camera.m_Position.y -
                      g_Spu.m_ActiveSounds[voice_slot].m_Moby->m_Position.y,
                  0)),
          maxDist, &g_Spu.m_ActiveSounds[voice_slot].m_Volume);
      break;
    }

    // Scale final volume by master sound volume
    attr.volume.left = attr.volume.left * g_Spu.m_SoundVolume >> 12;
    attr.volume.right = attr.volume.right * g_Spu.m_SoundVolume >> 12;

    SpuSetVoiceAttr(&attr);

    // Mark voice to be keyed on next SPU update
    g_Spu.m_PlayVoice |= 1 << voice_slot;
  }

  // Store the sound ref pointer so the caller can track this voice slot
  g_Spu.m_ActiveSounds[voice_slot].m_SoundRefPtr = pSoundRefOut;

  if (pSoundRefOut != 0) {

    *pSoundRefOut = voice_slot;

    // If the sound loops, flag it (But only if we have a reference out? Lol)
    if (g_Spu.m_SoundDefinitions[pSoundId].m_LoopAddr != 0)
      g_Spu.m_ActiveSounds[voice_slot].m_Flags |= 0x100;
  }

  return 0;
}

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
int SoundsUpdate(void) {
  SpuVoiceAttr voiceAttr;
  Vector3D vecDiff;
  unsigned char cameraAngle;
  int distance;
  int maxDistance;
  int voicesToStop;
  char angle;
  int i;

  voicesToStop = 0;

  // Get camera rotation (scaled down by 16)
  cameraAngle = g_Camera.m_Rotation.z >> 4;

  for (i = 0; i < 24; i++) {
    u_char keyStatus;

    // Check if sound is marked for removal
    if (g_Spu.m_ActiveSounds[i].m_Flags & 0x40) {
      g_Spu.m_ActiveSounds[i].m_Flags = 0;
      continue;
    }

    if (!(g_Spu.m_ActiveSounds[i].m_Flags & 0x1)) {
      continue;
    }

    // Get SPU voice key status
    keyStatus = SpuGetKeyStatus(1 << i);

    // Handle sound state transitions
    if ((g_Spu.m_ActiveSounds[i].m_Flags & 0x2)) {
      // Sound was already playing
      if (keyStatus == SPU_RESET) {

        voicesToStop |= 1 << i;

        // Sound finished playing
        if (g_Spu.m_ActiveSounds[i].m_SoundRefPtr != nullptr) {
          *g_Spu.m_ActiveSounds[i].m_SoundRefPtr = 0x7F;
        }

        // Mark sound slot as free
        g_Spu.m_ActiveSounds[i].m_Flags = 0x40;
        g_Spu.m_ActiveSounds[i].m_SoundRefPtr = nullptr;
        g_Spu.m_ActiveSounds[i].m_Moby = nullptr;
        g_Spu.m_ActiveSounds[i].m_SoundId = 0xFF;
        continue;
      }

    } else {
      // Sound is starting or transitioning
      if (keyStatus == SPU_ON || keyStatus == SPU_RESET) {
        // Mark as playing
        g_Spu.m_ActiveSounds[i].m_Flags |= 0x2;
      }
    }

    // Check if.. uhm.. yeah
    if (!(g_Spu.m_ActiveSounds[i].m_Flags & 0x1)) {
      continue;
    }

    // Sound processing flags, I guess?
    switch (g_Spu.m_ActiveSounds[i].m_Flags & 0x1C) {
    case 0x4:
      // Static volume mode
      voiceAttr.volume.right = 0x2000;
      voiceAttr.volume.left = 0x2000;
      break;

    case 0x8: {
      // 3D positional audio

      // Get current voice volume
      SpuGetVoiceVolume(i, &g_Spu.m_ActiveSounds[i].m_StereoVolume.left,
                        &g_Spu.m_ActiveSounds[i].m_StereoVolume.right);

      // Calculate max audible distance from sound definition
      maxDistance = g_Spu.m_ActiveSounds[i].m_Moby->m_SoundDistance << 10;

      if (maxDistance == 0) {
        maxDistance = 0x4000;
      }

      // Calculate distance from camera to sound source
      VecSub(&vecDiff, &g_Spu.m_ActiveSounds[i].m_Moby->m_Position,
             &g_Camera.m_Position);
      distance = VecMagnitude(&vecDiff, 1);

      if (distance >= maxDistance) {
        // Sound is too far, fade it out
        voiceAttr.volume.right = g_Spu.m_ActiveSounds[i].m_StereoVolume.right =
            g_Spu.m_ActiveSounds[i].m_StereoVolume.right >> 1;
        voiceAttr.volume.left = g_Spu.m_ActiveSounds[i].m_StereoVolume.left =
            g_Spu.m_ActiveSounds[i].m_StereoVolume.left >> 1;

        // Stop sound if volume is too low
        if (voiceAttr.volume.right < 0x40 && voiceAttr.volume.left < 0x40) {
          voicesToStop |= 1 << i;

          // Sound finished playing
          if (g_Spu.m_ActiveSounds[i].m_SoundRefPtr != nullptr) {
            *g_Spu.m_ActiveSounds[i].m_SoundRefPtr = 0x7F;
          }

          // Mark sound slot as free
          g_Spu.m_ActiveSounds[i].m_Flags = 0x40;
          g_Spu.m_ActiveSounds[i].m_SoundRefPtr = nullptr;
          g_Spu.m_ActiveSounds[i].m_Moby = nullptr;
          g_Spu.m_ActiveSounds[i].m_SoundId = 0xFF;
          continue;
        }

        // Apply volume fade
        g_Spu.m_ActiveSounds[i].m_StereoVolume.left =
            (g_Spu.m_ActiveSounds[i].m_StereoVolume.left *
             g_Spu.m_SoundVolume) >>
            12;
        g_Spu.m_ActiveSounds[i].m_StereoVolume.right =
            (g_Spu.m_ActiveSounds[i].m_StereoVolume.right *
             g_Spu.m_SoundVolume) >>
            12;

        SpuSetVoiceVolume(i, g_Spu.m_ActiveSounds[i].m_StereoVolume.left,
                          g_Spu.m_ActiveSounds[i].m_StereoVolume.right);
        continue;
      } else {
        // Sound is in range, calculate stereo positioning
        angle = Atan2(g_Spu.m_ActiveSounds[i].m_Moby->m_Position.x -
                          g_Camera.m_Position.x,
                      g_Spu.m_ActiveSounds[i].m_Moby->m_Position.y -
                          g_Camera.m_Position.y,
                      0) -
                cameraAngle;

        func_80056C84(&voiceAttr.volume, distance, angle, maxDistance,
                      &g_Spu.m_ActiveSounds[i].m_Volume);
      }
      break;
    }

    case 0x10:
      // Use pre-calculated stereo volume
      voiceAttr.volume.right = g_Spu.m_ActiveSounds[i].m_StereoVolume.right;
      voiceAttr.volume.left = g_Spu.m_ActiveSounds[i].m_StereoVolume.left;
      break;

    default:
      break;
    }

    // Apply master sound volume
    voiceAttr.volume.left =
        FIXED_MUL(voiceAttr.volume.left, g_Spu.m_SoundVolume);
    voiceAttr.volume.right =
        FIXED_MUL(voiceAttr.volume.right, g_Spu.m_SoundVolume);

    // Set up voice attributes
    voiceAttr.voice = 1 << i;
    voiceAttr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR;

    // Apply pitch changes
    g_Spu.m_ActiveSounds[i].m_Pitch = g_Spu.m_ActiveSounds[i].m_Pitch +
                                      g_Spu.m_ActiveSounds[i].m_PitchIncrease;
    g_Spu.m_ActiveSounds[i].m_PitchIncrease = 0;

    // lol
    voiceAttr.mask |= SPU_VOICE_PITCH;
    voiceAttr.pitch = g_Spu.m_ActiveSounds[i].m_Pitch;

    // Update SPU voice
    SpuSetVoiceAttr(&voiceAttr);
  }

  g_Spu.m_StopVoice |= voicesToStop;
  return 0;
}

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
void KillOrphans(void) {
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
  if (g_GameTick % 64 == 0) {
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
