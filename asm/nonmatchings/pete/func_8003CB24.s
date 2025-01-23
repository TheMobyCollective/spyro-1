.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003CB24
/* 2D324 8003CB24 0880053C */  lui        $a1, %hi(g_Spyro + 0x24)
/* 2D328 8003CB28 7C8AA524 */  addiu      $a1, $a1, %lo(g_Spyro + 0x24)
/* 2D32C 8003CB2C 0000A290 */  lbu        $v0, 0x0($a1)
/* 2D330 8003CB30 00000000 */  nop
/* 2D334 8003CB34 21184400 */  addu       $v1, $v0, $a0
/* 2D338 8003CB38 FF006230 */  andi       $v0, $v1, 0xFF
/* 2D33C 8003CB3C 1000422C */  sltiu      $v0, $v0, 0x10
/* 2D340 8003CB40 1B004014 */  bnez       $v0, .L8003CBB0
/* 2D344 8003CB44 0000A3A0 */   sb        $v1, 0x0($a1)
/* 2D348 8003CB48 F0FF6224 */  addiu      $v0, $v1, -0x10
/* 2D34C 8003CB4C 0000A2A0 */  sb         $v0, 0x0($a1)
/* 2D350 8003CB50 0880033C */  lui        $v1, %hi(g_Spyro + 0x1F)
/* 2D354 8003CB54 778A6390 */  lbu        $v1, %lo(g_Spyro + 0x1F)($v1)
/* 2D358 8003CB58 0880043C */  lui        $a0, %hi(g_Spyro + 0x19)
/* 2D35C 8003CB5C 718A8490 */  lbu        $a0, %lo(g_Spyro + 0x19)($a0)
/* 2D360 8003CB60 01006224 */  addiu      $v0, $v1, 0x1
/* 2D364 8003CB64 0880013C */  lui        $at, %hi(g_Spyro + 0x18)
/* 2D368 8003CB68 708A24A0 */  sb         $a0, %lo(g_Spyro + 0x18)($at)
/* 2D36C 8003CB6C 80200400 */  sll        $a0, $a0, 2
/* 2D370 8003CB70 0880013C */  lui        $at, %hi(g_Spyro + 0x1E)
/* 2D374 8003CB74 768A23A0 */  sb         $v1, %lo(g_Spyro + 0x1E)($at)
/* 2D378 8003CB78 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 2D37C 8003CB7C 778A22A0 */  sb         $v0, %lo(g_Spyro + 0x1F)($at)
/* 2D380 8003CB80 0780013C */  lui        $at, %hi(D_8006C4A1)
/* 2D384 8003CB84 21082400 */  addu       $at, $at, $a0
/* 2D388 8003CB88 A1C42390 */  lbu        $v1, %lo(D_8006C4A1)($at)
/* 2D38C 8003CB8C FF004230 */  andi       $v0, $v0, 0xFF
/* 2D390 8003CB90 2B104300 */  sltu       $v0, $v0, $v1
/* 2D394 8003CB94 06004014 */  bnez       $v0, .L8003CBB0
/* 2D398 8003CB98 00000000 */   nop
/* 2D39C 8003CB9C 0780013C */  lui        $at, %hi(spyro_AnimationDetails)
/* 2D3A0 8003CBA0 21082400 */  addu       $at, $at, $a0
/* 2D3A4 8003CBA4 A0C42290 */  lbu        $v0, %lo(spyro_AnimationDetails)($at)
/* 2D3A8 8003CBA8 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 2D3AC 8003CBAC 778A22A0 */  sb         $v0, %lo(g_Spyro + 0x1F)($at)
.L8003CBB0:
/* 2D3B0 8003CBB0 0800E003 */  jr         $ra
/* 2D3B4 8003CBB4 00000000 */   nop
.size func_8003CB24, . - func_8003CB24
