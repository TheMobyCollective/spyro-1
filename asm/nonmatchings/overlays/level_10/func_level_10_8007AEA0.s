.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_10_8007AEA0
/* 7F2C68 8007AEA0 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 7F2C6C 8007AEA4 2000B0AF */  sw         $s0, 0x20($sp)
/* 7F2C70 8007AEA8 21808000 */  addu       $s0, $a0, $zero
/* 7F2C74 8007AEAC 01000624 */  addiu      $a2, $zero, 0x1
/* 7F2C78 8007AEB0 2800BFAF */  sw         $ra, 0x28($sp)
/* 7F2C7C 8007AEB4 2400B1AF */  sw         $s1, 0x24($sp)
/* 7F2C80 8007AEB8 0000038E */  lw         $v1, 0x0($s0)
/* 7F2C84 8007AEBC 0C000224 */  addiu      $v0, $zero, 0xC
/* 7F2C88 8007AEC0 0780013C */  lui        $at, %hi(g_Gamestate)
/* 7F2C8C 8007AEC4 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 7F2C90 8007AEC8 01000224 */  addiu      $v0, $zero, 0x1
/* 7F2C94 8007AECC 0780013C */  lui        $at, %hi(D_800777E8)
/* 7F2C98 8007AED0 E87720AC */  sw         $zero, %lo(D_800777E8)($at)
/* 7F2C9C 8007AED4 0780013C */  lui        $at, %hi(D_800777EC)
/* 7F2CA0 8007AED8 EC7720AC */  sw         $zero, %lo(D_800777EC)($at)
/* 7F2CA4 8007AEDC 0780013C */  lui        $at, %hi(D_800777F0)
/* 7F2CA8 8007AEE0 F07720AC */  sw         $zero, %lo(D_800777F0)($at)
/* 7F2CAC 8007AEE4 0780013C */  lui        $at, %hi(D_8007784C)
/* 7F2CB0 8007AEE8 4C7830AC */  sw         $s0, %lo(D_8007784C)($at)
/* 7F2CB4 8007AEEC 0000638C */  lw         $v1, 0x0($v1)
/* 7F2CB8 8007AEF0 0780113C */  lui        $s1, %hi(g_Camera + 0x28)
/* 7F2CBC 8007AEF4 F86D3126 */  addiu      $s1, $s1, %lo(g_Camera + 0x28)
/* 7F2CC0 8007AEF8 0780013C */  lui        $at, %hi(D_8007570C)
/* 7F2CC4 8007AEFC 0C5722AC */  sw         $v0, %lo(D_8007570C)($at)
/* 7F2CC8 8007AF00 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 7F2CCC 8007AF04 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 7F2CD0 8007AF08 40100300 */  sll        $v0, $v1, 1
/* 7F2CD4 8007AF0C 21104300 */  addu       $v0, $v0, $v1
/* 7F2CD8 8007AF10 80100200 */  sll        $v0, $v0, 2
/* 7F2CDC 8007AF14 23104300 */  subu       $v0, $v0, $v1
/* 7F2CE0 8007AF18 0780033C */  lui        $v1, %hi(D_80075828)
/* 7F2CE4 8007AF1C 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 7F2CE8 8007AF20 C0100200 */  sll        $v0, $v0, 3
/* 7F2CEC 8007AF24 21186200 */  addu       $v1, $v1, $v0
/* 7F2CF0 8007AF28 0780013C */  lui        $at, %hi(D_80077850)
/* 7F2CF4 8007AF2C 507823AC */  sw         $v1, %lo(D_80077850)($at)
/* 7F2CF8 8007AF30 0000238E */  lw         $v1, 0x0($s1)
/* 7F2CFC 8007AF34 0C00048E */  lw         $a0, 0xC($s0)
/* 7F2D00 8007AF38 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* 7F2D04 8007AF3C FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* 7F2D08 8007AF40 1000058E */  lw         $a1, 0x10($s0)
/* 7F2D0C 8007AF44 23206400 */  subu       $a0, $v1, $a0
/* 7F2D10 8007AF48 AD5A000C */  jal        func_80016AB4
/* 7F2D14 8007AF4C 23284500 */   subu      $a1, $v0, $a1
/* 7F2D18 8007AF50 1000A427 */  addiu      $a0, $sp, 0x10
/* 7F2D1C 8007AF54 21282002 */  addu       $a1, $s1, $zero
/* 7F2D20 8007AF58 0780013C */  lui        $at, %hi(D_80077820)
/* 7F2D24 8007AF5C 207822AC */  sw         $v0, %lo(D_80077820)($at)
/* 7F2D28 8007AF60 E35D000C */  jal        VecSub
/* 7F2D2C 8007AF64 0C000626 */   addiu     $a2, $s0, 0xC
/* 7F2D30 8007AF68 1000A427 */  addiu      $a0, $sp, 0x10
/* 7F2D34 8007AF6C 7F5C000C */  jal        VecMagnitude
/* 7F2D38 8007AF70 21280000 */   addu      $a1, $zero, $zero
/* 7F2D3C 8007AF74 0780033C */  lui        $v1, %hi(g_Camera + 0x30)
/* 7F2D40 8007AF78 006E638C */  lw         $v1, %lo(g_Camera + 0x30)($v1)
/* 7F2D44 8007AF7C 0780013C */  lui        $at, %hi(D_80077824)
/* 7F2D48 8007AF80 247822AC */  sw         $v0, %lo(D_80077824)($at)
/* 7F2D4C 8007AF84 0780013C */  lui        $at, %hi(D_80077828)
/* 7F2D50 8007AF88 287823AC */  sw         $v1, %lo(D_80077828)($at)
/* 7F2D54 8007AF8C 46000292 */  lbu        $v0, 0x46($s0)
/* 7F2D58 8007AF90 2E050324 */  addiu      $v1, $zero, 0x52E
/* 7F2D5C 8007AF94 0780013C */  lui        $at, %hi(D_8007783C)
/* 7F2D60 8007AF98 3C7823AC */  sw         $v1, %lo(D_8007783C)($at)
/* 7F2D64 8007AF9C 00110200 */  sll        $v0, $v0, 4
/* 7F2D68 8007AFA0 EEFC4224 */  addiu      $v0, $v0, -0x312
/* 7F2D6C 8007AFA4 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 7F2D70 8007AFA8 0780013C */  lui        $at, %hi(D_80077838)
/* 7F2D74 8007AFAC 387822AC */  sw         $v0, %lo(D_80077838)($at)
/* 7F2D78 8007AFB0 1400028E */  lw         $v0, 0x14($s0)
/* 7F2D7C 8007AFB4 00000000 */  nop
/* 7F2D80 8007AFB8 8F054224 */  addiu      $v0, $v0, 0x58F
/* 7F2D84 8007AFBC 0780013C */  lui        $at, %hi(D_80077840)
/* 7F2D88 8007AFC0 407822AC */  sw         $v0, %lo(D_80077840)($at)
/* 7F2D8C 8007AFC4 2800BF8F */  lw         $ra, 0x28($sp)
/* 7F2D90 8007AFC8 2400B18F */  lw         $s1, 0x24($sp)
/* 7F2D94 8007AFCC 2000B08F */  lw         $s0, 0x20($sp)
/* 7F2D98 8007AFD0 3000BD27 */  addiu      $sp, $sp, 0x30
/* 7F2D9C 8007AFD4 0800E003 */  jr         $ra
/* 7F2DA0 8007AFD8 00000000 */   nop
.size func_level_10_8007AEA0, . - func_level_10_8007AEA0
