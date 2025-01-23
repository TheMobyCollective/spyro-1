.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */
glabel func_8002B4AC
/* 1BCAC 8002B4AC 0880193C */  lui        $t9, %hi(D_80078560)
/* 1BCB0 8002B4B0 60853927 */  addiu      $t9, $t9, %lo(D_80078560)
/* 1BCB4 8002B4B4 00002F8F */  lw         $t7, 0x0($t9)
/* 1BCB8 8002B4B8 04002E8F */  lw         $t6, 0x4($t9)
/* 1BCBC 8002B4BC 80780F00 */  sll        $t7, $t7, 2
/* 1BCC0 8002B4C0 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002B4C4:
/* 1BCC4 8002B4C4 2900CF11 */  beq        $t6, $t7, .L8002B56C
/* 1BCC8 8002B4C8 0000CD8D */   lw        $t5, 0x0($t6)
/* 1BCCC 8002B4CC 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1BCD0 8002B4D0 0200AB91 */  lbu        $t3, 0x2($t5)
/* 1BCD4 8002B4D4 0800AC21 */  addi       $t4, $t5, 0x8 /* handwritten instruction */
/* 1BCD8 8002B4D8 80580B00 */  sll        $t3, $t3, 2
/* 1BCDC 8002B4DC 20608B01 */  add        $t4, $t4, $t3 /* handwritten instruction */
/* 1BCE0 8002B4E0 03008391 */  lbu        $v1, 0x3($t4)
/* 1BCE4 8002B4E4 0400A48D */  lw         $a0, 0x4($t5)
/* 1BCE8 8002B4E8 0880013C */  lui        $at, %hi(g_Environment)
/* 1BCEC 8002B4EC A8852124 */  addiu      $at, $at, %lo(g_Environment)
/* 1BCF0 8002B4F0 1C00228C */  lw         $v0, 0x1C($at)
/* 1BCF4 8002B4F4 1800218C */  lw         $at, 0x18($at)
/* 1BCF8 8002B4F8 00290300 */  sll        $a1, $v1, 4
/* 1BCFC 8002B4FC 00310400 */  sll        $a2, $a0, 4
/* 1BD00 8002B500 2028A100 */  add        $a1, $a1, $at /* handwritten instruction */
/* 1BD04 8002B504 2030C100 */  add        $a2, $a2, $at /* handwritten instruction */
/* 1BD08 8002B508 A8000120 */  addi       $at, $zero, 0xA8 /* handwritten instruction */
/* 1BD0C 8002B50C 18002300 */  mult       $at, $v1
/* 1BD10 8002B510 0000A78C */  lw         $a3, 0x0($a1)
/* 1BD14 8002B514 0400A88C */  lw         $t0, 0x4($a1)
/* 1BD18 8002B518 0800A98C */  lw         $t1, 0x8($a1)
/* 1BD1C 8002B51C 0C00AA8C */  lw         $t2, 0xC($a1)
/* 1BD20 8002B520 12180000 */  mflo       $v1
/* 1BD24 8002B524 0000C7AC */  sw         $a3, 0x0($a2)
/* 1BD28 8002B528 0400C8AC */  sw         $t0, 0x4($a2)
/* 1BD2C 8002B52C 18002400 */  mult       $at, $a0
/* 1BD30 8002B530 0800C9AC */  sw         $t1, 0x8($a2)
/* 1BD34 8002B534 0C00CAAC */  sw         $t2, 0xC($a2)
/* 1BD38 8002B538 20084300 */  add        $at, $v0, $v1 /* handwritten instruction */
/* 1BD3C 8002B53C 12180000 */  mflo       $v1
/* 1BD40 8002B540 20104300 */  add        $v0, $v0, $v1 /* handwritten instruction */
/* 1BD44 8002B544 A8002320 */  addi       $v1, $at, 0xA8 /* handwritten instruction */
.L8002B548:
/* 1BD48 8002B548 0000248C */  lw         $a0, 0x0($at)
/* 1BD4C 8002B54C 0400258C */  lw         $a1, 0x4($at)
/* 1BD50 8002B550 000044AC */  sw         $a0, 0x0($v0)
/* 1BD54 8002B554 040045AC */  sw         $a1, 0x4($v0)
/* 1BD58 8002B558 08002120 */  addi       $at, $at, 0x8 /* handwritten instruction */
/* 1BD5C 8002B55C FAFF2314 */  bne        $at, $v1, .L8002B548
/* 1BD60 8002B560 08004220 */   addi      $v0, $v0, 0x8 /* handwritten instruction */
/* 1BD64 8002B564 31AD0008 */  j          .L8002B4C4
/* 1BD68 8002B568 00000000 */   nop
.L8002B56C:
/* 1BD6C 8002B56C 08002F8F */  lw         $t7, 0x8($t9)
/* 1BD70 8002B570 0C002E8F */  lw         $t6, 0xC($t9)
/* 1BD74 8002B574 80780F00 */  sll        $t7, $t7, 2
/* 1BD78 8002B578 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002B57C:
/* 1BD7C 8002B57C 4800CF11 */  beq        $t6, $t7, .L8002B6A0
/* 1BD80 8002B580 0000CD8D */   lw        $t5, 0x0($t6)
/* 1BD84 8002B584 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1BD88 8002B588 0400A495 */  lhu        $a0, 0x4($t5)
/* 1BD8C 8002B58C 0880013C */  lui        $at, %hi(g_Environment)
/* 1BD90 8002B590 A8852124 */  addiu      $at, $at, %lo(g_Environment)
/* 1BD94 8002B594 A8000220 */  addi       $v0, $zero, 0xA8 /* handwritten instruction */
/* 1BD98 8002B598 18004400 */  mult       $v0, $a0
/* 1BD9C 8002B59C 1C00228C */  lw         $v0, 0x1C($at)
/* 1BDA0 8002B5A0 1800218C */  lw         $at, 0x18($at)
/* 1BDA4 8002B5A4 0600A395 */  lhu        $v1, 0x6($t5)
/* 1BDA8 8002B5A8 00210400 */  sll        $a0, $a0, 4
/* 1BDAC 8002B5AC 20082400 */  add        $at, $at, $a0 /* handwritten instruction */
/* 1BDB0 8002B5B0 12200000 */  mflo       $a0
/* 1BDB4 8002B5B4 20104400 */  add        $v0, $v0, $a0 /* handwritten instruction */
/* 1BDB8 8002B5B8 82200300 */  srl        $a0, $v1, 2
/* 1BDBC 8002B5BC 010024A0 */  sb         $a0, 0x1($at)
/* 1BDC0 8002B5C0 050024A0 */  sb         $a0, 0x5($at)
/* 1BDC4 8002B5C4 090024A0 */  sb         $a0, 0x9($at)
/* 1BDC8 8002B5C8 0D0024A0 */  sb         $a0, 0xD($at)
/* 1BDCC 8002B5CC 010044A0 */  sb         $a0, 0x1($v0)
/* 1BDD0 8002B5D0 050044A0 */  sb         $a0, 0x5($v0)
/* 1BDD4 8002B5D4 42200300 */  srl        $a0, $v1, 1
/* 1BDD8 8002B5D8 090044A0 */  sb         $a0, 0x9($v0)
/* 1BDDC 8002B5DC 0D0044A0 */  sb         $a0, 0xD($v0)
/* 1BDE0 8002B5E0 110044A0 */  sb         $a0, 0x11($v0)
/* 1BDE4 8002B5E4 150044A0 */  sb         $a0, 0x15($v0)
/* 1BDE8 8002B5E8 20008420 */  addi       $a0, $a0, 0x20 /* handwritten instruction */
/* 1BDEC 8002B5EC 3F008430 */  andi       $a0, $a0, 0x3F
/* 1BDF0 8002B5F0 190044A0 */  sb         $a0, 0x19($v0)
/* 1BDF4 8002B5F4 1D0044A0 */  sb         $a0, 0x1D($v0)
/* 1BDF8 8002B5F8 210044A0 */  sb         $a0, 0x21($v0)
/* 1BDFC 8002B5FC 250044A0 */  sb         $a0, 0x25($v0)
/* 1BE00 8002B600 42200300 */  srl        $a0, $v1, 1
/* 1BE04 8002B604 290044A0 */  sb         $a0, 0x29($v0)
/* 1BE08 8002B608 2D0044A0 */  sb         $a0, 0x2D($v0)
/* 1BE0C 8002B60C 310044A0 */  sb         $a0, 0x31($v0)
/* 1BE10 8002B610 350044A0 */  sb         $a0, 0x35($v0)
/* 1BE14 8002B614 390044A0 */  sb         $a0, 0x39($v0)
/* 1BE18 8002B618 3D0044A0 */  sb         $a0, 0x3D($v0)
/* 1BE1C 8002B61C 410044A0 */  sb         $a0, 0x41($v0)
/* 1BE20 8002B620 450044A0 */  sb         $a0, 0x45($v0)
/* 1BE24 8002B624 10008420 */  addi       $a0, $a0, 0x10 /* handwritten instruction */
/* 1BE28 8002B628 3F008430 */  andi       $a0, $a0, 0x3F
/* 1BE2C 8002B62C 490044A0 */  sb         $a0, 0x49($v0)
/* 1BE30 8002B630 4D0044A0 */  sb         $a0, 0x4D($v0)
/* 1BE34 8002B634 510044A0 */  sb         $a0, 0x51($v0)
/* 1BE38 8002B638 550044A0 */  sb         $a0, 0x55($v0)
/* 1BE3C 8002B63C 590044A0 */  sb         $a0, 0x59($v0)
/* 1BE40 8002B640 5D0044A0 */  sb         $a0, 0x5D($v0)
/* 1BE44 8002B644 610044A0 */  sb         $a0, 0x61($v0)
/* 1BE48 8002B648 650044A0 */  sb         $a0, 0x65($v0)
/* 1BE4C 8002B64C 10008420 */  addi       $a0, $a0, 0x10 /* handwritten instruction */
/* 1BE50 8002B650 3F008430 */  andi       $a0, $a0, 0x3F
/* 1BE54 8002B654 690044A0 */  sb         $a0, 0x69($v0)
/* 1BE58 8002B658 6D0044A0 */  sb         $a0, 0x6D($v0)
/* 1BE5C 8002B65C 710044A0 */  sb         $a0, 0x71($v0)
/* 1BE60 8002B660 750044A0 */  sb         $a0, 0x75($v0)
/* 1BE64 8002B664 790044A0 */  sb         $a0, 0x79($v0)
/* 1BE68 8002B668 7D0044A0 */  sb         $a0, 0x7D($v0)
/* 1BE6C 8002B66C 810044A0 */  sb         $a0, 0x81($v0)
/* 1BE70 8002B670 850044A0 */  sb         $a0, 0x85($v0)
/* 1BE74 8002B674 10008420 */  addi       $a0, $a0, 0x10 /* handwritten instruction */
/* 1BE78 8002B678 3F008430 */  andi       $a0, $a0, 0x3F
/* 1BE7C 8002B67C 890044A0 */  sb         $a0, 0x89($v0)
/* 1BE80 8002B680 8D0044A0 */  sb         $a0, 0x8D($v0)
/* 1BE84 8002B684 910044A0 */  sb         $a0, 0x91($v0)
/* 1BE88 8002B688 950044A0 */  sb         $a0, 0x95($v0)
/* 1BE8C 8002B68C 990044A0 */  sb         $a0, 0x99($v0)
/* 1BE90 8002B690 9D0044A0 */  sb         $a0, 0x9D($v0)
/* 1BE94 8002B694 A10044A0 */  sb         $a0, 0xA1($v0)
/* 1BE98 8002B698 5FAD0008 */  j          .L8002B57C
/* 1BE9C 8002B69C A50044A0 */   sb        $a0, 0xA5($v0)
.L8002B6A0:
/* 1BEA0 8002B6A0 10002F8F */  lw         $t7, 0x10($t9)
/* 1BEA4 8002B6A4 14002E8F */  lw         $t6, 0x14($t9)
/* 1BEA8 8002B6A8 FFFF0D20 */  addi       $t5, $zero, -0x1 /* handwritten instruction */
/* 1BEAC 8002B6AC 80780F00 */  sll        $t7, $t7, 2
/* 1BEB0 8002B6B0 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002B6B4:
/* 1BEB4 8002B6B4 0C00CF11 */  beq        $t6, $t7, .L8002B6E8
/* 1BEB8 8002B6B8 0100AD21 */   addi      $t5, $t5, 0x1 /* handwritten instruction */
/* 1BEBC 8002B6BC 0000CC8D */  lw         $t4, 0x0($t6)
/* 1BEC0 8002B6C0 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1BEC4 8002B6C4 04008195 */  lhu        $at, 0x4($t4)
/* 1BEC8 8002B6C8 0880023C */  lui        $v0, %hi(g_Environment)
/* 1BECC 8002B6CC A8854224 */  addiu      $v0, $v0, %lo(g_Environment)
/* 1BED0 8002B6D0 0000428C */  lw         $v0, 0x0($v0)
/* 1BED4 8002B6D4 80080100 */  sll        $at, $at, 2
/* 1BED8 8002B6D8 20104100 */  add        $v0, $v0, $at /* handwritten instruction */
/* 1BEDC 8002B6DC 0000418C */  lw         $at, 0x0($v0)
/* 1BEE0 8002B6E0 ADAD0008 */  j          .L8002B6B4
/* 1BEE4 8002B6E4 18002DA0 */   sb        $t5, 0x18($at)
.L8002B6E8:
/* 1BEE8 8002B6E8 18002F8F */  lw         $t7, 0x18($t9)
/* 1BEEC 8002B6EC 1C002E8F */  lw         $t6, 0x1C($t9)
/* 1BEF0 8002B6F0 FFFF0D20 */  addi       $t5, $zero, -0x1 /* handwritten instruction */
/* 1BEF4 8002B6F4 80780F00 */  sll        $t7, $t7, 2
/* 1BEF8 8002B6F8 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002B6FC:
/* 1BEFC 8002B6FC 0C00CF11 */  beq        $t6, $t7, .L8002B730
/* 1BF00 8002B700 0100AD21 */   addi      $t5, $t5, 0x1 /* handwritten instruction */
/* 1BF04 8002B704 0000CC8D */  lw         $t4, 0x0($t6)
/* 1BF08 8002B708 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1BF0C 8002B70C 04008195 */  lhu        $at, 0x4($t4)
/* 1BF10 8002B710 0880023C */  lui        $v0, %hi(g_Environment)
/* 1BF14 8002B714 A8854224 */  addiu      $v0, $v0, %lo(g_Environment)
/* 1BF18 8002B718 0000428C */  lw         $v0, 0x0($v0)
/* 1BF1C 8002B71C 80080100 */  sll        $at, $at, 2
/* 1BF20 8002B720 20104100 */  add        $v0, $v0, $at /* handwritten instruction */
/* 1BF24 8002B724 0000418C */  lw         $at, 0x0($v0)
/* 1BF28 8002B728 BFAD0008 */  j          .L8002B6FC
/* 1BF2C 8002B72C 19002DA0 */   sb        $t5, 0x19($at)
.L8002B730:
/* 1BF30 8002B730 20002F8F */  lw         $t7, 0x20($t9)
/* 1BF34 8002B734 24002E8F */  lw         $t6, 0x24($t9)
/* 1BF38 8002B738 FFFF0D20 */  addi       $t5, $zero, -0x1 /* handwritten instruction */
/* 1BF3C 8002B73C 80780F00 */  sll        $t7, $t7, 2
/* 1BF40 8002B740 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002B744:
/* 1BF44 8002B744 0C00CF11 */  beq        $t6, $t7, .L8002B778
/* 1BF48 8002B748 0100AD21 */   addi      $t5, $t5, 0x1 /* handwritten instruction */
/* 1BF4C 8002B74C 0000CC8D */  lw         $t4, 0x0($t6)
/* 1BF50 8002B750 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1BF54 8002B754 04008195 */  lhu        $at, 0x4($t4)
/* 1BF58 8002B758 0880023C */  lui        $v0, %hi(g_Environment)
/* 1BF5C 8002B75C A8854224 */  addiu      $v0, $v0, %lo(g_Environment)
/* 1BF60 8002B760 0000428C */  lw         $v0, 0x0($v0)
/* 1BF64 8002B764 80080100 */  sll        $at, $at, 2
/* 1BF68 8002B768 20104100 */  add        $v0, $v0, $at /* handwritten instruction */
/* 1BF6C 8002B76C 0000418C */  lw         $at, 0x0($v0)
/* 1BF70 8002B770 D1AD0008 */  j          .L8002B744
/* 1BF74 8002B774 1A002DA0 */   sb        $t5, 0x1A($at)
.L8002B778:
/* 1BF78 8002B778 28002F8F */  lw         $t7, 0x28($t9)
/* 1BF7C 8002B77C 2C002E8F */  lw         $t6, 0x2C($t9)
/* 1BF80 8002B780 FFFF0D20 */  addi       $t5, $zero, -0x1 /* handwritten instruction */
/* 1BF84 8002B784 80780F00 */  sll        $t7, $t7, 2
/* 1BF88 8002B788 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002B78C:
/* 1BF8C 8002B78C 0C00CF11 */  beq        $t6, $t7, .L8002B7C0
/* 1BF90 8002B790 0100AD21 */   addi      $t5, $t5, 0x1 /* handwritten instruction */
/* 1BF94 8002B794 0000CC8D */  lw         $t4, 0x0($t6)
/* 1BF98 8002B798 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1BF9C 8002B79C 04008195 */  lhu        $at, 0x4($t4)
/* 1BFA0 8002B7A0 0880023C */  lui        $v0, %hi(g_Environment)
/* 1BFA4 8002B7A4 A8854224 */  addiu      $v0, $v0, %lo(g_Environment)
/* 1BFA8 8002B7A8 0000428C */  lw         $v0, 0x0($v0)
/* 1BFAC 8002B7AC 80080100 */  sll        $at, $at, 2
/* 1BFB0 8002B7B0 20104100 */  add        $v0, $v0, $at /* handwritten instruction */
/* 1BFB4 8002B7B4 0000418C */  lw         $at, 0x0($v0)
/* 1BFB8 8002B7B8 E3AD0008 */  j          .L8002B78C
/* 1BFBC 8002B7BC 1B002DA0 */   sb        $t5, 0x1B($at)
.L8002B7C0:
/* 1BFC0 8002B7C0 40002F8F */  lw         $t7, 0x40($t9)
/* 1BFC4 8002B7C4 44002E8F */  lw         $t6, 0x44($t9)
/* 1BFC8 8002B7C8 80780F00 */  sll        $t7, $t7, 2
/* 1BFCC 8002B7CC 2078EE01 */  add        $t7, $t7, $t6 /* handwritten instruction */
.L8002B7D0:
/* 1BFD0 8002B7D0 7C00CF11 */  beq        $t6, $t7, .L8002B9C4
/* 1BFD4 8002B7D4 0000CD8D */   lw        $t5, 0x0($t6)
/* 1BFD8 8002B7D8 0400CE21 */  addi       $t6, $t6, 0x4 /* handwritten instruction */
/* 1BFDC 8002B7DC 0200AB91 */  lbu        $t3, 0x2($t5)
/* 1BFE0 8002B7E0 0C00AC21 */  addi       $t4, $t5, 0xC /* handwritten instruction */
/* 1BFE4 8002B7E4 C0580B00 */  sll        $t3, $t3, 3
/* 1BFE8 8002B7E8 20608B01 */  add        $t4, $t4, $t3 /* handwritten instruction */
/* 1BFEC 8002B7EC 04008A8D */  lw         $t2, 0x4($t4)
/* 1BFF0 8002B7F0 0400A18D */  lw         $at, 0x4($t5)
/* 1BFF4 8002B7F4 025A0A00 */  srl        $t3, $t2, 8
/* 1BFF8 8002B7F8 FF006B31 */  andi       $t3, $t3, 0xFF
/* 1BFFC 8002B7FC 0800A58D */  lw         $a1, 0x8($t5)
/* 1C000 8002B800 FFFF2230 */  andi       $v0, $at, 0xFFFF
/* 1C004 8002B804 020C0100 */  srl        $at, $at, 16
/* 1C008 8002B808 80180200 */  sll        $v1, $v0, 2
/* 1C00C 8002B80C C0100200 */  sll        $v0, $v0, 3
/* 1C010 8002B810 20104300 */  add        $v0, $v0, $v1 /* handwritten instruction */
/* 1C014 8002B814 0880063C */  lui        $a2, %hi(g_Environment)
/* 1C018 8002B818 A885C624 */  addiu      $a2, $a2, %lo(g_Environment)
/* 1C01C 8002B81C 2028AD00 */  add        $a1, $a1, $t5 /* handwritten instruction */
/* 1C020 8002B820 2C00C68C */  lw         $a2, 0x2C($a2)
/* 1C024 8002B824 18004B00 */  mult       $v0, $t3
/* 1C028 8002B828 80180100 */  sll        $v1, $at, 2
/* 1C02C 8002B82C C0080100 */  sll        $at, $at, 3
/* 1C030 8002B830 20082300 */  add        $at, $at, $v1 /* handwritten instruction */
/* 1C034 8002B834 12580000 */  mflo       $t3
/* 1C038 8002B838 1000C68C */  lw         $a2, 0x10($a2)
/* 1C03C 8002B83C 2020AB00 */  add        $a0, $a1, $t3 /* handwritten instruction */
/* 1C040 8002B840 20208200 */  add        $a0, $a0, $v0 /* handwritten instruction */
/* 1C044 8002B844 2010AB00 */  add        $v0, $a1, $t3 /* handwritten instruction */
/* 1C048 8002B848 20082600 */  add        $at, $at, $a2 /* handwritten instruction */
.L8002B84C:
/* 1C04C 8002B84C 08004B8C */  lw         $t3, 0x8($v0)
/* 1C050 8002B850 0400488C */  lw         $t0, 0x4($v0)
/* 1C054 8002B854 0000458C */  lw         $a1, 0x0($v0)
/* 1C058 8002B858 40620B00 */  sll        $t4, $t3, 9
/* 1C05C 8002B85C C3650C00 */  sra        $t4, $t4, 23
/* 1C060 8002B860 0B008005 */  bltz       $t4, .L8002B890
/* 1C064 8002B864 C36D0B00 */   sra       $t5, $t3, 23
/* 1C068 8002B868 0900A005 */  bltz       $t5, .L8002B890
/* 1C06C 8002B86C FF3F6B31 */   andi      $t3, $t3, 0x3FFF
/* 1C070 8002B870 000025AC */  sw         $a1, 0x0($at)
/* 1C074 8002B874 040028AC */  sw         $t0, 0x4($at)
/* 1C078 8002B878 00640C00 */  sll        $t4, $t4, 16
/* 1C07C 8002B87C 006E0D00 */  sll        $t5, $t5, 24
/* 1C080 8002B880 25586C01 */  or         $t3, $t3, $t4
/* 1C084 8002B884 25586D01 */  or         $t3, $t3, $t5
/* 1C088 8002B888 6CAE0008 */  j          .L8002B9B0
/* 1C08C 8002B88C 08002BAC */   sw        $t3, 0x8($at)
.L8002B890:
/* 1C090 8002B890 2218AC01 */  sub        $v1, $t5, $t4 /* handwritten instruction */
/* 1C094 8002B894 FF3F6B31 */  andi       $t3, $t3, 0x3FFF
/* 1C098 8002B898 2068AB01 */  add        $t5, $t5, $t3 /* handwritten instruction */
/* 1C09C 8002B89C 20608B01 */  add        $t4, $t4, $t3 /* handwritten instruction */
/* 1C0A0 8002B8A0 C33D0500 */  sra        $a3, $a1, 23
/* 1C0A4 8002B8A4 40320500 */  sll        $a2, $a1, 9
/* 1C0A8 8002B8A8 C3350600 */  sra        $a2, $a2, 23
/* 1C0AC 8002B8AC FF3FA530 */  andi       $a1, $a1, 0x3FFF
/* 1C0B0 8002B8B0 2038E500 */  add        $a3, $a3, $a1 /* handwritten instruction */
/* 1C0B4 8002B8B4 2030C500 */  add        $a2, $a2, $a1 /* handwritten instruction */
/* 1C0B8 8002B8B8 C3550800 */  sra        $t2, $t0, 23
/* 1C0BC 8002B8BC 404A0800 */  sll        $t1, $t0, 9
/* 1C0C0 8002B8C0 C34D0900 */  sra        $t1, $t1, 23
/* 1C0C4 8002B8C4 FF3F0831 */  andi       $t0, $t0, 0x3FFF
/* 1C0C8 8002B8C8 20504801 */  add        $t2, $t2, $t0 /* handwritten instruction */
/* 1C0CC 8002B8CC 1D006004 */  bltz       $v1, .L8002B944
/* 1C0D0 8002B8D0 20482801 */   add       $t1, $t1, $t0 /* handwritten instruction */
/* 1C0D4 8002B8D4 2228A600 */  sub        $a1, $a1, $a2 /* handwritten instruction */
/* 1C0D8 8002B8D8 C02D0500 */  sll        $a1, $a1, 23
/* 1C0DC 8002B8DC 2238E600 */  sub        $a3, $a3, $a2 /* handwritten instruction */
/* 1C0E0 8002B8E0 FF01E730 */  andi       $a3, $a3, 0x1FF
/* 1C0E4 8002B8E4 803B0700 */  sll        $a3, $a3, 14
/* 1C0E8 8002B8E8 FF3FC630 */  andi       $a2, $a2, 0x3FFF
/* 1C0EC 8002B8EC 2530C500 */  or         $a2, $a2, $a1
/* 1C0F0 8002B8F0 2530C700 */  or         $a2, $a2, $a3
/* 1C0F4 8002B8F4 000026AC */  sw         $a2, 0x0($at)
/* 1C0F8 8002B8F8 22400901 */  sub        $t0, $t0, $t1 /* handwritten instruction */
/* 1C0FC 8002B8FC C0450800 */  sll        $t0, $t0, 23
/* 1C100 8002B900 22504901 */  sub        $t2, $t2, $t1 /* handwritten instruction */
/* 1C104 8002B904 FF014A31 */  andi       $t2, $t2, 0x1FF
/* 1C108 8002B908 80530A00 */  sll        $t2, $t2, 14
/* 1C10C 8002B90C FF3F2931 */  andi       $t1, $t1, 0x3FFF
/* 1C110 8002B910 25482801 */  or         $t1, $t1, $t0
/* 1C114 8002B914 25482A01 */  or         $t1, $t1, $t2
/* 1C118 8002B918 040029AC */  sw         $t1, 0x4($at)
/* 1C11C 8002B91C 22586C01 */  sub        $t3, $t3, $t4 /* handwritten instruction */
/* 1C120 8002B920 005E0B00 */  sll        $t3, $t3, 24
/* 1C124 8002B924 2268AC01 */  sub        $t5, $t5, $t4 /* handwritten instruction */
/* 1C128 8002B928 FF01AD31 */  andi       $t5, $t5, 0x1FF
/* 1C12C 8002B92C 006C0D00 */  sll        $t5, $t5, 16
/* 1C130 8002B930 FF3F8C31 */  andi       $t4, $t4, 0x3FFF
/* 1C134 8002B934 25608B01 */  or         $t4, $t4, $t3
/* 1C138 8002B938 25608D01 */  or         $t4, $t4, $t5
/* 1C13C 8002B93C 6CAE0008 */  j          .L8002B9B0
/* 1C140 8002B940 08002CAC */   sw        $t4, 0x8($at)
.L8002B944:
/* 1C144 8002B944 2230C700 */  sub        $a2, $a2, $a3 /* handwritten instruction */
/* 1C148 8002B948 C0350600 */  sll        $a2, $a2, 23
/* 1C14C 8002B94C 2228A700 */  sub        $a1, $a1, $a3 /* handwritten instruction */
/* 1C150 8002B950 FF01A530 */  andi       $a1, $a1, 0x1FF
/* 1C154 8002B954 802B0500 */  sll        $a1, $a1, 14
/* 1C158 8002B958 FF3FE730 */  andi       $a3, $a3, 0x3FFF
/* 1C15C 8002B95C 2538E600 */  or         $a3, $a3, $a2
/* 1C160 8002B960 2538E500 */  or         $a3, $a3, $a1
/* 1C164 8002B964 000027AC */  sw         $a3, 0x0($at)
/* 1C168 8002B968 22482A01 */  sub        $t1, $t1, $t2 /* handwritten instruction */
/* 1C16C 8002B96C C04D0900 */  sll        $t1, $t1, 23
/* 1C170 8002B970 22400A01 */  sub        $t0, $t0, $t2 /* handwritten instruction */
/* 1C174 8002B974 FF010831 */  andi       $t0, $t0, 0x1FF
/* 1C178 8002B978 80430800 */  sll        $t0, $t0, 14
/* 1C17C 8002B97C FF3F4A31 */  andi       $t2, $t2, 0x3FFF
/* 1C180 8002B980 25504901 */  or         $t2, $t2, $t1
/* 1C184 8002B984 25504801 */  or         $t2, $t2, $t0
/* 1C188 8002B988 04002AAC */  sw         $t2, 0x4($at)
/* 1C18C 8002B98C 22608D01 */  sub        $t4, $t4, $t5 /* handwritten instruction */
/* 1C190 8002B990 00660C00 */  sll        $t4, $t4, 24
/* 1C194 8002B994 22586D01 */  sub        $t3, $t3, $t5 /* handwritten instruction */
/* 1C198 8002B998 FF016B31 */  andi       $t3, $t3, 0x1FF
/* 1C19C 8002B99C 005C0B00 */  sll        $t3, $t3, 16
/* 1C1A0 8002B9A0 FF3FAD31 */  andi       $t5, $t5, 0x3FFF
/* 1C1A4 8002B9A4 2568AC01 */  or         $t5, $t5, $t4
/* 1C1A8 8002B9A8 2568AB01 */  or         $t5, $t5, $t3
/* 1C1AC 8002B9AC 08002DAC */  sw         $t5, 0x8($at)
.L8002B9B0:
/* 1C1B0 8002B9B0 0C004220 */  addi       $v0, $v0, 0xC /* handwritten instruction */
/* 1C1B4 8002B9B4 A5FF4414 */  bne        $v0, $a0, .L8002B84C
/* 1C1B8 8002B9B8 0C002120 */   addi      $at, $at, 0xC /* handwritten instruction */
/* 1C1BC 8002B9BC F4AD0008 */  j          .L8002B7D0
/* 1C1C0 8002B9C0 00000000 */   nop
.L8002B9C4:
/* 1C1C4 8002B9C4 0800E003 */  jr         $ra
/* 1C1C8 8002B9C8 00000000 */   nop
.size func_8002B4AC, . - func_8002B4AC
