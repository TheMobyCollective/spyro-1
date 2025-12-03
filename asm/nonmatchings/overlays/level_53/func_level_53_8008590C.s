.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_53_8008590C
/* 4B6B6D4 8008590C A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 4B6B6D8 80085910 3800B0AF */  sw         $s0, 0x38($sp)
/* 4B6B6DC 80085914 21808000 */  addu       $s0, $a0, $zero
/* 4B6B6E0 80085918 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 4B6B6E4 8008591C 21A8A000 */  addu       $s5, $a1, $zero
/* 4B6B6E8 80085920 5000BFAF */  sw         $ra, 0x50($sp)
/* 4B6B6EC 80085924 4800B4AF */  sw         $s4, 0x48($sp)
/* 4B6B6F0 80085928 4400B3AF */  sw         $s3, 0x44($sp)
/* 4B6B6F4 8008592C 4000B2AF */  sw         $s2, 0x40($sp)
/* 4B6B6F8 80085930 3149010C */  jal        func_800524C4
/* 4B6B6FC 80085934 3C00B1AF */   sw        $s1, 0x3C($sp)
/* 4B6B700 80085938 21984000 */  addu       $s3, $v0, $zero
/* 4B6B704 8008593C 1400A012 */  beqz       $s5, .Llevel_53_80085990
/* 4B6B708 80085940 360070A6 */   sh        $s0, 0x36($s3)
/* 4B6B70C 80085944 0780043C */  lui        $a0, %hi(D_80075828)
/* 4B6B710 80085948 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 4B6B714 8008594C 00000000 */  nop
/* 4B6B718 80085950 2320A402 */  subu       $a0, $s5, $a0
/* 4B6B71C 80085954 40190400 */  sll        $v1, $a0, 5
/* 4B6B720 80085958 23186400 */  subu       $v1, $v1, $a0
/* 4B6B724 8008595C 40190300 */  sll        $v1, $v1, 5
/* 4B6B728 80085960 21186400 */  addu       $v1, $v1, $a0
/* 4B6B72C 80085964 C0100300 */  sll        $v0, $v1, 3
/* 4B6B730 80085968 21186200 */  addu       $v1, $v1, $v0
/* 4B6B734 8008596C C0130300 */  sll        $v0, $v1, 15
/* 4B6B738 80085970 23104300 */  subu       $v0, $v0, $v1
/* 4B6B73C 80085974 80100200 */  sll        $v0, $v0, 2
/* 4B6B740 80085978 21104400 */  addu       $v0, $v0, $a0
/* 4B6B744 8008597C 23100200 */  negu       $v0, $v0
/* 4B6B748 80085980 C3180200 */  sra        $v1, $v0, 3
/* 4B6B74C 80085984 0001622C */  sltiu      $v0, $v1, 0x100
/* 4B6B750 80085988 03004014 */  bnez       $v0, .Llevel_53_80085998
/* 4B6B754 8008598C FB000224 */   addiu     $v0, $zero, 0xFB
.Llevel_53_80085990:
/* 4B6B758 80085990 21180000 */  addu       $v1, $zero, $zero
/* 4B6B75C 80085994 FB000224 */  addiu      $v0, $zero, 0xFB
.Llevel_53_80085998:
/* 4B6B760 80085998 6A020212 */  beq        $s0, $v0, .Llevel_53_80086344
/* 4B6B764 8008599C 560063A2 */   sb        $v1, 0x56($s3)
/* 4B6B768 800859A0 FC00022A */  slti       $v0, $s0, 0xFC
/* 4B6B76C 800859A4 3C004010 */  beqz       $v0, .Llevel_53_80085A98
/* 4B6B770 800859A8 4C000224 */   addiu     $v0, $zero, 0x4C
/* 4B6B774 800859AC 07030212 */  beq        $s0, $v0, .Llevel_53_800865CC
/* 4B6B778 800859B0 4D00022A */   slti      $v0, $s0, 0x4D
/* 4B6B77C 800859B4 1D004010 */  beqz       $v0, .Llevel_53_80085A2C
/* 4B6B780 800859B8 22000224 */   addiu     $v0, $zero, 0x22
/* 4B6B784 800859BC A4000212 */  beq        $s0, $v0, .Llevel_53_80085C50
/* 4B6B788 800859C0 2300022A */   slti      $v0, $s0, 0x23
/* 4B6B78C 800859C4 0E004010 */  beqz       $v0, .Llevel_53_80085A00
/* 4B6B790 800859C8 0F000224 */   addiu     $v0, $zero, 0xF
/* 4B6B794 800859CC 65000212 */  beq        $s0, $v0, .Llevel_53_80085B64
/* 4B6B798 800859D0 1000022A */   slti      $v0, $s0, 0x10
/* 4B6B79C 800859D4 05004010 */  beqz       $v0, .Llevel_53_800859EC
/* 4B6B7A0 800859D8 0E000224 */   addiu     $v0, $zero, 0xE
/* 4B6B7A4 800859DC 36010212 */  beq        $s0, $v0, .Llevel_53_80085EB8
/* 4B6B7A8 800859E0 00000000 */   nop
/* 4B6B7AC 800859E4 BD190208 */  j          .Llevel_53_800866F4
/* 4B6B7B0 800859E8 00000000 */   nop
.Llevel_53_800859EC:
/* 4B6B7B4 800859EC 10000224 */  addiu      $v0, $zero, 0x10
/* 4B6B7B8 800859F0 83000212 */  beq        $s0, $v0, .Llevel_53_80085C00
/* 4B6B7BC 800859F4 00000000 */   nop
/* 4B6B7C0 800859F8 BD190208 */  j          .Llevel_53_800866F4
/* 4B6B7C4 800859FC 00000000 */   nop
.Llevel_53_80085A00:
/* 4B6B7C8 80085A00 26000224 */  addiu      $v0, $zero, 0x26
/* 4B6B7CC 80085A04 A0000212 */  beq        $s0, $v0, .Llevel_53_80085C88
/* 4B6B7D0 80085A08 2600022A */   slti      $v0, $s0, 0x26
/* 4B6B7D4 80085A0C 39034014 */  bnez       $v0, .Llevel_53_800866F4
/* 4B6B7D8 80085A10 4600022A */   slti      $v0, $s0, 0x46
/* 4B6B7DC 80085A14 37034010 */  beqz       $v0, .Llevel_53_800866F4
/* 4B6B7E0 80085A18 4300022A */   slti      $v0, $s0, 0x43
/* 4B6B7E4 80085A1C DE014010 */  beqz       $v0, .Llevel_53_80086198
/* 4B6B7E8 80085A20 00000000 */   nop
/* 4B6B7EC 80085A24 BD190208 */  j          .Llevel_53_800866F4
/* 4B6B7F0 80085A28 00000000 */   nop
.Llevel_53_80085A2C:
/* 4B6B7F4 80085A2C 85000224 */  addiu      $v0, $zero, 0x85
/* 4B6B7F8 80085A30 D9010212 */  beq        $s0, $v0, .Llevel_53_80086198
/* 4B6B7FC 80085A34 8600022A */   slti      $v0, $s0, 0x86
/* 4B6B800 80085A38 09004010 */  beqz       $v0, .Llevel_53_80085A60
/* 4B6B804 80085A3C 5300022A */   slti      $v0, $s0, 0x53
/* 4B6B808 80085A40 2C034014 */  bnez       $v0, .Llevel_53_800866F4
/* 4B6B80C 80085A44 5800022A */   slti      $v0, $s0, 0x58
/* 4B6B810 80085A48 1B014014 */  bnez       $v0, .Llevel_53_80085EB8
/* 4B6B814 80085A4C 78000224 */   addiu     $v0, $zero, 0x78
/* 4B6B818 80085A50 B1010212 */  beq        $s0, $v0, .Llevel_53_80086118
/* 4B6B81C 80085A54 00000000 */   nop
/* 4B6B820 80085A58 BD190208 */  j          .Llevel_53_800866F4
/* 4B6B824 80085A5C 00000000 */   nop
.Llevel_53_80085A60:
/* 4B6B828 80085A60 9A00022A */  slti       $v0, $s0, 0x9A
/* 4B6B82C 80085A64 07004010 */  beqz       $v0, .Llevel_53_80085A84
/* 4B6B830 80085A68 9800022A */   slti      $v0, $s0, 0x98
/* 4B6B834 80085A6C BC014010 */  beqz       $v0, .Llevel_53_80086160
/* 4B6B838 80085A70 97000224 */   addiu     $v0, $zero, 0x97
/* 4B6B83C 80085A74 C8010212 */  beq        $s0, $v0, .Llevel_53_80086198
/* 4B6B840 80085A78 00000000 */   nop
/* 4B6B844 80085A7C BD190208 */  j          .Llevel_53_800866F4
/* 4B6B848 80085A80 00000000 */   nop
.Llevel_53_80085A84:
/* 4B6B84C 80085A84 D7000224 */  addiu      $v0, $zero, 0xD7
/* 4B6B850 80085A88 61010212 */  beq        $s0, $v0, .Llevel_53_80086010
/* 4B6B854 80085A8C 78000424 */   addiu     $a0, $zero, 0x78
/* 4B6B858 80085A90 BD190208 */  j          .Llevel_53_800866F4
/* 4B6B85C 80085A94 00000000 */   nop
.Llevel_53_80085A98:
/* 4B6B860 80085A98 88010224 */  addiu      $v0, $zero, 0x188
/* 4B6B864 80085A9C A6020212 */  beq        $s0, $v0, .Llevel_53_80086538
/* 4B6B868 80085AA0 8901022A */   slti      $v0, $s0, 0x189
/* 4B6B86C 80085AA4 19004010 */  beqz       $v0, .Llevel_53_80085B0C
/* 4B6B870 80085AA8 0E01022A */   slti      $v0, $s0, 0x10E
/* 4B6B874 80085AAC 09004010 */  beqz       $v0, .Llevel_53_80085AD4
/* 4B6B878 80085AB0 0401022A */   slti      $v0, $s0, 0x104
/* 4B6B87C 80085AB4 93024010 */  beqz       $v0, .Llevel_53_80086504
/* 4B6B880 80085AB8 0201022A */   slti      $v0, $s0, 0x102
/* 4B6B884 80085ABC 0D034010 */  beqz       $v0, .Llevel_53_800866F4
/* 4B6B888 80085AC0 FF00022A */   slti      $v0, $s0, 0xFF
/* 4B6B88C 80085AC4 B4014010 */  beqz       $v0, .Llevel_53_80086198
/* 4B6B890 80085AC8 00000000 */   nop
/* 4B6B894 80085ACC BD190208 */  j          .Llevel_53_800866F4
/* 4B6B898 80085AD0 00000000 */   nop
.Llevel_53_80085AD4:
/* 4B6B89C 80085AD4 3801022A */  slti       $v0, $s0, 0x138
/* 4B6B8A0 80085AD8 07004010 */  beqz       $v0, .Llevel_53_80085AF8
/* 4B6B8A4 80085ADC 3501022A */   slti      $v0, $s0, 0x135
/* 4B6B8A8 80085AE0 AD014010 */  beqz       $v0, .Llevel_53_80086198
/* 4B6B8AC 80085AE4 15010224 */   addiu     $v0, $zero, 0x115
/* 4B6B8B0 80085AE8 86020212 */  beq        $s0, $v0, .Llevel_53_80086504
/* 4B6B8B4 80085AEC 00000000 */   nop
/* 4B6B8B8 80085AF0 BD190208 */  j          .Llevel_53_800866F4
/* 4B6B8BC 80085AF4 00000000 */   nop
.Llevel_53_80085AF8:
/* 4B6B8C0 80085AF8 47010224 */  addiu      $v0, $zero, 0x147
/* 4B6B8C4 80085AFC 81020212 */  beq        $s0, $v0, .Llevel_53_80086504
/* 4B6B8C8 80085B00 00000000 */   nop
/* 4B6B8CC 80085B04 BD190208 */  j          .Llevel_53_800866F4
/* 4B6B8D0 80085B08 00000000 */   nop
.Llevel_53_80085B0C:
/* 4B6B8D4 80085B0C C401022A */  slti       $v0, $s0, 0x1C4
/* 4B6B8D8 80085B10 0B004010 */  beqz       $v0, .Llevel_53_80085B40
/* 4B6B8DC 80085B14 AA01022A */   slti      $v0, $s0, 0x1AA
/* 4B6B8E0 80085B18 AC024010 */  beqz       $v0, .Llevel_53_800865CC
/* 4B6B8E4 80085B1C 95010224 */   addiu     $v0, $zero, 0x195
/* 4B6B8E8 80085B20 8D020212 */  beq        $s0, $v0, .Llevel_53_80086558
/* 4B6B8EC 80085B24 9501022A */   slti      $v0, $s0, 0x195
/* 4B6B8F0 80085B28 F2024014 */  bnez       $v0, .Llevel_53_800866F4
/* 4B6B8F4 80085B2C A701022A */   slti      $v0, $s0, 0x1A7
/* 4B6B8F8 80085B30 99014010 */  beqz       $v0, .Llevel_53_80086198
/* 4B6B8FC 80085B34 00000000 */   nop
/* 4B6B900 80085B38 BD190208 */  j          .Llevel_53_800866F4
/* 4B6B904 80085B3C 00000000 */   nop
.Llevel_53_80085B40:
/* 4B6B908 80085B40 CA01022A */  slti       $v0, $s0, 0x1CA
/* 4B6B90C 80085B44 EB024014 */  bnez       $v0, .Llevel_53_800866F4
/* 4B6B910 80085B48 CC01022A */   slti      $v0, $s0, 0x1CC
/* 4B6B914 80085B4C A9024014 */  bnez       $v0, .Llevel_53_800865F4
/* 4B6B918 80085B50 DD010224 */   addiu     $v0, $zero, 0x1DD
/* 4B6B91C 80085B54 80020212 */  beq        $s0, $v0, .Llevel_53_80086558
/* 4B6B920 80085B58 00000000 */   nop
/* 4B6B924 80085B5C BD190208 */  j          .Llevel_53_800866F4
/* 4B6B928 80085B60 00000000 */   nop
.Llevel_53_80085B64:
/* 4B6B92C 80085B64 0000708E */  lw         $s0, 0x0($s3)
/* 4B6B930 80085B68 C8E9000C */  jal        func_8003A720
/* 4B6B934 80085B6C 21206002 */   addu      $a0, $s3, $zero
/* 4B6B938 80085B70 8C000224 */  addiu      $v0, $zero, 0x8C
/* 4B6B93C 80085B74 080002AE */  sw         $v0, 0x8($s0)
/* 4B6B940 80085B78 03000224 */  addiu      $v0, $zero, 0x3
/* 4B6B944 80085B7C 100002A2 */  sb         $v0, 0x10($s0)
/* 4B6B948 80085B80 FF000224 */  addiu      $v0, $zero, 0xFF
/* 4B6B94C 80085B84 140002A2 */  sb         $v0, 0x14($s0)
/* 4B6B950 80085B88 02000224 */  addiu      $v0, $zero, 0x2
/* 4B6B954 80085B8C 000000AE */  sw         $zero, 0x0($s0)
/* 4B6B958 80085B90 040000AE */  sw         $zero, 0x4($s0)
/* 4B6B95C 80085B94 0E0000A2 */  sb         $zero, 0xE($s0)
/* 4B6B960 80085B98 0F0000A2 */  sb         $zero, 0xF($s0)
/* 4B6B964 80085B9C 110000A2 */  sb         $zero, 0x11($s0)
/* 4B6B968 80085BA0 120000A2 */  sb         $zero, 0x12($s0)
/* 4B6B96C 80085BA4 130000A2 */  sb         $zero, 0x13($s0)
/* 4B6B970 80085BA8 490062A2 */  sb         $v0, 0x49($s3)
/* 4B6B974 80085BAC 18000224 */  addiu      $v0, $zero, 0x18
/* 4B6B978 80085BB0 500062A2 */  sb         $v0, 0x50($s3)
/* 4B6B97C 80085BB4 10000224 */  addiu      $v0, $zero, 0x10
/* 4B6B980 80085BB8 520062A2 */  sb         $v0, 0x52($s3)
/* 4B6B984 80085BBC 20000224 */  addiu      $v0, $zero, 0x20
/* 4B6B988 80085BC0 440062A2 */  sb         $v0, 0x44($s3)
/* 4B6B98C 80085BC4 450060A2 */  sb         $zero, 0x45($s3)
/* 4B6B990 80085BC8 0400A012 */  beqz       $s5, .Llevel_53_80085BDC
/* 4B6B994 80085BCC 460060A2 */   sb        $zero, 0x46($s3)
/* 4B6B998 80085BD0 0C006426 */  addiu      $a0, $s3, 0xC
/* 4B6B99C 80085BD4 C05D000C */  jal        VecCopy
/* 4B6B9A0 80085BD8 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_53_80085BDC:
/* 4B6B9A4 80085BDC AA49010C */  jal        func_800526A8
/* 4B6B9A8 80085BE0 21206002 */   addu      $a0, $s3, $zero
/* 4B6B9AC 80085BE4 4B006292 */  lbu        $v0, 0x4B($s3)
/* 4B6B9B0 80085BE8 01000324 */  addiu      $v1, $zero, 0x1
/* 4B6B9B4 80085BEC 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 4B6B9B8 80085BF0 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 4B6B9BC 80085BF4 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 4B6B9C0 80085BF8 CE180208 */  j          .Llevel_53_80086338
/* 4B6B9C4 80085BFC 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_53_80085C00:
/* 4B6B9C8 80085C00 0000718E */  lw         $s1, 0x0($s3)
/* 4B6B9CC 80085C04 C8E9000C */  jal        func_8003A720
/* 4B6B9D0 80085C08 21206002 */   addu      $a0, $s3, $zero
/* 4B6B9D4 80085C0C AA49010C */  jal        func_800526A8
/* 4B6B9D8 80085C10 21206002 */   addu      $a0, $s3, $zero
/* 4B6B9DC 80085C14 0C007026 */  addiu      $s0, $s3, 0xC
/* 4B6B9E0 80085C18 21200002 */  addu       $a0, $s0, $zero
/* 4B6B9E4 80085C1C C05D000C */  jal        VecCopy
/* 4B6B9E8 80085C20 0C00A526 */   addiu     $a1, $s5, 0xC
/* 4B6B9EC 80085C24 21280002 */  addu       $a1, $s0, $zero
/* 4B6B9F0 80085C28 1400628E */  lw         $v0, 0x14($s3)
/* 4B6B9F4 80085C2C 04002426 */  addiu      $a0, $s1, 0x4
/* 4B6B9F8 80085C30 00024224 */  addiu      $v0, $v0, 0x200
/* 4B6B9FC 80085C34 C05D000C */  jal        VecCopy
/* 4B6BA00 80085C38 140062AE */   sw        $v0, 0x14($s3)
/* 4B6BA04 80085C3C 08070224 */  addiu      $v0, $zero, 0x708
/* 4B6BA08 80085C40 130020A2 */  sb         $zero, 0x13($s1)
/* 4B6BA0C 80085C44 120020A2 */  sb         $zero, 0x12($s1)
/* 4B6BA10 80085C48 CA190208 */  j          .Llevel_53_80086728
/* 4B6BA14 80085C4C 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_53_80085C50:
/* 4B6BA18 80085C50 C8E9000C */  jal        func_8003A720
/* 4B6BA1C 80085C54 21206002 */   addu      $a0, $s3, $zero
/* 4B6BA20 80085C58 20000224 */  addiu      $v0, $zero, 0x20
/* 4B6BA24 80085C5C 500062A2 */  sb         $v0, 0x50($s3)
/* 4B6BA28 80085C60 FF000224 */  addiu      $v0, $zero, 0xFF
/* 4B6BA2C 80085C64 0400A012 */  beqz       $s5, .Llevel_53_80085C78
/* 4B6BA30 80085C68 520062A2 */   sb        $v0, 0x52($s3)
/* 4B6BA34 80085C6C 0C006426 */  addiu      $a0, $s3, 0xC
/* 4B6BA38 80085C70 C05D000C */  jal        VecCopy
/* 4B6BA3C 80085C74 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_53_80085C78:
/* 4B6BA40 80085C78 734A010C */  jal        func_800529CC
/* 4B6BA44 80085C7C 21206002 */   addu      $a0, $s3, $zero
/* 4B6BA48 80085C80 CB190208 */  j          .Llevel_53_8008672C
/* 4B6BA4C 80085C84 21106002 */   addu      $v0, $s3, $zero
.Llevel_53_80085C88:
/* 4B6BA50 80085C88 0000728E */  lw         $s2, 0x0($s3)
/* 4B6BA54 80085C8C C8E9000C */  jal        func_8003A720
/* 4B6BA58 80085C90 21206002 */   addu      $a0, $s3, $zero
/* 4B6BA5C 80085C94 0C007126 */  addiu      $s1, $s3, 0xC
/* 4B6BA60 80085C98 21202002 */  addu       $a0, $s1, $zero
/* 4B6BA64 80085C9C C05D000C */  jal        VecCopy
/* 4B6BA68 80085CA0 0C00A526 */   addiu     $a1, $s5, 0xC
/* 4B6BA6C 80085CA4 3600A286 */  lh         $v0, 0x36($s5)
/* 4B6BA70 80085CA8 00000000 */  nop
/* 4B6BA74 80085CAC 13005014 */  bne        $v0, $s0, .Llevel_53_80085CFC
/* 4B6BA78 80085CB0 03000324 */   addiu     $v1, $zero, 0x3
/* 4B6BA7C 80085CB4 4600A492 */  lbu        $a0, 0x46($s5)
/* 4B6BA80 80085CB8 36006286 */  lh         $v0, 0x36($s3)
/* 4B6BA84 80085CBC 480063A2 */  sb         $v1, 0x48($s3)
/* 4B6BA88 80085CC0 400060A2 */  sb         $zero, 0x40($s3)
/* 4B6BA8C 80085CC4 80100200 */  sll        $v0, $v0, 2
/* 4B6BA90 80085CC8 460064A2 */  sb         $a0, 0x46($s3)
/* 4B6BA94 80085CCC 0780013C */  lui        $at, %hi(g_Models)
/* 4B6BA98 80085CD0 21082200 */  addu       $at, $at, $v0
/* 4B6BA9C 80085CD4 7863228C */  lw         $v0, %lo(g_Models)($at)
/* 4B6BAA0 80085CD8 00000000 */  nop
/* 4B6BAA4 80085CDC 4400428C */  lw         $v0, 0x44($v0)
/* 4B6BAA8 80085CE0 00000000 */  nop
/* 4B6BAAC 80085CE4 0C004290 */  lbu        $v0, 0xC($v0)
/* 4B6BAB0 80085CE8 3C0063A2 */  sb         $v1, 0x3C($s3)
/* 4B6BAB4 80085CEC 3D0063A2 */  sb         $v1, 0x3D($s3)
/* 4B6BAB8 80085CF0 410062A2 */  sb         $v0, 0x41($s3)
/* 4B6BABC 80085CF4 AC170208 */  j          .Llevel_53_80085EB0
/* 4B6BAC0 80085CF8 03000224 */   addiu     $v0, $zero, 0x3
.Llevel_53_80085CFC:
/* 4B6BAC4 80085CFC 3F00A392 */  lbu        $v1, 0x3F($s5)
/* 4B6BAC8 80085D00 00000000 */  nop
/* 4B6BACC 80085D04 0600622C */  sltiu      $v0, $v1, 0x6
/* 4B6BAD0 80085D08 4A004014 */  bnez       $v0, .Llevel_53_80085E34
/* 4B6BAD4 80085D0C 0200622C */   sltiu     $v0, $v1, 0x2
/* 4B6BAD8 80085D10 4600A492 */  lbu        $a0, 0x46($s5)
/* 4B6BADC 80085D14 2C5B000C */  jal        Cos
/* 4B6BAE0 80085D18 00210400 */   sll       $a0, $a0, 4
/* 4B6BAE4 80085D1C 0C00638E */  lw         $v1, 0xC($s3)
/* 4B6BAE8 80085D20 83100200 */  sra        $v0, $v0, 2
/* 4B6BAEC 80085D24 21186200 */  addu       $v1, $v1, $v0
/* 4B6BAF0 80085D28 0C0063AE */  sw         $v1, 0xC($s3)
/* 4B6BAF4 80085D2C 4600A492 */  lbu        $a0, 0x46($s5)
/* 4B6BAF8 80085D30 165B000C */  jal        Sin
/* 4B6BAFC 80085D34 00210400 */   sll       $a0, $a0, 4
/* 4B6BB00 80085D38 21202002 */  addu       $a0, $s1, $zero
/* 4B6BB04 80085D3C 83100200 */  sra        $v0, $v0, 2
/* 4B6BB08 80085D40 1000638E */  lw         $v1, 0x10($s3)
/* 4B6BB0C 80085D44 1400658E */  lw         $a1, 0x14($s3)
/* 4B6BB10 80085D48 21186200 */  addu       $v1, $v1, $v0
/* 4B6BB14 80085D4C 2C01A524 */  addiu      $a1, $a1, 0x12C
/* 4B6BB18 80085D50 100063AE */  sw         $v1, 0x10($s3)
/* 4B6BB1C 80085D54 140065AE */  sw         $a1, 0x14($s3)
/* 4B6BB20 80085D58 4600A292 */  lbu        $v0, 0x46($s5)
/* 4B6BB24 80085D5C 0880053C */  lui        $a1, %hi(g_Spyro)
/* 4B6BB28 80085D60 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
/* 4B6BB2C 80085D64 645E000C */  jal        OctDistance
/* 4B6BB30 80085D68 460062A2 */   sb        $v0, 0x46($s3)
/* 4B6BB34 80085D6C 21204000 */  addu       $a0, $v0, $zero
/* 4B6BB38 80085D70 0880023C */  lui        $v0, %hi(g_Spyro + 0x8)
/* 4B6BB3C 80085D74 608A428C */  lw         $v0, %lo(g_Spyro + 0x8)($v0)
/* 4B6BB40 80085D78 1400658E */  lw         $a1, 0x14($s3)
/* 4B6BB44 80085D7C 21300000 */  addu       $a2, $zero, $zero
/* 4B6BB48 80085D80 AD5A000C */  jal        Atan2
/* 4B6BB4C 80085D84 23284500 */   subu      $a1, $v0, $a1
/* 4B6BB50 80085D88 4500A492 */  lbu        $a0, 0x45($s5)
/* 4B6BB54 80085D8C 00000000 */  nop
/* 4B6BB58 80085D90 23104400 */  subu       $v0, $v0, $a0
/* 4B6BB5C 80085D94 FF004330 */  andi       $v1, $v0, 0xFF
/* 4B6BB60 80085D98 81006228 */  slti       $v0, $v1, 0x81
/* 4B6BB64 80085D9C 03004014 */  bnez       $v0, .Llevel_53_80085DAC
/* 4B6BB68 80085DA0 F0FF6228 */   slti      $v0, $v1, -0x10
/* 4B6BB6C 80085DA4 00FF6324 */  addiu      $v1, $v1, -0x100
/* 4B6BB70 80085DA8 F0FF6228 */  slti       $v0, $v1, -0x10
.Llevel_53_80085DAC:
/* 4B6BB74 80085DAC 03004010 */  beqz       $v0, .Llevel_53_80085DBC
/* 4B6BB78 80085DB0 11006228 */   slti      $v0, $v1, 0x11
/* 4B6BB7C 80085DB4 F0FF0324 */  addiu      $v1, $zero, -0x10
/* 4B6BB80 80085DB8 11006228 */  slti       $v0, $v1, 0x11
.Llevel_53_80085DBC:
/* 4B6BB84 80085DBC 03004014 */  bnez       $v0, .Llevel_53_80085DCC
/* 4B6BB88 80085DC0 21108300 */   addu      $v0, $a0, $v1
/* 4B6BB8C 80085DC4 10000324 */  addiu      $v1, $zero, 0x10
/* 4B6BB90 80085DC8 21108300 */  addu       $v0, $a0, $v1
.Llevel_53_80085DCC:
/* 4B6BB94 80085DCC 450062A2 */  sb         $v0, 0x45($s3)
/* 4B6BB98 80085DD0 80000224 */  addiu      $v0, $zero, 0x80
/* 4B6BB9C 80085DD4 000042AE */  sw         $v0, 0x0($s2)
/* 4B6BBA0 80085DD8 36006286 */  lh         $v0, 0x36($s3)
/* 4B6BBA4 80085DDC 02000324 */  addiu      $v1, $zero, 0x2
/* 4B6BBA8 80085DE0 480063A2 */  sb         $v1, 0x48($s3)
/* 4B6BBAC 80085DE4 400060A2 */  sb         $zero, 0x40($s3)
/* 4B6BBB0 80085DE8 80100200 */  sll        $v0, $v0, 2
/* 4B6BBB4 80085DEC 0780013C */  lui        $at, %hi(g_Models)
/* 4B6BBB8 80085DF0 21082200 */  addu       $at, $at, $v0
/* 4B6BBBC 80085DF4 7863228C */  lw         $v0, %lo(g_Models)($at)
/* 4B6BBC0 80085DF8 04000424 */  addiu      $a0, $zero, 0x4
/* 4B6BBC4 80085DFC 4000428C */  lw         $v0, 0x40($v0)
/* 4B6BBC8 80085E00 07000524 */  addiu      $a1, $zero, 0x7
/* 4B6BBCC 80085E04 0C004290 */  lbu        $v0, 0xC($v0)
/* 4B6BBD0 80085E08 21302002 */  addu       $a2, $s1, $zero
/* 4B6BBD4 80085E0C 3C0063A2 */  sb         $v1, 0x3C($s3)
/* 4B6BBD8 80085E10 3D0063A2 */  sb         $v1, 0x3D($s3)
/* 4B6BBDC 80085E14 410062A2 */  sb         $v0, 0x41($s3)
/* 4B6BBE0 80085E18 0780023C */  lui        $v0, %hi(D_800758E4)
/* 4B6BBE4 80085E1C E458428C */  lw         $v0, %lo(D_800758E4)($v0)
/* 4B6BBE8 80085E20 00000000 */  nop
/* 4B6BBEC 80085E24 09F84000 */  jalr       $v0
/* 4B6BBF0 80085E28 10000724 */   addiu     $a3, $zero, 0x10
/* 4B6BBF4 80085E2C C8190208 */  j          .Llevel_53_80086720
/* 4B6BBF8 80085E30 00000000 */   nop
.Llevel_53_80085E34:
/* 4B6BBFC 80085E34 16004014 */  bnez       $v0, .Llevel_53_80085E90
/* 4B6BC00 80085E38 01000324 */   addiu     $v1, $zero, 0x1
/* 4B6BC04 80085E3C 1400628E */  lw         $v0, 0x14($s3)
/* 4B6BC08 80085E40 00000000 */  nop
/* 4B6BC0C 80085E44 2C014224 */  addiu      $v0, $v0, 0x12C
/* 4B6BC10 80085E48 140062AE */  sw         $v0, 0x14($s3)
/* 4B6BC14 80085E4C 4600A492 */  lbu        $a0, 0x46($s5)
/* 4B6BC18 80085E50 36006286 */  lh         $v0, 0x36($s3)
/* 4B6BC1C 80085E54 480063A2 */  sb         $v1, 0x48($s3)
/* 4B6BC20 80085E58 400060A2 */  sb         $zero, 0x40($s3)
/* 4B6BC24 80085E5C 80100200 */  sll        $v0, $v0, 2
/* 4B6BC28 80085E60 460064A2 */  sb         $a0, 0x46($s3)
/* 4B6BC2C 80085E64 0780013C */  lui        $at, %hi(g_Models)
/* 4B6BC30 80085E68 21082200 */  addu       $at, $at, $v0
/* 4B6BC34 80085E6C 7863228C */  lw         $v0, %lo(g_Models)($at)
/* 4B6BC38 80085E70 00000000 */  nop
/* 4B6BC3C 80085E74 3C00428C */  lw         $v0, 0x3C($v0)
/* 4B6BC40 80085E78 00000000 */  nop
/* 4B6BC44 80085E7C 0C004290 */  lbu        $v0, 0xC($v0)
/* 4B6BC48 80085E80 3C0063A2 */  sb         $v1, 0x3C($s3)
/* 4B6BC4C 80085E84 3D0063A2 */  sb         $v1, 0x3D($s3)
/* 4B6BC50 80085E88 AB170208 */  j          .Llevel_53_80085EAC
/* 4B6BC54 80085E8C 410062A2 */   sb        $v0, 0x41($s3)
.Llevel_53_80085E90:
/* 4B6BC58 80085E90 1400628E */  lw         $v0, 0x14($s3)
/* 4B6BC5C 80085E94 00000000 */  nop
/* 4B6BC60 80085E98 80014224 */  addiu      $v0, $v0, 0x180
/* 4B6BC64 80085E9C 140062AE */  sw         $v0, 0x14($s3)
/* 4B6BC68 80085EA0 4600A292 */  lbu        $v0, 0x46($s5)
/* 4B6BC6C 80085EA4 00000000 */  nop
/* 4B6BC70 80085EA8 460062A2 */  sb         $v0, 0x46($s3)
.Llevel_53_80085EAC:
/* 4B6BC74 80085EAC 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_53_80085EB0:
/* 4B6BC78 80085EB0 C8190208 */  j          .Llevel_53_80086720
/* 4B6BC7C 80085EB4 000042AE */   sw        $v0, 0x0($s2)
.Llevel_53_80085EB8:
/* 4B6BC80 80085EB8 0000718E */  lw         $s1, 0x0($s3)
/* 4B6BC84 80085EBC C8E9000C */  jal        func_8003A720
/* 4B6BC88 80085EC0 21206002 */   addu      $a0, $s3, $zero
/* 4B6BC8C 80085EC4 8C000224 */  addiu      $v0, $zero, 0x8C
/* 4B6BC90 80085EC8 000020AE */  sw         $zero, 0x0($s1)
/* 4B6BC94 80085ECC 040020AE */  sw         $zero, 0x4($s1)
/* 4B6BC98 80085ED0 080022AE */  sw         $v0, 0x8($s1)
/* 4B6BC9C 80085ED4 0E0020A2 */  sb         $zero, 0xE($s1)
/* 4B6BCA0 80085ED8 0F0020A2 */  sb         $zero, 0xF($s1)
/* 4B6BCA4 80085EDC 110020A2 */  sb         $zero, 0x11($s1)
/* 4B6BCA8 80085EE0 120020A2 */  sb         $zero, 0x12($s1)
/* 4B6BCAC 80085EE4 130020A2 */  sb         $zero, 0x13($s1)
/* 4B6BCB0 80085EE8 3600A386 */  lh         $v1, 0x36($s5)
/* 4B6BCB4 80085EEC 0D000224 */  addiu      $v0, $zero, 0xD
/* 4B6BCB8 80085EF0 02006214 */  bne        $v1, $v0, .Llevel_53_80085EFC
/* 4B6BCBC 80085EF4 03000224 */   addiu     $v0, $zero, 0x3
/* 4B6BCC0 80085EF8 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_53_80085EFC:
/* 4B6BCC4 80085EFC 100022A2 */  sb         $v0, 0x10($s1)
/* 4B6BCC8 80085F00 0C007026 */  addiu      $s0, $s3, 0xC
/* 4B6BCCC 80085F04 21200002 */  addu       $a0, $s0, $zero
/* 4B6BCD0 80085F08 0C00A526 */  addiu      $a1, $s5, 0xC
/* 4B6BCD4 80085F0C FF000224 */  addiu      $v0, $zero, 0xFF
/* 4B6BCD8 80085F10 140022A2 */  sb         $v0, 0x14($s1)
/* 4B6BCDC 80085F14 02001124 */  addiu      $s1, $zero, 0x2
/* 4B6BCE0 80085F18 18000224 */  addiu      $v0, $zero, 0x18
/* 4B6BCE4 80085F1C 500062A2 */  sb         $v0, 0x50($s3)
/* 4B6BCE8 80085F20 40000224 */  addiu      $v0, $zero, 0x40
/* 4B6BCEC 80085F24 520062A2 */  sb         $v0, 0x52($s3)
/* 4B6BCF0 80085F28 20000224 */  addiu      $v0, $zero, 0x20
/* 4B6BCF4 80085F2C 490071A2 */  sb         $s1, 0x49($s3)
/* 4B6BCF8 80085F30 440062A2 */  sb         $v0, 0x44($s3)
/* 4B6BCFC 80085F34 450060A2 */  sb         $zero, 0x45($s3)
/* 4B6BD00 80085F38 C05D000C */  jal        VecCopy
/* 4B6BD04 80085F3C 460060A2 */   sb        $zero, 0x46($s3)
/* 4B6BD08 80085F40 734A010C */  jal        func_800529CC
/* 4B6BD0C 80085F44 21206002 */   addu      $a0, $s3, $zero
/* 4B6BD10 80085F48 1000A427 */  addiu      $a0, $sp, 0x10
/* 4B6BD14 80085F4C 21280002 */  addu       $a1, $s0, $zero
/* 4B6BD18 80085F50 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 4B6BD1C 80085F54 C05D000C */  jal        VecCopy
/* 4B6BD20 80085F58 1C0062AE */   sw        $v0, 0x1C($s3)
/* 4B6BD24 80085F5C 1000A427 */  addiu      $a0, $sp, 0x10
/* 4B6BD28 80085F60 1800A28F */  lw         $v0, 0x18($sp)
/* 4B6BD2C 80085F64 0100053C */  lui        $a1, (0x10000 >> 16)
/* 4B6BD30 80085F68 00044224 */  addiu      $v0, $v0, 0x400
/* 4B6BD34 80085F6C 7B35010C */  jal        func_8004D5EC
/* 4B6BD38 80085F70 1800A2AF */   sw        $v0, 0x18($sp)
/* 4B6BD3C 80085F74 F44C010C */  jal        func_800533D0
/* 4B6BD40 80085F78 21206002 */   addu      $a0, $s3, $zero
/* 4B6BD44 80085F7C 36006386 */  lh         $v1, 0x36($s3)
/* 4B6BD48 80085F80 0E000224 */  addiu      $v0, $zero, 0xE
/* 4B6BD4C 80085F84 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 4B6BD50 80085F88 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 4B6BD54 80085F8C 03006214 */  bne        $v1, $v0, .Llevel_53_80085F9C
/* 4B6BD58 80085F90 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 4B6BD5C 80085F94 0C000224 */  addiu      $v0, $zero, 0xC
/* 4B6BD60 80085F98 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_53_80085F9C:
/* 4B6BD64 80085F9C 36006386 */  lh         $v1, 0x36($s3)
/* 4B6BD68 80085FA0 53000224 */  addiu      $v0, $zero, 0x53
/* 4B6BD6C 80085FA4 05006214 */  bne        $v1, $v0, .Llevel_53_80085FBC
/* 4B6BD70 80085FA8 54000224 */   addiu     $v0, $zero, 0x54
/* 4B6BD74 80085FAC 01000224 */  addiu      $v0, $zero, 0x1
/* 4B6BD78 80085FB0 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 4B6BD7C 80085FB4 36006386 */  lh         $v1, 0x36($s3)
/* 4B6BD80 80085FB8 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_53_80085FBC:
/* 4B6BD84 80085FBC 02006214 */  bne        $v1, $v0, .Llevel_53_80085FC8
/* 4B6BD88 80085FC0 00000000 */   nop
/* 4B6BD8C 80085FC4 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_53_80085FC8:
/* 4B6BD90 80085FC8 36006386 */  lh         $v1, 0x36($s3)
/* 4B6BD94 80085FCC 55000224 */  addiu      $v0, $zero, 0x55
/* 4B6BD98 80085FD0 05006214 */  bne        $v1, $v0, .Llevel_53_80085FE8
/* 4B6BD9C 80085FD4 56000224 */   addiu     $v0, $zero, 0x56
/* 4B6BDA0 80085FD8 03000224 */  addiu      $v0, $zero, 0x3
/* 4B6BDA4 80085FDC 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 4B6BDA8 80085FE0 36006386 */  lh         $v1, 0x36($s3)
/* 4B6BDAC 80085FE4 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_53_80085FE8:
/* 4B6BDB0 80085FE8 02006214 */  bne        $v1, $v0, .Llevel_53_80085FF4
/* 4B6BDB4 80085FEC 04000224 */   addiu     $v0, $zero, 0x4
/* 4B6BDB8 80085FF0 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_53_80085FF4:
/* 4B6BDBC 80085FF4 36006386 */  lh         $v1, 0x36($s3)
/* 4B6BDC0 80085FF8 57000224 */  addiu      $v0, $zero, 0x57
/* 4B6BDC4 80085FFC CB016214 */  bne        $v1, $v0, .Llevel_53_8008672C
/* 4B6BDC8 80086000 21106002 */   addu      $v0, $s3, $zero
/* 4B6BDCC 80086004 05000224 */  addiu      $v0, $zero, 0x5
/* 4B6BDD0 80086008 CA190208 */  j          .Llevel_53_80086728
/* 4B6BDD4 8008600C 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_53_80086010:
/* 4B6BDD8 80086010 A8DF000C */  jal        RandRange
/* 4B6BDDC 80086014 96000524 */   addiu     $a1, $zero, 0x96
/* 4B6BDE0 80086018 21206002 */  addu       $a0, $s3, $zero
/* 4B6BDE4 8008601C 0000708E */  lw         $s0, 0x0($s3)
/* 4B6BDE8 80086020 C8E9000C */  jal        func_8003A720
/* 4B6BDEC 80086024 21884000 */   addu      $s1, $v0, $zero
/* 4B6BDF0 80086028 0C006426 */  addiu      $a0, $s3, 0xC
/* 4B6BDF4 8008602C 0C00A526 */  addiu      $a1, $s5, 0xC
/* 4B6BDF8 80086030 20000224 */  addiu      $v0, $zero, 0x20
/* 4B6BDFC 80086034 C05D000C */  jal        VecCopy
/* 4B6BE00 80086038 500062A2 */   sb        $v0, 0x50($s3)
/* 4B6BE04 8008603C AA49010C */  jal        func_800526A8
/* 4B6BE08 80086040 21206002 */   addu      $a0, $s3, $zero
/* 4B6BE0C 80086044 F1FF0424 */  addiu      $a0, $zero, -0xF
/* 4B6BE10 80086048 A8DF000C */  jal        RandRange
/* 4B6BE14 8008604C 0F000524 */   addiu     $a1, $zero, 0xF
/* 4B6BE18 80086050 4500A392 */  lbu        $v1, 0x45($s5)
/* 4B6BE1C 80086054 00000000 */  nop
/* 4B6BE20 80086058 21186200 */  addu       $v1, $v1, $v0
/* 4B6BE24 8008605C FF006330 */  andi       $v1, $v1, 0xFF
/* 4B6BE28 80086060 40180300 */  sll        $v1, $v1, 1
/* 4B6BE2C 80086064 0780013C */  lui        $at, %hi(D_8006CC78)
/* 4B6BE30 80086068 21082300 */  addu       $at, $at, $v1
/* 4B6BE34 8008606C 78CC2284 */  lh         $v0, %lo(D_8006CC78)($at)
/* 4B6BE38 80086070 00000000 */  nop
/* 4B6BE3C 80086074 18002202 */  mult       $s1, $v0
/* 4B6BE40 80086078 12400000 */  mflo       $t0
/* 4B6BE44 8008607C 03130800 */  sra        $v0, $t0, 12
/* 4B6BE48 80086080 000002A6 */  sh         $v0, 0x0($s0)
/* 4B6BE4C 80086084 0780013C */  lui        $at, %hi(D_8006CBF8)
/* 4B6BE50 80086088 21082300 */  addu       $at, $at, $v1
/* 4B6BE54 8008608C F8CB2284 */  lh         $v0, %lo(D_8006CBF8)($at)
/* 4B6BE58 80086090 00000000 */  nop
/* 4B6BE5C 80086094 18002202 */  mult       $s1, $v0
/* 4B6BE60 80086098 64000424 */  addiu      $a0, $zero, 0x64
/* 4B6BE64 8008609C 8C000524 */  addiu      $a1, $zero, 0x8C
/* 4B6BE68 800860A0 12400000 */  mflo       $t0
/* 4B6BE6C 800860A4 03130800 */  sra        $v0, $t0, 12
/* 4B6BE70 800860A8 A8DF000C */  jal        RandRange
/* 4B6BE74 800860AC 020002A6 */   sh        $v0, 0x2($s0)
/* 4B6BE78 800860B0 1E000424 */  addiu      $a0, $zero, 0x1E
/* 4B6BE7C 800860B4 32000524 */  addiu      $a1, $zero, 0x32
/* 4B6BE80 800860B8 A8DF000C */  jal        RandRange
/* 4B6BE84 800860BC 040002A6 */   sh        $v0, 0x4($s0)
/* 4B6BE88 800860C0 07000424 */  addiu      $a0, $zero, 0x7
/* 4B6BE8C 800860C4 0C000524 */  addiu      $a1, $zero, 0xC
/* 4B6BE90 800860C8 C4DF000C */  jal        RandRangeSigned
/* 4B6BE94 800860CC 0C0002AE */   sw        $v0, 0xC($s0)
/* 4B6BE98 800860D0 07000424 */  addiu      $a0, $zero, 0x7
/* 4B6BE9C 800860D4 0C000524 */  addiu      $a1, $zero, 0xC
/* 4B6BEA0 800860D8 C4DF000C */  jal        RandRangeSigned
/* 4B6BEA4 800860DC 060002A6 */   sh        $v0, 0x6($s0)
/* 4B6BEA8 800860E0 07000424 */  addiu      $a0, $zero, 0x7
/* 4B6BEAC 800860E4 0C000524 */  addiu      $a1, $zero, 0xC
/* 4B6BEB0 800860E8 C4DF000C */  jal        RandRangeSigned
/* 4B6BEB4 800860EC 080002A6 */   sh        $v0, 0x8($s0)
/* 4B6BEB8 800860F0 0A0002A6 */  sh         $v0, 0xA($s0)
/* 4B6BEBC 800860F4 3800A386 */  lh         $v1, 0x38($s5)
/* 4B6BEC0 800860F8 1400A28E */  lw         $v0, 0x14($s5)
/* 4B6BEC4 800860FC 00000000 */  nop
/* 4B6BEC8 80086100 23104300 */  subu       $v0, $v0, $v1
/* 4B6BECC 80086104 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 4B6BED0 80086108 100002AE */  sw         $v0, 0x10($s0)
/* 4B6BED4 8008610C 4B006292 */  lbu        $v0, 0x4B($s3)
/* 4B6BED8 80086110 CD180208 */  j          .Llevel_53_80086334
/* 4B6BEDC 80086114 0001033C */   lui       $v1, (0x1000000 >> 16)
.Llevel_53_80086118:
/* 4B6BEE0 80086118 0000708E */  lw         $s0, 0x0($s3)
/* 4B6BEE4 8008611C C8E9000C */  jal        func_8003A720
/* 4B6BEE8 80086120 21206002 */   addu      $a0, $s3, $zero
/* 4B6BEEC 80086124 AA49010C */  jal        func_800526A8
/* 4B6BEF0 80086128 21206002 */   addu      $a0, $s3, $zero
/* 4B6BEF4 8008612C 490060A2 */  sb         $zero, 0x49($s3)
/* 4B6BEF8 80086130 000000AE */  sw         $zero, 0x0($s0)
/* 4B6BEFC 80086134 080000A6 */  sh         $zero, 0x8($s0)
/* 4B6BF00 80086138 060000A6 */  sh         $zero, 0x6($s0)
/* 4B6BF04 8008613C 040000A6 */  sh         $zero, 0x4($s0)
/* 4B6BF08 80086140 0C0000AE */  sw         $zero, 0xC($s0)
/* 4B6BF0C 80086144 7801A012 */  beqz       $s5, .Llevel_53_80086728
/* 4B6BF10 80086148 100000AE */   sw        $zero, 0x10($s0)
/* 4B6BF14 8008614C 0C006426 */  addiu      $a0, $s3, 0xC
/* 4B6BF18 80086150 C05D000C */  jal        VecCopy
/* 4B6BF1C 80086154 0C00A526 */   addiu     $a1, $s5, 0xC
/* 4B6BF20 80086158 CB190208 */  j          .Llevel_53_8008672C
/* 4B6BF24 8008615C 21106002 */   addu      $v0, $s3, $zero
.Llevel_53_80086160:
/* 4B6BF28 80086160 C8E9000C */  jal        func_8003A720
/* 4B6BF2C 80086164 21206002 */   addu      $a0, $s3, $zero
/* 4B6BF30 80086168 21206002 */  addu       $a0, $s3, $zero
/* 4B6BF34 8008616C 20000224 */  addiu      $v0, $zero, 0x20
/* 4B6BF38 80086170 500062A2 */  sb         $v0, 0x50($s3)
/* 4B6BF3C 80086174 FF000224 */  addiu      $v0, $zero, 0xFF
/* 4B6BF40 80086178 734A010C */  jal        func_800529CC
/* 4B6BF44 8008617C 520062A2 */   sb        $v0, 0x52($s3)
/* 4B6BF48 80086180 0D000224 */  addiu      $v0, $zero, 0xD
/* 4B6BF4C 80086184 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 4B6BF50 80086188 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 4B6BF54 8008618C 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 4B6BF58 80086190 CA190208 */  j          .Llevel_53_80086728
/* 4B6BF5C 80086194 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_53_80086198:
/* 4B6BF60 80086198 0000748E */  lw         $s4, 0x0($s3)
/* 4B6BF64 8008619C C8E9000C */  jal        func_8003A720
/* 4B6BF68 800861A0 21206002 */   addu      $a0, $s3, $zero
/* 4B6BF6C 800861A4 0C006426 */  addiu      $a0, $s3, 0xC
/* 4B6BF70 800861A8 0C00A526 */  addiu      $a1, $s5, 0xC
/* 4B6BF74 800861AC 20000224 */  addiu      $v0, $zero, 0x20
/* 4B6BF78 800861B0 C05D000C */  jal        VecCopy
/* 4B6BF7C 800861B4 500062A2 */   sb        $v0, 0x50($s3)
/* 4B6BF80 800861B8 AA49010C */  jal        func_800526A8
/* 4B6BF84 800861BC 21206002 */   addu      $a0, $s3, $zero
/* 4B6BF88 800861C0 CB89010C */  jal        rand
/* 4B6BF8C 800861C4 00000000 */   nop
/* 4B6BF90 800861C8 CB89010C */  jal        rand
/* 4B6BF94 800861CC FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 4B6BF98 800861D0 FF075130 */  andi       $s1, $v0, 0x7FF
/* 4B6BF9C 800861D4 2C5B000C */  jal        Cos
/* 4B6BFA0 800861D8 21202002 */   addu      $a0, $s1, $zero
/* 4B6BFA4 800861DC 21204002 */  addu       $a0, $s2, $zero
/* 4B6BFA8 800861E0 2C5B000C */  jal        Cos
/* 4B6BFAC 800861E4 21804000 */   addu      $s0, $v0, $zero
/* 4B6BFB0 800861E8 43811000 */  sra        $s0, $s0, 5
/* 4B6BFB4 800861EC 18000202 */  mult       $s0, $v0
/* 4B6BFB8 800861F0 21202002 */  addu       $a0, $s1, $zero
/* 4B6BFBC 800861F4 12400000 */  mflo       $t0
/* 4B6BFC0 800861F8 03130800 */  sra        $v0, $t0, 12
/* 4B6BFC4 800861FC 2C5B000C */  jal        Cos
/* 4B6BFC8 80086200 000082A6 */   sh        $v0, 0x0($s4)
/* 4B6BFCC 80086204 21204002 */  addu       $a0, $s2, $zero
/* 4B6BFD0 80086208 165B000C */  jal        Sin
/* 4B6BFD4 8008620C 21804000 */   addu      $s0, $v0, $zero
/* 4B6BFD8 80086210 43811000 */  sra        $s0, $s0, 5
/* 4B6BFDC 80086214 18000202 */  mult       $s0, $v0
/* 4B6BFE0 80086218 21202002 */  addu       $a0, $s1, $zero
/* 4B6BFE4 8008621C 12400000 */  mflo       $t0
/* 4B6BFE8 80086220 03130800 */  sra        $v0, $t0, 12
/* 4B6BFEC 80086224 165B000C */  jal        Sin
/* 4B6BFF0 80086228 020082A6 */   sh        $v0, 0x2($s4)
/* 4B6BFF4 8008622C 43110200 */  sra        $v0, $v0, 5
/* 4B6BFF8 80086230 040082A6 */  sh         $v0, 0x4($s4)
/* 4B6BFFC 80086234 1800A28E */  lw         $v0, 0x18($s5)
/* 4B6C000 80086238 0200033C */  lui        $v1, (0x20000 >> 16)
/* 4B6C004 8008623C 24104300 */  and        $v0, $v0, $v1
/* 4B6C008 80086240 13004010 */  beqz       $v0, .Llevel_53_80086290
/* 4B6C00C 80086244 00000000 */   nop
/* 4B6C010 80086248 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 4B6C014 8008624C 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 4B6C018 80086250 00008396 */  lhu        $v1, 0x0($s4)
/* 4B6C01C 80086254 83110200 */  sra        $v0, $v0, 6
/* 4B6C020 80086258 21186200 */  addu       $v1, $v1, $v0
/* 4B6C024 8008625C 000083A6 */  sh         $v1, 0x0($s4)
/* 4B6C028 80086260 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 4B6C02C 80086264 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 4B6C030 80086268 02008396 */  lhu        $v1, 0x2($s4)
/* 4B6C034 8008626C 83110200 */  sra        $v0, $v0, 6
/* 4B6C038 80086270 21186200 */  addu       $v1, $v1, $v0
/* 4B6C03C 80086274 020083A6 */  sh         $v1, 0x2($s4)
/* 4B6C040 80086278 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 4B6C044 8008627C 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 4B6C048 80086280 04008396 */  lhu        $v1, 0x4($s4)
/* 4B6C04C 80086284 83110200 */  sra        $v0, $v0, 6
/* 4B6C050 80086288 21186200 */  addu       $v1, $v1, $v0
/* 4B6C054 8008628C 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_53_80086290:
/* 4B6C058 80086290 00008286 */  lh         $v0, 0x0($s4)
/* 4B6C05C 80086294 0C00638E */  lw         $v1, 0xC($s3)
/* 4B6C060 80086298 80100200 */  sll        $v0, $v0, 2
/* 4B6C064 8008629C 21186200 */  addu       $v1, $v1, $v0
/* 4B6C068 800862A0 0C0063AE */  sw         $v1, 0xC($s3)
/* 4B6C06C 800862A4 02008286 */  lh         $v0, 0x2($s4)
/* 4B6C070 800862A8 1000638E */  lw         $v1, 0x10($s3)
/* 4B6C074 800862AC 80100200 */  sll        $v0, $v0, 2
/* 4B6C078 800862B0 21186200 */  addu       $v1, $v1, $v0
/* 4B6C07C 800862B4 100063AE */  sw         $v1, 0x10($s3)
/* 4B6C080 800862B8 04008286 */  lh         $v0, 0x4($s4)
/* 4B6C084 800862BC 1400638E */  lw         $v1, 0x14($s3)
/* 4B6C088 800862C0 80100200 */  sll        $v0, $v0, 2
/* 4B6C08C 800862C4 21186200 */  addu       $v1, $v1, $v0
/* 4B6C090 800862C8 CB89010C */  jal        rand
/* 4B6C094 800862CC 140063AE */   sw        $v1, 0x14($s3)
/* 4B6C098 800862D0 0F004230 */  andi       $v0, $v0, 0xF
/* 4B6C09C 800862D4 CB89010C */  jal        rand
/* 4B6C0A0 800862D8 060082A6 */   sh        $v0, 0x6($s4)
/* 4B6C0A4 800862DC 0F004230 */  andi       $v0, $v0, 0xF
/* 4B6C0A8 800862E0 CB89010C */  jal        rand
/* 4B6C0AC 800862E4 080082A6 */   sh        $v0, 0x8($s4)
/* 4B6C0B0 800862E8 0F004230 */  andi       $v0, $v0, 0xF
/* 4B6C0B4 800862EC 0A0082A6 */  sh         $v0, 0xA($s4)
/* 4B6C0B8 800862F0 1400A28E */  lw         $v0, 0x14($s5)
/* 4B6C0BC 800862F4 00000000 */  nop
/* 4B6C0C0 800862F8 C0FF4224 */  addiu      $v0, $v0, -0x40
/* 4B6C0C4 800862FC CB89010C */  jal        rand
/* 4B6C0C8 80086300 100082AE */   sw        $v0, 0x10($s4)
/* 4B6C0CC 80086304 0F004230 */  andi       $v0, $v0, 0xF
/* 4B6C0D0 80086308 40000324 */  addiu      $v1, $zero, 0x40
/* 4B6C0D4 8008630C 23186200 */  subu       $v1, $v1, $v0
/* 4B6C0D8 80086310 0C0083AE */  sw         $v1, 0xC($s4)
/* 4B6C0DC 80086314 36006296 */  lhu        $v0, 0x36($s3)
/* 4B6C0E0 80086318 00000000 */  nop
/* 4B6C0E4 8008631C CBFE4224 */  addiu      $v0, $v0, -0x135
/* 4B6C0E8 80086320 0300422C */  sltiu      $v0, $v0, 0x3
/* 4B6C0EC 80086324 00014010 */  beqz       $v0, .Llevel_53_80086728
/* 4B6C0F0 80086328 A100033C */   lui       $v1, (0xA18618 >> 16)
/* 4B6C0F4 8008632C 4B006292 */  lbu        $v0, 0x4B($s3)
/* 4B6C0F8 80086330 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
.Llevel_53_80086334:
/* 4B6C0FC 80086334 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_53_80086338:
/* 4B6C100 80086338 80004234 */  ori        $v0, $v0, 0x80
/* 4B6C104 8008633C CA190208 */  j          .Llevel_53_80086728
/* 4B6C108 80086340 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_53_80086344:
/* 4B6C10C 80086344 0000718E */  lw         $s1, 0x0($s3)
/* 4B6C110 80086348 C8E9000C */  jal        func_8003A720
/* 4B6C114 8008634C 21206002 */   addu      $a0, $s3, $zero
/* 4B6C118 80086350 21206002 */  addu       $a0, $s3, $zero
/* 4B6C11C 80086354 20000224 */  addiu      $v0, $zero, 0x20
/* 4B6C120 80086358 500062A2 */  sb         $v0, 0x50($s3)
/* 4B6C124 8008635C FF000224 */  addiu      $v0, $zero, 0xFF
/* 4B6C128 80086360 734A010C */  jal        func_800529CC
/* 4B6C12C 80086364 520062A2 */   sb        $v0, 0x52($s3)
/* 4B6C130 80086368 0E000224 */  addiu      $v0, $zero, 0xE
/* 4B6C134 8008636C 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 4B6C138 80086370 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 4B6C13C 80086374 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 4B6C140 80086378 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 4B6C144 8008637C 0780033C */  lui        $v1, %hi(g_DragonCutscene + 0x28)
/* 4B6C148 80086380 5870638C */  lw         $v1, %lo(g_DragonCutscene + 0x28)($v1)
/* 4B6C14C 80086384 03000224 */  addiu      $v0, $zero, 0x3
/* 4B6C150 80086388 03006214 */  bne        $v1, $v0, .Llevel_53_80086398
/* 4B6C154 8008638C 01000224 */   addiu     $v0, $zero, 0x1
/* 4B6C158 80086390 E8180208 */  j          .Llevel_53_800863A0
/* 4B6C15C 80086394 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_53_80086398:
/* 4B6C160 80086398 02006214 */  bne        $v1, $v0, .Llevel_53_800863A4
/* 4B6C164 8008639C 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_53_800863A0:
/* 4B6C168 800863A0 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_53_800863A4:
/* 4B6C16C 800863A4 CB89010C */  jal        rand
/* 4B6C170 800863A8 00000000 */   nop
/* 4B6C174 800863AC 2000A426 */  addiu      $a0, $s5, 0x20
/* 4B6C178 800863B0 07004230 */  andi       $v0, $v0, 0x7
/* 4B6C17C 800863B4 80100200 */  sll        $v0, $v0, 2
/* 4B6C180 800863B8 2000B027 */  addiu      $s0, $sp, 0x20
/* 4B6C184 800863BC 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 4B6C188 800863C0 21082200 */  addu       $at, $at, $v0
/* 4B6C18C 800863C4 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 4B6C190 800863C8 21280002 */  addu       $a1, $s0, $zero
/* 4B6C194 800863CC 2400A0AF */  sw         $zero, 0x24($sp)
/* 4B6C198 800863D0 2000A3AF */  sw         $v1, 0x20($sp)
/* 4B6C19C 800863D4 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 4B6C1A0 800863D8 21082200 */  addu       $at, $at, $v0
/* 4B6C1A4 800863DC A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 4B6C1A8 800863E0 21300002 */  addu       $a2, $s0, $zero
/* 4B6C1AC 800863E4 125C000C */  jal        VecRotateByMatrix
/* 4B6C1B0 800863E8 2800A2AF */   sw        $v0, 0x28($sp)
/* 4B6C1B4 800863EC CB89010C */  jal        rand
/* 4B6C1B8 800863F0 00000000 */   nop
/* 4B6C1BC 800863F4 2000A38F */  lw         $v1, 0x20($sp)
/* 4B6C1C0 800863F8 7F004230 */  andi       $v0, $v0, 0x7F
/* 4B6C1C4 800863FC C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 4B6C1C8 80086400 21186200 */  addu       $v1, $v1, $v0
/* 4B6C1CC 80086404 CB89010C */  jal        rand
/* 4B6C1D0 80086408 2000A3AF */   sw        $v1, 0x20($sp)
/* 4B6C1D4 8008640C 2400A38F */  lw         $v1, 0x24($sp)
/* 4B6C1D8 80086410 7F004230 */  andi       $v0, $v0, 0x7F
/* 4B6C1DC 80086414 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 4B6C1E0 80086418 21186200 */  addu       $v1, $v1, $v0
/* 4B6C1E4 8008641C CB89010C */  jal        rand
/* 4B6C1E8 80086420 2400A3AF */   sw        $v1, 0x24($sp)
/* 4B6C1EC 80086424 0C006426 */  addiu      $a0, $s3, 0xC
/* 4B6C1F0 80086428 0C00A526 */  addiu      $a1, $s5, 0xC
/* 4B6C1F4 8008642C 21300002 */  addu       $a2, $s0, $zero
/* 4B6C1F8 80086430 2800A38F */  lw         $v1, 0x28($sp)
/* 4B6C1FC 80086434 7F004230 */  andi       $v0, $v0, 0x7F
/* 4B6C200 80086438 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 4B6C204 8008643C 21186200 */  addu       $v1, $v1, $v0
/* 4B6C208 80086440 D65D000C */  jal        VecAdd
/* 4B6C20C 80086444 2800A3AF */   sw        $v1, 0x28($sp)
/* 4B6C210 80086448 21202002 */  addu       $a0, $s1, $zero
/* 4B6C214 8008644C C05D000C */  jal        VecCopy
/* 4B6C218 80086450 21280002 */   addu      $a1, $s0, $zero
/* 4B6C21C 80086454 21202002 */  addu       $a0, $s1, $zero
/* 4B6C220 80086458 B25D000C */  jal        VecShiftRight
/* 4B6C224 8008645C 02000524 */   addiu     $a1, $zero, 0x2
/* 4B6C228 80086460 CB89010C */  jal        rand
/* 4B6C22C 80086464 00000000 */   nop
/* 4B6C230 80086468 0000238E */  lw         $v1, 0x0($s1)
/* 4B6C234 8008646C FF004230 */  andi       $v0, $v0, 0xFF
/* 4B6C238 80086470 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 4B6C23C 80086474 21186200 */  addu       $v1, $v1, $v0
/* 4B6C240 80086478 CB89010C */  jal        rand
/* 4B6C244 8008647C 000023AE */   sw        $v1, 0x0($s1)
/* 4B6C248 80086480 0400238E */  lw         $v1, 0x4($s1)
/* 4B6C24C 80086484 FF004230 */  andi       $v0, $v0, 0xFF
/* 4B6C250 80086488 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 4B6C254 8008648C 21186200 */  addu       $v1, $v1, $v0
/* 4B6C258 80086490 CB89010C */  jal        rand
/* 4B6C25C 80086494 040023AE */   sw        $v1, 0x4($s1)
/* 4B6C260 80086498 0800238E */  lw         $v1, 0x8($s1)
/* 4B6C264 8008649C FF004230 */  andi       $v0, $v0, 0xFF
/* 4B6C268 800864A0 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 4B6C26C 800864A4 21186200 */  addu       $v1, $v1, $v0
/* 4B6C270 800864A8 CB89010C */  jal        rand
/* 4B6C274 800864AC 080023AE */   sw        $v1, 0x8($s1)
/* 4B6C278 800864B0 CB89010C */  jal        rand
/* 4B6C27C 800864B4 440062A2 */   sb        $v0, 0x44($s3)
/* 4B6C280 800864B8 CB89010C */  jal        rand
/* 4B6C284 800864BC 450062A2 */   sb        $v0, 0x45($s3)
/* 4B6C288 800864C0 CB89010C */  jal        rand
/* 4B6C28C 800864C4 460062A2 */   sb        $v0, 0x46($s3)
/* 4B6C290 800864C8 0F004230 */  andi       $v0, $v0, 0xF
/* 4B6C294 800864CC CB89010C */  jal        rand
/* 4B6C298 800864D0 100022A2 */   sb        $v0, 0x10($s1)
/* 4B6C29C 800864D4 0F004230 */  andi       $v0, $v0, 0xF
/* 4B6C2A0 800864D8 CB89010C */  jal        rand
/* 4B6C2A4 800864DC 110022A2 */   sb        $v0, 0x11($s1)
/* 4B6C2A8 800864E0 0F004230 */  andi       $v0, $v0, 0xF
/* 4B6C2AC 800864E4 120022A2 */  sb         $v0, 0x12($s1)
/* 4B6C2B0 800864E8 1400A28E */  lw         $v0, 0x14($s5)
/* 4B6C2B4 800864EC CB89010C */  jal        rand
/* 4B6C2B8 800864F0 0C0022AE */   sw        $v0, 0xC($s1)
/* 4B6C2BC 800864F4 03004230 */  andi       $v0, $v0, 0x3
/* 4B6C2C0 800864F8 10004224 */  addiu      $v0, $v0, 0x10
/* 4B6C2C4 800864FC CA190208 */  j          .Llevel_53_80086728
/* 4B6C2C8 80086500 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_53_80086504:
/* 4B6C2CC 80086504 0000708E */  lw         $s0, 0x0($s3)
/* 4B6C2D0 80086508 C8E9000C */  jal        func_8003A720
/* 4B6C2D4 8008650C 21206002 */   addu      $a0, $s3, $zero
/* 4B6C2D8 80086510 734A010C */  jal        func_800529CC
/* 4B6C2DC 80086514 21206002 */   addu      $a0, $s3, $zero
/* 4B6C2E0 80086518 02000224 */  addiu      $v0, $zero, 0x2
/* 4B6C2E4 8008651C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 4B6C2E8 80086520 40000224 */  addiu      $v0, $zero, 0x40
/* 4B6C2EC 80086524 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 4B6C2F0 80086528 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 4B6C2F4 8008652C 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 4B6C2F8 80086530 CA190208 */  j          .Llevel_53_80086728
/* 4B6C2FC 80086534 000002AE */   sw        $v0, 0x0($s0)
.Llevel_53_80086538:
/* 4B6C300 80086538 C8E9000C */  jal        func_8003A720
/* 4B6C304 8008653C 21206002 */   addu      $a0, $s3, $zero
/* 4B6C308 80086540 05000224 */  addiu      $v0, $zero, 0x5
/* 4B6C30C 80086544 7100A012 */  beqz       $s5, .Llevel_53_8008670C
/* 4B6C310 80086548 470062A2 */   sb        $v0, 0x47($s3)
/* 4B6C314 8008654C 0C006426 */  addiu      $a0, $s3, 0xC
/* 4B6C318 80086550 C6190208 */  j          .Llevel_53_80086718
/* 4B6C31C 80086554 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_53_80086558:
/* 4B6C320 80086558 C8E9000C */  jal        func_8003A720
/* 4B6C324 8008655C 21206002 */   addu      $a0, $s3, $zero
/* 4B6C328 80086560 0300A012 */  beqz       $s5, .Llevel_53_80086570
/* 4B6C32C 80086564 0C006426 */   addiu     $a0, $s3, 0xC
/* 4B6C330 80086568 5E190208 */  j          .Llevel_53_80086578
/* 4B6C334 8008656C 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_53_80086570:
/* 4B6C338 80086570 0880053C */  lui        $a1, %hi(g_Spyro)
/* 4B6C33C 80086574 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_53_80086578:
/* 4B6C340 80086578 C05D000C */  jal        VecCopy
/* 4B6C344 8008657C 00000000 */   nop
/* 4B6C348 80086580 0C006426 */  addiu      $a0, $s3, 0xC
/* 4B6C34C 80086584 1400628E */  lw         $v0, 0x14($s3)
/* 4B6C350 80086588 00080524 */  addiu      $a1, $zero, 0x800
/* 4B6C354 8008658C 00024224 */  addiu      $v0, $v0, 0x200
/* 4B6C358 80086590 7B35010C */  jal        func_8004D5EC
/* 4B6C35C 80086594 140062AE */   sw        $v0, 0x14($s3)
/* 4B6C360 80086598 1400648E */  lw         $a0, 0x14($s3)
/* 4B6C364 8008659C 21184000 */  addu       $v1, $v0, $zero
/* 4B6C368 800865A0 23106400 */  subu       $v0, $v1, $a0
/* 4B6C36C 800865A4 02004104 */  bgez       $v0, .Llevel_53_800865B0
/* 4B6C370 800865A8 00000000 */   nop
/* 4B6C374 800865AC 23100200 */  negu       $v0, $v0
.Llevel_53_800865B0:
/* 4B6C378 800865B0 00084228 */  slti       $v0, $v0, 0x800
/* 4B6C37C 800865B4 03004010 */  beqz       $v0, .Llevel_53_800865C4
/* 4B6C380 800865B8 00FE8224 */   addiu     $v0, $a0, -0x200
/* 4B6C384 800865BC C8190208 */  j          .Llevel_53_80086720
/* 4B6C388 800865C0 140063AE */   sw        $v1, 0x14($s3)
.Llevel_53_800865C4:
/* 4B6C38C 800865C4 C8190208 */  j          .Llevel_53_80086720
/* 4B6C390 800865C8 140062AE */   sw        $v0, 0x14($s3)
.Llevel_53_800865CC:
/* 4B6C394 800865CC C8E9000C */  jal        func_8003A720
/* 4B6C398 800865D0 21206002 */   addu      $a0, $s3, $zero
/* 4B6C39C 800865D4 21206002 */  addu       $a0, $s3, $zero
/* 4B6C3A0 800865D8 20000224 */  addiu      $v0, $zero, 0x20
/* 4B6C3A4 800865DC 500062A2 */  sb         $v0, 0x50($s3)
/* 4B6C3A8 800865E0 FF000224 */  addiu      $v0, $zero, 0xFF
/* 4B6C3AC 800865E4 734A010C */  jal        func_800529CC
/* 4B6C3B0 800865E8 520062A2 */   sb        $v0, 0x52($s3)
/* 4B6C3B4 800865EC CB190208 */  j          .Llevel_53_8008672C
/* 4B6C3B8 800865F0 21106002 */   addu      $v0, $s3, $zero
.Llevel_53_800865F4:
/* 4B6C3BC 800865F4 0000708E */  lw         $s0, 0x0($s3)
/* 4B6C3C0 800865F8 C8E9000C */  jal        func_8003A720
/* 4B6C3C4 800865FC 21206002 */   addu      $a0, $s3, $zero
/* 4B6C3C8 80086600 0C006426 */  addiu      $a0, $s3, 0xC
/* 4B6C3CC 80086604 0C00A526 */  addiu      $a1, $s5, 0xC
/* 4B6C3D0 80086608 20000224 */  addiu      $v0, $zero, 0x20
/* 4B6C3D4 8008660C C05D000C */  jal        VecCopy
/* 4B6C3D8 80086610 500062A2 */   sb        $v0, 0x50($s3)
/* 4B6C3DC 80086614 AA49010C */  jal        func_800526A8
/* 4B6C3E0 80086618 21206002 */   addu      $a0, $s3, $zero
/* 4B6C3E4 8008661C 3600A386 */  lh         $v1, 0x36($s5)
/* 4B6C3E8 80086620 B0000224 */  addiu      $v0, $zero, 0xB0
/* 4B6C3EC 80086624 0B006214 */  bne        $v1, $v0, .Llevel_53_80086654
/* 4B6C3F0 80086628 6AFF0424 */   addiu     $a0, $zero, -0x96
/* 4B6C3F4 8008662C 9CFF0424 */  addiu      $a0, $zero, -0x64
/* 4B6C3F8 80086630 A8DF000C */  jal        RandRange
/* 4B6C3FC 80086634 64000524 */   addiu     $a1, $zero, 0x64
/* 4B6C400 80086638 9CFF0424 */  addiu      $a0, $zero, -0x64
/* 4B6C404 8008663C 64000524 */  addiu      $a1, $zero, 0x64
/* 4B6C408 80086640 A8DF000C */  jal        RandRange
/* 4B6C40C 80086644 000002A6 */   sh        $v0, 0x0($s0)
/* 4B6C410 80086648 C4FF0424 */  addiu      $a0, $zero, -0x3C
/* 4B6C414 8008664C 9D190208 */  j          .Llevel_53_80086674
/* 4B6C418 80086650 6E000524 */   addiu     $a1, $zero, 0x6E
.Llevel_53_80086654:
/* 4B6C41C 80086654 A8DF000C */  jal        RandRange
/* 4B6C420 80086658 96000524 */   addiu     $a1, $zero, 0x96
/* 4B6C424 8008665C 6AFF0424 */  addiu      $a0, $zero, -0x96
/* 4B6C428 80086660 96000524 */  addiu      $a1, $zero, 0x96
/* 4B6C42C 80086664 A8DF000C */  jal        RandRange
/* 4B6C430 80086668 000002A6 */   sh        $v0, 0x0($s0)
/* 4B6C434 8008666C BAFF0424 */  addiu      $a0, $zero, -0x46
/* 4B6C438 80086670 96000524 */  addiu      $a1, $zero, 0x96
.Llevel_53_80086674:
/* 4B6C43C 80086674 A8DF000C */  jal        RandRange
/* 4B6C440 80086678 020002A6 */   sh        $v0, 0x2($s0)
/* 4B6C444 8008667C 040002A6 */  sh         $v0, 0x4($s0)
/* 4B6C448 80086680 00000286 */  lh         $v0, 0x0($s0)
/* 4B6C44C 80086684 0C00638E */  lw         $v1, 0xC($s3)
/* 4B6C450 80086688 80100200 */  sll        $v0, $v0, 2
/* 4B6C454 8008668C 21186200 */  addu       $v1, $v1, $v0
/* 4B6C458 80086690 0C0063AE */  sw         $v1, 0xC($s3)
/* 4B6C45C 80086694 02000286 */  lh         $v0, 0x2($s0)
/* 4B6C460 80086698 1000638E */  lw         $v1, 0x10($s3)
/* 4B6C464 8008669C 80100200 */  sll        $v0, $v0, 2
/* 4B6C468 800866A0 21186200 */  addu       $v1, $v1, $v0
/* 4B6C46C 800866A4 100063AE */  sw         $v1, 0x10($s3)
/* 4B6C470 800866A8 04000286 */  lh         $v0, 0x4($s0)
/* 4B6C474 800866AC 1400638E */  lw         $v1, 0x14($s3)
/* 4B6C478 800866B0 80100200 */  sll        $v0, $v0, 2
/* 4B6C47C 800866B4 21186200 */  addu       $v1, $v1, $v0
/* 4B6C480 800866B8 CB89010C */  jal        rand
/* 4B6C484 800866BC 140063AE */   sw        $v1, 0x14($s3)
/* 4B6C488 800866C0 0F004230 */  andi       $v0, $v0, 0xF
/* 4B6C48C 800866C4 CB89010C */  jal        rand
/* 4B6C490 800866C8 060002A6 */   sh        $v0, 0x6($s0)
/* 4B6C494 800866CC 0F004230 */  andi       $v0, $v0, 0xF
/* 4B6C498 800866D0 CB89010C */  jal        rand
/* 4B6C49C 800866D4 080002A6 */   sh        $v0, 0x8($s0)
/* 4B6C4A0 800866D8 18000424 */  addiu      $a0, $zero, 0x18
/* 4B6C4A4 800866DC 23000524 */  addiu      $a1, $zero, 0x23
/* 4B6C4A8 800866E0 0F004230 */  andi       $v0, $v0, 0xF
/* 4B6C4AC 800866E4 A8DF000C */  jal        RandRange
/* 4B6C4B0 800866E8 0A0002A6 */   sh        $v0, 0xA($s0)
/* 4B6C4B4 800866EC CA190208 */  j          .Llevel_53_80086728
/* 4B6C4B8 800866F0 0C0002AE */   sw        $v0, 0xC($s0)
.Llevel_53_800866F4:
/* 4B6C4BC 800866F4 C8E9000C */  jal        func_8003A720
/* 4B6C4C0 800866F8 21206002 */   addu      $a0, $s3, $zero
/* 4B6C4C4 800866FC 0300A012 */  beqz       $s5, .Llevel_53_8008670C
/* 4B6C4C8 80086700 0C00A526 */   addiu     $a1, $s5, 0xC
/* 4B6C4CC 80086704 C6190208 */  j          .Llevel_53_80086718
/* 4B6C4D0 80086708 0C006426 */   addiu     $a0, $s3, 0xC
.Llevel_53_8008670C:
/* 4B6C4D4 8008670C 0C006426 */  addiu      $a0, $s3, 0xC
/* 4B6C4D8 80086710 0880053C */  lui        $a1, %hi(g_Spyro)
/* 4B6C4DC 80086714 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_53_80086718:
/* 4B6C4E0 80086718 C05D000C */  jal        VecCopy
/* 4B6C4E4 8008671C 00000000 */   nop
.Llevel_53_80086720:
/* 4B6C4E8 80086720 AA49010C */  jal        func_800526A8
/* 4B6C4EC 80086724 21206002 */   addu      $a0, $s3, $zero
.Llevel_53_80086728:
/* 4B6C4F0 80086728 21106002 */  addu       $v0, $s3, $zero
.Llevel_53_8008672C:
/* 4B6C4F4 8008672C 5000BF8F */  lw         $ra, 0x50($sp)
/* 4B6C4F8 80086730 4C00B58F */  lw         $s5, 0x4C($sp)
/* 4B6C4FC 80086734 4800B48F */  lw         $s4, 0x48($sp)
/* 4B6C500 80086738 4400B38F */  lw         $s3, 0x44($sp)
/* 4B6C504 8008673C 4000B28F */  lw         $s2, 0x40($sp)
/* 4B6C508 80086740 3C00B18F */  lw         $s1, 0x3C($sp)
/* 4B6C50C 80086744 3800B08F */  lw         $s0, 0x38($sp)
/* 4B6C510 80086748 5800BD27 */  addiu      $sp, $sp, 0x58
/* 4B6C514 8008674C 0800E003 */  jr         $ra
/* 4B6C518 80086750 00000000 */   nop
.size func_level_53_8008590C, . - func_level_53_8008590C
