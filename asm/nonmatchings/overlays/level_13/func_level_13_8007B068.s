.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_13_8007B068
/* 118EE30 8007B068 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 118EE34 8007B06C 1000BFAF */  sw         $ra, 0x10($sp)
/* 118EE38 8007B070 0BB4000C */  jal        func_8002D02C
/* 118EE3C 8007B074 00000000 */   nop
/* 118EE40 8007B078 0780033C */  lui        $v1, %hi(g_Sparx)
/* 118EE44 8007B07C 9858638C */  lw         $v1, %lo(g_Sparx)($v1)
/* 118EE48 8007B080 0880013C */  lui        $at, %hi(g_Spyro + 0x1B4)
/* 118EE4C 8007B084 0C8C20AC */  sw         $zero, %lo(g_Spyro + 0x1B4)($at)
/* 118EE50 8007B088 0880013C */  lui        $at, %hi(g_Spyro + 0x11)
/* 118EE54 8007B08C 698A20A0 */  sb         $zero, %lo(g_Spyro + 0x11)($at)
/* 118EE58 8007B090 02006010 */  beqz       $v1, .Llevel_13_8007B09C
/* 118EE5C 8007B094 10000224 */   addiu     $v0, $zero, 0x10
/* 118EE60 8007B098 500062A0 */  sb         $v0, 0x50($v1)
.Llevel_13_8007B09C:
/* 118EE64 8007B09C 1000BF8F */  lw         $ra, 0x10($sp)
/* 118EE68 8007B0A0 1800BD27 */  addiu      $sp, $sp, 0x18
/* 118EE6C 8007B0A4 0800E003 */  jr         $ra
/* 118EE70 8007B0A8 00000000 */   nop
.size func_level_13_8007B068, . - func_level_13_8007B068
