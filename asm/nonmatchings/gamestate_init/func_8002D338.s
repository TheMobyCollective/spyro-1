.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002D338
/* 1DB38 8002D338 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 1DB3C 8002D33C 0E000224 */  addiu      $v0, $zero, 0xE
/* 1DB40 8002D340 0780033C */  lui        $v1, %hi(D_80075680)
/* 1DB44 8002D344 8056638C */  lw         $v1, %lo(D_80075680)($v1)
/* 1DB48 8002D348 0780043C */  lui        $a0, %hi(D_8007566C)
/* 1DB4C 8002D34C 6C56848C */  lw         $a0, %lo(D_8007566C)($a0)
/* 1DB50 8002D350 01000524 */  addiu      $a1, $zero, 0x1
/* 1DB54 8002D354 1000BFAF */  sw         $ra, 0x10($sp)
/* 1DB58 8002D358 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1DB5C 8002D35C D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1DB60 8002D360 0780013C */  lui        $at, %hi(g_Fade)
/* 1DB64 8002D364 185920AC */  sw         $zero, %lo(g_Fade)($at)
/* 1DB68 8002D368 03008514 */  bne        $a0, $a1, .L8002D378
/* 1DB6C 8002D36C 000060AC */   sw        $zero, 0x0($v1)
/* 1DB70 8002D370 0780013C */  lui        $at, %hi(D_8007591C)
/* 1DB74 8002D374 1C5925AC */  sw         $a1, %lo(D_8007591C)($at)
.L8002D378:
/* 1DB78 8002D378 0780023C */  lui        $v0, %hi(D_800778F0)
/* 1DB7C 8002D37C F0784224 */  addiu      $v0, $v0, %lo(D_800778F0)
/* 1DB80 8002D380 0780013C */  lui        $at, %hi(g_Spu + 0x2C8)
/* 1DB84 8002D384 D06122AC */  sw         $v0, %lo(g_Spu + 0x2C8)($at)
/* 1DB88 8002D388 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 1DB8C 8002D38C D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 1DB90 8002D390 10100224 */  addiu      $v0, $zero, 0x1010
/* 1DB94 8002D394 000062AC */  sw         $v0, 0x0($v1)
/* 1DB98 8002D398 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 1DB9C 8002D39C D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 1DBA0 8002D3A0 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 1DBA4 8002D3A4 040062AC */  sw         $v0, 0x4($v1)
/* 1DBA8 8002D3A8 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 1DBAC 8002D3AC D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 1DBB0 8002D3B0 50000224 */  addiu      $v0, $zero, 0x50
/* 1DBB4 8002D3B4 080062A4 */  sh         $v0, 0x8($v1)
/* 1DBB8 8002D3B8 80100400 */  sll        $v0, $a0, 2
/* 1DBBC 8002D3BC 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 1DBC0 8002D3C0 D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 1DBC4 8002D3C4 0780013C */  lui        $at, %hi(D_8006EE6C)
/* 1DBC8 8002D3C8 21082200 */  addu       $at, $at, $v0
/* 1DBCC 8002D3CC 6CEE228C */  lw         $v0, %lo(D_8006EE6C)($at)
/* 1DBD0 8002D3D0 00000000 */  nop
/* 1DBD4 8002D3D4 0A0062A4 */  sh         $v0, 0xA($v1)
/* 1DBD8 8002D3D8 0780023C */  lui        $v0, %hi(g_Spu + 0x2C8)
/* 1DBDC 8002D3DC D061428C */  lw         $v0, %lo(g_Spu + 0x2C8)($v0)
/* 1DBE0 8002D3E0 10000624 */  addiu      $a2, $zero, 0x10
/* 1DBE4 8002D3E4 0C0040A4 */  sh         $zero, 0xC($v0)
/* 1DBE8 8002D3E8 0780023C */  lui        $v0, %hi(g_Spu + 0x2C8)
/* 1DBEC 8002D3EC D061428C */  lw         $v0, %lo(g_Spu + 0x2C8)($v0)
/* 1DBF0 8002D3F0 0780073C */  lui        $a3, %hi(D_80077030 + 0x54)
/* 1DBF4 8002D3F4 8470E724 */  addiu      $a3, $a3, %lo(D_80077030 + 0x54)
/* 1DBF8 8002D3F8 0E0040A4 */  sh         $zero, 0xE($v0)
/* 1DBFC 8002D3FC 0780023C */  lui        $v0, %hi(g_Spu + 0x2C8)
/* 1DC00 8002D400 D061428C */  lw         $v0, %lo(g_Spu + 0x2C8)($v0)
/* 1DC04 8002D404 21200000 */  addu       $a0, $zero, $zero
/* 1DC08 8002D408 100040AC */  sw         $zero, 0x10($v0)
/* 1DC0C 8002D40C FF3F0224 */  addiu      $v0, $zero, 0x3FFF
/* 1DC10 8002D410 0780013C */  lui        $at, %hi(g_Spu + 0x2D4)
/* 1DC14 8002D414 DC6125AC */  sw         $a1, %lo(g_Spu + 0x2D4)($at)
/* 1DC18 8002D418 0780013C */  lui        $at, %hi(g_Spu + 0x2E0)
/* 1DC1C 8002D41C E86122A4 */  sh         $v0, %lo(g_Spu + 0x2E0)($at)
/* 1DC20 8002D420 0780013C */  lui        $at, %hi(g_Spu + 0x2E2)
/* 1DC24 8002D424 EA6122A4 */  sh         $v0, %lo(g_Spu + 0x2E2)($at)
/* 1DC28 8002D428 9E56010C */  jal        PlaySound
/* 1DC2C 8002D42C 21280000 */   addu      $a1, $zero, $zero
/* 1DC30 8002D430 1000BF8F */  lw         $ra, 0x10($sp)
/* 1DC34 8002D434 1800BD27 */  addiu      $sp, $sp, 0x18
/* 1DC38 8002D438 0800E003 */  jr         $ra
/* 1DC3C 8002D43C 00000000 */   nop
.size func_8002D338, . - func_8002D338
