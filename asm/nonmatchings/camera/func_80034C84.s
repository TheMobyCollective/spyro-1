.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80034C84
/* 25484 80034C84 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 25488 80034C88 1000B0AF */  sw         $s0, 0x10($sp)
/* 2548C 80034C8C 0780103C */  lui        $s0, %hi(g_Camera + 0x28)
/* 25490 80034C90 F86D1026 */  addiu      $s0, $s0, %lo(g_Camera + 0x28)
/* 25494 80034C94 21200002 */  addu       $a0, $s0, $zero
/* 25498 80034C98 1400BFAF */  sw         $ra, 0x14($sp)
/* 2549C 80034C9C C05D000C */  jal        VecCopy
/* 254A0 80034CA0 0C000526 */   addiu     $a1, $s0, 0xC
/* 254A4 80034CA4 01000224 */  addiu      $v0, $zero, 0x1
/* 254A8 80034CA8 0780013C */  lui        $at, %hi(g_Camera + 0xC4)
/* 254AC 80034CAC 946E20AC */  sw         $zero, %lo(g_Camera + 0xC4)($at)
/* 254B0 80034CB0 0780013C */  lui        $at, %hi(g_Camera + 0xC8)
/* 254B4 80034CB4 986E20AC */  sw         $zero, %lo(g_Camera + 0xC8)($at)
/* 254B8 80034CB8 0780013C */  lui        $at, %hi(g_Camera + 0xCC)
/* 254BC 80034CBC 9C6E22AC */  sw         $v0, %lo(g_Camera + 0xCC)($at)
/* 254C0 80034CC0 540482AF */  sw         $v0, %gp_rel(D_800756B8)($gp)
/* 254C4 80034CC4 C2CF000C */  jal        func_80033F08
/* 254C8 80034CC8 21200002 */   addu      $a0, $s0, $zero
/* 254CC 80034CCC 0780013C */  lui        $at, %hi(g_Camera + 0xE8)
/* 254D0 80034CD0 B86E22AC */  sw         $v0, %lo(g_Camera + 0xE8)($at)
/* 254D4 80034CD4 1400BF8F */  lw         $ra, 0x14($sp)
/* 254D8 80034CD8 1000B08F */  lw         $s0, 0x10($sp)
/* 254DC 80034CDC 1800BD27 */  addiu      $sp, $sp, 0x18
/* 254E0 80034CE0 0800E003 */  jr         $ra
/* 254E4 80034CE4 00000000 */   nop
.size func_80034C84, . - func_80034C84
