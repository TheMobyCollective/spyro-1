#ifndef __CYCLORAMA_H
#define __CYCLORAMA_H

#include <sys/types.h>

typedef struct {
  int m_SectorCount;
  void *m_Sectors; // TODO: Type
  int m_OcclusionGroupsCount;
  void *m_OcclusionGroups; // TODO: Type
  struct {
    u_char r, g, b, s;
  } m_BackgroundColor;
} Cyclorama;

extern Cyclorama g_Cyclorama;

extern Cyclorama g_NewCyclorama;

#endif