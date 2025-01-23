.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_800495D8
/* 39DD8 800495D8 0880053C */  lui        $a1, %hi(g_Spyro + 0x25)
/* 39DDC 800495DC 7D8AA524 */  addiu      $a1, $a1, %lo(g_Spyro + 0x25)
/* 39DE0 800495E0 0000A290 */  lbu        $v0, 0x0($a1)
/* 39DE4 800495E4 00000000 */  nop
/* 39DE8 800495E8 21184400 */  addu       $v1, $v0, $a0
/* 39DEC 800495EC FF006230 */  andi       $v0, $v1, 0xFF
/* 39DF0 800495F0 1000422C */  sltiu      $v0, $v0, 0x10
/* 39DF4 800495F4 18004014 */  bnez       $v0, .L80049658
/* 39DF8 800495F8 0000A3A0 */   sb        $v1, 0x0($a1)
/* 39DFC 800495FC F0FF6224 */  addiu      $v0, $v1, -0x10
/* 39E00 80049600 0000A2A0 */  sb         $v0, 0x0($a1)
/* 39E04 80049604 0880043C */  lui        $a0, %hi(g_Spyro + 0x21)
/* 39E08 80049608 798A8490 */  lbu        $a0, %lo(g_Spyro + 0x21)($a0)
/* 39E0C 8004960C 0880033C */  lui        $v1, %hi(g_Spyro + 0x1B)
/* 39E10 80049610 738A6390 */  lbu        $v1, %lo(g_Spyro + 0x1B)($v1)
/* 39E14 80049614 01008224 */  addiu      $v0, $a0, 0x1
/* 39E18 80049618 0880013C */  lui        $at, %hi(g_Spyro + 0x1A)
/* 39E1C 8004961C 728A23A0 */  sb         $v1, %lo(g_Spyro + 0x1A)($at)
/* 39E20 80049620 80180300 */  sll        $v1, $v1, 2
/* 39E24 80049624 0880013C */  lui        $at, %hi(g_Spyro + 0x20)
/* 39E28 80049628 788A24A0 */  sb         $a0, %lo(g_Spyro + 0x20)($at)
/* 39E2C 8004962C 0880013C */  lui        $at, %hi(g_Spyro + 0x21)
/* 39E30 80049630 798A22A0 */  sb         $v0, %lo(g_Spyro + 0x21)($at)
/* 39E34 80049634 0780013C */  lui        $at, %hi(D_8006C4A2)
/* 39E38 80049638 21082300 */  addu       $at, $at, $v1
/* 39E3C 8004963C A2C42390 */  lbu        $v1, %lo(D_8006C4A2)($at)
/* 39E40 80049640 FF004230 */  andi       $v0, $v0, 0xFF
/* 39E44 80049644 2B104300 */  sltu       $v0, $v0, $v1
/* 39E48 80049648 03004014 */  bnez       $v0, .L80049658
/* 39E4C 8004964C FFFF6224 */   addiu     $v0, $v1, -0x1
/* 39E50 80049650 0880013C */  lui        $at, %hi(g_Spyro + 0x21)
/* 39E54 80049654 798A22A0 */  sb         $v0, %lo(g_Spyro + 0x21)($at)
.L80049658:
/* 39E58 80049658 0800E003 */  jr         $ra
/* 39E5C 8004965C 00000000 */   nop
.size func_800495D8, . - func_800495D8
