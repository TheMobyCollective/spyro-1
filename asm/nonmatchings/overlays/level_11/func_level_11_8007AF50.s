.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_11_8007AF50
/* B83D18 8007AF50 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* B83D1C 8007AF54 2000B0AF */  sw         $s0, 0x20($sp)
/* B83D20 8007AF58 21808000 */  addu       $s0, $a0, $zero
/* B83D24 8007AF5C 01000624 */  addiu      $a2, $zero, 0x1
/* B83D28 8007AF60 2800BFAF */  sw         $ra, 0x28($sp)
/* B83D2C 8007AF64 2400B1AF */  sw         $s1, 0x24($sp)
/* B83D30 8007AF68 0000038E */  lw         $v1, 0x0($s0)
/* B83D34 8007AF6C 0C000224 */  addiu      $v0, $zero, 0xC
/* B83D38 8007AF70 0780013C */  lui        $at, %hi(g_Gamestate)
/* B83D3C 8007AF74 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* B83D40 8007AF78 01000224 */  addiu      $v0, $zero, 0x1
/* B83D44 8007AF7C 0780013C */  lui        $at, %hi(D_800777E8)
/* B83D48 8007AF80 E87720AC */  sw         $zero, %lo(D_800777E8)($at)
/* B83D4C 8007AF84 0780013C */  lui        $at, %hi(D_800777E8 + 0x4)
/* B83D50 8007AF88 EC7720AC */  sw         $zero, %lo(D_800777E8 + 0x4)($at)
/* B83D54 8007AF8C 0780013C */  lui        $at, %hi(D_800777E8 + 0x8)
/* B83D58 8007AF90 F07720AC */  sw         $zero, %lo(D_800777E8 + 0x8)($at)
/* B83D5C 8007AF94 0780013C */  lui        $at, %hi(D_800777E8 + 0x64)
/* B83D60 8007AF98 4C7830AC */  sw         $s0, %lo(D_800777E8 + 0x64)($at)
/* B83D64 8007AF9C 0000638C */  lw         $v1, 0x0($v1)
/* B83D68 8007AFA0 0780113C */  lui        $s1, %hi(g_Camera + 0x28)
/* B83D6C 8007AFA4 F86D3126 */  addiu      $s1, $s1, %lo(g_Camera + 0x28)
/* B83D70 8007AFA8 0780013C */  lui        $at, %hi(D_8007570C)
/* B83D74 8007AFAC 0C5722AC */  sw         $v0, %lo(D_8007570C)($at)
/* B83D78 8007AFB0 0780013C */  lui        $at, %hi(g_StateSwitch)
/* B83D7C 8007AFB4 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* B83D80 8007AFB8 40100300 */  sll        $v0, $v1, 1
/* B83D84 8007AFBC 21104300 */  addu       $v0, $v0, $v1
/* B83D88 8007AFC0 80100200 */  sll        $v0, $v0, 2
/* B83D8C 8007AFC4 23104300 */  subu       $v0, $v0, $v1
/* B83D90 8007AFC8 0780033C */  lui        $v1, %hi(D_80075828)
/* B83D94 8007AFCC 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* B83D98 8007AFD0 C0100200 */  sll        $v0, $v0, 3
/* B83D9C 8007AFD4 21186200 */  addu       $v1, $v1, $v0
/* B83DA0 8007AFD8 0780013C */  lui        $at, %hi(D_800777E8 + 0x68)
/* B83DA4 8007AFDC 507823AC */  sw         $v1, %lo(D_800777E8 + 0x68)($at)
/* B83DA8 8007AFE0 0000238E */  lw         $v1, 0x0($s1)
/* B83DAC 8007AFE4 0C00048E */  lw         $a0, 0xC($s0)
/* B83DB0 8007AFE8 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* B83DB4 8007AFEC FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* B83DB8 8007AFF0 1000058E */  lw         $a1, 0x10($s0)
/* B83DBC 8007AFF4 23206400 */  subu       $a0, $v1, $a0
/* B83DC0 8007AFF8 AD5A000C */  jal        Atan2
/* B83DC4 8007AFFC 23284500 */   subu      $a1, $v0, $a1
/* B83DC8 8007B000 1000A427 */  addiu      $a0, $sp, 0x10
/* B83DCC 8007B004 21282002 */  addu       $a1, $s1, $zero
/* B83DD0 8007B008 0780013C */  lui        $at, %hi(D_800777E8 + 0x38)
/* B83DD4 8007B00C 207822AC */  sw         $v0, %lo(D_800777E8 + 0x38)($at)
/* B83DD8 8007B010 E35D000C */  jal        VecSub
/* B83DDC 8007B014 0C000626 */   addiu     $a2, $s0, 0xC
/* B83DE0 8007B018 1000A427 */  addiu      $a0, $sp, 0x10
/* B83DE4 8007B01C 7F5C000C */  jal        VecMagnitude
/* B83DE8 8007B020 21280000 */   addu      $a1, $zero, $zero
/* B83DEC 8007B024 0780033C */  lui        $v1, %hi(g_Camera + 0x30)
/* B83DF0 8007B028 006E638C */  lw         $v1, %lo(g_Camera + 0x30)($v1)
/* B83DF4 8007B02C 0780013C */  lui        $at, %hi(D_800777E8 + 0x3C)
/* B83DF8 8007B030 247822AC */  sw         $v0, %lo(D_800777E8 + 0x3C)($at)
/* B83DFC 8007B034 0780013C */  lui        $at, %hi(D_800777E8 + 0x40)
/* B83E00 8007B038 287823AC */  sw         $v1, %lo(D_800777E8 + 0x40)($at)
/* B83E04 8007B03C 46000292 */  lbu        $v0, 0x46($s0)
/* B83E08 8007B040 2E050324 */  addiu      $v1, $zero, 0x52E
/* B83E0C 8007B044 0780013C */  lui        $at, %hi(D_800777E8 + 0x54)
/* B83E10 8007B048 3C7823AC */  sw         $v1, %lo(D_800777E8 + 0x54)($at)
/* B83E14 8007B04C 00110200 */  sll        $v0, $v0, 4
/* B83E18 8007B050 EEFC4224 */  addiu      $v0, $v0, -0x312
/* B83E1C 8007B054 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* B83E20 8007B058 0780013C */  lui        $at, %hi(D_800777E8 + 0x50)
/* B83E24 8007B05C 387822AC */  sw         $v0, %lo(D_800777E8 + 0x50)($at)
/* B83E28 8007B060 1400028E */  lw         $v0, 0x14($s0)
/* B83E2C 8007B064 00000000 */  nop
/* B83E30 8007B068 8F054224 */  addiu      $v0, $v0, 0x58F
/* B83E34 8007B06C 0780013C */  lui        $at, %hi(D_800777E8 + 0x58)
/* B83E38 8007B070 407822AC */  sw         $v0, %lo(D_800777E8 + 0x58)($at)
/* B83E3C 8007B074 2800BF8F */  lw         $ra, 0x28($sp)
/* B83E40 8007B078 2400B18F */  lw         $s1, 0x24($sp)
/* B83E44 8007B07C 2000B08F */  lw         $s0, 0x20($sp)
/* B83E48 8007B080 3000BD27 */  addiu      $sp, $sp, 0x30
/* B83E4C 8007B084 0800E003 */  jr         $ra
/* B83E50 8007B088 00000000 */   nop
.size func_level_11_8007AF50, . - func_level_11_8007AF50
