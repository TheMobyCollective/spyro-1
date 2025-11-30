.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002EB2C
/* 1F32C 8002EB2C E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1F330 8002EB30 E338023C */  lui        $v0, (0x38E38E39 >> 16)
/* 1F334 8002EB34 398E4234 */  ori        $v0, $v0, (0x38E38E39 & 0xFFFF)
/* 1F338 8002EB38 0780053C */  lui        $a1, %hi(g_Hud + 0x40)
/* 1F33C 8002EB3C E87FA58C */  lw         $a1, %lo(g_Hud + 0x40)($a1)
/* 1F340 8002EB40 0780073C */  lui        $a3, %hi(g_Hud + 0x3C)
/* 1F344 8002EB44 E47FE724 */  addiu      $a3, $a3, %lo(g_Hud + 0x3C)
/* 1F348 8002EB48 0100A524 */  addiu      $a1, $a1, 0x1
/* 1F34C 8002EB4C 1800A200 */  mult       $a1, $v0
/* 1F350 8002EB50 0780063C */  lui        $a2, %hi(g_DeltaTime)
/* 1F354 8002EB54 CC56C68C */  lw         $a2, %lo(g_DeltaTime)($a2)
/* 1F358 8002EB58 0780033C */  lui        $v1, %hi(D_8007568C)
/* 1F35C 8002EB5C 8C56638C */  lw         $v1, %lo(D_8007568C)($v1)
/* 1F360 8002EB60 1000BFAF */  sw         $ra, 0x10($sp)
/* 1F364 8002EB64 0000E28C */  lw         $v0, 0x0($a3)
/* 1F368 8002EB68 21186600 */  addu       $v1, $v1, $a2
/* 1F36C 8002EB6C 0780013C */  lui        $at, %hi(D_8007568C)
/* 1F370 8002EB70 8C5623AC */  sw         $v1, %lo(D_8007568C)($at)
/* 1F374 8002EB74 23104600 */  subu       $v0, $v0, $a2
/* 1F378 8002EB78 FF004230 */  andi       $v0, $v0, 0xFF
/* 1F37C 8002EB7C 0000E2AC */  sw         $v0, 0x0($a3)
/* 1F380 8002EB80 C3170500 */  sra        $v0, $a1, 31
/* 1F384 8002EB84 10400000 */  mfhi       $t0
/* 1F388 8002EB88 43180800 */  sra        $v1, $t0, 1
/* 1F38C 8002EB8C 23186200 */  subu       $v1, $v1, $v0
/* 1F390 8002EB90 C0100300 */  sll        $v0, $v1, 3
/* 1F394 8002EB94 21104300 */  addu       $v0, $v0, $v1
/* 1F398 8002EB98 2328A200 */  subu       $a1, $a1, $v0
/* 1F39C 8002EB9C 0780013C */  lui        $at, %hi(g_Hud + 0x40)
/* 1F3A0 8002EBA0 E87F25AC */  sw         $a1, %lo(g_Hud + 0x40)($at)
/* 1F3A4 8002EBA4 3063010C */  jal        SpecularUpdate
/* 1F3A8 8002EBA8 03000424 */   addiu     $a0, $zero, 0x3
/* 1F3AC 8002EBAC 0780023C */  lui        $v0, %hi(D_800758B8)
/* 1F3B0 8002EBB0 B858428C */  lw         $v0, %lo(D_800758B8)($v0)
/* 1F3B4 8002EBB4 00000000 */  nop
/* 1F3B8 8002EBB8 05004228 */  slti       $v0, $v0, 0x5
/* 1F3BC 8002EBBC 88004014 */  bnez       $v0, .L8002EDE0
/* 1F3C0 8002EBC0 00000000 */   nop
/* 1F3C4 8002EBC4 0780023C */  lui        $v0, %hi(g_LevelCheatActive)
/* 1F3C8 8002EBC8 8058428C */  lw         $v0, %lo(g_LevelCheatActive)($v0)
/* 1F3CC 8002EBCC 00000000 */  nop
/* 1F3D0 8002EBD0 05004010 */  beqz       $v0, .L8002EBE8
/* 1F3D4 8002EBD4 00000000 */   nop
/* 1F3D8 8002EBD8 60B5000C */  jal        CheatProcessLevelWarp
/* 1F3DC 8002EBDC 00000000 */   nop
/* 1F3E0 8002EBE0 78BB0008 */  j          .L8002EDE0
/* 1F3E4 8002EBE4 00000000 */   nop
.L8002EBE8:
/* 1F3E8 8002EBE8 3BB6000C */  jal        CheatsProcess
/* 1F3EC 8002EBEC 00000000 */   nop
/* 1F3F0 8002EBF0 0780023C */  lui        $v0, %hi(D_800757CC)
/* 1F3F4 8002EBF4 CC57428C */  lw         $v0, %lo(D_800757CC)($v0)
/* 1F3F8 8002EBF8 00000000 */  nop
/* 1F3FC 8002EBFC 3A004014 */  bnez       $v0, .L8002ECE8
/* 1F400 8002EC00 00000000 */   nop
/* 1F404 8002EC04 0780033C */  lui        $v1, %hi(D_80075744)
/* 1F408 8002EC08 4457638C */  lw         $v1, %lo(D_80075744)($v1)
/* 1F40C 8002EC0C 00000000 */  nop
/* 1F410 8002EC10 1A006018 */  blez       $v1, .L8002EC7C
/* 1F414 8002EC14 40100300 */   sll       $v0, $v1, 1
/* 1F418 8002EC18 21104300 */  addu       $v0, $v0, $v1
/* 1F41C 8002EC1C 40100200 */  sll        $v0, $v0, 1
/* 1F420 8002EC20 0880013C */  lui        $at, %hi(g_VisitedFlags)
/* 1F424 8002EC24 21082200 */  addu       $at, $at, $v0
/* 1F428 8002EC28 728E2290 */  lbu        $v0, %lo(g_VisitedFlags)($at)
/* 1F42C 8002EC2C 00000000 */  nop
/* 1F430 8002EC30 14004010 */  beqz       $v0, .L8002EC84
/* 1F434 8002EC34 05006228 */   slti      $v0, $v1, 0x5
/* 1F438 8002EC38 0780023C */  lui        $v0, %hi(g_Pad + 0x8)
/* 1F43C 8002EC3C 8073428C */  lw         $v0, %lo(g_Pad + 0x8)($v0)
/* 1F440 8002EC40 00000000 */  nop
/* 1F444 8002EC44 00804230 */  andi       $v0, $v0, 0x8000
/* 1F448 8002EC48 0C004010 */  beqz       $v0, .L8002EC7C
/* 1F44C 8002EC4C 21280000 */   addu      $a1, $zero, $zero
/* 1F450 8002EC50 0780023C */  lui        $v0, %hi(g_Spu + 0x2CC)
/* 1F454 8002EC54 D461428C */  lw         $v0, %lo(g_Spu + 0x2CC)($v0)
/* 1F458 8002EC58 10000624 */  addiu      $a2, $zero, 0x10
/* 1F45C 8002EC5C 38004490 */  lbu        $a0, 0x38($v0)
/* 1F460 8002EC60 9E56010C */  jal        PlaySound
/* 1F464 8002EC64 21380000 */   addu      $a3, $zero, $zero
/* 1F468 8002EC68 40000224 */  addiu      $v0, $zero, 0x40
/* 1F46C 8002EC6C 0780013C */  lui        $at, %hi(D_800756D4)
/* 1F470 8002EC70 D45622AC */  sw         $v0, %lo(D_800756D4)($at)
/* 1F474 8002EC74 0780033C */  lui        $v1, %hi(D_80075744)
/* 1F478 8002EC78 4457638C */  lw         $v1, %lo(D_80075744)($v1)
.L8002EC7C:
/* 1F47C 8002EC7C 00000000 */  nop
/* 1F480 8002EC80 05006228 */  slti       $v0, $v1, 0x5
.L8002EC84:
/* 1F484 8002EC84 18004010 */  beqz       $v0, .L8002ECE8
/* 1F488 8002EC88 40100300 */   sll       $v0, $v1, 1
/* 1F48C 8002EC8C 21104300 */  addu       $v0, $v0, $v1
/* 1F490 8002EC90 40100200 */  sll        $v0, $v0, 1
/* 1F494 8002EC94 0880013C */  lui        $at, %hi(g_VisitedFlags + 0xC)
/* 1F498 8002EC98 21082200 */  addu       $at, $at, $v0
/* 1F49C 8002EC9C 7E8E2290 */  lbu        $v0, %lo(g_VisitedFlags + 0xC)($at)
/* 1F4A0 8002ECA0 00000000 */  nop
/* 1F4A4 8002ECA4 10004010 */  beqz       $v0, .L8002ECE8
/* 1F4A8 8002ECA8 00000000 */   nop
/* 1F4AC 8002ECAC 0780023C */  lui        $v0, %hi(g_Pad + 0x8)
/* 1F4B0 8002ECB0 8073428C */  lw         $v0, %lo(g_Pad + 0x8)($v0)
/* 1F4B4 8002ECB4 00000000 */  nop
/* 1F4B8 8002ECB8 00204230 */  andi       $v0, $v0, 0x2000
/* 1F4BC 8002ECBC 0A004010 */  beqz       $v0, .L8002ECE8
/* 1F4C0 8002ECC0 21280000 */   addu      $a1, $zero, $zero
/* 1F4C4 8002ECC4 0780023C */  lui        $v0, %hi(g_Spu + 0x2CC)
/* 1F4C8 8002ECC8 D461428C */  lw         $v0, %lo(g_Spu + 0x2CC)($v0)
/* 1F4CC 8002ECCC 10000624 */  addiu      $a2, $zero, 0x10
/* 1F4D0 8002ECD0 38004490 */  lbu        $a0, 0x38($v0)
/* 1F4D4 8002ECD4 9E56010C */  jal        PlaySound
/* 1F4D8 8002ECD8 21380000 */   addu      $a3, $zero, $zero
/* 1F4DC 8002ECDC C0FF0224 */  addiu      $v0, $zero, -0x40
/* 1F4E0 8002ECE0 0780013C */  lui        $at, %hi(D_800756D4)
/* 1F4E4 8002ECE4 D45622AC */  sw         $v0, %lo(D_800756D4)($at)
.L8002ECE8:
/* 1F4E8 8002ECE8 0780033C */  lui        $v1, %hi(D_800756D4)
/* 1F4EC 8002ECEC D456638C */  lw         $v1, %lo(D_800756D4)($v1)
/* 1F4F0 8002ECF0 00000000 */  nop
/* 1F4F4 8002ECF4 27006010 */  beqz       $v1, .L8002ED94
/* 1F4F8 8002ECF8 00000000 */   nop
/* 1F4FC 8002ECFC 0780023C */  lui        $v0, %hi(D_800757CC)
/* 1F500 8002ED00 CC57428C */  lw         $v0, %lo(D_800757CC)($v0)
/* 1F504 8002ED04 00000000 */  nop
/* 1F508 8002ED08 21184300 */  addu       $v1, $v0, $v1
/* 1F50C 8002ED0C 0780013C */  lui        $at, %hi(D_800757CC)
/* 1F510 8002ED10 CC5723AC */  sw         $v1, %lo(D_800757CC)($at)
/* 1F514 8002ED14 05006014 */  bnez       $v1, .L8002ED2C
/* 1F518 8002ED18 40FE0424 */   addiu     $a0, $zero, -0x1C0
/* 1F51C 8002ED1C 0780013C */  lui        $at, %hi(D_800756D4)
/* 1F520 8002ED20 D45620AC */  sw         $zero, %lo(D_800756D4)($at)
/* 1F524 8002ED24 65BB0008 */  j          .L8002ED94
/* 1F528 8002ED28 00000000 */   nop
.L8002ED2C:
/* 1F52C 8002ED2C 0E006414 */  bne        $v1, $a0, .L8002ED68
/* 1F530 8002ED30 C0010224 */   addiu     $v0, $zero, 0x1C0
/* 1F534 8002ED34 C0FF0224 */  addiu      $v0, $zero, -0x40
/* 1F538 8002ED38 0780013C */  lui        $at, %hi(D_800756D4)
/* 1F53C 8002ED3C D45622AC */  sw         $v0, %lo(D_800756D4)($at)
/* 1F540 8002ED40 0780023C */  lui        $v0, %hi(D_80075744)
/* 1F544 8002ED44 4457428C */  lw         $v0, %lo(D_80075744)($v0)
/* 1F548 8002ED48 C0010324 */  addiu      $v1, $zero, 0x1C0
/* 1F54C 8002ED4C 0780013C */  lui        $at, %hi(D_800757CC)
/* 1F550 8002ED50 CC5723AC */  sw         $v1, %lo(D_800757CC)($at)
/* 1F554 8002ED54 01004224 */  addiu      $v0, $v0, 0x1
/* 1F558 8002ED58 0780013C */  lui        $at, %hi(D_80075744)
/* 1F55C 8002ED5C 445722AC */  sw         $v0, %lo(D_80075744)($at)
/* 1F560 8002ED60 65BB0008 */  j          .L8002ED94
/* 1F564 8002ED64 00000000 */   nop
.L8002ED68:
/* 1F568 8002ED68 0A006214 */  bne        $v1, $v0, .L8002ED94
/* 1F56C 8002ED6C 40000224 */   addiu     $v0, $zero, 0x40
/* 1F570 8002ED70 0780033C */  lui        $v1, %hi(D_80075744)
/* 1F574 8002ED74 4457638C */  lw         $v1, %lo(D_80075744)($v1)
/* 1F578 8002ED78 0780013C */  lui        $at, %hi(D_800756D4)
/* 1F57C 8002ED7C D45622AC */  sw         $v0, %lo(D_800756D4)($at)
/* 1F580 8002ED80 0780013C */  lui        $at, %hi(D_800757CC)
/* 1F584 8002ED84 CC5724AC */  sw         $a0, %lo(D_800757CC)($at)
/* 1F588 8002ED88 FFFF6324 */  addiu      $v1, $v1, -0x1
/* 1F58C 8002ED8C 0780013C */  lui        $at, %hi(D_80075744)
/* 1F590 8002ED90 445723AC */  sw         $v1, %lo(D_80075744)($at)
.L8002ED94:
/* 1F594 8002ED94 0780033C */  lui        $v1, %hi(g_Pad)
/* 1F598 8002ED98 7873638C */  lw         $v1, %lo(g_Pad)($v1)
/* 1F59C 8002ED9C 00000000 */  nop
/* 1F5A0 8002EDA0 10086230 */  andi       $v0, $v1, 0x810
/* 1F5A4 8002EDA4 05004010 */  beqz       $v0, .L8002EDBC
/* 1F5A8 8002EDA8 40016230 */   andi      $v0, $v1, 0x140
/* 1F5AC 8002EDAC 08B1000C */  jal        func_8002C420
/* 1F5B0 8002EDB0 21200000 */   addu      $a0, $zero, $zero
/* 1F5B4 8002EDB4 78BB0008 */  j          .L8002EDE0
/* 1F5B8 8002EDB8 00000000 */   nop
.L8002EDBC:
/* 1F5BC 8002EDBC 08004010 */  beqz       $v0, .L8002EDE0
/* 1F5C0 8002EDC0 00000000 */   nop
/* 1F5C4 8002EDC4 0780023C */  lui        $v0, %hi(g_LevelCheatActive)
/* 1F5C8 8002EDC8 8058428C */  lw         $v0, %lo(g_LevelCheatActive)($v0)
/* 1F5CC 8002EDCC 00000000 */  nop
/* 1F5D0 8002EDD0 03004014 */  bnez       $v0, .L8002EDE0
/* 1F5D4 8002EDD4 00000000 */   nop
/* 1F5D8 8002EDD8 EFB1000C */  jal        func_8002C7BC
/* 1F5DC 8002EDDC 00000000 */   nop
.L8002EDE0:
/* 1F5E0 8002EDE0 1000BF8F */  lw         $ra, 0x10($sp)
/* 1F5E4 8002EDE4 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1F5E8 8002EDE8 0800E003 */  jr         $ra
/* 1F5EC 8002EDEC 00000000 */   nop
.size func_8002EB2C, . - func_8002EB2C
