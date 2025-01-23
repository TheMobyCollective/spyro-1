.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002C420
/* 1CC20 8002C420 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1CC24 8002C424 1000B0AF */  sw         $s0, 0x10($sp)
/* 1CC28 8002C428 21808000 */  addu       $s0, $a0, $zero
/* 1CC2C 8002C42C 03000012 */  beqz       $s0, .L8002C43C
/* 1CC30 8002C430 1400BFAF */   sw        $ra, 0x14($sp)
/* 1CC34 8002C434 CA5A010C */  jal        func_80056B28
/* 1CC38 8002C438 21200000 */   addu      $a0, $zero, $zero
.L8002C43C:
/* 1CC3C 8002C43C 21280000 */  addu       $a1, $zero, $zero
/* 1CC40 8002C440 0780023C */  lui        $v0, %hi(g_Spu + 0x2CC)
/* 1CC44 8002C444 D461428C */  lw         $v0, %lo(g_Spu + 0x2CC)($v0)
/* 1CC48 8002C448 10000624 */  addiu      $a2, $zero, 0x10
/* 1CC4C 8002C44C 2C004490 */  lbu        $a0, 0x2C($v0)
/* 1CC50 8002C450 9E56010C */  jal        PlaySound
/* 1CC54 8002C454 21380000 */   addu      $a3, $zero, $zero
/* 1CC58 8002C458 0780033C */  lui        $v1, %hi(D_80075690)
/* 1CC5C 8002C45C 9056638C */  lw         $v1, %lo(D_80075690)($v1)
/* 1CC60 8002C460 02000224 */  addiu      $v0, $zero, 0x2
/* 1CC64 8002C464 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1CC68 8002C468 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1CC6C 8002C46C 0780013C */  lui        $at, %hi(D_80075720)
/* 1CC70 8002C470 205720AC */  sw         $zero, %lo(D_80075720)($at)
/* 1CC74 8002C474 0780013C */  lui        $at, %hi(D_800757C8)
/* 1CC78 8002C478 C85720AC */  sw         $zero, %lo(D_800757C8)($at)
/* 1CC7C 8002C47C 0780013C */  lui        $at, %hi(D_8007568C)
/* 1CC80 8002C480 8C5620AC */  sw         $zero, %lo(D_8007568C)($at)
/* 1CC84 8002C484 07006010 */  beqz       $v1, .L8002C4A4
/* 1CC88 8002C488 00000000 */   nop
/* 1CC8C 8002C48C 24000012 */  beqz       $s0, .L8002C520
/* 1CC90 8002C490 00000000 */   nop
/* 1CC94 8002C494 0780013C */  lui        $at, %hi(D_800758B8)
/* 1CC98 8002C498 B85820AC */  sw         $zero, %lo(D_800758B8)($at)
/* 1CC9C 8002C49C 48B10008 */  j          .L8002C520
/* 1CCA0 8002C4A0 00000000 */   nop
.L8002C4A4:
/* 1CCA4 8002C4A4 8051010C */  jal        func_80054600
/* 1CCA8 8002C4A8 21200000 */   addu      $a0, $zero, $zero
/* 1CCAC 8002C4AC 05000012 */  beqz       $s0, .L8002C4C4
/* 1CCB0 8002C4B0 01000224 */   addiu     $v0, $zero, 0x1
/* 1CCB4 8002C4B4 0780013C */  lui        $at, %hi(D_800758B8)
/* 1CCB8 8002C4B8 B85820AC */  sw         $zero, %lo(D_800758B8)($at)
/* 1CCBC 8002C4BC 46B10008 */  j          .L8002C518
/* 1CCC0 8002C4C0 00000000 */   nop
.L8002C4C4:
/* 1CCC4 8002C4C4 0780013C */  lui        $at, %hi(D_80077FA8)
/* 1CCC8 8002C4C8 A87F22A0 */  sb         $v0, %lo(D_80077FA8)($at)
/* 1CCCC 8002C4CC 0780013C */  lui        $at, %hi(D_80077FA9)
/* 1CCD0 8002C4D0 A97F22A0 */  sb         $v0, %lo(D_80077FA9)($at)
/* 1CCD4 8002C4D4 0780013C */  lui        $at, %hi(D_80077FAA)
/* 1CCD8 8002C4D8 AA7F22A0 */  sb         $v0, %lo(D_80077FAA)($at)
/* 1CCDC 8002C4DC 0780013C */  lui        $at, %hi(D_80077FAB)
/* 1CCE0 8002C4E0 AB7F22A0 */  sb         $v0, %lo(D_80077FAB)($at)
/* 1CCE4 8002C4E4 0780013C */  lui        $at, %hi(D_80077FAC)
/* 1CCE8 8002C4E8 AC7F22A0 */  sb         $v0, %lo(D_80077FAC)($at)
/* 1CCEC 8002C4EC 0C000224 */  addiu      $v0, $zero, 0xC
/* 1CCF0 8002C4F0 0780013C */  lui        $at, %hi(D_80077FAD)
/* 1CCF4 8002C4F4 AD7F22A0 */  sb         $v0, %lo(D_80077FAD)($at)
/* 1CCF8 8002C4F8 0780013C */  lui        $at, %hi(D_80077FAE)
/* 1CCFC 8002C4FC AE7F22A0 */  sb         $v0, %lo(D_80077FAE)($at)
/* 1CD00 8002C500 0780013C */  lui        $at, %hi(D_80077FAF)
/* 1CD04 8002C504 AF7F22A0 */  sb         $v0, %lo(D_80077FAF)($at)
/* 1CD08 8002C508 0780013C */  lui        $at, %hi(D_80077FB0)
/* 1CD0C 8002C50C B07F22A0 */  sb         $v0, %lo(D_80077FB0)($at)
/* 1CD10 8002C510 0780013C */  lui        $at, %hi(D_80077FB1)
/* 1CD14 8002C514 B17F22A0 */  sb         $v0, %lo(D_80077FB1)($at)
.L8002C518:
/* 1CD18 8002C518 6252010C */  jal        func_80054988
/* 1CD1C 8002C51C 00000000 */   nop
.L8002C520:
/* 1CD20 8002C520 1400BF8F */  lw         $ra, 0x14($sp)
/* 1CD24 8002C524 1000B08F */  lw         $s0, 0x10($sp)
/* 1CD28 8002C528 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1CD2C 8002C52C 0800E003 */  jr         $ra
/* 1CD30 8002C530 00000000 */   nop
.size func_8002C420, . - func_8002C420
