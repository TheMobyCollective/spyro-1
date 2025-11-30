.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_32_8008883C
/* 2CBA604 8008883C 98FFBD27 */  addiu      $sp, $sp, -0x68
/* 2CBA608 80088840 4800B0AF */  sw         $s0, 0x48($sp)
/* 2CBA60C 80088844 21808000 */  addu       $s0, $a0, $zero
/* 2CBA610 80088848 5C00B5AF */  sw         $s5, 0x5C($sp)
/* 2CBA614 8008884C 21A8A000 */  addu       $s5, $a1, $zero
/* 2CBA618 80088850 6000BFAF */  sw         $ra, 0x60($sp)
/* 2CBA61C 80088854 5800B4AF */  sw         $s4, 0x58($sp)
/* 2CBA620 80088858 5400B3AF */  sw         $s3, 0x54($sp)
/* 2CBA624 8008885C 5000B2AF */  sw         $s2, 0x50($sp)
/* 2CBA628 80088860 3149010C */  jal        func_800524C4
/* 2CBA62C 80088864 4C00B1AF */   sw        $s1, 0x4C($sp)
/* 2CBA630 80088868 21984000 */  addu       $s3, $v0, $zero
/* 2CBA634 8008886C 1400A012 */  beqz       $s5, .Llevel_32_800888C0
/* 2CBA638 80088870 360070A6 */   sh        $s0, 0x36($s3)
/* 2CBA63C 80088874 0780043C */  lui        $a0, %hi(D_80075828)
/* 2CBA640 80088878 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 2CBA644 8008887C 00000000 */  nop
/* 2CBA648 80088880 2320A402 */  subu       $a0, $s5, $a0
/* 2CBA64C 80088884 40190400 */  sll        $v1, $a0, 5
/* 2CBA650 80088888 23186400 */  subu       $v1, $v1, $a0
/* 2CBA654 8008888C 40190300 */  sll        $v1, $v1, 5
/* 2CBA658 80088890 21186400 */  addu       $v1, $v1, $a0
/* 2CBA65C 80088894 C0100300 */  sll        $v0, $v1, 3
/* 2CBA660 80088898 21186200 */  addu       $v1, $v1, $v0
/* 2CBA664 8008889C C0130300 */  sll        $v0, $v1, 15
/* 2CBA668 800888A0 23104300 */  subu       $v0, $v0, $v1
/* 2CBA66C 800888A4 80100200 */  sll        $v0, $v0, 2
/* 2CBA670 800888A8 21104400 */  addu       $v0, $v0, $a0
/* 2CBA674 800888AC 23100200 */  negu       $v0, $v0
/* 2CBA678 800888B0 C3180200 */  sra        $v1, $v0, 3
/* 2CBA67C 800888B4 0001622C */  sltiu      $v0, $v1, 0x100
/* 2CBA680 800888B8 03004014 */  bnez       $v0, .Llevel_32_800888C8
/* 2CBA684 800888BC 0201022A */   slti      $v0, $s0, 0x102
.Llevel_32_800888C0:
/* 2CBA688 800888C0 21180000 */  addu       $v1, $zero, $zero
/* 2CBA68C 800888C4 0201022A */  slti       $v0, $s0, 0x102
.Llevel_32_800888C8:
/* 2CBA690 800888C8 31004010 */  beqz       $v0, .Llevel_32_80088990
/* 2CBA694 800888CC 560063A2 */   sb        $v1, 0x56($s3)
/* 2CBA698 800888D0 FF00022A */  slti       $v0, $s0, 0xFF
/* 2CBA69C 800888D4 1E014010 */  beqz       $v0, .Llevel_32_80088D50
/* 2CBA6A0 800888D8 4C000224 */   addiu     $v0, $zero, 0x4C
/* 2CBA6A4 800888DC BA020212 */  beq        $s0, $v0, .Llevel_32_800893C8
/* 2CBA6A8 800888E0 4D00022A */   slti      $v0, $s0, 0x4D
/* 2CBA6AC 800888E4 16004010 */  beqz       $v0, .Llevel_32_80088940
/* 2CBA6B0 800888E8 10000224 */   addiu     $v0, $zero, 0x10
/* 2CBA6B4 800888EC 80000212 */  beq        $s0, $v0, .Llevel_32_80088AF0
/* 2CBA6B8 800888F0 1100022A */   slti      $v0, $s0, 0x11
/* 2CBA6BC 800888F4 07004010 */  beqz       $v0, .Llevel_32_80088914
/* 2CBA6C0 800888F8 0E000224 */   addiu     $v0, $zero, 0xE
/* 2CBA6C4 800888FC 9E000212 */  beq        $s0, $v0, .Llevel_32_80088B78
/* 2CBA6C8 80088900 0F000224 */   addiu     $v0, $zero, 0xF
/* 2CBA6CC 80088904 53000212 */  beq        $s0, $v0, .Llevel_32_80088A54
/* 2CBA6D0 80088908 00000000 */   nop
/* 2CBA6D4 8008890C FC240208 */  j          .Llevel_32_800893F0
/* 2CBA6D8 80088910 00000000 */   nop
.Llevel_32_80088914:
/* 2CBA6DC 80088914 22000224 */  addiu      $v0, $zero, 0x22
/* 2CBA6E0 80088918 89000212 */  beq        $s0, $v0, .Llevel_32_80088B40
/* 2CBA6E4 8008891C 2200022A */   slti      $v0, $s0, 0x22
/* 2CBA6E8 80088920 B3024014 */  bnez       $v0, .Llevel_32_800893F0
/* 2CBA6EC 80088924 4600022A */   slti      $v0, $s0, 0x46
/* 2CBA6F0 80088928 B1024010 */  beqz       $v0, .Llevel_32_800893F0
/* 2CBA6F4 8008892C 4300022A */   slti      $v0, $s0, 0x43
/* 2CBA6F8 80088930 07014010 */  beqz       $v0, .Llevel_32_80088D50
/* 2CBA6FC 80088934 00000000 */   nop
/* 2CBA700 80088938 FC240208 */  j          .Llevel_32_800893F0
/* 2CBA704 8008893C 00000000 */   nop
.Llevel_32_80088940:
/* 2CBA708 80088940 97000224 */  addiu      $v0, $zero, 0x97
/* 2CBA70C 80088944 02010212 */  beq        $s0, $v0, .Llevel_32_80088D50
/* 2CBA710 80088948 9800022A */   slti      $v0, $s0, 0x98
/* 2CBA714 8008894C 09004010 */  beqz       $v0, .Llevel_32_80088974
/* 2CBA718 80088950 5300022A */   slti      $v0, $s0, 0x53
/* 2CBA71C 80088954 A6024014 */  bnez       $v0, .Llevel_32_800893F0
/* 2CBA720 80088958 5800022A */   slti      $v0, $s0, 0x58
/* 2CBA724 8008895C 86004014 */  bnez       $v0, .Llevel_32_80088B78
/* 2CBA728 80088960 78000224 */   addiu     $v0, $zero, 0x78
/* 2CBA72C 80088964 DA000212 */  beq        $s0, $v0, .Llevel_32_80088CD0
/* 2CBA730 80088968 00000000 */   nop
/* 2CBA734 8008896C FC240208 */  j          .Llevel_32_800893F0
/* 2CBA738 80088970 00000000 */   nop
.Llevel_32_80088974:
/* 2CBA73C 80088974 9A00022A */  slti       $v0, $s0, 0x9A
/* 2CBA740 80088978 E7004014 */  bnez       $v0, .Llevel_32_80088D18
/* 2CBA744 8008897C FB000224 */   addiu     $v0, $zero, 0xFB
/* 2CBA748 80088980 5E010212 */  beq        $s0, $v0, .Llevel_32_80088EFC
/* 2CBA74C 80088984 00000000 */   nop
/* 2CBA750 80088988 FC240208 */  j          .Llevel_32_800893F0
/* 2CBA754 8008898C 00000000 */   nop
.Llevel_32_80088990:
/* 2CBA758 80088990 3801022A */  slti       $v0, $s0, 0x138
/* 2CBA75C 80088994 14004010 */  beqz       $v0, .Llevel_32_800889E8
/* 2CBA760 80088998 3501022A */   slti      $v0, $s0, 0x135
/* 2CBA764 8008899C EC004010 */  beqz       $v0, .Llevel_32_80088D50
/* 2CBA768 800889A0 15010224 */   addiu     $v0, $zero, 0x115
/* 2CBA76C 800889A4 C5010212 */  beq        $s0, $v0, .Llevel_32_800890BC
/* 2CBA770 800889A8 1601022A */   slti      $v0, $s0, 0x116
/* 2CBA774 800889AC 07004010 */  beqz       $v0, .Llevel_32_800889CC
/* 2CBA778 800889B0 0E01022A */   slti      $v0, $s0, 0x10E
/* 2CBA77C 800889B4 8E024010 */  beqz       $v0, .Llevel_32_800893F0
/* 2CBA780 800889B8 0401022A */   slti      $v0, $s0, 0x104
/* 2CBA784 800889BC BF014010 */  beqz       $v0, .Llevel_32_800890BC
/* 2CBA788 800889C0 00000000 */   nop
/* 2CBA78C 800889C4 FC240208 */  j          .Llevel_32_800893F0
/* 2CBA790 800889C8 00000000 */   nop
.Llevel_32_800889CC:
/* 2CBA794 800889CC 27010224 */  addiu      $v0, $zero, 0x127
/* 2CBA798 800889D0 C7010212 */  beq        $s0, $v0, .Llevel_32_800890F0
/* 2CBA79C 800889D4 30010224 */   addiu     $v0, $zero, 0x130
/* 2CBA7A0 800889D8 1C020212 */  beq        $s0, $v0, .Llevel_32_8008924C
/* 2CBA7A4 800889DC 00000000 */   nop
/* 2CBA7A8 800889E0 FC240208 */  j          .Llevel_32_800893F0
/* 2CBA7AC 800889E4 00000000 */   nop
.Llevel_32_800889E8:
/* 2CBA7B0 800889E8 95010224 */  addiu      $v0, $zero, 0x195
/* 2CBA7B4 800889EC 59020212 */  beq        $s0, $v0, .Llevel_32_80089354
/* 2CBA7B8 800889F0 9601022A */   slti      $v0, $s0, 0x196
/* 2CBA7BC 800889F4 0E004010 */  beqz       $v0, .Llevel_32_80088A30
/* 2CBA7C0 800889F8 47010224 */   addiu     $v0, $zero, 0x147
/* 2CBA7C4 800889FC AF010212 */  beq        $s0, $v0, .Llevel_32_800890BC
/* 2CBA7C8 80088A00 4801022A */   slti      $v0, $s0, 0x148
/* 2CBA7CC 80088A04 05004010 */  beqz       $v0, .Llevel_32_80088A1C
/* 2CBA7D0 80088A08 3E010224 */   addiu     $v0, $zero, 0x13E
/* 2CBA7D4 80088A0C 30020212 */  beq        $s0, $v0, .Llevel_32_800892D0
/* 2CBA7D8 80088A10 00000000 */   nop
/* 2CBA7DC 80088A14 FC240208 */  j          .Llevel_32_800893F0
/* 2CBA7E0 80088A18 00000000 */   nop
.Llevel_32_80088A1C:
/* 2CBA7E4 80088A1C 88010224 */  addiu      $v0, $zero, 0x188
/* 2CBA7E8 80088A20 44020212 */  beq        $s0, $v0, .Llevel_32_80089334
/* 2CBA7EC 80088A24 00000000 */   nop
/* 2CBA7F0 80088A28 FC240208 */  j          .Llevel_32_800893F0
/* 2CBA7F4 80088A2C 00000000 */   nop
.Llevel_32_80088A30:
/* 2CBA7F8 80088A30 AA01022A */  slti       $v0, $s0, 0x1AA
/* 2CBA7FC 80088A34 6E024014 */  bnez       $v0, .Llevel_32_800893F0
/* 2CBA800 80088A38 C401022A */   slti      $v0, $s0, 0x1C4
/* 2CBA804 80088A3C 62024014 */  bnez       $v0, .Llevel_32_800893C8
/* 2CBA808 80088A40 DD010224 */   addiu     $v0, $zero, 0x1DD
/* 2CBA80C 80088A44 43020212 */  beq        $s0, $v0, .Llevel_32_80089354
/* 2CBA810 80088A48 00000000 */   nop
/* 2CBA814 80088A4C FC240208 */  j          .Llevel_32_800893F0
/* 2CBA818 80088A50 00000000 */   nop
.Llevel_32_80088A54:
/* 2CBA81C 80088A54 0000708E */  lw         $s0, 0x0($s3)
/* 2CBA820 80088A58 C8E9000C */  jal        func_8003A720
/* 2CBA824 80088A5C 21206002 */   addu      $a0, $s3, $zero
/* 2CBA828 80088A60 8C000224 */  addiu      $v0, $zero, 0x8C
/* 2CBA82C 80088A64 080002AE */  sw         $v0, 0x8($s0)
/* 2CBA830 80088A68 03000224 */  addiu      $v0, $zero, 0x3
/* 2CBA834 80088A6C 100002A2 */  sb         $v0, 0x10($s0)
/* 2CBA838 80088A70 FF000224 */  addiu      $v0, $zero, 0xFF
/* 2CBA83C 80088A74 140002A2 */  sb         $v0, 0x14($s0)
/* 2CBA840 80088A78 02000224 */  addiu      $v0, $zero, 0x2
/* 2CBA844 80088A7C 000000AE */  sw         $zero, 0x0($s0)
/* 2CBA848 80088A80 040000AE */  sw         $zero, 0x4($s0)
/* 2CBA84C 80088A84 0E0000A2 */  sb         $zero, 0xE($s0)
/* 2CBA850 80088A88 0F0000A2 */  sb         $zero, 0xF($s0)
/* 2CBA854 80088A8C 110000A2 */  sb         $zero, 0x11($s0)
/* 2CBA858 80088A90 120000A2 */  sb         $zero, 0x12($s0)
/* 2CBA85C 80088A94 130000A2 */  sb         $zero, 0x13($s0)
/* 2CBA860 80088A98 490062A2 */  sb         $v0, 0x49($s3)
/* 2CBA864 80088A9C 18000224 */  addiu      $v0, $zero, 0x18
/* 2CBA868 80088AA0 500062A2 */  sb         $v0, 0x50($s3)
/* 2CBA86C 80088AA4 10000224 */  addiu      $v0, $zero, 0x10
/* 2CBA870 80088AA8 520062A2 */  sb         $v0, 0x52($s3)
/* 2CBA874 80088AAC 20000224 */  addiu      $v0, $zero, 0x20
/* 2CBA878 80088AB0 440062A2 */  sb         $v0, 0x44($s3)
/* 2CBA87C 80088AB4 450060A2 */  sb         $zero, 0x45($s3)
/* 2CBA880 80088AB8 0400A012 */  beqz       $s5, .Llevel_32_80088ACC
/* 2CBA884 80088ABC 460060A2 */   sb        $zero, 0x46($s3)
/* 2CBA888 80088AC0 0C006426 */  addiu      $a0, $s3, 0xC
/* 2CBA88C 80088AC4 C05D000C */  jal        VecCopy
/* 2CBA890 80088AC8 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_32_80088ACC:
/* 2CBA894 80088ACC AA49010C */  jal        func_800526A8
/* 2CBA898 80088AD0 21206002 */   addu      $a0, $s3, $zero
/* 2CBA89C 80088AD4 4B006292 */  lbu        $v0, 0x4B($s3)
/* 2CBA8A0 80088AD8 01000324 */  addiu      $v1, $zero, 0x1
/* 2CBA8A4 80088ADC 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 2CBA8A8 80088AE0 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 2CBA8AC 80088AE4 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 2CBA8B0 80088AE8 BC230208 */  j          .Llevel_32_80088EF0
/* 2CBA8B4 80088AEC 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_32_80088AF0:
/* 2CBA8B8 80088AF0 0000718E */  lw         $s1, 0x0($s3)
/* 2CBA8BC 80088AF4 C8E9000C */  jal        func_8003A720
/* 2CBA8C0 80088AF8 21206002 */   addu      $a0, $s3, $zero
/* 2CBA8C4 80088AFC AA49010C */  jal        func_800526A8
/* 2CBA8C8 80088B00 21206002 */   addu      $a0, $s3, $zero
/* 2CBA8CC 80088B04 0C007026 */  addiu      $s0, $s3, 0xC
/* 2CBA8D0 80088B08 21200002 */  addu       $a0, $s0, $zero
/* 2CBA8D4 80088B0C C05D000C */  jal        VecCopy
/* 2CBA8D8 80088B10 0C00A526 */   addiu     $a1, $s5, 0xC
/* 2CBA8DC 80088B14 21280002 */  addu       $a1, $s0, $zero
/* 2CBA8E0 80088B18 1400628E */  lw         $v0, 0x14($s3)
/* 2CBA8E4 80088B1C 04002426 */  addiu      $a0, $s1, 0x4
/* 2CBA8E8 80088B20 00024224 */  addiu      $v0, $v0, 0x200
/* 2CBA8EC 80088B24 C05D000C */  jal        VecCopy
/* 2CBA8F0 80088B28 140062AE */   sw        $v0, 0x14($s3)
/* 2CBA8F4 80088B2C 08070224 */  addiu      $v0, $zero, 0x708
/* 2CBA8F8 80088B30 130020A2 */  sb         $zero, 0x13($s1)
/* 2CBA8FC 80088B34 120020A2 */  sb         $zero, 0x12($s1)
/* 2CBA900 80088B38 0A250208 */  j          .Llevel_32_80089428
/* 2CBA904 80088B3C 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_32_80088B40:
/* 2CBA908 80088B40 C8E9000C */  jal        func_8003A720
/* 2CBA90C 80088B44 21206002 */   addu      $a0, $s3, $zero
/* 2CBA910 80088B48 20000224 */  addiu      $v0, $zero, 0x20
/* 2CBA914 80088B4C 500062A2 */  sb         $v0, 0x50($s3)
/* 2CBA918 80088B50 FF000224 */  addiu      $v0, $zero, 0xFF
/* 2CBA91C 80088B54 0400A012 */  beqz       $s5, .Llevel_32_80088B68
/* 2CBA920 80088B58 520062A2 */   sb        $v0, 0x52($s3)
/* 2CBA924 80088B5C 0C006426 */  addiu      $a0, $s3, 0xC
/* 2CBA928 80088B60 C05D000C */  jal        VecCopy
/* 2CBA92C 80088B64 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_32_80088B68:
/* 2CBA930 80088B68 734A010C */  jal        func_800529CC
/* 2CBA934 80088B6C 21206002 */   addu      $a0, $s3, $zero
/* 2CBA938 80088B70 0B250208 */  j          .Llevel_32_8008942C
/* 2CBA93C 80088B74 21106002 */   addu      $v0, $s3, $zero
.Llevel_32_80088B78:
/* 2CBA940 80088B78 0000718E */  lw         $s1, 0x0($s3)
/* 2CBA944 80088B7C C8E9000C */  jal        func_8003A720
/* 2CBA948 80088B80 21206002 */   addu      $a0, $s3, $zero
/* 2CBA94C 80088B84 8C000224 */  addiu      $v0, $zero, 0x8C
/* 2CBA950 80088B88 000020AE */  sw         $zero, 0x0($s1)
/* 2CBA954 80088B8C 040020AE */  sw         $zero, 0x4($s1)
/* 2CBA958 80088B90 080022AE */  sw         $v0, 0x8($s1)
/* 2CBA95C 80088B94 0E0020A2 */  sb         $zero, 0xE($s1)
/* 2CBA960 80088B98 0F0020A2 */  sb         $zero, 0xF($s1)
/* 2CBA964 80088B9C 110020A2 */  sb         $zero, 0x11($s1)
/* 2CBA968 80088BA0 120020A2 */  sb         $zero, 0x12($s1)
/* 2CBA96C 80088BA4 130020A2 */  sb         $zero, 0x13($s1)
/* 2CBA970 80088BA8 3600A386 */  lh         $v1, 0x36($s5)
/* 2CBA974 80088BAC 0D000224 */  addiu      $v0, $zero, 0xD
/* 2CBA978 80088BB0 02006214 */  bne        $v1, $v0, .Llevel_32_80088BBC
/* 2CBA97C 80088BB4 03000224 */   addiu     $v0, $zero, 0x3
/* 2CBA980 80088BB8 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_32_80088BBC:
/* 2CBA984 80088BBC 100022A2 */  sb         $v0, 0x10($s1)
/* 2CBA988 80088BC0 0C007026 */  addiu      $s0, $s3, 0xC
/* 2CBA98C 80088BC4 21200002 */  addu       $a0, $s0, $zero
/* 2CBA990 80088BC8 0C00A526 */  addiu      $a1, $s5, 0xC
/* 2CBA994 80088BCC FF000224 */  addiu      $v0, $zero, 0xFF
/* 2CBA998 80088BD0 140022A2 */  sb         $v0, 0x14($s1)
/* 2CBA99C 80088BD4 02001124 */  addiu      $s1, $zero, 0x2
/* 2CBA9A0 80088BD8 18000224 */  addiu      $v0, $zero, 0x18
/* 2CBA9A4 80088BDC 500062A2 */  sb         $v0, 0x50($s3)
/* 2CBA9A8 80088BE0 40000224 */  addiu      $v0, $zero, 0x40
/* 2CBA9AC 80088BE4 520062A2 */  sb         $v0, 0x52($s3)
/* 2CBA9B0 80088BE8 20000224 */  addiu      $v0, $zero, 0x20
/* 2CBA9B4 80088BEC 490071A2 */  sb         $s1, 0x49($s3)
/* 2CBA9B8 80088BF0 440062A2 */  sb         $v0, 0x44($s3)
/* 2CBA9BC 80088BF4 450060A2 */  sb         $zero, 0x45($s3)
/* 2CBA9C0 80088BF8 C05D000C */  jal        VecCopy
/* 2CBA9C4 80088BFC 460060A2 */   sb        $zero, 0x46($s3)
/* 2CBA9C8 80088C00 734A010C */  jal        func_800529CC
/* 2CBA9CC 80088C04 21206002 */   addu      $a0, $s3, $zero
/* 2CBA9D0 80088C08 1000A427 */  addiu      $a0, $sp, 0x10
/* 2CBA9D4 80088C0C 21280002 */  addu       $a1, $s0, $zero
/* 2CBA9D8 80088C10 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 2CBA9DC 80088C14 C05D000C */  jal        VecCopy
/* 2CBA9E0 80088C18 1C0062AE */   sw        $v0, 0x1C($s3)
/* 2CBA9E4 80088C1C 1000A427 */  addiu      $a0, $sp, 0x10
/* 2CBA9E8 80088C20 1800A28F */  lw         $v0, 0x18($sp)
/* 2CBA9EC 80088C24 0100053C */  lui        $a1, (0x10000 >> 16)
/* 2CBA9F0 80088C28 00044224 */  addiu      $v0, $v0, 0x400
/* 2CBA9F4 80088C2C 7B35010C */  jal        func_8004D5EC
/* 2CBA9F8 80088C30 1800A2AF */   sw        $v0, 0x18($sp)
/* 2CBA9FC 80088C34 F44C010C */  jal        func_800533D0
/* 2CBAA00 80088C38 21206002 */   addu      $a0, $s3, $zero
/* 2CBAA04 80088C3C 36006386 */  lh         $v1, 0x36($s3)
/* 2CBAA08 80088C40 0E000224 */  addiu      $v0, $zero, 0xE
/* 2CBAA0C 80088C44 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 2CBAA10 80088C48 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 2CBAA14 80088C4C 03006214 */  bne        $v1, $v0, .Llevel_32_80088C5C
/* 2CBAA18 80088C50 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 2CBAA1C 80088C54 0C000224 */  addiu      $v0, $zero, 0xC
/* 2CBAA20 80088C58 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_32_80088C5C:
/* 2CBAA24 80088C5C 36006386 */  lh         $v1, 0x36($s3)
/* 2CBAA28 80088C60 53000224 */  addiu      $v0, $zero, 0x53
/* 2CBAA2C 80088C64 05006214 */  bne        $v1, $v0, .Llevel_32_80088C7C
/* 2CBAA30 80088C68 54000224 */   addiu     $v0, $zero, 0x54
/* 2CBAA34 80088C6C 01000224 */  addiu      $v0, $zero, 0x1
/* 2CBAA38 80088C70 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 2CBAA3C 80088C74 36006386 */  lh         $v1, 0x36($s3)
/* 2CBAA40 80088C78 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_32_80088C7C:
/* 2CBAA44 80088C7C 02006214 */  bne        $v1, $v0, .Llevel_32_80088C88
/* 2CBAA48 80088C80 00000000 */   nop
/* 2CBAA4C 80088C84 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_32_80088C88:
/* 2CBAA50 80088C88 36006386 */  lh         $v1, 0x36($s3)
/* 2CBAA54 80088C8C 55000224 */  addiu      $v0, $zero, 0x55
/* 2CBAA58 80088C90 05006214 */  bne        $v1, $v0, .Llevel_32_80088CA8
/* 2CBAA5C 80088C94 56000224 */   addiu     $v0, $zero, 0x56
/* 2CBAA60 80088C98 03000224 */  addiu      $v0, $zero, 0x3
/* 2CBAA64 80088C9C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 2CBAA68 80088CA0 36006386 */  lh         $v1, 0x36($s3)
/* 2CBAA6C 80088CA4 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_32_80088CA8:
/* 2CBAA70 80088CA8 02006214 */  bne        $v1, $v0, .Llevel_32_80088CB4
/* 2CBAA74 80088CAC 04000224 */   addiu     $v0, $zero, 0x4
/* 2CBAA78 80088CB0 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_32_80088CB4:
/* 2CBAA7C 80088CB4 36006386 */  lh         $v1, 0x36($s3)
/* 2CBAA80 80088CB8 57000224 */  addiu      $v0, $zero, 0x57
/* 2CBAA84 80088CBC DB016214 */  bne        $v1, $v0, .Llevel_32_8008942C
/* 2CBAA88 80088CC0 21106002 */   addu      $v0, $s3, $zero
/* 2CBAA8C 80088CC4 05000224 */  addiu      $v0, $zero, 0x5
/* 2CBAA90 80088CC8 0A250208 */  j          .Llevel_32_80089428
/* 2CBAA94 80088CCC 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_32_80088CD0:
/* 2CBAA98 80088CD0 0000708E */  lw         $s0, 0x0($s3)
/* 2CBAA9C 80088CD4 C8E9000C */  jal        func_8003A720
/* 2CBAAA0 80088CD8 21206002 */   addu      $a0, $s3, $zero
/* 2CBAAA4 80088CDC AA49010C */  jal        func_800526A8
/* 2CBAAA8 80088CE0 21206002 */   addu      $a0, $s3, $zero
/* 2CBAAAC 80088CE4 490060A2 */  sb         $zero, 0x49($s3)
/* 2CBAAB0 80088CE8 000000AE */  sw         $zero, 0x0($s0)
/* 2CBAAB4 80088CEC 080000A6 */  sh         $zero, 0x8($s0)
/* 2CBAAB8 80088CF0 060000A6 */  sh         $zero, 0x6($s0)
/* 2CBAABC 80088CF4 040000A6 */  sh         $zero, 0x4($s0)
/* 2CBAAC0 80088CF8 0C0000AE */  sw         $zero, 0xC($s0)
/* 2CBAAC4 80088CFC CA01A012 */  beqz       $s5, .Llevel_32_80089428
/* 2CBAAC8 80088D00 100000AE */   sw        $zero, 0x10($s0)
/* 2CBAACC 80088D04 0C006426 */  addiu      $a0, $s3, 0xC
/* 2CBAAD0 80088D08 C05D000C */  jal        VecCopy
/* 2CBAAD4 80088D0C 0C00A526 */   addiu     $a1, $s5, 0xC
/* 2CBAAD8 80088D10 0B250208 */  j          .Llevel_32_8008942C
/* 2CBAADC 80088D14 21106002 */   addu      $v0, $s3, $zero
.Llevel_32_80088D18:
/* 2CBAAE0 80088D18 C8E9000C */  jal        func_8003A720
/* 2CBAAE4 80088D1C 21206002 */   addu      $a0, $s3, $zero
/* 2CBAAE8 80088D20 21206002 */  addu       $a0, $s3, $zero
/* 2CBAAEC 80088D24 20000224 */  addiu      $v0, $zero, 0x20
/* 2CBAAF0 80088D28 500062A2 */  sb         $v0, 0x50($s3)
/* 2CBAAF4 80088D2C FF000224 */  addiu      $v0, $zero, 0xFF
/* 2CBAAF8 80088D30 734A010C */  jal        func_800529CC
/* 2CBAAFC 80088D34 520062A2 */   sb        $v0, 0x52($s3)
/* 2CBAB00 80088D38 0D000224 */  addiu      $v0, $zero, 0xD
/* 2CBAB04 80088D3C 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 2CBAB08 80088D40 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 2CBAB0C 80088D44 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 2CBAB10 80088D48 0A250208 */  j          .Llevel_32_80089428
/* 2CBAB14 80088D4C 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_32_80088D50:
/* 2CBAB18 80088D50 0000748E */  lw         $s4, 0x0($s3)
/* 2CBAB1C 80088D54 C8E9000C */  jal        func_8003A720
/* 2CBAB20 80088D58 21206002 */   addu      $a0, $s3, $zero
/* 2CBAB24 80088D5C 0C006426 */  addiu      $a0, $s3, 0xC
/* 2CBAB28 80088D60 0C00A526 */  addiu      $a1, $s5, 0xC
/* 2CBAB2C 80088D64 20000224 */  addiu      $v0, $zero, 0x20
/* 2CBAB30 80088D68 C05D000C */  jal        VecCopy
/* 2CBAB34 80088D6C 500062A2 */   sb        $v0, 0x50($s3)
/* 2CBAB38 80088D70 AA49010C */  jal        func_800526A8
/* 2CBAB3C 80088D74 21206002 */   addu      $a0, $s3, $zero
/* 2CBAB40 80088D78 CB89010C */  jal        rand
/* 2CBAB44 80088D7C 00000000 */   nop
/* 2CBAB48 80088D80 CB89010C */  jal        rand
/* 2CBAB4C 80088D84 FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 2CBAB50 80088D88 FF075130 */  andi       $s1, $v0, 0x7FF
/* 2CBAB54 80088D8C 2C5B000C */  jal        Cos
/* 2CBAB58 80088D90 21202002 */   addu      $a0, $s1, $zero
/* 2CBAB5C 80088D94 21204002 */  addu       $a0, $s2, $zero
/* 2CBAB60 80088D98 2C5B000C */  jal        Cos
/* 2CBAB64 80088D9C 21804000 */   addu      $s0, $v0, $zero
/* 2CBAB68 80088DA0 43811000 */  sra        $s0, $s0, 5
/* 2CBAB6C 80088DA4 18000202 */  mult       $s0, $v0
/* 2CBAB70 80088DA8 21202002 */  addu       $a0, $s1, $zero
/* 2CBAB74 80088DAC 12380000 */  mflo       $a3
/* 2CBAB78 80088DB0 03130700 */  sra        $v0, $a3, 12
/* 2CBAB7C 80088DB4 2C5B000C */  jal        Cos
/* 2CBAB80 80088DB8 000082A6 */   sh        $v0, 0x0($s4)
/* 2CBAB84 80088DBC 21204002 */  addu       $a0, $s2, $zero
/* 2CBAB88 80088DC0 165B000C */  jal        Sin
/* 2CBAB8C 80088DC4 21804000 */   addu      $s0, $v0, $zero
/* 2CBAB90 80088DC8 43811000 */  sra        $s0, $s0, 5
/* 2CBAB94 80088DCC 18000202 */  mult       $s0, $v0
/* 2CBAB98 80088DD0 21202002 */  addu       $a0, $s1, $zero
/* 2CBAB9C 80088DD4 12380000 */  mflo       $a3
/* 2CBABA0 80088DD8 03130700 */  sra        $v0, $a3, 12
/* 2CBABA4 80088DDC 165B000C */  jal        Sin
/* 2CBABA8 80088DE0 020082A6 */   sh        $v0, 0x2($s4)
/* 2CBABAC 80088DE4 43110200 */  sra        $v0, $v0, 5
/* 2CBABB0 80088DE8 040082A6 */  sh         $v0, 0x4($s4)
/* 2CBABB4 80088DEC 1800A28E */  lw         $v0, 0x18($s5)
/* 2CBABB8 80088DF0 0200033C */  lui        $v1, (0x20000 >> 16)
/* 2CBABBC 80088DF4 24104300 */  and        $v0, $v0, $v1
/* 2CBABC0 80088DF8 13004010 */  beqz       $v0, .Llevel_32_80088E48
/* 2CBABC4 80088DFC 00000000 */   nop
/* 2CBABC8 80088E00 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 2CBABCC 80088E04 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 2CBABD0 80088E08 00008396 */  lhu        $v1, 0x0($s4)
/* 2CBABD4 80088E0C 83110200 */  sra        $v0, $v0, 6
/* 2CBABD8 80088E10 21186200 */  addu       $v1, $v1, $v0
/* 2CBABDC 80088E14 000083A6 */  sh         $v1, 0x0($s4)
/* 2CBABE0 80088E18 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 2CBABE4 80088E1C 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 2CBABE8 80088E20 02008396 */  lhu        $v1, 0x2($s4)
/* 2CBABEC 80088E24 83110200 */  sra        $v0, $v0, 6
/* 2CBABF0 80088E28 21186200 */  addu       $v1, $v1, $v0
/* 2CBABF4 80088E2C 020083A6 */  sh         $v1, 0x2($s4)
/* 2CBABF8 80088E30 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 2CBABFC 80088E34 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 2CBAC00 80088E38 04008396 */  lhu        $v1, 0x4($s4)
/* 2CBAC04 80088E3C 83110200 */  sra        $v0, $v0, 6
/* 2CBAC08 80088E40 21186200 */  addu       $v1, $v1, $v0
/* 2CBAC0C 80088E44 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_32_80088E48:
/* 2CBAC10 80088E48 00008286 */  lh         $v0, 0x0($s4)
/* 2CBAC14 80088E4C 0C00638E */  lw         $v1, 0xC($s3)
/* 2CBAC18 80088E50 80100200 */  sll        $v0, $v0, 2
/* 2CBAC1C 80088E54 21186200 */  addu       $v1, $v1, $v0
/* 2CBAC20 80088E58 0C0063AE */  sw         $v1, 0xC($s3)
/* 2CBAC24 80088E5C 02008286 */  lh         $v0, 0x2($s4)
/* 2CBAC28 80088E60 1000638E */  lw         $v1, 0x10($s3)
/* 2CBAC2C 80088E64 80100200 */  sll        $v0, $v0, 2
/* 2CBAC30 80088E68 21186200 */  addu       $v1, $v1, $v0
/* 2CBAC34 80088E6C 100063AE */  sw         $v1, 0x10($s3)
/* 2CBAC38 80088E70 04008286 */  lh         $v0, 0x4($s4)
/* 2CBAC3C 80088E74 1400638E */  lw         $v1, 0x14($s3)
/* 2CBAC40 80088E78 80100200 */  sll        $v0, $v0, 2
/* 2CBAC44 80088E7C 21186200 */  addu       $v1, $v1, $v0
/* 2CBAC48 80088E80 CB89010C */  jal        rand
/* 2CBAC4C 80088E84 140063AE */   sw        $v1, 0x14($s3)
/* 2CBAC50 80088E88 0F004230 */  andi       $v0, $v0, 0xF
/* 2CBAC54 80088E8C CB89010C */  jal        rand
/* 2CBAC58 80088E90 060082A6 */   sh        $v0, 0x6($s4)
/* 2CBAC5C 80088E94 0F004230 */  andi       $v0, $v0, 0xF
/* 2CBAC60 80088E98 CB89010C */  jal        rand
/* 2CBAC64 80088E9C 080082A6 */   sh        $v0, 0x8($s4)
/* 2CBAC68 80088EA0 0F004230 */  andi       $v0, $v0, 0xF
/* 2CBAC6C 80088EA4 0A0082A6 */  sh         $v0, 0xA($s4)
/* 2CBAC70 80088EA8 1400A28E */  lw         $v0, 0x14($s5)
/* 2CBAC74 80088EAC 00000000 */  nop
/* 2CBAC78 80088EB0 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 2CBAC7C 80088EB4 CB89010C */  jal        rand
/* 2CBAC80 80088EB8 100082AE */   sw        $v0, 0x10($s4)
/* 2CBAC84 80088EBC 0F004230 */  andi       $v0, $v0, 0xF
/* 2CBAC88 80088EC0 40000324 */  addiu      $v1, $zero, 0x40
/* 2CBAC8C 80088EC4 23186200 */  subu       $v1, $v1, $v0
/* 2CBAC90 80088EC8 0C0083AE */  sw         $v1, 0xC($s4)
/* 2CBAC94 80088ECC 36006296 */  lhu        $v0, 0x36($s3)
/* 2CBAC98 80088ED0 00000000 */  nop
/* 2CBAC9C 80088ED4 CBFE4224 */  addiu      $v0, $v0, -0x135
/* 2CBACA0 80088ED8 0300422C */  sltiu      $v0, $v0, 0x3
/* 2CBACA4 80088EDC 52014010 */  beqz       $v0, .Llevel_32_80089428
/* 2CBACA8 80088EE0 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 2CBACAC 80088EE4 4B006292 */  lbu        $v0, 0x4B($s3)
/* 2CBACB0 80088EE8 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 2CBACB4 80088EEC 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_32_80088EF0:
/* 2CBACB8 80088EF0 80004234 */  ori        $v0, $v0, 0x80
/* 2CBACBC 80088EF4 0A250208 */  j          .Llevel_32_80089428
/* 2CBACC0 80088EF8 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_32_80088EFC:
/* 2CBACC4 80088EFC 0000718E */  lw         $s1, 0x0($s3)
/* 2CBACC8 80088F00 C8E9000C */  jal        func_8003A720
/* 2CBACCC 80088F04 21206002 */   addu      $a0, $s3, $zero
/* 2CBACD0 80088F08 21206002 */  addu       $a0, $s3, $zero
/* 2CBACD4 80088F0C 20000224 */  addiu      $v0, $zero, 0x20
/* 2CBACD8 80088F10 500062A2 */  sb         $v0, 0x50($s3)
/* 2CBACDC 80088F14 FF000224 */  addiu      $v0, $zero, 0xFF
/* 2CBACE0 80088F18 734A010C */  jal        func_800529CC
/* 2CBACE4 80088F1C 520062A2 */   sb        $v0, 0x52($s3)
/* 2CBACE8 80088F20 0E000224 */  addiu      $v0, $zero, 0xE
/* 2CBACEC 80088F24 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 2CBACF0 80088F28 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 2CBACF4 80088F2C 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 2CBACF8 80088F30 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 2CBACFC 80088F34 0780033C */  lui        $v1, %hi(D_80077030 + 0x28)
/* 2CBAD00 80088F38 5870638C */  lw         $v1, %lo(D_80077030 + 0x28)($v1)
/* 2CBAD04 80088F3C 03000224 */  addiu      $v0, $zero, 0x3
/* 2CBAD08 80088F40 03006214 */  bne        $v1, $v0, .Llevel_32_80088F50
/* 2CBAD0C 80088F44 01000224 */   addiu     $v0, $zero, 0x1
/* 2CBAD10 80088F48 D6230208 */  j          .Llevel_32_80088F58
/* 2CBAD14 80088F4C 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_32_80088F50:
/* 2CBAD18 80088F50 02006214 */  bne        $v1, $v0, .Llevel_32_80088F5C
/* 2CBAD1C 80088F54 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_32_80088F58:
/* 2CBAD20 80088F58 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_32_80088F5C:
/* 2CBAD24 80088F5C CB89010C */  jal        rand
/* 2CBAD28 80088F60 00000000 */   nop
/* 2CBAD2C 80088F64 2000A426 */  addiu      $a0, $s5, 0x20
/* 2CBAD30 80088F68 07004230 */  andi       $v0, $v0, 0x7
/* 2CBAD34 80088F6C 80100200 */  sll        $v0, $v0, 2
/* 2CBAD38 80088F70 2000B027 */  addiu      $s0, $sp, 0x20
/* 2CBAD3C 80088F74 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 2CBAD40 80088F78 21082200 */  addu       $at, $at, $v0
/* 2CBAD44 80088F7C A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 2CBAD48 80088F80 21280002 */  addu       $a1, $s0, $zero
/* 2CBAD4C 80088F84 2400A0AF */  sw         $zero, 0x24($sp)
/* 2CBAD50 80088F88 2000A3AF */  sw         $v1, 0x20($sp)
/* 2CBAD54 80088F8C 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 2CBAD58 80088F90 21082200 */  addu       $at, $at, $v0
/* 2CBAD5C 80088F94 A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 2CBAD60 80088F98 21300002 */  addu       $a2, $s0, $zero
/* 2CBAD64 80088F9C 125C000C */  jal        VecRotateByMatrix
/* 2CBAD68 80088FA0 2800A2AF */   sw        $v0, 0x28($sp)
/* 2CBAD6C 80088FA4 CB89010C */  jal        rand
/* 2CBAD70 80088FA8 00000000 */   nop
/* 2CBAD74 80088FAC 2000A38F */  lw         $v1, 0x20($sp)
/* 2CBAD78 80088FB0 7F004230 */  andi       $v0, $v0, 0x7F
/* 2CBAD7C 80088FB4 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 2CBAD80 80088FB8 21186200 */  addu       $v1, $v1, $v0
/* 2CBAD84 80088FBC CB89010C */  jal        rand
/* 2CBAD88 80088FC0 2000A3AF */   sw        $v1, 0x20($sp)
/* 2CBAD8C 80088FC4 2400A38F */  lw         $v1, 0x24($sp)
/* 2CBAD90 80088FC8 7F004230 */  andi       $v0, $v0, 0x7F
/* 2CBAD94 80088FCC C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 2CBAD98 80088FD0 21186200 */  addu       $v1, $v1, $v0
/* 2CBAD9C 80088FD4 CB89010C */  jal        rand
/* 2CBADA0 80088FD8 2400A3AF */   sw        $v1, 0x24($sp)
/* 2CBADA4 80088FDC 0C006426 */  addiu      $a0, $s3, 0xC
/* 2CBADA8 80088FE0 0C00A526 */  addiu      $a1, $s5, 0xC
/* 2CBADAC 80088FE4 21300002 */  addu       $a2, $s0, $zero
/* 2CBADB0 80088FE8 2800A38F */  lw         $v1, 0x28($sp)
/* 2CBADB4 80088FEC 7F004230 */  andi       $v0, $v0, 0x7F
/* 2CBADB8 80088FF0 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 2CBADBC 80088FF4 21186200 */  addu       $v1, $v1, $v0
/* 2CBADC0 80088FF8 D65D000C */  jal        VecAdd
/* 2CBADC4 80088FFC 2800A3AF */   sw        $v1, 0x28($sp)
/* 2CBADC8 80089000 21202002 */  addu       $a0, $s1, $zero
/* 2CBADCC 80089004 C05D000C */  jal        VecCopy
/* 2CBADD0 80089008 21280002 */   addu      $a1, $s0, $zero
/* 2CBADD4 8008900C 21202002 */  addu       $a0, $s1, $zero
/* 2CBADD8 80089010 B25D000C */  jal        VecShiftRight
/* 2CBADDC 80089014 02000524 */   addiu     $a1, $zero, 0x2
/* 2CBADE0 80089018 CB89010C */  jal        rand
/* 2CBADE4 8008901C 00000000 */   nop
/* 2CBADE8 80089020 0000238E */  lw         $v1, 0x0($s1)
/* 2CBADEC 80089024 FF004230 */  andi       $v0, $v0, 0xFF
/* 2CBADF0 80089028 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 2CBADF4 8008902C 21186200 */  addu       $v1, $v1, $v0
/* 2CBADF8 80089030 CB89010C */  jal        rand
/* 2CBADFC 80089034 000023AE */   sw        $v1, 0x0($s1)
/* 2CBAE00 80089038 0400238E */  lw         $v1, 0x4($s1)
/* 2CBAE04 8008903C FF004230 */  andi       $v0, $v0, 0xFF
/* 2CBAE08 80089040 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 2CBAE0C 80089044 21186200 */  addu       $v1, $v1, $v0
/* 2CBAE10 80089048 CB89010C */  jal        rand
/* 2CBAE14 8008904C 040023AE */   sw        $v1, 0x4($s1)
/* 2CBAE18 80089050 0800238E */  lw         $v1, 0x8($s1)
/* 2CBAE1C 80089054 FF004230 */  andi       $v0, $v0, 0xFF
/* 2CBAE20 80089058 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 2CBAE24 8008905C 21186200 */  addu       $v1, $v1, $v0
/* 2CBAE28 80089060 CB89010C */  jal        rand
/* 2CBAE2C 80089064 080023AE */   sw        $v1, 0x8($s1)
/* 2CBAE30 80089068 CB89010C */  jal        rand
/* 2CBAE34 8008906C 440062A2 */   sb        $v0, 0x44($s3)
/* 2CBAE38 80089070 CB89010C */  jal        rand
/* 2CBAE3C 80089074 450062A2 */   sb        $v0, 0x45($s3)
/* 2CBAE40 80089078 CB89010C */  jal        rand
/* 2CBAE44 8008907C 460062A2 */   sb        $v0, 0x46($s3)
/* 2CBAE48 80089080 0F004230 */  andi       $v0, $v0, 0xF
/* 2CBAE4C 80089084 CB89010C */  jal        rand
/* 2CBAE50 80089088 100022A2 */   sb        $v0, 0x10($s1)
/* 2CBAE54 8008908C 0F004230 */  andi       $v0, $v0, 0xF
/* 2CBAE58 80089090 CB89010C */  jal        rand
/* 2CBAE5C 80089094 110022A2 */   sb        $v0, 0x11($s1)
/* 2CBAE60 80089098 0F004230 */  andi       $v0, $v0, 0xF
/* 2CBAE64 8008909C 120022A2 */  sb         $v0, 0x12($s1)
/* 2CBAE68 800890A0 1400A28E */  lw         $v0, 0x14($s5)
/* 2CBAE6C 800890A4 CB89010C */  jal        rand
/* 2CBAE70 800890A8 0C0022AE */   sw        $v0, 0xC($s1)
/* 2CBAE74 800890AC 03004230 */  andi       $v0, $v0, 0x3
/* 2CBAE78 800890B0 10004224 */  addiu      $v0, $v0, 0x10
/* 2CBAE7C 800890B4 0A250208 */  j          .Llevel_32_80089428
/* 2CBAE80 800890B8 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_32_800890BC:
/* 2CBAE84 800890BC 0000708E */  lw         $s0, 0x0($s3)
/* 2CBAE88 800890C0 C8E9000C */  jal        func_8003A720
/* 2CBAE8C 800890C4 21206002 */   addu      $a0, $s3, $zero
/* 2CBAE90 800890C8 734A010C */  jal        func_800529CC
/* 2CBAE94 800890CC 21206002 */   addu      $a0, $s3, $zero
/* 2CBAE98 800890D0 02000224 */  addiu      $v0, $zero, 0x2
/* 2CBAE9C 800890D4 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 2CBAEA0 800890D8 40000224 */  addiu      $v0, $zero, 0x40
/* 2CBAEA4 800890DC 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 2CBAEA8 800890E0 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 2CBAEAC 800890E4 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 2CBAEB0 800890E8 0A250208 */  j          .Llevel_32_80089428
/* 2CBAEB4 800890EC 000002AE */   sw        $v0, 0x0($s0)
.Llevel_32_800890F0:
/* 2CBAEB8 800890F0 0000718E */  lw         $s1, 0x0($s3)
/* 2CBAEBC 800890F4 C8E9000C */  jal        func_8003A720
/* 2CBAEC0 800890F8 21206002 */   addu      $a0, $s3, $zero
/* 2CBAEC4 800890FC 21300000 */  addu       $a2, $zero, $zero
/* 2CBAEC8 80089100 4600A292 */  lbu        $v0, 0x46($s5)
/* 2CBAECC 80089104 0880103C */  lui        $s0, %hi(g_Spyro)
/* 2CBAED0 80089108 588A1026 */  addiu      $s0, $s0, %lo(g_Spyro)
/* 2CBAED4 8008910C 40100200 */  sll        $v0, $v0, 1
/* 2CBAED8 80089110 0780013C */  lui        $at, %hi(D_8006CC78)
/* 2CBAEDC 80089114 21082200 */  addu       $at, $at, $v0
/* 2CBAEE0 80089118 78CC2294 */  lhu        $v0, %lo(D_8006CC78)($at)
/* 2CBAEE4 8008911C 0C00A38E */  lw         $v1, 0xC($s5)
/* 2CBAEE8 80089120 00140200 */  sll        $v0, $v0, 16
/* 2CBAEEC 80089124 43140200 */  sra        $v0, $v0, 17
/* 2CBAEF0 80089128 21186200 */  addu       $v1, $v1, $v0
/* 2CBAEF4 8008912C 0C0063AE */  sw         $v1, 0xC($s3)
/* 2CBAEF8 80089130 4600A292 */  lbu        $v0, 0x46($s5)
/* 2CBAEFC 80089134 1000A38E */  lw         $v1, 0x10($s5)
/* 2CBAF00 80089138 40100200 */  sll        $v0, $v0, 1
/* 2CBAF04 8008913C 0780013C */  lui        $at, %hi(D_8006CBF8)
/* 2CBAF08 80089140 21082200 */  addu       $at, $at, $v0
/* 2CBAF0C 80089144 F8CB2294 */  lhu        $v0, %lo(D_8006CBF8)($at)
/* 2CBAF10 80089148 0C00648E */  lw         $a0, 0xC($s3)
/* 2CBAF14 8008914C 00140200 */  sll        $v0, $v0, 16
/* 2CBAF18 80089150 43140200 */  sra        $v0, $v0, 17
/* 2CBAF1C 80089154 21186200 */  addu       $v1, $v1, $v0
/* 2CBAF20 80089158 100063AE */  sw         $v1, 0x10($s3)
/* 2CBAF24 8008915C 1400A28E */  lw         $v0, 0x14($s5)
/* 2CBAF28 80089160 1000658E */  lw         $a1, 0x10($s3)
/* 2CBAF2C 80089164 00034224 */  addiu      $v0, $v0, 0x300
/* 2CBAF30 80089168 140062AE */  sw         $v0, 0x14($s3)
/* 2CBAF34 8008916C 0000038E */  lw         $v1, 0x0($s0)
/* 2CBAF38 80089170 0880023C */  lui        $v0, %hi(g_Spyro + 0x4)
/* 2CBAF3C 80089174 5C8A428C */  lw         $v0, %lo(g_Spyro + 0x4)($v0)
/* 2CBAF40 80089178 23206400 */  subu       $a0, $v1, $a0
/* 2CBAF44 8008917C AD5A000C */  jal        Atan2
/* 2CBAF48 80089180 23284500 */   subu      $a1, $v0, $a1
/* 2CBAF4C 80089184 4600A692 */  lbu        $a2, 0x46($s5)
/* 2CBAF50 80089188 00000000 */  nop
/* 2CBAF54 8008918C 23104600 */  subu       $v0, $v0, $a2
/* 2CBAF58 80089190 FF004330 */  andi       $v1, $v0, 0xFF
/* 2CBAF5C 80089194 81006228 */  slti       $v0, $v1, 0x81
/* 2CBAF60 80089198 03004014 */  bnez       $v0, .Llevel_32_800891A8
/* 2CBAF64 8008919C E0FF6228 */   slti      $v0, $v1, -0x20
/* 2CBAF68 800891A0 00FF6324 */  addiu      $v1, $v1, -0x100
/* 2CBAF6C 800891A4 E0FF6228 */  slti       $v0, $v1, -0x20
.Llevel_32_800891A8:
/* 2CBAF70 800891A8 03004010 */  beqz       $v0, .Llevel_32_800891B8
/* 2CBAF74 800891AC 21006228 */   slti      $v0, $v1, 0x21
/* 2CBAF78 800891B0 E0FF0324 */  addiu      $v1, $zero, -0x20
/* 2CBAF7C 800891B4 21006228 */  slti       $v0, $v1, 0x21
.Llevel_32_800891B8:
/* 2CBAF80 800891B8 02004014 */  bnez       $v0, .Llevel_32_800891C4
/* 2CBAF84 800891BC 0C006426 */   addiu     $a0, $s3, 0xC
/* 2CBAF88 800891C0 20000324 */  addiu      $v1, $zero, 0x20
.Llevel_32_800891C4:
/* 2CBAF8C 800891C4 21280002 */  addu       $a1, $s0, $zero
/* 2CBAF90 800891C8 2110C300 */  addu       $v0, $a2, $v1
/* 2CBAF94 800891CC 645E000C */  jal        OctDistance
/* 2CBAF98 800891D0 460062A2 */   sb        $v0, 0x46($s3)
/* 2CBAF9C 800891D4 21204000 */  addu       $a0, $v0, $zero
/* 2CBAFA0 800891D8 21300000 */  addu       $a2, $zero, $zero
/* 2CBAFA4 800891DC 1400658E */  lw         $a1, 0x14($s3)
/* 2CBAFA8 800891E0 0880023C */  lui        $v0, %hi(g_Spyro + 0xA0)
/* 2CBAFAC 800891E4 F88A428C */  lw         $v0, %lo(g_Spyro + 0xA0)($v0)
/* 2CBAFB0 800891E8 9CFEA524 */  addiu      $a1, $a1, -0x164
/* 2CBAFB4 800891EC AD5A000C */  jal        Atan2
/* 2CBAFB8 800891F0 23284500 */   subu      $a1, $v0, $a1
/* 2CBAFBC 800891F4 4500A592 */  lbu        $a1, 0x45($s5)
/* 2CBAFC0 800891F8 00000000 */  nop
/* 2CBAFC4 800891FC 23104500 */  subu       $v0, $v0, $a1
/* 2CBAFC8 80089200 FF004330 */  andi       $v1, $v0, 0xFF
/* 2CBAFCC 80089204 81006228 */  slti       $v0, $v1, 0x81
/* 2CBAFD0 80089208 03004014 */  bnez       $v0, .Llevel_32_80089218
/* 2CBAFD4 8008920C D0FF6228 */   slti      $v0, $v1, -0x30
/* 2CBAFD8 80089210 00FF6324 */  addiu      $v1, $v1, -0x100
/* 2CBAFDC 80089214 D0FF6228 */  slti       $v0, $v1, -0x30
.Llevel_32_80089218:
/* 2CBAFE0 80089218 03004010 */  beqz       $v0, .Llevel_32_80089228
/* 2CBAFE4 8008921C 31006228 */   slti      $v0, $v1, 0x31
/* 2CBAFE8 80089220 D0FF0324 */  addiu      $v1, $zero, -0x30
/* 2CBAFEC 80089224 31006228 */  slti       $v0, $v1, 0x31
.Llevel_32_80089228:
/* 2CBAFF0 80089228 02004014 */  bnez       $v0, .Llevel_32_80089234
/* 2CBAFF4 8008922C 21206002 */   addu      $a0, $s3, $zero
/* 2CBAFF8 80089230 30000324 */  addiu      $v1, $zero, 0x30
.Llevel_32_80089234:
/* 2CBAFFC 80089234 2110A300 */  addu       $v0, $a1, $v1
/* 2CBB000 80089238 450062A2 */  sb         $v0, 0x45($s3)
/* 2CBB004 8008923C 5A000224 */  addiu      $v0, $zero, 0x5A
/* 2CBB008 80089240 040022AE */  sw         $v0, 0x4($s1)
/* 2CBB00C 80089244 08250208 */  j          .Llevel_32_80089420
/* 2CBB010 80089248 000020AE */   sw        $zero, 0x0($s1)
.Llevel_32_8008924C:
/* 2CBB014 8008924C 0000708E */  lw         $s0, 0x0($s3)
/* 2CBB018 80089250 0000B18E */  lw         $s1, 0x0($s5)
/* 2CBB01C 80089254 C8E9000C */  jal        func_8003A720
/* 2CBB020 80089258 21206002 */   addu      $a0, $s3, $zero
/* 2CBB024 8008925C 0C007226 */  addiu      $s2, $s3, 0xC
/* 2CBB028 80089260 21204002 */  addu       $a0, $s2, $zero
/* 2CBB02C 80089264 C05D000C */  jal        VecCopy
/* 2CBB030 80089268 0C00A526 */   addiu     $a1, $s5, 0xC
/* 2CBB034 8008926C 040015AE */  sw         $s5, 0x4($s0)
/* 2CBB038 80089270 0000228E */  lw         $v0, 0x0($s1)
/* 2CBB03C 80089274 08000426 */  addiu      $a0, $s0, 0x8
/* 2CBB040 80089278 BC5D000C */  jal        VecNull
/* 2CBB044 8008927C 000002AE */   sw        $v0, 0x0($s0)
/* 2CBB048 80089280 21206002 */  addu       $a0, $s3, $zero
/* 2CBB04C 80089284 20000224 */  addiu      $v0, $zero, 0x20
/* 2CBB050 80089288 AA49010C */  jal        func_800526A8
/* 2CBB054 8008928C 500062A2 */   sb        $v0, 0x50($s3)
/* 2CBB058 80089290 3000B027 */  addiu      $s0, $sp, 0x30
/* 2CBB05C 80089294 21200002 */  addu       $a0, $s0, $zero
/* 2CBB060 80089298 21284002 */  addu       $a1, $s2, $zero
/* 2CBB064 8008929C FFFF0224 */  addiu      $v0, $zero, -0x1
/* 2CBB068 800892A0 C05D000C */  jal        VecCopy
/* 2CBB06C 800892A4 1C0062AE */   sw        $v0, 0x1C($s3)
/* 2CBB070 800892A8 21200002 */  addu       $a0, $s0, $zero
/* 2CBB074 800892AC 3800A28F */  lw         $v0, 0x38($sp)
/* 2CBB078 800892B0 0100053C */  lui        $a1, (0x10000 >> 16)
/* 2CBB07C 800892B4 00044224 */  addiu      $v0, $v0, 0x400
/* 2CBB080 800892B8 7B35010C */  jal        func_8004D5EC
/* 2CBB084 800892BC 3800A2AF */   sw        $v0, 0x38($sp)
/* 2CBB088 800892C0 F44C010C */  jal        func_800533D0
/* 2CBB08C 800892C4 21206002 */   addu      $a0, $s3, $zero
/* 2CBB090 800892C8 0B250208 */  j          .Llevel_32_8008942C
/* 2CBB094 800892CC 21106002 */   addu      $v0, $s3, $zero
.Llevel_32_800892D0:
/* 2CBB098 800892D0 0000708E */  lw         $s0, 0x0($s3)
/* 2CBB09C 800892D4 C8E9000C */  jal        func_8003A720
/* 2CBB0A0 800892D8 21206002 */   addu      $a0, $s3, $zero
/* 2CBB0A4 800892DC 0C006426 */  addiu      $a0, $s3, 0xC
/* 2CBB0A8 800892E0 C05D000C */  jal        VecCopy
/* 2CBB0AC 800892E4 0C00A526 */   addiu     $a1, $s5, 0xC
/* 2CBB0B0 800892E8 CB89010C */  jal        rand
/* 2CBB0B4 800892EC 00000000 */   nop
/* 2CBB0B8 800892F0 7E004230 */  andi       $v0, $v0, 0x7E
/* 2CBB0BC 800892F4 C1FF4224 */  addiu      $v0, $v0, -0x3F
/* 2CBB0C0 800892F8 CB89010C */  jal        rand
/* 2CBB0C4 800892FC 000002AE */   sw        $v0, 0x0($s0)
/* 2CBB0C8 80089300 7E004230 */  andi       $v0, $v0, 0x7E
/* 2CBB0CC 80089304 C1FF4224 */  addiu      $v0, $v0, -0x3F
/* 2CBB0D0 80089308 CB89010C */  jal        rand
/* 2CBB0D4 8008930C 040002AE */   sw        $v0, 0x4($s0)
/* 2CBB0D8 80089310 7E004230 */  andi       $v0, $v0, 0x7E
/* 2CBB0DC 80089314 F0FF4224 */  addiu      $v0, $v0, -0x10
/* 2CBB0E0 80089318 CB89010C */  jal        rand
/* 2CBB0E4 8008931C 080002AE */   sw        $v0, 0x8($s0)
/* 2CBB0E8 80089320 21206002 */  addu       $a0, $s3, $zero
/* 2CBB0EC 80089324 1F004230 */  andi       $v0, $v0, 0x1F
/* 2CBB0F0 80089328 20004224 */  addiu      $v0, $v0, 0x20
/* 2CBB0F4 8008932C 08250208 */  j          .Llevel_32_80089420
/* 2CBB0F8 80089330 0C0002AE */   sw        $v0, 0xC($s0)
.Llevel_32_80089334:
/* 2CBB0FC 80089334 C8E9000C */  jal        func_8003A720
/* 2CBB100 80089338 21206002 */   addu      $a0, $s3, $zero
/* 2CBB104 8008933C 05000224 */  addiu      $v0, $zero, 0x5
/* 2CBB108 80089340 3100A012 */  beqz       $s5, .Llevel_32_80089408
/* 2CBB10C 80089344 470062A2 */   sb        $v0, 0x47($s3)
/* 2CBB110 80089348 0C006426 */  addiu      $a0, $s3, 0xC
/* 2CBB114 8008934C 05250208 */  j          .Llevel_32_80089414
/* 2CBB118 80089350 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_32_80089354:
/* 2CBB11C 80089354 C8E9000C */  jal        func_8003A720
/* 2CBB120 80089358 21206002 */   addu      $a0, $s3, $zero
/* 2CBB124 8008935C 0300A012 */  beqz       $s5, .Llevel_32_8008936C
/* 2CBB128 80089360 0C006426 */   addiu     $a0, $s3, 0xC
/* 2CBB12C 80089364 DD240208 */  j          .Llevel_32_80089374
/* 2CBB130 80089368 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_32_8008936C:
/* 2CBB134 8008936C 0880053C */  lui        $a1, %hi(g_Spyro)
/* 2CBB138 80089370 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_32_80089374:
/* 2CBB13C 80089374 C05D000C */  jal        VecCopy
/* 2CBB140 80089378 00000000 */   nop
/* 2CBB144 8008937C 0C006426 */  addiu      $a0, $s3, 0xC
/* 2CBB148 80089380 1400628E */  lw         $v0, 0x14($s3)
/* 2CBB14C 80089384 00080524 */  addiu      $a1, $zero, 0x800
/* 2CBB150 80089388 00024224 */  addiu      $v0, $v0, 0x200
/* 2CBB154 8008938C 7B35010C */  jal        func_8004D5EC
/* 2CBB158 80089390 140062AE */   sw        $v0, 0x14($s3)
/* 2CBB15C 80089394 1400648E */  lw         $a0, 0x14($s3)
/* 2CBB160 80089398 21184000 */  addu       $v1, $v0, $zero
/* 2CBB164 8008939C 23106400 */  subu       $v0, $v1, $a0
/* 2CBB168 800893A0 02004104 */  bgez       $v0, .Llevel_32_800893AC
/* 2CBB16C 800893A4 00000000 */   nop
/* 2CBB170 800893A8 23100200 */  negu       $v0, $v0
.Llevel_32_800893AC:
/* 2CBB174 800893AC 00084228 */  slti       $v0, $v0, 0x800
/* 2CBB178 800893B0 03004010 */  beqz       $v0, .Llevel_32_800893C0
/* 2CBB17C 800893B4 00FE8224 */   addiu     $v0, $a0, -0x200
/* 2CBB180 800893B8 07250208 */  j          .Llevel_32_8008941C
/* 2CBB184 800893BC 140063AE */   sw        $v1, 0x14($s3)
.Llevel_32_800893C0:
/* 2CBB188 800893C0 07250208 */  j          .Llevel_32_8008941C
/* 2CBB18C 800893C4 140062AE */   sw        $v0, 0x14($s3)
.Llevel_32_800893C8:
/* 2CBB190 800893C8 C8E9000C */  jal        func_8003A720
/* 2CBB194 800893CC 21206002 */   addu      $a0, $s3, $zero
/* 2CBB198 800893D0 21206002 */  addu       $a0, $s3, $zero
/* 2CBB19C 800893D4 20000224 */  addiu      $v0, $zero, 0x20
/* 2CBB1A0 800893D8 500062A2 */  sb         $v0, 0x50($s3)
/* 2CBB1A4 800893DC FF000224 */  addiu      $v0, $zero, 0xFF
/* 2CBB1A8 800893E0 734A010C */  jal        func_800529CC
/* 2CBB1AC 800893E4 520062A2 */   sb        $v0, 0x52($s3)
/* 2CBB1B0 800893E8 0B250208 */  j          .Llevel_32_8008942C
/* 2CBB1B4 800893EC 21106002 */   addu      $v0, $s3, $zero
.Llevel_32_800893F0:
/* 2CBB1B8 800893F0 C8E9000C */  jal        func_8003A720
/* 2CBB1BC 800893F4 21206002 */   addu      $a0, $s3, $zero
/* 2CBB1C0 800893F8 0300A012 */  beqz       $s5, .Llevel_32_80089408
/* 2CBB1C4 800893FC 0C006426 */   addiu     $a0, $s3, 0xC
/* 2CBB1C8 80089400 05250208 */  j          .Llevel_32_80089414
/* 2CBB1CC 80089404 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_32_80089408:
/* 2CBB1D0 80089408 0C006426 */  addiu      $a0, $s3, 0xC
/* 2CBB1D4 8008940C 0880053C */  lui        $a1, %hi(g_Spyro)
/* 2CBB1D8 80089410 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_32_80089414:
/* 2CBB1DC 80089414 C05D000C */  jal        VecCopy
/* 2CBB1E0 80089418 00000000 */   nop
.Llevel_32_8008941C:
/* 2CBB1E4 8008941C 21206002 */  addu       $a0, $s3, $zero
.Llevel_32_80089420:
/* 2CBB1E8 80089420 AA49010C */  jal        func_800526A8
/* 2CBB1EC 80089424 00000000 */   nop
.Llevel_32_80089428:
/* 2CBB1F0 80089428 21106002 */  addu       $v0, $s3, $zero
.Llevel_32_8008942C:
/* 2CBB1F4 8008942C 6000BF8F */  lw         $ra, 0x60($sp)
/* 2CBB1F8 80089430 5C00B58F */  lw         $s5, 0x5C($sp)
/* 2CBB1FC 80089434 5800B48F */  lw         $s4, 0x58($sp)
/* 2CBB200 80089438 5400B38F */  lw         $s3, 0x54($sp)
/* 2CBB204 8008943C 5000B28F */  lw         $s2, 0x50($sp)
/* 2CBB208 80089440 4C00B18F */  lw         $s1, 0x4C($sp)
/* 2CBB20C 80089444 4800B08F */  lw         $s0, 0x48($sp)
/* 2CBB210 80089448 6800BD27 */  addiu      $sp, $sp, 0x68
/* 2CBB214 8008944C 0800E003 */  jr         $ra
/* 2CBB218 80089450 00000000 */   nop
.size func_level_32_8008883C, . - func_level_32_8008883C
