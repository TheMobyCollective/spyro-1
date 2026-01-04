#ifndef __SPU_H
#define __SPU_H

#include <sys/types.h>

#include <libspu.h>

#include "moby.h"
#include "sound_table.h"

// Mixed sounds and music stuff

typedef struct {
  Moby *m_Moby;

  SpuVolume m_StereoVolume; // Transformed m_Volume to stereo based on the
                            // position of the Moby

  u_int m_Pitch;

  u_char unk_0xC;
  u_char m_SoundId;
  u_short m_Flags;

  SpuVolume m_Volume;

  int m_PitchIncrease;

  u_char *m_SoundRefPtr; // Pointer to a flag that is set when the sound is
                         // done playing
} ActiveSound;

typedef struct {
  u_long m_Addr;
  u_long m_LoopAddr; // Saved but completely unnecessary
  short unk_0x8;     // Named unusedVolume in my notes
  u_short m_Pitch;
  u_short m_PitchVariance;
  short m_PitchMultiplier;

  // 0: Positive and negative pitch variance
  // 1: Only positive pitch variance
  // 2: Only negative pitch variance
  int m_VarianceType;
} SoundDefinition;

extern struct {
  SpuCommonAttr m_CommonAttr;
  ActiveSound m_ActiveSounds[24];

  SoundDefinition *m_SoundDefinitions;
  SoundTable *m_SoundTable;

  int m_MusicFadeTarget;
  int m_NextSoundOverrideFlags;

  int unk_0x2d8;              // No XREFs
  int unk_0x2dc;              // No XREFs
  SpuVolume m_VolumeOverride; // Used when m_NextSoundOverrideFlags & 1
  int unk_0x2e4;              // No XREFs
  int unk_0x2e8;              // No XREFs

  u_short m_PitchOverride; // Overrides the pitch of the next sound
  u_char unk_0x2ee[46];    // No XREFs

  int m_MusicVolume;
  int unk_0x320;
  int m_SoundVolume;

  int m_MusicFadeCurrent;
  int m_SoundTableSize;

  int m_PlayVoice;
  int m_StopVoice;

  int m_AudioMono;

  int unk_0x33c; // No XREFs
} g_Spu;

/// @brief Initializes the sound system
void SpuInitialize(void);

/// @brief Plays a sound
void PlaySound(u_int pSoundId, Moby *pMoby, u_int pFlags, u_char *pSoundRefOut);

/// @brief Stops a sound
void StopSound(u_int pVoice, u_int pType);

/// @brief Stops all sounds made by a Moby
void func_800562A4(Moby *pMoby, u_int pType);

/// @brief Update sounds
void func_8005637C(void);

/// @brief Set music state
void func_800567F4(int pSong, int pFlags);

/// @brief Stops all sounds and music, except for the voices that are skipped
void func_80056B28(int pSkipVoices);

/// @brief Stereo sound calculation
void func_80056C84(SpuVolume *pVolumeOut, u_int pDistance, u_char pAngleToSound,
                   u_int pMaxDistance, SpuVolume *pVolumeIn);

/// @brief Is moby playing this sound?
int IsMobyPlayingSound(Moby *pMoby, u_int pSoundId);

/// @brief Updates the SPU voices
void SpuUpdate(void);

// static_assert(sizeof(g_Spu) == 0x340);

#endif
