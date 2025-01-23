.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003CBB8
/* 2D3B8 8003CBB8 0880073C */  lui        $a3, %hi(g_Spyro + 0x24)
/* 2D3BC 8003CBBC 7C8AE724 */  addiu      $a3, $a3, %lo(g_Spyro + 0x24)
/* 2D3C0 8003CBC0 0000E290 */  lbu        $v0, 0x0($a3)
/* 2D3C4 8003CBC4 00000000 */  nop
/* 2D3C8 8003CBC8 21184400 */  addu       $v1, $v0, $a0
/* 2D3CC 8003CBCC FF006230 */  andi       $v0, $v1, 0xFF
/* 2D3D0 8003CBD0 1000422C */  sltiu      $v0, $v0, 0x10
/* 2D3D4 8003CBD4 40004014 */  bnez       $v0, .L8003CCD8
/* 2D3D8 8003CBD8 0000E3A0 */   sb        $v1, 0x0($a3)
/* 2D3DC 8003CBDC F0FF6224 */  addiu      $v0, $v1, -0x10
/* 2D3E0 8003CBE0 0000E2A0 */  sb         $v0, 0x0($a3)
/* 2D3E4 8003CBE4 0880043C */  lui        $a0, %hi(g_Spyro + 0x1F)
/* 2D3E8 8003CBE8 778A8490 */  lbu        $a0, %lo(g_Spyro + 0x1F)($a0)
/* 2D3EC 8003CBEC 0880033C */  lui        $v1, %hi(g_Spyro + 0x19)
/* 2D3F0 8003CBF0 718A6390 */  lbu        $v1, %lo(g_Spyro + 0x19)($v1)
/* 2D3F4 8003CBF4 01008224 */  addiu      $v0, $a0, 0x1
/* 2D3F8 8003CBF8 0880013C */  lui        $at, %hi(g_Spyro + 0x18)
/* 2D3FC 8003CBFC 708A23A0 */  sb         $v1, %lo(g_Spyro + 0x18)($at)
/* 2D400 8003CC00 80180300 */  sll        $v1, $v1, 2
/* 2D404 8003CC04 0880013C */  lui        $at, %hi(g_Spyro + 0x1E)
/* 2D408 8003CC08 768A24A0 */  sb         $a0, %lo(g_Spyro + 0x1E)($at)
/* 2D40C 8003CC0C 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 2D410 8003CC10 778A22A0 */  sb         $v0, %lo(g_Spyro + 0x1F)($at)
/* 2D414 8003CC14 0780013C */  lui        $at, %hi(D_8006C4A2)
/* 2D418 8003CC18 21082300 */  addu       $at, $at, $v1
/* 2D41C 8003CC1C A2C42390 */  lbu        $v1, %lo(D_8006C4A2)($at)
/* 2D420 8003CC20 FF004230 */  andi       $v0, $v0, 0xFF
/* 2D424 8003CC24 2B104300 */  sltu       $v0, $v0, $v1
/* 2D428 8003CC28 2C004014 */  bnez       $v0, .L8003CCDC
/* 2D42C 8003CC2C 21100000 */   addu      $v0, $zero, $zero
/* 2D430 8003CC30 0880053C */  lui        $a1, %hi(g_Spyro + 0x78)
/* 2D434 8003CC34 D08AA58C */  lw         $a1, %lo(g_Spyro + 0x78)($a1)
/* 2D438 8003CC38 0780023C */  lui        $v0, %hi(spyro_StateDefaultAnimation)
/* 2D43C 8003CC3C 70C44224 */  addiu      $v0, $v0, %lo(spyro_StateDefaultAnimation)
/* 2D440 8003CC40 2130A200 */  addu       $a2, $a1, $v0
/* 2D444 8003CC44 0000C290 */  lbu        $v0, 0x0($a2)
/* 2D448 8003CC48 0880013C */  lui        $at, %hi(g_Spyro + 0x19)
/* 2D44C 8003CC4C 718A22A0 */  sb         $v0, %lo(g_Spyro + 0x19)($at)
/* 2D450 8003CC50 0880023C */  lui        $v0, %hi(g_Spyro + 0x5C)
/* 2D454 8003CC54 B48A428C */  lw         $v0, %lo(g_Spyro + 0x5C)($v0)
/* 2D458 8003CC58 0780043C */  lui        $a0, %hi(D_8006BC84)
/* 2D45C 8003CC5C 84BC8424 */  addiu      $a0, $a0, %lo(D_8006BC84)
/* 2D460 8003CC60 40180200 */  sll        $v1, $v0, 1
/* 2D464 8003CC64 21186200 */  addu       $v1, $v1, $v0
/* 2D468 8003CC68 00110300 */  sll        $v0, $v1, 4
/* 2D46C 8003CC6C 23104300 */  subu       $v0, $v0, $v1
/* 2D470 8003CC70 21104400 */  addu       $v0, $v0, $a0
/* 2D474 8003CC74 21104500 */  addu       $v0, $v0, $a1
/* 2D478 8003CC78 00004390 */  lbu        $v1, 0x0($v0)
/* 2D47C 8003CC7C 0A000224 */  addiu      $v0, $zero, 0xA
/* 2D480 8003CC80 0B006214 */  bne        $v1, $v0, .L8003CCB0
/* 2D484 8003CC84 01000224 */   addiu     $v0, $zero, 0x1
/* 2D488 8003CC88 0000C290 */  lbu        $v0, 0x0($a2)
/* 2D48C 8003CC8C 00000000 */  nop
/* 2D490 8003CC90 80100200 */  sll        $v0, $v0, 2
/* 2D494 8003CC94 0780013C */  lui        $at, %hi(spyro_AnimationDetails)
/* 2D498 8003CC98 21082200 */  addu       $at, $at, $v0
/* 2D49C 8003CC9C A0C42290 */  lbu        $v0, %lo(spyro_AnimationDetails)($at)
/* 2D4A0 8003CCA0 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 2D4A4 8003CCA4 778A22A0 */  sb         $v0, %lo(g_Spyro + 0x1F)($at)
/* 2D4A8 8003CCA8 30F30008 */  j          .L8003CCC0
/* 2D4AC 8003CCAC 00000000 */   nop
.L8003CCB0:
/* 2D4B0 8003CCB0 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 2D4B4 8003CCB4 778A22A0 */  sb         $v0, %lo(g_Spyro + 0x1F)($at)
/* 2D4B8 8003CCB8 04000224 */  addiu      $v0, $zero, 0x4
/* 2D4BC 8003CCBC 0000E2A0 */  sb         $v0, 0x0($a3)
.L8003CCC0:
/* 2D4C0 8003CCC0 0880033C */  lui        $v1, %hi(g_Spyro + 0x78)
/* 2D4C4 8003CCC4 D08A638C */  lw         $v1, %lo(g_Spyro + 0x78)($v1)
/* 2D4C8 8003CCC8 0880013C */  lui        $at, %hi(g_Spyro + 0x5C)
/* 2D4CC 8003CCCC B48A23AC */  sw         $v1, %lo(g_Spyro + 0x5C)($at)
/* 2D4D0 8003CCD0 37F30008 */  j          .L8003CCDC
/* 2D4D4 8003CCD4 01000224 */   addiu     $v0, $zero, 0x1
.L8003CCD8:
/* 2D4D8 8003CCD8 21100000 */  addu       $v0, $zero, $zero
.L8003CCDC:
/* 2D4DC 8003CCDC 0800E003 */  jr         $ra
/* 2D4E0 8003CCE0 00000000 */   nop
.size func_8003CBB8, . - func_8003CBB8
