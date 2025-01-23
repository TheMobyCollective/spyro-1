.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003DF60
/* 2E760 8003DF60 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 2E764 8003DF64 1000B0AF */  sw         $s0, 0x10($sp)
/* 2E768 8003DF68 0880103C */  lui        $s0, %hi(g_Spyro)
/* 2E76C 8003DF6C 588A1026 */  addiu      $s0, $s0, %lo(g_Spyro)
/* 2E770 8003DF70 21200002 */  addu       $a0, $s0, $zero
/* 2E774 8003DF74 1400BFAF */  sw         $ra, 0x14($sp)
/* 2E778 8003DF78 C05D000C */  jal        VecCopy
/* 2E77C 8003DF7C 8C000526 */   addiu     $a1, $s0, 0x8C
/* 2E780 8003DF80 BC5D000C */  jal        VecNull
/* 2E784 8003DF84 0C010426 */   addiu     $a0, $s0, 0x10C
/* 2E788 8003DF88 0880013C */  lui        $at, %hi(g_Spyro + 0x128)
/* 2E78C 8003DF8C 808B20AC */  sw         $zero, %lo(g_Spyro + 0x128)($at)
/* 2E790 8003DF90 1400BF8F */  lw         $ra, 0x14($sp)
/* 2E794 8003DF94 1000B08F */  lw         $s0, 0x10($sp)
/* 2E798 8003DF98 1800BD27 */  addiu      $sp, $sp, 0x18
/* 2E79C 8003DF9C 0800E003 */  jr         $ra
/* 2E7A0 8003DFA0 00000000 */   nop
.size func_8003DF60, . - func_8003DF60
