.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8001E9C8
/* F1C8 8001E9C8 0880023C */  lui        $v0, %hi(g_Cyclorama + 0x10)
/* F1CC 8001E9CC 508A4290 */  lbu        $v0, %lo(g_Cyclorama + 0x10)($v0)
/* F1D0 8001E9D0 0880033C */  lui        $v1, %hi(g_Cyclorama + 0x11)
/* F1D4 8001E9D4 518A6390 */  lbu        $v1, %lo(g_Cyclorama + 0x11)($v1)
/* F1D8 8001E9D8 0880043C */  lui        $a0, %hi(g_Cyclorama + 0x12)
/* F1DC 8001E9DC 528A8490 */  lbu        $a0, %lo(g_Cyclorama + 0x12)($a0)
/* F1E0 8001E9E0 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* F1E4 8001E9E4 1400BFAF */  sw         $ra, 0x14($sp)
/* F1E8 8001E9E8 1000B0AF */  sw         $s0, 0x10($sp)
/* F1EC 8001E9EC 0780013C */  lui        $at, %hi(g_DB + 0x19)
/* F1F0 8001E9F0 F96E22A0 */  sb         $v0, %lo(g_DB + 0x19)($at)
/* F1F4 8001E9F4 0780013C */  lui        $at, %hi(g_DB + 0x1A)
/* F1F8 8001E9F8 FA6E23A0 */  sb         $v1, %lo(g_DB + 0x1A)($at)
/* F1FC 8001E9FC 0780013C */  lui        $at, %hi(g_DB + 0x1B)
/* F200 8001EA00 FB6E24A0 */  sb         $a0, %lo(g_DB + 0x1B)($at)
/* F204 8001EA04 0780013C */  lui        $at, %hi(g_DB + 0x9D)
/* F208 8001EA08 7D6F22A0 */  sb         $v0, %lo(g_DB + 0x9D)($at)
/* F20C 8001EA0C 0780013C */  lui        $at, %hi(g_DB + 0x9E)
/* F210 8001EA10 7E6F23A0 */  sb         $v1, %lo(g_DB + 0x9E)($at)
/* F214 8001EA14 0780013C */  lui        $at, %hi(g_DB + 0x9F)
/* F218 8001EA18 7F6F24A0 */  sb         $a0, %lo(g_DB + 0x9F)($at)
/* F21C 8001EA1C 7048010C */  jal        func_800521C0
/* F220 8001EA20 00000000 */   nop
/* F224 8001EA24 567C000C */  jal        func_8001F158
/* F228 8001EA28 00000000 */   nop
/* F22C 8001EA2C 0780103C */  lui        $s0, %hi(D_8006FCF4)
/* F230 8001EA30 F4FC1026 */  addiu      $s0, $s0, %lo(D_8006FCF4)
/* F234 8001EA34 21200002 */  addu       $a0, $s0, $zero
/* F238 8001EA38 21280000 */  addu       $a1, $zero, $zero
/* F23C 8001EA3C 455A000C */  jal        Memset
/* F240 8001EA40 00090624 */   addiu     $a2, $zero, 0x900
/* F244 8001EA44 E67D000C */  jal        func_8001F798
/* F248 8001EA48 00000000 */   nop
/* F24C 8001EA4C 21200002 */  addu       $a0, $s0, $zero
/* F250 8001EA50 21280000 */  addu       $a1, $zero, $zero
/* F254 8001EA54 455A000C */  jal        Memset
/* F258 8001EA58 001C0624 */   addiu     $a2, $zero, 0x1C00
/* F25C 8001EA5C 0100023C */  lui        $v0, (0x14000 >> 16)
/* F260 8001EA60 00404234 */  ori        $v0, $v0, (0x14000 & 0xFFFF)
/* F264 8001EA64 0880013C */  lui        $at, %hi(g_Environment + 0x28)
/* F268 8001EA68 D08522AC */  sw         $v0, %lo(g_Environment + 0x28)($at)
/* F26C 8001EA6C 3C96000C */  jal        func_800258F0
/* F270 8001EA70 FFFF0424 */   addiu     $a0, $zero, -0x1
/* F274 8001EA74 FFFF0424 */  addiu      $a0, $zero, -0x1
/* F278 8001EA78 0780053C */  lui        $a1, %hi(g_Camera + 0x14)
/* F27C 8001EA7C E46DA524 */  addiu      $a1, $a1, %lo(g_Camera + 0x14)
/* F280 8001EA80 EA3A010C */  jal        func_8004EBA8
/* F284 8001EA84 ECFFA624 */   addiu     $a2, $a1, -0x14
/* F288 8001EA88 0780053C */  lui        $a1, %hi(D_80075918)
/* F28C 8001EA8C 1859A58C */  lw         $a1, %lo(D_80075918)($a1)
/* F290 8001EA90 00000000 */  nop
/* F294 8001EA94 0500A010 */  beqz       $a1, .L8001EAAC
/* F298 8001EA98 02000424 */   addiu     $a0, $zero, 0x2
/* F29C 8001EA9C 00290500 */  sll        $a1, $a1, 4
/* F2A0 8001EAA0 2130A000 */  addu       $a2, $a1, $zero
/* F2A4 8001EAA4 3564000C */  jal        func_800190D4
/* F2A8 8001EAA8 2138A000 */   addu      $a3, $a1, $zero
.L8001EAAC:
/* F2AC 8001EAAC D97D010C */  jal        DrawSync
/* F2B0 8001EAB0 21200000 */   addu      $a0, $zero, $zero
/* F2B4 8001EAB4 0780023C */  lui        $v0, %hi(D_80075784)
/* F2B8 8001EAB8 8457428C */  lw         $v0, %lo(D_80075784)($v0)
/* F2BC 8001EABC 00000000 */  nop
/* F2C0 8001EAC0 03004010 */  beqz       $v0, .L8001EAD0
/* F2C4 8001EAC4 00000000 */   nop
/* F2C8 8001EAC8 F176010C */  jal        VSync
/* F2CC 8001EACC 21200000 */   addu      $a0, $zero, $zero
.L8001EAD0:
/* F2D0 8001EAD0 F176010C */  jal        VSync
/* F2D4 8001EAD4 FFFF0424 */   addiu     $a0, $zero, -0x1
/* F2D8 8001EAD8 0780033C */  lui        $v1, %hi(D_80075950)
/* F2DC 8001EADC 5059638C */  lw         $v1, %lo(D_80075950)($v1)
/* F2E0 8001EAE0 0780013C */  lui        $at, %hi(D_80075954)
/* F2E4 8001EAE4 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* F2E8 8001EAE8 23104300 */  subu       $v0, $v0, $v1
/* F2EC 8001EAEC 02004228 */  slti       $v0, $v0, 0x2
/* F2F0 8001EAF0 0E004010 */  beqz       $v0, .L8001EB2C
/* F2F4 8001EAF4 00000000 */   nop
/* F2F8 8001EAF8 0780103C */  lui        $s0, %hi(D_80075954)
/* F2FC 8001EAFC 54591026 */  addiu      $s0, $s0, %lo(D_80075954)
.L8001EB00:
/* F300 8001EB00 F176010C */  jal        VSync
/* F304 8001EB04 21200000 */   addu      $a0, $zero, $zero
/* F308 8001EB08 F176010C */  jal        VSync
/* F30C 8001EB0C FFFF0424 */   addiu     $a0, $zero, -0x1
/* F310 8001EB10 FCFF038E */  lw         $v1, -0x4($s0)
/* F314 8001EB14 0780013C */  lui        $at, %hi(D_80075954)
/* F318 8001EB18 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* F31C 8001EB1C 23104300 */  subu       $v0, $v0, $v1
/* F320 8001EB20 02004228 */  slti       $v0, $v0, 0x2
/* F324 8001EB24 F6FF4014 */  bnez       $v0, .L8001EB00
/* F328 8001EB28 00000000 */   nop
.L8001EB2C:
/* F32C 8001EB2C F176010C */  jal        VSync
/* F330 8001EB30 FFFF0424 */   addiu     $a0, $zero, -0x1
/* F334 8001EB34 0780043C */  lui        $a0, %hi(D_80075888)
/* F338 8001EB38 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* F33C 8001EB3C 0780013C */  lui        $at, %hi(D_80075950)
/* F340 8001EB40 505922AC */  sw         $v0, %lo(D_80075950)($at)
/* F344 8001EB44 0C80010C */  jal        PutDispEnv
/* F348 8001EB48 5C008424 */   addiu     $a0, $a0, 0x5C
/* F34C 8001EB4C 0780043C */  lui        $a0, %hi(D_80075888)
/* F350 8001EB50 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* F354 8001EB54 767F010C */  jal        PutDrawEnv
/* F358 8001EB58 00000000 */   nop
/* F35C 8001EB5C E159000C */  jal        func_80016784
/* F360 8001EB60 00080424 */   addiu     $a0, $zero, 0x800
/* F364 8001EB64 597F010C */  jal        DrawOTag
/* F368 8001EB68 21204000 */   addu      $a0, $v0, $zero
/* F36C 8001EB6C 1400BF8F */  lw         $ra, 0x14($sp)
/* F370 8001EB70 1000B08F */  lw         $s0, 0x10($sp)
/* F374 8001EB74 1800BD27 */  addiu      $sp, $sp, 0x18
/* F378 8001EB78 0800E003 */  jr         $ra
/* F37C 8001EB7C 00000000 */   nop
.size func_8001E9C8, . - func_8001E9C8
