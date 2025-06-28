#ifndef __TITLESCREEN_H
#define __TITLESCREEN_H

#include <sys/types.h>

extern struct {
  int m_0x00; // State
  int m_0x04;
  int m_0x08;
  int m_0x0C;
  int m_0x10; // State 2?
  int m_0x14;
  int m_0x18;
  int m_0x1C;
  int m_0x20;
  int m_0x24;
  int m_0x28;
  int m_CardIdxChecking; // 0 or 1

  // McErrNone (Connected), McErrCardNotExist (Not connected)
  int m_CardStates[4];
  int m_CardCompletedFunc;
  int m_CardResultData;
  int m_0x48;
  void *m_0x4C;
  int m_0x50;
  int m_0x54;
  int m_0x58;
} g_TitlescreenState; // 0x5C in size

#endif