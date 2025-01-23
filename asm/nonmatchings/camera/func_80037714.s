.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80037714
/* 27F14 80037714 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 27F18 80037718 21288000 */  addu       $a1, $a0, $zero
/* 27F1C 8003771C 0780023C */  lui        $v0, %hi(g_Camera + 0xEC)
/* 27F20 80037720 BC6E4224 */  addiu      $v0, $v0, %lo(g_Camera + 0xEC)
/* 27F24 80037724 3CFF4424 */  addiu      $a0, $v0, -0xC4
/* 27F28 80037728 1000BFAF */  sw         $ra, 0x10($sp)
/* 27F2C 8003772C 000045AC */  sw         $a1, 0x0($v0)
/* 27F30 80037730 C05D000C */  jal        VecCopy
/* 27F34 80037734 1800A524 */   addiu     $a1, $a1, 0x18
/* 27F38 80037738 0880043C */  lui        $a0, %hi(g_Spyro + 0xF4)
/* 27F3C 8003773C 4C8B8424 */  addiu      $a0, $a0, %lo(g_Spyro + 0xF4)
/* 27F40 80037740 BC5D000C */  jal        VecNull
/* 27F44 80037744 00000000 */   nop
/* 27F48 80037748 0780033C */  lui        $v1, %hi(g_Camera + 0xEC)
/* 27F4C 8003774C BC6E638C */  lw         $v1, %lo(g_Camera + 0xEC)($v1)
/* 27F50 80037750 00DD0224 */  addiu      $v0, $zero, -0x2300
/* 27F54 80037754 0880013C */  lui        $at, %hi(g_Spyro + 0xFC)
/* 27F58 80037758 548B22AC */  sw         $v0, %lo(g_Spyro + 0xFC)($at)
/* 27F5C 8003775C 2400628C */  lw         $v0, 0x24($v1)
/* 27F60 80037760 0780013C */  lui        $at, %hi(g_Camera + 0x4C)
/* 27F64 80037764 1C6E22A4 */  sh         $v0, %lo(g_Camera + 0x4C)($at)
/* 27F68 80037768 2800628C */  lw         $v0, 0x28($v1)
/* 27F6C 8003776C 0080043C */  lui        $a0, (0x8000000E >> 16)
/* 27F70 80037770 0780013C */  lui        $at, %hi(g_Camera + 0x4E)
/* 27F74 80037774 1E6E22A4 */  sh         $v0, %lo(g_Camera + 0x4E)($at)
/* 27F78 80037778 2C00628C */  lw         $v0, 0x2C($v1)
/* 27F7C 8003777C 0E008434 */  ori        $a0, $a0, (0x8000000E & 0xFFFF)
/* 27F80 80037780 0780013C */  lui        $at, %hi(g_Camera + 0x58)
/* 27F84 80037784 286E24AC */  sw         $a0, %lo(g_Camera + 0x58)($at)
/* 27F88 80037788 0780013C */  lui        $at, %hi(g_Camera + 0xC0)
/* 27F8C 8003778C 906E24AC */  sw         $a0, %lo(g_Camera + 0xC0)($at)
/* 27F90 80037790 0780013C */  lui        $at, %hi(g_Camera + 0x50)
/* 27F94 80037794 206E22A4 */  sh         $v0, %lo(g_Camera + 0x50)($at)
/* 27F98 80037798 1000BF8F */  lw         $ra, 0x10($sp)
/* 27F9C 8003779C 1800BD27 */  addiu      $sp, $sp, 0x18
/* 27FA0 800377A0 0800E003 */  jr         $ra
/* 27FA4 800377A4 00000000 */   nop
.size func_80037714, . - func_80037714
