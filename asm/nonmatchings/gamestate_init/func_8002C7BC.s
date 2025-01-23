.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002C7BC
/* 1CFBC 8002C7BC E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 1CFC0 8002C7C0 FEFF033C */  lui        $v1, (0xFFFE3E00 >> 16)
/* 1CFC4 8002C7C4 003E6334 */  ori        $v1, $v1, (0xFFFE3E00 & 0xFFFF)
/* 1CFC8 8002C7C8 1000A427 */  addiu      $a0, $sp, 0x10
/* 1CFCC 8002C7CC 0880053C */  lui        $a1, %hi(D_800785F0)
/* 1CFD0 8002C7D0 F085A58C */  lw         $a1, %lo(D_800785F0)($a1)
/* 1CFD4 8002C7D4 00020224 */  addiu      $v0, $zero, 0x200
/* 1CFD8 8002C7D8 1000A2A7 */  sh         $v0, 0x10($sp)
/* 1CFDC 8002C7DC 00010224 */  addiu      $v0, $zero, 0x100
/* 1CFE0 8002C7E0 1400A2A7 */  sh         $v0, 0x14($sp)
/* 1CFE4 8002C7E4 E1000224 */  addiu      $v0, $zero, 0xE1
/* 1CFE8 8002C7E8 1800BFAF */  sw         $ra, 0x18($sp)
/* 1CFEC 8002C7EC 1200A0A7 */  sh         $zero, 0x12($sp)
/* 1CFF0 8002C7F0 1600A2A7 */  sh         $v0, 0x16($sp)
/* 1CFF4 8002C7F4 8A7E010C */  jal        LoadImage
/* 1CFF8 8002C7F8 2128A300 */   addu      $a1, $a1, $v1
/* 1CFFC 8002C7FC D97D010C */  jal        DrawSync
/* 1D000 8002C800 21200000 */   addu      $a0, $zero, $zero
/* 1D004 8002C804 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1D008 8002C808 D85720AC */  sw         $zero, %lo(g_Gamestate)($at)
/* 1D00C 8002C80C 1F63010C */  jal        SpecularReset
/* 1D010 8002C810 00000000 */   nop
/* 1D014 8002C814 0780043C */  lui        $a0, %hi(D_800774B0)
/* 1D018 8002C818 B074848C */  lw         $a0, %lo(D_800774B0)($a0)
/* 1D01C 8002C81C 0780013C */  lui        $at, %hi(D_80077FA8)
/* 1D020 8002C820 A87F20A0 */  sb         $zero, %lo(D_80077FA8)($at)
/* 1D024 8002C824 0780013C */  lui        $at, %hi(D_80077FA9)
/* 1D028 8002C828 A97F20A0 */  sb         $zero, %lo(D_80077FA9)($at)
/* 1D02C 8002C82C 0780013C */  lui        $at, %hi(D_80077FAA)
/* 1D030 8002C830 AA7F20A0 */  sb         $zero, %lo(D_80077FAA)($at)
/* 1D034 8002C834 0780013C */  lui        $at, %hi(D_80077FAB)
/* 1D038 8002C838 AB7F20A0 */  sb         $zero, %lo(D_80077FAB)($at)
/* 1D03C 8002C83C 0780013C */  lui        $at, %hi(D_80077FAC)
/* 1D040 8002C840 AC7F20A0 */  sb         $zero, %lo(D_80077FAC)($at)
/* 1D044 8002C844 FD59010C */  jal        func_800567F4
/* 1D048 8002C848 08000524 */   addiu     $a1, $zero, 0x8
/* 1D04C 8002C84C 1800BF8F */  lw         $ra, 0x18($sp)
/* 1D050 8002C850 2000BD27 */  addiu      $sp, $sp, 0x20
/* 1D054 8002C854 0800E003 */  jr         $ra
/* 1D058 8002C858 00000000 */   nop
.size func_8002C7BC, . - func_8002C7BC
