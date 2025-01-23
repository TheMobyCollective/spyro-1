.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80032AB0
/* 232B0 80032AB0 0780023C */  lui        $v0, %hi(g_Pad)
/* 232B4 80032AB4 7873428C */  lw         $v0, %lo(g_Pad)($v0)
/* 232B8 80032AB8 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 232BC 80032ABC 10004230 */  andi       $v0, $v0, 0x10
/* 232C0 80032AC0 0D004010 */  beqz       $v0, .L80032AF8
/* 232C4 80032AC4 1000BFAF */   sw        $ra, 0x10($sp)
/* 232C8 80032AC8 0880063C */  lui        $a2, %hi(D_80078D78)
/* 232CC 80032ACC 788DC624 */  addiu      $a2, $a2, %lo(D_80078D78)
/* 232D0 80032AD0 01000224 */  addiu      $v0, $zero, 0x1
/* 232D4 80032AD4 21200000 */  addu       $a0, $zero, $zero
/* 232D8 80032AD8 4000C524 */  addiu      $a1, $a2, 0x40
/* 232DC 80032ADC 0000C2AC */  sw         $v0, 0x0($a2)
/* 232E0 80032AE0 0880013C */  lui        $at, %hi(D_80078D88)
/* 232E4 80032AE4 888D20AC */  sw         $zero, %lo(D_80078D88)($at)
/* 232E8 80032AE8 0880013C */  lui        $at, %hi(D_80078D7C)
/* 232EC 80032AEC 7C8D20AC */  sw         $zero, %lo(D_80078D7C)($at)
/* 232F0 80032AF0 8A9D010C */  jal        MemCardSync
/* 232F4 80032AF4 4400C624 */   addiu     $a2, $a2, 0x44
.L80032AF8:
/* 232F8 80032AF8 1000BF8F */  lw         $ra, 0x10($sp)
/* 232FC 80032AFC 1800BD27 */  addiu      $sp, $sp, 0x18
/* 23300 80032B00 0800E003 */  jr         $ra
/* 23304 80032B04 00000000 */   nop
.size func_80032AB0, . - func_80032AB0
