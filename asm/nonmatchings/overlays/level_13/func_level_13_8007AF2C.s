.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_13_8007AF2C
/* 118ECF4 8007AF2C D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 118ECF8 8007AF30 2000B0AF */  sw         $s0, 0x20($sp)
/* 118ECFC 8007AF34 21808000 */  addu       $s0, $a0, $zero
/* 118ED00 8007AF38 01000624 */  addiu      $a2, $zero, 0x1
/* 118ED04 8007AF3C 2800BFAF */  sw         $ra, 0x28($sp)
/* 118ED08 8007AF40 2400B1AF */  sw         $s1, 0x24($sp)
/* 118ED0C 8007AF44 0000038E */  lw         $v1, 0x0($s0)
/* 118ED10 8007AF48 0C000224 */  addiu      $v0, $zero, 0xC
/* 118ED14 8007AF4C 0780013C */  lui        $at, %hi(g_Gamestate)
/* 118ED18 8007AF50 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 118ED1C 8007AF54 01000224 */  addiu      $v0, $zero, 0x1
/* 118ED20 8007AF58 0780013C */  lui        $at, %hi(D_800777E8)
/* 118ED24 8007AF5C E87720AC */  sw         $zero, %lo(D_800777E8)($at)
/* 118ED28 8007AF60 0780013C */  lui        $at, %hi(D_800777EC)
/* 118ED2C 8007AF64 EC7720AC */  sw         $zero, %lo(D_800777EC)($at)
/* 118ED30 8007AF68 0780013C */  lui        $at, %hi(D_800777F0)
/* 118ED34 8007AF6C F07720AC */  sw         $zero, %lo(D_800777F0)($at)
/* 118ED38 8007AF70 0780013C */  lui        $at, %hi(D_8007784C)
/* 118ED3C 8007AF74 4C7830AC */  sw         $s0, %lo(D_8007784C)($at)
/* 118ED40 8007AF78 0000638C */  lw         $v1, 0x0($v1)
/* 118ED44 8007AF7C 0780113C */  lui        $s1, %hi(g_Camera + 0x28)
/* 118ED48 8007AF80 F86D3126 */  addiu      $s1, $s1, %lo(g_Camera + 0x28)
/* 118ED4C 8007AF84 0780013C */  lui        $at, %hi(D_8007570C)
/* 118ED50 8007AF88 0C5722AC */  sw         $v0, %lo(D_8007570C)($at)
/* 118ED54 8007AF8C 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 118ED58 8007AF90 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 118ED5C 8007AF94 40100300 */  sll        $v0, $v1, 1
/* 118ED60 8007AF98 21104300 */  addu       $v0, $v0, $v1
/* 118ED64 8007AF9C 80100200 */  sll        $v0, $v0, 2
/* 118ED68 8007AFA0 23104300 */  subu       $v0, $v0, $v1
/* 118ED6C 8007AFA4 0780033C */  lui        $v1, %hi(D_80075828)
/* 118ED70 8007AFA8 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 118ED74 8007AFAC C0100200 */  sll        $v0, $v0, 3
/* 118ED78 8007AFB0 21186200 */  addu       $v1, $v1, $v0
/* 118ED7C 8007AFB4 0780013C */  lui        $at, %hi(D_80077850)
/* 118ED80 8007AFB8 507823AC */  sw         $v1, %lo(D_80077850)($at)
/* 118ED84 8007AFBC 0000238E */  lw         $v1, 0x0($s1)
/* 118ED88 8007AFC0 0C00048E */  lw         $a0, 0xC($s0)
/* 118ED8C 8007AFC4 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* 118ED90 8007AFC8 FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* 118ED94 8007AFCC 1000058E */  lw         $a1, 0x10($s0)
/* 118ED98 8007AFD0 23206400 */  subu       $a0, $v1, $a0
/* 118ED9C 8007AFD4 AD5A000C */  jal        func_80016AB4
/* 118EDA0 8007AFD8 23284500 */   subu      $a1, $v0, $a1
/* 118EDA4 8007AFDC 1000A427 */  addiu      $a0, $sp, 0x10
/* 118EDA8 8007AFE0 21282002 */  addu       $a1, $s1, $zero
/* 118EDAC 8007AFE4 0780013C */  lui        $at, %hi(D_80077820)
/* 118EDB0 8007AFE8 207822AC */  sw         $v0, %lo(D_80077820)($at)
/* 118EDB4 8007AFEC E35D000C */  jal        VecSub
/* 118EDB8 8007AFF0 0C000626 */   addiu     $a2, $s0, 0xC
/* 118EDBC 8007AFF4 1000A427 */  addiu      $a0, $sp, 0x10
/* 118EDC0 8007AFF8 7F5C000C */  jal        VecMagnitude
/* 118EDC4 8007AFFC 21280000 */   addu      $a1, $zero, $zero
/* 118EDC8 8007B000 0780033C */  lui        $v1, %hi(g_Camera + 0x30)
/* 118EDCC 8007B004 006E638C */  lw         $v1, %lo(g_Camera + 0x30)($v1)
/* 118EDD0 8007B008 0780013C */  lui        $at, %hi(D_80077824)
/* 118EDD4 8007B00C 247822AC */  sw         $v0, %lo(D_80077824)($at)
/* 118EDD8 8007B010 0780013C */  lui        $at, %hi(D_80077828)
/* 118EDDC 8007B014 287823AC */  sw         $v1, %lo(D_80077828)($at)
/* 118EDE0 8007B018 46000292 */  lbu        $v0, 0x46($s0)
/* 118EDE4 8007B01C 2E050324 */  addiu      $v1, $zero, 0x52E
/* 118EDE8 8007B020 0780013C */  lui        $at, %hi(D_8007783C)
/* 118EDEC 8007B024 3C7823AC */  sw         $v1, %lo(D_8007783C)($at)
/* 118EDF0 8007B028 00110200 */  sll        $v0, $v0, 4
/* 118EDF4 8007B02C EEFC4224 */  addiu      $v0, $v0, -0x312
/* 118EDF8 8007B030 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 118EDFC 8007B034 0780013C */  lui        $at, %hi(D_80077838)
/* 118EE00 8007B038 387822AC */  sw         $v0, %lo(D_80077838)($at)
/* 118EE04 8007B03C 1400028E */  lw         $v0, 0x14($s0)
/* 118EE08 8007B040 00000000 */  nop
/* 118EE0C 8007B044 8F054224 */  addiu      $v0, $v0, 0x58F
/* 118EE10 8007B048 0780013C */  lui        $at, %hi(D_80077840)
/* 118EE14 8007B04C 407822AC */  sw         $v0, %lo(D_80077840)($at)
/* 118EE18 8007B050 2800BF8F */  lw         $ra, 0x28($sp)
/* 118EE1C 8007B054 2400B18F */  lw         $s1, 0x24($sp)
/* 118EE20 8007B058 2000B08F */  lw         $s0, 0x20($sp)
/* 118EE24 8007B05C 3000BD27 */  addiu      $sp, $sp, 0x30
/* 118EE28 8007B060 0800E003 */  jr         $ra
/* 118EE2C 8007B064 00000000 */   nop
.size func_level_13_8007AF2C, . - func_level_13_8007AF2C
