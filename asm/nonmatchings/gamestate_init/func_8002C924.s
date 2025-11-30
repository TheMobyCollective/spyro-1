.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002C924
/* 1D124 8002C924 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 1D128 8002C928 21388000 */  addu       $a3, $a0, $zero
/* 1D12C 8002C92C 0780023C */  lui        $v0, %hi(g_LevelId)
/* 1D130 8002C930 6C59428C */  lw         $v0, %lo(g_LevelId)($v0)
/* 1D134 8002C934 0A000324 */  addiu      $v1, $zero, 0xA
/* 1D138 8002C938 1800BFAF */  sw         $ra, 0x18($sp)
/* 1D13C 8002C93C 1400B1AF */  sw         $s1, 0x14($sp)
/* 1D140 8002C940 1000B0AF */  sw         $s0, 0x10($sp)
/* 1D144 8002C944 0000E68C */  lw         $a2, 0x0($a3)
/* 1D148 8002C948 1A004314 */  bne        $v0, $v1, .L8002C9B4
/* 1D14C 8002C94C 01000224 */   addiu     $v0, $zero, 0x1
/* 1D150 8002C950 1800C38C */  lw         $v1, 0x18($a2)
/* 1D154 8002C954 00000000 */  nop
/* 1D158 8002C958 16006214 */  bne        $v1, $v0, .L8002C9B4
/* 1D15C 8002C95C 00000000 */   nop
/* 1D160 8002C960 0880023C */  lui        $v0, %hi(g_LevelVortexExitFlags + 0x1)
/* 1D164 8002C964 A9A64290 */  lbu        $v0, %lo(g_LevelVortexExitFlags + 0x1)($v0)
/* 1D168 8002C968 00000000 */  nop
/* 1D16C 8002C96C 10004014 */  bnez       $v0, .L8002C9B0
/* 1D170 8002C970 02000224 */   addiu     $v0, $zero, 0x2
/* 1D174 8002C974 0880023C */  lui        $v0, %hi(g_LevelVortexExitFlags + 0x2)
/* 1D178 8002C978 AAA64290 */  lbu        $v0, %lo(g_LevelVortexExitFlags + 0x2)($v0)
/* 1D17C 8002C97C 00000000 */  nop
/* 1D180 8002C980 0B004014 */  bnez       $v0, .L8002C9B0
/* 1D184 8002C984 02000224 */   addiu     $v0, $zero, 0x2
/* 1D188 8002C988 0880023C */  lui        $v0, %hi(g_LevelVortexExitFlags + 0x3)
/* 1D18C 8002C98C ABA64290 */  lbu        $v0, %lo(g_LevelVortexExitFlags + 0x3)($v0)
/* 1D190 8002C990 00000000 */  nop
/* 1D194 8002C994 06004014 */  bnez       $v0, .L8002C9B0
/* 1D198 8002C998 02000224 */   addiu     $v0, $zero, 0x2
/* 1D19C 8002C99C 0880023C */  lui        $v0, %hi(g_LevelVortexExitFlags + 0x5)
/* 1D1A0 8002C9A0 ADA64290 */  lbu        $v0, %lo(g_LevelVortexExitFlags + 0x5)($v0)
/* 1D1A4 8002C9A4 00000000 */  nop
/* 1D1A8 8002C9A8 02004010 */  beqz       $v0, .L8002C9B4
/* 1D1AC 8002C9AC 02000224 */   addiu     $v0, $zero, 0x2
.L8002C9B0:
/* 1D1B0 8002C9B0 1800C2AC */  sw         $v0, 0x18($a2)
.L8002C9B4:
/* 1D1B4 8002C9B4 0780033C */  lui        $v1, %hi(g_LevelId)
/* 1D1B8 8002C9B8 6C59638C */  lw         $v1, %lo(g_LevelId)($v1)
/* 1D1BC 8002C9BC 3C000224 */  addiu      $v0, $zero, 0x3C
/* 1D1C0 8002C9C0 1D006214 */  bne        $v1, $v0, .L8002CA38
/* 1D1C4 8002C9C4 08000224 */   addiu     $v0, $zero, 0x8
/* 1D1C8 8002C9C8 0880023C */  lui        $v0, %hi(g_LevelVortexExitFlags + 0x21)
/* 1D1CC 8002C9CC C9A64290 */  lbu        $v0, %lo(g_LevelVortexExitFlags + 0x21)($v0)
/* 1D1D0 8002C9D0 00000000 */  nop
/* 1D1D4 8002C9D4 17004010 */  beqz       $v0, .L8002CA34
/* 1D1D8 8002C9D8 0100053C */   lui       $a1, (0x134BF >> 16)
/* 1D1DC 8002C9DC BF34A534 */  ori        $a1, $a1, (0x134BF & 0xFFFF)
/* 1D1E0 8002C9E0 0100043C */  lui        $a0, (0x13CE9 >> 16)
/* 1D1E4 8002C9E4 E93C8434 */  ori        $a0, $a0, (0x13CE9 & 0xFFFF)
/* 1D1E8 8002C9E8 01000224 */  addiu      $v0, $zero, 0x1
/* 1D1EC 8002C9EC 00080324 */  addiu      $v1, $zero, 0x800
/* 1D1F0 8002C9F0 1800C2AC */  sw         $v0, 0x18($a2)
/* 1D1F4 8002C9F4 C80C0224 */  addiu      $v0, $zero, 0xCC8
/* 1D1F8 8002C9F8 2C00C2AC */  sw         $v0, 0x2C($a2)
/* 1D1FC 8002C9FC 61250224 */  addiu      $v0, $zero, 0x2561
/* 1D200 8002CA00 0800C2AC */  sw         $v0, 0x8($a2)
/* 1D204 8002CA04 FC0F0224 */  addiu      $v0, $zero, 0xFFC
/* 1D208 8002CA08 0C00C2AC */  sw         $v0, 0xC($a2)
/* 1D20C 8002CA0C 6A000224 */  addiu      $v0, $zero, 0x6A
/* 1D210 8002CA10 1000C2AC */  sw         $v0, 0x10($a2)
/* 1D214 8002CA14 BB000224 */  addiu      $v0, $zero, 0xBB
/* 1D218 8002CA18 1400C2AC */  sw         $v0, 0x14($a2)
/* 1D21C 8002CA1C 10000224 */  addiu      $v0, $zero, 0x10
/* 1D220 8002CA20 2800C3AC */  sw         $v1, 0x28($a2)
/* 1D224 8002CA24 3000C3AC */  sw         $v1, 0x30($a2)
/* 1D228 8002CA28 0000C5AC */  sw         $a1, 0x0($a2)
/* 1D22C 8002CA2C 0400C4AC */  sw         $a0, 0x4($a2)
/* 1D230 8002CA30 3800C2AC */  sw         $v0, 0x38($a2)
.L8002CA34:
/* 1D234 8002CA34 08000224 */  addiu      $v0, $zero, 0x8
.L8002CA38:
/* 1D238 8002CA38 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1D23C 8002CA3C D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1D240 8002CA40 0780023C */  lui        $v0, %hi(g_LevelDragonCount)
/* 1D244 8002CA44 D8724224 */  addiu      $v0, $v0, %lo(g_LevelDragonCount)
/* 1D248 8002CA48 01000424 */  addiu      $a0, $zero, 0x1
/* 1D24C 8002CA4C 0780103C */  lui        $s0, %hi(D_80077030 + 0x28)
/* 1D250 8002CA50 58701026 */  addiu      $s0, $s0, %lo(D_80077030 + 0x28)
/* 1D254 8002CA54 0780033C */  lui        $v1, %hi(g_LevelIndex)
/* 1D258 8002CA58 6459638C */  lw         $v1, %lo(g_LevelIndex)($v1)
/* 1D25C 8002CA5C 0780053C */  lui        $a1, %hi(g_DragonTotal)
/* 1D260 8002CA60 5057A58C */  lw         $a1, %lo(g_DragonTotal)($a1)
/* 1D264 8002CA64 80180300 */  sll        $v1, $v1, 2
/* 1D268 8002CA68 21186200 */  addu       $v1, $v1, $v0
/* 1D26C 8002CA6C 0780013C */  lui        $at, %hi(g_Hud + 0x24)
/* 1D270 8002CA70 CC7F25AC */  sw         $a1, %lo(g_Hud + 0x24)($at)
/* 1D274 8002CA74 0000628C */  lw         $v0, 0x0($v1)
/* 1D278 8002CA78 0780013C */  lui        $at, %hi(D_8007570C)
/* 1D27C 8002CA7C 0C5724AC */  sw         $a0, %lo(D_8007570C)($at)
/* 1D280 8002CA80 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 1D284 8002CA84 9C5724AC */  sw         $a0, %lo(g_StateSwitch)($at)
/* 1D288 8002CA88 01004224 */  addiu      $v0, $v0, 0x1
/* 1D28C 8002CA8C 000062AC */  sw         $v0, 0x0($v1)
/* 1D290 8002CA90 000000AE */  sw         $zero, 0x0($s0)
/* 1D294 8002CA94 0780013C */  lui        $at, %hi(D_80077030 + 0x2C)
/* 1D298 8002CA98 5C7020AC */  sw         $zero, %lo(D_80077030 + 0x2C)($at)
/* 1D29C 8002CA9C 0780013C */  lui        $at, %hi(D_80077030 + 0x3C)
/* 1D2A0 8002CAA0 6C7020AC */  sw         $zero, %lo(D_80077030 + 0x3C)($at)
/* 1D2A4 8002CAA4 0780013C */  lui        $at, %hi(D_80077030 + 0x50)
/* 1D2A8 8002CAA8 807020AC */  sw         $zero, %lo(D_80077030 + 0x50)($at)
/* 1D2AC 8002CAAC 0780013C */  lui        $at, %hi(D_80077030 + 0x5C)
/* 1D2B0 8002CAB0 8C7020AC */  sw         $zero, %lo(D_80077030 + 0x5C)($at)
/* 1D2B4 8002CAB4 0780013C */  lui        $at, %hi(D_80077030 + 0x58)
/* 1D2B8 8002CAB8 887020AC */  sw         $zero, %lo(D_80077030 + 0x58)($at)
/* 1D2BC 8002CABC 680007AE */  sw         $a3, 0x68($s0)
/* 1D2C0 8002CAC0 1800C28C */  lw         $v0, 0x18($a2)
/* 1D2C4 8002CAC4 0100A524 */  addiu      $a1, $a1, 0x1
/* 1D2C8 8002CAC8 0780013C */  lui        $at, %hi(g_DragonTotal)
/* 1D2CC 8002CACC 505725AC */  sw         $a1, %lo(g_DragonTotal)($at)
/* 1D2D0 8002CAD0 0780013C */  lui        $at, %hi(D_80077030 + 0x24)
/* 1D2D4 8002CAD4 547022AC */  sw         $v0, %lo(D_80077030 + 0x24)($at)
/* 1D2D8 8002CAD8 2000C38C */  lw         $v1, 0x20($a2)
/* 1D2DC 8002CADC FFFF0224 */  addiu      $v0, $zero, -0x1
/* 1D2E0 8002CAE0 0B006210 */  beq        $v1, $v0, .L8002CB10
/* 1D2E4 8002CAE4 68001126 */   addiu     $s1, $s0, 0x68
/* 1D2E8 8002CAE8 40100300 */  sll        $v0, $v1, 1
/* 1D2EC 8002CAEC 21104300 */  addu       $v0, $v0, $v1
/* 1D2F0 8002CAF0 80100200 */  sll        $v0, $v0, 2
/* 1D2F4 8002CAF4 23104300 */  subu       $v0, $v0, $v1
/* 1D2F8 8002CAF8 0780033C */  lui        $v1, %hi(D_80075828)
/* 1D2FC 8002CAFC 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 1D300 8002CB00 C0100200 */  sll        $v0, $v0, 3
/* 1D304 8002CB04 21104300 */  addu       $v0, $v0, $v1
/* 1D308 8002CB08 01000324 */  addiu      $v1, $zero, 0x1
/* 1D30C 8002CB0C 3C0043A0 */  sb         $v1, 0x3C($v0)
.L8002CB10:
/* 1D310 8002CB10 0780043C */  lui        $a0, %hi(D_8007624C)
/* 1D314 8002CB14 4C628424 */  addiu      $a0, $a0, %lo(D_8007624C)
/* 1D318 8002CB18 C05D000C */  jal        VecCopy
/* 1D31C 8002CB1C 0C00E524 */   addiu     $a1, $a3, 0xC
/* 1D320 8002CB20 21282002 */  addu       $a1, $s1, $zero
/* 1D324 8002CB24 10000624 */  addiu      $a2, $zero, 0x10
/* 1D328 8002CB28 0780023C */  lui        $v0, %hi(D_80076254)
/* 1D32C 8002CB2C 5462428C */  lw         $v0, %lo(D_80076254)($v0)
/* 1D330 8002CB30 0780033C */  lui        $v1, %hi(g_Spu + 0x2CC)
/* 1D334 8002CB34 D461638C */  lw         $v1, %lo(g_Spu + 0x2CC)($v1)
/* 1D338 8002CB38 40004224 */  addiu      $v0, $v0, 0x40
/* 1D33C 8002CB3C 0780013C */  lui        $at, %hi(D_80076254)
/* 1D340 8002CB40 546222AC */  sw         $v0, %lo(D_80076254)($at)
/* 1D344 8002CB44 6800078E */  lw         $a3, 0x68($s0)
/* 1D348 8002CB48 30006490 */  lbu        $a0, 0x30($v1)
/* 1D34C 8002CB4C 9E56010C */  jal        PlaySound
/* 1D350 8002CB50 5400E724 */   addiu     $a3, $a3, 0x54
/* 1D354 8002CB54 1800BF8F */  lw         $ra, 0x18($sp)
/* 1D358 8002CB58 1400B18F */  lw         $s1, 0x14($sp)
/* 1D35C 8002CB5C 1000B08F */  lw         $s0, 0x10($sp)
/* 1D360 8002CB60 2000BD27 */  addiu      $sp, $sp, 0x20
/* 1D364 8002CB64 0800E003 */  jr         $ra
/* 1D368 8002CB68 00000000 */   nop
.size func_8002C924, . - func_8002C924
