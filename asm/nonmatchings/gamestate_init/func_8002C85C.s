.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002C85C
/* 1D05C 8002C85C 0780023C */  lui        $v0, %hi(D_8007582C)
/* 1D060 8002C860 2C58428C */  lw         $v0, %lo(D_8007582C)($v0)
/* 1D064 8002C864 00000000 */  nop
/* 1D068 8002C868 05004010 */  beqz       $v0, .L8002C880
/* 1D06C 8002C86C FFFF4224 */   addiu     $v0, $v0, -0x1
/* 1D070 8002C870 0780013C */  lui        $at, %hi(D_8007582C)
/* 1D074 8002C874 2C5822AC */  sw         $v0, %lo(D_8007582C)($at)
/* 1D078 8002C878 21B20008 */  j          .L8002C884
/* 1D07C 8002C87C 04000224 */   addiu     $v0, $zero, 0x4
.L8002C880:
/* 1D080 8002C880 05000224 */  addiu      $v0, $zero, 0x5
.L8002C884:
/* 1D084 8002C884 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1D088 8002C888 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1D08C 8002C88C 0780013C */  lui        $at, %hi(D_80075940)
/* 1D090 8002C890 405920AC */  sw         $zero, %lo(D_80075940)($at)
/* 1D094 8002C894 0780013C */  lui        $at, %hi(D_8007593C)
/* 1D098 8002C898 3C5920AC */  sw         $zero, %lo(D_8007593C)($at)
/* 1D09C 8002C89C 0800E003 */  jr         $ra
/* 1D0A0 8002C8A0 00000000 */   nop
.size func_8002C85C, . - func_8002C85C
