.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_11_8008772C
/* B904F4 8008772C A8FFBD27 */  addiu      $sp, $sp, -0x58
/* B904F8 80087730 3800B0AF */  sw         $s0, 0x38($sp)
/* B904FC 80087734 21808000 */  addu       $s0, $a0, $zero
/* B90500 80087738 4C00B5AF */  sw         $s5, 0x4C($sp)
/* B90504 8008773C 21A8A000 */  addu       $s5, $a1, $zero
/* B90508 80087740 5000BFAF */  sw         $ra, 0x50($sp)
/* B9050C 80087744 4800B4AF */  sw         $s4, 0x48($sp)
/* B90510 80087748 4400B3AF */  sw         $s3, 0x44($sp)
/* B90514 8008774C 4000B2AF */  sw         $s2, 0x40($sp)
/* B90518 80087750 3149010C */  jal        func_800524C4
/* B9051C 80087754 3C00B1AF */   sw        $s1, 0x3C($sp)
/* B90520 80087758 21984000 */  addu       $s3, $v0, $zero
/* B90524 8008775C 1400A012 */  beqz       $s5, .Llevel_11_800877B0
/* B90528 80087760 360070A6 */   sh        $s0, 0x36($s3)
/* B9052C 80087764 0780043C */  lui        $a0, %hi(D_80075828)
/* B90530 80087768 2858848C */  lw         $a0, %lo(D_80075828)($a0)
/* B90534 8008776C 00000000 */  nop
/* B90538 80087770 2320A402 */  subu       $a0, $s5, $a0
/* B9053C 80087774 40190400 */  sll        $v1, $a0, 5
/* B90540 80087778 23186400 */  subu       $v1, $v1, $a0
/* B90544 8008777C 40190300 */  sll        $v1, $v1, 5
/* B90548 80087780 21186400 */  addu       $v1, $v1, $a0
/* B9054C 80087784 C0100300 */  sll        $v0, $v1, 3
/* B90550 80087788 21186200 */  addu       $v1, $v1, $v0
/* B90554 8008778C C0130300 */  sll        $v0, $v1, 15
/* B90558 80087790 23104300 */  subu       $v0, $v0, $v1
/* B9055C 80087794 80100200 */  sll        $v0, $v0, 2
/* B90560 80087798 21104400 */  addu       $v0, $v0, $a0
/* B90564 8008779C 23100200 */  negu       $v0, $v0
/* B90568 800877A0 C3180200 */  sra        $v1, $v0, 3
/* B9056C 800877A4 0001622C */  sltiu      $v0, $v1, 0x100
/* B90570 800877A8 03004014 */  bnez       $v0, .Llevel_11_800877B8
/* B90574 800877AC 0201022A */   slti      $v0, $s0, 0x102
.Llevel_11_800877B0:
/* B90578 800877B0 21180000 */  addu       $v1, $zero, $zero
/* B9057C 800877B4 0201022A */  slti       $v0, $s0, 0x102
.Llevel_11_800877B8:
/* B90580 800877B8 29004010 */  beqz       $v0, .Llevel_11_80087860
/* B90584 800877BC 560063A2 */   sb        $v1, 0x56($s3)
/* B90588 800877C0 FF00022A */  slti       $v0, $s0, 0xFF
/* B9058C 800877C4 0D014010 */  beqz       $v0, .Llevel_11_80087BFC
/* B90590 800877C8 4C000224 */   addiu     $v0, $zero, 0x4C
/* B90594 800877CC 10020212 */  beq        $s0, $v0, .Llevel_11_80088010
/* B90598 800877D0 4D00022A */   slti      $v0, $s0, 0x4D
/* B9059C 800877D4 10004010 */  beqz       $v0, .Llevel_11_80087818
/* B905A0 800877D8 0F000224 */   addiu     $v0, $zero, 0xF
/* B905A4 800877DC 46000212 */  beq        $s0, $v0, .Llevel_11_800878F8
/* B905A8 800877E0 1000022A */   slti      $v0, $s0, 0x10
/* B905AC 800877E4 05004010 */  beqz       $v0, .Llevel_11_800877FC
/* B905B0 800877E8 0E000224 */   addiu     $v0, $zero, 0xE
/* B905B4 800877EC 8B000212 */  beq        $s0, $v0, .Llevel_11_80087A1C
/* B905B8 800877F0 00000000 */   nop
/* B905BC 800877F4 0E200208 */  j          .Llevel_11_80088038
/* B905C0 800877F8 00000000 */   nop
.Llevel_11_800877FC:
/* B905C4 800877FC 10000224 */  addiu      $v0, $zero, 0x10
/* B905C8 80087800 64000212 */  beq        $s0, $v0, .Llevel_11_80087994
/* B905CC 80087804 22000224 */   addiu     $v0, $zero, 0x22
/* B905D0 80087808 76000212 */  beq        $s0, $v0, .Llevel_11_800879E4
/* B905D4 8008780C 00000000 */   nop
/* B905D8 80087810 0E200208 */  j          .Llevel_11_80088038
/* B905DC 80087814 00000000 */   nop
.Llevel_11_80087818:
/* B905E0 80087818 78000224 */  addiu      $v0, $zero, 0x78
/* B905E4 8008781C D5000212 */  beq        $s0, $v0, .Llevel_11_80087B74
/* B905E8 80087820 7900022A */   slti      $v0, $s0, 0x79
/* B905EC 80087824 07004010 */  beqz       $v0, .Llevel_11_80087844
/* B905F0 80087828 5800022A */   slti      $v0, $s0, 0x58
/* B905F4 8008782C 02024010 */  beqz       $v0, .Llevel_11_80088038
/* B905F8 80087830 5300022A */   slti      $v0, $s0, 0x53
/* B905FC 80087834 79004010 */  beqz       $v0, .Llevel_11_80087A1C
/* B90600 80087838 00000000 */   nop
/* B90604 8008783C 0E200208 */  j          .Llevel_11_80088038
/* B90608 80087840 00000000 */   nop
.Llevel_11_80087844:
/* B9060C 80087844 EA000224 */  addiu      $v0, $zero, 0xEA
/* B90610 80087848 DC000212 */  beq        $s0, $v0, .Llevel_11_80087BBC
/* B90614 8008784C FB000224 */   addiu     $v0, $zero, 0xFB
/* B90618 80087850 55010212 */  beq        $s0, $v0, .Llevel_11_80087DA8
/* B9061C 80087854 00000000 */   nop
/* B90620 80087858 0E200208 */  j          .Llevel_11_80088038
/* B90624 8008785C 00000000 */   nop
.Llevel_11_80087860:
/* B90628 80087860 47010224 */  addiu      $v0, $zero, 0x147
/* B9062C 80087864 C0010212 */  beq        $s0, $v0, .Llevel_11_80087F68
/* B90630 80087868 4801022A */   slti      $v0, $s0, 0x148
/* B90634 8008786C 12004010 */  beqz       $v0, .Llevel_11_800878B8
/* B90638 80087870 15010224 */   addiu     $v0, $zero, 0x115
/* B9063C 80087874 BC010212 */  beq        $s0, $v0, .Llevel_11_80087F68
/* B90640 80087878 1601022A */   slti      $v0, $s0, 0x116
/* B90644 8008787C 07004010 */  beqz       $v0, .Llevel_11_8008789C
/* B90648 80087880 0E01022A */   slti      $v0, $s0, 0x10E
/* B9064C 80087884 EC014010 */  beqz       $v0, .Llevel_11_80088038
/* B90650 80087888 0401022A */   slti      $v0, $s0, 0x104
/* B90654 8008788C B6014010 */  beqz       $v0, .Llevel_11_80087F68
/* B90658 80087890 00000000 */   nop
/* B9065C 80087894 0E200208 */  j          .Llevel_11_80088038
/* B90660 80087898 00000000 */   nop
.Llevel_11_8008789C:
/* B90664 8008789C 3801022A */  slti       $v0, $s0, 0x138
/* B90668 800878A0 E5014010 */  beqz       $v0, .Llevel_11_80088038
/* B9066C 800878A4 3501022A */   slti      $v0, $s0, 0x135
/* B90670 800878A8 D4004010 */  beqz       $v0, .Llevel_11_80087BFC
/* B90674 800878AC 00000000 */   nop
/* B90678 800878B0 0E200208 */  j          .Llevel_11_80088038
/* B9067C 800878B4 00000000 */   nop
.Llevel_11_800878B8:
/* B90680 800878B8 AA01022A */  slti       $v0, $s0, 0x1AA
/* B90684 800878BC 07004010 */  beqz       $v0, .Llevel_11_800878DC
/* B90688 800878C0 A701022A */   slti      $v0, $s0, 0x1A7
/* B9068C 800878C4 CD004010 */  beqz       $v0, .Llevel_11_80087BFC
/* B90690 800878C8 95010224 */   addiu     $v0, $zero, 0x195
/* B90694 800878CC B3010212 */  beq        $s0, $v0, .Llevel_11_80087F9C
/* B90698 800878D0 00000000 */   nop
/* B9069C 800878D4 0E200208 */  j          .Llevel_11_80088038
/* B906A0 800878D8 00000000 */   nop
.Llevel_11_800878DC:
/* B906A4 800878DC C401022A */  slti       $v0, $s0, 0x1C4
/* B906A8 800878E0 CB014014 */  bnez       $v0, .Llevel_11_80088010
/* B906AC 800878E4 DD010224 */   addiu     $v0, $zero, 0x1DD
/* B906B0 800878E8 AC010212 */  beq        $s0, $v0, .Llevel_11_80087F9C
/* B906B4 800878EC 00000000 */   nop
/* B906B8 800878F0 0E200208 */  j          .Llevel_11_80088038
/* B906BC 800878F4 00000000 */   nop
.Llevel_11_800878F8:
/* B906C0 800878F8 0000708E */  lw         $s0, 0x0($s3)
/* B906C4 800878FC C8E9000C */  jal        func_8003A720
/* B906C8 80087900 21206002 */   addu      $a0, $s3, $zero
/* B906CC 80087904 8C000224 */  addiu      $v0, $zero, 0x8C
/* B906D0 80087908 080002AE */  sw         $v0, 0x8($s0)
/* B906D4 8008790C 03000224 */  addiu      $v0, $zero, 0x3
/* B906D8 80087910 100002A2 */  sb         $v0, 0x10($s0)
/* B906DC 80087914 FF000224 */  addiu      $v0, $zero, 0xFF
/* B906E0 80087918 140002A2 */  sb         $v0, 0x14($s0)
/* B906E4 8008791C 02000224 */  addiu      $v0, $zero, 0x2
/* B906E8 80087920 000000AE */  sw         $zero, 0x0($s0)
/* B906EC 80087924 040000AE */  sw         $zero, 0x4($s0)
/* B906F0 80087928 0E0000A2 */  sb         $zero, 0xE($s0)
/* B906F4 8008792C 0F0000A2 */  sb         $zero, 0xF($s0)
/* B906F8 80087930 110000A2 */  sb         $zero, 0x11($s0)
/* B906FC 80087934 120000A2 */  sb         $zero, 0x12($s0)
/* B90700 80087938 130000A2 */  sb         $zero, 0x13($s0)
/* B90704 8008793C 490062A2 */  sb         $v0, 0x49($s3)
/* B90708 80087940 18000224 */  addiu      $v0, $zero, 0x18
/* B9070C 80087944 500062A2 */  sb         $v0, 0x50($s3)
/* B90710 80087948 10000224 */  addiu      $v0, $zero, 0x10
/* B90714 8008794C 520062A2 */  sb         $v0, 0x52($s3)
/* B90718 80087950 20000224 */  addiu      $v0, $zero, 0x20
/* B9071C 80087954 440062A2 */  sb         $v0, 0x44($s3)
/* B90720 80087958 450060A2 */  sb         $zero, 0x45($s3)
/* B90724 8008795C 0400A012 */  beqz       $s5, .Llevel_11_80087970
/* B90728 80087960 460060A2 */   sb        $zero, 0x46($s3)
/* B9072C 80087964 0C006426 */  addiu      $a0, $s3, 0xC
/* B90730 80087968 C05D000C */  jal        VecCopy
/* B90734 8008796C 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_11_80087970:
/* B90738 80087970 AA49010C */  jal        func_800526A8
/* B9073C 80087974 21206002 */   addu      $a0, $s3, $zero
/* B90740 80087978 4B006292 */  lbu        $v0, 0x4B($s3)
/* B90744 8008797C 01000324 */  addiu      $v1, $zero, 0x1
/* B90748 80087980 4C0060A2 */  sb         $zero, 0x4C($s3)
/* B9074C 80087984 4D0060A2 */  sb         $zero, 0x4D($s3)
/* B90750 80087988 4E0060A2 */  sb         $zero, 0x4E($s3)
/* B90754 8008798C 671F0208 */  j          .Llevel_11_80087D9C
/* B90758 80087990 4F0063A2 */   sb        $v1, 0x4F($s3)
.Llevel_11_80087994:
/* B9075C 80087994 0000718E */  lw         $s1, 0x0($s3)
/* B90760 80087998 C8E9000C */  jal        func_8003A720
/* B90764 8008799C 21206002 */   addu      $a0, $s3, $zero
/* B90768 800879A0 AA49010C */  jal        func_800526A8
/* B9076C 800879A4 21206002 */   addu      $a0, $s3, $zero
/* B90770 800879A8 0C007026 */  addiu      $s0, $s3, 0xC
/* B90774 800879AC 21200002 */  addu       $a0, $s0, $zero
/* B90778 800879B0 C05D000C */  jal        VecCopy
/* B9077C 800879B4 0C00A526 */   addiu     $a1, $s5, 0xC
/* B90780 800879B8 21280002 */  addu       $a1, $s0, $zero
/* B90784 800879BC 1400628E */  lw         $v0, 0x14($s3)
/* B90788 800879C0 04002426 */  addiu      $a0, $s1, 0x4
/* B9078C 800879C4 00024224 */  addiu      $v0, $v0, 0x200
/* B90790 800879C8 C05D000C */  jal        VecCopy
/* B90794 800879CC 140062AE */   sw        $v0, 0x14($s3)
/* B90798 800879D0 08070224 */  addiu      $v0, $zero, 0x708
/* B9079C 800879D4 130020A2 */  sb         $zero, 0x13($s1)
/* B907A0 800879D8 120020A2 */  sb         $zero, 0x12($s1)
/* B907A4 800879DC 1B200208 */  j          .Llevel_11_8008806C
/* B907A8 800879E0 140022A6 */   sh        $v0, 0x14($s1)
.Llevel_11_800879E4:
/* B907AC 800879E4 C8E9000C */  jal        func_8003A720
/* B907B0 800879E8 21206002 */   addu      $a0, $s3, $zero
/* B907B4 800879EC 20000224 */  addiu      $v0, $zero, 0x20
/* B907B8 800879F0 500062A2 */  sb         $v0, 0x50($s3)
/* B907BC 800879F4 FF000224 */  addiu      $v0, $zero, 0xFF
/* B907C0 800879F8 0400A012 */  beqz       $s5, .Llevel_11_80087A0C
/* B907C4 800879FC 520062A2 */   sb        $v0, 0x52($s3)
/* B907C8 80087A00 0C006426 */  addiu      $a0, $s3, 0xC
/* B907CC 80087A04 C05D000C */  jal        VecCopy
/* B907D0 80087A08 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_11_80087A0C:
/* B907D4 80087A0C 734A010C */  jal        func_800529CC
/* B907D8 80087A10 21206002 */   addu      $a0, $s3, $zero
/* B907DC 80087A14 1C200208 */  j          .Llevel_11_80088070
/* B907E0 80087A18 21106002 */   addu      $v0, $s3, $zero
.Llevel_11_80087A1C:
/* B907E4 80087A1C 0000718E */  lw         $s1, 0x0($s3)
/* B907E8 80087A20 C8E9000C */  jal        func_8003A720
/* B907EC 80087A24 21206002 */   addu      $a0, $s3, $zero
/* B907F0 80087A28 8C000224 */  addiu      $v0, $zero, 0x8C
/* B907F4 80087A2C 000020AE */  sw         $zero, 0x0($s1)
/* B907F8 80087A30 040020AE */  sw         $zero, 0x4($s1)
/* B907FC 80087A34 080022AE */  sw         $v0, 0x8($s1)
/* B90800 80087A38 0E0020A2 */  sb         $zero, 0xE($s1)
/* B90804 80087A3C 0F0020A2 */  sb         $zero, 0xF($s1)
/* B90808 80087A40 110020A2 */  sb         $zero, 0x11($s1)
/* B9080C 80087A44 120020A2 */  sb         $zero, 0x12($s1)
/* B90810 80087A48 130020A2 */  sb         $zero, 0x13($s1)
/* B90814 80087A4C 3600A386 */  lh         $v1, 0x36($s5)
/* B90818 80087A50 0D000224 */  addiu      $v0, $zero, 0xD
/* B9081C 80087A54 02006214 */  bne        $v1, $v0, .Llevel_11_80087A60
/* B90820 80087A58 03000224 */   addiu     $v0, $zero, 0x3
/* B90824 80087A5C 02000224 */  addiu      $v0, $zero, 0x2
.Llevel_11_80087A60:
/* B90828 80087A60 100022A2 */  sb         $v0, 0x10($s1)
/* B9082C 80087A64 0C007026 */  addiu      $s0, $s3, 0xC
/* B90830 80087A68 21200002 */  addu       $a0, $s0, $zero
/* B90834 80087A6C 0C00A526 */  addiu      $a1, $s5, 0xC
/* B90838 80087A70 FF000224 */  addiu      $v0, $zero, 0xFF
/* B9083C 80087A74 140022A2 */  sb         $v0, 0x14($s1)
/* B90840 80087A78 02001124 */  addiu      $s1, $zero, 0x2
/* B90844 80087A7C 18000224 */  addiu      $v0, $zero, 0x18
/* B90848 80087A80 500062A2 */  sb         $v0, 0x50($s3)
/* B9084C 80087A84 40000224 */  addiu      $v0, $zero, 0x40
/* B90850 80087A88 520062A2 */  sb         $v0, 0x52($s3)
/* B90854 80087A8C 20000224 */  addiu      $v0, $zero, 0x20
/* B90858 80087A90 490071A2 */  sb         $s1, 0x49($s3)
/* B9085C 80087A94 440062A2 */  sb         $v0, 0x44($s3)
/* B90860 80087A98 450060A2 */  sb         $zero, 0x45($s3)
/* B90864 80087A9C C05D000C */  jal        VecCopy
/* B90868 80087AA0 460060A2 */   sb        $zero, 0x46($s3)
/* B9086C 80087AA4 734A010C */  jal        func_800529CC
/* B90870 80087AA8 21206002 */   addu      $a0, $s3, $zero
/* B90874 80087AAC 1000A427 */  addiu      $a0, $sp, 0x10
/* B90878 80087AB0 21280002 */  addu       $a1, $s0, $zero
/* B9087C 80087AB4 FFFF0224 */  addiu      $v0, $zero, -0x1
/* B90880 80087AB8 C05D000C */  jal        VecCopy
/* B90884 80087ABC 1C0062AE */   sw        $v0, 0x1C($s3)
/* B90888 80087AC0 1000A427 */  addiu      $a0, $sp, 0x10
/* B9088C 80087AC4 1800A28F */  lw         $v0, 0x18($sp)
/* B90890 80087AC8 0100053C */  lui        $a1, (0x10000 >> 16)
/* B90894 80087ACC 00044224 */  addiu      $v0, $v0, 0x400
/* B90898 80087AD0 7B35010C */  jal        func_8004D5EC
/* B9089C 80087AD4 1800A2AF */   sw        $v0, 0x18($sp)
/* B908A0 80087AD8 F44C010C */  jal        func_800533D0
/* B908A4 80087ADC 21206002 */   addu      $a0, $s3, $zero
/* B908A8 80087AE0 36006386 */  lh         $v1, 0x36($s3)
/* B908AC 80087AE4 0E000224 */  addiu      $v0, $zero, 0xE
/* B908B0 80087AE8 4C0060A2 */  sb         $zero, 0x4C($s3)
/* B908B4 80087AEC 4D0060A2 */  sb         $zero, 0x4D($s3)
/* B908B8 80087AF0 03006214 */  bne        $v1, $v0, .Llevel_11_80087B00
/* B908BC 80087AF4 4E0060A2 */   sb        $zero, 0x4E($s3)
/* B908C0 80087AF8 0C000224 */  addiu      $v0, $zero, 0xC
/* B908C4 80087AFC 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_11_80087B00:
/* B908C8 80087B00 36006386 */  lh         $v1, 0x36($s3)
/* B908CC 80087B04 53000224 */  addiu      $v0, $zero, 0x53
/* B908D0 80087B08 05006214 */  bne        $v1, $v0, .Llevel_11_80087B20
/* B908D4 80087B0C 54000224 */   addiu     $v0, $zero, 0x54
/* B908D8 80087B10 01000224 */  addiu      $v0, $zero, 0x1
/* B908DC 80087B14 4F0062A2 */  sb         $v0, 0x4F($s3)
/* B908E0 80087B18 36006386 */  lh         $v1, 0x36($s3)
/* B908E4 80087B1C 54000224 */  addiu      $v0, $zero, 0x54
.Llevel_11_80087B20:
/* B908E8 80087B20 02006214 */  bne        $v1, $v0, .Llevel_11_80087B2C
/* B908EC 80087B24 00000000 */   nop
/* B908F0 80087B28 4F0071A2 */  sb         $s1, 0x4F($s3)
.Llevel_11_80087B2C:
/* B908F4 80087B2C 36006386 */  lh         $v1, 0x36($s3)
/* B908F8 80087B30 55000224 */  addiu      $v0, $zero, 0x55
/* B908FC 80087B34 05006214 */  bne        $v1, $v0, .Llevel_11_80087B4C
/* B90900 80087B38 56000224 */   addiu     $v0, $zero, 0x56
/* B90904 80087B3C 03000224 */  addiu      $v0, $zero, 0x3
/* B90908 80087B40 4F0062A2 */  sb         $v0, 0x4F($s3)
/* B9090C 80087B44 36006386 */  lh         $v1, 0x36($s3)
/* B90910 80087B48 56000224 */  addiu      $v0, $zero, 0x56
.Llevel_11_80087B4C:
/* B90914 80087B4C 02006214 */  bne        $v1, $v0, .Llevel_11_80087B58
/* B90918 80087B50 04000224 */   addiu     $v0, $zero, 0x4
/* B9091C 80087B54 4F0062A2 */  sb         $v0, 0x4F($s3)
.Llevel_11_80087B58:
/* B90920 80087B58 36006386 */  lh         $v1, 0x36($s3)
/* B90924 80087B5C 57000224 */  addiu      $v0, $zero, 0x57
/* B90928 80087B60 43016214 */  bne        $v1, $v0, .Llevel_11_80088070
/* B9092C 80087B64 21106002 */   addu      $v0, $s3, $zero
/* B90930 80087B68 05000224 */  addiu      $v0, $zero, 0x5
/* B90934 80087B6C 1B200208 */  j          .Llevel_11_8008806C
/* B90938 80087B70 4F0062A2 */   sb        $v0, 0x4F($s3)
.Llevel_11_80087B74:
/* B9093C 80087B74 0000708E */  lw         $s0, 0x0($s3)
/* B90940 80087B78 C8E9000C */  jal        func_8003A720
/* B90944 80087B7C 21206002 */   addu      $a0, $s3, $zero
/* B90948 80087B80 AA49010C */  jal        func_800526A8
/* B9094C 80087B84 21206002 */   addu      $a0, $s3, $zero
/* B90950 80087B88 490060A2 */  sb         $zero, 0x49($s3)
/* B90954 80087B8C 000000AE */  sw         $zero, 0x0($s0)
/* B90958 80087B90 080000A6 */  sh         $zero, 0x8($s0)
/* B9095C 80087B94 060000A6 */  sh         $zero, 0x6($s0)
/* B90960 80087B98 040000A6 */  sh         $zero, 0x4($s0)
/* B90964 80087B9C 0C0000AE */  sw         $zero, 0xC($s0)
/* B90968 80087BA0 3201A012 */  beqz       $s5, .Llevel_11_8008806C
/* B9096C 80087BA4 100000AE */   sw        $zero, 0x10($s0)
/* B90970 80087BA8 0C006426 */  addiu      $a0, $s3, 0xC
/* B90974 80087BAC C05D000C */  jal        VecCopy
/* B90978 80087BB0 0C00A526 */   addiu     $a1, $s5, 0xC
/* B9097C 80087BB4 1C200208 */  j          .Llevel_11_80088070
/* B90980 80087BB8 21106002 */   addu      $v0, $s3, $zero
.Llevel_11_80087BBC:
/* B90984 80087BBC C8E9000C */  jal        func_8003A720
/* B90988 80087BC0 21206002 */   addu      $a0, $s3, $zero
/* B9098C 80087BC4 0880053C */  lui        $a1, %hi(g_Spyro + 0x17C)
/* B90990 80087BC8 D48BA524 */  addiu      $a1, $a1, %lo(g_Spyro + 0x17C)
/* B90994 80087BCC C05D000C */  jal        VecCopy
/* B90998 80087BD0 0C006426 */   addiu     $a0, $s3, 0xC
/* B9099C 80087BD4 0880043C */  lui        $a0, %hi(g_Spyro + 0x188)
/* B909A0 80087BD8 E08B848C */  lw         $a0, %lo(g_Spyro + 0x188)($a0)
/* B909A4 80087BDC 0880053C */  lui        $a1, %hi(g_Spyro + 0x18C)
/* B909A8 80087BE0 E48BA58C */  lw         $a1, %lo(g_Spyro + 0x18C)($a1)
/* B909AC 80087BE4 AD5A000C */  jal        func_80016AB4
/* B909B0 80087BE8 21300000 */   addu      $a2, $zero, $zero
/* B909B4 80087BEC 21206002 */  addu       $a0, $s3, $zero
/* B909B8 80087BF0 40004224 */  addiu      $v0, $v0, 0x40
/* B909BC 80087BF4 19200208 */  j          .Llevel_11_80088064
/* B909C0 80087BF8 460062A2 */   sb        $v0, 0x46($s3)
.Llevel_11_80087BFC:
/* B909C4 80087BFC 0000748E */  lw         $s4, 0x0($s3)
/* B909C8 80087C00 C8E9000C */  jal        func_8003A720
/* B909CC 80087C04 21206002 */   addu      $a0, $s3, $zero
/* B909D0 80087C08 0C006426 */  addiu      $a0, $s3, 0xC
/* B909D4 80087C0C 0C00A526 */  addiu      $a1, $s5, 0xC
/* B909D8 80087C10 20000224 */  addiu      $v0, $zero, 0x20
/* B909DC 80087C14 C05D000C */  jal        VecCopy
/* B909E0 80087C18 500062A2 */   sb        $v0, 0x50($s3)
/* B909E4 80087C1C AA49010C */  jal        func_800526A8
/* B909E8 80087C20 21206002 */   addu      $a0, $s3, $zero
/* B909EC 80087C24 CB89010C */  jal        rand
/* B909F0 80087C28 00000000 */   nop
/* B909F4 80087C2C CB89010C */  jal        rand
/* B909F8 80087C30 FF0F5230 */   andi      $s2, $v0, 0xFFF
/* B909FC 80087C34 FF075130 */  andi       $s1, $v0, 0x7FF
/* B90A00 80087C38 2C5B000C */  jal        Cos
/* B90A04 80087C3C 21202002 */   addu      $a0, $s1, $zero
/* B90A08 80087C40 21204002 */  addu       $a0, $s2, $zero
/* B90A0C 80087C44 2C5B000C */  jal        Cos
/* B90A10 80087C48 21804000 */   addu      $s0, $v0, $zero
/* B90A14 80087C4C 43811000 */  sra        $s0, $s0, 5
/* B90A18 80087C50 18000202 */  mult       $s0, $v0
/* B90A1C 80087C54 21202002 */  addu       $a0, $s1, $zero
/* B90A20 80087C58 12380000 */  mflo       $a3
/* B90A24 80087C5C 03130700 */  sra        $v0, $a3, 12
/* B90A28 80087C60 2C5B000C */  jal        Cos
/* B90A2C 80087C64 000082A6 */   sh        $v0, 0x0($s4)
/* B90A30 80087C68 21204002 */  addu       $a0, $s2, $zero
/* B90A34 80087C6C 165B000C */  jal        Sin
/* B90A38 80087C70 21804000 */   addu      $s0, $v0, $zero
/* B90A3C 80087C74 43811000 */  sra        $s0, $s0, 5
/* B90A40 80087C78 18000202 */  mult       $s0, $v0
/* B90A44 80087C7C 21202002 */  addu       $a0, $s1, $zero
/* B90A48 80087C80 12380000 */  mflo       $a3
/* B90A4C 80087C84 03130700 */  sra        $v0, $a3, 12
/* B90A50 80087C88 165B000C */  jal        Sin
/* B90A54 80087C8C 020082A6 */   sh        $v0, 0x2($s4)
/* B90A58 80087C90 43110200 */  sra        $v0, $v0, 5
/* B90A5C 80087C94 040082A6 */  sh         $v0, 0x4($s4)
/* B90A60 80087C98 1800A28E */  lw         $v0, 0x18($s5)
/* B90A64 80087C9C 0200033C */  lui        $v1, (0x20000 >> 16)
/* B90A68 80087CA0 24104300 */  and        $v0, $v0, $v1
/* B90A6C 80087CA4 13004010 */  beqz       $v0, .Llevel_11_80087CF4
/* B90A70 80087CA8 00000000 */   nop
/* B90A74 80087CAC 0880023C */  lui        $v0, %hi(g_Spyro + 0xF4)
/* B90A78 80087CB0 4C8B428C */  lw         $v0, %lo(g_Spyro + 0xF4)($v0)
/* B90A7C 80087CB4 00008396 */  lhu        $v1, 0x0($s4)
/* B90A80 80087CB8 83110200 */  sra        $v0, $v0, 6
/* B90A84 80087CBC 21186200 */  addu       $v1, $v1, $v0
/* B90A88 80087CC0 000083A6 */  sh         $v1, 0x0($s4)
/* B90A8C 80087CC4 0880023C */  lui        $v0, %hi(g_Spyro + 0xF8)
/* B90A90 80087CC8 508B428C */  lw         $v0, %lo(g_Spyro + 0xF8)($v0)
/* B90A94 80087CCC 02008396 */  lhu        $v1, 0x2($s4)
/* B90A98 80087CD0 83110200 */  sra        $v0, $v0, 6
/* B90A9C 80087CD4 21186200 */  addu       $v1, $v1, $v0
/* B90AA0 80087CD8 020083A6 */  sh         $v1, 0x2($s4)
/* B90AA4 80087CDC 0880023C */  lui        $v0, %hi(g_Spyro + 0xFC)
/* B90AA8 80087CE0 548B428C */  lw         $v0, %lo(g_Spyro + 0xFC)($v0)
/* B90AAC 80087CE4 04008396 */  lhu        $v1, 0x4($s4)
/* B90AB0 80087CE8 83110200 */  sra        $v0, $v0, 6
/* B90AB4 80087CEC 21186200 */  addu       $v1, $v1, $v0
/* B90AB8 80087CF0 040083A6 */  sh         $v1, 0x4($s4)
.Llevel_11_80087CF4:
/* B90ABC 80087CF4 00008286 */  lh         $v0, 0x0($s4)
/* B90AC0 80087CF8 0C00638E */  lw         $v1, 0xC($s3)
/* B90AC4 80087CFC 80100200 */  sll        $v0, $v0, 2
/* B90AC8 80087D00 21186200 */  addu       $v1, $v1, $v0
/* B90ACC 80087D04 0C0063AE */  sw         $v1, 0xC($s3)
/* B90AD0 80087D08 02008286 */  lh         $v0, 0x2($s4)
/* B90AD4 80087D0C 1000638E */  lw         $v1, 0x10($s3)
/* B90AD8 80087D10 80100200 */  sll        $v0, $v0, 2
/* B90ADC 80087D14 21186200 */  addu       $v1, $v1, $v0
/* B90AE0 80087D18 100063AE */  sw         $v1, 0x10($s3)
/* B90AE4 80087D1C 04008286 */  lh         $v0, 0x4($s4)
/* B90AE8 80087D20 1400638E */  lw         $v1, 0x14($s3)
/* B90AEC 80087D24 80100200 */  sll        $v0, $v0, 2
/* B90AF0 80087D28 21186200 */  addu       $v1, $v1, $v0
/* B90AF4 80087D2C CB89010C */  jal        rand
/* B90AF8 80087D30 140063AE */   sw        $v1, 0x14($s3)
/* B90AFC 80087D34 0F004230 */  andi       $v0, $v0, 0xF
/* B90B00 80087D38 CB89010C */  jal        rand
/* B90B04 80087D3C 060082A6 */   sh        $v0, 0x6($s4)
/* B90B08 80087D40 0F004230 */  andi       $v0, $v0, 0xF
/* B90B0C 80087D44 CB89010C */  jal        rand
/* B90B10 80087D48 080082A6 */   sh        $v0, 0x8($s4)
/* B90B14 80087D4C 0F004230 */  andi       $v0, $v0, 0xF
/* B90B18 80087D50 0A0082A6 */  sh         $v0, 0xA($s4)
/* B90B1C 80087D54 1400A28E */  lw         $v0, 0x14($s5)
/* B90B20 80087D58 00000000 */  nop
/* B90B24 80087D5C C0FF4224 */  addiu      $v0, $v0, -0x40
/* B90B28 80087D60 CB89010C */  jal        rand
/* B90B2C 80087D64 100082AE */   sw        $v0, 0x10($s4)
/* B90B30 80087D68 0F004230 */  andi       $v0, $v0, 0xF
/* B90B34 80087D6C 40000324 */  addiu      $v1, $zero, 0x40
/* B90B38 80087D70 23186200 */  subu       $v1, $v1, $v0
/* B90B3C 80087D74 0C0083AE */  sw         $v1, 0xC($s4)
/* B90B40 80087D78 36006296 */  lhu        $v0, 0x36($s3)
/* B90B44 80087D7C 00000000 */  nop
/* B90B48 80087D80 CBFE4224 */  addiu      $v0, $v0, -0x135
/* B90B4C 80087D84 0300422C */  sltiu      $v0, $v0, 0x3
/* B90B50 80087D88 B8004010 */  beqz       $v0, .Llevel_11_8008806C
/* B90B54 80087D8C A100033C */   lui       $v1, (0xA18618 >> 16)
/* B90B58 80087D90 4B006292 */  lbu        $v0, 0x4B($s3)
/* B90B5C 80087D94 18866334 */  ori        $v1, $v1, (0xA18618 & 0xFFFF)
/* B90B60 80087D98 4C0063AE */  sw         $v1, 0x4C($s3)
.Llevel_11_80087D9C:
/* B90B64 80087D9C 80004234 */  ori        $v0, $v0, 0x80
/* B90B68 80087DA0 1B200208 */  j          .Llevel_11_8008806C
/* B90B6C 80087DA4 4B0062A2 */   sb        $v0, 0x4B($s3)
.Llevel_11_80087DA8:
/* B90B70 80087DA8 0000718E */  lw         $s1, 0x0($s3)
/* B90B74 80087DAC C8E9000C */  jal        func_8003A720
/* B90B78 80087DB0 21206002 */   addu      $a0, $s3, $zero
/* B90B7C 80087DB4 21206002 */  addu       $a0, $s3, $zero
/* B90B80 80087DB8 20000224 */  addiu      $v0, $zero, 0x20
/* B90B84 80087DBC 500062A2 */  sb         $v0, 0x50($s3)
/* B90B88 80087DC0 FF000224 */  addiu      $v0, $zero, 0xFF
/* B90B8C 80087DC4 734A010C */  jal        func_800529CC
/* B90B90 80087DC8 520062A2 */   sb        $v0, 0x52($s3)
/* B90B94 80087DCC 0E000224 */  addiu      $v0, $zero, 0xE
/* B90B98 80087DD0 4C0060A2 */  sb         $zero, 0x4C($s3)
/* B90B9C 80087DD4 4D0060A2 */  sb         $zero, 0x4D($s3)
/* B90BA0 80087DD8 4E0060A2 */  sb         $zero, 0x4E($s3)
/* B90BA4 80087DDC 4F0062A2 */  sb         $v0, 0x4F($s3)
/* B90BA8 80087DE0 0780033C */  lui        $v1, %hi(D_80077058)
/* B90BAC 80087DE4 5870638C */  lw         $v1, %lo(D_80077058)($v1)
/* B90BB0 80087DE8 03000224 */  addiu      $v0, $zero, 0x3
/* B90BB4 80087DEC 03006214 */  bne        $v1, $v0, .Llevel_11_80087DFC
/* B90BB8 80087DF0 01000224 */   addiu     $v0, $zero, 0x1
/* B90BBC 80087DF4 811F0208 */  j          .Llevel_11_80087E04
/* B90BC0 80087DF8 14000224 */   addiu     $v0, $zero, 0x14
.Llevel_11_80087DFC:
/* B90BC4 80087DFC 02006214 */  bne        $v1, $v0, .Llevel_11_80087E08
/* B90BC8 80087E00 30000224 */   addiu     $v0, $zero, 0x30
.Llevel_11_80087E04:
/* B90BCC 80087E04 570062A2 */  sb         $v0, 0x57($s3)
.Llevel_11_80087E08:
/* B90BD0 80087E08 CB89010C */  jal        rand
/* B90BD4 80087E0C 00000000 */   nop
/* B90BD8 80087E10 2000A426 */  addiu      $a0, $s5, 0x20
/* B90BDC 80087E14 07004230 */  andi       $v0, $v0, 0x7
/* B90BE0 80087E18 80100200 */  sll        $v0, $v0, 2
/* B90BE4 80087E1C 2000B027 */  addiu      $s0, $sp, 0x20
/* B90BE8 80087E20 0780013C */  lui        $at, %hi(D_8006F3A0)
/* B90BEC 80087E24 21082200 */  addu       $at, $at, $v0
/* B90BF0 80087E28 A0F32384 */  lh         $v1, %lo(D_8006F3A0)($at)
/* B90BF4 80087E2C 21280002 */  addu       $a1, $s0, $zero
/* B90BF8 80087E30 2400A0AF */  sw         $zero, 0x24($sp)
/* B90BFC 80087E34 2000A3AF */  sw         $v1, 0x20($sp)
/* B90C00 80087E38 0780013C */  lui        $at, %hi(D_8006F3A0 + 0x02)
/* B90C04 80087E3C 21082200 */  addu       $at, $at, $v0
/* B90C08 80087E40 A2F32284 */  lh         $v0, %lo(D_8006F3A0 + 0x02)($at)
/* B90C0C 80087E44 21300002 */  addu       $a2, $s0, $zero
/* B90C10 80087E48 125C000C */  jal        VecRotateByMatrix
/* B90C14 80087E4C 2800A2AF */   sw        $v0, 0x28($sp)
/* B90C18 80087E50 CB89010C */  jal        rand
/* B90C1C 80087E54 00000000 */   nop
/* B90C20 80087E58 2000A38F */  lw         $v1, 0x20($sp)
/* B90C24 80087E5C 7F004230 */  andi       $v0, $v0, 0x7F
/* B90C28 80087E60 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* B90C2C 80087E64 21186200 */  addu       $v1, $v1, $v0
/* B90C30 80087E68 CB89010C */  jal        rand
/* B90C34 80087E6C 2000A3AF */   sw        $v1, 0x20($sp)
/* B90C38 80087E70 2400A38F */  lw         $v1, 0x24($sp)
/* B90C3C 80087E74 7F004230 */  andi       $v0, $v0, 0x7F
/* B90C40 80087E78 C1FF6324 */  addiu      $v1, $v1, -0x3F
/* B90C44 80087E7C 21186200 */  addu       $v1, $v1, $v0
/* B90C48 80087E80 CB89010C */  jal        rand
/* B90C4C 80087E84 2400A3AF */   sw        $v1, 0x24($sp)
/* B90C50 80087E88 0C006426 */  addiu      $a0, $s3, 0xC
/* B90C54 80087E8C 0C00A526 */  addiu      $a1, $s5, 0xC
/* B90C58 80087E90 21300002 */  addu       $a2, $s0, $zero
/* B90C5C 80087E94 2800A38F */  lw         $v1, 0x28($sp)
/* B90C60 80087E98 7F004230 */  andi       $v0, $v0, 0x7F
/* B90C64 80087E9C C1FF6324 */  addiu      $v1, $v1, -0x3F
/* B90C68 80087EA0 21186200 */  addu       $v1, $v1, $v0
/* B90C6C 80087EA4 D65D000C */  jal        VecAdd
/* B90C70 80087EA8 2800A3AF */   sw        $v1, 0x28($sp)
/* B90C74 80087EAC 21202002 */  addu       $a0, $s1, $zero
/* B90C78 80087EB0 C05D000C */  jal        VecCopy
/* B90C7C 80087EB4 21280002 */   addu      $a1, $s0, $zero
/* B90C80 80087EB8 21202002 */  addu       $a0, $s1, $zero
/* B90C84 80087EBC B25D000C */  jal        VecShiftRight
/* B90C88 80087EC0 02000524 */   addiu     $a1, $zero, 0x2
/* B90C8C 80087EC4 CB89010C */  jal        rand
/* B90C90 80087EC8 00000000 */   nop
/* B90C94 80087ECC 0000238E */  lw         $v1, 0x0($s1)
/* B90C98 80087ED0 FF004230 */  andi       $v0, $v0, 0xFF
/* B90C9C 80087ED4 81FF6324 */  addiu      $v1, $v1, -0x7F
/* B90CA0 80087ED8 21186200 */  addu       $v1, $v1, $v0
/* B90CA4 80087EDC CB89010C */  jal        rand
/* B90CA8 80087EE0 000023AE */   sw        $v1, 0x0($s1)
/* B90CAC 80087EE4 0400238E */  lw         $v1, 0x4($s1)
/* B90CB0 80087EE8 FF004230 */  andi       $v0, $v0, 0xFF
/* B90CB4 80087EEC 81FF6324 */  addiu      $v1, $v1, -0x7F
/* B90CB8 80087EF0 21186200 */  addu       $v1, $v1, $v0
/* B90CBC 80087EF4 CB89010C */  jal        rand
/* B90CC0 80087EF8 040023AE */   sw        $v1, 0x4($s1)
/* B90CC4 80087EFC 0800238E */  lw         $v1, 0x8($s1)
/* B90CC8 80087F00 FF004230 */  andi       $v0, $v0, 0xFF
/* B90CCC 80087F04 81FF6324 */  addiu      $v1, $v1, -0x7F
/* B90CD0 80087F08 21186200 */  addu       $v1, $v1, $v0
/* B90CD4 80087F0C CB89010C */  jal        rand
/* B90CD8 80087F10 080023AE */   sw        $v1, 0x8($s1)
/* B90CDC 80087F14 CB89010C */  jal        rand
/* B90CE0 80087F18 440062A2 */   sb        $v0, 0x44($s3)
/* B90CE4 80087F1C CB89010C */  jal        rand
/* B90CE8 80087F20 450062A2 */   sb        $v0, 0x45($s3)
/* B90CEC 80087F24 CB89010C */  jal        rand
/* B90CF0 80087F28 460062A2 */   sb        $v0, 0x46($s3)
/* B90CF4 80087F2C 0F004230 */  andi       $v0, $v0, 0xF
/* B90CF8 80087F30 CB89010C */  jal        rand
/* B90CFC 80087F34 100022A2 */   sb        $v0, 0x10($s1)
/* B90D00 80087F38 0F004230 */  andi       $v0, $v0, 0xF
/* B90D04 80087F3C CB89010C */  jal        rand
/* B90D08 80087F40 110022A2 */   sb        $v0, 0x11($s1)
/* B90D0C 80087F44 0F004230 */  andi       $v0, $v0, 0xF
/* B90D10 80087F48 120022A2 */  sb         $v0, 0x12($s1)
/* B90D14 80087F4C 1400A28E */  lw         $v0, 0x14($s5)
/* B90D18 80087F50 CB89010C */  jal        rand
/* B90D1C 80087F54 0C0022AE */   sw        $v0, 0xC($s1)
/* B90D20 80087F58 03004230 */  andi       $v0, $v0, 0x3
/* B90D24 80087F5C 10004224 */  addiu      $v0, $v0, 0x10
/* B90D28 80087F60 1B200208 */  j          .Llevel_11_8008806C
/* B90D2C 80087F64 130022A2 */   sb        $v0, 0x13($s1)
.Llevel_11_80087F68:
/* B90D30 80087F68 0000708E */  lw         $s0, 0x0($s3)
/* B90D34 80087F6C C8E9000C */  jal        func_8003A720
/* B90D38 80087F70 21206002 */   addu      $a0, $s3, $zero
/* B90D3C 80087F74 734A010C */  jal        func_800529CC
/* B90D40 80087F78 21206002 */   addu      $a0, $s3, $zero
/* B90D44 80087F7C 02000224 */  addiu      $v0, $zero, 0x2
/* B90D48 80087F80 4F0062A2 */  sb         $v0, 0x4F($s3)
/* B90D4C 80087F84 40000224 */  addiu      $v0, $zero, 0x40
/* B90D50 80087F88 4C0060A2 */  sb         $zero, 0x4C($s3)
/* B90D54 80087F8C 4D0060A2 */  sb         $zero, 0x4D($s3)
/* B90D58 80087F90 4E0060A2 */  sb         $zero, 0x4E($s3)
/* B90D5C 80087F94 1B200208 */  j          .Llevel_11_8008806C
/* B90D60 80087F98 000002AE */   sw        $v0, 0x0($s0)
.Llevel_11_80087F9C:
/* B90D64 80087F9C C8E9000C */  jal        func_8003A720
/* B90D68 80087FA0 21206002 */   addu      $a0, $s3, $zero
/* B90D6C 80087FA4 0300A012 */  beqz       $s5, .Llevel_11_80087FB4
/* B90D70 80087FA8 0C006426 */   addiu     $a0, $s3, 0xC
/* B90D74 80087FAC EF1F0208 */  j          .Llevel_11_80087FBC
/* B90D78 80087FB0 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_11_80087FB4:
/* B90D7C 80087FB4 0880053C */  lui        $a1, %hi(g_Spyro)
/* B90D80 80087FB8 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_11_80087FBC:
/* B90D84 80087FBC C05D000C */  jal        VecCopy
/* B90D88 80087FC0 00000000 */   nop
/* B90D8C 80087FC4 0C006426 */  addiu      $a0, $s3, 0xC
/* B90D90 80087FC8 1400628E */  lw         $v0, 0x14($s3)
/* B90D94 80087FCC 00080524 */  addiu      $a1, $zero, 0x800
/* B90D98 80087FD0 00024224 */  addiu      $v0, $v0, 0x200
/* B90D9C 80087FD4 7B35010C */  jal        func_8004D5EC
/* B90DA0 80087FD8 140062AE */   sw        $v0, 0x14($s3)
/* B90DA4 80087FDC 1400648E */  lw         $a0, 0x14($s3)
/* B90DA8 80087FE0 21184000 */  addu       $v1, $v0, $zero
/* B90DAC 80087FE4 23106400 */  subu       $v0, $v1, $a0
/* B90DB0 80087FE8 02004104 */  bgez       $v0, .Llevel_11_80087FF4
/* B90DB4 80087FEC 00000000 */   nop
/* B90DB8 80087FF0 23100200 */  negu       $v0, $v0
.Llevel_11_80087FF4:
/* B90DBC 80087FF4 00084228 */  slti       $v0, $v0, 0x800
/* B90DC0 80087FF8 03004010 */  beqz       $v0, .Llevel_11_80088008
/* B90DC4 80087FFC 00FE8224 */   addiu     $v0, $a0, -0x200
/* B90DC8 80088000 18200208 */  j          .Llevel_11_80088060
/* B90DCC 80088004 140063AE */   sw        $v1, 0x14($s3)
.Llevel_11_80088008:
/* B90DD0 80088008 18200208 */  j          .Llevel_11_80088060
/* B90DD4 8008800C 140062AE */   sw        $v0, 0x14($s3)
.Llevel_11_80088010:
/* B90DD8 80088010 C8E9000C */  jal        func_8003A720
/* B90DDC 80088014 21206002 */   addu      $a0, $s3, $zero
/* B90DE0 80088018 21206002 */  addu       $a0, $s3, $zero
/* B90DE4 8008801C 20000224 */  addiu      $v0, $zero, 0x20
/* B90DE8 80088020 500062A2 */  sb         $v0, 0x50($s3)
/* B90DEC 80088024 FF000224 */  addiu      $v0, $zero, 0xFF
/* B90DF0 80088028 734A010C */  jal        func_800529CC
/* B90DF4 8008802C 520062A2 */   sb        $v0, 0x52($s3)
/* B90DF8 80088030 1C200208 */  j          .Llevel_11_80088070
/* B90DFC 80088034 21106002 */   addu      $v0, $s3, $zero
.Llevel_11_80088038:
/* B90E00 80088038 C8E9000C */  jal        func_8003A720
/* B90E04 8008803C 21206002 */   addu      $a0, $s3, $zero
/* B90E08 80088040 0300A012 */  beqz       $s5, .Llevel_11_80088050
/* B90E0C 80088044 0C006426 */   addiu     $a0, $s3, 0xC
/* B90E10 80088048 16200208 */  j          .Llevel_11_80088058
/* B90E14 8008804C 0C00A526 */   addiu     $a1, $s5, 0xC
.Llevel_11_80088050:
/* B90E18 80088050 0880053C */  lui        $a1, %hi(g_Spyro)
/* B90E1C 80088054 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
.Llevel_11_80088058:
/* B90E20 80088058 C05D000C */  jal        VecCopy
/* B90E24 8008805C 00000000 */   nop
.Llevel_11_80088060:
/* B90E28 80088060 21206002 */  addu       $a0, $s3, $zero
.Llevel_11_80088064:
/* B90E2C 80088064 AA49010C */  jal        func_800526A8
/* B90E30 80088068 00000000 */   nop
.Llevel_11_8008806C:
/* B90E34 8008806C 21106002 */  addu       $v0, $s3, $zero
.Llevel_11_80088070:
/* B90E38 80088070 5000BF8F */  lw         $ra, 0x50($sp)
/* B90E3C 80088074 4C00B58F */  lw         $s5, 0x4C($sp)
/* B90E40 80088078 4800B48F */  lw         $s4, 0x48($sp)
/* B90E44 8008807C 4400B38F */  lw         $s3, 0x44($sp)
/* B90E48 80088080 4000B28F */  lw         $s2, 0x40($sp)
/* B90E4C 80088084 3C00B18F */  lw         $s1, 0x3C($sp)
/* B90E50 80088088 3800B08F */  lw         $s0, 0x38($sp)
/* B90E54 8008808C 5800BD27 */  addiu      $sp, $sp, 0x58
/* B90E58 80088090 0800E003 */  jr         $ra
/* B90E5C 80088094 00000000 */   nop
.size func_level_11_8008772C, . - func_level_11_8008772C
