.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8001C694
/* CE94 8001C694 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* CE98 8001C698 0100033C */  lui        $v1, (0x1C000 >> 16)
/* CE9C 8001C69C 0880023C */  lui        $v0, %hi(D_800785E8)
/* CEA0 8001C6A0 E885428C */  lw         $v0, %lo(D_800785E8)($v0)
/* CEA4 8001C6A4 0780043C */  lui        $a0, %hi(D_800758B8)
/* CEA8 8001C6A8 B858848C */  lw         $a0, %lo(D_800758B8)($a0)
/* CEAC 8001C6AC 00C06334 */  ori        $v1, $v1, (0x1C000 & 0xFFFF)
/* CEB0 8001C6B0 2C00BFAF */  sw         $ra, 0x2C($sp)
/* CEB4 8001C6B4 2800B2AF */  sw         $s2, 0x28($sp)
/* CEB8 8001C6B8 2400B1AF */  sw         $s1, 0x24($sp)
/* CEBC 8001C6BC 2000B0AF */  sw         $s0, 0x20($sp)
/* CEC0 8001C6C0 0780013C */  lui        $at, %hi(D_800758B0)
/* CEC4 8001C6C4 B05820AC */  sw         $zero, %lo(D_800758B0)($at)
/* CEC8 8001C6C8 0780013C */  lui        $at, %hi(D_800757B0)
/* CECC 8001C6CC B05722AC */  sw         $v0, %lo(D_800757B0)($at)
/* CED0 8001C6D0 21104300 */  addu       $v0, $v0, $v1
/* CED4 8001C6D4 0780013C */  lui        $at, %hi(D_80075780)
/* CED8 8001C6D8 805722AC */  sw         $v0, %lo(D_80075780)($at)
/* CEDC 8001C6DC 05008010 */  beqz       $a0, .L8001C6F4
/* CEE0 8001C6E0 01000224 */   addiu     $v0, $zero, 0x1
/* CEE4 8001C6E4 6F008210 */  beq        $a0, $v0, .L8001C8A4
/* CEE8 8001C6E8 20000624 */   addiu     $a2, $zero, 0x20
/* CEEC 8001C6EC 54720008 */  j          .L8001C950
/* CEF0 8001C6F0 00000000 */   nop
.L8001C6F4:
/* CEF4 8001C6F4 0780023C */  lui        $v0, %hi(D_80075888)
/* CEF8 8001C6F8 8858428C */  lw         $v0, %lo(D_80075888)($v0)
/* CEFC 8001C6FC 0780043C */  lui        $a0, %hi(g_DB)
/* CF00 8001C700 E06E8424 */  addiu      $a0, $a0, %lo(g_DB)
/* CF04 8001C704 02004414 */  bne        $v0, $a0, .L8001C710
/* CF08 8001C708 00000000 */   nop
/* CF0C 8001C70C 84008424 */  addiu      $a0, $a0, 0x84
.L8001C710:
/* CF10 8001C710 767F010C */  jal        PutDrawEnv
/* CF14 8001C714 21880000 */   addu      $s1, $zero, $zero
/* CF18 8001C718 1000A427 */  addiu      $a0, $sp, 0x10
/* CF1C 8001C71C 0780053C */  lui        $a1, %hi(D_8006F310)
/* CF20 8001C720 10F3A524 */  addiu      $a1, $a1, %lo(D_8006F310)
/* CF24 8001C724 0780033C */  lui        $v1, %hi(D_8007568C)
/* CF28 8001C728 8C56638C */  lw         $v1, %lo(D_8007568C)($v1)
/* CF2C 8001C72C E0000224 */  addiu      $v0, $zero, 0xE0
/* CF30 8001C730 1200A2A7 */  sh         $v0, 0x12($sp)
/* CF34 8001C734 01000224 */  addiu      $v0, $zero, 0x1
/* CF38 8001C738 1600A2A7 */  sh         $v0, 0x16($sp)
/* CF3C 8001C73C 00026224 */  addiu      $v0, $v1, 0x200
/* CF40 8001C740 1000A2A7 */  sh         $v0, 0x10($sp)
/* CF44 8001C744 20000224 */  addiu      $v0, $zero, 0x20
/* CF48 8001C748 23104300 */  subu       $v0, $v0, $v1
/* CF4C 8001C74C 8A7E010C */  jal        LoadImage
/* CF50 8001C750 1400A2A7 */   sh        $v0, 0x14($sp)
/* CF54 8001C754 D97D010C */  jal        DrawSync
/* CF58 8001C758 21200000 */   addu      $a0, $zero, $zero
/* CF5C 8001C75C FF030524 */  addiu      $a1, $zero, 0x3FF
.L8001C760:
/* CF60 8001C760 C0191100 */  sll        $v1, $s1, 7
/* CF64 8001C764 88002826 */  addiu      $t0, $s1, 0x88
/* CF68 8001C768 0780103C */  lui        $s0, %hi(D_800757B0)
/* CF6C 8001C76C B057108E */  lw         $s0, %lo(D_800757B0)($s0)
/* CF70 8001C770 0009023C */  lui        $v0, (0x9000000 >> 16)
/* CF74 8001C774 000002AE */  sw         $v0, 0x0($s0)
/* CF78 8001C778 2C000224 */  addiu      $v0, $zero, 0x2C
/* CF7C 8001C77C 070002A2 */  sb         $v0, 0x7($s0)
/* CF80 8001C780 4C000224 */  addiu      $v0, $zero, 0x4C
/* CF84 8001C784 040002A2 */  sb         $v0, 0x4($s0)
/* CF88 8001C788 80000224 */  addiu      $v0, $zero, 0x80
/* CF8C 8001C78C 050002A2 */  sb         $v0, 0x5($s0)
/* CF90 8001C790 08000224 */  addiu      $v0, $zero, 0x8
/* CF94 8001C794 080003A6 */  sh         $v1, 0x8($s0)
/* CF98 8001C798 0A0002A6 */  sh         $v0, 0xA($s0)
/* CF9C 8001C79C 08000296 */  lhu        $v0, 0x8($s0)
/* CFA0 8001C7A0 0A000696 */  lhu        $a2, 0xA($s0)
/* CFA4 8001C7A4 08000796 */  lhu        $a3, 0x8($s0)
/* CFA8 8001C7A8 0A000396 */  lhu        $v1, 0xA($s0)
/* CFAC 8001C7AC 80004224 */  addiu      $v0, $v0, 0x80
/* CFB0 8001C7B0 100002A6 */  sh         $v0, 0x10($s0)
/* CFB4 8001C7B4 08000296 */  lhu        $v0, 0x8($s0)
/* CFB8 8001C7B8 DF006324 */  addiu      $v1, $v1, 0xDF
/* CFBC 8001C7BC 1A0003A6 */  sh         $v1, 0x1A($s0)
/* CFC0 8001C7C0 0A000396 */  lhu        $v1, 0xA($s0)
/* CFC4 8001C7C4 01003126 */  addiu      $s1, $s1, 0x1
/* CFC8 8001C7C8 0D0000A2 */  sb         $zero, 0xD($s0)
/* CFCC 8001C7CC 120006A6 */  sh         $a2, 0x12($s0)
/* CFD0 8001C7D0 0D000692 */  lbu        $a2, 0xD($s0)
/* CFD4 8001C7D4 40001224 */  addiu      $s2, $zero, 0x40
/* CFD8 8001C7D8 0C0000A2 */  sb         $zero, 0xC($s0)
/* CFDC 8001C7DC 180007A6 */  sh         $a3, 0x18($s0)
/* CFE0 8001C7E0 0C000792 */  lbu        $a3, 0xC($s0)
/* CFE4 8001C7E4 80004224 */  addiu      $v0, $v0, 0x80
/* CFE8 8001C7E8 200002A6 */  sh         $v0, 0x20($s0)
/* CFEC 8001C7EC 0C000292 */  lbu        $v0, 0xC($s0)
/* CFF0 8001C7F0 DF006324 */  addiu      $v1, $v1, 0xDF
/* CFF4 8001C7F4 220003A6 */  sh         $v1, 0x22($s0)
/* CFF8 8001C7F8 0D000392 */  lbu        $v1, 0xD($s0)
/* CFFC 8001C7FC 21200002 */  addu       $a0, $s0, $zero
/* D000 8001C800 060012A2 */  sb         $s2, 0x6($s0)
/* D004 8001C804 150006A2 */  sb         $a2, 0x15($s0)
/* D008 8001C808 1C0007A2 */  sb         $a3, 0x1C($s0)
/* D00C 8001C80C 80004224 */  addiu      $v0, $v0, 0x80
/* D010 8001C810 140002A2 */  sb         $v0, 0x14($s0)
/* D014 8001C814 0C000292 */  lbu        $v0, 0xC($s0)
/* D018 8001C818 DFFF6324 */  addiu      $v1, $v1, -0x21
/* D01C 8001C81C 1D0003A2 */  sb         $v1, 0x1D($s0)
/* D020 8001C820 0D000392 */  lbu        $v1, 0xD($s0)
/* D024 8001C824 80004224 */  addiu      $v0, $v0, 0x80
/* D028 8001C828 DFFF6324 */  addiu      $v1, $v1, -0x21
/* D02C 8001C82C 240002A2 */  sb         $v0, 0x24($s0)
/* D030 8001C830 20380224 */  addiu      $v0, $zero, 0x3820
/* D034 8001C834 250003A2 */  sb         $v1, 0x25($s0)
/* D038 8001C838 0E0002A6 */  sh         $v0, 0xE($s0)
/* D03C 8001C83C 285A000C */  jal        func_800168A0
/* D040 8001C840 160008A6 */   sh        $t0, 0x16($s0)
/* D044 8001C844 28000426 */  addiu      $a0, $s0, 0x28
/* D048 8001C848 0400222A */  slti       $v0, $s1, 0x4
/* D04C 8001C84C 0780013C */  lui        $at, %hi(D_800757B0)
/* D050 8001C850 B05724AC */  sw         $a0, %lo(D_800757B0)($at)
/* D054 8001C854 C2FF4014 */  bnez       $v0, .L8001C760
/* D058 8001C858 FF030524 */   addiu     $a1, $zero, 0x3FF
/* D05C 8001C85C 0003023C */  lui        $v0, (0x3000000 >> 16)
/* D060 8001C860 E7000324 */  addiu      $v1, $zero, 0xE7
/* D064 8001C864 280002AE */  sw         $v0, 0x28($s0)
/* D068 8001C868 00020224 */  addiu      $v0, $zero, 0x200
/* D06C 8001C86C 2F0012A2 */  sb         $s2, 0x2F($s0)
/* D070 8001C870 300000A6 */  sh         $zero, 0x30($s0)
/* D074 8001C874 320003A6 */  sh         $v1, 0x32($s0)
/* D078 8001C878 340002A6 */  sh         $v0, 0x34($s0)
/* D07C 8001C87C 360003A6 */  sh         $v1, 0x36($s0)
/* D080 8001C880 2C0000A2 */  sb         $zero, 0x2C($s0)
/* D084 8001C884 2D0000A2 */  sb         $zero, 0x2D($s0)
/* D088 8001C888 285A000C */  jal        func_800168A0
/* D08C 8001C88C 2E0000A2 */   sb        $zero, 0x2E($s0)
/* D090 8001C890 38000226 */  addiu      $v0, $s0, 0x38
/* D094 8001C894 0780013C */  lui        $at, %hi(D_800757B0)
/* D098 8001C898 B05722AC */  sw         $v0, %lo(D_800757B0)($at)
/* D09C 8001C89C 54720008 */  j          .L8001C950
/* D0A0 8001C8A0 00000000 */   nop
.L8001C8A4:
/* D0A4 8001C8A4 0880043C */  lui        $a0, %hi(D_80078A40 + 0x10)
/* D0A8 8001C8A8 508A848C */  lw         $a0, %lo(D_80078A40 + 0x10)($a0)
/* D0AC 8001C8AC 0780023C */  lui        $v0, %hi(D_8007568C)
/* D0B0 8001C8B0 8C56428C */  lw         $v0, %lo(D_8007568C)($v0)
/* D0B4 8001C8B4 0780013C */  lui        $at, %hi(D_800757D4)
/* D0B8 8001C8B8 D45720AC */  sw         $zero, %lo(D_800757D4)($at)
/* D0BC 8001C8BC 2330C200 */  subu       $a2, $a2, $v0
/* D0C0 8001C8C0 C0310600 */  sll        $a2, $a2, 7
/* D0C4 8001C8C4 0780013C */  lui        $at, %hi(D_8007575C)
/* D0C8 8001C8C8 5C5726AC */  sw         $a2, %lo(D_8007575C)($at)
/* D0CC 8001C8CC 955F000C */  jal        func_80017E54
/* D0D0 8001C8D0 21280000 */   addu      $a1, $zero, $zero
/* D0D4 8001C8D4 1800A2AF */  sw         $v0, 0x18($sp)
/* D0D8 8001C8D8 0780023C */  lui        $v0, %hi(D_80075888)
/* D0DC 8001C8DC 8858428C */  lw         $v0, %lo(D_80075888)($v0)
/* D0E0 8001C8E0 0780043C */  lui        $a0, %hi(g_DB)
/* D0E4 8001C8E4 E06E8424 */  addiu      $a0, $a0, %lo(g_DB)
/* D0E8 8001C8E8 0C004414 */  bne        $v0, $a0, .L8001C91C
/* D0EC 8001C8EC 00000000 */   nop
/* D0F0 8001C8F0 1800A293 */  lbu        $v0, 0x18($sp)
/* D0F4 8001C8F4 1900A393 */  lbu        $v1, 0x19($sp)
/* D0F8 8001C8F8 1A00A593 */  lbu        $a1, 0x1A($sp)
/* D0FC 8001C8FC 0780013C */  lui        $at, %hi(g_DB + 0x9D)
/* D100 8001C900 7D6F22A0 */  sb         $v0, %lo(g_DB + 0x9D)($at)
/* D104 8001C904 0780013C */  lui        $at, %hi(g_DB + 0x9E)
/* D108 8001C908 7E6F23A0 */  sb         $v1, %lo(g_DB + 0x9E)($at)
/* D10C 8001C90C 0780013C */  lui        $at, %hi(g_DB + 0x9F)
/* D110 8001C910 7F6F25A0 */  sb         $a1, %lo(g_DB + 0x9F)($at)
/* D114 8001C914 50720008 */  j          .L8001C940
/* D118 8001C918 84008424 */   addiu     $a0, $a0, 0x84
.L8001C91C:
/* D11C 8001C91C 1800A293 */  lbu        $v0, 0x18($sp)
/* D120 8001C920 1900A393 */  lbu        $v1, 0x19($sp)
/* D124 8001C924 1A00A593 */  lbu        $a1, 0x1A($sp)
/* D128 8001C928 0780013C */  lui        $at, %hi(g_DB + 0x19)
/* D12C 8001C92C F96E22A0 */  sb         $v0, %lo(g_DB + 0x19)($at)
/* D130 8001C930 0780013C */  lui        $at, %hi(g_DB + 0x1A)
/* D134 8001C934 FA6E23A0 */  sb         $v1, %lo(g_DB + 0x1A)($at)
/* D138 8001C938 0780013C */  lui        $at, %hi(g_DB + 0x1B)
/* D13C 8001C93C FB6E25A0 */  sb         $a1, %lo(g_DB + 0x1B)($at)
.L8001C940:
/* D140 8001C940 767F010C */  jal        PutDrawEnv
/* D144 8001C944 00000000 */   nop
/* D148 8001C948 003C010C */  jal        func_8004F000
/* D14C 8001C94C 00000000 */   nop
.L8001C950:
/* D150 8001C950 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* D154 8001C954 F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* D158 8001C958 21280000 */  addu       $a1, $zero, $zero
/* D15C 8001C95C 455A000C */  jal        Memset
/* D160 8001C960 00090624 */   addiu     $a2, $zero, 0x900
/* D164 8001C964 B18E000C */  jal        func_80023AC4
/* D168 8001C968 00000000 */   nop
/* D16C 8001C96C E159000C */  jal        func_80016784
/* D170 8001C970 00080424 */   addiu     $a0, $zero, 0x800
/* D174 8001C974 597F010C */  jal        DrawOTag
/* D178 8001C978 21204000 */   addu      $a0, $v0, $zero
/* D17C 8001C97C D97D010C */  jal        DrawSync
/* D180 8001C980 21200000 */   addu      $a0, $zero, $zero
/* D184 8001C984 0780023C */  lui        $v0, %hi(D_80075784)
/* D188 8001C988 8457428C */  lw         $v0, %lo(D_80075784)($v0)
/* D18C 8001C98C 00000000 */  nop
/* D190 8001C990 03004010 */  beqz       $v0, .L8001C9A0
/* D194 8001C994 00000000 */   nop
/* D198 8001C998 F176010C */  jal        VSync
/* D19C 8001C99C 21200000 */   addu      $a0, $zero, $zero
.L8001C9A0:
/* D1A0 8001C9A0 F176010C */  jal        VSync
/* D1A4 8001C9A4 FFFF0424 */   addiu     $a0, $zero, -0x1
/* D1A8 8001C9A8 0780033C */  lui        $v1, %hi(D_80075950)
/* D1AC 8001C9AC 5059638C */  lw         $v1, %lo(D_80075950)($v1)
/* D1B0 8001C9B0 0780013C */  lui        $at, %hi(D_80075954)
/* D1B4 8001C9B4 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* D1B8 8001C9B8 23104300 */  subu       $v0, $v0, $v1
/* D1BC 8001C9BC 02004228 */  slti       $v0, $v0, 0x2
/* D1C0 8001C9C0 0E004010 */  beqz       $v0, .L8001C9FC
/* D1C4 8001C9C4 00000000 */   nop
/* D1C8 8001C9C8 0780103C */  lui        $s0, %hi(D_80075954)
/* D1CC 8001C9CC 54591026 */  addiu      $s0, $s0, %lo(D_80075954)
.L8001C9D0:
/* D1D0 8001C9D0 F176010C */  jal        VSync
/* D1D4 8001C9D4 21200000 */   addu      $a0, $zero, $zero
/* D1D8 8001C9D8 F176010C */  jal        VSync
/* D1DC 8001C9DC FFFF0424 */   addiu     $a0, $zero, -0x1
/* D1E0 8001C9E0 FCFF038E */  lw         $v1, -0x4($s0)
/* D1E4 8001C9E4 0780013C */  lui        $at, %hi(D_80075954)
/* D1E8 8001C9E8 545922AC */  sw         $v0, %lo(D_80075954)($at)
/* D1EC 8001C9EC 23104300 */  subu       $v0, $v0, $v1
/* D1F0 8001C9F0 02004228 */  slti       $v0, $v0, 0x2
/* D1F4 8001C9F4 F6FF4014 */  bnez       $v0, .L8001C9D0
/* D1F8 8001C9F8 00000000 */   nop
.L8001C9FC:
/* D1FC 8001C9FC F176010C */  jal        VSync
/* D200 8001CA00 FFFF0424 */   addiu     $a0, $zero, -0x1
/* D204 8001CA04 0780043C */  lui        $a0, %hi(D_80075888)
/* D208 8001CA08 8858848C */  lw         $a0, %lo(D_80075888)($a0)
/* D20C 8001CA0C 0780013C */  lui        $at, %hi(D_80075950)
/* D210 8001CA10 505922AC */  sw         $v0, %lo(D_80075950)($at)
/* D214 8001CA14 0C80010C */  jal        PutDispEnv
/* D218 8001CA18 5C008424 */   addiu     $a0, $a0, 0x5C
/* D21C 8001CA1C 2C00BF8F */  lw         $ra, 0x2C($sp)
/* D220 8001CA20 2800B28F */  lw         $s2, 0x28($sp)
/* D224 8001CA24 2400B18F */  lw         $s1, 0x24($sp)
/* D228 8001CA28 2000B08F */  lw         $s0, 0x20($sp)
/* D22C 8001CA2C 3000BD27 */  addiu      $sp, $sp, 0x30
/* D230 8001CA30 0800E003 */  jr         $ra
/* D234 8001CA34 00000000 */   nop
.size func_8001C694, . - func_8001C694
