.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_20_8007B9B4
/* 187EF7C 8007B9B4 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 187EF80 8007B9B8 1000BFAF */  sw         $ra, 0x10($sp)
/* 187EF84 8007B9BC 0BB4000C */  jal        func_8002D02C
/* 187EF88 8007B9C0 00000000 */   nop
/* 187EF8C 8007B9C4 0780033C */  lui        $v1, %hi(g_Sparx)
/* 187EF90 8007B9C8 9858638C */  lw         $v1, %lo(g_Sparx)($v1)
/* 187EF94 8007B9CC 0880013C */  lui        $at, %hi(g_Spyro + 0x1B4)
/* 187EF98 8007B9D0 0C8C20AC */  sw         $zero, %lo(g_Spyro + 0x1B4)($at)
/* 187EF9C 8007B9D4 0880013C */  lui        $at, %hi(g_Spyro + 0x11)
/* 187EFA0 8007B9D8 698A20A0 */  sb         $zero, %lo(g_Spyro + 0x11)($at)
/* 187EFA4 8007B9DC 02006010 */  beqz       $v1, .Llevel_20_8007B9E8
/* 187EFA8 8007B9E0 10000224 */   addiu     $v0, $zero, 0x10
/* 187EFAC 8007B9E4 500062A0 */  sb         $v0, 0x50($v1)
.Llevel_20_8007B9E8:
/* 187EFB0 8007B9E8 1000BF8F */  lw         $ra, 0x10($sp)
/* 187EFB4 8007B9EC 1800BD27 */  addiu      $sp, $sp, 0x18
/* 187EFB8 8007B9F0 0800E003 */  jr         $ra
/* 187EFBC 8007B9F4 00000000 */   nop
.size func_level_20_8007B9B4, . - func_level_20_8007B9B4
