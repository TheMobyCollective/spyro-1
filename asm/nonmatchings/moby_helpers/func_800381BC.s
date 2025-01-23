.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_800381BC
/* 289BC 800381BC 2328A400 */  subu       $a1, $a1, $a0
/* 289C0 800381C0 8100A228 */  slti       $v0, $a1, 0x81
/* 289C4 800381C4 03004014 */  bnez       $v0, .L800381D4
/* 289C8 800381C8 80FFA228 */   slti      $v0, $a1, -0x80
/* 289CC 800381CC 00FFA524 */  addiu      $a1, $a1, -0x100
/* 289D0 800381D0 80FFA228 */  slti       $v0, $a1, -0x80
.L800381D4:
/* 289D4 800381D4 02004010 */  beqz       $v0, .L800381E0
/* 289D8 800381D8 00000000 */   nop
/* 289DC 800381DC 0001A524 */  addiu      $a1, $a1, 0x100
.L800381E0:
/* 289E0 800381E0 0800E003 */  jr         $ra
/* 289E4 800381E4 2110A000 */   addu      $v0, $a1, $zero
.size func_800381BC, . - func_800381BC
