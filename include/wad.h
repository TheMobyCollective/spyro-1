#ifndef __WAD_H_
#define __WAD_H_

extern struct {
  // struct {
  //   int offset, size;
  // } m_entry[102];
  int m_entry[102][2]; // Struct does not match (func_800144C8)
} D_8007A6D0;

#define WAD_OFFSET(x) D_8007A6D0.m_entry[x][0]
#define WAD_SIZE(x) D_8007A6D0.m_entry[x][1]

typedef struct {
  int m_VramSramOffset;
  int m_VramSramSize;
  int m_SceneOffset;
  int m_SceneSize;
  int m_ModelDataOffset;
  int m_ModelDataSize;
  int m_LayoutOffset;
  int m_LayoutSize;
  struct {
    int offset, size;
  } m_Dragons[6];
  int m_ModelOffsets[64];
  short m_ModelIndices[64];
} LevelHeader;

LevelHeader D_80076C00;

#endif