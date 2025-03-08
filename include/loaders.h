#ifndef __LOADERS_H
#define __LOADERS_H

#include <sys/types.h>

extern int D_800758AC;  // Portal level id
extern int g_LoadStage; // Load stage
extern int D_8007566C;  // Cutscene type

extern int D_800756D0; // Has level transition
extern int D_800756B0; // Show transition text
extern int D_800756AC; // Ticks in level transition

void func_80014564(void); // Load titlescreen

void func_80015370(int); // Load level

typedef struct {
  u_int m_0x00;
  u_int m_0x04;
  u_int m_0x08;
  int nMobyCount;
  void *m_0x10;
  void *m_0x14[1]; // TODO - how many of these?
} CutsceneLayout;

extern CutsceneLayout *D_80075680;

extern int D_8007637C[249];

#endif