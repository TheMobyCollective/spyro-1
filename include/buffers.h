#ifndef __BUFFERS_H
#define __BUFFERS_H

extern struct {
  void *m_CopyBuf;
  void *m_DiscCopyBuf;
  void *m_EndOfSceneData; // TODO: Rename?
  void *m_LevelLayout;
  void *m_LowerPolyBuffer;
  void *m_HigherPolyBuffer;
  void *m_HudOTStart;
  void *m_WorldOTStart;
  void *m_ParticleSpaceStart;
  void *m_SharedAnimations;
  int m_LevelLayoutOffset; // Bwahaha
  int m_LevelLayoutSize;
} D_800785D8;

extern void *D_80075780; // Something skybox related

#endif