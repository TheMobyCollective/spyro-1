.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_22_8007B718
/* 1E02CE0 8007B718 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 1E02CE4 8007B71C 2000B0AF */  sw         $s0, 0x20($sp)
/* 1E02CE8 8007B720 21808000 */  addu       $s0, $a0, $zero
/* 1E02CEC 8007B724 01000624 */  addiu      $a2, $zero, 0x1
/* 1E02CF0 8007B728 2800BFAF */  sw         $ra, 0x28($sp)
/* 1E02CF4 8007B72C 2400B1AF */  sw         $s1, 0x24($sp)
/* 1E02CF8 8007B730 0000038E */  lw         $v1, 0x0($s0)
/* 1E02CFC 8007B734 0C000224 */  addiu      $v0, $zero, 0xC
/* 1E02D00 8007B738 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1E02D04 8007B73C D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1E02D08 8007B740 01000224 */  addiu      $v0, $zero, 0x1
/* 1E02D0C 8007B744 0780013C */  lui        $at, %hi(D_800777E8)
/* 1E02D10 8007B748 E87720AC */  sw         $zero, %lo(D_800777E8)($at)
/* 1E02D14 8007B74C 0780013C */  lui        $at, %hi(D_800777EC)
/* 1E02D18 8007B750 EC7720AC */  sw         $zero, %lo(D_800777EC)($at)
/* 1E02D1C 8007B754 0780013C */  lui        $at, %hi(D_800777F0)
/* 1E02D20 8007B758 F07720AC */  sw         $zero, %lo(D_800777F0)($at)
/* 1E02D24 8007B75C 0780013C */  lui        $at, %hi(D_8007784C)
/* 1E02D28 8007B760 4C7830AC */  sw         $s0, %lo(D_8007784C)($at)
/* 1E02D2C 8007B764 0000638C */  lw         $v1, 0x0($v1)
/* 1E02D30 8007B768 0780113C */  lui        $s1, %hi(g_Camera + 0x28)
/* 1E02D34 8007B76C F86D3126 */  addiu      $s1, $s1, %lo(g_Camera + 0x28)
/* 1E02D38 8007B770 0780013C */  lui        $at, %hi(D_8007570C)
/* 1E02D3C 8007B774 0C5722AC */  sw         $v0, %lo(D_8007570C)($at)
/* 1E02D40 8007B778 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 1E02D44 8007B77C 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 1E02D48 8007B780 40100300 */  sll        $v0, $v1, 1
/* 1E02D4C 8007B784 21104300 */  addu       $v0, $v0, $v1
/* 1E02D50 8007B788 80100200 */  sll        $v0, $v0, 2
/* 1E02D54 8007B78C 23104300 */  subu       $v0, $v0, $v1
/* 1E02D58 8007B790 0780033C */  lui        $v1, %hi(D_80075828)
/* 1E02D5C 8007B794 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 1E02D60 8007B798 C0100200 */  sll        $v0, $v0, 3
/* 1E02D64 8007B79C 21186200 */  addu       $v1, $v1, $v0
/* 1E02D68 8007B7A0 0780013C */  lui        $at, %hi(D_80077850)
/* 1E02D6C 8007B7A4 507823AC */  sw         $v1, %lo(D_80077850)($at)
/* 1E02D70 8007B7A8 0000238E */  lw         $v1, 0x0($s1)
/* 1E02D74 8007B7AC 0C00048E */  lw         $a0, 0xC($s0)
/* 1E02D78 8007B7B0 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* 1E02D7C 8007B7B4 FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* 1E02D80 8007B7B8 1000058E */  lw         $a1, 0x10($s0)
/* 1E02D84 8007B7BC 23206400 */  subu       $a0, $v1, $a0
/* 1E02D88 8007B7C0 AD5A000C */  jal        func_80016AB4
/* 1E02D8C 8007B7C4 23284500 */   subu      $a1, $v0, $a1
/* 1E02D90 8007B7C8 1000A427 */  addiu      $a0, $sp, 0x10
/* 1E02D94 8007B7CC 21282002 */  addu       $a1, $s1, $zero
/* 1E02D98 8007B7D0 0780013C */  lui        $at, %hi(D_80077820)
/* 1E02D9C 8007B7D4 207822AC */  sw         $v0, %lo(D_80077820)($at)
/* 1E02DA0 8007B7D8 E35D000C */  jal        VecSub
/* 1E02DA4 8007B7DC 0C000626 */   addiu     $a2, $s0, 0xC
/* 1E02DA8 8007B7E0 1000A427 */  addiu      $a0, $sp, 0x10
/* 1E02DAC 8007B7E4 7F5C000C */  jal        func_800171FC
/* 1E02DB0 8007B7E8 21280000 */   addu      $a1, $zero, $zero
/* 1E02DB4 8007B7EC 0780033C */  lui        $v1, %hi(g_Camera + 0x30)
/* 1E02DB8 8007B7F0 006E638C */  lw         $v1, %lo(g_Camera + 0x30)($v1)
/* 1E02DBC 8007B7F4 0780013C */  lui        $at, %hi(D_80077824)
/* 1E02DC0 8007B7F8 247822AC */  sw         $v0, %lo(D_80077824)($at)
/* 1E02DC4 8007B7FC 0780013C */  lui        $at, %hi(D_80077828)
/* 1E02DC8 8007B800 287823AC */  sw         $v1, %lo(D_80077828)($at)
/* 1E02DCC 8007B804 46000292 */  lbu        $v0, 0x46($s0)
/* 1E02DD0 8007B808 2E050324 */  addiu      $v1, $zero, 0x52E
/* 1E02DD4 8007B80C 0780013C */  lui        $at, %hi(D_8007783C)
/* 1E02DD8 8007B810 3C7823AC */  sw         $v1, %lo(D_8007783C)($at)
/* 1E02DDC 8007B814 00110200 */  sll        $v0, $v0, 4
/* 1E02DE0 8007B818 EEFC4224 */  addiu      $v0, $v0, -0x312
/* 1E02DE4 8007B81C FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 1E02DE8 8007B820 0780013C */  lui        $at, %hi(D_80077838)
/* 1E02DEC 8007B824 387822AC */  sw         $v0, %lo(D_80077838)($at)
/* 1E02DF0 8007B828 1400028E */  lw         $v0, 0x14($s0)
/* 1E02DF4 8007B82C 00000000 */  nop
/* 1E02DF8 8007B830 8F054224 */  addiu      $v0, $v0, 0x58F
/* 1E02DFC 8007B834 0780013C */  lui        $at, %hi(D_80077840)
/* 1E02E00 8007B838 407822AC */  sw         $v0, %lo(D_80077840)($at)
/* 1E02E04 8007B83C 2800BF8F */  lw         $ra, 0x28($sp)
/* 1E02E08 8007B840 2400B18F */  lw         $s1, 0x24($sp)
/* 1E02E0C 8007B844 2000B08F */  lw         $s0, 0x20($sp)
/* 1E02E10 8007B848 3000BD27 */  addiu      $sp, $sp, 0x30
/* 1E02E14 8007B84C 0800E003 */  jr         $ra
/* 1E02E18 8007B850 00000000 */   nop
.size func_level_22_8007B718, . - func_level_22_8007B718
