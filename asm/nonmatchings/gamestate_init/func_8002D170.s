.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002D170
/* 1D970 8002D170 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1D974 8002D174 0880043C */  lui        $a0, %hi(D_80078D78)
/* 1D978 8002D178 788D8424 */  addiu      $a0, $a0, %lo(D_80078D78)
/* 1D97C 8002D17C 0D000224 */  addiu      $v0, $zero, 0xD
/* 1D980 8002D180 21280000 */  addu       $a1, $zero, $zero
/* 1D984 8002D184 1000BFAF */  sw         $ra, 0x10($sp)
/* 1D988 8002D188 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1D98C 8002D18C D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1D990 8002D190 455A000C */  jal        Memset
/* 1D994 8002D194 5C000624 */   addiu     $a2, $zero, 0x5C
/* 1D998 8002D198 0780053C */  lui        $a1, %hi(g_Spu + 0x320)
/* 1D99C 8002D19C 2862A524 */  addiu      $a1, $a1, %lo(g_Spu + 0x320)
/* 1D9A0 8002D1A0 FF3F0224 */  addiu      $v0, $zero, 0x3FFF
/* 1D9A4 8002D1A4 0000A2AC */  sw         $v0, 0x0($a1)
/* 1D9A8 8002D1A8 00500224 */  addiu      $v0, $zero, 0x5000
/* 1D9AC 8002D1AC 0780013C */  lui        $at, %hi(g_Spu + 0x31C)
/* 1D9B0 8002D1B0 246222AC */  sw         $v0, %lo(g_Spu + 0x31C)($at)
/* 1D9B4 8002D1B4 0780013C */  lui        $at, %hi(g_Spu + 0x10)
/* 1D9B8 8002D1B8 185F22A4 */  sh         $v0, %lo(g_Spu + 0x10)($at)
/* 1D9BC 8002D1BC 0780013C */  lui        $at, %hi(g_Spu + 0x12)
/* 1D9C0 8002D1C0 1A5F22A4 */  sh         $v0, %lo(g_Spu + 0x12)($at)
/* 1D9C4 8002D1C4 0880023C */  lui        $v0, %hi(D_800785E8)
/* 1D9C8 8002D1C8 E885428C */  lw         $v0, %lo(D_800785E8)($v0)
/* 1D9CC 8002D1CC 0A000324 */  addiu      $v1, $zero, 0xA
/* 1D9D0 8002D1D0 0780013C */  lui        $at, %hi(D_80075754)
/* 1D9D4 8002D1D4 545723AC */  sw         $v1, %lo(D_80075754)($at)
/* 1D9D8 8002D1D8 0780013C */  lui        $at, %hi(D_80075748)
/* 1D9DC 8002D1DC 485723AC */  sw         $v1, %lo(D_80075748)($at)
/* 1D9E0 8002D1E0 C0000324 */  addiu      $v1, $zero, 0xC0
/* 1D9E4 8002D1E4 E0FCA3AC */  sw         $v1, -0x320($a1)
/* 1D9E8 8002D1E8 00E04224 */  addiu      $v0, $v0, -0x2000
/* 1D9EC 8002D1EC 0880013C */  lui        $at, %hi(D_80078D78 + 0x4C)
/* 1D9F0 8002D1F0 C48D22AC */  sw         $v0, %lo(D_80078D78 + 0x4C)($at)
/* 1D9F4 8002D1F4 1673010C */  jal        SpuSetCommonAttr
/* 1D9F8 8002D1F8 E0FCA424 */   addiu     $a0, $a1, -0x320
/* 1D9FC 8002D1FC 0780023C */  lui        $v0, %hi(D_80075680)
/* 1DA00 8002D200 8056428C */  lw         $v0, %lo(D_80075680)($v0)
/* 1DA04 8002D204 59010424 */  addiu      $a0, $zero, 0x159
/* 1DA08 8002D208 0780013C */  lui        $at, %hi(D_8007591C)
/* 1DA0C 8002D20C 1C5920AC */  sw         $zero, %lo(D_8007591C)($at)
/* 1DA10 8002D210 D789010C */  jal        srand
/* 1DA14 8002D214 000040AC */   sw        $zero, 0x0($v0)
/* 1DA18 8002D218 1000BF8F */  lw         $ra, 0x10($sp)
/* 1DA1C 8002D21C 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1DA20 8002D220 0800E003 */  jr         $ra
/* 1DA24 8002D224 00000000 */   nop
.size func_8002D170, . - func_8002D170
