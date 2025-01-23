.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_22_8007B854
/* 1E02E1C 8007B854 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1E02E20 8007B858 1000BFAF */  sw         $ra, 0x10($sp)
/* 1E02E24 8007B85C 0BB4000C */  jal        func_8002D02C
/* 1E02E28 8007B860 00000000 */   nop
/* 1E02E2C 8007B864 0780033C */  lui        $v1, %hi(D_80075898)
/* 1E02E30 8007B868 9858638C */  lw         $v1, %lo(D_80075898)($v1)
/* 1E02E34 8007B86C 0880013C */  lui        $at, %hi(g_Spyro + 0x1B4)
/* 1E02E38 8007B870 0C8C20AC */  sw         $zero, %lo(g_Spyro + 0x1B4)($at)
/* 1E02E3C 8007B874 0880013C */  lui        $at, %hi(g_Spyro + 0x11)
/* 1E02E40 8007B878 698A20A0 */  sb         $zero, %lo(g_Spyro + 0x11)($at)
/* 1E02E44 8007B87C 02006010 */  beqz       $v1, .Llevel_22_8007B888
/* 1E02E48 8007B880 10000224 */   addiu     $v0, $zero, 0x10
/* 1E02E4C 8007B884 500062A0 */  sb         $v0, 0x50($v1)
.Llevel_22_8007B888:
/* 1E02E50 8007B888 1000BF8F */  lw         $ra, 0x10($sp)
/* 1E02E54 8007B88C 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1E02E58 8007B890 0800E003 */  jr         $ra
/* 1E02E5C 8007B894 00000000 */   nop
.size func_level_22_8007B854, . - func_level_22_8007B854
