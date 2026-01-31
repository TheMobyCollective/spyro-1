#ifndef __BALLOONIST_H
#define __BALLOONIST_H

#include <sys/types.h>

#include "moby.h"

// Balloonist struct
extern struct {
  int m_State;
  int unk_0x04;
  int unk_0x08;
  int m_DialogueId;
  int m_DialogueTopStr;
  int m_Homeworld;
  Vector3D unk_0x18;
  Vector3D unk_0x2C;
  int unk_0x30;
  int unk_0x34;
  int unk_0x38;
  int unk_0x3c;
  int unk_0x40;
  Vector3D unk_0x44;
  int unk_0x50;
  int unk_0x54;
  int unk_0x58;
  int unk_0x5C[2];
  Moby *m_BalloonistMoby;
  Moby *m_BalloonMoby;
} D_800777E8;

#endif
