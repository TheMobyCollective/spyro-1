#include "overlay_pointers.h"
#include "buffers.h"
#include "common.h"
#include "moby.h"

extern void *main_BSS_END;

// This is placed into sdata, but I think this is cleaner than having an
// assembly file
void *g_OverlaySpacePointer = &main_BSS_END;

// TODO: This file is fucked up

/// Unused levels

// Level 0
void func_level_0_80082068();
Moby *func_level_0_80080548();
void func_level_0_8007D8E0();
void func_level_0_80081568();
void func_level_0_80080A0C();
void func_level_0_8007ADB8();
void func_level_0_8007AEF4();
void func_level_0_8007AF38();
void func_level_0_8007CED8();

// Level 1
void func_level_1_8007BFF0();
Moby *func_level_1_8007B070();
void func_level_1_8007AC8C();
void func_level_1_8007B8AC();
void func_level_1_8007B144();

// Level 2
void func_level_2_8007F490();
Moby *func_level_2_8007D970();
void func_level_2_8007AD08();
void func_level_2_8007E990();
void func_level_2_8007DE34();

// Level 3
void func_level_3_8007C7B0();
Moby *func_level_3_8007B0AC();
void func_level_3_8007ACC8();
void func_level_3_8007BC50();
void func_level_3_8007B180();

// Level 4
void func_level_4_8007C204();
Moby *func_level_4_8007B08C();
void func_level_4_8007ACA8();
void func_level_4_8007B9F0();
void func_level_4_8007B160();

// Level 7
void func_level_7_8007F2F4();
Moby *func_level_7_8007D970();
void func_level_7_8007AD08();
void func_level_7_8007E8E4();
void func_level_7_8007DE34();

// Level 9
void func_level_9_8007C204();
Moby *func_level_9_8007B08C();
void func_level_9_8007ACA8();
void func_level_9_8007B9F0();
void func_level_9_8007B160();

// Level 99
void func_level_99_8007C654();
Moby *func_level_99_8007B0C0();
void func_level_99_8007ACDC();
void func_level_99_8007BC44();
void func_level_99_8007B194();

/// Normal levels

// Level 10
void func_level_10_80088620();
Moby *func_level_10_800857CC();
void func_level_10_8007D9C8();
void func_level_10_800873E0();
void func_level_10_80086134();
void func_level_10_8007AEA0();
void func_level_10_8007AFDC();
void func_level_10_8007B020();
void func_level_10_8007CFC0();

// Level 11
void func_level_11_8008A3B8();
Moby *func_level_11_8008772C();
void func_level_11_8007DA78();
void func_level_11_800892C4();
void func_level_11_80088098();
void func_level_11_8007AF50();
void func_level_11_8007B08C();
void func_level_11_8007B0D0();
void func_level_11_8007D070();

// Level 12
void func_level_12_80085594();
Moby *func_level_12_80082960();
void func_level_12_8007AE40();
void func_level_12_800844A0();
void func_level_12_80083274();

// Level 13
void func_level_13_80089ECC();
Moby *func_level_13_800872A4();
void func_level_13_8007DA54();
void func_level_13_80088F68();
void func_level_13_80087E20();
void func_level_13_8007AF2C();
void func_level_13_8007B068();
void func_level_13_8007B0AC();
void func_level_13_8007D04C();

// Level 14
void func_level_14_80084A10();
Moby *func_level_14_80081DA8();
void func_level_14_8007AF94();
void func_level_14_8008391C();
void func_level_14_800826F0();

// Level 15
void func_level_15_80084ED0();
Moby *func_level_15_8008249C();
void func_level_15_8007CFB4();
void func_level_15_80084128();
void func_level_15_80083330();
void func_level_15_8007AE08();
void func_level_15_8007AEDC();
void func_level_15_8007B1FC();
void func_level_15_8007B68C();
void func_level_15_8007B4B0();

// Level 20
void func_level_20_8008CFA4();
Moby *func_level_20_8008A258();
void func_level_20_8007E3A0();
void func_level_20_8008BFF0();
void func_level_20_8008AE28();
void func_level_20_8007B878();
void func_level_20_8007B9B4();
void func_level_20_8007B9F8();
void func_level_20_8007D998();

// Level 21
void func_level_21_8008D600();
Moby *func_level_21_8008A4D0();
void func_level_21_8007E240();
void func_level_21_8008C540();
void func_level_21_8008B1C0();
void func_level_21_8007B718();
void func_level_21_8007B854();
void func_level_21_8007B898();
void func_level_21_8007D838();

