.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80012CF0
/* 34F0 80012CF0 0780013C */  lui        $at, %hi(g_Spu + 0x2CC)
/* 34F4 80012CF4 D46124AC */  sw         $a0, %lo(g_Spu + 0x2CC)($at)
/* 34F8 80012CF8 00018424 */  addiu      $a0, $a0, 0x100
/* 34FC 80012CFC 0000868C */  lw         $a2, 0x0($a0)
/* 3500 80012D00 04008424 */  addiu      $a0, $a0, 0x4
/* 3504 80012D04 0780013C */  lui        $at, %hi(g_Spu + 0x2C8)
/* 3508 80012D08 D06124AC */  sw         $a0, %lo(g_Spu + 0x2C8)($at)
/* 350C 80012D0C 1000A010 */  beqz       $a1, .L80012D50
/* 3510 80012D10 00000000 */   nop
/* 3514 80012D14 FFFFC624 */  addiu      $a2, $a2, -0x1
/* 3518 80012D18 0D00C004 */  bltz       $a2, .L80012D50
/* 351C 80012D1C 00000000 */   nop
/* 3520 80012D20 80100600 */  sll        $v0, $a2, 2
/* 3524 80012D24 21104600 */  addu       $v0, $v0, $a2
/* 3528 80012D28 80200200 */  sll        $a0, $v0, 2
.L80012D2C:
/* 352C 80012D2C 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 3530 80012D30 D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 3534 80012D34 FFFFC624 */  addiu      $a2, $a2, -0x1
/* 3538 80012D38 21188300 */  addu       $v1, $a0, $v1
/* 353C 80012D3C 0000628C */  lw         $v0, 0x0($v1)
/* 3540 80012D40 ECFF8424 */  addiu      $a0, $a0, -0x14
/* 3544 80012D44 10104224 */  addiu      $v0, $v0, 0x1010
/* 3548 80012D48 F8FFC104 */  bgez       $a2, .L80012D2C
/* 354C 80012D4C 000062AC */   sw        $v0, 0x0($v1)
.L80012D50:
/* 3550 80012D50 0800E003 */  jr         $ra
/* 3554 80012D54 00000000 */   nop
.size func_80012CF0, . - func_80012CF0
