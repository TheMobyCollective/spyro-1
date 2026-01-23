.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_15_8007B1FC
/* 16A87C4 8007B1FC 0780023C */  lui        $v0, %hi(D_8007568C)
/* 16A87C8 8007B200 8C56428C */  lw         $v0, %lo(D_8007568C)($v0)
/* 16A87CC 8007B204 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 16A87D0 8007B208 1400BFAF */  sw         $ra, 0x14($sp)
/* 16A87D4 8007B20C 03004014 */  bnez       $v0, .Llevel_15_8007B21C
/* 16A87D8 8007B210 1000B0AF */   sw        $s0, 0x10($sp)
/* 16A87DC 8007B214 CA5A010C */  jal        func_80056B28
/* 16A87E0 8007B218 21200000 */   addu      $a0, $zero, $zero
.Llevel_15_8007B21C:
/* 16A87E4 8007B21C 0780033C */  lui        $v1, %hi(g_Hud + 0x3C)
/* 16A87E8 8007B220 E47F6324 */  addiu      $v1, $v1, %lo(g_Hud + 0x3C)
/* 16A87EC 8007B224 0000628C */  lw         $v0, 0x0($v1)
/* 16A87F0 8007B228 03000424 */  addiu      $a0, $zero, 0x3
/* 16A87F4 8007B22C FCFF4224 */  addiu      $v0, $v0, -0x4
/* 16A87F8 8007B230 FF004230 */  andi       $v0, $v0, 0xFF
/* 16A87FC 8007B234 3063010C */  jal        SpecularUpdate
/* 16A8800 8007B238 000062AC */   sw        $v0, 0x0($v1)
/* 16A8804 8007B23C 0780023C */  lui        $v0, %hi(D_8007568C)
/* 16A8808 8007B240 8C56428C */  lw         $v0, %lo(D_8007568C)($v0)
/* 16A880C 8007B244 0780033C */  lui        $v1, %hi(D_800757CC)
/* 16A8810 8007B248 CC57638C */  lw         $v1, %lo(D_800757CC)($v1)
/* 16A8814 8007B24C 01004224 */  addiu      $v0, $v0, 0x1
/* 16A8818 8007B250 01006324 */  addiu      $v1, $v1, 0x1
/* 16A881C 8007B254 0780013C */  lui        $at, %hi(D_800757CC)
/* 16A8820 8007B258 CC5723AC */  sw         $v1, %lo(D_800757CC)($at)
/* 16A8824 8007B25C 05006328 */  slti       $v1, $v1, 0x5
/* 16A8828 8007B260 0780013C */  lui        $at, %hi(D_8007568C)
/* 16A882C 8007B264 8C5622AC */  sw         $v0, %lo(D_8007568C)($at)
/* 16A8830 8007B268 0C006014 */  bnez       $v1, .Llevel_15_8007B29C
/* 16A8834 8007B26C 21200000 */   addu      $a0, $zero, $zero
/* 16A8838 8007B270 0780033C */  lui        $v1, %hi(D_80075744)
/* 16A883C 8007B274 4457638C */  lw         $v1, %lo(D_80075744)($v1)
/* 16A8840 8007B278 00000000 */  nop
/* 16A8844 8007B27C 09006228 */  slti       $v0, $v1, 0x9
/* 16A8848 8007B280 03004010 */  beqz       $v0, .Llevel_15_8007B290
/* 16A884C 8007B284 01006224 */   addiu     $v0, $v1, 0x1
/* 16A8850 8007B288 0780013C */  lui        $at, %hi(D_80075744)
/* 16A8854 8007B28C 445722AC */  sw         $v0, %lo(D_80075744)($at)
.Llevel_15_8007B290:
/* 16A8858 8007B290 0780013C */  lui        $at, %hi(D_800757CC)
/* 16A885C 8007B294 CC5720AC */  sw         $zero, %lo(D_800757CC)($at)
/* 16A8860 8007B298 21200000 */  addu       $a0, $zero, $zero
.Llevel_15_8007B29C:
/* 16A8864 8007B29C 0880033C */  lui        $v1, %hi(g_Hud + 0x8A)
/* 16A8868 8007B2A0 32806324 */  addiu      $v1, $v1, %lo(g_Hud + 0x8A)
.Llevel_15_8007B2A4:
/* 16A886C 8007B2A4 00006290 */  lbu        $v0, 0x0($v1)
/* 16A8870 8007B2A8 01008424 */  addiu      $a0, $a0, 0x1
/* 16A8874 8007B2AC 08004224 */  addiu      $v0, $v0, 0x8
/* 16A8878 8007B2B0 000062A0 */  sb         $v0, 0x0($v1)
/* 16A887C 8007B2B4 04008228 */  slti       $v0, $a0, 0x4
/* 16A8880 8007B2B8 FAFF4014 */  bnez       $v0, .Llevel_15_8007B2A4
/* 16A8884 8007B2BC 58006324 */   addiu     $v1, $v1, 0x58
/* 16A8888 8007B2C0 0780023C */  lui        $v0, %hi(D_80075744)
/* 16A888C 8007B2C4 4457428C */  lw         $v0, %lo(D_80075744)($v0)
/* 16A8890 8007B2C8 00000000 */  nop
/* 16A8894 8007B2CC 09004228 */  slti       $v0, $v0, 0x9
/* 16A8898 8007B2D0 61004014 */  bnez       $v0, .Llevel_15_8007B458
/* 16A889C 8007B2D4 00000000 */   nop
/* 16A88A0 8007B2D8 0780103C */  lui        $s0, %hi(g_Pad)
/* 16A88A4 8007B2DC 78731026 */  addiu      $s0, $s0, %lo(g_Pad)
/* 16A88A8 8007B2E0 0000028E */  lw         $v0, 0x0($s0)
/* 16A88AC 8007B2E4 00000000 */  nop
/* 16A88B0 8007B2E8 00504230 */  andi       $v0, $v0, 0x5000
/* 16A88B4 8007B2EC 0F004010 */  beqz       $v0, .Llevel_15_8007B32C
/* 16A88B8 8007B2F0 21280000 */   addu      $a1, $zero, $zero
/* 16A88BC 8007B2F4 10000624 */  addiu      $a2, $zero, 0x10
/* 16A88C0 8007B2F8 0780033C */  lui        $v1, %hi(D_80075720)
/* 16A88C4 8007B2FC 2057638C */  lw         $v1, %lo(D_80075720)($v1)
/* 16A88C8 8007B300 0780043C */  lui        $a0, %hi(g_Spu + 0x2CC)
/* 16A88CC 8007B304 D461848C */  lw         $a0, %lo(g_Spu + 0x2CC)($a0)
/* 16A88D0 8007B308 01000224 */  addiu      $v0, $zero, 0x1
/* 16A88D4 8007B30C 0780013C */  lui        $at, %hi(D_8007568C)
/* 16A88D8 8007B310 8C5620AC */  sw         $zero, %lo(D_8007568C)($at)
/* 16A88DC 8007B314 23104300 */  subu       $v0, $v0, $v1
/* 16A88E0 8007B318 0780013C */  lui        $at, %hi(D_80075720)
/* 16A88E4 8007B31C 205722AC */  sw         $v0, %lo(D_80075720)($at)
/* 16A88E8 8007B320 2D008490 */  lbu        $a0, 0x2D($a0)
/* 16A88EC 8007B324 9E56010C */  jal        PlaySound
/* 16A88F0 8007B328 21380000 */   addu      $a3, $zero, $zero
.Llevel_15_8007B32C:
/* 16A88F4 8007B32C 0000028E */  lw         $v0, 0x0($s0)
/* 16A88F8 8007B330 00000000 */  nop
/* 16A88FC 8007B334 40084230 */  andi       $v0, $v0, 0x840
/* 16A8900 8007B338 58004010 */  beqz       $v0, .Llevel_15_8007B49C
/* 16A8904 8007B33C 00000000 */   nop
/* 16A8908 8007B340 0780023C */  lui        $v0, %hi(D_80075744)
/* 16A890C 8007B344 4457428C */  lw         $v0, %lo(D_80075744)($v0)
/* 16A8910 8007B348 00000000 */  nop
/* 16A8914 8007B34C 64004228 */  slti       $v0, $v0, 0x64
/* 16A8918 8007B350 1A004010 */  beqz       $v0, .Llevel_15_8007B3BC
/* 16A891C 8007B354 00000000 */   nop
/* 16A8920 8007B358 0880023C */  lui        $v0, %hi(g_FlightObjectiveCounters)
/* 16A8924 8007B35C 3086428C */  lw         $v0, %lo(g_FlightObjectiveCounters)($v0)
/* 16A8928 8007B360 0880033C */  lui        $v1, %hi(g_FlightObjectiveCounters + 0x4)
/* 16A892C 8007B364 3486638C */  lw         $v1, %lo(g_FlightObjectiveCounters + 0x4)($v1)
/* 16A8930 8007B368 00000000 */  nop
/* 16A8934 8007B36C 21104300 */  addu       $v0, $v0, $v1
/* 16A8938 8007B370 0880033C */  lui        $v1, %hi(g_FlightObjectiveCounters + 0x8)
/* 16A893C 8007B374 3886638C */  lw         $v1, %lo(g_FlightObjectiveCounters + 0x8)($v1)
/* 16A8940 8007B378 0880043C */  lui        $a0, %hi(g_FlightObjectiveCounters + 0xC)
/* 16A8944 8007B37C 3C86848C */  lw         $a0, %lo(g_FlightObjectiveCounters + 0xC)($a0)
/* 16A8948 8007B380 21104300 */  addu       $v0, $v0, $v1
/* 16A894C 8007B384 21104400 */  addu       $v0, $v0, $a0
/* 16A8950 8007B388 20004228 */  slti       $v0, $v0, 0x20
/* 16A8954 8007B38C 2B004010 */  beqz       $v0, .Llevel_15_8007B43C
/* 16A8958 8007B390 21280000 */   addu      $a1, $zero, $zero
/* 16A895C 8007B394 0780023C */  lui        $v0, %hi(g_Homeworld)
/* 16A8960 8007B398 5C59428C */  lw         $v0, %lo(g_Homeworld)($v0)
/* 16A8964 8007B39C 00000000 */  nop
/* 16A8968 8007B3A0 80100200 */  sll        $v0, $v0, 2
/* 16A896C 8007B3A4 0880013C */  lui        $at, %hi(g_FlightCourseRecords)
/* 16A8970 8007B3A8 21082200 */  addu       $at, $at, $v0
/* 16A8974 8007B3AC 1886228C */  lw         $v0, %lo(g_FlightCourseRecords)($at)
/* 16A8978 8007B3B0 00000000 */  nop
/* 16A897C 8007B3B4 21004014 */  bnez       $v0, .Llevel_15_8007B43C
/* 16A8980 8007B3B8 00000000 */   nop
.Llevel_15_8007B3BC:
/* 16A8984 8007B3BC 0780033C */  lui        $v1, %hi(D_80075720)
/* 16A8988 8007B3C0 2057638C */  lw         $v1, %lo(D_80075720)($v1)
/* 16A898C 8007B3C4 00000000 */  nop
/* 16A8990 8007B3C8 05006010 */  beqz       $v1, .Llevel_15_8007B3E0
/* 16A8994 8007B3CC 01000224 */   addiu     $v0, $zero, 0x1
/* 16A8998 8007B3D0 0C006210 */  beq        $v1, $v0, .Llevel_15_8007B404
/* 16A899C 8007B3D4 21280000 */   addu      $a1, $zero, $zero
/* 16A89A0 8007B3D8 09ED0108 */  j          .Llevel_15_8007B424
/* 16A89A4 8007B3DC 00000000 */   nop
.Llevel_15_8007B3E0:
/* 16A89A8 8007B3E0 0780023C */  lui        $v0, %hi(D_800757A8)
/* 16A89AC 8007B3E4 A857428C */  lw         $v0, %lo(D_800757A8)($v0)
/* 16A89B0 8007B3E8 00000000 */  nop
/* 16A89B4 8007B3EC 09F84000 */  jalr       $v0
/* 16A89B8 8007B3F0 01000424 */   addiu     $a0, $zero, 0x1
/* 16A89BC 8007B3F4 3251000C */  jal        func_800144C8
/* 16A89C0 8007B3F8 00000000 */   nop
/* 16A89C4 8007B3FC 09ED0108 */  j          .Llevel_15_8007B424
/* 16A89C8 8007B400 21280000 */   addu      $a1, $zero, $zero
.Llevel_15_8007B404:
/* 16A89CC 8007B404 0780023C */  lui        $v0, %hi(D_800757A8)
/* 16A89D0 8007B408 A857428C */  lw         $v0, %lo(D_800757A8)($v0)
/* 16A89D4 8007B40C 00000000 */  nop
/* 16A89D8 8007B410 09F84000 */  jalr       $v0
/* 16A89DC 8007B414 21200000 */   addu      $a0, $zero, $zero
/* 16A89E0 8007B418 86B1000C */  jal        func_8002C618
/* 16A89E4 8007B41C 00000000 */   nop
/* 16A89E8 8007B420 21280000 */  addu       $a1, $zero, $zero
.Llevel_15_8007B424:
/* 16A89EC 8007B424 0780023C */  lui        $v0, %hi(g_Spu + 0x2CC)
/* 16A89F0 8007B428 D461428C */  lw         $v0, %lo(g_Spu + 0x2CC)($v0)
/* 16A89F4 8007B42C 00000000 */  nop
/* 16A89F8 8007B430 2D004490 */  lbu        $a0, 0x2D($v0)
/* 16A89FC 8007B434 25ED0108 */  j          .Llevel_15_8007B494
/* 16A8A00 8007B438 10000624 */   addiu     $a2, $zero, 0x10
.Llevel_15_8007B43C:
/* 16A8A04 8007B43C 0780033C */  lui        $v1, %hi(g_Spu + 0x2CC)
/* 16A8A08 8007B440 D461638C */  lw         $v1, %lo(g_Spu + 0x2CC)($v1)
/* 16A8A0C 8007B444 64000224 */  addiu      $v0, $zero, 0x64
/* 16A8A10 8007B448 0780013C */  lui        $at, %hi(D_80075744)
/* 16A8A14 8007B44C 445722AC */  sw         $v0, %lo(D_80075744)($at)
/* 16A8A18 8007B450 24ED0108 */  j          .Llevel_15_8007B490
/* 16A8A1C 8007B454 10000624 */   addiu     $a2, $zero, 0x10
.Llevel_15_8007B458:
/* 16A8A20 8007B458 0780023C */  lui        $v0, %hi(g_Pad)
/* 16A8A24 8007B45C 7873428C */  lw         $v0, %lo(g_Pad)($v0)
/* 16A8A28 8007B460 00000000 */  nop
/* 16A8A2C 8007B464 40084230 */  andi       $v0, $v0, 0x840
/* 16A8A30 8007B468 0C004010 */  beqz       $v0, .Llevel_15_8007B49C
/* 16A8A34 8007B46C 21280000 */   addu      $a1, $zero, $zero
/* 16A8A38 8007B470 10000624 */  addiu      $a2, $zero, 0x10
/* 16A8A3C 8007B474 0780033C */  lui        $v1, %hi(g_Spu + 0x2CC)
/* 16A8A40 8007B478 D461638C */  lw         $v1, %lo(g_Spu + 0x2CC)($v1)
/* 16A8A44 8007B47C 09000224 */  addiu      $v0, $zero, 0x9
/* 16A8A48 8007B480 0780013C */  lui        $at, %hi(D_80075744)
/* 16A8A4C 8007B484 445722AC */  sw         $v0, %lo(D_80075744)($at)
/* 16A8A50 8007B488 0780013C */  lui        $at, %hi(D_800757CC)
/* 16A8A54 8007B48C CC5720AC */  sw         $zero, %lo(D_800757CC)($at)
.Llevel_15_8007B490:
/* 16A8A58 8007B490 2D006490 */  lbu        $a0, 0x2D($v1)
.Llevel_15_8007B494:
/* 16A8A5C 8007B494 9E56010C */  jal        PlaySound
/* 16A8A60 8007B498 21380000 */   addu      $a3, $zero, $zero
.Llevel_15_8007B49C:
/* 16A8A64 8007B49C 1400BF8F */  lw         $ra, 0x14($sp)
/* 16A8A68 8007B4A0 1000B08F */  lw         $s0, 0x10($sp)
/* 16A8A6C 8007B4A4 1800BD27 */  addiu      $sp, $sp, 0x18
/* 16A8A70 8007B4A8 0800E003 */  jr         $ra
/* 16A8A74 8007B4AC 00000000 */   nop
.size func_level_15_8007B1FC, . - func_level_15_8007B1FC
