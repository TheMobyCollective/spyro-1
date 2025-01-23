.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */
glabel func_8002A6FC
/* 1AEFC 8002A6FC 0880193C */  lui        $t9, %hi(D_80078560)
/* 1AF00 8002A700 60853927 */  addiu      $t9, $t9, %lo(D_80078560)
/* 1AF04 8002A704 00009820 */  addi       $t8, $a0, 0x0 /* handwritten instruction */
/* 1AF08 8002A708 00002F8F */  lw         $t7, 0x0($t9)
/* 1AF0C 8002A70C 04002E8F */  lw         $t6, 0x4($t9)
/* 1AF10 8002A710 80780F00 */  sll        $t7, $t7, 2
/* 1AF14 8002A714 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002A718:
/* 1AF18 8002A718 4900CF11 */  beq        $t6, $t7, .L8002A840
/* 1AF1C 8002A71C 0000CD8D */   lw        $t5, 0x0($t6)
/* 1AF20 8002A720 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1AF24 8002A724 0100A191 */  lbu        $at, 0x1($t5)
/* 1AF28 8002A728 0300A291 */  lbu        $v0, 0x3($t5)
/* 1AF2C 8002A72C 02002330 */  andi       $v1, $at, 0x2
/* 1AF30 8002A730 F9FF601C */  bgtz       $v1, .L8002A718
/* 1AF34 8002A734 00000C23 */   addi      $t4, $t8, 0x0 /* handwritten instruction */
/* 1AF38 8002A738 22104C00 */  sub        $v0, $v0, $t4 /* handwritten instruction */
/* 1AF3C 8002A73C 03004018 */  blez       $v0, .L8002A74C
/* 1AF40 8002A740 22600200 */   neg       $t4, $v0 /* handwritten instruction */
/* 1AF44 8002A744 C6A90008 */  j          .L8002A718
/* 1AF48 8002A748 0300A2A1 */   sb        $v0, 0x3($t5)
.L8002A74C:
/* 1AF4C 8002A74C 0200A391 */  lbu        $v1, 0x2($t5)
/* 1AF50 8002A750 0800AB21 */  addi       $t3, $t5, 0x8 /* handwritten instruction */
/* 1AF54 8002A754 80200300 */  sll        $a0, $v1, 2
/* 1AF58 8002A758 20208B00 */  add        $a0, $a0, $t3 /* handwritten instruction */
/* 1AF5C 8002A75C 01002130 */  andi       $at, $at, 0x1
/* 1AF60 8002A760 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1AF64 8002A764 01008390 */  lbu        $v1, 0x1($a0)
.L8002A768:
/* 1AF68 8002A768 00000000 */  nop
/* 1AF6C 8002A76C 80200300 */  sll        $a0, $v1, 2
/* 1AF70 8002A770 20208B00 */  add        $a0, $a0, $t3 /* handwritten instruction */
/* 1AF74 8002A774 00008290 */  lbu        $v0, 0x0($a0)
/* 1AF78 8002A778 00000000 */  nop
/* 1AF7C 8002A77C 03004130 */  andi       $at, $v0, 0x3
/* 1AF80 8002A780 0100A1A1 */  sb         $at, 0x1($t5)
/* 1AF84 8002A784 02002530 */  andi       $a1, $at, 0x2
/* 1AF88 8002A788 0800A01C */  bgtz       $a1, .L8002A7AC
/* 1AF8C 8002A78C 82100200 */   srl       $v0, $v0, 2
/* 1AF90 8002A790 22104C00 */  sub        $v0, $v0, $t4 /* handwritten instruction */
/* 1AF94 8002A794 0500401C */  bgtz       $v0, .L8002A7AC
/* 1AF98 8002A798 22600200 */   neg       $t4, $v0 /* handwritten instruction */
/* 1AF9C 8002A79C 01002130 */  andi       $at, $at, 0x1
/* 1AFA0 8002A7A0 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1AFA4 8002A7A4 DAA90008 */  j          .L8002A768
/* 1AFA8 8002A7A8 01008390 */   lbu       $v1, 0x1($a0)
.L8002A7AC:
/* 1AFAC 8002A7AC 0300A2A1 */  sb         $v0, 0x3($t5)
/* 1AFB0 8002A7B0 0200A3A1 */  sb         $v1, 0x2($t5)
/* 1AFB4 8002A7B4 03008390 */  lbu        $v1, 0x3($a0)
/* 1AFB8 8002A7B8 0400A48D */  lw         $a0, 0x4($t5)
/* 1AFBC 8002A7BC 0880013C */  lui        $at, %hi(g_Environment)
/* 1AFC0 8002A7C0 A8852124 */  addiu      $at, $at, %lo(g_Environment)
/* 1AFC4 8002A7C4 1C00228C */  lw         $v0, 0x1C($at)
/* 1AFC8 8002A7C8 1800218C */  lw         $at, 0x18($at)
/* 1AFCC 8002A7CC 00290300 */  sll        $a1, $v1, 4
/* 1AFD0 8002A7D0 00310400 */  sll        $a2, $a0, 4
/* 1AFD4 8002A7D4 2028A100 */  add        $a1, $a1, $at /* handwritten instruction */
/* 1AFD8 8002A7D8 2030C100 */  add        $a2, $a2, $at /* handwritten instruction */
/* 1AFDC 8002A7DC A8000120 */  addi       $at, $zero, 0xA8 /* handwritten instruction */
/* 1AFE0 8002A7E0 18002300 */  mult       $at, $v1
/* 1AFE4 8002A7E4 0000A78C */  lw         $a3, 0x0($a1)
/* 1AFE8 8002A7E8 0400A88C */  lw         $t0, 0x4($a1)
/* 1AFEC 8002A7EC 0800A98C */  lw         $t1, 0x8($a1)
/* 1AFF0 8002A7F0 0C00AA8C */  lw         $t2, 0xC($a1)
/* 1AFF4 8002A7F4 12180000 */  mflo       $v1
/* 1AFF8 8002A7F8 0000C7AC */  sw         $a3, 0x0($a2)
/* 1AFFC 8002A7FC 0400C8AC */  sw         $t0, 0x4($a2)
/* 1B000 8002A800 18002400 */  mult       $at, $a0
/* 1B004 8002A804 0800C9AC */  sw         $t1, 0x8($a2)
/* 1B008 8002A808 0C00CAAC */  sw         $t2, 0xC($a2)
/* 1B00C 8002A80C 20084300 */  add        $at, $v0, $v1 /* handwritten instruction */
/* 1B010 8002A810 12180000 */  mflo       $v1
/* 1B014 8002A814 20104300 */  add        $v0, $v0, $v1 /* handwritten instruction */
/* 1B018 8002A818 A8002320 */  addi       $v1, $at, 0xA8 /* handwritten instruction */
.L8002A81C:
/* 1B01C 8002A81C 0000248C */  lw         $a0, 0x0($at)
/* 1B020 8002A820 0400258C */  lw         $a1, 0x4($at)
/* 1B024 8002A824 000044AC */  sw         $a0, 0x0($v0)
/* 1B028 8002A828 040045AC */  sw         $a1, 0x4($v0)
/* 1B02C 8002A82C 08002120 */  addi       $at, $at, 0x8 /* handwritten instruction */
/* 1B030 8002A830 FAFF2314 */  bne        $at, $v1, .L8002A81C
/* 1B034 8002A834 08004220 */   addi      $v0, $v0, 0x8 /* handwritten instruction */
/* 1B038 8002A838 C6A90008 */  j          .L8002A718
/* 1B03C 8002A83C 00000000 */   nop
.L8002A840:
/* 1B040 8002A840 08002F8F */  lw         $t7, 0x8($t9)
/* 1B044 8002A844 0C002E8F */  lw         $t6, 0xC($t9)
/* 1B048 8002A848 80780F00 */  sll        $t7, $t7, 2
/* 1B04C 8002A84C 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002A850:
/* 1B050 8002A850 7100CF11 */  beq        $t6, $t7, .L8002AA18
/* 1B054 8002A854 0000CD8D */   lw        $t5, 0x0($t6)
/* 1B058 8002A858 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1B05C 8002A85C 0100A191 */  lbu        $at, 0x1($t5)
/* 1B060 8002A860 0300A291 */  lbu        $v0, 0x3($t5)
/* 1B064 8002A864 02002330 */  andi       $v1, $at, 0x2
/* 1B068 8002A868 F9FF601C */  bgtz       $v1, .L8002A850
/* 1B06C 8002A86C 00000C23 */   addi      $t4, $t8, 0x0 /* handwritten instruction */
/* 1B070 8002A870 22104C00 */  sub        $v0, $v0, $t4 /* handwritten instruction */
/* 1B074 8002A874 03004018 */  blez       $v0, .L8002A884
/* 1B078 8002A878 22600200 */   neg       $t4, $v0 /* handwritten instruction */
/* 1B07C 8002A87C 14AA0008 */  j          .L8002A850
/* 1B080 8002A880 0300A2A1 */   sb        $v0, 0x3($t5)
.L8002A884:
/* 1B084 8002A884 0200A391 */  lbu        $v1, 0x2($t5)
/* 1B088 8002A888 0800AB21 */  addi       $t3, $t5, 0x8 /* handwritten instruction */
/* 1B08C 8002A88C 80200300 */  sll        $a0, $v1, 2
/* 1B090 8002A890 20208B00 */  add        $a0, $a0, $t3 /* handwritten instruction */
/* 1B094 8002A894 01002130 */  andi       $at, $at, 0x1
/* 1B098 8002A898 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B09C 8002A89C 01008390 */  lbu        $v1, 0x1($a0)
/* 1B0A0 8002A8A0 00000620 */  addi       $a2, $zero, 0x0 /* handwritten instruction */
.L8002A8A4:
/* 1B0A4 8002A8A4 00000000 */  nop
/* 1B0A8 8002A8A8 80200300 */  sll        $a0, $v1, 2
/* 1B0AC 8002A8AC 20208B00 */  add        $a0, $a0, $t3 /* handwritten instruction */
/* 1B0B0 8002A8B0 00008290 */  lbu        $v0, 0x0($a0)
/* 1B0B4 8002A8B4 03008780 */  lb         $a3, 0x3($a0)
/* 1B0B8 8002A8B8 03004130 */  andi       $at, $v0, 0x3
/* 1B0BC 8002A8BC 0100A1A1 */  sb         $at, 0x1($t5)
/* 1B0C0 8002A8C0 2030C700 */  add        $a2, $a2, $a3 /* handwritten instruction */
/* 1B0C4 8002A8C4 02002530 */  andi       $a1, $at, 0x2
/* 1B0C8 8002A8C8 0800A01C */  bgtz       $a1, .L8002A8EC
/* 1B0CC 8002A8CC 82100200 */   srl       $v0, $v0, 2
/* 1B0D0 8002A8D0 22104C00 */  sub        $v0, $v0, $t4 /* handwritten instruction */
/* 1B0D4 8002A8D4 0500401C */  bgtz       $v0, .L8002A8EC
/* 1B0D8 8002A8D8 22600200 */   neg       $t4, $v0 /* handwritten instruction */
/* 1B0DC 8002A8DC 01002130 */  andi       $at, $at, 0x1
/* 1B0E0 8002A8E0 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B0E4 8002A8E4 29AA0008 */  j          .L8002A8A4
/* 1B0E8 8002A8E8 01008390 */   lbu       $v1, 0x1($a0)
.L8002A8EC:
/* 1B0EC 8002A8EC 0300A2A1 */  sb         $v0, 0x3($t5)
/* 1B0F0 8002A8F0 0200A3A1 */  sb         $v1, 0x2($t5)
/* 1B0F4 8002A8F4 0400A395 */  lhu        $v1, 0x4($t5)
/* 1B0F8 8002A8F8 0880013C */  lui        $at, %hi(g_Environment)
/* 1B0FC 8002A8FC A8852124 */  addiu      $at, $at, %lo(g_Environment)
/* 1B100 8002A900 A8000220 */  addi       $v0, $zero, 0xA8 /* handwritten instruction */
/* 1B104 8002A904 18004300 */  mult       $v0, $v1
/* 1B108 8002A908 1C00228C */  lw         $v0, 0x1C($at)
/* 1B10C 8002A90C 1800218C */  lw         $at, 0x18($at)
/* 1B110 8002A910 0600A495 */  lhu        $a0, 0x6($t5)
/* 1B114 8002A914 00190300 */  sll        $v1, $v1, 4
/* 1B118 8002A918 20082300 */  add        $at, $at, $v1 /* handwritten instruction */
/* 1B11C 8002A91C 12180000 */  mflo       $v1
/* 1B120 8002A920 20104300 */  add        $v0, $v0, $v1 /* handwritten instruction */
/* 1B124 8002A924 20188600 */  add        $v1, $a0, $a2 /* handwritten instruction */
/* 1B128 8002A928 7F006330 */  andi       $v1, $v1, 0x7F
/* 1B12C 8002A92C 0600A3A5 */  sh         $v1, 0x6($t5)
/* 1B130 8002A930 82200300 */  srl        $a0, $v1, 2
/* 1B134 8002A934 010024A0 */  sb         $a0, 0x1($at)
/* 1B138 8002A938 050024A0 */  sb         $a0, 0x5($at)
/* 1B13C 8002A93C 090024A0 */  sb         $a0, 0x9($at)
/* 1B140 8002A940 0D0024A0 */  sb         $a0, 0xD($at)
/* 1B144 8002A944 010044A0 */  sb         $a0, 0x1($v0)
/* 1B148 8002A948 050044A0 */  sb         $a0, 0x5($v0)
/* 1B14C 8002A94C 42200300 */  srl        $a0, $v1, 1
/* 1B150 8002A950 090044A0 */  sb         $a0, 0x9($v0)
/* 1B154 8002A954 0D0044A0 */  sb         $a0, 0xD($v0)
/* 1B158 8002A958 110044A0 */  sb         $a0, 0x11($v0)
/* 1B15C 8002A95C 150044A0 */  sb         $a0, 0x15($v0)
/* 1B160 8002A960 20008420 */  addi       $a0, $a0, 0x20 /* handwritten instruction */
/* 1B164 8002A964 3F008430 */  andi       $a0, $a0, 0x3F
/* 1B168 8002A968 190044A0 */  sb         $a0, 0x19($v0)
/* 1B16C 8002A96C 1D0044A0 */  sb         $a0, 0x1D($v0)
/* 1B170 8002A970 210044A0 */  sb         $a0, 0x21($v0)
/* 1B174 8002A974 250044A0 */  sb         $a0, 0x25($v0)
/* 1B178 8002A978 42200300 */  srl        $a0, $v1, 1
/* 1B17C 8002A97C 290044A0 */  sb         $a0, 0x29($v0)
/* 1B180 8002A980 2D0044A0 */  sb         $a0, 0x2D($v0)
/* 1B184 8002A984 310044A0 */  sb         $a0, 0x31($v0)
/* 1B188 8002A988 350044A0 */  sb         $a0, 0x35($v0)
/* 1B18C 8002A98C 390044A0 */  sb         $a0, 0x39($v0)
/* 1B190 8002A990 3D0044A0 */  sb         $a0, 0x3D($v0)
/* 1B194 8002A994 410044A0 */  sb         $a0, 0x41($v0)
/* 1B198 8002A998 450044A0 */  sb         $a0, 0x45($v0)
/* 1B19C 8002A99C 10008420 */  addi       $a0, $a0, 0x10 /* handwritten instruction */
/* 1B1A0 8002A9A0 3F008430 */  andi       $a0, $a0, 0x3F
/* 1B1A4 8002A9A4 490044A0 */  sb         $a0, 0x49($v0)
/* 1B1A8 8002A9A8 4D0044A0 */  sb         $a0, 0x4D($v0)
/* 1B1AC 8002A9AC 510044A0 */  sb         $a0, 0x51($v0)
/* 1B1B0 8002A9B0 550044A0 */  sb         $a0, 0x55($v0)
/* 1B1B4 8002A9B4 590044A0 */  sb         $a0, 0x59($v0)
/* 1B1B8 8002A9B8 5D0044A0 */  sb         $a0, 0x5D($v0)
/* 1B1BC 8002A9BC 610044A0 */  sb         $a0, 0x61($v0)
/* 1B1C0 8002A9C0 650044A0 */  sb         $a0, 0x65($v0)
/* 1B1C4 8002A9C4 10008420 */  addi       $a0, $a0, 0x10 /* handwritten instruction */
/* 1B1C8 8002A9C8 3F008430 */  andi       $a0, $a0, 0x3F
/* 1B1CC 8002A9CC 690044A0 */  sb         $a0, 0x69($v0)
/* 1B1D0 8002A9D0 6D0044A0 */  sb         $a0, 0x6D($v0)
/* 1B1D4 8002A9D4 710044A0 */  sb         $a0, 0x71($v0)
/* 1B1D8 8002A9D8 750044A0 */  sb         $a0, 0x75($v0)
/* 1B1DC 8002A9DC 790044A0 */  sb         $a0, 0x79($v0)
/* 1B1E0 8002A9E0 7D0044A0 */  sb         $a0, 0x7D($v0)
/* 1B1E4 8002A9E4 810044A0 */  sb         $a0, 0x81($v0)
/* 1B1E8 8002A9E8 850044A0 */  sb         $a0, 0x85($v0)
/* 1B1EC 8002A9EC 10008420 */  addi       $a0, $a0, 0x10 /* handwritten instruction */
/* 1B1F0 8002A9F0 3F008430 */  andi       $a0, $a0, 0x3F
/* 1B1F4 8002A9F4 890044A0 */  sb         $a0, 0x89($v0)
/* 1B1F8 8002A9F8 8D0044A0 */  sb         $a0, 0x8D($v0)
/* 1B1FC 8002A9FC 910044A0 */  sb         $a0, 0x91($v0)
/* 1B200 8002AA00 950044A0 */  sb         $a0, 0x95($v0)
/* 1B204 8002AA04 990044A0 */  sb         $a0, 0x99($v0)
/* 1B208 8002AA08 9D0044A0 */  sb         $a0, 0x9D($v0)
/* 1B20C 8002AA0C A10044A0 */  sb         $a0, 0xA1($v0)
/* 1B210 8002AA10 14AA0008 */  j          .L8002A850
/* 1B214 8002AA14 A50044A0 */   sb        $a0, 0xA5($v0)
.L8002AA18:
/* 1B218 8002AA18 10002F8F */  lw         $t7, 0x10($t9)
/* 1B21C 8002AA1C 14002E8F */  lw         $t6, 0x14($t9)
/* 1B220 8002AA20 FFFF0D20 */  addi       $t5, $zero, -0x1 /* handwritten instruction */
/* 1B224 8002AA24 80780F00 */  sll        $t7, $t7, 2
/* 1B228 8002AA28 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002AA2C:
/* 1B22C 8002AA2C 2E00CF11 */  beq        $t6, $t7, .L8002AAE8
/* 1B230 8002AA30 0100AD21 */   addi      $t5, $t5, 0x1 /* handwritten instruction */
/* 1B234 8002AA34 0000CC8D */  lw         $t4, 0x0($t6)
/* 1B238 8002AA38 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1B23C 8002AA3C 01008191 */  lbu        $at, 0x1($t4)
/* 1B240 8002AA40 03008291 */  lbu        $v0, 0x3($t4)
/* 1B244 8002AA44 02002330 */  andi       $v1, $at, 0x2
/* 1B248 8002AA48 F8FF601C */  bgtz       $v1, .L8002AA2C
/* 1B24C 8002AA4C 00000B23 */   addi      $t3, $t8, 0x0 /* handwritten instruction */
/* 1B250 8002AA50 22104B00 */  sub        $v0, $v0, $t3 /* handwritten instruction */
/* 1B254 8002AA54 03004018 */  blez       $v0, .L8002AA64
/* 1B258 8002AA58 22580200 */   neg       $t3, $v0 /* handwritten instruction */
/* 1B25C 8002AA5C 8BAA0008 */  j          .L8002AA2C
/* 1B260 8002AA60 030082A1 */   sb        $v0, 0x3($t4)
.L8002AA64:
/* 1B264 8002AA64 02008391 */  lbu        $v1, 0x2($t4)
/* 1B268 8002AA68 0C008A21 */  addi       $t2, $t4, 0xC /* handwritten instruction */
/* 1B26C 8002AA6C C0200300 */  sll        $a0, $v1, 3
/* 1B270 8002AA70 20208A00 */  add        $a0, $a0, $t2 /* handwritten instruction */
/* 1B274 8002AA74 01002130 */  andi       $at, $at, 0x1
/* 1B278 8002AA78 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B27C 8002AA7C 02008390 */  lbu        $v1, 0x2($a0)
.L8002AA80:
/* 1B280 8002AA80 00000000 */  nop
/* 1B284 8002AA84 C0200300 */  sll        $a0, $v1, 3
/* 1B288 8002AA88 20208A00 */  add        $a0, $a0, $t2 /* handwritten instruction */
/* 1B28C 8002AA8C 00008190 */  lbu        $at, 0x0($a0)
/* 1B290 8002AA90 01008290 */  lbu        $v0, 0x1($a0)
/* 1B294 8002AA94 02002530 */  andi       $a1, $at, 0x2
/* 1B298 8002AA98 0800A01C */  bgtz       $a1, .L8002AABC
/* 1B29C 8002AA9C 010081A1 */   sb        $at, 0x1($t4)
/* 1B2A0 8002AAA0 22104B00 */  sub        $v0, $v0, $t3 /* handwritten instruction */
/* 1B2A4 8002AAA4 0500401C */  bgtz       $v0, .L8002AABC
/* 1B2A8 8002AAA8 22580200 */   neg       $t3, $v0 /* handwritten instruction */
/* 1B2AC 8002AAAC 01002130 */  andi       $at, $at, 0x1
/* 1B2B0 8002AAB0 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B2B4 8002AAB4 A0AA0008 */  j          .L8002AA80
/* 1B2B8 8002AAB8 02008390 */   lbu       $v1, 0x2($a0)
.L8002AABC:
/* 1B2BC 8002AABC 030082A1 */  sb         $v0, 0x3($t4)
/* 1B2C0 8002AAC0 020083A1 */  sb         $v1, 0x2($t4)
/* 1B2C4 8002AAC4 04008195 */  lhu        $at, 0x4($t4)
/* 1B2C8 8002AAC8 0880023C */  lui        $v0, %hi(g_Environment)
/* 1B2CC 8002AACC A8854224 */  addiu      $v0, $v0, %lo(g_Environment)
/* 1B2D0 8002AAD0 0000428C */  lw         $v0, 0x0($v0)
/* 1B2D4 8002AAD4 80080100 */  sll        $at, $at, 2
/* 1B2D8 8002AAD8 20104100 */  add        $v0, $v0, $at /* handwritten instruction */
/* 1B2DC 8002AADC 0000418C */  lw         $at, 0x0($v0)
/* 1B2E0 8002AAE0 8BAA0008 */  j          .L8002AA2C
/* 1B2E4 8002AAE4 18002DA0 */   sb        $t5, 0x18($at)
.L8002AAE8:
/* 1B2E8 8002AAE8 18002F8F */  lw         $t7, 0x18($t9)
/* 1B2EC 8002AAEC 1C002E8F */  lw         $t6, 0x1C($t9)
/* 1B2F0 8002AAF0 FFFF0D20 */  addi       $t5, $zero, -0x1 /* handwritten instruction */
/* 1B2F4 8002AAF4 80780F00 */  sll        $t7, $t7, 2
/* 1B2F8 8002AAF8 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002AAFC:
/* 1B2FC 8002AAFC 2E00CF11 */  beq        $t6, $t7, .L8002ABB8
/* 1B300 8002AB00 0100AD21 */   addi      $t5, $t5, 0x1 /* handwritten instruction */
/* 1B304 8002AB04 0000CC8D */  lw         $t4, 0x0($t6)
/* 1B308 8002AB08 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1B30C 8002AB0C 01008191 */  lbu        $at, 0x1($t4)
/* 1B310 8002AB10 03008291 */  lbu        $v0, 0x3($t4)
/* 1B314 8002AB14 02002330 */  andi       $v1, $at, 0x2
/* 1B318 8002AB18 F8FF601C */  bgtz       $v1, .L8002AAFC
/* 1B31C 8002AB1C 00000B23 */   addi      $t3, $t8, 0x0 /* handwritten instruction */
/* 1B320 8002AB20 22104B00 */  sub        $v0, $v0, $t3 /* handwritten instruction */
/* 1B324 8002AB24 03004018 */  blez       $v0, .L8002AB34
/* 1B328 8002AB28 22580200 */   neg       $t3, $v0 /* handwritten instruction */
/* 1B32C 8002AB2C BFAA0008 */  j          .L8002AAFC
/* 1B330 8002AB30 030082A1 */   sb        $v0, 0x3($t4)
.L8002AB34:
/* 1B334 8002AB34 02008391 */  lbu        $v1, 0x2($t4)
/* 1B338 8002AB38 0C008A21 */  addi       $t2, $t4, 0xC /* handwritten instruction */
/* 1B33C 8002AB3C C0200300 */  sll        $a0, $v1, 3
/* 1B340 8002AB40 20208A00 */  add        $a0, $a0, $t2 /* handwritten instruction */
/* 1B344 8002AB44 01002130 */  andi       $at, $at, 0x1
/* 1B348 8002AB48 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B34C 8002AB4C 02008390 */  lbu        $v1, 0x2($a0)
.L8002AB50:
/* 1B350 8002AB50 00000000 */  nop
/* 1B354 8002AB54 C0200300 */  sll        $a0, $v1, 3
/* 1B358 8002AB58 20208A00 */  add        $a0, $a0, $t2 /* handwritten instruction */
/* 1B35C 8002AB5C 00008190 */  lbu        $at, 0x0($a0)
/* 1B360 8002AB60 01008290 */  lbu        $v0, 0x1($a0)
/* 1B364 8002AB64 02002530 */  andi       $a1, $at, 0x2
/* 1B368 8002AB68 0800A01C */  bgtz       $a1, .L8002AB8C
/* 1B36C 8002AB6C 010081A1 */   sb        $at, 0x1($t4)
/* 1B370 8002AB70 22104B00 */  sub        $v0, $v0, $t3 /* handwritten instruction */
/* 1B374 8002AB74 0500401C */  bgtz       $v0, .L8002AB8C
/* 1B378 8002AB78 22580200 */   neg       $t3, $v0 /* handwritten instruction */
/* 1B37C 8002AB7C 01002130 */  andi       $at, $at, 0x1
/* 1B380 8002AB80 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B384 8002AB84 D4AA0008 */  j          .L8002AB50
/* 1B388 8002AB88 02008390 */   lbu       $v1, 0x2($a0)
.L8002AB8C:
/* 1B38C 8002AB8C 030082A1 */  sb         $v0, 0x3($t4)
/* 1B390 8002AB90 020083A1 */  sb         $v1, 0x2($t4)
/* 1B394 8002AB94 04008195 */  lhu        $at, 0x4($t4)
/* 1B398 8002AB98 0880023C */  lui        $v0, %hi(g_Environment)
/* 1B39C 8002AB9C A8854224 */  addiu      $v0, $v0, %lo(g_Environment)
/* 1B3A0 8002ABA0 0000428C */  lw         $v0, 0x0($v0)
/* 1B3A4 8002ABA4 80080100 */  sll        $at, $at, 2
/* 1B3A8 8002ABA8 20104100 */  add        $v0, $v0, $at /* handwritten instruction */
/* 1B3AC 8002ABAC 0000418C */  lw         $at, 0x0($v0)
/* 1B3B0 8002ABB0 BFAA0008 */  j          .L8002AAFC
/* 1B3B4 8002ABB4 19002DA0 */   sb        $t5, 0x19($at)
.L8002ABB8:
/* 1B3B8 8002ABB8 20002F8F */  lw         $t7, 0x20($t9)
/* 1B3BC 8002ABBC 24002E8F */  lw         $t6, 0x24($t9)
/* 1B3C0 8002ABC0 FFFF0D20 */  addi       $t5, $zero, -0x1 /* handwritten instruction */
/* 1B3C4 8002ABC4 80780F00 */  sll        $t7, $t7, 2
/* 1B3C8 8002ABC8 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002ABCC:
/* 1B3CC 8002ABCC 2E00CF11 */  beq        $t6, $t7, .L8002AC88
/* 1B3D0 8002ABD0 0100AD21 */   addi      $t5, $t5, 0x1 /* handwritten instruction */
/* 1B3D4 8002ABD4 0000CC8D */  lw         $t4, 0x0($t6)
/* 1B3D8 8002ABD8 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1B3DC 8002ABDC 01008191 */  lbu        $at, 0x1($t4)
/* 1B3E0 8002ABE0 03008291 */  lbu        $v0, 0x3($t4)
/* 1B3E4 8002ABE4 02002330 */  andi       $v1, $at, 0x2
/* 1B3E8 8002ABE8 F8FF601C */  bgtz       $v1, .L8002ABCC
/* 1B3EC 8002ABEC 00000B23 */   addi      $t3, $t8, 0x0 /* handwritten instruction */
/* 1B3F0 8002ABF0 22104B00 */  sub        $v0, $v0, $t3 /* handwritten instruction */
/* 1B3F4 8002ABF4 03004018 */  blez       $v0, .L8002AC04
/* 1B3F8 8002ABF8 22580200 */   neg       $t3, $v0 /* handwritten instruction */
/* 1B3FC 8002ABFC F3AA0008 */  j          .L8002ABCC
/* 1B400 8002AC00 030082A1 */   sb        $v0, 0x3($t4)
.L8002AC04:
/* 1B404 8002AC04 02008391 */  lbu        $v1, 0x2($t4)
/* 1B408 8002AC08 0C008A21 */  addi       $t2, $t4, 0xC /* handwritten instruction */
/* 1B40C 8002AC0C C0200300 */  sll        $a0, $v1, 3
/* 1B410 8002AC10 20208A00 */  add        $a0, $a0, $t2 /* handwritten instruction */
/* 1B414 8002AC14 01002130 */  andi       $at, $at, 0x1
/* 1B418 8002AC18 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B41C 8002AC1C 02008390 */  lbu        $v1, 0x2($a0)
.L8002AC20:
/* 1B420 8002AC20 00000000 */  nop
/* 1B424 8002AC24 C0200300 */  sll        $a0, $v1, 3
/* 1B428 8002AC28 20208A00 */  add        $a0, $a0, $t2 /* handwritten instruction */
/* 1B42C 8002AC2C 00008190 */  lbu        $at, 0x0($a0)
/* 1B430 8002AC30 01008290 */  lbu        $v0, 0x1($a0)
/* 1B434 8002AC34 02002530 */  andi       $a1, $at, 0x2
/* 1B438 8002AC38 0800A01C */  bgtz       $a1, .L8002AC5C
/* 1B43C 8002AC3C 010081A1 */   sb        $at, 0x1($t4)
/* 1B440 8002AC40 22104B00 */  sub        $v0, $v0, $t3 /* handwritten instruction */
/* 1B444 8002AC44 0500401C */  bgtz       $v0, .L8002AC5C
/* 1B448 8002AC48 22580200 */   neg       $t3, $v0 /* handwritten instruction */
/* 1B44C 8002AC4C 01002130 */  andi       $at, $at, 0x1
/* 1B450 8002AC50 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B454 8002AC54 08AB0008 */  j          .L8002AC20
/* 1B458 8002AC58 02008390 */   lbu       $v1, 0x2($a0)
.L8002AC5C:
/* 1B45C 8002AC5C 030082A1 */  sb         $v0, 0x3($t4)
/* 1B460 8002AC60 020083A1 */  sb         $v1, 0x2($t4)
/* 1B464 8002AC64 04008195 */  lhu        $at, 0x4($t4)
/* 1B468 8002AC68 0880023C */  lui        $v0, %hi(g_Environment)
/* 1B46C 8002AC6C A8854224 */  addiu      $v0, $v0, %lo(g_Environment)
/* 1B470 8002AC70 0000428C */  lw         $v0, 0x0($v0)
/* 1B474 8002AC74 80080100 */  sll        $at, $at, 2
/* 1B478 8002AC78 20104100 */  add        $v0, $v0, $at /* handwritten instruction */
/* 1B47C 8002AC7C 0000418C */  lw         $at, 0x0($v0)
/* 1B480 8002AC80 F3AA0008 */  j          .L8002ABCC
/* 1B484 8002AC84 1A002DA0 */   sb        $t5, 0x1A($at)
.L8002AC88:
/* 1B488 8002AC88 28002F8F */  lw         $t7, 0x28($t9)
/* 1B48C 8002AC8C 2C002E8F */  lw         $t6, 0x2C($t9)
/* 1B490 8002AC90 FFFF0D20 */  addi       $t5, $zero, -0x1 /* handwritten instruction */
/* 1B494 8002AC94 80780F00 */  sll        $t7, $t7, 2
/* 1B498 8002AC98 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002AC9C:
/* 1B49C 8002AC9C 2E00CF11 */  beq        $t6, $t7, .L8002AD58
/* 1B4A0 8002ACA0 0100AD21 */   addi      $t5, $t5, 0x1 /* handwritten instruction */
/* 1B4A4 8002ACA4 0000CC8D */  lw         $t4, 0x0($t6)
/* 1B4A8 8002ACA8 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1B4AC 8002ACAC 01008191 */  lbu        $at, 0x1($t4)
/* 1B4B0 8002ACB0 03008291 */  lbu        $v0, 0x3($t4)
/* 1B4B4 8002ACB4 02002330 */  andi       $v1, $at, 0x2
/* 1B4B8 8002ACB8 F8FF601C */  bgtz       $v1, .L8002AC9C
/* 1B4BC 8002ACBC 00000B23 */   addi      $t3, $t8, 0x0 /* handwritten instruction */
/* 1B4C0 8002ACC0 22104B00 */  sub        $v0, $v0, $t3 /* handwritten instruction */
/* 1B4C4 8002ACC4 03004018 */  blez       $v0, .L8002ACD4
/* 1B4C8 8002ACC8 22580200 */   neg       $t3, $v0 /* handwritten instruction */
/* 1B4CC 8002ACCC 27AB0008 */  j          .L8002AC9C
/* 1B4D0 8002ACD0 030082A1 */   sb        $v0, 0x3($t4)
.L8002ACD4:
/* 1B4D4 8002ACD4 02008391 */  lbu        $v1, 0x2($t4)
/* 1B4D8 8002ACD8 0C008A21 */  addi       $t2, $t4, 0xC /* handwritten instruction */
/* 1B4DC 8002ACDC C0200300 */  sll        $a0, $v1, 3
/* 1B4E0 8002ACE0 20208A00 */  add        $a0, $a0, $t2 /* handwritten instruction */
/* 1B4E4 8002ACE4 01002130 */  andi       $at, $at, 0x1
/* 1B4E8 8002ACE8 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B4EC 8002ACEC 02008390 */  lbu        $v1, 0x2($a0)
.L8002ACF0:
/* 1B4F0 8002ACF0 00000000 */  nop
/* 1B4F4 8002ACF4 C0200300 */  sll        $a0, $v1, 3
/* 1B4F8 8002ACF8 20208A00 */  add        $a0, $a0, $t2 /* handwritten instruction */
/* 1B4FC 8002ACFC 00008190 */  lbu        $at, 0x0($a0)
/* 1B500 8002AD00 01008290 */  lbu        $v0, 0x1($a0)
/* 1B504 8002AD04 02002530 */  andi       $a1, $at, 0x2
/* 1B508 8002AD08 0800A01C */  bgtz       $a1, .L8002AD2C
/* 1B50C 8002AD0C 010081A1 */   sb        $at, 0x1($t4)
/* 1B510 8002AD10 22104B00 */  sub        $v0, $v0, $t3 /* handwritten instruction */
/* 1B514 8002AD14 0500401C */  bgtz       $v0, .L8002AD2C
/* 1B518 8002AD18 22580200 */   neg       $t3, $v0 /* handwritten instruction */
/* 1B51C 8002AD1C 01002130 */  andi       $at, $at, 0x1
/* 1B520 8002AD20 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B524 8002AD24 3CAB0008 */  j          .L8002ACF0
/* 1B528 8002AD28 02008390 */   lbu       $v1, 0x2($a0)
.L8002AD2C:
/* 1B52C 8002AD2C 030082A1 */  sb         $v0, 0x3($t4)
/* 1B530 8002AD30 020083A1 */  sb         $v1, 0x2($t4)
/* 1B534 8002AD34 04008195 */  lhu        $at, 0x4($t4)
/* 1B538 8002AD38 0880023C */  lui        $v0, %hi(g_Environment)
/* 1B53C 8002AD3C A8854224 */  addiu      $v0, $v0, %lo(g_Environment)
/* 1B540 8002AD40 0000428C */  lw         $v0, 0x0($v0)
/* 1B544 8002AD44 80080100 */  sll        $at, $at, 2
/* 1B548 8002AD48 20104100 */  add        $v0, $v0, $at /* handwritten instruction */
/* 1B54C 8002AD4C 0000418C */  lw         $at, 0x0($v0)
/* 1B550 8002AD50 27AB0008 */  j          .L8002AC9C
/* 1B554 8002AD54 1B002DA0 */   sb        $t5, 0x1B($at)
.L8002AD58:
/* 1B558 8002AD58 40002F8F */  lw         $t7, 0x40($t9)
/* 1B55C 8002AD5C 44002E8F */  lw         $t6, 0x44($t9)
/* 1B560 8002AD60 80780F00 */  sll        $t7, $t7, 2
/* 1B564 8002AD64 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002AD68:
/* 1B568 8002AD68 8701CF11 */  beq        $t6, $t7, .L8002B388
/* 1B56C 8002AD6C 0000CD8D */   lw        $t5, 0x0($t6)
/* 1B570 8002AD70 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1B574 8002AD74 0100A191 */  lbu        $at, 0x1($t5)
/* 1B578 8002AD78 0300A291 */  lbu        $v0, 0x3($t5)
/* 1B57C 8002AD7C 02002330 */  andi       $v1, $at, 0x2
/* 1B580 8002AD80 F9FF601C */  bgtz       $v1, .L8002AD68
/* 1B584 8002AD84 00000B23 */   addi      $t3, $t8, 0x0 /* handwritten instruction */
/* 1B588 8002AD88 22104B00 */  sub        $v0, $v0, $t3 /* handwritten instruction */
/* 1B58C 8002AD8C 03004018 */  blez       $v0, .L8002AD9C
/* 1B590 8002AD90 22580200 */   neg       $t3, $v0 /* handwritten instruction */
/* 1B594 8002AD94 5AAB0008 */  j          .L8002AD68
/* 1B598 8002AD98 0300A2A1 */   sb        $v0, 0x3($t5)
.L8002AD9C:
/* 1B59C 8002AD9C 0200A391 */  lbu        $v1, 0x2($t5)
/* 1B5A0 8002ADA0 0C00AA21 */  addi       $t2, $t5, 0xC /* handwritten instruction */
/* 1B5A4 8002ADA4 C0200300 */  sll        $a0, $v1, 3
/* 1B5A8 8002ADA8 20208A00 */  add        $a0, $a0, $t2 /* handwritten instruction */
/* 1B5AC 8002ADAC 01002130 */  andi       $at, $at, 0x1
/* 1B5B0 8002ADB0 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B5B4 8002ADB4 02008390 */  lbu        $v1, 0x2($a0)
.L8002ADB8:
/* 1B5B8 8002ADB8 00000000 */  nop
/* 1B5BC 8002ADBC C0200300 */  sll        $a0, $v1, 3
/* 1B5C0 8002ADC0 20208A00 */  add        $a0, $a0, $t2 /* handwritten instruction */
/* 1B5C4 8002ADC4 00008190 */  lbu        $at, 0x0($a0)
/* 1B5C8 8002ADC8 01008290 */  lbu        $v0, 0x1($a0)
/* 1B5CC 8002ADCC 02002530 */  andi       $a1, $at, 0x2
/* 1B5D0 8002ADD0 0800A01C */  bgtz       $a1, .L8002ADF4
/* 1B5D4 8002ADD4 0100A1A1 */   sb        $at, 0x1($t5)
/* 1B5D8 8002ADD8 22104B00 */  sub        $v0, $v0, $t3 /* handwritten instruction */
/* 1B5DC 8002ADDC 0500401C */  bgtz       $v0, .L8002ADF4
/* 1B5E0 8002ADE0 22580200 */   neg       $t3, $v0 /* handwritten instruction */
/* 1B5E4 8002ADE4 01002130 */  andi       $at, $at, 0x1
/* 1B5E8 8002ADE8 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 1B5EC 8002ADEC 6EAB0008 */  j          .L8002ADB8
/* 1B5F0 8002ADF0 02008390 */   lbu       $v1, 0x2($a0)
.L8002ADF4:
/* 1B5F4 8002ADF4 0300A2A1 */  sb         $v0, 0x3($t5)
/* 1B5F8 8002ADF8 0200A3A1 */  sb         $v1, 0x2($t5)
/* 1B5FC 8002ADFC 04008A8C */  lw         $t2, 0x4($a0)
/* 1B600 8002AE00 0400A18D */  lw         $at, 0x4($t5)
/* 1B604 8002AE04 FF004C31 */  andi       $t4, $t2, 0xFF
/* 1B608 8002AE08 025A0A00 */  srl        $t3, $t2, 8
/* 1B60C 8002AE0C FF006B31 */  andi       $t3, $t3, 0xFF
/* 1B610 8002AE10 02540A00 */  srl        $t2, $t2, 16
/* 1B614 8002AE14 FF004A31 */  andi       $t2, $t2, 0xFF
/* 1B618 8002AE18 0800A58D */  lw         $a1, 0x8($t5)
/* 1B61C 8002AE1C FFFF2230 */  andi       $v0, $at, 0xFFFF
/* 1B620 8002AE20 020C0100 */  srl        $at, $at, 16
/* 1B624 8002AE24 80180200 */  sll        $v1, $v0, 2
/* 1B628 8002AE28 C0100200 */  sll        $v0, $v0, 3
/* 1B62C 8002AE2C 20104300 */  add        $v0, $v0, $v1 /* handwritten instruction */
/* 1B630 8002AE30 0880063C */  lui        $a2, %hi(g_Environment)
/* 1B634 8002AE34 A885C624 */  addiu      $a2, $a2, %lo(g_Environment)
/* 1B638 8002AE38 2028AD00 */  add        $a1, $a1, $t5 /* handwritten instruction */
/* 1B63C 8002AE3C 6900801D */  bgtz       $t4, .L8002AFE4
/* 1B640 8002AE40 2C00C68C */   lw        $a2, 0x2C($a2)
/* 1B644 8002AE44 18004B00 */  mult       $v0, $t3
/* 1B648 8002AE48 80180100 */  sll        $v1, $at, 2
/* 1B64C 8002AE4C C0080100 */  sll        $at, $at, 3
/* 1B650 8002AE50 20082300 */  add        $at, $at, $v1 /* handwritten instruction */
/* 1B654 8002AE54 12580000 */  mflo       $t3
/* 1B658 8002AE58 1000C68C */  lw         $a2, 0x10($a2)
/* 1B65C 8002AE5C 2020AB00 */  add        $a0, $a1, $t3 /* handwritten instruction */
/* 1B660 8002AE60 20208200 */  add        $a0, $a0, $v0 /* handwritten instruction */
/* 1B664 8002AE64 2010AB00 */  add        $v0, $a1, $t3 /* handwritten instruction */
/* 1B668 8002AE68 20082600 */  add        $at, $at, $a2 /* handwritten instruction */
.L8002AE6C:
/* 1B66C 8002AE6C 08004B8C */  lw         $t3, 0x8($v0)
/* 1B670 8002AE70 0400488C */  lw         $t0, 0x4($v0)
/* 1B674 8002AE74 0000458C */  lw         $a1, 0x0($v0)
/* 1B678 8002AE78 40620B00 */  sll        $t4, $t3, 9
/* 1B67C 8002AE7C C3650C00 */  sra        $t4, $t4, 23
/* 1B680 8002AE80 0B008005 */  bltz       $t4, .L8002AEB0
/* 1B684 8002AE84 C36D0B00 */   sra       $t5, $t3, 23
/* 1B688 8002AE88 0900A005 */  bltz       $t5, .L8002AEB0
/* 1B68C 8002AE8C FF3F6B31 */   andi      $t3, $t3, 0x3FFF
/* 1B690 8002AE90 000025AC */  sw         $a1, 0x0($at)
/* 1B694 8002AE94 040028AC */  sw         $t0, 0x4($at)
/* 1B698 8002AE98 00640C00 */  sll        $t4, $t4, 16
/* 1B69C 8002AE9C 006E0D00 */  sll        $t5, $t5, 24
/* 1B6A0 8002AEA0 25586C01 */  or         $t3, $t3, $t4
/* 1B6A4 8002AEA4 25586D01 */  or         $t3, $t3, $t5
/* 1B6A8 8002AEA8 F4AB0008 */  j          .L8002AFD0
/* 1B6AC 8002AEAC 08002BAC */   sw        $t3, 0x8($at)
.L8002AEB0:
/* 1B6B0 8002AEB0 2218AC01 */  sub        $v1, $t5, $t4 /* handwritten instruction */
/* 1B6B4 8002AEB4 FF3F6B31 */  andi       $t3, $t3, 0x3FFF
/* 1B6B8 8002AEB8 2068AB01 */  add        $t5, $t5, $t3 /* handwritten instruction */
/* 1B6BC 8002AEBC 20608B01 */  add        $t4, $t4, $t3 /* handwritten instruction */
/* 1B6C0 8002AEC0 C33D0500 */  sra        $a3, $a1, 23
/* 1B6C4 8002AEC4 40320500 */  sll        $a2, $a1, 9
/* 1B6C8 8002AEC8 C3350600 */  sra        $a2, $a2, 23
/* 1B6CC 8002AECC FF3FA530 */  andi       $a1, $a1, 0x3FFF
/* 1B6D0 8002AED0 2038E500 */  add        $a3, $a3, $a1 /* handwritten instruction */
/* 1B6D4 8002AED4 2030C500 */  add        $a2, $a2, $a1 /* handwritten instruction */
/* 1B6D8 8002AED8 C3550800 */  sra        $t2, $t0, 23
/* 1B6DC 8002AEDC 404A0800 */  sll        $t1, $t0, 9
/* 1B6E0 8002AEE0 C34D0900 */  sra        $t1, $t1, 23
/* 1B6E4 8002AEE4 FF3F0831 */  andi       $t0, $t0, 0x3FFF
/* 1B6E8 8002AEE8 20504801 */  add        $t2, $t2, $t0 /* handwritten instruction */
/* 1B6EC 8002AEEC 1D006004 */  bltz       $v1, .L8002AF64
/* 1B6F0 8002AEF0 20482801 */   add       $t1, $t1, $t0 /* handwritten instruction */
/* 1B6F4 8002AEF4 2228A600 */  sub        $a1, $a1, $a2 /* handwritten instruction */
/* 1B6F8 8002AEF8 C02D0500 */  sll        $a1, $a1, 23
/* 1B6FC 8002AEFC 2238E600 */  sub        $a3, $a3, $a2 /* handwritten instruction */
/* 1B700 8002AF00 FF01E730 */  andi       $a3, $a3, 0x1FF
/* 1B704 8002AF04 803B0700 */  sll        $a3, $a3, 14
/* 1B708 8002AF08 FF3FC630 */  andi       $a2, $a2, 0x3FFF
/* 1B70C 8002AF0C 2530C500 */  or         $a2, $a2, $a1
/* 1B710 8002AF10 2530C700 */  or         $a2, $a2, $a3
/* 1B714 8002AF14 000026AC */  sw         $a2, 0x0($at)
/* 1B718 8002AF18 22400901 */  sub        $t0, $t0, $t1 /* handwritten instruction */
/* 1B71C 8002AF1C C0450800 */  sll        $t0, $t0, 23
/* 1B720 8002AF20 22504901 */  sub        $t2, $t2, $t1 /* handwritten instruction */
/* 1B724 8002AF24 FF014A31 */  andi       $t2, $t2, 0x1FF
/* 1B728 8002AF28 80530A00 */  sll        $t2, $t2, 14
/* 1B72C 8002AF2C FF3F2931 */  andi       $t1, $t1, 0x3FFF
/* 1B730 8002AF30 25482801 */  or         $t1, $t1, $t0
/* 1B734 8002AF34 25482A01 */  or         $t1, $t1, $t2
/* 1B738 8002AF38 040029AC */  sw         $t1, 0x4($at)
/* 1B73C 8002AF3C 22586C01 */  sub        $t3, $t3, $t4 /* handwritten instruction */
/* 1B740 8002AF40 005E0B00 */  sll        $t3, $t3, 24
/* 1B744 8002AF44 2268AC01 */  sub        $t5, $t5, $t4 /* handwritten instruction */
/* 1B748 8002AF48 FF01AD31 */  andi       $t5, $t5, 0x1FF
/* 1B74C 8002AF4C 006C0D00 */  sll        $t5, $t5, 16
/* 1B750 8002AF50 FF3F8C31 */  andi       $t4, $t4, 0x3FFF
/* 1B754 8002AF54 25608B01 */  or         $t4, $t4, $t3
/* 1B758 8002AF58 25608D01 */  or         $t4, $t4, $t5
/* 1B75C 8002AF5C F4AB0008 */  j          .L8002AFD0
/* 1B760 8002AF60 08002CAC */   sw        $t4, 0x8($at)
.L8002AF64:
/* 1B764 8002AF64 2230C700 */  sub        $a2, $a2, $a3 /* handwritten instruction */
/* 1B768 8002AF68 C0350600 */  sll        $a2, $a2, 23
/* 1B76C 8002AF6C 2228A700 */  sub        $a1, $a1, $a3 /* handwritten instruction */
/* 1B770 8002AF70 FF01A530 */  andi       $a1, $a1, 0x1FF
/* 1B774 8002AF74 802B0500 */  sll        $a1, $a1, 14
/* 1B778 8002AF78 FF3FE730 */  andi       $a3, $a3, 0x3FFF
/* 1B77C 8002AF7C 2538E600 */  or         $a3, $a3, $a2
/* 1B780 8002AF80 2538E500 */  or         $a3, $a3, $a1
/* 1B784 8002AF84 000027AC */  sw         $a3, 0x0($at)
/* 1B788 8002AF88 22482A01 */  sub        $t1, $t1, $t2 /* handwritten instruction */
/* 1B78C 8002AF8C C04D0900 */  sll        $t1, $t1, 23
/* 1B790 8002AF90 22400A01 */  sub        $t0, $t0, $t2 /* handwritten instruction */
/* 1B794 8002AF94 FF010831 */  andi       $t0, $t0, 0x1FF
/* 1B798 8002AF98 80430800 */  sll        $t0, $t0, 14
/* 1B79C 8002AF9C FF3F4A31 */  andi       $t2, $t2, 0x3FFF
/* 1B7A0 8002AFA0 25504901 */  or         $t2, $t2, $t1
/* 1B7A4 8002AFA4 25504801 */  or         $t2, $t2, $t0
/* 1B7A8 8002AFA8 04002AAC */  sw         $t2, 0x4($at)
/* 1B7AC 8002AFAC 22608D01 */  sub        $t4, $t4, $t5 /* handwritten instruction */
/* 1B7B0 8002AFB0 00660C00 */  sll        $t4, $t4, 24
/* 1B7B4 8002AFB4 22586D01 */  sub        $t3, $t3, $t5 /* handwritten instruction */
/* 1B7B8 8002AFB8 FF016B31 */  andi       $t3, $t3, 0x1FF
/* 1B7BC 8002AFBC 005C0B00 */  sll        $t3, $t3, 16
/* 1B7C0 8002AFC0 FF3FAD31 */  andi       $t5, $t5, 0x3FFF
/* 1B7C4 8002AFC4 2568AC01 */  or         $t5, $t5, $t4
/* 1B7C8 8002AFC8 2568AB01 */  or         $t5, $t5, $t3
/* 1B7CC 8002AFCC 08002DAC */  sw         $t5, 0x8($at)
.L8002AFD0:
/* 1B7D0 8002AFD0 0C004220 */  addi       $v0, $v0, 0xC /* handwritten instruction */
/* 1B7D4 8002AFD4 A5FF4414 */  bne        $v0, $a0, .L8002AE6C
/* 1B7D8 8002AFD8 0C002120 */   addi      $at, $at, 0xC /* handwritten instruction */
/* 1B7DC 8002AFDC 5AAB0008 */  j          .L8002AD68
/* 1B7E0 8002AFE0 00000000 */   nop
.L8002AFE4:
/* 1B7E4 8002AFE4 18004A00 */  mult       $v0, $t2
/* 1B7E8 8002AFE8 80180100 */  sll        $v1, $at, 2
/* 1B7EC 8002AFEC C0080100 */  sll        $at, $at, 3
/* 1B7F0 8002AFF0 20082300 */  add        $at, $at, $v1 /* handwritten instruction */
/* 1B7F4 8002AFF4 12500000 */  mflo       $t2
/* 1B7F8 8002AFF8 1000C68C */  lw         $a2, 0x10($a2)
/* 1B7FC 8002AFFC 2018AA00 */  add        $v1, $a1, $t2 /* handwritten instruction */
/* 1B800 8002B000 18004B00 */  mult       $v0, $t3
/* 1B804 8002B004 20082600 */  add        $at, $at, $a2 /* handwritten instruction */
/* 1B808 8002B008 12580000 */  mflo       $t3
/* 1B80C 8002B00C 2020AB00 */  add        $a0, $a1, $t3 /* handwritten instruction */
/* 1B810 8002B010 20208200 */  add        $a0, $a0, $v0 /* handwritten instruction */
/* 1B814 8002B014 2010AB00 */  add        $v0, $a1, $t3 /* handwritten instruction */
/* 1B818 8002B018 00290C00 */  sll        $a1, $t4, 4
/* 1B81C 8002B01C 00100620 */  addi       $a2, $zero, 0x1000 /* handwritten instruction */
/* 1B820 8002B020 2230C500 */  sub        $a2, $a2, $a1 /* handwritten instruction */
.L8002B024:
/* 1B824 8002B024 0000478C */  lw         $a3, 0x0($v0)
/* 1B828 8002B028 00006A8C */  lw         $t2, 0x0($v1)
/* 1B82C 8002B02C C34D0700 */  sra        $t1, $a3, 23
/* 1B830 8002B030 40420700 */  sll        $t0, $a3, 9
/* 1B834 8002B034 C3450800 */  sra        $t0, $t0, 23
/* 1B838 8002B038 FF3FE730 */  andi       $a3, $a3, 0x3FFF
/* 1B83C 8002B03C 20400701 */  add        $t0, $t0, $a3 /* handwritten instruction */
/* 1B840 8002B040 20482701 */  add        $t1, $t1, $a3 /* handwritten instruction */
/* 1B844 8002B044 00408648 */  mtc2       $a2, $8 /* handwritten instruction */
/* 1B848 8002B048 00488748 */  mtc2       $a3, $9 /* handwritten instruction */
/* 1B84C 8002B04C 00508848 */  mtc2       $t0, $10 /* handwritten instruction */
/* 1B850 8002B050 00588948 */  mtc2       $t1, $11 /* handwritten instruction */
/* 1B854 8002B054 C3650A00 */  sra        $t4, $t2, 23
/* 1B858 8002B058 405A0A00 */  sll        $t3, $t2, 9
/* 1B85C 8002B05C 3D00904B */  GPF        0
/* 1B860 8002B060 C35D0B00 */  sra        $t3, $t3, 23
/* 1B864 8002B064 FF3F4A31 */  andi       $t2, $t2, 0x3FFF
/* 1B868 8002B068 20586A01 */  add        $t3, $t3, $t2 /* handwritten instruction */
/* 1B86C 8002B06C 20608A01 */  add        $t4, $t4, $t2 /* handwritten instruction */
/* 1B870 8002B070 00408548 */  mtc2       $a1, $8 /* handwritten instruction */
/* 1B874 8002B074 00488A48 */  mtc2       $t2, $9 /* handwritten instruction */
/* 1B878 8002B078 00508B48 */  mtc2       $t3, $10 /* handwritten instruction */
/* 1B87C 8002B07C 00588C48 */  mtc2       $t4, $11 /* handwritten instruction */
/* 1B880 8002B080 00000000 */  nop
/* 1B884 8002B084 801F083C */  lui        $t0, (0x1F800008 >> 16)
/* 1B888 8002B088 3E00A04B */  GPL        0
/* 1B88C 8002B08C 0400478C */  lw         $a3, 0x4($v0)
/* 1B890 8002B090 00C80B48 */  mfc2       $t3, $25 /* handwritten instruction */
/* 1B894 8002B094 00D00C48 */  mfc2       $t4, $26 /* handwritten instruction */
/* 1B898 8002B098 00D80D48 */  mfc2       $t5, $27 /* handwritten instruction */
/* 1B89C 8002B09C 04006A8C */  lw         $t2, 0x4($v1)
/* 1B8A0 8002B0A0 035B0B00 */  sra        $t3, $t3, 12
/* 1B8A4 8002B0A4 03630C00 */  sra        $t4, $t4, 12
/* 1B8A8 8002B0A8 036B0D00 */  sra        $t5, $t5, 12
/* 1B8AC 8002B0AC 00000BAD */  sw         $t3, (0x1F800000 & 0xFFFF)($t0)
/* 1B8B0 8002B0B0 04000CAD */  sw         $t4, (0x1F800004 & 0xFFFF)($t0)
/* 1B8B4 8002B0B4 08000DAD */  sw         $t5, (0x1F800008 & 0xFFFF)($t0)
/* 1B8B8 8002B0B8 C34D0700 */  sra        $t1, $a3, 23
/* 1B8BC 8002B0BC 40420700 */  sll        $t0, $a3, 9
/* 1B8C0 8002B0C0 C3450800 */  sra        $t0, $t0, 23
/* 1B8C4 8002B0C4 FF3FE730 */  andi       $a3, $a3, 0x3FFF
/* 1B8C8 8002B0C8 20400701 */  add        $t0, $t0, $a3 /* handwritten instruction */
/* 1B8CC 8002B0CC 20482701 */  add        $t1, $t1, $a3 /* handwritten instruction */
/* 1B8D0 8002B0D0 00408648 */  mtc2       $a2, $8 /* handwritten instruction */
/* 1B8D4 8002B0D4 00488748 */  mtc2       $a3, $9 /* handwritten instruction */
/* 1B8D8 8002B0D8 00508848 */  mtc2       $t0, $10 /* handwritten instruction */
/* 1B8DC 8002B0DC 00588948 */  mtc2       $t1, $11 /* handwritten instruction */
/* 1B8E0 8002B0E0 C3650A00 */  sra        $t4, $t2, 23
/* 1B8E4 8002B0E4 405A0A00 */  sll        $t3, $t2, 9
/* 1B8E8 8002B0E8 3D00904B */  GPF        0
/* 1B8EC 8002B0EC C35D0B00 */  sra        $t3, $t3, 23
/* 1B8F0 8002B0F0 FF3F4A31 */  andi       $t2, $t2, 0x3FFF
/* 1B8F4 8002B0F4 20586A01 */  add        $t3, $t3, $t2 /* handwritten instruction */
/* 1B8F8 8002B0F8 20608A01 */  add        $t4, $t4, $t2 /* handwritten instruction */
/* 1B8FC 8002B0FC 00408548 */  mtc2       $a1, $8 /* handwritten instruction */
/* 1B900 8002B100 00488A48 */  mtc2       $t2, $9 /* handwritten instruction */
/* 1B904 8002B104 00508B48 */  mtc2       $t3, $10 /* handwritten instruction */
/* 1B908 8002B108 00588C48 */  mtc2       $t4, $11 /* handwritten instruction */
/* 1B90C 8002B10C 00000000 */  nop
/* 1B910 8002B110 801F083C */  lui        $t0, (0x1F800014 >> 16)
/* 1B914 8002B114 3E00A04B */  GPL        0
/* 1B918 8002B118 0800478C */  lw         $a3, 0x8($v0)
/* 1B91C 8002B11C 00C80B48 */  mfc2       $t3, $25 /* handwritten instruction */
/* 1B920 8002B120 00D00C48 */  mfc2       $t4, $26 /* handwritten instruction */
/* 1B924 8002B124 00D80D48 */  mfc2       $t5, $27 /* handwritten instruction */
/* 1B928 8002B128 08006A8C */  lw         $t2, 0x8($v1)
/* 1B92C 8002B12C 035B0B00 */  sra        $t3, $t3, 12
/* 1B930 8002B130 03630C00 */  sra        $t4, $t4, 12
/* 1B934 8002B134 036B0D00 */  sra        $t5, $t5, 12
/* 1B938 8002B138 0C000BAD */  sw         $t3, (0x1F80000C & 0xFFFF)($t0)
/* 1B93C 8002B13C 10000CAD */  sw         $t4, (0x1F800010 & 0xFFFF)($t0)
/* 1B940 8002B140 14000DAD */  sw         $t5, (0x1F800014 & 0xFFFF)($t0)
/* 1B944 8002B144 C34D0700 */  sra        $t1, $a3, 23
/* 1B948 8002B148 40420700 */  sll        $t0, $a3, 9
/* 1B94C 8002B14C C3450800 */  sra        $t0, $t0, 23
/* 1B950 8002B150 FF3FE730 */  andi       $a3, $a3, 0x3FFF
/* 1B954 8002B154 20400701 */  add        $t0, $t0, $a3 /* handwritten instruction */
/* 1B958 8002B158 20482701 */  add        $t1, $t1, $a3 /* handwritten instruction */
/* 1B95C 8002B15C 00408648 */  mtc2       $a2, $8 /* handwritten instruction */
/* 1B960 8002B160 00488748 */  mtc2       $a3, $9 /* handwritten instruction */
/* 1B964 8002B164 00508848 */  mtc2       $t0, $10 /* handwritten instruction */
/* 1B968 8002B168 00588948 */  mtc2       $t1, $11 /* handwritten instruction */
/* 1B96C 8002B16C C3650A00 */  sra        $t4, $t2, 23
/* 1B970 8002B170 405A0A00 */  sll        $t3, $t2, 9
/* 1B974 8002B174 3D00904B */  GPF        0
/* 1B978 8002B178 C35D0B00 */  sra        $t3, $t3, 23
/* 1B97C 8002B17C FF3F4A31 */  andi       $t2, $t2, 0x3FFF
/* 1B980 8002B180 20586A01 */  add        $t3, $t3, $t2 /* handwritten instruction */
/* 1B984 8002B184 20608A01 */  add        $t4, $t4, $t2 /* handwritten instruction */
/* 1B988 8002B188 00408548 */  mtc2       $a1, $8 /* handwritten instruction */
/* 1B98C 8002B18C 00488A48 */  mtc2       $t2, $9 /* handwritten instruction */
/* 1B990 8002B190 00508B48 */  mtc2       $t3, $10 /* handwritten instruction */
/* 1B994 8002B194 00588C48 */  mtc2       $t4, $11 /* handwritten instruction */
/* 1B998 8002B198 00000000 */  nop
/* 1B99C 8002B19C 801F083C */  lui        $t0, (0x1F800000 >> 16)
/* 1B9A0 8002B1A0 3E00A04B */  GPL        0
/* 1B9A4 8002B1A4 00C80B48 */  mfc2       $t3, $25 /* handwritten instruction */
/* 1B9A8 8002B1A8 00D00C48 */  mfc2       $t4, $26 /* handwritten instruction */
/* 1B9AC 8002B1AC 00D80D48 */  mfc2       $t5, $27 /* handwritten instruction */
/* 1B9B0 8002B1B0 025B0B00 */  srl        $t3, $t3, 12
/* 1B9B4 8002B1B4 02630C00 */  srl        $t4, $t4, 12
/* 1B9B8 8002B1B8 026B0D00 */  srl        $t5, $t5, 12
/* 1B9BC 8002B1BC 22388B01 */  sub        $a3, $t4, $t3 /* handwritten instruction */
/* 1B9C0 8002B1C0 2500E004 */  bltz       $a3, .L8002B258
/* 1B9C4 8002B1C4 2238AB01 */   sub       $a3, $t5, $t3 /* handwritten instruction */
/* 1B9C8 8002B1C8 2300E004 */  bltz       $a3, .L8002B258
/* 1B9CC 8002B1CC 801F073C */   lui       $a3, (0x1F800004 >> 16)
/* 1B9D0 8002B1D0 2268AB01 */  sub        $t5, $t5, $t3 /* handwritten instruction */
/* 1B9D4 8002B1D4 006E0D00 */  sll        $t5, $t5, 24
/* 1B9D8 8002B1D8 22608B01 */  sub        $t4, $t4, $t3 /* handwritten instruction */
/* 1B9DC 8002B1DC FF008C31 */  andi       $t4, $t4, 0xFF
/* 1B9E0 8002B1E0 00640C00 */  sll        $t4, $t4, 16
/* 1B9E4 8002B1E4 FF3F6B31 */  andi       $t3, $t3, 0x3FFF
/* 1B9E8 8002B1E8 25586C01 */  or         $t3, $t3, $t4
/* 1B9EC 8002B1EC 25586D01 */  or         $t3, $t3, $t5
/* 1B9F0 8002B1F0 08002BAC */  sw         $t3, 0x8($at)
/* 1B9F4 8002B1F4 0C00EB8C */  lw         $t3, (0x1F80000C & 0xFFFF)($a3)
/* 1B9F8 8002B1F8 1400ED8C */  lw         $t5, (0x1F800014 & 0xFFFF)($a3)
/* 1B9FC 8002B1FC 1000EC8C */  lw         $t4, (0x1F800010 & 0xFFFF)($a3)
/* 1BA00 8002B200 2268AB01 */  sub        $t5, $t5, $t3 /* handwritten instruction */
/* 1BA04 8002B204 C06D0D00 */  sll        $t5, $t5, 23
/* 1BA08 8002B208 22608B01 */  sub        $t4, $t4, $t3 /* handwritten instruction */
/* 1BA0C 8002B20C FF018C31 */  andi       $t4, $t4, 0x1FF
/* 1BA10 8002B210 80630C00 */  sll        $t4, $t4, 14
/* 1BA14 8002B214 FF3F6B31 */  andi       $t3, $t3, 0x3FFF
/* 1BA18 8002B218 25586C01 */  or         $t3, $t3, $t4
/* 1BA1C 8002B21C 25586D01 */  or         $t3, $t3, $t5
/* 1BA20 8002B220 04002BAC */  sw         $t3, 0x4($at)
/* 1BA24 8002B224 0000EB8C */  lw         $t3, (0x1F800000 & 0xFFFF)($a3)
/* 1BA28 8002B228 0800ED8C */  lw         $t5, (0x1F800008 & 0xFFFF)($a3)
/* 1BA2C 8002B22C 0400EC8C */  lw         $t4, (0x1F800004 & 0xFFFF)($a3)
/* 1BA30 8002B230 2268AB01 */  sub        $t5, $t5, $t3 /* handwritten instruction */
/* 1BA34 8002B234 C06D0D00 */  sll        $t5, $t5, 23
/* 1BA38 8002B238 22608B01 */  sub        $t4, $t4, $t3 /* handwritten instruction */
/* 1BA3C 8002B23C FF018C31 */  andi       $t4, $t4, 0x1FF
/* 1BA40 8002B240 80630C00 */  sll        $t4, $t4, 14
/* 1BA44 8002B244 FF3F6B31 */  andi       $t3, $t3, 0x3FFF
/* 1BA48 8002B248 25586C01 */  or         $t3, $t3, $t4
/* 1BA4C 8002B24C 25586D01 */  or         $t3, $t3, $t5
/* 1BA50 8002B250 DCAC0008 */  j          .L8002B370
/* 1BA54 8002B254 00002BAC */   sw        $t3, 0x0($at)
.L8002B258:
/* 1BA58 8002B258 2238AC01 */  sub        $a3, $t5, $t4 /* handwritten instruction */
/* 1BA5C 8002B25C 2300E004 */  bltz       $a3, .L8002B2EC
/* 1BA60 8002B260 801F073C */   lui       $a3, (0x1F800000 >> 16)
/* 1BA64 8002B264 22586C01 */  sub        $t3, $t3, $t4 /* handwritten instruction */
/* 1BA68 8002B268 005E0B00 */  sll        $t3, $t3, 24
/* 1BA6C 8002B26C 2268AC01 */  sub        $t5, $t5, $t4 /* handwritten instruction */
/* 1BA70 8002B270 FF00AD31 */  andi       $t5, $t5, 0xFF
/* 1BA74 8002B274 006C0D00 */  sll        $t5, $t5, 16
/* 1BA78 8002B278 FF3F8C31 */  andi       $t4, $t4, 0x3FFF
/* 1BA7C 8002B27C 25608D01 */  or         $t4, $t4, $t5
/* 1BA80 8002B280 25608B01 */  or         $t4, $t4, $t3
/* 1BA84 8002B284 08002CAC */  sw         $t4, 0x8($at)
/* 1BA88 8002B288 0C00EB8C */  lw         $t3, (0x1F80000C & 0xFFFF)($a3)
/* 1BA8C 8002B28C 1000EC8C */  lw         $t4, (0x1F800010 & 0xFFFF)($a3)
/* 1BA90 8002B290 1400ED8C */  lw         $t5, (0x1F800014 & 0xFFFF)($a3)
/* 1BA94 8002B294 22586C01 */  sub        $t3, $t3, $t4 /* handwritten instruction */
/* 1BA98 8002B298 C05D0B00 */  sll        $t3, $t3, 23
/* 1BA9C 8002B29C 2268AC01 */  sub        $t5, $t5, $t4 /* handwritten instruction */
/* 1BAA0 8002B2A0 FF01AD31 */  andi       $t5, $t5, 0x1FF
/* 1BAA4 8002B2A4 806B0D00 */  sll        $t5, $t5, 14
/* 1BAA8 8002B2A8 FF3F8C31 */  andi       $t4, $t4, 0x3FFF
/* 1BAAC 8002B2AC 25608D01 */  or         $t4, $t4, $t5
/* 1BAB0 8002B2B0 25608B01 */  or         $t4, $t4, $t3
/* 1BAB4 8002B2B4 04002CAC */  sw         $t4, 0x4($at)
/* 1BAB8 8002B2B8 0000EB8C */  lw         $t3, (0x1F800000 & 0xFFFF)($a3)
/* 1BABC 8002B2BC 0400EC8C */  lw         $t4, (0x1F800004 & 0xFFFF)($a3)
/* 1BAC0 8002B2C0 0800ED8C */  lw         $t5, (0x1F800008 & 0xFFFF)($a3)
/* 1BAC4 8002B2C4 22586C01 */  sub        $t3, $t3, $t4 /* handwritten instruction */
/* 1BAC8 8002B2C8 C05D0B00 */  sll        $t3, $t3, 23
/* 1BACC 8002B2CC 2268AC01 */  sub        $t5, $t5, $t4 /* handwritten instruction */
/* 1BAD0 8002B2D0 FF01AD31 */  andi       $t5, $t5, 0x1FF
/* 1BAD4 8002B2D4 806B0D00 */  sll        $t5, $t5, 14
/* 1BAD8 8002B2D8 FF3F8C31 */  andi       $t4, $t4, 0x3FFF
/* 1BADC 8002B2DC 25608D01 */  or         $t4, $t4, $t5
/* 1BAE0 8002B2E0 25608B01 */  or         $t4, $t4, $t3
/* 1BAE4 8002B2E4 DCAC0008 */  j          .L8002B370
/* 1BAE8 8002B2E8 00002CAC */   sw        $t4, 0x0($at)
.L8002B2EC:
/* 1BAEC 8002B2EC 22608D01 */  sub        $t4, $t4, $t5 /* handwritten instruction */
/* 1BAF0 8002B2F0 00660C00 */  sll        $t4, $t4, 24
/* 1BAF4 8002B2F4 22586D01 */  sub        $t3, $t3, $t5 /* handwritten instruction */
/* 1BAF8 8002B2F8 FF006B31 */  andi       $t3, $t3, 0xFF
/* 1BAFC 8002B2FC 005C0B00 */  sll        $t3, $t3, 16
/* 1BB00 8002B300 FF3FAD31 */  andi       $t5, $t5, 0x3FFF
/* 1BB04 8002B304 2568AB01 */  or         $t5, $t5, $t3
/* 1BB08 8002B308 2568AC01 */  or         $t5, $t5, $t4
/* 1BB0C 8002B30C 08002DAC */  sw         $t5, 0x8($at)
/* 1BB10 8002B310 1000EC8C */  lw         $t4, (0x1F800010 & 0xFFFF)($a3)
/* 1BB14 8002B314 1400ED8C */  lw         $t5, (0x1F800014 & 0xFFFF)($a3)
/* 1BB18 8002B318 0C00EB8C */  lw         $t3, (0x1F80000C & 0xFFFF)($a3)
/* 1BB1C 8002B31C 22608D01 */  sub        $t4, $t4, $t5 /* handwritten instruction */
/* 1BB20 8002B320 C0650C00 */  sll        $t4, $t4, 23
/* 1BB24 8002B324 22586D01 */  sub        $t3, $t3, $t5 /* handwritten instruction */
/* 1BB28 8002B328 FF016B31 */  andi       $t3, $t3, 0x1FF
/* 1BB2C 8002B32C 805B0B00 */  sll        $t3, $t3, 14
/* 1BB30 8002B330 FF3FAD31 */  andi       $t5, $t5, 0x3FFF
/* 1BB34 8002B334 2568AB01 */  or         $t5, $t5, $t3
/* 1BB38 8002B338 2568AC01 */  or         $t5, $t5, $t4
/* 1BB3C 8002B33C 04002DAC */  sw         $t5, 0x4($at)
/* 1BB40 8002B340 0400EC8C */  lw         $t4, (0x1F800004 & 0xFFFF)($a3)
/* 1BB44 8002B344 0800ED8C */  lw         $t5, (0x1F800008 & 0xFFFF)($a3)
/* 1BB48 8002B348 0000EB8C */  lw         $t3, (0x1F800000 & 0xFFFF)($a3)
/* 1BB4C 8002B34C 22608D01 */  sub        $t4, $t4, $t5 /* handwritten instruction */
/* 1BB50 8002B350 C0650C00 */  sll        $t4, $t4, 23
/* 1BB54 8002B354 22586D01 */  sub        $t3, $t3, $t5 /* handwritten instruction */
/* 1BB58 8002B358 FF016B31 */  andi       $t3, $t3, 0x1FF
/* 1BB5C 8002B35C 805B0B00 */  sll        $t3, $t3, 14
/* 1BB60 8002B360 FF3FAD31 */  andi       $t5, $t5, 0x3FFF
/* 1BB64 8002B364 2568AB01 */  or         $t5, $t5, $t3
/* 1BB68 8002B368 2568AC01 */  or         $t5, $t5, $t4
/* 1BB6C 8002B36C 00002DAC */  sw         $t5, 0x0($at)
.L8002B370:
/* 1BB70 8002B370 0C004220 */  addi       $v0, $v0, 0xC /* handwritten instruction */
/* 1BB74 8002B374 0C006320 */  addi       $v1, $v1, 0xC /* handwritten instruction */
/* 1BB78 8002B378 2AFF4414 */  bne        $v0, $a0, .L8002B024
/* 1BB7C 8002B37C 0C002120 */   addi      $at, $at, 0xC /* handwritten instruction */
/* 1BB80 8002B380 5AAB0008 */  j          .L8002AD68
/* 1BB84 8002B384 00000000 */   nop
.L8002B388:
/* 1BB88 8002B388 0800E003 */  jr         $ra
/* 1BB8C 8002B38C 00000000 */   nop
.size func_8002A6FC, . - func_8002A6FC
