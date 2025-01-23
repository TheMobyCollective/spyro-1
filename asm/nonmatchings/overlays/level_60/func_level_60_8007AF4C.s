.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_60_8007AF4C
/* 51E3514 8007AF4C E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 51E3518 8007AF50 1000BFAF */  sw         $ra, 0x10($sp)
/* 51E351C 8007AF54 0BB4000C */  jal        func_8002D02C
/* 51E3520 8007AF58 00000000 */   nop
/* 51E3524 8007AF5C 0780033C */  lui        $v1, %hi(D_80075898)
/* 51E3528 8007AF60 9858638C */  lw         $v1, %lo(D_80075898)($v1)
/* 51E352C 8007AF64 0880013C */  lui        $at, %hi(g_Spyro + 0x1B4)
/* 51E3530 8007AF68 0C8C20AC */  sw         $zero, %lo(g_Spyro + 0x1B4)($at)
/* 51E3534 8007AF6C 0880013C */  lui        $at, %hi(g_Spyro + 0x11)
/* 51E3538 8007AF70 698A20A0 */  sb         $zero, %lo(g_Spyro + 0x11)($at)
/* 51E353C 8007AF74 02006010 */  beqz       $v1, .Llevel_60_8007AF80
/* 51E3540 8007AF78 10000224 */   addiu     $v0, $zero, 0x10
/* 51E3544 8007AF7C 500062A0 */  sb         $v0, 0x50($v1)
.Llevel_60_8007AF80:
/* 51E3548 8007AF80 1000BF8F */  lw         $ra, 0x10($sp)
/* 51E354C 8007AF84 1800BD27 */  addiu      $sp, $sp, 0x18
/* 51E3550 8007AF88 0800E003 */  jr         $ra
/* 51E3554 8007AF8C 00000000 */   nop
.size func_level_60_8007AF4C, . - func_level_60_8007AF4C
