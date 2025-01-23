.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_800385BC
/* 28DBC 800385BC E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 28DC0 800385C0 1000B0AF */  sw         $s0, 0x10($sp)
/* 28DC4 800385C4 21808000 */  addu       $s0, $a0, $zero
/* 28DC8 800385C8 1400B1AF */  sw         $s1, 0x14($sp)
/* 28DCC 800385CC 2188A000 */  addu       $s1, $a1, $zero
/* 28DD0 800385D0 08000012 */  beqz       $s0, .L800385F4
/* 28DD4 800385D4 1800BFAF */   sw        $ra, 0x18($sp)
/* 28DD8 800385D8 21280002 */  addu       $a1, $s0, $zero
/* 28DDC 800385DC 0780023C */  lui        $v0, %hi(g_Spu + 0x2CC)
/* 28DE0 800385E0 D461428C */  lw         $v0, %lo(g_Spu + 0x2CC)($v0)
/* 28DE4 800385E4 08000624 */  addiu      $a2, $zero, 0x8
/* 28DE8 800385E8 26004490 */  lbu        $a0, 0x26($v0)
/* 28DEC 800385EC 83E10008 */  j          .L8003860C
/* 28DF0 800385F0 54000726 */   addiu     $a3, $s0, 0x54
.L800385F4:
/* 28DF4 800385F4 21280000 */  addu       $a1, $zero, $zero
/* 28DF8 800385F8 0780023C */  lui        $v0, %hi(g_Spu + 0x2CC)
/* 28DFC 800385FC D461428C */  lw         $v0, %lo(g_Spu + 0x2CC)($v0)
/* 28E00 80038600 10000624 */  addiu      $a2, $zero, 0x10
/* 28E04 80038604 26004490 */  lbu        $a0, 0x26($v0)
/* 28E08 80038608 21380000 */  addu       $a3, $zero, $zero
.L8003860C:
/* 28E0C 8003860C 9E56010C */  jal        PlaySound
/* 28E10 80038610 00000000 */   nop
/* 28E14 80038614 21200002 */  addu       $a0, $s0, $zero
/* 28E18 80038618 304C010C */  jal        func_800530C0
/* 28E1C 8003861C 21282002 */   addu      $a1, $s1, $zero
/* 28E20 80038620 1800BF8F */  lw         $ra, 0x18($sp)
/* 28E24 80038624 1400B18F */  lw         $s1, 0x14($sp)
/* 28E28 80038628 1000B08F */  lw         $s0, 0x10($sp)
/* 28E2C 8003862C 2000BD27 */  addiu      $sp, $sp, 0x20
/* 28E30 80038630 0800E003 */  jr         $ra
/* 28E34 80038634 00000000 */   nop
.size func_800385BC, . - func_800385BC
