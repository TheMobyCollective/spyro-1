.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8002CCC8
/* 1D4C8 8002CCC8 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 1D4CC 8002CCCC 2000B0AF */  sw         $s0, 0x20($sp)
/* 1D4D0 8002CCD0 21808000 */  addu       $s0, $a0, $zero
/* 1D4D4 8002CCD4 2C00BFAF */  sw         $ra, 0x2C($sp)
/* 1D4D8 8002CCD8 2800B2AF */  sw         $s2, 0x28($sp)
/* 1D4DC 8002CCDC 2400B1AF */  sw         $s1, 0x24($sp)
/* 1D4E0 8002CCE0 0000128E */  lw         $s2, 0x0($s0)
/* 1D4E4 8002CCE4 0880033C */  lui        $v1, %hi(D_80078D00 + 0x14)
/* 1D4E8 8002CCE8 148D638C */  lw         $v1, %lo(D_80078D00 + 0x14)($v1)
/* 1D4EC 8002CCEC 0B000224 */  addiu      $v0, $zero, 0xB
/* 1D4F0 8002CCF0 0780013C */  lui        $at, %hi(g_Gamestate)
/* 1D4F4 8002CCF4 D85722AC */  sw         $v0, %lo(g_Gamestate)($at)
/* 1D4F8 8002CCF8 01000224 */  addiu      $v0, $zero, 0x1
/* 1D4FC 8002CCFC 0780013C */  lui        $at, %hi(D_8007570C)
/* 1D500 8002CD00 0C5722AC */  sw         $v0, %lo(D_8007570C)($at)
/* 1D504 8002CD04 0780013C */  lui        $at, %hi(g_StateSwitch)
/* 1D508 8002CD08 9C5722AC */  sw         $v0, %lo(g_StateSwitch)($at)
/* 1D50C 8002CD0C 0880013C */  lui        $at, %hi(D_80078D00)
/* 1D510 8002CD10 008D20AC */  sw         $zero, %lo(D_80078D00)($at)
/* 1D514 8002CD14 0880013C */  lui        $at, %hi(D_80078D00 + 0x4)
/* 1D518 8002CD18 048D20AC */  sw         $zero, %lo(D_80078D00 + 0x4)($at)
/* 1D51C 8002CD1C 0880013C */  lui        $at, %hi(D_80078D00 + 0xC)
/* 1D520 8002CD20 0C8D20AC */  sw         $zero, %lo(D_80078D00 + 0xC)($at)
/* 1D524 8002CD24 05006010 */  beqz       $v1, .L8002CD3C
/* 1D528 8002CD28 02000224 */   addiu     $v0, $zero, 0x2
/* 1D52C 8002CD2C 0880013C */  lui        $at, %hi(D_80078D00 + 0x8)
/* 1D530 8002CD30 088D20AC */  sw         $zero, %lo(D_80078D00 + 0x8)($at)
/* 1D534 8002CD34 52B30008 */  j          .L8002CD48
/* 1D538 8002CD38 21280000 */   addu      $a1, $zero, $zero
.L8002CD3C:
/* 1D53C 8002CD3C 0880013C */  lui        $at, %hi(D_80078D00 + 0x8)
/* 1D540 8002CD40 088D22AC */  sw         $v0, %lo(D_80078D00 + 0x8)($at)
/* 1D544 8002CD44 21280000 */  addu       $a1, $zero, $zero
.L8002CD48:
/* 1D548 8002CD48 0880023C */  lui        $v0, %hi(g_SpyroFlame + 0xA0)
/* 1D54C 8002CD4C 6887428C */  lw         $v0, %lo(g_SpyroFlame + 0xA0)($v0)
/* 1D550 8002CD50 0780033C */  lui        $v1, %hi(g_Spu + 0x2CC)
/* 1D554 8002CD54 D461638C */  lw         $v1, %lo(g_Spu + 0x2CC)($v1)
/* 1D558 8002CD58 10000624 */  addiu      $a2, $zero, 0x10
/* 1D55C 8002CD5C 0880013C */  lui        $at, %hi(D_80078D00 + 0x74)
/* 1D560 8002CD60 748D30AC */  sw         $s0, %lo(D_80078D00 + 0x74)($at)
/* 1D564 8002CD64 0780013C */  lui        $at, %hi(D_800758A4)
/* 1D568 8002CD68 A45822AC */  sw         $v0, %lo(D_800758A4)($at)
/* 1D56C 8002CD6C 2C006490 */  lbu        $a0, 0x2C($v1)
/* 1D570 8002CD70 9E56010C */  jal        PlaySound
/* 1D574 8002CD74 21380000 */   addu      $a3, $zero, $zero
/* 1D578 8002CD78 092B010C */  jal        func_8004AC24
/* 1D57C 8002CD7C 01000424 */   addiu     $a0, $zero, 0x1
/* 1D580 8002CD80 0880113C */  lui        $s1, %hi(g_Spyro + 0x18)
/* 1D584 8002CD84 708A3126 */  addiu      $s1, $s1, %lo(g_Spyro + 0x18)
/* 1D588 8002CD88 0880033C */  lui        $v1, %hi(g_Spyro + 0x11C)
/* 1D58C 8002CD8C 748B638C */  lw         $v1, %lo(g_Spyro + 0x11C)($v1)
/* 1D590 8002CD90 01000224 */  addiu      $v0, $zero, 0x1
/* 1D594 8002CD94 000022A2 */  sb         $v0, 0x0($s1)
/* 1D598 8002CD98 0880053C */  lui        $a1, %hi(g_Spyro + 0x4)
/* 1D59C 8002CD9C 5C8AA58C */  lw         $a1, %lo(g_Spyro + 0x4)($a1)
/* 1D5A0 8002CDA0 01000624 */  addiu      $a2, $zero, 0x1
/* 1D5A4 8002CDA4 0880013C */  lui        $at, %hi(g_Spyro + 0x19)
/* 1D5A8 8002CDA8 718A22A0 */  sb         $v0, %lo(g_Spyro + 0x19)($at)
/* 1D5AC 8002CDAC 0880013C */  lui        $at, %hi(g_Spyro + 0x1E)
/* 1D5B0 8002CDB0 768A20A0 */  sb         $zero, %lo(g_Spyro + 0x1E)($at)
/* 1D5B4 8002CDB4 0880013C */  lui        $at, %hi(g_Spyro + 0x1F)
/* 1D5B8 8002CDB8 778A22A0 */  sb         $v0, %lo(g_Spyro + 0x1F)($at)
/* 1D5BC 8002CDBC 0880013C */  lui        $at, %hi(g_Spyro + 0x24)
/* 1D5C0 8002CDC0 7C8A20A0 */  sb         $zero, %lo(g_Spyro + 0x24)($at)
/* 1D5C4 8002CDC4 0880013C */  lui        $at, %hi(D_80078D00 + 0x6C)
/* 1D5C8 8002CDC8 6C8D23AC */  sw         $v1, %lo(D_80078D00 + 0x6C)($at)
/* 1D5CC 8002CDCC 0400438E */  lw         $v1, 0x4($s2)
/* 1D5D0 8002CDD0 E8FF248E */  lw         $a0, -0x18($s1)
/* 1D5D4 8002CDD4 40100300 */  sll        $v0, $v1, 1
/* 1D5D8 8002CDD8 21104300 */  addu       $v0, $v0, $v1
/* 1D5DC 8002CDDC 80100200 */  sll        $v0, $v0, 2
/* 1D5E0 8002CDE0 23104300 */  subu       $v0, $v0, $v1
/* 1D5E4 8002CDE4 0780033C */  lui        $v1, %hi(D_80075828)
/* 1D5E8 8002CDE8 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 1D5EC 8002CDEC C0100200 */  sll        $v0, $v0, 3
/* 1D5F0 8002CDF0 21104300 */  addu       $v0, $v0, $v1
/* 1D5F4 8002CDF4 0C00438C */  lw         $v1, 0xC($v0)
/* 1D5F8 8002CDF8 1000428C */  lw         $v0, 0x10($v0)
/* 1D5FC 8002CDFC 23206400 */  subu       $a0, $v1, $a0
/* 1D600 8002CE00 AD5A000C */  jal        Atan2
/* 1D604 8002CE04 23284500 */   subu      $a1, $v0, $a1
/* 1D608 8002CE08 01000624 */  addiu      $a2, $zero, 0x1
/* 1D60C 8002CE0C 0880013C */  lui        $at, %hi(D_80078D00 + 0x70)
/* 1D610 8002CE10 708D22AC */  sw         $v0, %lo(D_80078D00 + 0x70)($at)
/* 1D614 8002CE14 0C00038E */  lw         $v1, 0xC($s0)
/* 1D618 8002CE18 E8FF248E */  lw         $a0, -0x18($s1)
/* 1D61C 8002CE1C 1000028E */  lw         $v0, 0x10($s0)
/* 1D620 8002CE20 0880053C */  lui        $a1, %hi(g_Spyro + 0x4)
/* 1D624 8002CE24 5C8AA58C */  lw         $a1, %lo(g_Spyro + 0x4)($a1)
/* 1D628 8002CE28 23206400 */  subu       $a0, $v1, $a0
/* 1D62C 8002CE2C AD5A000C */  jal        Atan2
/* 1D630 8002CE30 23284500 */   subu      $a1, $v0, $a1
/* 1D634 8002CE34 1000A427 */  addiu      $a0, $sp, 0x10
/* 1D638 8002CE38 0C000526 */  addiu      $a1, $s0, 0xC
/* 1D63C 8002CE3C E8FF3226 */  addiu      $s2, $s1, -0x18
/* 1D640 8002CE40 0880013C */  lui        $at, %hi(D_80078D00 + 0x2C)
/* 1D644 8002CE44 2C8D22AC */  sw         $v0, %lo(D_80078D00 + 0x2C)($at)
/* 1D648 8002CE48 E35D000C */  jal        VecSub
/* 1D64C 8002CE4C 21304002 */   addu      $a2, $s2, $zero
/* 1D650 8002CE50 1000A427 */  addiu      $a0, $sp, 0x10
/* 1D654 8002CE54 7F5C000C */  jal        VecMagnitude
/* 1D658 8002CE58 21280000 */   addu      $a1, $zero, $zero
/* 1D65C 8002CE5C 0880013C */  lui        $at, %hi(D_80078D00 + 0x30)
/* 1D660 8002CE60 308D22AC */  sw         $v0, %lo(D_80078D00 + 0x30)($at)
/* 1D664 8002CE64 1400038E */  lw         $v1, 0x14($s0)
/* 1D668 8002CE68 0880043C */  lui        $a0, %hi(D_80078D00 + 0x70)
/* 1D66C 8002CE6C 708D848C */  lw         $a0, %lo(D_80078D00 + 0x70)($a0)
/* 1D670 8002CE70 80040224 */  addiu      $v0, $zero, 0x480
/* 1D674 8002CE74 0880013C */  lui        $at, %hi(D_80078D00 + 0x3C)
/* 1D678 8002CE78 3C8D22AC */  sw         $v0, %lo(D_80078D00 + 0x3C)($at)
/* 1D67C 8002CE7C 0880013C */  lui        $at, %hi(D_80078D00 + 0x34)
/* 1D680 8002CE80 348D23AC */  sw         $v1, %lo(D_80078D00 + 0x34)($at)
/* 1D684 8002CE84 0880013C */  lui        $at, %hi(D_80078D00 + 0x38)
/* 1D688 8002CE88 388D24AC */  sw         $a0, %lo(D_80078D00 + 0x38)($at)
/* 1D68C 8002CE8C F0FF228E */  lw         $v0, -0x10($s1)
/* 1D690 8002CE90 0780053C */  lui        $a1, %hi(D_80075898)
/* 1D694 8002CE94 9858A58C */  lw         $a1, %lo(D_80075898)($a1)
/* 1D698 8002CE98 70014224 */  addiu      $v0, $v0, 0x170
/* 1D69C 8002CE9C 0880013C */  lui        $at, %hi(D_80078D00 + 0x40)
/* 1D6A0 8002CEA0 408D22AC */  sw         $v0, %lo(D_80078D00 + 0x40)($at)
/* 1D6A4 8002CEA4 2000A010 */  beqz       $a1, .L8002CF28
/* 1D6A8 8002CEA8 00000000 */   nop
/* 1D6AC 8002CEAC 01000624 */  addiu      $a2, $zero, 0x1
/* 1D6B0 8002CEB0 0C00A38C */  lw         $v1, 0xC($a1)
/* 1D6B4 8002CEB4 E8FF248E */  lw         $a0, -0x18($s1)
/* 1D6B8 8002CEB8 1000A28C */  lw         $v0, 0x10($a1)
/* 1D6BC 8002CEBC 0880053C */  lui        $a1, %hi(g_Spyro + 0x4)
/* 1D6C0 8002CEC0 5C8AA58C */  lw         $a1, %lo(g_Spyro + 0x4)($a1)
/* 1D6C4 8002CEC4 23206400 */  subu       $a0, $v1, $a0
/* 1D6C8 8002CEC8 AD5A000C */  jal        Atan2
/* 1D6CC 8002CECC 23284500 */   subu      $a1, $v0, $a1
/* 1D6D0 8002CED0 1000A427 */  addiu      $a0, $sp, 0x10
/* 1D6D4 8002CED4 0780053C */  lui        $a1, %hi(D_80075898)
/* 1D6D8 8002CED8 9858A58C */  lw         $a1, %lo(D_80075898)($a1)
/* 1D6DC 8002CEDC 21304002 */  addu       $a2, $s2, $zero
/* 1D6E0 8002CEE0 0880013C */  lui        $at, %hi(D_80078D00 + 0x44)
/* 1D6E4 8002CEE4 448D22AC */  sw         $v0, %lo(D_80078D00 + 0x44)($at)
/* 1D6E8 8002CEE8 E35D000C */  jal        VecSub
/* 1D6EC 8002CEEC 0C00A524 */   addiu     $a1, $a1, 0xC
/* 1D6F0 8002CEF0 1000A427 */  addiu      $a0, $sp, 0x10
/* 1D6F4 8002CEF4 7F5C000C */  jal        VecMagnitude
/* 1D6F8 8002CEF8 21280000 */   addu      $a1, $zero, $zero
/* 1D6FC 8002CEFC 0880013C */  lui        $at, %hi(D_80078D00 + 0x48)
/* 1D700 8002CF00 488D22AC */  sw         $v0, %lo(D_80078D00 + 0x48)($at)
/* 1D704 8002CF04 0880023C */  lui        $v0, %hi(D_80078D00 + 0x70)
/* 1D708 8002CF08 708D428C */  lw         $v0, %lo(D_80078D00 + 0x70)($v0)
/* 1D70C 8002CF0C 00060324 */  addiu      $v1, $zero, 0x600
/* 1D710 8002CF10 0880013C */  lui        $at, %hi(D_80078D00 + 0x50)
/* 1D714 8002CF14 508D23AC */  sw         $v1, %lo(D_80078D00 + 0x50)($at)
/* 1D718 8002CF18 00084224 */  addiu      $v0, $v0, 0x800
/* 1D71C 8002CF1C FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 1D720 8002CF20 0880013C */  lui        $at, %hi(D_80078D00 + 0x4C)
/* 1D724 8002CF24 4C8D22AC */  sw         $v0, %lo(D_80078D00 + 0x4C)($at)
.L8002CF28:
/* 1D728 8002CF28 01000624 */  addiu      $a2, $zero, 0x1
/* 1D72C 8002CF2C 0780103C */  lui        $s0, %hi(g_Camera + 0x28)
/* 1D730 8002CF30 F86D1026 */  addiu      $s0, $s0, %lo(g_Camera + 0x28)
/* 1D734 8002CF34 0000038E */  lw         $v1, 0x0($s0)
/* 1D738 8002CF38 E8FF248E */  lw         $a0, -0x18($s1)
/* 1D73C 8002CF3C 0780023C */  lui        $v0, %hi(g_Camera + 0x2C)
/* 1D740 8002CF40 FC6D428C */  lw         $v0, %lo(g_Camera + 0x2C)($v0)
/* 1D744 8002CF44 0880053C */  lui        $a1, %hi(g_Spyro + 0x4)
/* 1D748 8002CF48 5C8AA58C */  lw         $a1, %lo(g_Spyro + 0x4)($a1)
/* 1D74C 8002CF4C 23206400 */  subu       $a0, $v1, $a0
/* 1D750 8002CF50 AD5A000C */  jal        Atan2
/* 1D754 8002CF54 23284500 */   subu      $a1, $v0, $a1
/* 1D758 8002CF58 1000A427 */  addiu      $a0, $sp, 0x10
/* 1D75C 8002CF5C 21280002 */  addu       $a1, $s0, $zero
/* 1D760 8002CF60 0880013C */  lui        $at, %hi(D_80078D00 + 0x54)
/* 1D764 8002CF64 548D22AC */  sw         $v0, %lo(D_80078D00 + 0x54)($at)
/* 1D768 8002CF68 E35D000C */  jal        VecSub
/* 1D76C 8002CF6C 21304002 */   addu      $a2, $s2, $zero
/* 1D770 8002CF70 1000A427 */  addiu      $a0, $sp, 0x10
/* 1D774 8002CF74 7F5C000C */  jal        VecMagnitude
/* 1D778 8002CF78 21280000 */   addu      $a1, $zero, $zero
/* 1D77C 8002CF7C 0880043C */  lui        $a0, %hi(D_80078D00 + 0x54)
/* 1D780 8002CF80 548D848C */  lw         $a0, %lo(D_80078D00 + 0x54)($a0)
/* 1D784 8002CF84 0880053C */  lui        $a1, %hi(D_80078D00 + 0x70)
/* 1D788 8002CF88 708DA58C */  lw         $a1, %lo(D_80078D00 + 0x70)($a1)
/* 1D78C 8002CF8C 0880013C */  lui        $at, %hi(D_80078D00 + 0x58)
/* 1D790 8002CF90 588D22AC */  sw         $v0, %lo(D_80078D00 + 0x58)($at)
/* 1D794 8002CF94 B0000224 */  addiu      $v0, $zero, 0xB0
/* 1D798 8002CF98 0880013C */  lui        $at, %hi(D_80078D00 + 0x10)
/* 1D79C 8002CF9C 108D22AC */  sw         $v0, %lo(D_80078D00 + 0x10)($at)
/* 1D7A0 8002CFA0 0780023C */  lui        $v0, %hi(g_Camera + 0x30)
/* 1D7A4 8002CFA4 006E428C */  lw         $v0, %lo(g_Camera + 0x30)($v0)
/* 1D7A8 8002CFA8 0B03A524 */  addiu      $a1, $a1, 0x30B
/* 1D7AC 8002CFAC FF0FA530 */  andi       $a1, $a1, 0xFFF
/* 1D7B0 8002CFB0 0880013C */  lui        $at, %hi(D_80078D00 + 0x5C)
/* 1D7B4 8002CFB4 5C8D22AC */  sw         $v0, %lo(D_80078D00 + 0x5C)($at)
/* 1D7B8 8002CFB8 0880013C */  lui        $at, %hi(D_80078D00 + 0x60)
/* 1D7BC 8002CFBC 608D25AC */  sw         $a1, %lo(D_80078D00 + 0x60)($at)
/* 1D7C0 8002CFC0 4A5E000C */  jal        func_80017928
/* 1D7C4 8002CFC4 00000000 */   nop
/* 1D7C8 8002CFC8 01044228 */  slti       $v0, $v0, 0x401
/* 1D7CC 8002CFCC 09004014 */  bnez       $v0, .L8002CFF4
/* 1D7D0 8002CFD0 00000000 */   nop
/* 1D7D4 8002CFD4 0880023C */  lui        $v0, %hi(D_80078D00 + 0x70)
/* 1D7D8 8002CFD8 708D428C */  lw         $v0, %lo(D_80078D00 + 0x70)($v0)
/* 1D7DC 8002CFDC 0880013C */  lui        $at, %hi(D_80078D00 + 0x10)
/* 1D7E0 8002CFE0 108D20AC */  sw         $zero, %lo(D_80078D00 + 0x10)($at)
/* 1D7E4 8002CFE4 F5FC4224 */  addiu      $v0, $v0, -0x30B
/* 1D7E8 8002CFE8 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 1D7EC 8002CFEC 0880013C */  lui        $at, %hi(D_80078D00 + 0x60)
/* 1D7F0 8002CFF0 608D22AC */  sw         $v0, %lo(D_80078D00 + 0x60)($at)
.L8002CFF4:
/* 1D7F4 8002CFF4 F0FF228E */  lw         $v0, -0x10($s1)
/* 1D7F8 8002CFF8 C9040324 */  addiu      $v1, $zero, 0x4C9
/* 1D7FC 8002CFFC 0880013C */  lui        $at, %hi(D_80078D00 + 0x64)
/* 1D800 8002D000 648D23AC */  sw         $v1, %lo(D_80078D00 + 0x64)($at)
/* 1D804 8002D004 6B054224 */  addiu      $v0, $v0, 0x56B
/* 1D808 8002D008 0880013C */  lui        $at, %hi(D_80078D00 + 0x68)
/* 1D80C 8002D00C 688D22AC */  sw         $v0, %lo(D_80078D00 + 0x68)($at)
/* 1D810 8002D010 2C00BF8F */  lw         $ra, 0x2C($sp)
/* 1D814 8002D014 2800B28F */  lw         $s2, 0x28($sp)
/* 1D818 8002D018 2400B18F */  lw         $s1, 0x24($sp)
/* 1D81C 8002D01C 2000B08F */  lw         $s0, 0x20($sp)
/* 1D820 8002D020 3000BD27 */  addiu      $sp, $sp, 0x30
/* 1D824 8002D024 0800E003 */  jr         $ra
/* 1D828 8002D028 00000000 */   nop
.size func_8002CCC8, . - func_8002CCC8
