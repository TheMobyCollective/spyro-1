.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_30_8007B870
/* 2727E38 8007B870 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 2727E3C 8007B874 2000B0AF */  sw         $s0, 0x20($sp)
/* 2727E40 8007B878 21808000 */  addu       $s0, $a0, $zero
/* 2727E44 8007B87C 01000624 */  addiu      $a2, $zero, 0x1
/* 2727E48 8007B880 2800BFAF */  sw         $ra, 0x28($sp)
/* 2727E4C 8007B884 2400B1AF */  sw         $s1, 0x24($sp)
/* 2727E50 8007B888 0000038E */  lw         $v1, 0x0($s0)
/* 2727E54 8007B88C 0C000224 */  addiu      $v0, $zero, 0xC
/* 2727E58 8007B890 0780013C */  lui        $at, %hi(g_Gamestate)
/* 2727E5C 8007B894 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 2727E60 8007B898 01000224 */  addiu      $v0, $zero, 0x1
/* 2727E64 8007B89C 0780013C */  lui        $at, %hi(D_800777E8)
/* 2727E68 8007B8A0 E87720AC */  sw         $zero, %lo(D_800777E8)($at)
/* 2727E6C 8007B8A4 0780013C */  lui        $at, %hi(D_800777EC)
/* 2727E70 8007B8A8 EC7720AC */  sw         $zero, %lo(D_800777EC)($at)
/* 2727E74 8007B8AC 0780013C */  lui        $at, %hi(D_800777F0)
/* 2727E78 8007B8B0 F07720AC */  sw         $zero, %lo(D_800777F0)($at)
/* 2727E7C 8007B8B4 0780013C */  lui        $at, %hi(D_8007784C)
/* 2727E80 8007B8B8 4C7830AC */  sw         $s0, %lo(D_8007784C)($at)
/* 2727E84 8007B8BC 0000638C */  lw         $v1, 0x0($v1)
/* 2727E88 8007B8C0 0780113C */  lui        $s1, %hi(g_Camera + 0x28)
/* 2727E8C 8007B8C4 F86D3126 */  addiu      $s1, $s1, %lo(g_Camera + 0x28)
/* 2727E90 8007B8C8 0780013C */  lui        $at, %hi(D_8007570C)
/* 2727E94 8007B8CC 0C5722AC */  sw         $v0, %lo(D_8007570C)($at)
/* 2727E98 8007B8D0 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 2727E9C 8007B8D4 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 2727EA0 8007B8D8 40100300 */  sll        $v0, $v1, 1
/* 2727EA4 8007B8DC 21104300 */  addu       $v0, $v0, $v1
/* 2727EA8 8007B8E0 80100200 */  sll        $v0, $v0, 2
/* 2727EAC 8007B8E4 23104300 */  subu       $v0, $v0, $v1
/* 2727EB0 8007B8E8 0780033C */  lui        $v1, %hi(D_80075828)
/* 2727EB4 8007B8EC 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 2727EB8 8007B8F0 C0100200 */  sll        $v0, $v0, 3
/* 2727EBC 8007B8F4 21186200 */  addu       $v1, $v1, $v0
/* 2727EC0 8007B8F8 0780013C */  lui        $at, %hi(D_80077850)
/* 2727EC4 8007B8FC 507823AC */  sw         $v1, %lo(D_80077850)($at)
/* 2727EC8 8007B900 0000238E */  lw         $v1, 0x0($s1)
/* 2727ECC 8007B904 0C00048E */  lw         $a0, 0xC($s0)
/* 2727ED0 8007B908 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* 2727ED4 8007B90C FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* 2727ED8 8007B910 1000058E */  lw         $a1, 0x10($s0)
/* 2727EDC 8007B914 23206400 */  subu       $a0, $v1, $a0
/* 2727EE0 8007B918 AD5A000C */  jal        func_80016AB4
/* 2727EE4 8007B91C 23284500 */   subu      $a1, $v0, $a1
/* 2727EE8 8007B920 1000A427 */  addiu      $a0, $sp, 0x10
/* 2727EEC 8007B924 21282002 */  addu       $a1, $s1, $zero
/* 2727EF0 8007B928 0780013C */  lui        $at, %hi(D_80077820)
/* 2727EF4 8007B92C 207822AC */  sw         $v0, %lo(D_80077820)($at)
/* 2727EF8 8007B930 E35D000C */  jal        VecSub
/* 2727EFC 8007B934 0C000626 */   addiu     $a2, $s0, 0xC
/* 2727F00 8007B938 1000A427 */  addiu      $a0, $sp, 0x10
/* 2727F04 8007B93C 7F5C000C */  jal        func_800171FC
/* 2727F08 8007B940 21280000 */   addu      $a1, $zero, $zero
/* 2727F0C 8007B944 0780033C */  lui        $v1, %hi(g_Camera + 0x30)
/* 2727F10 8007B948 006E638C */  lw         $v1, %lo(g_Camera + 0x30)($v1)
/* 2727F14 8007B94C 0780013C */  lui        $at, %hi(D_80077824)
/* 2727F18 8007B950 247822AC */  sw         $v0, %lo(D_80077824)($at)
/* 2727F1C 8007B954 0780013C */  lui        $at, %hi(D_80077828)
/* 2727F20 8007B958 287823AC */  sw         $v1, %lo(D_80077828)($at)
/* 2727F24 8007B95C 46000292 */  lbu        $v0, 0x46($s0)
/* 2727F28 8007B960 2E050324 */  addiu      $v1, $zero, 0x52E
/* 2727F2C 8007B964 0780013C */  lui        $at, %hi(D_8007783C)
/* 2727F30 8007B968 3C7823AC */  sw         $v1, %lo(D_8007783C)($at)
/* 2727F34 8007B96C 00110200 */  sll        $v0, $v0, 4
/* 2727F38 8007B970 EEFC4224 */  addiu      $v0, $v0, -0x312
/* 2727F3C 8007B974 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 2727F40 8007B978 0780013C */  lui        $at, %hi(D_80077838)
/* 2727F44 8007B97C 387822AC */  sw         $v0, %lo(D_80077838)($at)
/* 2727F48 8007B980 1400028E */  lw         $v0, 0x14($s0)
/* 2727F4C 8007B984 00000000 */  nop
/* 2727F50 8007B988 8F054224 */  addiu      $v0, $v0, 0x58F
/* 2727F54 8007B98C 0780013C */  lui        $at, %hi(D_80077840)
/* 2727F58 8007B990 407822AC */  sw         $v0, %lo(D_80077840)($at)
/* 2727F5C 8007B994 2800BF8F */  lw         $ra, 0x28($sp)
/* 2727F60 8007B998 2400B18F */  lw         $s1, 0x24($sp)
/* 2727F64 8007B99C 2000B08F */  lw         $s0, 0x20($sp)
/* 2727F68 8007B9A0 3000BD27 */  addiu      $sp, $sp, 0x30
/* 2727F6C 8007B9A4 0800E003 */  jr         $ra
/* 2727F70 8007B9A8 00000000 */   nop
.size func_level_30_8007B870, . - func_level_30_8007B870