// Level 22
void func_level_22_8008BAF8();
Moby *func_level_22_80088B88();
void func_level_22_8007E240();
void func_level_22_8008A9A8();
void func_level_22_80089714();
void func_level_22_8007B718();
void func_level_22_8007B854();
void func_level_22_8007B898();
void func_level_22_8007D838();

// Level 23
void func_level_23_80086260();
Moby *func_level_23_80083608();
void func_level_23_8007B4C8();
void func_level_23_80085184();
void func_level_23_80083F2C();

// Level 24
void func_level_24_80087210();
Moby *func_level_24_800845F0();
void func_level_24_8007AEB8();
void func_level_24_8008611C();
void func_level_24_80084EF0();

// Level 25
void func_level_25_80083BF0();
Moby *func_level_25_800819BC();
void func_level_25_8007CFB4();
void func_level_25_80082F58();
void func_level_25_80082300();
void func_level_25_8007AE08();
void func_level_25_8007AEDC();
void func_level_25_8007B1FC();
void func_level_25_8007B68C();
void func_level_25_8007B4B0();

// Level 30
void func_level_30_8008E608();
Moby *func_level_30_8008B2C0();
void func_level_30_8007E398();
void func_level_30_8008D2D0();
void func_level_30_8008BE98();
void func_level_30_8007B870();
void func_level_30_8007B9AC();
void func_level_30_8007B9F0();
void func_level_30_8007D990();

// Level 31
void func_level_31_8008DEC0();
Moby *func_level_31_8008A36C();
void func_level_31_8007BB00();
void func_level_31_8008C9D8();
void func_level_31_8008AF54();

// Level 32
void func_level_32_8008C73C();
Moby *func_level_32_8008883C();
void func_level_32_8007B64C();
void func_level_32_8008B0B0();
void func_level_32_80089454();

// Level 33
void func_level_33_8008A8A0();
Moby *func_level_33_80086DD8();
void func_level_33_8007B7A8();
void func_level_33_80089450();
void func_level_33_80087B40();

// Level 34
void func_level_34_8008749C();
Moby *func_level_34_80083AB4();
void func_level_34_8007AF28();
void func_level_34_80085F40();
void func_level_34_80084830();

// Level 35
void func_level_35_80084390();
Moby *func_level_35_80081F0C();
void func_level_35_8007CFB4();
void func_level_35_800836F8();
void func_level_35_80082AA0();
void func_level_35_8007AE08();
void func_level_35_8007AEDC();
void func_level_35_8007B1FC();
void func_level_35_8007B68C();
void func_level_35_8007B4B0();

// Level 40
void func_level_40_8008AB70();
Moby *func_level_40_80087EF0();
void func_level_40_8007E18C();
void func_level_40_80089AB8();
void func_level_40_800888F8();
void func_level_40_8007B664();
void func_level_40_8007B7A0();
void func_level_40_8007B7E4();
void func_level_40_8007D784();

// Level 41
void func_level_41_80087944();
Moby *func_level_41_8008465C();
void func_level_41_8007B5DC();
void func_level_41_800866D8();
void func_level_41_800853AC();

// Level 42
void func_level_42_80087130();
Moby *func_level_42_80084718();
void func_level_42_8007AFBC();
void func_level_42_800861CC();
void func_level_42_80085084();

// Level 43
void func_level_43_80089848();
Moby *func_level_43_80086B38();
void func_level_43_8007B698();
void func_level_43_8008869C();
void func_level_43_80087400();

// Level 44
void func_level_44_8008A69C();
Moby *func_level_44_800874FC();
void func_level_44_8007B770();
void func_level_44_800894B0();
void func_level_44_80088178();

// Level 45
void func_level_45_80084844();
Moby *func_level_45_8008223C();
void func_level_45_8007CFB4();
void func_level_45_80083BAC();
void func_level_45_80082F54();
void func_level_45_8007AE08();
void func_level_45_8007AEDC();
void func_level_45_8007B1FC();
void func_level_45_8007B68C();
void func_level_45_8007B4B0();

// Level 50
void func_level_50_8008BB38();
Moby *func_level_50_80088E24();
void func_level_50_8007E3C0();
void func_level_50_8008AA24();
void func_level_50_800897FC();
void func_level_50_8007B898();
void func_level_50_8007B9D4();
void func_level_50_8007BA18();
void func_level_50_8007D9B8();

// Level 51
void func_level_51_800880D4();
Moby *func_level_51_80084B94();
void func_level_51_8007B4F8();
void func_level_51_80086D38();
void func_level_51_800857FC();

// Level 52
void func_level_52_8008771C();
Moby *func_level_52_80084620();
void func_level_52_8007B4DC();
void func_level_52_80086438();
void func_level_52_800850A0();

