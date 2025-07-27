.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_20_8007B878
/* 187EE40 8007B878 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 187EE44 8007B87C 2000B0AF */  sw         $s0, 0x20($sp)
/* 187EE48 8007B880 21808000 */  addu       $s0, $a0, $zero
/* 187EE4C 8007B884 01000624 */  addiu      $a2, $zero, 0x1
/* 187EE50 8007B888 2800BFAF */  sw         $ra, 0x28($sp)
/* 187EE54 8007B88C 2400B1AF */  sw         $s1, 0x24($sp)
/* 187EE58 8007B890 0000038E */  lw         $v1, 0x0($s0)
/* 187EE5C 8007B894 0C000224 */  addiu      $v0, $zero, 0xC
/* 187EE60 8007B898 0780013C */  lui        $at, %hi(g_Gamestate)
/* 187EE64 8007B89C D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 187EE68 8007B8A0 01000224 */  addiu      $v0, $zero, 0x1
/* 187EE6C 8007B8A4 0780013C */  lui        $at, %hi(D_800777E8)
/* 187EE70 8007B8A8 E87720AC */  sw         $zero, %lo(D_800777E8)($at)
/* 187EE74 8007B8AC 0780013C */  lui        $at, %hi(D_800777E8 + 0x4)
/* 187EE78 8007B8B0 EC7720AC */  sw         $zero, %lo(D_800777E8 + 0x4)($at)
/* 187EE7C 8007B8B4 0780013C */  lui        $at, %hi(D_800777E8 + 0x8)
/* 187EE80 8007B8B8 F07720AC */  sw         $zero, %lo(D_800777E8 + 0x8)($at)
/* 187EE84 8007B8BC 0780013C */  lui        $at, %hi(D_800777E8 + 0x64)
/* 187EE88 8007B8C0 4C7830AC */  sw         $s0, %lo(D_800777E8 + 0x64)($at)
/* 187EE8C 8007B8C4 0000638C */  lw         $v1, 0x0($v1)
/* 187EE90 8007B8C8 0780113C */  lui        $s1, %hi(g_Camera + 0x28)
/* 187EE94 8007B8CC F86D3126 */  addiu      $s1, $s1, %lo(g_Camera + 0x28)
/* 187EE98 8007B8D0 0780013C */  lui        $at, %hi(D_8007570C)
/* 187EE9C 8007B8D4 0C5722AC */  sw         $v0, %lo(D_8007570C)($at)
/* 187EEA0 8007B8D8 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 187EEA4 8007B8DC 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 187EEA8 8007B8E0 40100300 */  sll        $v0, $v1, 1
/* 187EEAC 8007B8E4 21104300 */  addu       $v0, $v0, $v1
/* 187EEB0 8007B8E8 80100200 */  sll        $v0, $v0, 2
/* 187EEB4 8007B8EC 23104300 */  subu       $v0, $v0, $v1
/* 187EEB8 8007B8F0 0780033C */  lui        $v1, %hi(D_80075828)
/* 187EEBC 8007B8F4 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 187EEC0 8007B8F8 C0100200 */  sll        $v0, $v0, 3
/* 187EEC4 8007B8FC 21186200 */  addu       $v1, $v1, $v0
/* 187EEC8 8007B900 0780013C */  lui        $at, %hi(D_800777E8 + 0x68)
/* 187EECC 8007B904 507823AC */  sw         $v1, %lo(D_800777E8 + 0x68)($at)
/* 187EED0 8007B908 0000238E */  lw         $v1, 0x0($s1)
/* 187EED4 8007B90C 0C00048E */  lw         $a0, 0xC($s0)
/* 187EED8 8007B910 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* 187EEDC 8007B914 FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* 187EEE0 8007B918 1000058E */  lw         $a1, 0x10($s0)
/* 187EEE4 8007B91C 23206400 */  subu       $a0, $v1, $a0
/* 187EEE8 8007B920 AD5A000C */  jal        Atan2
/* 187EEEC 8007B924 23284500 */   subu      $a1, $v0, $a1
/* 187EEF0 8007B928 1000A427 */  addiu      $a0, $sp, 0x10
/* 187EEF4 8007B92C 21282002 */  addu       $a1, $s1, $zero
/* 187EEF8 8007B930 0780013C */  lui        $at, %hi(D_800777E8 + 0x38)
/* 187EEFC 8007B934 207822AC */  sw         $v0, %lo(D_800777E8 + 0x38)($at)
/* 187EF00 8007B938 E35D000C */  jal        VecSub
/* 187EF04 8007B93C 0C000626 */   addiu     $a2, $s0, 0xC
/* 187EF08 8007B940 1000A427 */  addiu      $a0, $sp, 0x10
/* 187EF0C 8007B944 7F5C000C */  jal        VecMagnitude
/* 187EF10 8007B948 21280000 */   addu      $a1, $zero, $zero
/* 187EF14 8007B94C 0780033C */  lui        $v1, %hi(g_Camera + 0x30)
/* 187EF18 8007B950 006E638C */  lw         $v1, %lo(g_Camera + 0x30)($v1)
/* 187EF1C 8007B954 0780013C */  lui        $at, %hi(D_800777E8 + 0x3C)
/* 187EF20 8007B958 247822AC */  sw         $v0, %lo(D_800777E8 + 0x3C)($at)
/* 187EF24 8007B95C 0780013C */  lui        $at, %hi(D_800777E8 + 0x40)
/* 187EF28 8007B960 287823AC */  sw         $v1, %lo(D_800777E8 + 0x40)($at)
/* 187EF2C 8007B964 46000292 */  lbu        $v0, 0x46($s0)
/* 187EF30 8007B968 2E050324 */  addiu      $v1, $zero, 0x52E
/* 187EF34 8007B96C 0780013C */  lui        $at, %hi(D_800777E8 + 0x54)
/* 187EF38 8007B970 3C7823AC */  sw         $v1, %lo(D_800777E8 + 0x54)($at)
/* 187EF3C 8007B974 00110200 */  sll        $v0, $v0, 4
/* 187EF40 8007B978 EEFC4224 */  addiu      $v0, $v0, -0x312
/* 187EF44 8007B97C FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 187EF48 8007B980 0780013C */  lui        $at, %hi(D_800777E8 + 0x50)
/* 187EF4C 8007B984 387822AC */  sw         $v0, %lo(D_800777E8 + 0x50)($at)
/* 187EF50 8007B988 1400028E */  lw         $v0, 0x14($s0)
/* 187EF54 8007B98C 00000000 */  nop
/* 187EF58 8007B990 8F054224 */  addiu      $v0, $v0, 0x58F
/* 187EF5C 8007B994 0780013C */  lui        $at, %hi(D_800777E8 + 0x58)
/* 187EF60 8007B998 407822AC */  sw         $v0, %lo(D_800777E8 + 0x58)($at)
/* 187EF64 8007B99C 2800BF8F */  lw         $ra, 0x28($sp)
/* 187EF68 8007B9A0 2400B18F */  lw         $s1, 0x24($sp)
/* 187EF6C 8007B9A4 2000B08F */  lw         $s0, 0x20($sp)
/* 187EF70 8007B9A8 3000BD27 */  addiu      $sp, $sp, 0x30
/* 187EF74 8007B9AC 0800E003 */  jr         $ra
/* 187EF78 8007B9B0 00000000 */   nop
.size func_level_20_8007B878, . - func_level_20_8007B878
