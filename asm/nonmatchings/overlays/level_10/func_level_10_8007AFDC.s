.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_10_8007AFDC
/* 7F2DA4 8007AFDC E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 7F2DA8 8007AFE0 1000BFAF */  sw         $ra, 0x10($sp)
/* 7F2DAC 8007AFE4 0BB4000C */  jal        func_8002D02C
/* 7F2DB0 8007AFE8 00000000 */   nop
/* 7F2DB4 8007AFEC 0780033C */  lui        $v1, %hi(D_80075898)
/* 7F2DB8 8007AFF0 9858638C */  lw         $v1, %lo(D_80075898)($v1)
/* 7F2DBC 8007AFF4 0880013C */  lui        $at, %hi(g_Spyro + 0x1B4)
/* 7F2DC0 8007AFF8 0C8C20AC */  sw         $zero, %lo(g_Spyro + 0x1B4)($at)
/* 7F2DC4 8007AFFC 0880013C */  lui        $at, %hi(g_Spyro + 0x11)
/* 7F2DC8 8007B000 698A20A0 */  sb         $zero, %lo(g_Spyro + 0x11)($at)
/* 7F2DCC 8007B004 02006010 */  beqz       $v1, .Llevel_10_8007B010
/* 7F2DD0 8007B008 10000224 */   addiu     $v0, $zero, 0x10
/* 7F2DD4 8007B00C 500062A0 */  sb         $v0, 0x50($v1)
.Llevel_10_8007B010:
/* 7F2DD8 8007B010 1000BF8F */  lw         $ra, 0x10($sp)
/* 7F2DDC 8007B014 1800BD27 */  addiu      $sp, $sp, 0x18
/* 7F2DE0 8007B018 0800E003 */  jr         $ra
/* 7F2DE4 8007B01C 00000000 */   nop
.size func_level_10_8007AFDC, . - func_level_10_8007AFDC