// Level 53
void func_level_53_80089820();
Moby *func_level_53_8008590C();
void func_level_53_8007B510();
void func_level_53_800881D8();
void func_level_53_80086754();

// Level 54
void func_level_54_80086348();
Moby *func_level_54_800836A8();
void func_level_54_8007AF50();
void func_level_54_80085254();
void func_level_54_80084028();

// Level 55
void func_level_55_80084934();
Moby *func_level_55_80082028();
void func_level_55_8007CFB4();
void func_level_55_80083B8C();
void func_level_55_80082D94();
void func_level_55_8007AE08();
void func_level_55_8007AEDC();
void func_level_55_8007B1FC();
void func_level_55_8007B68C();
void func_level_55_8007B4B0();

// Level 60
void func_level_60_80085CE0();
Moby *func_level_60_80083568();
void func_level_60_8007D938();
void func_level_60_80084EA0();
void func_level_60_80083ED8();
void func_level_60_8007AE10();
void func_level_60_8007AF4C();
void func_level_60_8007AF90();
void func_level_60_8007CF30();

// Level 61
void func_level_61_80088668();
Moby *func_level_61_80085664();
void func_level_61_8007B528();
void func_level_61_8008747C();
void func_level_61_80086144();

// Level 62
void func_level_62_80086004();
Moby *func_level_62_80083108();
void func_level_62_8007AE5C();
void func_level_62_80084EAC();
void func_level_62_80083B4C();

// Level 63
void func_level_63_800854B4();
Moby *func_level_63_80082F24();
void func_level_63_8007AD64();
void func_level_63_80084634();
void func_level_63_800836F0();

// Level 64
void func_level_64_80086264();
Moby *func_level_64_80083690();
void func_level_64_8007AD4C();
void func_level_64_80085230();
void func_level_64_800840FC();

// TODO: In the future, turn this into a preprocessor macro.

