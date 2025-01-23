#ifndef __CYCLORAMA_H
#define __CYCLORAMA_H

#include <sys/types.h>

extern struct {
  int m_SectorCount;
  void *m_Sectors; // TODO: Type
  int m_OcclusionGroupsCount;
  void *m_OcclusionGroups; // TODO: Type
  struct {
    u_char r, g, b, s;
  } m_BackgroundColor;
} D_80078A40;

#endif