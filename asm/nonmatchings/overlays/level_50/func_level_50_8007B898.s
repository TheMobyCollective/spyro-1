.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_50_8007B898
/* 43DBE60 8007B898 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 43DBE64 8007B89C 2000B0AF */  sw         $s0, 0x20($sp)
/* 43DBE68 8007B8A0 21808000 */  addu       $s0, $a0, $zero
/* 43DBE6C 8007B8A4 01000624 */  addiu      $a2, $zero, 0x1
/* 43DBE70 8007B8A8 2800BFAF */  sw         $ra, 0x28($sp)
/* 43DBE74 8007B8AC 2400B1AF */  sw         $s1, 0x24($sp)
/* 43DBE78 8007B8B0 0000038E */  lw         $v1, 0x0($s0)
/* 43DBE7C 8007B8B4 0C000224 */  addiu      $v0, $zero, 0xC
/* 43DBE80 8007B8B8 0780013C */  lui        $at, %hi(g_Gamestate)
/* 43DBE84 8007B8BC D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 43DBE88 8007B8C0 01000224 */  addiu      $v0, $zero, 0x1
/* 43DBE8C 8007B8C4 0780013C */  lui        $at, %hi(D_800777E8)
/* 43DBE90 8007B8C8 E87720AC */  sw         $zero, %lo(D_800777E8)($at)
/* 43DBE94 8007B8CC 0780013C */  lui        $at, %hi(D_800777E8 + 0x4)
/* 43DBE98 8007B8D0 EC7720AC */  sw         $zero, %lo(D_800777E8 + 0x4)($at)
/* 43DBE9C 8007B8D4 0780013C */  lui        $at, %hi(D_800777E8 + 0x8)
/* 43DBEA0 8007B8D8 F07720AC */  sw         $zero, %lo(D_800777E8 + 0x8)($at)
/* 43DBEA4 8007B8DC 0780013C */  lui        $at, %hi(D_800777E8 + 0x64)
/* 43DBEA8 8007B8E0 4C7830AC */  sw         $s0, %lo(D_800777E8 + 0x64)($at)
/* 43DBEAC 8007B8E4 0000638C */  lw         $v1, 0x0($v1)
/* 43DBEB0 8007B8E8 0780113C */  lui        $s1, %hi(g_Camera + 0x28)
/* 43DBEB4 8007B8EC F86D3126 */  addiu      $s1, $s1, %lo(g_Camera + 0x28)
/* 43DBEB8 8007B8F0 0780013C */  lui        $at, %hi(D_8007570C)
/* 43DBEBC 8007B8F4 0C5722AC */  sw         $v0, %lo(D_8007570C)($at)
/* 43DBEC0 8007B8F8 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 43DBEC4 8007B8FC 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 43DBEC8 8007B900 40100300 */  sll        $v0, $v1, 1
/* 43DBECC 8007B904 21104300 */  addu       $v0, $v0, $v1
/* 43DBED0 8007B908 80100200 */  sll        $v0, $v0, 2
/* 43DBED4 8007B90C 23104300 */  subu       $v0, $v0, $v1
/* 43DBED8 8007B910 0780033C */  lui        $v1, %hi(D_80075828)
/* 43DBEDC 8007B914 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 43DBEE0 8007B918 C0100200 */  sll        $v0, $v0, 3
/* 43DBEE4 8007B91C 21186200 */  addu       $v1, $v1, $v0
/* 43DBEE8 8007B920 0780013C */  lui        $at, %hi(D_800777E8 + 0x68)
/* 43DBEEC 8007B924 507823AC */  sw         $v1, %lo(D_800777E8 + 0x68)($at)
/* 43DBEF0 8007B928 0000238E */  lw         $v1, 0x0($s1)
/* 43DBEF4 8007B92C 0C00048E */  lw         $a0, 0xC($s0)
/* 43DBEF8 8007B930 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* 43DBEFC 8007B934 FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* 43DBF00 8007B938 1000058E */  lw         $a1, 0x10($s0)
/* 43DBF04 8007B93C 23206400 */  subu       $a0, $v1, $a0
/* 43DBF08 8007B940 AD5A000C */  jal        Atan2
/* 43DBF0C 8007B944 23284500 */   subu      $a1, $v0, $a1
/* 43DBF10 8007B948 1000A427 */  addiu      $a0, $sp, 0x10
/* 43DBF14 8007B94C 21282002 */  addu       $a1, $s1, $zero
/* 43DBF18 8007B950 0780013C */  lui        $at, %hi(D_800777E8 + 0x38)
/* 43DBF1C 8007B954 207822AC */  sw         $v0, %lo(D_800777E8 + 0x38)($at)
/* 43DBF20 8007B958 E35D000C */  jal        VecSub
/* 43DBF24 8007B95C 0C000626 */   addiu     $a2, $s0, 0xC
/* 43DBF28 8007B960 1000A427 */  addiu      $a0, $sp, 0x10
/* 43DBF2C 8007B964 7F5C000C */  jal        VecMagnitude
/* 43DBF30 8007B968 21280000 */   addu      $a1, $zero, $zero
/* 43DBF34 8007B96C 0780033C */  lui        $v1, %hi(g_Camera + 0x30)
/* 43DBF38 8007B970 006E638C */  lw         $v1, %lo(g_Camera + 0x30)($v1)
/* 43DBF3C 8007B974 0780013C */  lui        $at, %hi(D_800777E8 + 0x3C)
/* 43DBF40 8007B978 247822AC */  sw         $v0, %lo(D_800777E8 + 0x3C)($at)
/* 43DBF44 8007B97C 0780013C */  lui        $at, %hi(D_800777E8 + 0x40)
/* 43DBF48 8007B980 287823AC */  sw         $v1, %lo(D_800777E8 + 0x40)($at)
/* 43DBF4C 8007B984 46000292 */  lbu        $v0, 0x46($s0)
/* 43DBF50 8007B988 2E050324 */  addiu      $v1, $zero, 0x52E
/* 43DBF54 8007B98C 0780013C */  lui        $at, %hi(D_800777E8 + 0x54)
/* 43DBF58 8007B990 3C7823AC */  sw         $v1, %lo(D_800777E8 + 0x54)($at)
/* 43DBF5C 8007B994 00110200 */  sll        $v0, $v0, 4
/* 43DBF60 8007B998 EEFC4224 */  addiu      $v0, $v0, -0x312
/* 43DBF64 8007B99C FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 43DBF68 8007B9A0 0780013C */  lui        $at, %hi(D_800777E8 + 0x50)
/* 43DBF6C 8007B9A4 387822AC */  sw         $v0, %lo(D_800777E8 + 0x50)($at)
/* 43DBF70 8007B9A8 1400028E */  lw         $v0, 0x14($s0)
/* 43DBF74 8007B9AC 00000000 */  nop
/* 43DBF78 8007B9B0 8F054224 */  addiu      $v0, $v0, 0x58F
/* 43DBF7C 8007B9B4 0780013C */  lui        $at, %hi(D_800777E8 + 0x58)
/* 43DBF80 8007B9B8 407822AC */  sw         $v0, %lo(D_800777E8 + 0x58)($at)
/* 43DBF84 8007B9BC 2800BF8F */  lw         $ra, 0x28($sp)
/* 43DBF88 8007B9C0 2400B18F */  lw         $s1, 0x24($sp)
/* 43DBF8C 8007B9C4 2000B08F */  lw         $s0, 0x20($sp)
/* 43DBF90 8007B9C8 3000BD27 */  addiu      $sp, $sp, 0x30
/* 43DBF94 8007B9CC 0800E003 */  jr         $ra
/* 43DBF98 8007B9D0 00000000 */   nop
.size func_level_50_8007B898, . - func_level_50_8007B898
