.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_40_8007B7A0
/* 358CD68 8007B7A0 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 358CD6C 8007B7A4 1000BFAF */  sw         $ra, 0x10($sp)
/* 358CD70 8007B7A8 0BB4000C */  jal        func_8002D02C
/* 358CD74 8007B7AC 00000000 */   nop
/* 358CD78 8007B7B0 0780033C */  lui        $v1, %hi(D_80075898)
/* 358CD7C 8007B7B4 9858638C */  lw         $v1, %lo(D_80075898)($v1)
/* 358CD80 8007B7B8 0880013C */  lui        $at, %hi(g_Spyro + 0x1B4)
/* 358CD84 8007B7BC 0C8C20AC */  sw         $zero, %lo(g_Spyro + 0x1B4)($at)
/* 358CD88 8007B7C0 0880013C */  lui        $at, %hi(g_Spyro + 0x11)
/* 358CD8C 8007B7C4 698A20A0 */  sb         $zero, %lo(g_Spyro + 0x11)($at)
/* 358CD90 8007B7C8 02006010 */  beqz       $v1, .Llevel_40_8007B7D4
/* 358CD94 8007B7CC 10000224 */   addiu     $v0, $zero, 0x10
/* 358CD98 8007B7D0 500062A0 */  sb         $v0, 0x50($v1)
.Llevel_40_8007B7D4:
/* 358CD9C 8007B7D4 1000BF8F */  lw         $ra, 0x10($sp)
/* 358CDA0 8007B7D8 1800BD27 */  addiu      $sp, $sp, 0x18
/* 358CDA4 8007B7DC 0800E003 */  jr         $ra
/* 358CDA8 8007B7E0 00000000 */   nop
.size func_level_40_8007B7A0, . - func_level_40_8007B7A0
