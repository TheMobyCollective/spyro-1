.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_21_8007B718
/* 1B2FCE0 8007B718 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 1B2FCE4 8007B71C 2000B0AF */  sw         $s0, 0x20($sp)
/* 1B2FCE8 8007B720 21808000 */  addu       $s0, $a0, $zero
/* 1B2FCEC 8007B724 01000624 */  addiu      $a2, $zero, 0x1
/* 1B2FCF0 8007B728 2800BFAF */  sw         $ra, 0x28($sp)
/* 1B2FCF4 8007B72C 2400B1AF */  sw         $s1, 0x24($sp)
/* 1B2FCF8 8007B730 0000038E */  lw         $v1, 0x0($s0)
/* 1B2FCFC 8007B734 0C000224 */  addiu      $v0, $zero, 0xC
/* 1B2FD00 8007B738 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1B2FD04 8007B73C D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1B2FD08 8007B740 01000224 */  addiu      $v0, $zero, 0x1
/* 1B2FD0C 8007B744 0780013C */  lui        $at, %hi(D_800777E8)
/* 1B2FD10 8007B748 E87720AC */  sw         $zero, %lo(D_800777E8)($at)
/* 1B2FD14 8007B74C 0780013C */  lui        $at, %hi(D_800777E8 + 0x4)
/* 1B2FD18 8007B750 EC7720AC */  sw         $zero, %lo(D_800777E8 + 0x4)($at)
/* 1B2FD1C 8007B754 0780013C */  lui        $at, %hi(D_800777E8 + 0x8)
/* 1B2FD20 8007B758 F07720AC */  sw         $zero, %lo(D_800777E8 + 0x8)($at)
/* 1B2FD24 8007B75C 0780013C */  lui        $at, %hi(D_800777E8 + 0x64)
/* 1B2FD28 8007B760 4C7830AC */  sw         $s0, %lo(D_800777E8 + 0x64)($at)
/* 1B2FD2C 8007B764 0000638C */  lw         $v1, 0x0($v1)
/* 1B2FD30 8007B768 0780113C */  lui        $s1, %hi(g_Camera + 0x28)
/* 1B2FD34 8007B76C F86D3126 */  addiu      $s1, $s1, %lo(g_Camera + 0x28)
/* 1B2FD38 8007B770 0780013C */  lui        $at, %hi(D_8007570C)
/* 1B2FD3C 8007B774 0C5722AC */  sw         $v0, %lo(D_8007570C)($at)
/* 1B2FD40 8007B778 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 1B2FD44 8007B77C 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 1B2FD48 8007B780 40100300 */  sll        $v0, $v1, 1
/* 1B2FD4C 8007B784 21104300 */  addu       $v0, $v0, $v1
/* 1B2FD50 8007B788 80100200 */  sll        $v0, $v0, 2
/* 1B2FD54 8007B78C 23104300 */  subu       $v0, $v0, $v1
/* 1B2FD58 8007B790 0780033C */  lui        $v1, %hi(D_80075828)
/* 1B2FD5C 8007B794 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 1B2FD60 8007B798 C0100200 */  sll        $v0, $v0, 3
/* 1B2FD64 8007B79C 21186200 */  addu       $v1, $v1, $v0
/* 1B2FD68 8007B7A0 0780013C */  lui        $at, %hi(D_800777E8 + 0x68)
/* 1B2FD6C 8007B7A4 507823AC */  sw         $v1, %lo(D_800777E8 + 0x68)($at)
/* 1B2FD70 8007B7A8 0000238E */  lw         $v1, 0x0($s1)
/* 1B2FD74 8007B7AC 0C00048E */  lw         $a0, 0xC($s0)
/* 1B2FD78 8007B7B0 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* 1B2FD7C 8007B7B4 FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* 1B2FD80 8007B7B8 1000058E */  lw         $a1, 0x10($s0)
/* 1B2FD84 8007B7BC 23206400 */  subu       $a0, $v1, $a0
/* 1B2FD88 8007B7C0 AD5A000C */  jal        Atan2
/* 1B2FD8C 8007B7C4 23284500 */   subu      $a1, $v0, $a1
/* 1B2FD90 8007B7C8 1000A427 */  addiu      $a0, $sp, 0x10
/* 1B2FD94 8007B7CC 21282002 */  addu       $a1, $s1, $zero
/* 1B2FD98 8007B7D0 0780013C */  lui        $at, %hi(D_800777E8 + 0x38)
/* 1B2FD9C 8007B7D4 207822AC */  sw         $v0, %lo(D_800777E8 + 0x38)($at)
/* 1B2FDA0 8007B7D8 E35D000C */  jal        VecSub
/* 1B2FDA4 8007B7DC 0C000626 */   addiu     $a2, $s0, 0xC
/* 1B2FDA8 8007B7E0 1000A427 */  addiu      $a0, $sp, 0x10
/* 1B2FDAC 8007B7E4 7F5C000C */  jal        VecMagnitude
/* 1B2FDB0 8007B7E8 21280000 */   addu      $a1, $zero, $zero
/* 1B2FDB4 8007B7EC 0780033C */  lui        $v1, %hi(g_Camera + 0x30)
/* 1B2FDB8 8007B7F0 006E638C */  lw         $v1, %lo(g_Camera + 0x30)($v1)
/* 1B2FDBC 8007B7F4 0780013C */  lui        $at, %hi(D_800777E8 + 0x3C)
/* 1B2FDC0 8007B7F8 247822AC */  sw         $v0, %lo(D_800777E8 + 0x3C)($at)
/* 1B2FDC4 8007B7FC 0780013C */  lui        $at, %hi(D_800777E8 + 0x40)
/* 1B2FDC8 8007B800 287823AC */  sw         $v1, %lo(D_800777E8 + 0x40)($at)
/* 1B2FDCC 8007B804 46000292 */  lbu        $v0, 0x46($s0)
/* 1B2FDD0 8007B808 2E050324 */  addiu      $v1, $zero, 0x52E
/* 1B2FDD4 8007B80C 0780013C */  lui        $at, %hi(D_800777E8 + 0x54)
/* 1B2FDD8 8007B810 3C7823AC */  sw         $v1, %lo(D_800777E8 + 0x54)($at)
/* 1B2FDDC 8007B814 00110200 */  sll        $v0, $v0, 4
/* 1B2FDE0 8007B818 EEFC4224 */  addiu      $v0, $v0, -0x312
/* 1B2FDE4 8007B81C FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 1B2FDE8 8007B820 0780013C */  lui        $at, %hi(D_800777E8 + 0x50)
/* 1B2FDEC 8007B824 387822AC */  sw         $v0, %lo(D_800777E8 + 0x50)($at)
/* 1B2FDF0 8007B828 1400028E */  lw         $v0, 0x14($s0)
/* 1B2FDF4 8007B82C 00000000 */  nop
/* 1B2FDF8 8007B830 8F054224 */  addiu      $v0, $v0, 0x58F
/* 1B2FDFC 8007B834 0780013C */  lui        $at, %hi(D_800777E8 + 0x58)
/* 1B2FE00 8007B838 407822AC */  sw         $v0, %lo(D_800777E8 + 0x58)($at)
/* 1B2FE04 8007B83C 2800BF8F */  lw         $ra, 0x28($sp)
/* 1B2FE08 8007B840 2400B18F */  lw         $s1, 0x24($sp)
/* 1B2FE0C 8007B844 2000B08F */  lw         $s0, 0x20($sp)
/* 1B2FE10 8007B848 3000BD27 */  addiu      $sp, $sp, 0x30
/* 1B2FE14 8007B84C 0800E003 */  jr         $ra
/* 1B2FE18 8007B850 00000000 */   nop
.size func_level_21_8007B718, . - func_level_21_8007B718
