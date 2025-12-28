.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_60_8007AE10
/* 51E33D8 8007AE10 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 51E33DC 8007AE14 2000B0AF */  sw         $s0, 0x20($sp)
/* 51E33E0 8007AE18 21808000 */  addu       $s0, $a0, $zero
/* 51E33E4 8007AE1C 01000624 */  addiu      $a2, $zero, 0x1
/* 51E33E8 8007AE20 2800BFAF */  sw         $ra, 0x28($sp)
/* 51E33EC 8007AE24 2400B1AF */  sw         $s1, 0x24($sp)
/* 51E33F0 8007AE28 0000038E */  lw         $v1, 0x0($s0)
/* 51E33F4 8007AE2C 0C000224 */  addiu      $v0, $zero, 0xC
/* 51E33F8 8007AE30 0780013C */  lui        $at, %hi(g_Gamestate)
/* 51E33FC 8007AE34 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 51E3400 8007AE38 01000224 */  addiu      $v0, $zero, 0x1
/* 51E3404 8007AE3C 0780013C */  lui        $at, %hi(D_800777E8)
/* 51E3408 8007AE40 E87720AC */  sw         $zero, %lo(D_800777E8)($at)
/* 51E340C 8007AE44 0780013C */  lui        $at, %hi(D_800777E8 + 0x4)
/* 51E3410 8007AE48 EC7720AC */  sw         $zero, %lo(D_800777E8 + 0x4)($at)
/* 51E3414 8007AE4C 0780013C */  lui        $at, %hi(D_800777E8 + 0x8)
/* 51E3418 8007AE50 F07720AC */  sw         $zero, %lo(D_800777E8 + 0x8)($at)
/* 51E341C 8007AE54 0780013C */  lui        $at, %hi(D_800777E8 + 0x64)
/* 51E3420 8007AE58 4C7830AC */  sw         $s0, %lo(D_800777E8 + 0x64)($at)
/* 51E3424 8007AE5C 0000638C */  lw         $v1, 0x0($v1)
/* 51E3428 8007AE60 0780113C */  lui        $s1, %hi(g_Camera + 0x28)
/* 51E342C 8007AE64 F86D3126 */  addiu      $s1, $s1, %lo(g_Camera + 0x28)
/* 51E3430 8007AE68 0780013C */  lui        $at, %hi(g_ScreenBorderEnabled)
/* 51E3434 8007AE6C 0C5722AC */  sw         $v0, %lo(g_ScreenBorderEnabled)($at)
/* 51E3438 8007AE70 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 51E343C 8007AE74 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 51E3440 8007AE78 40100300 */  sll        $v0, $v1, 1
/* 51E3444 8007AE7C 21104300 */  addu       $v0, $v0, $v1
/* 51E3448 8007AE80 80100200 */  sll        $v0, $v0, 2
/* 51E344C 8007AE84 23104300 */  subu       $v0, $v0, $v1
/* 51E3450 8007AE88 0780033C */  lui        $v1, %hi(g_LevelMobys)
/* 51E3454 8007AE8C 2858638C */  lw         $v1, %lo(g_LevelMobys)($v1)
/* 51E3458 8007AE90 C0100200 */  sll        $v0, $v0, 3
/* 51E345C 8007AE94 21186200 */  addu       $v1, $v1, $v0
/* 51E3460 8007AE98 0780013C */  lui        $at, %hi(D_800777E8 + 0x68)
/* 51E3464 8007AE9C 507823AC */  sw         $v1, %lo(D_800777E8 + 0x68)($at)
/* 51E3468 8007AEA0 0000238E */  lw         $v1, 0x0($s1)
/* 51E346C 8007AEA4 0C00048E */  lw         $a0, 0xC($s0)
/* 51E3470 8007AEA8 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* 51E3474 8007AEAC FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* 51E3478 8007AEB0 1000058E */  lw         $a1, 0x10($s0)
/* 51E347C 8007AEB4 23206400 */  subu       $a0, $v1, $a0
/* 51E3480 8007AEB8 AD5A000C */  jal        Atan2
/* 51E3484 8007AEBC 23284500 */   subu      $a1, $v0, $a1
/* 51E3488 8007AEC0 1000A427 */  addiu      $a0, $sp, 0x10
/* 51E348C 8007AEC4 21282002 */  addu       $a1, $s1, $zero
/* 51E3490 8007AEC8 0780013C */  lui        $at, %hi(D_800777E8 + 0x38)
/* 51E3494 8007AECC 207822AC */  sw         $v0, %lo(D_800777E8 + 0x38)($at)
/* 51E3498 8007AED0 E35D000C */  jal        VecSub
/* 51E349C 8007AED4 0C000626 */   addiu     $a2, $s0, 0xC
/* 51E34A0 8007AED8 1000A427 */  addiu      $a0, $sp, 0x10
/* 51E34A4 8007AEDC 7F5C000C */  jal        VecMagnitude
/* 51E34A8 8007AEE0 21280000 */   addu      $a1, $zero, $zero
/* 51E34AC 8007AEE4 0780033C */  lui        $v1, %hi(g_Camera + 0x30)
/* 51E34B0 8007AEE8 006E638C */  lw         $v1, %lo(g_Camera + 0x30)($v1)
/* 51E34B4 8007AEEC 0780013C */  lui        $at, %hi(D_800777E8 + 0x3C)
/* 51E34B8 8007AEF0 247822AC */  sw         $v0, %lo(D_800777E8 + 0x3C)($at)
/* 51E34BC 8007AEF4 0780013C */  lui        $at, %hi(D_800777E8 + 0x40)
/* 51E34C0 8007AEF8 287823AC */  sw         $v1, %lo(D_800777E8 + 0x40)($at)
/* 51E34C4 8007AEFC 46000292 */  lbu        $v0, 0x46($s0)
/* 51E34C8 8007AF00 2E050324 */  addiu      $v1, $zero, 0x52E
/* 51E34CC 8007AF04 0780013C */  lui        $at, %hi(D_800777E8 + 0x54)
/* 51E34D0 8007AF08 3C7823AC */  sw         $v1, %lo(D_800777E8 + 0x54)($at)
/* 51E34D4 8007AF0C 00110200 */  sll        $v0, $v0, 4
/* 51E34D8 8007AF10 EEFC4224 */  addiu      $v0, $v0, -0x312
/* 51E34DC 8007AF14 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 51E34E0 8007AF18 0780013C */  lui        $at, %hi(D_800777E8 + 0x50)
/* 51E34E4 8007AF1C 387822AC */  sw         $v0, %lo(D_800777E8 + 0x50)($at)
/* 51E34E8 8007AF20 1400028E */  lw         $v0, 0x14($s0)
/* 51E34EC 8007AF24 00000000 */  nop
/* 51E34F0 8007AF28 8F054224 */  addiu      $v0, $v0, 0x58F
/* 51E34F4 8007AF2C 0780013C */  lui        $at, %hi(D_800777E8 + 0x58)
/* 51E34F8 8007AF30 407822AC */  sw         $v0, %lo(D_800777E8 + 0x58)($at)
/* 51E34FC 8007AF34 2800BF8F */  lw         $ra, 0x28($sp)
/* 51E3500 8007AF38 2400B18F */  lw         $s1, 0x24($sp)
/* 51E3504 8007AF3C 2000B08F */  lw         $s0, 0x20($sp)
/* 51E3508 8007AF40 3000BD27 */  addiu      $sp, $sp, 0x30
/* 51E350C 8007AF44 0800E003 */  jr         $ra
/* 51E3510 8007AF48 00000000 */   nop
.size func_level_60_8007AE10, . - func_level_60_8007AE10