void func_8005A470(void) {
  switch (g_LevelId) {
  case 0:
    g_Buffers.m_CopyBuf = func_level_0_80082068; // g_CopyBufferPointer
    g_SpawnMoby = func_level_0_80080548;         // g_SpawnMoby
    g_UpdateMoby = func_level_0_8007D8E0;        // g_UpdateMoby
    D_800758E4 = func_level_0_80081568;          // g_SpawnParticle
    g_UpdateParticle = func_level_0_80080A0C;    // g_UpdateParticle
    D_800757A0 = func_level_0_8007ADB8;          // g_BalloonistTriggerCode
    D_800758A8 = func_level_0_8007AEF4;          // g_BalloonistCloseDialogue
    D_8007574C = func_level_0_8007AF38;          // g_BalloonistCameraCode
    D_800758D8 = func_level_0_8007CED8;          // g_BalloonistTalkCode
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 1:
    g_Buffers.m_CopyBuf = func_level_1_8007BFF0; // g_CopyBufferPointer
    g_SpawnMoby = func_level_1_8007B070;         // g_SpawnMoby
    g_UpdateMoby = func_level_1_8007AC8C;        // g_UpdateMoby
    D_800758E4 = func_level_1_8007B8AC;          // g_SpawnParticle
    g_UpdateParticle = func_level_1_8007B144;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 2:
    g_Buffers.m_CopyBuf = func_level_2_8007F490; // g_CopyBufferPointer
    g_SpawnMoby = func_level_2_8007D970;         // g_SpawnMoby
    g_UpdateMoby = func_level_2_8007AD08;        // g_UpdateMoby
    D_800758E4 = func_level_2_8007E990;          // g_SpawnParticle
    g_UpdateParticle = func_level_2_8007DE34;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 3:
    g_Buffers.m_CopyBuf = func_level_3_8007C7B0; // g_CopyBufferPointer
    g_SpawnMoby = func_level_3_8007B0AC;         // g_SpawnMoby
    g_UpdateMoby = func_level_3_8007ACC8;        // g_UpdateMoby
    D_800758E4 = func_level_3_8007BC50;          // g_SpawnParticle
    g_UpdateParticle = func_level_3_8007B180;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 4:
    g_Buffers.m_CopyBuf = func_level_4_8007C204; // g_CopyBufferPointer
    g_SpawnMoby = func_level_4_8007B08C;         // g_SpawnMoby
    g_UpdateMoby = func_level_4_8007ACA8;        // g_UpdateMoby
    D_800758E4 = func_level_4_8007B9F0;          // g_SpawnParticle
    g_UpdateParticle = func_level_4_8007B160;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 7:
    g_Buffers.m_CopyBuf = func_level_7_8007F2F4; // g_CopyBufferPointer
    g_SpawnMoby = func_level_7_8007D970;         // g_SpawnMoby
    g_UpdateMoby = func_level_7_8007AD08;        // g_UpdateMoby
    D_800758E4 = func_level_7_8007E8E4;          // g_SpawnParticle
    g_UpdateParticle = func_level_7_8007DE34;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 9:
    g_Buffers.m_CopyBuf = func_level_9_8007C204; // g_CopyBufferPointer
    g_SpawnMoby = func_level_9_8007B08C;         // g_SpawnMoby
    g_UpdateMoby = func_level_9_8007ACA8;        // g_UpdateMoby
    D_800758E4 = func_level_9_8007B9F0;          // g_SpawnParticle
    g_UpdateParticle = func_level_9_8007B160;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 10:
    g_Buffers.m_CopyBuf = func_level_10_80088620; // g_CopyBufferPointer
    g_SpawnMoby = SpawnMoby_level_10;             // g_SpawnMoby
    g_UpdateMoby = func_level_10_8007D9C8;        // g_UpdateMoby
    D_800758E4 = func_level_10_800873E0;          // g_SpawnParticle
    g_UpdateParticle = func_level_10_80086134;    // g_UpdateParticle
    D_800757A0 = func_level_10_8007AEA0;          // g_BalloonistTriggerCode
    D_800758A8 = func_level_10_8007AFDC;          // g_BalloonistCloseDialogue
    D_8007574C = func_level_10_8007B020;          // g_BalloonistCameraCode
    D_800758D8 = func_level_10_8007CFC0;          // g_BalloonistTalkCode
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 11:
    g_Buffers.m_CopyBuf = func_level_11_8008A3B8; // g_CopyBufferPointer
    g_SpawnMoby = SpawnMoby_level_11;             // g_SpawnMoby
    g_UpdateMoby = func_level_11_8007DA78;        // g_UpdateMoby
    D_800758E4 = func_level_11_800892C4;          // g_SpawnParticle
    g_UpdateParticle = func_level_11_80088098;    // g_UpdateParticle
    D_800757A0 = func_level_11_8007AF50;          // g_BalloonistTriggerCode
    D_800758A8 = func_level_11_8007B08C;          // g_BalloonistCloseDialogue
    D_8007574C = func_level_11_8007B0D0;          // g_BalloonistCameraCode
    D_800758D8 = func_level_11_8007D070;          // g_BalloonistTalkCode
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 12:
    g_Buffers.m_CopyBuf = func_level_12_80085594; // g_CopyBufferPointer
    g_SpawnMoby = SpawnMoby_level_12;             // g_SpawnMoby
    g_UpdateMoby = func_level_12_8007AE40;        // g_UpdateMoby
    D_800758E4 = func_level_12_800844A0;          // g_SpawnParticle
    g_UpdateParticle = func_level_12_80083274;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 13:
    g_Buffers.m_CopyBuf = func_level_13_80089ECC; // g_CopyBufferPointer
    g_SpawnMoby = SpawnMoby_level_13;             // g_SpawnMoby
    g_UpdateMoby = func_level_13_8007DA54;        // g_UpdateMoby
    D_800758E4 = func_level_13_80088F68;          // g_SpawnParticle
    g_UpdateParticle = func_level_13_80087E20;    // g_UpdateParticle
    D_800757A0 = func_level_13_8007AF2C;          // g_BalloonistTriggerCode
    D_800758A8 = func_level_13_8007B068;          // g_BalloonistCloseDialogue
    D_8007574C = func_level_13_8007B0AC;          // g_BalloonistCameraCode
    D_800758D8 = func_level_13_8007D04C;          // g_BalloonistTalkCode
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 14:
    g_Buffers.m_CopyBuf = func_level_14_80084A10; // g_CopyBufferPointer
    g_SpawnMoby = SpawnMoby_level_14;             // g_SpawnMoby
    g_UpdateMoby = func_level_14_8007AF94;        // g_UpdateMoby
    D_800758E4 = func_level_14_8008391C;          // g_SpawnParticle
    g_UpdateParticle = func_level_14_800826F0;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 15:
    g_Buffers.m_CopyBuf = func_level_15_80084ED0; // g_CopyBufferPointer
    g_SpawnMoby = func_level_15_8008249C;         // g_SpawnMoby
    g_UpdateMoby = func_level_15_8007CFB4;        // g_UpdateMoby
    D_800758E4 = func_level_15_80084128;          // g_SpawnParticle
    g_UpdateParticle = func_level_15_80083330;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    D_80075694 = func_level_15_8007AE08;            // g_UnkFunc1Flight
    D_800757A8 = func_level_15_8007AEDC;            // g_UnkFunc2Flight
    g_FlightResultsUpdate = func_level_15_8007B1FC; // g_UpdateGameState7
    D_8007567C = func_level_15_8007B68C;            // g_DrawGameState7
    D_800758C4 = func_level_15_8007B4B0;            // g_DrawTime
    break;
  case 20:
    g_Buffers.m_CopyBuf = func_level_20_8008CFA4; // g_CopyBufferPointer
    g_SpawnMoby = func_level_20_8008A258;         // g_SpawnMoby
    g_UpdateMoby = func_level_20_8007E3A0;        // g_UpdateMoby
    D_800758E4 = func_level_20_8008BFF0;          // g_SpawnParticle
    g_UpdateParticle = func_level_20_8008AE28;    // g_UpdateParticle
    D_800757A0 = func_level_20_8007B878;          // g_BalloonistTriggerCode
    D_800758A8 = func_level_20_8007B9B4;          // g_BalloonistCloseDialogue
    D_8007574C = func_level_20_8007B9F8;          // g_BalloonistCameraCode
    D_800758D8 = func_level_20_8007D998;          // g_BalloonistTalkCode
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 21:
    g_Buffers.m_CopyBuf = func_level_21_8008D600; // g_CopyBufferPointer
    g_SpawnMoby = func_level_21_8008A4D0;         // g_SpawnMoby
    g_UpdateMoby = func_level_21_8007E240;        // g_UpdateMoby
    D_800758E4 = func_level_21_8008C540;          // g_SpawnParticle
    g_UpdateParticle = func_level_21_8008B1C0;    // g_UpdateParticle
    D_800757A0 = func_level_21_8007B718;          // g_BalloonistTriggerCode
    D_800758A8 = func_level_21_8007B854;          // g_BalloonistCloseDialogue
    D_8007574C = func_level_21_8007B898;          // g_BalloonistCameraCode
    D_800758D8 = func_level_21_8007D838;          // g_BalloonistTalkCode
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 22:
    g_Buffers.m_CopyBuf = func_level_22_8008BAF8; // g_CopyBufferPointer
    g_SpawnMoby = func_level_22_80088B88;         // g_SpawnMoby
    g_UpdateMoby = func_level_22_8007E240;        // g_UpdateMoby
    D_800758E4 = func_level_22_8008A9A8;          // g_SpawnParticle
    g_UpdateParticle = func_level_22_80089714;    // g_UpdateParticle
    D_800757A0 = func_level_22_8007B718;          // g_BalloonistTriggerCode
    D_800758A8 = func_level_22_8007B854;          // g_BalloonistCloseDialogue
    D_8007574C = func_level_22_8007B898;          // g_BalloonistCameraCode
    D_800758D8 = func_level_22_8007D838;          // g_BalloonistTalkCode
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 23:
    g_Buffers.m_CopyBuf = func_level_23_80086260; // g_CopyBufferPointer
    g_SpawnMoby = func_level_23_80083608;         // g_SpawnMoby
    g_UpdateMoby = func_level_23_8007B4C8;        // g_UpdateMoby
    D_800758E4 = func_level_23_80085184;          // g_SpawnParticle
    g_UpdateParticle = func_level_23_80083F2C;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 24:
    g_Buffers.m_CopyBuf = func_level_24_80087210; // g_CopyBufferPointer
    g_SpawnMoby = func_level_24_800845F0;         // g_SpawnMoby
    g_UpdateMoby = func_level_24_8007AEB8;        // g_UpdateMoby
    D_800758E4 = func_level_24_8008611C;          // g_SpawnParticle
    g_UpdateParticle = func_level_24_80084EF0;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 25:
    g_Buffers.m_CopyBuf = func_level_25_80083BF0; // g_CopyBufferPointer
    g_SpawnMoby = func_level_25_800819BC;         // g_SpawnMoby
    g_UpdateMoby = func_level_25_8007CFB4;        // g_UpdateMoby
    D_800758E4 = func_level_25_80082F58;          // g_SpawnParticle
    g_UpdateParticle = func_level_25_80082300;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    D_80075694 = func_level_25_8007AE08;            // g_UnkFunc1Flight
    D_800757A8 = func_level_25_8007AEDC;            // g_UnkFunc2Flight
    g_FlightResultsUpdate = func_level_25_8007B1FC; // g_UpdateGameState7
    D_8007567C = func_level_25_8007B68C;            // g_DrawGameState7
    D_800758C4 = func_level_25_8007B4B0;            // g_DrawTime
    break;
  case 30:
    g_Buffers.m_CopyBuf = func_level_30_8008E608; // g_CopyBufferPointer
    g_SpawnMoby = func_level_30_8008B2C0;         // g_SpawnMoby
    g_UpdateMoby = func_level_30_8007E398;        // g_UpdateMoby
    D_800758E4 = func_level_30_8008D2D0;          // g_SpawnParticle
    g_UpdateParticle = func_level_30_8008BE98;    // g_UpdateParticle
    D_800757A0 = func_level_30_8007B870;          // g_BalloonistTriggerCode
    D_800758A8 = func_level_30_8007B9AC;          // g_BalloonistCloseDialogue
    D_8007574C = func_level_30_8007B9F0;          // g_BalloonistCameraCode
    D_800758D8 = func_level_30_8007D990;          // g_BalloonistTalkCode
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 31:
    g_Buffers.m_CopyBuf = func_level_31_8008DEC0; // g_CopyBufferPointer
    g_SpawnMoby = func_level_31_8008A36C;         // g_SpawnMoby
    g_UpdateMoby = func_level_31_8007BB00;        // g_UpdateMoby
    D_800758E4 = func_level_31_8008C9D8;          // g_SpawnParticle
    g_UpdateParticle = func_level_31_8008AF54;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 32:
    g_Buffers.m_CopyBuf = func_level_32_8008C73C; // g_CopyBufferPointer
    g_SpawnMoby = func_level_32_8008883C;         // g_SpawnMoby
    g_UpdateMoby = func_level_32_8007B64C;        // g_UpdateMoby
    D_800758E4 = func_level_32_8008B0B0;          // g_SpawnParticle
    g_UpdateParticle = func_level_32_80089454;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 33:
    g_Buffers.m_CopyBuf = func_level_33_8008A8A0; // g_CopyBufferPointer
    g_SpawnMoby = func_level_33_80086DD8;         // g_SpawnMoby
    g_UpdateMoby = func_level_33_8007B7A8;        // g_UpdateMoby
    D_800758E4 = func_level_33_80089450;          // g_SpawnParticle
    g_UpdateParticle = func_level_33_80087B40;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 34:
    g_Buffers.m_CopyBuf = func_level_34_8008749C; // g_CopyBufferPointer
    g_SpawnMoby = func_level_34_80083AB4;         // g_SpawnMoby
    g_UpdateMoby = func_level_34_8007AF28;        // g_UpdateMoby
    D_800758E4 = func_level_34_80085F40;          // g_SpawnParticle
    g_UpdateParticle = func_level_34_80084830;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 35:
    g_Buffers.m_CopyBuf = func_level_35_80084390; // g_CopyBufferPointer
    g_SpawnMoby = func_level_35_80081F0C;         // g_SpawnMoby
    g_UpdateMoby = func_level_35_8007CFB4;        // g_UpdateMoby
    D_800758E4 = func_level_35_800836F8;          // g_SpawnParticle
    g_UpdateParticle = func_level_35_80082AA0;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    D_80075694 = func_level_35_8007AE08;            // g_UnkFunc1Flight
    D_800757A8 = func_level_35_8007AEDC;            // g_UnkFunc2Flight
    g_FlightResultsUpdate = func_level_35_8007B1FC; // g_UpdateGameState7
    D_8007567C = func_level_35_8007B68C;            // g_DrawGameState7
    D_800758C4 = func_level_35_8007B4B0;            // g_DrawTime
    break;
  case 40:
    g_Buffers.m_CopyBuf = func_level_40_8008AB70; // g_CopyBufferPointer
    g_SpawnMoby = func_level_40_80087EF0;         // g_SpawnMoby
    g_UpdateMoby = func_level_40_8007E18C;        // g_UpdateMoby
    D_800758E4 = func_level_40_80089AB8;          // g_SpawnParticle
    g_UpdateParticle = func_level_40_800888F8;    // g_UpdateParticle
    D_800757A0 = func_level_40_8007B664;          // g_BalloonistTriggerCode
    D_800758A8 = func_level_40_8007B7A0;          // g_BalloonistCloseDialogue
    D_8007574C = func_level_40_8007B7E4;          // g_BalloonistCameraCode
    D_800758D8 = func_level_40_8007D784;          // g_BalloonistTalkCode
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 41:
    g_Buffers.m_CopyBuf = func_level_41_80087944; // g_CopyBufferPointer
    g_SpawnMoby = func_level_41_8008465C;         // g_SpawnMoby
    g_UpdateMoby = func_level_41_8007B5DC;        // g_UpdateMoby
    D_800758E4 = func_level_41_800866D8;          // g_SpawnParticle
    g_UpdateParticle = func_level_41_800853AC;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 42:
    g_Buffers.m_CopyBuf = func_level_42_80087130; // g_CopyBufferPointer
    g_SpawnMoby = func_level_42_80084718;         // g_SpawnMoby
    g_UpdateMoby = func_level_42_8007AFBC;        // g_UpdateMoby
    D_800758E4 = func_level_42_800861CC;          // g_SpawnParticle
    g_UpdateParticle = func_level_42_80085084;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 43:
    g_Buffers.m_CopyBuf = func_level_43_80089848; // g_CopyBufferPointer
    g_SpawnMoby = func_level_43_80086B38;         // g_SpawnMoby
    g_UpdateMoby = func_level_43_8007B698;        // g_UpdateMoby
    D_800758E4 = func_level_43_8008869C;          // g_SpawnParticle
    g_UpdateParticle = func_level_43_80087400;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 44:
    g_Buffers.m_CopyBuf = func_level_44_8008A69C; // g_CopyBufferPointer
    g_SpawnMoby = func_level_44_800874FC;         // g_SpawnMoby
    g_UpdateMoby = func_level_44_8007B770;        // g_UpdateMoby
    D_800758E4 = func_level_44_800894B0;          // g_SpawnParticle
    g_UpdateParticle = func_level_44_80088178;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 45:
    g_Buffers.m_CopyBuf = func_level_45_80084844; // g_CopyBufferPointer
    g_SpawnMoby = func_level_45_8008223C;         // g_SpawnMoby
    g_UpdateMoby = func_level_45_8007CFB4;        // g_UpdateMoby
    D_800758E4 = func_level_45_80083BAC;          // g_SpawnParticle
    g_UpdateParticle = func_level_45_80082F54;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    D_80075694 = func_level_45_8007AE08;            // g_UnkFunc1Flight
    D_800757A8 = func_level_45_8007AEDC;            // g_UnkFunc2Flight
    g_FlightResultsUpdate = func_level_45_8007B1FC; // g_UpdateGameState7
    D_8007567C = func_level_45_8007B68C;            // g_DrawGameState7
    D_800758C4 = func_level_45_8007B4B0;            // g_DrawTime
    break;
  case 50:
    g_Buffers.m_CopyBuf = func_level_50_8008BB38; // g_CopyBufferPointer
    g_SpawnMoby = func_level_50_80088E24;         // g_SpawnMoby
    g_UpdateMoby = func_level_50_8007E3C0;        // g_UpdateMoby
    D_800758E4 = func_level_50_8008AA24;          // g_SpawnParticle
    g_UpdateParticle = func_level_50_800897FC;    // g_UpdateParticle
    D_800757A0 = func_level_50_8007B898;          // g_BalloonistTriggerCode
    D_800758A8 = func_level_50_8007B9D4;          // g_BalloonistCloseDialogue
    D_8007574C = func_level_50_8007BA18;          // g_BalloonistCameraCode
    D_800758D8 = func_level_50_8007D9B8;          // g_BalloonistTalkCode
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 51:
    g_Buffers.m_CopyBuf = func_level_51_800880D4; // g_CopyBufferPointer
    g_SpawnMoby = func_level_51_80084B94;         // g_SpawnMoby
    g_UpdateMoby = func_level_51_8007B4F8;        // g_UpdateMoby
    D_800758E4 = func_level_51_80086D38;          // g_SpawnParticle
    g_UpdateParticle = func_level_51_800857FC;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 52:
    g_Buffers.m_CopyBuf = func_level_52_8008771C; // g_CopyBufferPointer
    g_SpawnMoby = func_level_52_80084620;         // g_SpawnMoby
    g_UpdateMoby = func_level_52_8007B4DC;        // g_UpdateMoby
    D_800758E4 = func_level_52_80086438;          // g_SpawnParticle
    g_UpdateParticle = func_level_52_800850A0;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 53:
    g_Buffers.m_CopyBuf = func_level_53_80089820; // g_CopyBufferPointer
    g_SpawnMoby = func_level_53_8008590C;         // g_SpawnMoby
    g_UpdateMoby = func_level_53_8007B510;        // g_UpdateMoby
    D_800758E4 = func_level_53_800881D8;          // g_SpawnParticle
    g_UpdateParticle = func_level_53_80086754;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 54:
    g_Buffers.m_CopyBuf = func_level_54_80086348; // g_CopyBufferPointer
    g_SpawnMoby = func_level_54_800836A8;         // g_SpawnMoby
    g_UpdateMoby = func_level_54_8007AF50;        // g_UpdateMoby
    D_800758E4 = func_level_54_80085254;          // g_SpawnParticle
    g_UpdateParticle = func_level_54_80084028;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 55:
    g_Buffers.m_CopyBuf = func_level_55_80084934; // g_CopyBufferPointer
    g_SpawnMoby = func_level_55_80082028;         // g_SpawnMoby
    g_UpdateMoby = func_level_55_8007CFB4;        // g_UpdateMoby
    D_800758E4 = func_level_55_80083B8C;          // g_SpawnParticle
    g_UpdateParticle = func_level_55_80082D94;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    D_80075694 = func_level_55_8007AE08;            // g_UnkFunc1Flight
    D_800757A8 = func_level_55_8007AEDC;            // g_UnkFunc2Flight
    g_FlightResultsUpdate = func_level_55_8007B1FC; // g_UpdateGameState7
    D_8007567C = func_level_55_8007B68C;            // g_DrawGameState7
    D_800758C4 = func_level_55_8007B4B0;            // g_DrawTime
    break;
  case 60:
    g_Buffers.m_CopyBuf = func_level_60_80085CE0; // g_CopyBufferPointer
    g_SpawnMoby = func_level_60_80083568;         // g_SpawnMoby
    g_UpdateMoby = func_level_60_8007D938;        // g_UpdateMoby
    D_800758E4 = func_level_60_80084EA0;          // g_SpawnParticle
    g_UpdateParticle = func_level_60_80083ED8;    // g_UpdateParticle
    D_800757A0 = func_level_60_8007AE10;          // g_BalloonistTriggerCode
    D_800758A8 = func_level_60_8007AF4C;          // g_BalloonistCloseDialogue
    D_8007574C = func_level_60_8007AF90;          // g_BalloonistCameraCode
    D_800758D8 = func_level_60_8007CF30;          // g_BalloonistTalkCode
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 61:
    g_Buffers.m_CopyBuf = func_level_61_80088668; // g_CopyBufferPointer
    g_SpawnMoby = func_level_61_80085664;         // g_SpawnMoby
    g_UpdateMoby = func_level_61_8007B528;        // g_UpdateMoby
    D_800758E4 = func_level_61_8008747C;          // g_SpawnParticle
    g_UpdateParticle = func_level_61_80086144;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 62:
    g_Buffers.m_CopyBuf = func_level_62_80086004; // g_CopyBufferPointer
    g_SpawnMoby = func_level_62_80083108;         // g_SpawnMoby
    g_UpdateMoby = func_level_62_8007AE5C;        // g_UpdateMoby
    D_800758E4 = func_level_62_80084EAC;          // g_SpawnParticle
    g_UpdateParticle = func_level_62_80083B4C;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 63:
    g_Buffers.m_CopyBuf = func_level_63_800854B4; // g_CopyBufferPointer
    g_SpawnMoby = func_level_63_80082F24;         // g_SpawnMoby
    g_UpdateMoby = func_level_63_8007AD64;        // g_UpdateMoby
    D_800758E4 = func_level_63_80084634;          // g_SpawnParticle
    g_UpdateParticle = func_level_63_800836F0;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 64:
    g_Buffers.m_CopyBuf = func_level_64_80086264; // g_CopyBufferPointer
    g_SpawnMoby = func_level_64_80083690;         // g_SpawnMoby
    g_UpdateMoby = func_level_64_8007AD4C;        // g_UpdateMoby
    D_800758E4 = func_level_64_80085230;          // g_SpawnParticle
    g_UpdateParticle = func_level_64_800840FC;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  case 99:
    g_Buffers.m_CopyBuf = func_level_99_8007C654; // g_CopyBufferPointer
    g_SpawnMoby = func_level_99_8007B0C0;         // g_SpawnMoby
    g_UpdateMoby = func_level_99_8007ACDC;        // g_UpdateMoby
    D_800758E4 = func_level_99_8007BC44;          // g_SpawnParticle
    g_UpdateParticle = func_level_99_8007B194;    // g_UpdateParticle
    // D_800757A0 = (int *)0x0;
    // D_800758A8 = (int *)0x0;
    // D_8007574C = (int *)0x0;
    // D_800758D8 = (int *)0x0;
    // D_80075694 = (int *)0x0;
    // D_800757A8 = (int *)0x0;
    // g_FlightResultsUpdate = (int *)0x0;
    // D_8007567C = (int *)0x0;
    // D_800758C4 = (int *)0x0;
    break;
  }

  g_Buffers.m_DiscCopyBuf = g_Buffers.m_CopyBuf;
}
