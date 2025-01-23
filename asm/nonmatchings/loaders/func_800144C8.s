.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_800144C8
/* 4CC8 800144C8 C0FFBD27 */  addiu      $sp, $sp, -0x40
/* 4CCC 800144CC 3800BFAF */  sw         $ra, 0x38($sp)
/* 4CD0 800144D0 CA5A010C */  jal        func_80056B28
/* 4CD4 800144D4 21200000 */   addu      $a0, $zero, $zero
/* 4CD8 800144D8 0780023C */  lui        $v0, %hi(D_80075964)
/* 4CDC 800144DC 6459428C */  lw         $v0, %lo(D_80075964)($v0)
/* 4CE0 800144E0 0780043C */  lui        $a0, %hi(D_80076B90)
/* 4CE4 800144E4 906B848C */  lw         $a0, %lo(D_80076B90)($a0)
/* 4CE8 800144E8 0880073C */  lui        $a3, %hi(D_80078600)
/* 4CEC 800144EC 0086E78C */  lw         $a3, %lo(D_80078600)($a3)
/* 4CF0 800144F0 0880053C */  lui        $a1, %hi(D_800785E4)
/* 4CF4 800144F4 E485A58C */  lw         $a1, %lo(D_800785E4)($a1)
/* 4CF8 800144F8 0880063C */  lui        $a2, %hi(D_80078604)
/* 4CFC 800144FC 0486C68C */  lw         $a2, %lo(D_80078604)($a2)
/* 4D00 80014500 00110200 */  sll        $v0, $v0, 4
/* 4D04 80014504 0880013C */  lui        $at, %hi(D_8007A720)
/* 4D08 80014508 21082200 */  addu       $at, $at, $v0
/* 4D0C 8001450C 20A7238C */  lw         $v1, %lo(D_8007A720)($at)
/* 4D10 80014510 58020224 */  addiu      $v0, $zero, 0x258
/* 4D14 80014514 1000A2AF */  sw         $v0, 0x10($sp)
/* 4D18 80014518 4059000C */  jal        CDLoadSync
/* 4D1C 8001451C 2138E300 */   addu      $a3, $a3, $v1
/* 4D20 80014520 934D000C */  jal        func_8001364C
/* 4D24 80014524 01000424 */   addiu     $a0, $zero, 0x1
/* 4D28 80014528 0780023C */  lui        $v0, %hi(D_80075690)
/* 4D2C 8001452C 9056428C */  lw         $v0, %lo(D_80075690)($v0)
/* 4D30 80014530 00000000 */  nop
/* 4D34 80014534 02004010 */  beqz       $v0, .L80014540
/* 4D38 80014538 21200000 */   addu      $a0, $zero, $zero
/* 4D3C 8001453C 20000424 */  addiu      $a0, $zero, 0x20
.L80014540:
/* 4D40 80014540 72FF000C */  jal        func_8003FDC8
/* 4D44 80014544 00000000 */   nop
/* 4D48 80014548 03000224 */  addiu      $v0, $zero, 0x3
/* 4D4C 8001454C 0880013C */  lui        $at, %hi(g_Spyro + 0x164)
/* 4D50 80014550 BC8B22AC */  sw         $v0, %lo(g_Spyro + 0x164)($at)
/* 4D54 80014554 3800BF8F */  lw         $ra, 0x38($sp)
/* 4D58 80014558 4000BD27 */  addiu      $sp, $sp, 0x40
/* 4D5C 8001455C 0800E003 */  jr         $ra
/* 4D60 80014560 00000000 */   nop
.size func_800144C8, . - func_800144C8
