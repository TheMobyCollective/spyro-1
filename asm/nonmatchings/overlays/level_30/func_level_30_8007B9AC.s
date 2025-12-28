.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_30_8007B9AC
/* 2727F74 8007B9AC E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 2727F78 8007B9B0 1000BFAF */  sw         $ra, 0x10($sp)
/* 2727F7C 8007B9B4 0BB4000C */  jal        func_8002D02C
/* 2727F80 8007B9B8 00000000 */   nop
/* 2727F84 8007B9BC 0780033C */  lui        $v1, %hi(g_Sparx)
/* 2727F88 8007B9C0 9858638C */  lw         $v1, %lo(g_Sparx)($v1)
/* 2727F8C 8007B9C4 0880013C */  lui        $at, %hi(g_Spyro + 0x1B4)
/* 2727F90 8007B9C8 0C8C20AC */  sw         $zero, %lo(g_Spyro + 0x1B4)($at)
/* 2727F94 8007B9CC 0880013C */  lui        $at, %hi(g_Spyro + 0x11)
/* 2727F98 8007B9D0 698A20A0 */  sb         $zero, %lo(g_Spyro + 0x11)($at)
/* 2727F9C 8007B9D4 02006010 */  beqz       $v1, .Llevel_30_8007B9E0
/* 2727FA0 8007B9D8 10000224 */   addiu     $v0, $zero, 0x10
/* 2727FA4 8007B9DC 500062A0 */  sb         $v0, 0x50($v1)
.Llevel_30_8007B9E0:
/* 2727FA8 8007B9E0 1000BF8F */  lw         $ra, 0x10($sp)
/* 2727FAC 8007B9E4 1800BD27 */  addiu      $sp, $sp, 0x18
/* 2727FB0 8007B9E8 0800E003 */  jr         $ra
/* 2727FB4 8007B9EC 00000000 */   nop
.size func_level_30_8007B9AC, . - func_level_30_8007B9AC
