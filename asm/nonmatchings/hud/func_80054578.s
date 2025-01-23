.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80054578
/* 44D78 80054578 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 44D7C 8005457C 1000B0AF */  sw         $s0, 0x10($sp)
/* 44D80 80054580 0780103C */  lui        $s0, %hi(D_80077FC8)
/* 44D84 80054584 C87F1026 */  addiu      $s0, $s0, %lo(D_80077FC8)
/* 44D88 80054588 21200000 */  addu       $a0, $zero, $zero
/* 44D8C 8005458C 0780023C */  lui        $v0, %hi(D_80075964)
/* 44D90 80054590 6459428C */  lw         $v0, %lo(D_80075964)($v0)
/* 44D94 80054594 04000524 */  addiu      $a1, $zero, 0x4
/* 44D98 80054598 1400BFAF */  sw         $ra, 0x14($sp)
/* 44D9C 8005459C 80100200 */  sll        $v0, $v0, 2
/* 44DA0 800545A0 0780013C */  lui        $at, %hi(g_LevelGemCount)
/* 44DA4 800545A4 21082200 */  addu       $at, $at, $v0
/* 44DA8 800545A8 2074268C */  lw         $a2, %lo(g_LevelGemCount)($at)
/* 44DAC 800545AC 01000724 */  addiu      $a3, $zero, 0x1
/* 44DB0 800545B0 B950010C */  jal        func_800542E4
/* 44DB4 800545B4 000006AE */   sw        $a2, 0x0($s0)
/* 44DB8 800545B8 E0FF0392 */  lbu        $v1, -0x20($s0)
/* 44DBC 800545BC 00000000 */  nop
/* 44DC0 800545C0 FFFF6224 */  addiu      $v0, $v1, -0x1
/* 44DC4 800545C4 0200422C */  sltiu      $v0, $v0, 0x2
/* 44DC8 800545C8 05004014 */  bnez       $v0, .L800545E0
/* 44DCC 800545CC 03000224 */   addiu     $v0, $zero, 0x3
/* 44DD0 800545D0 FF006330 */  andi       $v1, $v1, 0xFF
/* 44DD4 800545D4 04000224 */  addiu      $v0, $zero, 0x4
/* 44DD8 800545D8 04006214 */  bne        $v1, $v0, .L800545EC
/* 44DDC 800545DC 03000224 */   addiu     $v0, $zero, 0x3
.L800545E0:
/* 44DE0 800545E0 E0FF02A2 */  sb         $v0, -0x20($s0)
/* 44DE4 800545E4 0D000224 */  addiu      $v0, $zero, 0xD
/* 44DE8 800545E8 E5FF02A2 */  sb         $v0, -0x1B($s0)
.L800545EC:
/* 44DEC 800545EC 1400BF8F */  lw         $ra, 0x14($sp)
/* 44DF0 800545F0 1000B08F */  lw         $s0, 0x10($sp)
/* 44DF4 800545F4 1800BD27 */  addiu      $sp, $sp, 0x18
/* 44DF8 800545F8 0800E003 */  jr         $ra
/* 44DFC 800545FC 00000000 */   nop
.size func_80054578, . - func_80054578
