.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_50_8007B9D4
/* 43DBF9C 8007B9D4 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 43DBFA0 8007B9D8 1000BFAF */  sw         $ra, 0x10($sp)
/* 43DBFA4 8007B9DC 0BB4000C */  jal        func_8002D02C
/* 43DBFA8 8007B9E0 00000000 */   nop
/* 43DBFAC 8007B9E4 0780033C */  lui        $v1, %hi(g_Sparx)
/* 43DBFB0 8007B9E8 9858638C */  lw         $v1, %lo(g_Sparx)($v1)
/* 43DBFB4 8007B9EC 0880013C */  lui        $at, %hi(g_Spyro + 0x1B4)
/* 43DBFB8 8007B9F0 0C8C20AC */  sw         $zero, %lo(g_Spyro + 0x1B4)($at)
/* 43DBFBC 8007B9F4 0880013C */  lui        $at, %hi(g_Spyro + 0x11)
/* 43DBFC0 8007B9F8 698A20A0 */  sb         $zero, %lo(g_Spyro + 0x11)($at)
/* 43DBFC4 8007B9FC 02006010 */  beqz       $v1, .Llevel_50_8007BA08
/* 43DBFC8 8007BA00 10000224 */   addiu     $v0, $zero, 0x10
/* 43DBFCC 8007BA04 500062A0 */  sb         $v0, 0x50($v1)
.Llevel_50_8007BA08:
/* 43DBFD0 8007BA08 1000BF8F */  lw         $ra, 0x10($sp)
/* 43DBFD4 8007BA0C 1800BD27 */  addiu      $sp, $sp, 0x18
/* 43DBFD8 8007BA10 0800E003 */  jr         $ra
/* 43DBFDC 8007BA14 00000000 */   nop
.size func_level_50_8007B9D4, . - func_level_50_8007B9D4
