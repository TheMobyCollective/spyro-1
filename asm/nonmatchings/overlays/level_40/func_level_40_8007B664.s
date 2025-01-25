.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_40_8007B664
/* 358CC2C 8007B664 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 358CC30 8007B668 2000B0AF */  sw         $s0, 0x20($sp)
/* 358CC34 8007B66C 21808000 */  addu       $s0, $a0, $zero
/* 358CC38 8007B670 01000624 */  addiu      $a2, $zero, 0x1
/* 358CC3C 8007B674 2800BFAF */  sw         $ra, 0x28($sp)
/* 358CC40 8007B678 2400B1AF */  sw         $s1, 0x24($sp)
/* 358CC44 8007B67C 0000038E */  lw         $v1, 0x0($s0)
/* 358CC48 8007B680 0C000224 */  addiu      $v0, $zero, 0xC
/* 358CC4C 8007B684 0780013C */  lui        $at, %hi(g_Gamestate)
/* 358CC50 8007B688 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 358CC54 8007B68C 01000224 */  addiu      $v0, $zero, 0x1
/* 358CC58 8007B690 0780013C */  lui        $at, %hi(D_800777E8)
/* 358CC5C 8007B694 E87720AC */  sw         $zero, %lo(D_800777E8)($at)
/* 358CC60 8007B698 0780013C */  lui        $at, %hi(D_800777EC)
/* 358CC64 8007B69C EC7720AC */  sw         $zero, %lo(D_800777EC)($at)
/* 358CC68 8007B6A0 0780013C */  lui        $at, %hi(D_800777F0)
/* 358CC6C 8007B6A4 F07720AC */  sw         $zero, %lo(D_800777F0)($at)
/* 358CC70 8007B6A8 0780013C */  lui        $at, %hi(D_8007784C)
/* 358CC74 8007B6AC 4C7830AC */  sw         $s0, %lo(D_8007784C)($at)
/* 358CC78 8007B6B0 0000638C */  lw         $v1, 0x0($v1)
/* 358CC7C 8007B6B4 0780113C */  lui        $s1, %hi(g_Camera + 0x28)
/* 358CC80 8007B6B8 F86D3126 */  addiu      $s1, $s1, %lo(g_Camera + 0x28)
/* 358CC84 8007B6BC 0780013C */  lui        $at, %hi(D_8007570C)
/* 358CC88 8007B6C0 0C5722AC */  sw         $v0, %lo(D_8007570C)($at)
/* 358CC8C 8007B6C4 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 358CC90 8007B6C8 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 358CC94 8007B6CC 40100300 */  sll        $v0, $v1, 1
/* 358CC98 8007B6D0 21104300 */  addu       $v0, $v0, $v1
/* 358CC9C 8007B6D4 80100200 */  sll        $v0, $v0, 2
/* 358CCA0 8007B6D8 23104300 */  subu       $v0, $v0, $v1
/* 358CCA4 8007B6DC 0780033C */  lui        $v1, %hi(D_80075828)
/* 358CCA8 8007B6E0 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 358CCAC 8007B6E4 C0100200 */  sll        $v0, $v0, 3
/* 358CCB0 8007B6E8 21186200 */  addu       $v1, $v1, $v0
/* 358CCB4 8007B6EC 0780013C */  lui        $at, %hi(D_80077850)
/* 358CCB8 8007B6F0 507823AC */  sw         $v1, %lo(D_80077850)($at)
/* 358CCBC 8007B6F4 0000238E */  lw         $v1, 0x0($s1)
/* 358CCC0 8007B6F8 0C00048E */  lw         $a0, 0xC($s0)
/* 358CCC4 8007B6FC 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* 358CCC8 8007B700 FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* 358CCCC 8007B704 1000058E */  lw         $a1, 0x10($s0)
/* 358CCD0 8007B708 23206400 */  subu       $a0, $v1, $a0
/* 358CCD4 8007B70C AD5A000C */  jal        func_80016AB4
/* 358CCD8 8007B710 23284500 */   subu      $a1, $v0, $a1
/* 358CCDC 8007B714 1000A427 */  addiu      $a0, $sp, 0x10
/* 358CCE0 8007B718 21282002 */  addu       $a1, $s1, $zero
/* 358CCE4 8007B71C 0780013C */  lui        $at, %hi(D_80077820)
/* 358CCE8 8007B720 207822AC */  sw         $v0, %lo(D_80077820)($at)
/* 358CCEC 8007B724 E35D000C */  jal        VecSub
/* 358CCF0 8007B728 0C000626 */   addiu     $a2, $s0, 0xC
/* 358CCF4 8007B72C 1000A427 */  addiu      $a0, $sp, 0x10
/* 358CCF8 8007B730 7F5C000C */  jal        VecMagnitude
/* 358CCFC 8007B734 21280000 */   addu      $a1, $zero, $zero
/* 358CD00 8007B738 0780033C */  lui        $v1, %hi(g_Camera + 0x30)
/* 358CD04 8007B73C 006E638C */  lw         $v1, %lo(g_Camera + 0x30)($v1)
/* 358CD08 8007B740 0780013C */  lui        $at, %hi(D_80077824)
/* 358CD0C 8007B744 247822AC */  sw         $v0, %lo(D_80077824)($at)
/* 358CD10 8007B748 0780013C */  lui        $at, %hi(D_80077828)
/* 358CD14 8007B74C 287823AC */  sw         $v1, %lo(D_80077828)($at)
/* 358CD18 8007B750 46000292 */  lbu        $v0, 0x46($s0)
/* 358CD1C 8007B754 2E050324 */  addiu      $v1, $zero, 0x52E
/* 358CD20 8007B758 0780013C */  lui        $at, %hi(D_8007783C)
/* 358CD24 8007B75C 3C7823AC */  sw         $v1, %lo(D_8007783C)($at)
/* 358CD28 8007B760 00110200 */  sll        $v0, $v0, 4
/* 358CD2C 8007B764 EEFC4224 */  addiu      $v0, $v0, -0x312
/* 358CD30 8007B768 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 358CD34 8007B76C 0780013C */  lui        $at, %hi(D_80077838)
/* 358CD38 8007B770 387822AC */  sw         $v0, %lo(D_80077838)($at)
/* 358CD3C 8007B774 1400028E */  lw         $v0, 0x14($s0)
/* 358CD40 8007B778 00000000 */  nop
/* 358CD44 8007B77C 8F054224 */  addiu      $v0, $v0, 0x58F
/* 358CD48 8007B780 0780013C */  lui        $at, %hi(D_80077840)
/* 358CD4C 8007B784 407822AC */  sw         $v0, %lo(D_80077840)($at)
/* 358CD50 8007B788 2800BF8F */  lw         $ra, 0x28($sp)
/* 358CD54 8007B78C 2400B18F */  lw         $s1, 0x24($sp)
/* 358CD58 8007B790 2000B08F */  lw         $s0, 0x20($sp)
/* 358CD5C 8007B794 3000BD27 */  addiu      $sp, $sp, 0x30
/* 358CD60 8007B798 0800E003 */  jr         $ra
/* 358CD64 8007B79C 00000000 */   nop
.size func_level_40_8007B664, . - func_level_40_8007B664
