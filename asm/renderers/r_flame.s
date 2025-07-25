.include "macro.inc"
.include "c2regs.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Generated by spimdisasm 1.27.0 */

/* Handwritten function */
glabel func_80058D64
/* 49564 80058D64 0780013C */  lui        $at, %hi(D_80077DD8)
/* 49568 80058D68 D87D2124 */  addiu      $at, $at, %lo(D_80077DD8)
/* 4956C 80058D6C 000030AC */  sw         $s0, 0x0($at)
/* 49570 80058D70 040031AC */  sw         $s1, 0x4($at)
/* 49574 80058D74 080032AC */  sw         $s2, 0x8($at)
/* 49578 80058D78 0C0033AC */  sw         $s3, 0xC($at)
/* 4957C 80058D7C 100034AC */  sw         $s4, 0x10($at)
/* 49580 80058D80 140035AC */  sw         $s5, 0x14($at)
/* 49584 80058D84 180036AC */  sw         $s6, 0x18($at)
/* 49588 80058D88 1C0037AC */  sw         $s7, 0x1C($at)
/* 4958C 80058D8C 20003CAC */  sw         $gp, 0x20($at)
/* 49590 80058D90 24003DAC */  sw         $sp, 0x24($at)
/* 49594 80058D94 28003EAC */  sw         $fp, 0x28($at)
/* 49598 80058D98 2C003FAC */  sw         $ra, 0x2C($at)
/* 4959C 80058D9C 07801D3C */  lui        $sp, %hi(g_WorldOT)
/* 495A0 80058DA0 2058BD27 */  addiu      $sp, $sp, %lo(g_WorldOT)
/* 495A4 80058DA4 0000BD8F */  lw         $sp, 0x0($sp)
/* 495A8 80058DA8 07801E3C */  lui        $fp, %hi(D_800757B0)
/* 495AC 80058DAC B057DE27 */  addiu      $fp, $fp, %lo(D_800757B0)
/* 495B0 80058DB0 0000DE8F */  lw         $fp, 0x0($fp)
/* 495B4 80058DB4 08801F3C */  lui        $ra, %hi(D_800786C8)
/* 495B8 80058DB8 C886FF27 */  addiu      $ra, $ra, %lo(D_800786C8)
/* 495BC 80058DBC 07800A3C */  lui        $t2, %hi(g_Camera)
/* 495C0 80058DC0 D06D4A25 */  addiu      $t2, $t2, %lo(g_Camera)
/* 495C4 80058DC4 0000E18F */  lw         $at, 0x0($ra)
/* 495C8 80058DC8 0400E28F */  lw         $v0, 0x4($ra)
/* 495CC 80058DCC 0800E38F */  lw         $v1, 0x8($ra)
/* 495D0 80058DD0 2800448D */  lw         $a0, 0x28($t2)
/* 495D4 80058DD4 2C00458D */  lw         $a1, 0x2C($t2)
/* 495D8 80058DD8 3000468D */  lw         $a2, 0x30($t2)
/* 495DC 80058DDC 22082400 */  sub        $at, $at, $a0 /* handwritten instruction */
/* 495E0 80058DE0 2210A200 */  sub        $v0, $a1, $v0 /* handwritten instruction */
/* 495E4 80058DE4 2218C300 */  sub        $v1, $a2, $v1 /* handwritten instruction */
/* 495E8 80058DE8 0000448D */  lw         $a0, 0x0($t2)
/* 495EC 80058DEC 0400458D */  lw         $a1, 0x4($t2)
/* 495F0 80058DF0 0800468D */  lw         $a2, 0x8($t2)
/* 495F4 80058DF4 0C00478D */  lw         $a3, 0xC($t2)
/* 495F8 80058DF8 1000488D */  lw         $t0, 0x10($t2)
/* 495FC 80058DFC 0000C448 */  ctc2       $a0, C2_R11R12 /* handwritten instruction */
/* 49600 80058E00 0008C548 */  ctc2       $a1, C2_R13R21 /* handwritten instruction */
/* 49604 80058E04 0010C648 */  ctc2       $a2, C2_R22R23 /* handwritten instruction */
/* 49608 80058E08 0018C748 */  ctc2       $a3, C2_R31R32 /* handwritten instruction */
/* 4960C 80058E0C 0020C848 */  ctc2       $t0, C2_R33 /* handwritten instruction */
/* 49610 80058E10 0028C048 */  ctc2       $zero, C2_TRX /* handwritten instruction */
/* 49614 80058E14 0030C048 */  ctc2       $zero, C2_TRY /* handwritten instruction */
/* 49618 80058E18 0038C048 */  ctc2       $zero, C2_TRZ /* handwritten instruction */
/* 4961C 80058E1C 00588148 */  mtc2       $at, C2_IR3 /* handwritten instruction */
/* 49620 80058E20 00488248 */  mtc2       $v0, C2_IR1 /* handwritten instruction */
/* 49624 80058E24 00508348 */  mtc2       $v1, C2_IR2 /* handwritten instruction */
/* 49628 80058E28 00000000 */  nop
/* 4962C 80058E2C 00000000 */  nop
/* 49630 80058E30 12E0494A */  MVMVA      1, 0, 3, 3, 0
/* 49634 80058E34 00D80348 */  mfc2       $v1, C2_MAC3 /* handwritten instruction */
/* 49638 80058E38 00D00248 */  mfc2       $v0, C2_MAC2 /* handwritten instruction */
/* 4963C 80058E3C 00C80148 */  mfc2       $at, C2_MAC1 /* handwritten instruction */
/* 49640 80058E40 0038C348 */  ctc2       $v1, C2_TRZ /* handwritten instruction */
/* 49644 80058E44 0030C248 */  ctc2       $v0, C2_TRY /* handwritten instruction */
/* 49648 80058E48 0028C148 */  ctc2       $at, C2_TRX /* handwritten instruction */
/* 4964C 80058E4C B800E78F */  lw         $a3, 0xB8($ra)
/* 49650 80058E50 BC00E88F */  lw         $t0, 0xBC($ra)
/* 49654 80058E54 C000E98F */  lw         $t1, 0xC0($ra)
/* 49658 80058E58 C400EA8F */  lw         $t2, 0xC4($ra)
/* 4965C 80058E5C C800EB8F */  lw         $t3, 0xC8($ra)
/* 49660 80058E60 0000C748 */  ctc2       $a3, C2_R11R12 /* handwritten instruction */
/* 49664 80058E64 0008C848 */  ctc2       $t0, C2_R13R21 /* handwritten instruction */
/* 49668 80058E68 0010C948 */  ctc2       $t1, C2_R22R23 /* handwritten instruction */
/* 4966C 80058E6C 0018CA48 */  ctc2       $t2, C2_R31R32 /* handwritten instruction */
/* 49670 80058E70 0020CB48 */  ctc2       $t3, C2_R33 /* handwritten instruction */
/* 49674 80058E74 9C00F28F */  lw         $s2, 0x9C($ra)
/* 49678 80058E78 0780133C */  lui        $s3, %hi(D_8006CBF8)
/* 4967C 80058E7C F8CB7326 */  addiu      $s3, $s3, %lo(D_8006CBF8)
/* 49680 80058E80 08001920 */  addi       $t9, $zero, 0x8 /* handwritten instruction */
.L80058E84:
/* 49684 80058E84 68012013 */  beqz       $t9, .L80059428
/* 49688 80058E88 FFFF3923 */   addi      $t9, $t9, -0x1 /* handwritten instruction */
/* 4968C 80058E8C 20083F03 */  add        $at, $t9, $ra /* handwritten instruction */
/* 49690 80058E90 20002480 */  lb         $a0, 0x20($at)
/* 49694 80058E94 28003580 */  lb         $s5, 0x28($at)
/* 49698 80058E98 0780013C */  lui        $at, %hi(D_8006D94C)
/* 4969C 80058E9C 4CD92124 */  addiu      $at, $at, %lo(D_8006D94C)
/* 496A0 80058EA0 F8FF8018 */  blez       $a0, .L80058E84
/* 496A4 80058EA4 FFFF8420 */   addi      $a0, $a0, -0x1 /* handwritten instruction */
/* 496A8 80058EA8 80200400 */  sll        $a0, $a0, 2
/* 496AC 80058EAC 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 496B0 80058EB0 FCFF2123 */  addi       $at, $t9, -0x4 /* handwritten instruction */
/* 496B4 80058EB4 04002104 */  bgez       $at, .L80058EC8
/* 496B8 80058EB8 C0000120 */   addi      $at, $zero, 0xC0 /* handwritten instruction */
/* 496BC 80058EBC 00002223 */  addi       $v0, $t9, 0x0 /* handwritten instruction */
/* 496C0 80058EC0 B6630108 */  j          .L80058ED8
/* 496C4 80058EC4 00000320 */   addi      $v1, $zero, 0x0 /* handwritten instruction */
.L80058EC8:
/* 496C8 80058EC8 00010120 */  addi       $at, $zero, 0x100 /* handwritten instruction */
/* 496CC 80058ECC FCFF2223 */  addi       $v0, $t9, -0x4 /* handwritten instruction */
/* 496D0 80058ED0 00030320 */  addi       $v1, $zero, 0x300 /* handwritten instruction */
/* 496D4 80058ED4 80008420 */  addi       $a0, $a0, 0x80 /* handwritten instruction */
.L80058ED8:
/* 496D8 80058ED8 18002200 */  mult       $at, $v0
/* 496DC 80058EDC 0000988C */  lw         $t8, 0x0($a0)
/* 496E0 80058EE0 12100000 */  mflo       $v0
/* 496E4 80058EE4 20104300 */  add        $v0, $v0, $v1 /* handwritten instruction */
/* 496E8 80058EE8 0780163C */  lui        $s6, %hi(D_8006DAA8)
/* 496EC 80058EEC A8DAD626 */  addiu      $s6, $s6, %lo(D_8006DAA8)
/* 496F0 80058EF0 20B0C202 */  add        $s6, $s6, $v0 /* handwritten instruction */
/* 496F4 80058EF4 0000D722 */  addi       $s7, $s6, 0x0 /* handwritten instruction */
/* 496F8 80058EF8 2018C102 */  add        $v1, $s6, $at /* handwritten instruction */
/* 496FC 80058EFC 00001C20 */  addi       $gp, $zero, 0x0 /* handwritten instruction */
/* 49700 80058F00 020E1800 */  srl        $at, $t8, 24
/* 49704 80058F04 C0100100 */  sll        $v0, $at, 3
/* 49708 80058F08 F8074230 */  andi       $v0, $v0, 0x7F8
/* 4970C 80058F0C 20B8E202 */  add        $s7, $s7, $v0 /* handwritten instruction */
/* 49710 80058F10 C0A81500 */  sll        $s5, $s5, 3
/* 49714 80058F14 20A8B602 */  add        $s5, $s5, $s6 /* handwritten instruction */
/* 49718 80058F18 2208F502 */  sub        $at, $s7, $s5 /* handwritten instruction */
/* 4971C 80058F1C BB00201C */  bgtz       $at, .L8005920C
/* 49720 80058F20 22187700 */   sub       $v1, $v1, $s7 /* handwritten instruction */
/* 49724 80058F24 B9006018 */  blez       $v1, .L8005920C
/* 49728 80058F28 00000000 */   nop
/* 4972C 80058F2C 01001C20 */  addi       $gp, $zero, 0x1 /* handwritten instruction */
/* 49730 80058F30 0000E28E */  lw         $v0, 0x0($s7)
/* 49734 80058F34 0400E38E */  lw         $v1, 0x4($s7)
/* 49738 80058F38 000C0200 */  sll        $at, $v0, 16
/* 4973C 80058F3C 030C0100 */  sra        $at, $at, 16
/* 49740 80058F40 03140200 */  sra        $v0, $v0, 16
/* 49744 80058F44 22100200 */  neg        $v0, $v0 /* handwritten instruction */
/* 49748 80058F48 FFFF4230 */  andi       $v0, $v0, 0xFFFF
/* 4974C 80058F4C 001C0300 */  sll        $v1, $v1, 16
/* 49750 80058F50 22180300 */  neg        $v1, $v1 /* handwritten instruction */
/* 49754 80058F54 25104300 */  or         $v0, $v0, $v1
/* 49758 80058F58 00088148 */  mtc2       $at, C2_VZ0 /* handwritten instruction */
/* 4975C 80058F5C 00008248 */  mtc2       $v0, C2_VXY0 /* handwritten instruction */
/* 49760 80058F60 F0FFE28E */  lw         $v0, -0x10($s7)
/* 49764 80058F64 F4FFE38E */  lw         $v1, -0xC($s7)
/* 49768 80058F68 0100184A */  RTPS
/* 4976C 80058F6C 000C0200 */  sll        $at, $v0, 16
/* 49770 80058F70 030C0100 */  sra        $at, $at, 16
/* 49774 80058F74 03140200 */  sra        $v0, $v0, 16
/* 49778 80058F78 02004012 */  beqz       $s2, .L80058F84
/* 4977C 80058F7C 2C000420 */   addi      $a0, $zero, 0x2C /* handwritten instruction */
/* 49780 80058F80 40000420 */  addi       $a0, $zero, 0x40 /* handwritten instruction */
.L80058F84:
/* 49784 80058F84 C22B0300 */  srl        $a1, $v1, 15
/* 49788 80058F88 FE01A530 */  andi       $a1, $a1, 0x1FE
/* 4978C 80058F8C 001C0300 */  sll        $v1, $v1, 16
/* 49790 80058F90 031C0300 */  sra        $v1, $v1, 16
/* 49794 80058F94 20486502 */  add        $t1, $s3, $a1 /* handwritten instruction */
/* 49798 80058F98 80002821 */  addi       $t0, $t1, 0x80 /* handwritten instruction */
/* 4979C 80058F9C 00000885 */  lh         $t0, 0x0($t0)
/* 497A0 80058FA0 00002985 */  lh         $t1, 0x0($t1)
/* 497A4 80058FA4 00981148 */  mfc2       $s1, C2_SZ3 /* handwritten instruction */
/* 497A8 80058FA8 00700D48 */  mfc2       $t5, C2_SXY2 /* handwritten instruction */
/* 497AC 80058FAC 18008800 */  mult       $a0, $t0
/* 497B0 80058FB0 12400000 */  mflo       $t0
/* 497B4 80058FB4 C3420800 */  sra        $t0, $t0, 11
/* 497B8 80058FB8 00000000 */  nop
/* 497BC 80058FBC 18008900 */  mult       $a0, $t1
/* 497C0 80058FC0 12480000 */  mflo       $t1
/* 497C4 80058FC4 C34A0900 */  sra        $t1, $t1, 11
/* 497C8 80058FC8 22200201 */  sub        $a0, $t0, $v0 /* handwritten instruction */
/* 497CC 80058FCC 22282301 */  sub        $a1, $t1, $v1 /* handwritten instruction */
/* 497D0 80058FD0 40300800 */  sll        $a2, $t0, 1
/* 497D4 80058FD4 40380900 */  sll        $a3, $t1, 1
/* 497D8 80058FD8 22308600 */  sub        $a2, $a0, $a2 /* handwritten instruction */
/* 497DC 80058FDC 2238A700 */  sub        $a3, $a1, $a3 /* handwritten instruction */
/* 497E0 80058FE0 03004012 */  beqz       $s2, .L80058FF0
/* 497E4 80058FE4 22400800 */   neg       $t0, $t0 /* handwritten instruction */
/* 497E8 80058FE8 43400800 */  sra        $t0, $t0, 1
/* 497EC 80058FEC 43480900 */  sra        $t1, $t1, 1
.L80058FF0:
/* 497F0 80058FF0 22102201 */  sub        $v0, $t1, $v0 /* handwritten instruction */
/* 497F4 80058FF4 22180301 */  sub        $v1, $t0, $v1 /* handwritten instruction */
/* 497F8 80058FF8 00088148 */  mtc2       $at, C2_VZ0 /* handwritten instruction */
/* 497FC 80058FFC 00188148 */  mtc2       $at, C2_VZ1 /* handwritten instruction */
/* 49800 80059000 00288148 */  mtc2       $at, C2_VZ2 /* handwritten instruction */
/* 49804 80059004 FFFF4230 */  andi       $v0, $v0, 0xFFFF
/* 49808 80059008 FFFF8430 */  andi       $a0, $a0, 0xFFFF
/* 4980C 8005900C FFFFC630 */  andi       $a2, $a2, 0xFFFF
/* 49810 80059010 001C0300 */  sll        $v1, $v1, 16
/* 49814 80059014 002C0500 */  sll        $a1, $a1, 16
/* 49818 80059018 003C0700 */  sll        $a3, $a3, 16
/* 4981C 8005901C 25104300 */  or         $v0, $v0, $v1
/* 49820 80059020 25208500 */  or         $a0, $a0, $a1
/* 49824 80059024 2530C700 */  or         $a2, $a2, $a3
/* 49828 80059028 00008248 */  mtc2       $v0, C2_VXY0 /* handwritten instruction */
/* 4982C 8005902C 00108448 */  mtc2       $a0, C2_VXY1 /* handwritten instruction */
/* 49830 80059030 00208648 */  mtc2       $a2, C2_VXY2 /* handwritten instruction */
/* 49834 80059034 0780043C */  lui        $a0, %hi(D_8006E1A8)
/* 49838 80059038 A8E18424 */  addiu      $a0, $a0, %lo(D_8006E1A8)
/* 4983C 8005903C 3000284A */  RTPT
/* 49840 80059040 02004012 */  beqz       $s2, .L8005904C
/* 49844 80059044 00008420 */   addi      $a0, $a0, 0x0 /* handwritten instruction */
/* 49848 80059048 10008420 */  addi       $a0, $a0, 0x10 /* handwritten instruction */
.L8005904C:
/* 4984C 8005904C 0000818C */  lw         $at, 0x0($a0)
/* 49850 80059050 0400828C */  lw         $v0, 0x4($a0)
/* 49854 80059054 0800838C */  lw         $v1, 0x8($a0)
/* 49858 80059058 0C00848C */  lw         $a0, 0xC($a0)
/* 4985C 8005905C C2891100 */  srl        $s1, $s1, 7
/* 49860 80059060 FEFF3122 */  addi       $s1, $s1, -0x2 /* handwritten instruction */
/* 49864 80059064 87FF2006 */  bltz       $s1, .L80058E84
/* 49868 80059068 C0881100 */   sll       $s1, $s1, 3
/* 4986C 8005906C 20883D02 */  add        $s1, $s1, $sp /* handwritten instruction */
/* 49870 80059070 00600E48 */  mfc2       $t6, C2_SXY0 /* handwritten instruction */
/* 49874 80059074 00680F48 */  mfc2       $t7, C2_SXY1 /* handwritten instruction */
/* 49878 80059078 00701048 */  mfc2       $s0, C2_SXY2 /* handwritten instruction */
/* 4987C 8005907C 00608D48 */  mtc2       $t5, C2_SXY0 /* handwritten instruction */
/* 49880 80059080 00688F48 */  mtc2       $t7, C2_SXY1 /* handwritten instruction */
/* 49884 80059084 00708E48 */  mtc2       $t6, C2_SXY2 /* handwritten instruction */
/* 49888 80059088 0800CDAF */  sw         $t5, 0x8($fp)
/* 4988C 8005908C 1000CFAF */  sw         $t7, 0x10($fp)
/* 49890 80059090 0600404B */  NCLIP
/* 49894 80059094 1800CEAF */  sw         $t6, 0x18($fp)
/* 49898 80059098 0400C1AF */  sw         $at, 0x4($fp)
/* 4989C 8005909C 0C00C3AF */  sw         $v1, 0xC($fp)
/* 498A0 800590A0 1400C2AF */  sw         $v0, 0x14($fp)
/* 498A4 800590A4 00C00548 */  mfc2       $a1, C2_MAC0 /* handwritten instruction */
/* 498A8 800590A8 0006063C */  lui        $a2, (0x6000000 >> 16)
/* 498AC 800590AC 0C00A018 */  blez       $a1, .L800590E0
/* 498B0 800590B0 0000C6AF */   sw        $a2, 0x0($fp)
/* 498B4 800590B4 0000258E */  lw         $a1, 0x0($s1)
/* 498B8 800590B8 00003EAE */  sw         $fp, 0x0($s1)
/* 498BC 800590BC 0500A010 */  beqz       $a1, .L800590D4
/* 498C0 800590C0 02341E00 */   srl       $a2, $fp, 16
/* 498C4 800590C4 0000BEA4 */  sh         $fp, 0x0($a1)
/* 498C8 800590C8 0200A6A0 */  sb         $a2, 0x2($a1)
/* 498CC 800590CC 38640108 */  j          .L800590E0
/* 498D0 800590D0 1C00DE23 */   addi      $fp, $fp, 0x1C /* handwritten instruction */
.L800590D4:
/* 498D4 800590D4 04003EAE */  sw         $fp, 0x4($s1)
/* 498D8 800590D8 38640108 */  j          .L800590E0
/* 498DC 800590DC 1C00DE23 */   addi      $fp, $fp, 0x1C /* handwritten instruction */
.L800590E0:
/* 498E0 800590E0 00608D48 */  mtc2       $t5, C2_SXY0 /* handwritten instruction */
/* 498E4 800590E4 00688E48 */  mtc2       $t6, C2_SXY1 /* handwritten instruction */
/* 498E8 800590E8 00709048 */  mtc2       $s0, C2_SXY2 /* handwritten instruction */
/* 498EC 800590EC 0800CDAF */  sw         $t5, 0x8($fp)
/* 498F0 800590F0 1000CEAF */  sw         $t6, 0x10($fp)
/* 498F4 800590F4 0600404B */  NCLIP
/* 498F8 800590F8 1800D0AF */  sw         $s0, 0x18($fp)
/* 498FC 800590FC 0400C1AF */  sw         $at, 0x4($fp)
/* 49900 80059100 0C00C2AF */  sw         $v0, 0xC($fp)
/* 49904 80059104 1400C4AF */  sw         $a0, 0x14($fp)
/* 49908 80059108 00C00548 */  mfc2       $a1, C2_MAC0 /* handwritten instruction */
/* 4990C 8005910C 0006063C */  lui        $a2, (0x6000000 >> 16)
/* 49910 80059110 0C00A018 */  blez       $a1, .L80059144
/* 49914 80059114 0000C6AF */   sw        $a2, 0x0($fp)
/* 49918 80059118 0000258E */  lw         $a1, 0x0($s1)
/* 4991C 8005911C 00003EAE */  sw         $fp, 0x0($s1)
/* 49920 80059120 0500A010 */  beqz       $a1, .L80059138
/* 49924 80059124 02341E00 */   srl       $a2, $fp, 16
/* 49928 80059128 0000BEA4 */  sh         $fp, 0x0($a1)
/* 4992C 8005912C 0200A6A0 */  sb         $a2, 0x2($a1)
/* 49930 80059130 51640108 */  j          .L80059144
/* 49934 80059134 1C00DE23 */   addi      $fp, $fp, 0x1C /* handwritten instruction */
.L80059138:
/* 49938 80059138 04003EAE */  sw         $fp, 0x4($s1)
/* 4993C 8005913C 51640108 */  j          .L80059144
/* 49940 80059140 1C00DE23 */   addi      $fp, $fp, 0x1C /* handwritten instruction */
.L80059144:
/* 49944 80059144 00608D48 */  mtc2       $t5, C2_SXY0 /* handwritten instruction */
/* 49948 80059148 00689048 */  mtc2       $s0, C2_SXY1 /* handwritten instruction */
/* 4994C 8005914C 00708F48 */  mtc2       $t7, C2_SXY2 /* handwritten instruction */
/* 49950 80059150 0800CDAF */  sw         $t5, 0x8($fp)
/* 49954 80059154 1000D0AF */  sw         $s0, 0x10($fp)
/* 49958 80059158 0600404B */  NCLIP
/* 4995C 8005915C 1800CFAF */  sw         $t7, 0x18($fp)
/* 49960 80059160 0400C1AF */  sw         $at, 0x4($fp)
/* 49964 80059164 0C00C4AF */  sw         $a0, 0xC($fp)
/* 49968 80059168 1400C3AF */  sw         $v1, 0x14($fp)
/* 4996C 8005916C 00C00548 */  mfc2       $a1, C2_MAC0 /* handwritten instruction */
/* 49970 80059170 0006063C */  lui        $a2, (0x6000000 >> 16)
/* 49974 80059174 0C00A018 */  blez       $a1, .L800591A8
/* 49978 80059178 0000C6AF */   sw        $a2, 0x0($fp)
/* 4997C 8005917C 0000258E */  lw         $a1, 0x0($s1)
/* 49980 80059180 00003EAE */  sw         $fp, 0x0($s1)
/* 49984 80059184 0500A010 */  beqz       $a1, .L8005919C
/* 49988 80059188 02341E00 */   srl       $a2, $fp, 16
/* 4998C 8005918C 0000BEA4 */  sh         $fp, 0x0($a1)
/* 49990 80059190 0200A6A0 */  sb         $a2, 0x2($a1)
/* 49994 80059194 6A640108 */  j          .L800591A8
/* 49998 80059198 1C00DE23 */   addi      $fp, $fp, 0x1C /* handwritten instruction */
.L8005919C:
/* 4999C 8005919C 04003EAE */  sw         $fp, 0x4($s1)
/* 499A0 800591A0 6A640108 */  j          .L800591A8
/* 499A4 800591A4 1C00DE23 */   addi      $fp, $fp, 0x1C /* handwritten instruction */
.L800591A8:
/* 499A8 800591A8 00608E48 */  mtc2       $t6, C2_SXY0 /* handwritten instruction */
/* 499AC 800591AC 00688F48 */  mtc2       $t7, C2_SXY1 /* handwritten instruction */
/* 499B0 800591B0 00709048 */  mtc2       $s0, C2_SXY2 /* handwritten instruction */
/* 499B4 800591B4 0800CEAF */  sw         $t6, 0x8($fp)
/* 499B8 800591B8 1000CFAF */  sw         $t7, 0x10($fp)
/* 499BC 800591BC 0600404B */  NCLIP
/* 499C0 800591C0 1800D0AF */  sw         $s0, 0x18($fp)
/* 499C4 800591C4 0400C2AF */  sw         $v0, 0x4($fp)
/* 499C8 800591C8 0C00C3AF */  sw         $v1, 0xC($fp)
/* 499CC 800591CC 1400C4AF */  sw         $a0, 0x14($fp)
/* 499D0 800591D0 00C00548 */  mfc2       $a1, C2_MAC0 /* handwritten instruction */
/* 499D4 800591D4 0006063C */  lui        $a2, (0x6000000 >> 16)
/* 499D8 800591D8 0C00A018 */  blez       $a1, .L8005920C
/* 499DC 800591DC 0000C6AF */   sw        $a2, 0x0($fp)
/* 499E0 800591E0 0000258E */  lw         $a1, 0x0($s1)
/* 499E4 800591E4 00003EAE */  sw         $fp, 0x0($s1)
/* 499E8 800591E8 0500A010 */  beqz       $a1, .L80059200
/* 499EC 800591EC 02341E00 */   srl       $a2, $fp, 16
/* 499F0 800591F0 0000BEA4 */  sh         $fp, 0x0($a1)
/* 499F4 800591F4 0200A6A0 */  sb         $a2, 0x2($a1)
/* 499F8 800591F8 83640108 */  j          .L8005920C
/* 499FC 800591FC 1C00DE23 */   addi      $fp, $fp, 0x1C /* handwritten instruction */
.L80059200:
/* 49A00 80059200 04003EAE */  sw         $fp, 0x4($s1)
/* 49A04 80059204 83640108 */  j          .L8005920C
/* 49A08 80059208 1C00DE23 */   addi      $fp, $fp, 0x1C /* handwritten instruction */
.L8005920C:
/* 49A0C 8005920C F0FFF722 */  addi       $s7, $s7, -0x10 /* handwritten instruction */
/* 49A10 80059210 020A1800 */  srl        $at, $t8, 8
/* 49A14 80059214 FF002130 */  andi       $at, $at, 0xFF
/* 49A18 80059218 02C41800 */  srl        $t8, $t8, 16
/* 49A1C 8005921C FF001833 */  andi       $t8, $t8, 0xFF
/* 49A20 80059220 2210F502 */  sub        $v0, $s7, $s5 /* handwritten instruction */
/* 49A24 80059224 04004018 */  blez       $v0, .L80059238
/* 49A28 80059228 C2100200 */   srl       $v0, $v0, 3
/* 49A2C 8005922C 20082200 */  add        $at, $at, $v0 /* handwritten instruction */
/* 49A30 80059230 22C00203 */  sub        $t8, $t8, $v0 /* handwritten instruction */
/* 49A34 80059234 0000B722 */  addi       $s7, $s5, 0x0 /* handwritten instruction */
.L80059238:
/* 49A38 80059238 05000220 */  addi       $v0, $zero, 0x5 /* handwritten instruction */
/* 49A3C 8005923C 18002200 */  mult       $at, $v0
/* 49A40 80059240 80000220 */  addi       $v0, $zero, 0x80 /* handwritten instruction */
/* 49A44 80059244 12080000 */  mflo       $at
/* 49A48 80059248 22104100 */  sub        $v0, $v0, $at /* handwritten instruction */
/* 49A4C 8005924C 001A0200 */  sll        $v1, $v0, 8
/* 49A50 80059250 25104300 */  or         $v0, $v0, $v1
/* 49A54 80059254 001A0300 */  sll        $v1, $v1, 8
/* 49A58 80059258 25104300 */  or         $v0, $v0, $v1
/* 49A5C 8005925C 003E053C */  lui        $a1, (0x3E000000 >> 16)
/* 49A60 80059260 2528A200 */  or         $a1, $a1, $v0
/* 49A64 80059264 02004012 */  beqz       $s2, .L80059270
/* 49A68 80059268 0000E423 */   addi      $a0, $ra, 0x0 /* handwritten instruction */
/* 49A6C 8005926C 08008420 */  addi       $a0, $a0, 0x8 /* handwritten instruction */
.L80059270:
/* 49A70 80059270 1000838C */  lw         $v1, 0x10($a0)
/* 49A74 80059274 1400848C */  lw         $a0, 0x14($a0)
/* 49A78 80059278 000A0100 */  sll        $at, $at, 8
/* 49A7C 8005927C 20186100 */  add        $v1, $v1, $at /* handwritten instruction */
/* 49A80 80059280 20208100 */  add        $a0, $a0, $at /* handwritten instruction */
/* 49A84 80059284 000A1420 */  addi       $s4, $zero, 0xA00 /* handwritten instruction */
/* 49A88 80059288 0A00153C */  lui        $s5, (0xA0A0A >> 16)
/* 49A8C 8005928C 0A0AB522 */  addi       $s5, $s5, (0xA0A0A & 0xFFFF) /* handwritten instruction */
/* 49A90 80059290 AE640108 */  j          .L800592B8
/* 49A94 80059294 00000120 */   addi      $at, $zero, 0x0 /* handwritten instruction */
.L80059298:
/* 49A98 80059298 FAFE001B */  blez       $t8, .L80058E84
/* 49A9C 8005929C FFFF1823 */   addi      $t8, $t8, -0x1 /* handwritten instruction */
/* 49AA0 800592A0 0500001F */  bgtz       $t8, .L800592B8
/* 49AA4 800592A4 FFFF1823 */   addi      $t8, $t8, -0x1 /* handwritten instruction */
/* 49AA8 800592A8 0800F722 */  addi       $s7, $s7, 0x8 /* handwritten instruction */
/* 49AAC 800592AC 00051420 */  addi       $s4, $zero, 0x500 /* handwritten instruction */
/* 49AB0 800592B0 0500153C */  lui        $s5, (0x50505 >> 16)
/* 49AB4 800592B4 0505B522 */  addi       $s5, $s5, (0x50505 & 0xFFFF) /* handwritten instruction */
.L800592B8:
/* 49AB8 800592B8 0000E78E */  lw         $a3, 0x0($s7)
/* 49ABC 800592BC 0400E88E */  lw         $t0, 0x4($s7)
/* 49AC0 800592C0 F0FFF722 */  addi       $s7, $s7, -0x10 /* handwritten instruction */
/* 49AC4 800592C4 00340700 */  sll        $a2, $a3, 16
/* 49AC8 800592C8 03340600 */  sra        $a2, $a2, 16
/* 49ACC 800592CC 033C0700 */  sra        $a3, $a3, 16
/* 49AD0 800592D0 C2530800 */  srl        $t2, $t0, 15
/* 49AD4 800592D4 FE014A31 */  andi       $t2, $t2, 0x1FE
/* 49AD8 800592D8 20606A02 */  add        $t4, $s3, $t2 /* handwritten instruction */
/* 49ADC 800592DC 80008B21 */  addi       $t3, $t4, 0x80 /* handwritten instruction */
/* 49AE0 800592E0 00006B85 */  lh         $t3, 0x0($t3)
/* 49AE4 800592E4 00008C85 */  lh         $t4, 0x0($t4)
/* 49AE8 800592E8 0700001B */  blez       $t8, .L80059308
/* 49AEC 800592EC 08000920 */   addi      $t1, $zero, 0x8 /* handwritten instruction */
/* 49AF0 800592F0 20E08103 */  add        $gp, $gp, $at /* handwritten instruction */
/* 49AF4 800592F4 04008013 */  beqz       $gp, .L80059308
/* 49AF8 800592F8 00000000 */   nop
/* 49AFC 800592FC 02004012 */  beqz       $s2, .L80059308
/* 49B00 80059300 2C000920 */   addi      $t1, $zero, 0x2C /* handwritten instruction */
/* 49B04 80059304 40000920 */  addi       $t1, $zero, 0x40 /* handwritten instruction */
.L80059308:
/* 49B08 80059308 00440800 */  sll        $t0, $t0, 16
/* 49B0C 8005930C 03440800 */  sra        $t0, $t0, 16
/* 49B10 80059310 18002B01 */  mult       $t1, $t3
/* 49B14 80059314 12580000 */  mflo       $t3
/* 49B18 80059318 C35A0B00 */  sra        $t3, $t3, 11
/* 49B1C 8005931C 00000000 */  nop
/* 49B20 80059320 18002C01 */  mult       $t1, $t4
/* 49B24 80059324 12600000 */  mflo       $t4
/* 49B28 80059328 C3620C00 */  sra        $t4, $t4, 11
/* 49B2C 8005932C 22486701 */  sub        $t1, $t3, $a3 /* handwritten instruction */
/* 49B30 80059330 22508801 */  sub        $t2, $t4, $t0 /* handwritten instruction */
/* 49B34 80059334 40580B00 */  sll        $t3, $t3, 1
/* 49B38 80059338 40600C00 */  sll        $t4, $t4, 1
/* 49B3C 8005933C 22582B01 */  sub        $t3, $t1, $t3 /* handwritten instruction */
/* 49B40 80059340 22604C01 */  sub        $t4, $t2, $t4 /* handwritten instruction */
/* 49B44 80059344 FFFF2931 */  andi       $t1, $t1, 0xFFFF
/* 49B48 80059348 FFFF6B31 */  andi       $t3, $t3, 0xFFFF
/* 49B4C 8005934C 00540A00 */  sll        $t2, $t2, 16
/* 49B50 80059350 00640C00 */  sll        $t4, $t4, 16
/* 49B54 80059354 25482A01 */  or         $t1, $t1, $t2
/* 49B58 80059358 25586C01 */  or         $t3, $t3, $t4
/* 49B5C 8005935C 00088648 */  mtc2       $a2, C2_VZ0 /* handwritten instruction */
/* 49B60 80059360 00188648 */  mtc2       $a2, C2_VZ1 /* handwritten instruction */
/* 49B64 80059364 00008948 */  mtc2       $t1, C2_VXY0 /* handwritten instruction */
/* 49B68 80059368 00108B48 */  mtc2       $t3, C2_VXY1 /* handwritten instruction */
/* 49B6C 8005936C 00000000 */  nop
/* 49B70 80059370 00000000 */  nop
/* 49B74 80059374 3000284A */  RTPT
/* 49B78 80059378 0800C1AF */  sw         $at, 0x8($fp)
/* 49B7C 8005937C 1400C2AF */  sw         $v0, 0x14($fp)
/* 49B80 80059380 0C00C3AF */  sw         $v1, 0xC($fp)
/* 49B84 80059384 1800C4AF */  sw         $a0, 0x18($fp)
/* 49B88 80059388 0400C5AF */  sw         $a1, 0x4($fp)
/* 49B8C 8005938C 1000C5AF */  sw         $a1, 0x10($fp)
/* 49B90 80059390 000C063C */  lui        $a2, (0xC000000 >> 16)
/* 49B94 80059394 0000C6AF */  sw         $a2, 0x0($fp)
/* 49B98 80059398 00600648 */  mfc2       $a2, C2_SXY0 /* handwritten instruction */
/* 49B9C 8005939C 00680748 */  mfc2       $a3, C2_SXY1 /* handwritten instruction */
/* 49BA0 800593A0 00880848 */  mfc2       $t0, C2_SZ1 /* handwritten instruction */
/* 49BA4 800593A4 00900948 */  mfc2       $t1, C2_SZ2 /* handwritten instruction */
/* 49BA8 800593A8 1C002010 */  beqz       $at, .L8005941C
/* 49BAC 800593AC 20400901 */   add       $t0, $t0, $t1 /* handwritten instruction */
/* 49BB0 800593B0 02420800 */  srl        $t0, $t0, 8
/* 49BB4 800593B4 2000C6AF */  sw         $a2, 0x20($fp)
/* 49BB8 800593B8 2C00C7AF */  sw         $a3, 0x2C($fp)
/* 49BBC 800593BC 0000C120 */  addi       $at, $a2, 0x0 /* handwritten instruction */
/* 49BC0 800593C0 0000E220 */  addi       $v0, $a3, 0x0 /* handwritten instruction */
/* 49BC4 800593C4 20187400 */  add        $v1, $v1, $s4 /* handwritten instruction */
/* 49BC8 800593C8 2400C3AF */  sw         $v1, 0x24($fp)
/* 49BCC 800593CC 20209400 */  add        $a0, $a0, $s4 /* handwritten instruction */
/* 49BD0 800593D0 3000C4AF */  sw         $a0, 0x30($fp)
/* 49BD4 800593D4 2228B500 */  sub        $a1, $a1, $s5 /* handwritten instruction */
/* 49BD8 800593D8 1C00C5AF */  sw         $a1, 0x1C($fp)
/* 49BDC 800593DC 2800C5AF */  sw         $a1, 0x28($fp)
/* 49BE0 800593E0 FEFF0821 */  addi       $t0, $t0, -0x2 /* handwritten instruction */
/* 49BE4 800593E4 ACFF0005 */  bltz       $t0, .L80059298
/* 49BE8 800593E8 C0400800 */   sll       $t0, $t0, 3
/* 49BEC 800593EC 20401D01 */  add        $t0, $t0, $sp /* handwritten instruction */
/* 49BF0 800593F0 0000068D */  lw         $a2, 0x0($t0)
/* 49BF4 800593F4 00001EAD */  sw         $fp, 0x0($t0)
/* 49BF8 800593F8 0500C010 */  beqz       $a2, .L80059410
/* 49BFC 800593FC 023C1E00 */   srl       $a3, $fp, 16
/* 49C00 80059400 0000DEA4 */  sh         $fp, 0x0($a2)
/* 49C04 80059404 0200C7A0 */  sb         $a3, 0x2($a2)
/* 49C08 80059408 A6640108 */  j          .L80059298
/* 49C0C 8005940C 3400DE23 */   addi      $fp, $fp, 0x34 /* handwritten instruction */
.L80059410:
/* 49C10 80059410 04001EAD */  sw         $fp, 0x4($t0)
/* 49C14 80059414 A6640108 */  j          .L80059298
/* 49C18 80059418 3400DE23 */   addi      $fp, $fp, 0x34 /* handwritten instruction */
.L8005941C:
/* 49C1C 8005941C 0000C120 */  addi       $at, $a2, 0x0 /* handwritten instruction */
/* 49C20 80059420 A6640108 */  j          .L80059298
/* 49C24 80059424 0000E220 */   addi      $v0, $a3, 0x0 /* handwritten instruction */
.L80059428:
/* 49C28 80059428 0780013C */  lui        $at, %hi(D_800757B0)
/* 49C2C 8005942C B0572124 */  addiu      $at, $at, %lo(D_800757B0)
/* 49C30 80059430 00003EAC */  sw         $fp, 0x0($at)
/* 49C34 80059434 0780013C */  lui        $at, %hi(D_80077DD8)
/* 49C38 80059438 D87D2124 */  addiu      $at, $at, %lo(D_80077DD8)
/* 49C3C 8005943C 2C003F8C */  lw         $ra, 0x2C($at)
/* 49C40 80059440 28003E8C */  lw         $fp, 0x28($at)
/* 49C44 80059444 24003D8C */  lw         $sp, 0x24($at)
/* 49C48 80059448 20003C8C */  lw         $gp, 0x20($at)
/* 49C4C 8005944C 1C00378C */  lw         $s7, 0x1C($at)
/* 49C50 80059450 1800368C */  lw         $s6, 0x18($at)
/* 49C54 80059454 1400358C */  lw         $s5, 0x14($at)
/* 49C58 80059458 1000348C */  lw         $s4, 0x10($at)
/* 49C5C 8005945C 0C00338C */  lw         $s3, 0xC($at)
/* 49C60 80059460 0800328C */  lw         $s2, 0x8($at)
/* 49C64 80059464 0400318C */  lw         $s1, 0x4($at)
/* 49C68 80059468 0000308C */  lw         $s0, 0x0($at)
/* 49C6C 8005946C 0800E003 */  jr         $ra
/* 49C70 80059470 00000000 */   nop
.size func_80058D64, . - func_80058D64
