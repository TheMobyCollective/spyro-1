#ifndef __BUFFERS_H
#define __BUFFERS_H

extern struct {
  void *m_CopyBuf;
  void *m_DiscCopyBuf;
  void *m_ModelData;
  void *m_LevelScene;
  void *m_LowerPolyBuffer;
  void *m_HigherPolyBuffer;
  void *m_HudOTStart;
  void *m_WorldOTStart;
  void *m_ParticleSpaceStart;
  void *m_SharedAnimations;
  int m_LevelSceneOffset; // Bwahaha
  int m_LevelSceneSize;
} g_Buffers;

extern void *D_80075780; // Something skybox related

extern void *g_OverlaySpacePointer; // Pointer to overlay space

#endif
