.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_10_800857CC
/* 7FD594 800857CC A8FFBD27 */  addiu      $sp, $sp, -0x58
/* 7FD598 800857D0 3800B0AF */  sw         $s0, 0x38($sp)
/* 7FD59C 800857D4 21808000 */  addu       $s0, $a0, $zero
/* 7FD5A0 800857D8 4C00B5AF */  sw         $s5, 0x4C($sp)
/* 7FD5A4 800857DC 21A8A000 */  addu       $s5, $a1, $zero
/* 7FD5A8 800857E0 5000BFAF */  sw         $ra, 0x50($sp)
/* 7FD5AC 800857E4 4800B4AF */  sw         $s4, 0x48($sp)
/* 7FD5B0 800857E8 4400B3AF */  sw         $s3, 0x44($sp)
/* 7FD5B4 800857EC 4000B2AF */  sw         $s2, 0x40($sp)
/* 7FD5B8 800857F0 3149010C */  jal        func_800524C4
/* 7FD5BC 800857F4 3C00B1AF */   sw        $s1, 0x3C($sp)
/* 7FD5C0 800857F8 21984000 */  addu       $s3, $v0, $zero
/* 7FD5C4 800857FC 1400A012 */  beqz       $s5, .Llevel_10_80085850
/* 7FD5C8 80085800 360070A6 */   sh        $s0, 0x36($s3)
/* 7FD5CC 80085804 0780043C */  lui        $a0, %hi(D_80075828)
/* 7FD5D0 80085808 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* 7FD5D4 8008580C 00000000 */  nop
/* 7FD5D8 80085810 2320A402 */  subu       $a0, $s5, $a0
/* 7FD5DC 80085814 40190400 */  sll        $v1, $a0, 5
/* 7FD5E0 80085818 23186400 */  subu       $v1, $v1, $a0
/* 7FD5E4 8008581C 40190300 */  sll        $v1, $v1, 5
/* 7FD5E8 80085820 21186400 */  addu       $v1, $v1, $a0
/* 7FD5EC 80085824 C0100300 */  sll        $v0, $v1, 3
/* 7FD5F0 80085828 21186200 */  addu       $v1, $v1, $v0
/* 7FD5F4 8008582C C0130300 */  sll        $v0, $v1, 15
/* 7FD5F8 80085830 23104300 */  subu       $v0, $v0, $v1
/* 7FD5FC 80085834 80100200 */  sll        $v0, $v0, 2
/* 7FD600 80085838 21104400 */  addu       $v0, $v0, $a0
/* 7FD604 8008583C 23100200 */  negu       $v0, $v0
/* 7FD608 80085840 C3180200 */  sra        $v1, $v0, 3
/* 7FD60C 80085844 0001622C */  sltiu      $v0, $v1, 0x100
/* 7FD610 80085848 03004014 */  bnez       $v0, .Llevel_10_80085858
/* 7FD614 8008584C 0201022A */   slti      $v0, $s0, 0x102
.Llevel_10_80085850:
/* 7FD618 80085850 21180000 */  addu       $v1, $zero, $zero
/* 7FD61C 80085854 0201022A */  slti       $v0, $s0, 0x102
.Llevel_10_80085858:
/* 7FD620 80085858 27004010 */  beqz       $v0, .Llevel_10_800858F8
/* 7FD624 8008585C 560063A2 */   sb        $v1, 0x56($s3)
/* 7FD628 80085860 FF00022A */  slti       $v0, $s0, 0xFF
/* 7FD62C 80085864 F9004010 */  beqz       $v0, .Llevel_10_80085C4C
/* 7FD630 80085868 4C000224 */   addiu     $v0, $zero, 0x4C
/* 7FD634 8008586C 0F020212 */  beq        $s0, $v0, .Llevel_10_800860AC
/* 7FD638 80085870 4D00022A */   slti      $v0, $s0, 0x4D
/* 7FD63C 80085874 10004010 */  beqz       $v0, .Llevel_10_800858B8
/* 7FD640 80085878 0F000224 */   addiu     $v0, $zero, 0xF
/* 7FD644 8008587C 42000212 */  beq        $s0, $v0, .Llevel_10_80085988
/* 7FD648 80085880 1000022A */   slti      $v0, $s0, 0x10
/* 7FD64C 80085884 05004010 */  beqz       $v0, .Llevel_10_8008589C
/* 7FD650 80085888 0E000224 */   addiu     $v0, $zero, 0xE
/* 7FD654 8008588C 87000212 */  beq        $s0, $v0, .Llevel_10_80085AAC
/* 7FD658 80085890 00000000 */   nop
/* 7FD65C 80085894 35180208 */  j          .Llevel_10_800860D4
/* 7FD660 80085898 00000000 */   nop
.Llevel_10_8008589C:
/* 7FD664 8008589C 10000224 */  addiu      $v0, $zero, 0x10
/* 7FD668 800858A0 60000212 */  beq        $s0, $v0, .Llevel_10_80085A24
/* 7FD66C 800858A4 22000224 */   addiu     $v0, $zero, 0x22
/* 7FD670 800858A8 72000212 */  beq        $s0, $v0, .Llevel_10_80085A74
/* 7FD674 800858AC 00000000 */   nop
/* 7FD678 800858B0 35180208 */  j          .Llevel_10_800860D4
/* 7FD67C 800858B4 00000000 */   nop
.Llevel_10_800858B8:
/* 7FD680 800858B8 78000224 */  addiu      $v0, $zero, 0x78
/* 7FD684 800858BC D1000212 */  beq        $s0, $v0, .Llevel_10_80085C04
/* 7FD688 800858C0 7900022A */   slti      $v0, $s0, 0x79
/* 7FD68C 800858C4 07004010 */  beqz       $v0, .Llevel_10_800858E4
/* 7FD690 800858C8 5800022A */   slti      $v0, $s0, 0x58
/* 7FD694 800858CC 01024010 */  beqz       $v0, .Llevel_10_800860D4
/* 7FD698 800858D0 5300022A */   slti      $v0, $s0, 0x53
/* 7FD69C 800858D4 75004010 */  beqz       $v0, .Llevel_10_80085AAC
/* 7FD6A0 800858D8 00000000 */   nop
/* 7FD6A4 800858DC 35180208 */  j          .Llevel_10_800860D4
/* 7FD6A8 800858E0 00000000 */   nop
.Llevel_10_800858E4:
/* 7FD6AC 800858E4 FB000224 */  addiu      $v0, $zero, 0xFB
/* 7FD6B0 800858E8 43010212 */  beq        $s0, $v0, .Llevel_10_80085DF8
/* 7FD6B4 800858EC 00000000 */   nop
/* 7FD6B8 800858F0 35180208 */  j          .Llevel_10_800860D4
/* 7FD6BC 800858F4 00000000 */   nop
.Llevel_10_800858F8:
/* 7FD6C0 800858F8 95010224 */  addiu      $v0, $zero, 0x195
/* 7FD6C4 800858FC CE010212 */  beq        $s0, $v0, .Llevel_10_80086038
/* 7FD6C8 80085900 9601022A */   slti      $v0, $s0, 0x196
/* 7FD6CC 80085904 12004010 */  beqz       $v0, .Llevel_10_80085950
/* 7FD6D0 80085908 15010224 */   addiu     $v0, $zero, 0x115
/* 7FD6D4 8008590C AA010212 */  beq        $s0, $v0, .Llevel_10_80085FB8
/* 7FD6D8 80085910 1601022A */   slti      $v0, $s0, 0x116
/* 7FD6DC 80085914 07004010 */  beqz       $v0, .Llevel_10_80085934
/* 7FD6E0 80085918 0E01022A */   slti      $v0, $s0, 0x10E
/* 7FD6E4 8008591C ED014010 */  beqz       $v0, .Llevel_10_800860D4
/* 7FD6E8 80085920 0401022A */   slti      $v0, $s0, 0x104
/* 7FD6EC 80085924 A4014010 */  beqz       $v0, .Llevel_10_80085FB8
/* 7FD6F0 80085928 00000000 */   nop
/* 7FD6F4 8008592C 35180208 */  j          .Llevel_10_800860D4
/* 7FD6F8 80085930 00000000 */   nop
.Llevel_10_80085934:
/* 7FD6FC 80085934 47010224 */  addiu      $v0, $zero, 0x147
/* 7FD700 80085938 9F010212 */  beq        $s0, $v0, .Llevel_10_80085FB8
/* 7FD704 8008593C 8E010224 */   addiu     $v0, $zero, 0x18E
/* 7FD708 80085940 AA010212 */  beq        $s0, $v0, .Llevel_10_80085FEC
/* 7FD70C 80085944 00000000 */   nop
/* 7FD710 80085948 35180208 */  j          .Llevel_10_800860D4
/* 7FD714 8008594C 00000000 */   nop
.Llevel_10_80085950:
/* 7FD718 80085950 C401022A */  slti       $v0, $s0, 0x1C4
/* 7FD71C 80085954 07004010 */  beqz       $v0, .Llevel_10_80085974
/* 7FD720 80085958 AA01022A */   slti      $v0, $s0, 0x1AA
/* 7FD724 8008595C D3014010 */  beqz       $v0, .Llevel_10_800860AC
/* 7FD728 80085960 A701022A */   slti      $v0, $s0, 0x1A7
/* 7FD72C 80085964 B9004010 */  beqz       $v0, .Llevel_10_80085C4C
/* 7FD730 80085968 00000000 */   nop
/* 7FD734 8008596C 35180208 */  j          .Llevel_10_800860D4
/* 7FD738 80085970 00000000 */   nop
.Llevel_10_80085974:
/* 7FD73C 80085974 DD010224 */  addiu      $v0, $zero, 0x1DD
/* 7FD740 80085978 AF010212 */  beq        $s0, $v0, .Llevel_10_80086038
/* 7FD744 8008597C 00000000 */   nop
/* 7FD748 80085980 35180208 */  j          .Llevel_10_800860D4
/* 7FD74C 80085984 00000000 */   nop
.Llevel_10_80085988:
/* 7FD750 80085988 0000708E */  lw         $s0, 0x0($s3)
/* 7FD754 8008598C C8E9000C */  jal        func_8003A720
/* 7FD758 80085990 21206002 */   addu      $a0, $s3, $zero
/* 7FD75C 80085994 8C000224 */  addiu      $v0, $zero, 0x8C
/* 7FD760 80085998 080002AE */  sw         $v0, 0x8($s0)
/* 7FD764 8008599C 03000224 */  addiu      $v0, $zero, 0x3
/* 7FD768 800859A0 100002A2 */  sb         $v0, 0x10($s0)
/* 7FD76C 800859A4 FF000224 */  addiu      $v0, $zero, 0xFF
/* 7FD770 800859A8 140002A2 */  sb         $v0, 0x14($s0)
/* 7FD774 800859AC 02000224 */  addiu      $v0, $zero, 0x2
/* 7FD778 800859B0 000000AE */  sw         $zero, 0x0($s0)
/* 7FD77C 800859B4 040000AE */  sw         $zero, 0x4($s0)
/* 7FD780 800859B8 0E0000A2 */  sb         $zero, 0xE($s0)
/* 7FD784 800859BC 0F0000A2 */  sb         $zero, 0xF($s0)
/* 7FD788 800859C0 110000A2 */  sb         $zero, 0x11($s0)
/* 7FD78C 800859C4 120000A2 */  sb         $zero, 0x12($s0)
/* 7FD790 800859C8 130000A2 */  sb         $zero, 0x13($s0)
/* 7FD794 800859CC 490062A2 */  sb         $v0, 0x49($s3)
/* 7FD798 800859D0 18000224 */  addiu      $v0, $zero, 0x18
/* 7FD79C 800859D4 500062A2 */  sb         $v0, 0x50($s3)
/* 7FD7A0 800859D8 10000224 */  addiu      $v0, $zero, 0x10
/* 7FD7A4 800859DC 520062A2 */  sb         $v0, 0x52($s3)
/* 7FD7A8 800859E0 20000224 */  addiu      $v0, $zero, 0x20
/* 7FD7AC 800859E4 440062A2 */  sb         $v0, 0x44($s3)
/* 7FD7B0 800859E8 450060A2 */  sb         $zero, 0x45($s3)
/* 7FD7B4 800859EC 0400A012 */  beqz       $s5, .Llevel_10_80085A00
/* 7FD7B8 800859F0 460060A2 */   sb        $zero, 0x46($s3)
/* 7FD7BC 800859F4 0C006426 */  addiu      $a0, $s3, 0xC
/* 7FD7C0 800859F8 C05D000C */  jal        VecCopy
/* 7FD7C4 800859FC 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_10_80085A00:
/* 7FD7C8 80085A00 AA49010C */  jal        func_800526A8
/* 7FD7CC 80085A04 21206002 */   addu      $a0, $s3, $zero
/* 7FD7D0 80085A08 4B006292 */  lbu        $v0, 0x4B($s3)
/* 7FD7D4 80085A0C 01000324 */  addiu      $v1, $zero, 0x1
/* 7FD7D8 80085A10 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 7FD7DC 80085A14 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 7FD7E0 80085A18 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 7FD7E4 80085A1C 7B170208 */  j          .Llevel_10_80085DEC
/* 7FD7E8 80085A20 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_10_80085A24:
/* 7FD7EC 80085A24 0000718E */  lw         $s1, 0x0($s3)
/* 7FD7F0 80085A28 C8E9000C */  jal        func_8003A720
/* 7FD7F4 80085A2C 21206002 */   addu      $a0, $s3, $zero
/* 7FD7F8 80085A30 AA49010C */  jal        func_800526A8
/* 7FD7FC 80085A34 21206002 */   addu      $a0, $s3, $zero
/* 7FD800 80085A38 0C007026 */  addiu      $s0, $s3, 0xC
/* 7FD804 80085A3C 21200002 */  addu       $a0, $s0, $zero
/* 7FD808 80085A40 C05D000C */  jal        VecCopy
/* 7FD80C 80085A44 0C00A526 */   addiu     $a1, $s5, 0xC
/* 7FD810 80085A48 21280002 */  addu       $a1, $s0, $zero
/* 7FD814 80085A4C 1400628E */  lw         $v0, 0x14($s3)
/* 7FD818 80085A50 04002426 */  addiu      $a0, $s1, 0x4
/* 7FD81C 80085A54 00024224 */  addiu      $v0, $v0, 0x200
/* 7FD820 80085A58 C05D000C */  jal        VecCopy
/* 7FD824 80085A5C 140062AE */   sw        $v0, 0x14($s3)
/* 7FD828 80085A60 08070224 */  addiu      $v0, $zero, 0x708
/* 7FD82C 80085A64 130020A2 */  sb         $zero, 0x13($s1)
/* 7FD830 80085A68 120020A2 */  sb         $zero, 0x12($s1)
/* 7FD834 80085A6C 42180208 */  j          .Llevel_10_80086108
/* 7FD838 80085A70 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_10_80085A74:
/* 7FD83C 80085A74 C8E9000C */  jal        func_8003A720
/* 7FD840 80085A78 21206002 */   addu      $a0, $s3, $zero
/* 7FD844 80085A7C 20000224 */  addiu      $v0, $zero, 0x20
/* 7FD848 80085A80 500062A2 */  sb         $v0, 0x50($s3)
/* 7FD84C 80085A84 FF000224 */  addiu      $v0, $zero, 0xFF
/* 7FD850 80085A88 0400A012 */  beqz       $s5, .Llevel_10_80085A9C
/* 7FD854 80085A8C 520062A2 */   sb        $v0, 0x52($s3)
/* 7FD858 80085A90 0C006426 */  addiu      $a0, $s3, 0xC
/* 7FD85C 80085A94 C05D000C */  jal        VecCopy
/* 7FD860 80085A98 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_10_80085A9C:
/* 7FD864 80085A9C 734A010C */  jal        func_800529CC
/* 7FD868 80085AA0 21206002 */   addu      $a0, $s3, $zero
/* 7FD86C 80085AA4 43180208 */  j          .Llevel_10_8008610C
/* 7FD870 80085AA8 21106002 */   addu      $v0, $s3, $zero
.Llevel_10_80085AAC:
/* 7FD874 80085AAC 0000718E */  lw         $s1, 0x0($s3)
/* 7FD878 80085AB0 C8E9000C */  jal        func_8003A720
/* 7FD87C 80085AB4 21206002 */   addu      $a0, $s3, $zero
/* 7FD880 80085AB8 8C000224 */  addiu      $v0, $zero, 0x8C
/* 7FD884 80085ABC 000020AE */  sw         $zero, 0x0($s1)
/* 7FD888 80085AC0 040020AE */  sw         $zero, 0x4($s1)
/* 7FD88C 80085AC4 080022AE */  sw         $v0, 0x8($s1)
/* 7FD890 80085AC8 0E0020A2 */  sb         $zero, 0xE($s1)
/* 7FD894 80085ACC 0F0020A2 */  sb         $zero, 0xF($s1)
/* 7FD898 80085AD0 110020A2 */  sb         $zero, 0x11($s1)
/* 7FD89C 80085AD4 120020A2 */  sb         $zero, 0x12($s1)
/* 7FD8A0 80085AD8 130020A2 */  sb         $zero, 0x13($s1)
/* 7FD8A4 80085ADC 3600A386 */  lh         $v1, 0x36($s5)
/* 7FD8A8 80085AE0 0D000224 */  addiu      $v0, $zero, 0xD
/* 7FD8AC 80085AE4 02006214 */  bne        $v1, $v0, .Llevel_10_80085AF0
/* 7FD8B0 80085AE8 03000224 */   addiu     $v0, $zero, 0x3
/* 7FD8B4 80085AEC 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_10_80085AF0:
/* 7FD8B8 80085AF0 100022A2 */  sb         $v0, 0x10($s1)
/* 7FD8BC 80085AF4 0C007026 */  addiu      $s0, $s3, 0xC
/* 7FD8C0 80085AF8 21200002 */  addu       $a0, $s0, $zero
/* 7FD8C4 80085AFC 0C00A526 */  addiu      $a1, $s5, 0xC
/* 7FD8C8 80085B00 FF000224 */  addiu      $v0, $zero, 0xFF
/* 7FD8CC 80085B04 140022A2 */  sb         $v0, 0x14($s1)
/* 7FD8D0 80085B08 02001124 */  addiu      $s1, $zero, 0x2
/* 7FD8D4 80085B0C 18000224 */  addiu      $v0, $zero, 0x18
/* 7FD8D8 80085B10 500062A2 */  sb         $v0, 0x50($s3)
/* 7FD8DC 80085B14 40000224 */  addiu      $v0, $zero, 0x40
/* 7FD8E0 80085B18 520062A2 */  sb         $v0, 0x52($s3)
/* 7FD8E4 80085B1C 20000224 */  addiu      $v0, $zero, 0x20
/* 7FD8E8 80085B20 490071A2 */  sb         $s1, 0x49($s3)
/* 7FD8EC 80085B24 440062A2 */  sb         $v0, 0x44($s3)
/* 7FD8F0 80085B28 450060A2 */  sb         $zero, 0x45($s3)
/* 7FD8F4 80085B2C C05D000C */  jal        VecCopy
/* 7FD8F8 80085B30 460060A2 */   sb        $zero, 0x46($s3)
/* 7FD8FC 80085B34 734A010C */  jal        func_800529CC
/* 7FD900 80085B38 21206002 */   addu      $a0, $s3, $zero
/* 7FD904 80085B3C 1000A427 */  addiu      $a0, $sp, 0x10
/* 7FD908 80085B40 21280002 */  addu       $a1, $s0, $zero
/* 7FD90C 80085B44 FFFF0224 */  addiu      $v0, $zero, -0x1
/* 7FD910 80085B48 C05D000C */  jal        VecCopy
/* 7FD914 80085B4C 1C0062AE */   sw        $v0, 0x1C($s3)
/* 7FD918 80085B50 1000A427 */  addiu      $a0, $sp, 0x10
/* 7FD91C 80085B54 1800A28F */  lw         $v0, 0x18($sp)
/* 7FD920 80085B58 0100053C */  lui        $a1, (0x10000 >> 16)
/* 7FD924 80085B5C 00044224 */  addiu      $v0, $v0, 0x400
/* 7FD928 80085B60 7B35010C */  jal        func_8004D5EC
/* 7FD92C 80085B64 1800A2AF */   sw        $v0, 0x18($sp)
/* 7FD930 80085B68 F44C010C */  jal        func_800533D0
/* 7FD934 80085B6C 21206002 */   addu      $a0, $s3, $zero
/* 7FD938 80085B70 36006386 */  lh         $v1, 0x36($s3)
/* 7FD93C 80085B74 0E000224 */  addiu      $v0, $zero, 0xE
/* 7FD940 80085B78 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 7FD944 80085B7C 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 7FD948 80085B80 03006214 */  bne        $v1, $v0, .Llevel_10_80085B90
/* 7FD94C 80085B84 4E0060A2 */   sb        $zero, 0x4E($s3)
/* 7FD950 80085B88 0C000224 */  addiu      $v0, $zero, 0xC
/* 7FD954 80085B8C 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_10_80085B90:
/* 7FD958 80085B90 36006386 */  lh         $v1, 0x36($s3)
/* 7FD95C 80085B94 53000224 */  addiu      $v0, $zero, 0x53
/* 7FD960 80085B98 05006214 */  bne        $v1, $v0, .Llevel_10_80085BB0
/* 7FD964 80085B9C 54000224 */   addiu     $v0, $zero, 0x54
/* 7FD968 80085BA0 01000224 */  addiu      $v0, $zero, 0x1
/* 7FD96C 80085BA4 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 7FD970 80085BA8 36006386 */  lh         $v1, 0x36($s3)
/* 7FD974 80085BAC 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_10_80085BB0:
/* 7FD978 80085BB0 02006214 */  bne        $v1, $v0, .Llevel_10_80085BBC
/* 7FD97C 80085BB4 00000000 */   nop
/* 7FD980 80085BB8 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_10_80085BBC:
/* 7FD984 80085BBC 36006386 */  lh         $v1, 0x36($s3)
/* 7FD988 80085BC0 55000224 */  addiu      $v0, $zero, 0x55
/* 7FD98C 80085BC4 05006214 */  bne        $v1, $v0, .Llevel_10_80085BDC
/* 7FD990 80085BC8 56000224 */   addiu     $v0, $zero, 0x56
/* 7FD994 80085BCC 03000224 */  addiu      $v0, $zero, 0x3
/* 7FD998 80085BD0 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 7FD99C 80085BD4 36006386 */  lh         $v1, 0x36($s3)
/* 7FD9A0 80085BD8 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_10_80085BDC:
/* 7FD9A4 80085BDC 02006214 */  bne        $v1, $v0, .Llevel_10_80085BE8
/* 7FD9A8 80085BE0 04000224 */   addiu     $v0, $zero, 0x4
/* 7FD9AC 80085BE4 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_10_80085BE8:
/* 7FD9B0 80085BE8 36006386 */  lh         $v1, 0x36($s3)
/* 7FD9B4 80085BEC 57000224 */  addiu      $v0, $zero, 0x57
/* 7FD9B8 80085BF0 46016214 */  bne        $v1, $v0, .Llevel_10_8008610C
/* 7FD9BC 80085BF4 21106002 */   addu      $v0, $s3, $zero
/* 7FD9C0 80085BF8 05000224 */  addiu      $v0, $zero, 0x5
/* 7FD9C4 80085BFC 42180208 */  j          .Llevel_10_80086108
/* 7FD9C8 80085C00 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_10_80085C04:
/* 7FD9CC 80085C04 0000708E */  lw         $s0, 0x0($s3)
/* 7FD9D0 80085C08 C8E9000C */  jal        func_8003A720
/* 7FD9D4 80085C0C 21206002 */   addu      $a0, $s3, $zero
/* 7FD9D8 80085C10 AA49010C */  jal        func_800526A8
/* 7FD9DC 80085C14 21206002 */   addu      $a0, $s3, $zero
/* 7FD9E0 80085C18 490060A2 */  sb         $zero, 0x49($s3)
/* 7FD9E4 80085C1C 000000AE */  sw         $zero, 0x0($s0)
/* 7FD9E8 80085C20 080000A6 */  sh         $zero, 0x8($s0)
/* 7FD9EC 80085C24 060000A6 */  sh         $zero, 0x6($s0)
/* 7FD9F0 80085C28 040000A6 */  sh         $zero, 0x4($s0)
/* 7FD9F4 80085C2C 0C0000AE */  sw         $zero, 0xC($s0)
/* 7FD9F8 80085C30 3501A012 */  beqz       $s5, .Llevel_10_80086108
/* 7FD9FC 80085C34 100000AE */   sw        $zero, 0x10($s0)
/* 7FDA00 80085C38 0C006426 */  addiu      $a0, $s3, 0xC
/* 7FDA04 80085C3C C05D000C */  jal        VecCopy
/* 7FDA08 80085C40 0C00A526 */   addiu     $a1, $s5, 0xC
/* 7FDA0C 80085C44 43180208 */  j          .Llevel_10_8008610C
/* 7FDA10 80085C48 21106002 */   addu      $v0, $s3, $zero
.Llevel_10_80085C4C:
/* 7FDA14 80085C4C 0000748E */  lw         $s4, 0x0($s3)
/* 7FDA18 80085C50 C8E9000C */  jal        func_8003A720
/* 7FDA1C 80085C54 21206002 */   addu      $a0, $s3, $zero
/* 7FDA20 80085C58 0C006426 */  addiu      $a0, $s3, 0xC
/* 7FDA24 80085C5C 0C00A526 */  addiu      $a1, $s5, 0xC
/* 7FDA28 80085C60 20000224 */  addiu      $v0, $zero, 0x20
/* 7FDA2C 80085C64 C05D000C */  jal        VecCopy
/* 7FDA30 80085C68 500062A2 */   sb        $v0, 0x50($s3)
/* 7FDA34 80085C6C AA49010C */  jal        func_800526A8
/* 7FDA38 80085C70 21206002 */   addu      $a0, $s3, $zero
/* 7FDA3C 80085C74 CB89010C */  jal        rand
/* 7FDA40 80085C78 00000000 */   nop
/* 7FDA44 80085C7C CB89010C */  jal        rand
/* 7FDA48 80085C80 FF0F5230 */   andi      $s2, $v0, 0xFFF
/* 7FDA4C 80085C84 FF075130 */  andi       $s1, $v0, 0x7FF
/* 7FDA50 80085C88 2C5B000C */  jal        Cos
/* 7FDA54 80085C8C 21202002 */   addu      $a0, $s1, $zero
/* 7FDA58 80085C90 21204002 */  addu       $a0, $s2, $zero
/* 7FDA5C 80085C94 2C5B000C */  jal        Cos
/* 7FDA60 80085C98 21804000 */   addu      $s0, $v0, $zero
/* 7FDA64 80085C9C 43811000 */  sra        $s0, $s0, 5
/* 7FDA68 80085CA0 18000202 */  mult       $s0, $v0
/* 7FDA6C 80085CA4 21202002 */  addu       $a0, $s1, $zero
/* 7FDA70 80085CA8 12380000 */  mflo       $a3
/* 7FDA74 80085CAC 03130700 */  sra        $v0, $a3, 12
/* 7FDA78 80085CB0 2C5B000C */  jal        Cos
/* 7FDA7C 80085CB4 000082A6 */   sh        $v0, 0x0($s4)
/* 7FDA80 80085CB8 21204002 */  addu       $a0, $s2, $zero
/* 7FDA84 80085CBC 165B000C */  jal        Sin
/* 7FDA88 80085CC0 21804000 */   addu      $s0, $v0, $zero
/* 7FDA8C 80085CC4 43811000 */  sra        $s0, $s0, 5
/* 7FDA90 80085CC8 18000202 */  mult       $s0, $v0
/* 7FDA94 80085CCC 21202002 */  addu       $a0, $s1, $zero
/* 7FDA98 80085CD0 12380000 */  mflo       $a3
/* 7FDA9C 80085CD4 03130700 */  sra        $v0, $a3, 12
/* 7FDAA0 80085CD8 165B000C */  jal        Sin
/* 7FDAA4 80085CDC 020082A6 */   sh        $v0, 0x2($s4)
/* 7FDAA8 80085CE0 43110200 */  sra        $v0, $v0, 5
/* 7FDAAC 80085CE4 040082A6 */  sh         $v0, 0x4($s4)
/* 7FDAB0 80085CE8 1800A28E */  lw         $v0, 0x18($s5)
/* 7FDAB4 80085CEC 0200033C */  lui        $v1, (0x20000 >> 16)
/* 7FDAB8 80085CF0 24104300 */  and        $v0, $v0, $v1
/* 7FDABC 80085CF4 13004010 */  beqz       $v0, .Llevel_10_80085D44
/* 7FDAC0 80085CF8 00000000 */   nop
/* 7FDAC4 80085CFC 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* 7FDAC8 80085D00 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* 7FDACC 80085D04 00008396 */  lhu        $v1, 0x0($s4)
/* 7FDAD0 80085D08 83110200 */  sra        $v0, $v0, 6
/* 7FDAD4 80085D0C 21186200 */  addu       $v1, $v1, $v0
/* 7FDAD8 80085D10 000083A6 */  sh         $v1, 0x0($s4)
/* 7FDADC 80085D14 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* 7FDAE0 80085D18 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* 7FDAE4 80085D1C 02008396 */  lhu        $v1, 0x2($s4)
/* 7FDAE8 80085D20 83110200 */  sra        $v0, $v0, 6
/* 7FDAEC 80085D24 21186200 */  addu       $v1, $v1, $v0
/* 7FDAF0 80085D28 020083A6 */  sh         $v1, 0x2($s4)
/* 7FDAF4 80085D2C 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* 7FDAF8 80085D30 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* 7FDAFC 80085D34 04008396 */  lhu        $v1, 0x4($s4)
/* 7FDB00 80085D38 83110200 */  sra        $v0, $v0, 6
/* 7FDB04 80085D3C 21186200 */  addu       $v1, $v1, $v0
/* 7FDB08 80085D40 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_10_80085D44:
/* 7FDB0C 80085D44 00008286 */  lh         $v0, 0x0($s4)
/* 7FDB10 80085D48 0C00638E */  lw         $v1, 0xC($s3)
/* 7FDB14 80085D4C 80100200 */  sll        $v0, $v0, 2
/* 7FDB18 80085D50 21186200 */  addu       $v1, $v1, $v0
/* 7FDB1C 80085D54 0C0063AE */  sw         $v1, 0xC($s3)
/* 7FDB20 80085D58 02008286 */  lh         $v0, 0x2($s4)
/* 7FDB24 80085D5C 1000638E */  lw         $v1, 0x10($s3)
/* 7FDB28 80085D60 80100200 */  sll        $v0, $v0, 2
/* 7FDB2C 80085D64 21186200 */  addu       $v1, $v1, $v0
/* 7FDB30 80085D68 100063AE */  sw         $v1, 0x10($s3)
/* 7FDB34 80085D6C 04008286 */  lh         $v0, 0x4($s4)
/* 7FDB38 80085D70 1400638E */  lw         $v1, 0x14($s3)
/* 7FDB3C 80085D74 80100200 */  sll        $v0, $v0, 2
/* 7FDB40 80085D78 21186200 */  addu       $v1, $v1, $v0
/* 7FDB44 80085D7C CB89010C */  jal        rand
/* 7FDB48 80085D80 140063AE */   sw        $v1, 0x14($s3)
/* 7FDB4C 80085D84 0F004230 */  andi       $v0, $v0, 0xF
/* 7FDB50 80085D88 CB89010C */  jal        rand
/* 7FDB54 80085D8C 060082A6 */   sh        $v0, 0x6($s4)
/* 7FDB58 80085D90 0F004230 */  andi       $v0, $v0, 0xF
/* 7FDB5C 80085D94 CB89010C */  jal        rand
/* 7FDB60 80085D98 080082A6 */   sh        $v0, 0x8($s4)
/* 7FDB64 80085D9C 0F004230 */  andi       $v0, $v0, 0xF
/* 7FDB68 80085DA0 0A0082A6 */  sh         $v0, 0xA($s4)
/* 7FDB6C 80085DA4 1400A28E */  lw         $v0, 0x14($s5)
/* 7FDB70 80085DA8 00000000 */  nop
/* 7FDB74 80085DAC C0FF4224 */  addiu      $v0, $v0, -0x40
/* 7FDB78 80085DB0 CB89010C */  jal        rand
/* 7FDB7C 80085DB4 100082AE */   sw        $v0, 0x10($s4)
/* 7FDB80 80085DB8 0F004230 */  andi       $v0, $v0, 0xF
/* 7FDB84 80085DBC 40000324 */  addiu      $v1, $zero, 0x40
/* 7FDB88 80085DC0 23186200 */  subu       $v1, $v1, $v0
/* 7FDB8C 80085DC4 0C0083AE */  sw         $v1, 0xC($s4)
/* 7FDB90 80085DC8 36006296 */  lhu        $v0, 0x36($s3)
/* 7FDB94 80085DCC 00000000 */  nop
/* 7FDB98 80085DD0 CBFE4224 */  addiu      $v0, $v0, -0x135
/* 7FDB9C 80085DD4 0300422C */  sltiu      $v0, $v0, 0x3
/* 7FDBA0 80085DD8 CB004010 */  beqz       $v0, .Llevel_10_80086108
/* 7FDBA4 80085DDC A100033C */   lui       $v1, (0xA18618 >> 16)
/* 7FDBA8 80085DE0 4B006292 */  lbu        $v0, 0x4B($s3)
/* 7FDBAC 80085DE4 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* 7FDBB0 80085DE8 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_10_80085DEC:
/* 7FDBB4 80085DEC 80004234 */  ori        $v0, $v0, 0x80
/* 7FDBB8 80085DF0 42180208 */  j          .Llevel_10_80086108
/* 7FDBBC 80085DF4 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_10_80085DF8:
/* 7FDBC0 80085DF8 0000718E */  lw         $s1, 0x0($s3)
/* 7FDBC4 80085DFC C8E9000C */  jal        func_8003A720
/* 7FDBC8 80085E00 21206002 */   addu      $a0, $s3, $zero
/* 7FDBCC 80085E04 21206002 */  addu       $a0, $s3, $zero
/* 7FDBD0 80085E08 20000224 */  addiu      $v0, $zero, 0x20
/* 7FDBD4 80085E0C 500062A2 */  sb         $v0, 0x50($s3)
/* 7FDBD8 80085E10 FF000224 */  addiu      $v0, $zero, 0xFF
/* 7FDBDC 80085E14 734A010C */  jal        func_800529CC
/* 7FDBE0 80085E18 520062A2 */   sb        $v0, 0x52($s3)
/* 7FDBE4 80085E1C 0E000224 */  addiu      $v0, $zero, 0xE
/* 7FDBE8 80085E20 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 7FDBEC 80085E24 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 7FDBF0 80085E28 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 7FDBF4 80085E2C 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 7FDBF8 80085E30 0780033C */  lui        $v1, %hi(D_80077058)
/* 7FDBFC 80085E34 5870638C */  lw         $v1, %lo(D_80077058)($v1)
/* 7FDC00 80085E38 03000224 */  addiu      $v0, $zero, 0x3
/* 7FDC04 80085E3C 03006214 */  bne        $v1, $v0, .Llevel_10_80085E4C
/* 7FDC08 80085E40 01000224 */   addiu     $v0, $zero, 0x1
/* 7FDC0C 80085E44 95170208 */  j          .Llevel_10_80085E54
/* 7FDC10 80085E48 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_10_80085E4C:
/* 7FDC14 80085E4C 02006214 */  bne        $v1, $v0, .Llevel_10_80085E58
/* 7FDC18 80085E50 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_10_80085E54:
/* 7FDC1C 80085E54 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_10_80085E58:
/* 7FDC20 80085E58 CB89010C */  jal        rand
/* 7FDC24 80085E5C 00000000 */   nop
/* 7FDC28 80085E60 2000A426 */  addiu      $a0, $s5, 0x20
/* 7FDC2C 80085E64 07004230 */  andi       $v0, $v0, 0x7
/* 7FDC30 80085E68 80100200 */  sll        $v0, $v0, 2
/* 7FDC34 80085E6C 2000B027 */  addiu      $s0, $sp, 0x20
/* 7FDC38 80085E70 0780013C */  lui        $at, %hi(D_8006F3A0)
/* 7FDC3C 80085E74 21082200 */  addu       $at, $at, $v0
/* 7FDC40 80085E78 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* 7FDC44 80085E7C 21280002 */  addu       $a1, $s0, $zero
/* 7FDC48 80085E80 2400A0AF */  sw         $zero, 0x24($sp)
/* 7FDC4C 80085E84 2000A3AF */  sw         $v1, 0x20($sp)
/* 7FDC50 80085E88 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* 7FDC54 80085E8C 21082200 */  addu       $at, $at, $v0
/* 7FDC58 80085E90 A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* 7FDC5C 80085E94 21300002 */  addu       $a2, $s0, $zero
/* 7FDC60 80085E98 125C000C */  jal        func_80017048
/* 7FDC64 80085E9C 2800A2AF */   sw        $v0, 0x28($sp)
/* 7FDC68 80085EA0 CB89010C */  jal        rand
/* 7FDC6C 80085EA4 00000000 */   nop
/* 7FDC70 80085EA8 2000A38F */  lw         $v1, 0x20($sp)
/* 7FDC74 80085EAC 7F004230 */  andi       $v0, $v0, 0x7F
/* 7FDC78 80085EB0 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 7FDC7C 80085EB4 21186200 */  addu       $v1, $v1, $v0
/* 7FDC80 80085EB8 CB89010C */  jal        rand
/* 7FDC84 80085EBC 2000A3AF */   sw        $v1, 0x20($sp)
/* 7FDC88 80085EC0 2400A38F */  lw         $v1, 0x24($sp)
/* 7FDC8C 80085EC4 7F004230 */  andi       $v0, $v0, 0x7F
/* 7FDC90 80085EC8 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 7FDC94 80085ECC 21186200 */  addu       $v1, $v1, $v0
/* 7FDC98 80085ED0 CB89010C */  jal        rand
/* 7FDC9C 80085ED4 2400A3AF */   sw        $v1, 0x24($sp)
/* 7FDCA0 80085ED8 0C006426 */  addiu      $a0, $s3, 0xC
/* 7FDCA4 80085EDC 0C00A526 */  addiu      $a1, $s5, 0xC
/* 7FDCA8 80085EE0 21300002 */  addu       $a2, $s0, $zero
/* 7FDCAC 80085EE4 2800A38F */  lw         $v1, 0x28($sp)
/* 7FDCB0 80085EE8 7F004230 */  andi       $v0, $v0, 0x7F
/* 7FDCB4 80085EEC C1FF6324 */  addiu      $v1, $v1, -0x3F
/* 7FDCB8 80085EF0 21186200 */  addu       $v1, $v1, $v0
/* 7FDCBC 80085EF4 D65D000C */  jal        VecAdd
/* 7FDCC0 80085EF8 2800A3AF */   sw        $v1, 0x28($sp)
/* 7FDCC4 80085EFC 21202002 */  addu       $a0, $s1, $zero
/* 7FDCC8 80085F00 C05D000C */  jal        VecCopy
/* 7FDCCC 80085F04 21280002 */   addu      $a1, $s0, $zero
/* 7FDCD0 80085F08 21202002 */  addu       $a0, $s1, $zero
/* 7FDCD4 80085F0C B25D000C */  jal        VecShiftRight
/* 7FDCD8 80085F10 02000524 */   addiu     $a1, $zero, 0x2
/* 7FDCDC 80085F14 CB89010C */  jal        rand
/* 7FDCE0 80085F18 00000000 */   nop
/* 7FDCE4 80085F1C 0000238E */  lw         $v1, 0x0($s1)
/* 7FDCE8 80085F20 FF004230 */  andi       $v0, $v0, 0xFF
/* 7FDCEC 80085F24 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 7FDCF0 80085F28 21186200 */  addu       $v1, $v1, $v0
/* 7FDCF4 80085F2C CB89010C */  jal        rand
/* 7FDCF8 80085F30 000023AE */   sw        $v1, 0x0($s1)
/* 7FDCFC 80085F34 0400238E */  lw         $v1, 0x4($s1)
/* 7FDD00 80085F38 FF004230 */  andi       $v0, $v0, 0xFF
/* 7FDD04 80085F3C 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 7FDD08 80085F40 21186200 */  addu       $v1, $v1, $v0
/* 7FDD0C 80085F44 CB89010C */  jal        rand
/* 7FDD10 80085F48 040023AE */   sw        $v1, 0x4($s1)
/* 7FDD14 80085F4C 0800238E */  lw         $v1, 0x8($s1)
/* 7FDD18 80085F50 FF004230 */  andi       $v0, $v0, 0xFF
/* 7FDD1C 80085F54 81FF6324 */  addiu      $v1, $v1, -0x7F
/* 7FDD20 80085F58 21186200 */  addu       $v1, $v1, $v0
/* 7FDD24 80085F5C CB89010C */  jal        rand
/* 7FDD28 80085F60 080023AE */   sw        $v1, 0x8($s1)
/* 7FDD2C 80085F64 CB89010C */  jal        rand
/* 7FDD30 80085F68 440062A2 */   sb        $v0, 0x44($s3)
/* 7FDD34 80085F6C CB89010C */  jal        rand
/* 7FDD38 80085F70 450062A2 */   sb        $v0, 0x45($s3)
/* 7FDD3C 80085F74 CB89010C */  jal        rand
/* 7FDD40 80085F78 460062A2 */   sb        $v0, 0x46($s3)
/* 7FDD44 80085F7C 0F004230 */  andi       $v0, $v0, 0xF
/* 7FDD48 80085F80 CB89010C */  jal        rand
/* 7FDD4C 80085F84 100022A2 */   sb        $v0, 0x10($s1)
/* 7FDD50 80085F88 0F004230 */  andi       $v0, $v0, 0xF
/* 7FDD54 80085F8C CB89010C */  jal        rand
/* 7FDD58 80085F90 110022A2 */   sb        $v0, 0x11($s1)
/* 7FDD5C 80085F94 0F004230 */  andi       $v0, $v0, 0xF
/* 7FDD60 80085F98 120022A2 */  sb         $v0, 0x12($s1)
/* 7FDD64 80085F9C 1400A28E */  lw         $v0, 0x14($s5)
/* 7FDD68 80085FA0 CB89010C */  jal        rand
/* 7FDD6C 80085FA4 0C0022AE */   sw        $v0, 0xC($s1)
/* 7FDD70 80085FA8 03004230 */  andi       $v0, $v0, 0x3
/* 7FDD74 80085FAC 10004224 */  addiu      $v0, $v0, 0x10
/* 7FDD78 80085FB0 42180208 */  j          .Llevel_10_80086108
/* 7FDD7C 80085FB4 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_10_80085FB8:
/* 7FDD80 80085FB8 0000708E */  lw         $s0, 0x0($s3)
/* 7FDD84 80085FBC C8E9000C */  jal        func_8003A720
/* 7FDD88 80085FC0 21206002 */   addu      $a0, $s3, $zero
/* 7FDD8C 80085FC4 734A010C */  jal        func_800529CC
/* 7FDD90 80085FC8 21206002 */   addu      $a0, $s3, $zero
/* 7FDD94 80085FCC 02000224 */  addiu      $v0, $zero, 0x2
/* 7FDD98 80085FD0 4F0062A2 */  sb         $v0, 0x4F($s3)
/* 7FDD9C 80085FD4 40000224 */  addiu      $v0, $zero, 0x40
/* 7FDDA0 80085FD8 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 7FDDA4 80085FDC 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 7FDDA8 80085FE0 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 7FDDAC 80085FE4 42180208 */  j          .Llevel_10_80086108
/* 7FDDB0 80085FE8 000002AE */   sw        $v0, 0x0($s0)
.Llevel_10_80085FEC:
/* 7FDDB4 80085FEC C8E9000C */  jal        func_8003A720
/* 7FDDB8 80085FF0 21206002 */   addu      $a0, $s3, $zero
/* 7FDDBC 80085FF4 21206002 */  addu       $a0, $s3, $zero
/* 7FDDC0 80085FF8 FF000224 */  addiu      $v0, $zero, 0xFF
/* 7FDDC4 80085FFC 500062A2 */  sb         $v0, 0x50($s3)
/* 7FDDC8 80086000 CC010224 */  addiu      $v0, $zero, 0x1CC
/* 7FDDCC 80086004 0C0062AE */  sw         $v0, 0xC($s3)
/* 7FDDD0 80086008 28000224 */  addiu      $v0, $zero, 0x28
/* 7FDDD4 8008600C 100062AE */  sw         $v0, 0x10($s3)
/* 7FDDD8 80086010 00100224 */  addiu      $v0, $zero, 0x1000
/* 7FDDDC 80086014 734A010C */  jal        func_800529CC
/* 7FDDE0 80086018 140062AE */   sw        $v0, 0x14($s3)
/* 7FDDE4 8008601C 20000224 */  addiu      $v0, $zero, 0x20
/* 7FDDE8 80086020 470062A2 */  sb         $v0, 0x47($s3)
/* 7FDDEC 80086024 4C0060A2 */  sb         $zero, 0x4C($s3)
/* 7FDDF0 80086028 4D0060A2 */  sb         $zero, 0x4D($s3)
/* 7FDDF4 8008602C 4E0060A2 */  sb         $zero, 0x4E($s3)
/* 7FDDF8 80086030 42180208 */  j          .Llevel_10_80086108
/* 7FDDFC 80086034 4F0060A2 */   sb        $zero, 0x4F($s3)
.Llevel_10_80086038:
/* 7FDE00 80086038 C8E9000C */  jal        func_8003A720
/* 7FDE04 8008603C 21206002 */   addu      $a0, $s3, $zero
/* 7FDE08 80086040 0300A012 */  beqz       $s5, .Llevel_10_80086050
/* 7FDE0C 80086044 0C006426 */   addiu     $a0, $s3, 0xC
/* 7FDE10 80086048 16180208 */  j          .Llevel_10_80086058
/* 7FDE14 8008604C 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_10_80086050:
/* 7FDE18 80086050 0880053C */  lui        $a1, %hi(g_Spyro)
/* 7FDE1C 80086054 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_10_80086058:
/* 7FDE20 80086058 C05D000C */  jal        VecCopy
/* 7FDE24 8008605C 00000000 */   nop
/* 7FDE28 80086060 0C006426 */  addiu      $a0, $s3, 0xC
/* 7FDE2C 80086064 1400628E */  lw         $v0, 0x14($s3)
/* 7FDE30 80086068 00080524 */  addiu      $a1, $zero, 0x800
/* 7FDE34 8008606C 00024224 */  addiu      $v0, $v0, 0x200
/* 7FDE38 80086070 7B35010C */  jal        func_8004D5EC
/* 7FDE3C 80086074 140062AE */   sw        $v0, 0x14($s3)
/* 7FDE40 80086078 1400648E */  lw         $a0, 0x14($s3)
/* 7FDE44 8008607C 21184000 */  addu       $v1, $v0, $zero
/* 7FDE48 80086080 23106400 */  subu       $v0, $v1, $a0
/* 7FDE4C 80086084 02004104 */  bgez       $v0, .Llevel_10_80086090
/* 7FDE50 80086088 00000000 */   nop
/* 7FDE54 8008608C 23100200 */  negu       $v0, $v0
.Llevel_10_80086090:
/* 7FDE58 80086090 00084228 */  slti       $v0, $v0, 0x800
/* 7FDE5C 80086094 03004010 */  beqz       $v0, .Llevel_10_800860A4
/* 7FDE60 80086098 00FE8224 */   addiu     $v0, $a0, -0x200
/* 7FDE64 8008609C 40180208 */  j          .Llevel_10_80086100
/* 7FDE68 800860A0 140063AE */   sw        $v1, 0x14($s3)
.Llevel_10_800860A4:
/* 7FDE6C 800860A4 40180208 */  j          .Llevel_10_80086100
/* 7FDE70 800860A8 140062AE */   sw        $v0, 0x14($s3)
.Llevel_10_800860AC:
/* 7FDE74 800860AC C8E9000C */  jal        func_8003A720
/* 7FDE78 800860B0 21206002 */   addu      $a0, $s3, $zero
/* 7FDE7C 800860B4 21206002 */  addu       $a0, $s3, $zero
/* 7FDE80 800860B8 20000224 */  addiu      $v0, $zero, 0x20
/* 7FDE84 800860BC 500062A2 */  sb         $v0, 0x50($s3)
/* 7FDE88 800860C0 FF000224 */  addiu      $v0, $zero, 0xFF
/* 7FDE8C 800860C4 734A010C */  jal        func_800529CC
/* 7FDE90 800860C8 520062A2 */   sb        $v0, 0x52($s3)
/* 7FDE94 800860CC 43180208 */  j          .Llevel_10_8008610C
/* 7FDE98 800860D0 21106002 */   addu      $v0, $s3, $zero
.Llevel_10_800860D4:
/* 7FDE9C 800860D4 C8E9000C */  jal        func_8003A720
/* 7FDEA0 800860D8 21206002 */   addu      $a0, $s3, $zero
/* 7FDEA4 800860DC 0300A012 */  beqz       $s5, .Llevel_10_800860EC
/* 7FDEA8 800860E0 0C00A526 */   addiu     $a1, $s5, 0xC
/* 7FDEAC 800860E4 3E180208 */  j          .Llevel_10_800860F8
/* 7FDEB0 800860E8 0C006426 */   addiu     $a0, $s3, 0xC
.Llevel_10_800860EC:
/* 7FDEB4 800860EC 0C006426 */  addiu      $a0, $s3, 0xC
/* 7FDEB8 800860F0 0880053C */  lui        $a1, %hi(g_Spyro)
/* 7FDEBC 800860F4 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_10_800860F8:
/* 7FDEC0 800860F8 C05D000C */  jal        VecCopy
/* 7FDEC4 800860FC 00000000 */   nop
.Llevel_10_80086100:
/* 7FDEC8 80086100 AA49010C */  jal        func_800526A8
/* 7FDECC 80086104 21206002 */   addu      $a0, $s3, $zero
.Llevel_10_80086108:
/* 7FDED0 80086108 21106002 */  addu       $v0, $s3, $zero
.Llevel_10_8008610C:
/* 7FDED4 8008610C 5000BF8F */  lw         $ra, 0x50($sp)
/* 7FDED8 80086110 4C00B58F */  lw         $s5, 0x4C($sp)
/* 7FDEDC 80086114 4800B48F */  lw         $s4, 0x48($sp)
/* 7FDEE0 80086118 4400B38F */  lw         $s3, 0x44($sp)
/* 7FDEE4 8008611C 4000B28F */  lw         $s2, 0x40($sp)
/* 7FDEE8 80086120 3C00B18F */  lw         $s1, 0x3C($sp)
/* 7FDEEC 80086124 3800B08F */  lw         $s0, 0x38($sp)
/* 7FDEF0 80086128 5800BD27 */  addiu      $sp, $sp, 0x58
/* 7FDEF4 8008612C 0800E003 */  jr         $ra
/* 7FDEF8 80086130 00000000 */   nop
.size func_level_10_800857CC, . - func_level_10_800857CC
