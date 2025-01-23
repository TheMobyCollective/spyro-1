.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003DFA4
/* 2E7A4 8003DFA4 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 2E7A8 8003DFA8 1000B0AF */  sw         $s0, 0x10($sp)
/* 2E7AC 8003DFAC 0880103C */  lui        $s0, %hi(g_Spyro + 0x10C)
/* 2E7B0 8003DFB0 648B1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x10C)
/* 2E7B4 8003DFB4 1400BFAF */  sw         $ra, 0x14($sp)
/* 2E7B8 8003DFB8 BC5D000C */  jal        VecNull
/* 2E7BC 8003DFBC 21200002 */   addu      $a0, $s0, $zero
/* 2E7C0 8003DFC0 0880013C */  lui        $at, %hi(g_Spyro + 0x128)
/* 2E7C4 8003DFC4 808B20AC */  sw         $zero, %lo(g_Spyro + 0x128)($at)
/* 2E7C8 8003DFC8 BC5D000C */  jal        VecNull
/* 2E7CC 8003DFCC E8FF0426 */   addiu     $a0, $s0, -0x18
/* 2E7D0 8003DFD0 0880013C */  lui        $at, %hi(g_Spyro + 0x118)
/* 2E7D4 8003DFD4 708B20AC */  sw         $zero, %lo(g_Spyro + 0x118)($at)
/* 2E7D8 8003DFD8 1400BF8F */  lw         $ra, 0x14($sp)
/* 2E7DC 8003DFDC 1000B08F */  lw         $s0, 0x10($sp)
/* 2E7E0 8003DFE0 1800BD27 */  addiu      $sp, $sp, 0x18
/* 2E7E4 8003DFE4 0800E003 */  jr         $ra
/* 2E7E8 8003DFE8 00000000 */   nop
.size func_8003DFA4, . - func_8003DFA4
