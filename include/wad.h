#ifndef __WAD_H_
#define __WAD_H_

typedef struct {
  int m_Offset;
  int m_Length;
} OffsetLength;

enum CutsceneType {
  Cutscene_Titlescreen = 0,
  Cutscene_Intro = 1,
  Cutscene_Outro1 = 2,
  Cutscene_Outro2 = 3
};

// TODO: PETE.WAD
extern struct {
  OffsetLength m_UniversalLogo;
  OffsetLength m_wad1;

  OffsetLength m_TitleScreenOverlay;

  OffsetLength m_CutsceneData[4]; //CutsceneType

  OffsetLength m_wad8;
  OffsetLength m_wad9;

  struct {
    OffsetLength m_Overlay;
    OffsetLength m_Data;
  } m_LevelEntry[36]; // Last entry is empty

  OffsetLength m_CreditsOverlay;

  OffsetLength m_Credits1Data[10];
  OffsetLength m_Credits2Data[10];

} g_WadHeader;

typedef struct {
  int m_VramSramOffset;
  int m_VramSramSize;
  int m_SceneOffset;
  int m_SceneSize;
  int m_ModelDataOffset;
  int m_ModelDataSize;
  int m_LayoutOffset;
  int m_LayoutSize;
  OffsetLength m_Dragons[6];
  int m_ModelOffsets[64];
  short m_ModelIndices[64];
} LevelHeader;

extern LevelHeader g_LevelHeader;

#endif