#ifndef __BALLOONIST_H
#define __BALLOONIST_H

#include <sys/types.h>

#include "moby.h"

// Balloonist struct
struct {
  int m_State;
  int unk_0x04;
  int unk_0x08;
  int m_DialogueId;
  int m_DialogueTopStr;
  int m_Homeworld;
  int unk_0x18[8];
  int unk_0x38;
  int unk_0x3c;
  int unk_0x40;
  int unk_0x44[3];
  int unk_0x50;
  int unk_0x54;
  int unk_0x58;
  int unk_0x5C[2];
  Moby *m_BalloonistMoby;
  Moby *m_BalloonMoby;
} D_800777E8;

#endif