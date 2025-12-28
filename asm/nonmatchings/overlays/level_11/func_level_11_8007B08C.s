.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_11_8007B08C
/* B83E54 8007B08C E8FFBD27 */  addiu      $sp, $sp, -0x18
/* B83E58 8007B090 1000BFAF */  sw         $ra, 0x10($sp)
/* B83E5C 8007B094 0BB4000C */  jal        func_8002D02C
/* B83E60 8007B098 00000000 */   nop
/* B83E64 8007B09C 0780033C */  lui        $v1, %hi(g_Sparx)
/* B83E68 8007B0A0 9858638C */  lw         $v1, %lo(g_Sparx)($v1)
/* B83E6C 8007B0A4 0880013C */  lui        $at, %hi(g_Spyro + 0x1B4)
/* B83E70 8007B0A8 0C8C20AC */  sw         $zero, %lo(g_Spyro + 0x1B4)($at)
/* B83E74 8007B0AC 0880013C */  lui        $at, %hi(g_Spyro + 0x11)
/* B83E78 8007B0B0 698A20A0 */  sb         $zero, %lo(g_Spyro + 0x11)($at)
/* B83E7C 8007B0B4 02006010 */  beqz       $v1, .Llevel_11_8007B0C0
/* B83E80 8007B0B8 10000224 */   addiu     $v0, $zero, 0x10
/* B83E84 8007B0BC 500062A0 */  sb         $v0, 0x50($v1)
.Llevel_11_8007B0C0:
/* B83E88 8007B0C0 1000BF8F */  lw         $ra, 0x10($sp)
/* B83E8C 8007B0C4 1800BD27 */  addiu      $sp, $sp, 0x18
/* B83E90 8007B0C8 0800E003 */  jr         $ra
/* B83E94 8007B0CC 00000000 */   nop
.size func_level_11_8007B08C, . - func_level_11_8007B08C
