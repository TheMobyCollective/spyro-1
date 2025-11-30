.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_titlescreen_8007AAD4
/* 5B89C 8007AAD4 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 5B8A0 8007AAD8 0780023C */  lui        $v0, %hi(D_800778F0)
/* 5B8A4 8007AADC F0784224 */  addiu      $v0, $v0, %lo(D_800778F0)
/* 5B8A8 8007AAE0 80200400 */  sll        $a0, $a0, 2
/* 5B8AC 8007AAE4 1000BFAF */  sw         $ra, 0x10($sp)
/* 5B8B0 8007AAE8 0780013C */  lui        $at, %hi(g_Spu + 0x2C8)
/* 5B8B4 8007AAEC D06122AC */  sw         $v0, %lo(g_Spu + 0x2C8)($at)
/* 5B8B8 8007AAF0 0780013C */  lui        $at, %hi(D_8006FA74 + 0x20)
/* 5B8BC 8007AAF4 21082400 */  addu       $at, $at, $a0
/* 5B8C0 8007AAF8 94FA228C */  lw         $v0, %lo(D_8006FA74 + 0x20)($at)
/* 5B8C4 8007AAFC 21200000 */  addu       $a0, $zero, $zero
/* 5B8C8 8007AB00 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 5B8CC 8007AB04 D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 5B8D0 8007AB08 10104224 */  addiu      $v0, $v0, 0x1010
/* 5B8D4 8007AB0C 000062AC */  sw         $v0, 0x0($v1)
/* 5B8D8 8007AB10 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 5B8DC 8007AB14 D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 5B8E0 8007AB18 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 5B8E4 8007AB1C 040062AC */  sw         $v0, 0x4($v1)
/* 5B8E8 8007AB20 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 5B8EC 8007AB24 D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 5B8F0 8007AB28 50000224 */  addiu      $v0, $zero, 0x50
/* 5B8F4 8007AB2C 080062A4 */  sh         $v0, 0x8($v1)
/* 5B8F8 8007AB30 0780033C */  lui        $v1, %hi(g_Spu + 0x2C8)
/* 5B8FC 8007AB34 D061638C */  lw         $v1, %lo(g_Spu + 0x2C8)($v1)
/* 5B900 8007AB38 00080224 */  addiu      $v0, $zero, 0x800
/* 5B904 8007AB3C 0A0062A4 */  sh         $v0, 0xA($v1)
/* 5B908 8007AB40 0780023C */  lui        $v0, %hi(g_Spu + 0x2C8)
/* 5B90C 8007AB44 D061428C */  lw         $v0, %lo(g_Spu + 0x2C8)($v0)
/* 5B910 8007AB48 21280000 */  addu       $a1, $zero, $zero
/* 5B914 8007AB4C 0C0040A4 */  sh         $zero, 0xC($v0)
/* 5B918 8007AB50 0780023C */  lui        $v0, %hi(g_Spu + 0x2C8)
/* 5B91C 8007AB54 D061428C */  lw         $v0, %lo(g_Spu + 0x2C8)($v0)
/* 5B920 8007AB58 00000000 */  nop
/* 5B924 8007AB5C 0E0040A4 */  sh         $zero, 0xE($v0)
/* 5B928 8007AB60 0780023C */  lui        $v0, %hi(g_Spu + 0x2C8)
/* 5B92C 8007AB64 D061428C */  lw         $v0, %lo(g_Spu + 0x2C8)($v0)
/* 5B930 8007AB68 0780073C */  lui        $a3, %hi(D_80077030 + 0x54)
/* 5B934 8007AB6C 8470E724 */  addiu      $a3, $a3, %lo(D_80077030 + 0x54)
/* 5B938 8007AB70 100040AC */  sw         $zero, 0x10($v0)
/* 5B93C 8007AB74 01000224 */  addiu      $v0, $zero, 0x1
/* 5B940 8007AB78 0780013C */  lui        $at, %hi(g_Spu + 0x2D4)
/* 5B944 8007AB7C DC6122AC */  sw         $v0, %lo(g_Spu + 0x2D4)($at)
/* 5B948 8007AB80 FF3F0224 */  addiu      $v0, $zero, 0x3FFF
/* 5B94C 8007AB84 0780013C */  lui        $at, %hi(g_Spu + 0x2E0)
/* 5B950 8007AB88 E86122A4 */  sh         $v0, %lo(g_Spu + 0x2E0)($at)
/* 5B954 8007AB8C 0780013C */  lui        $at, %hi(g_Spu + 0x2E2)
/* 5B958 8007AB90 EA6122A4 */  sh         $v0, %lo(g_Spu + 0x2E2)($at)
/* 5B95C 8007AB94 9E56010C */  jal        PlaySound
/* 5B960 8007AB98 10000624 */   addiu     $a2, $zero, 0x10
/* 5B964 8007AB9C 1000BF8F */  lw         $ra, 0x10($sp)
/* 5B968 8007ABA0 1800BD27 */  addiu      $sp, $sp, 0x18
/* 5B96C 8007ABA4 0800E003 */  jr         $ra
/* 5B970 8007ABA8 00000000 */   nop
.size func_titlescreen_8007AAD4, . - func_titlescreen_8007AAD4
