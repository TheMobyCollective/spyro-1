.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80049660
/* 39E60 80049660 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 39E64 80049664 1000B0AF */  sw         $s0, 0x10($sp)
/* 39E68 80049668 0880103C */  lui        $s0, %hi(g_Spyro + 0x60)
/* 39E6C 8004966C B88A1026 */  addiu      $s0, $s0, %lo(g_Spyro + 0x60)
/* 39E70 80049670 1400BFAF */  sw         $ra, 0x14($sp)
/* 39E74 80049674 0000038E */  lw         $v1, 0x0($s0)
/* 39E78 80049678 01000524 */  addiu      $a1, $zero, 0x1
/* 39E7C 8004967C 6E006510 */  beq        $v1, $a1, .L80049838
/* 39E80 80049680 02006228 */   slti      $v0, $v1, 0x2
/* 39E84 80049684 05004010 */  beqz       $v0, .L8004969C
/* 39E88 80049688 00000000 */   nop
/* 39E8C 8004968C 08006010 */  beqz       $v1, .L800496B0
/* 39E90 80049690 00000000 */   nop
/* 39E94 80049694 1B260108 */  j          .L8004986C
/* 39E98 80049698 00000000 */   nop
.L8004969C:
/* 39E9C 8004969C 02000224 */  addiu      $v0, $zero, 0x2
/* 39EA0 800496A0 61006210 */  beq        $v1, $v0, .L80049828
/* 39EA4 800496A4 00000000 */   nop
/* 39EA8 800496A8 1B260108 */  j          .L8004986C
/* 39EAC 800496AC 00000000 */   nop
.L800496B0:
/* 39EB0 800496B0 0880073C */  lui        $a3, %hi(g_Spyro + 0x198)
/* 39EB4 800496B4 F08BE78C */  lw         $a3, %lo(g_Spyro + 0x198)($a3)
/* 39EB8 800496B8 0800028E */  lw         $v0, 0x8($s0)
/* 39EBC 800496BC 00000000 */  nop
/* 39EC0 800496C0 1F00E214 */  bne        $a3, $v0, .L80049740
/* 39EC4 800496C4 00000000 */   nop
/* 39EC8 800496C8 1700E014 */  bnez       $a3, .L80049728
/* 39ECC 800496CC 00000000 */   nop
/* 39ED0 800496D0 0880023C */  lui        $v0, %hi(g_Spyro + 0x18)
/* 39ED4 800496D4 708A4290 */  lbu        $v0, %lo(g_Spyro + 0x18)($v0)
/* 39ED8 800496D8 0880033C */  lui        $v1, %hi(g_Spyro + 0x1E)
/* 39EDC 800496DC 768A6390 */  lbu        $v1, %lo(g_Spyro + 0x1E)($v1)
/* 39EE0 800496E0 0880043C */  lui        $a0, %hi(g_Spyro + 0x19)
/* 39EE4 800496E4 718A8490 */  lbu        $a0, %lo(g_Spyro + 0x19)($a0)
/* 39EE8 800496E8 0880053C */  lui        $a1, %hi(g_Spyro + 0x1F)
/* 39EEC 800496EC 778AA590 */  lbu        $a1, %lo(g_Spyro + 0x1F)($a1)
/* 39EF0 800496F0 0880063C */  lui        $a2, %hi(g_Spyro + 0x24)
/* 39EF4 800496F4 7C8AC690 */  lbu        $a2, %lo(g_Spyro + 0x24)($a2)
/* 39EF8 800496F8 0880013C */  lui        $at, %hi(g_Spyro + 0x1A)
/* 39EFC 800496FC 728A22A0 */  sb         $v0, %lo(g_Spyro + 0x1A)($at)
/* 39F00 80049700 0880013C */  lui        $at, %hi(g_Spyro + 0x20)
/* 39F04 80049704 788A23A0 */  sb         $v1, %lo(g_Spyro + 0x20)($at)
/* 39F08 80049708 0880013C */  lui        $at, %hi(g_Spyro + 0x1B)
/* 39F0C 8004970C 738A24A0 */  sb         $a0, %lo(g_Spyro + 0x1B)($at)
/* 39F10 80049710 0880013C */  lui        $at, %hi(g_Spyro + 0x21)
/* 39F14 80049714 798A25A0 */  sb         $a1, %lo(g_Spyro + 0x21)($at)
/* 39F18 80049718 0880013C */  lui        $at, %hi(g_Spyro + 0x25)
/* 39F1C 8004971C 7D8A26A0 */  sb         $a2, %lo(g_Spyro + 0x25)($at)
/* 39F20 80049720 1B260108 */  j          .L8004986C
/* 39F24 80049724 00000000 */   nop
.L80049728:
/* 39F28 80049728 0880043C */  lui        $a0, %hi(g_Spyro + 0x64)
/* 39F2C 8004972C BC8A848C */  lw         $a0, %lo(g_Spyro + 0x64)($a0)
/* 39F30 80049730 7625010C */  jal        func_800495D8
/* 39F34 80049734 00000000 */   nop
/* 39F38 80049738 1B260108 */  j          .L8004986C
/* 39F3C 8004973C 00000000 */   nop
.L80049740:
/* 39F40 80049740 0880023C */  lui        $v0, %hi(g_Spyro + 0x68)
/* 39F44 80049744 C08A428C */  lw         $v0, %lo(g_Spyro + 0x68)($v0)
/* 39F48 80049748 0780033C */  lui        $v1, %hi(D_80075264)
/* 39F4C 8004974C 64526324 */  addiu      $v1, $v1, %lo(D_80075264)
/* 39F50 80049750 40100200 */  sll        $v0, $v0, 1
/* 39F54 80049754 21104300 */  addu       $v0, $v0, $v1
/* 39F58 80049758 21104700 */  addu       $v0, $v0, $a3
/* 39F5C 8004975C 00004490 */  lbu        $a0, 0x0($v0)
/* 39F60 80049760 00000000 */  nop
/* 39F64 80049764 19008510 */  beq        $a0, $a1, .L800497CC
/* 39F68 80049768 02000224 */   addiu     $v0, $zero, 0x2
/* 39F6C 8004976C 3F008214 */  bne        $a0, $v0, .L8004986C
/* 39F70 80049770 00000000 */   nop
/* 39F74 80049774 0880023C */  lui        $v0, %hi(g_Spyro + 0x1B)
/* 39F78 80049778 738A4290 */  lbu        $v0, %lo(g_Spyro + 0x1B)($v0)
/* 39F7C 8004977C 0880033C */  lui        $v1, %hi(g_Spyro + 0x21)
/* 39F80 80049780 798A6390 */  lbu        $v1, %lo(g_Spyro + 0x21)($v1)
/* 39F84 80049784 000004AE */  sw         $a0, 0x0($s0)
/* 39F88 80049788 0880013C */  lui        $at, %hi(g_Spyro + 0x1A)
/* 39F8C 8004978C 728A22A0 */  sb         $v0, %lo(g_Spyro + 0x1A)($at)
/* 39F90 80049790 0880013C */  lui        $at, %hi(g_Spyro + 0x20)
/* 39F94 80049794 788A23A0 */  sb         $v1, %lo(g_Spyro + 0x20)($at)
/* 39F98 80049798 0780013C */  lui        $at, %hi(D_80075268)
/* 39F9C 8004979C 21082700 */  addu       $at, $at, $a3
/* 39FA0 800497A0 68522390 */  lbu        $v1, %lo(D_80075268)($at)
/* 39FA4 800497A4 04000224 */  addiu      $v0, $zero, 0x4
/* 39FA8 800497A8 0880013C */  lui        $at, %hi(g_Spyro + 0x21)
/* 39FAC 800497AC 798A20A0 */  sb         $zero, %lo(g_Spyro + 0x21)($at)
/* 39FB0 800497B0 0880013C */  lui        $at, %hi(g_Spyro + 0x25)
/* 39FB4 800497B4 7D8A22A0 */  sb         $v0, %lo(g_Spyro + 0x25)($at)
/* 39FB8 800497B8 080007AE */  sw         $a3, 0x8($s0)
/* 39FBC 800497BC 0880013C */  lui        $at, %hi(g_Spyro + 0x1B)
/* 39FC0 800497C0 738A23A0 */  sb         $v1, %lo(g_Spyro + 0x1B)($at)
/* 39FC4 800497C4 1B260108 */  j          .L8004986C
/* 39FC8 800497C8 00000000 */   nop
.L800497CC:
/* 39FCC 800497CC 000004AE */  sw         $a0, 0x0($s0)
/* 39FD0 800497D0 0880033C */  lui        $v1, %hi(g_Spyro + 0x1B)
/* 39FD4 800497D4 738A6390 */  lbu        $v1, %lo(g_Spyro + 0x1B)($v1)
/* 39FD8 800497D8 0880043C */  lui        $a0, %hi(g_Spyro + 0x21)
/* 39FDC 800497DC 798A8490 */  lbu        $a0, %lo(g_Spyro + 0x21)($a0)
/* 39FE0 800497E0 0880053C */  lui        $a1, %hi(g_Spyro + 0x19)
/* 39FE4 800497E4 718AA590 */  lbu        $a1, %lo(g_Spyro + 0x19)($a1)
/* 39FE8 800497E8 0880063C */  lui        $a2, %hi(g_Spyro + 0x1F)
/* 39FEC 800497EC 778AC690 */  lbu        $a2, %lo(g_Spyro + 0x1F)($a2)
/* 39FF0 800497F0 02000224 */  addiu      $v0, $zero, 0x2
/* 39FF4 800497F4 0880013C */  lui        $at, %hi(g_Spyro + 0x25)
/* 39FF8 800497F8 7D8A22A0 */  sb         $v0, %lo(g_Spyro + 0x25)($at)
/* 39FFC 800497FC 080007AE */  sw         $a3, 0x8($s0)
/* 3A000 80049800 0880013C */  lui        $at, %hi(g_Spyro + 0x1A)
/* 3A004 80049804 728A23A0 */  sb         $v1, %lo(g_Spyro + 0x1A)($at)
/* 3A008 80049808 0880013C */  lui        $at, %hi(g_Spyro + 0x20)
/* 3A00C 8004980C 788A24A0 */  sb         $a0, %lo(g_Spyro + 0x20)($at)
/* 3A010 80049810 0880013C */  lui        $at, %hi(g_Spyro + 0x1B)
/* 3A014 80049814 738A25A0 */  sb         $a1, %lo(g_Spyro + 0x1B)($at)
/* 3A018 80049818 0880013C */  lui        $at, %hi(g_Spyro + 0x21)
/* 3A01C 8004981C 798A26A0 */  sb         $a2, %lo(g_Spyro + 0x21)($at)
/* 3A020 80049820 1B260108 */  j          .L8004986C
/* 3A024 80049824 00000000 */   nop
.L80049828:
/* 3A028 80049828 0880023C */  lui        $v0, %hi(g_Spyro + 0x25)
/* 3A02C 8004982C 7D8A4290 */  lbu        $v0, %lo(g_Spyro + 0x25)($v0)
/* 3A030 80049830 12260108 */  j          .L80049848
/* 3A034 80049834 04004224 */   addiu     $v0, $v0, 0x4
.L80049838:
/* 3A038 80049838 0880023C */  lui        $v0, %hi(g_Spyro + 0x25)
/* 3A03C 8004983C 7D8A4290 */  lbu        $v0, %lo(g_Spyro + 0x25)($v0)
/* 3A040 80049840 00000000 */  nop
/* 3A044 80049844 02004224 */  addiu      $v0, $v0, 0x2
.L80049848:
/* 3A048 80049848 0880013C */  lui        $at, %hi(g_Spyro + 0x25)
/* 3A04C 8004984C 7D8A22A0 */  sb         $v0, %lo(g_Spyro + 0x25)($at)
/* 3A050 80049850 FF004230 */  andi       $v0, $v0, 0xFF
/* 3A054 80049854 1000422C */  sltiu      $v0, $v0, 0x10
/* 3A058 80049858 04004014 */  bnez       $v0, .L8004986C
/* 3A05C 8004985C 00000000 */   nop
/* 3A060 80049860 7625010C */  jal        func_800495D8
/* 3A064 80049864 21200000 */   addu      $a0, $zero, $zero
/* 3A068 80049868 000000AE */  sw         $zero, 0x0($s0)
.L8004986C:
/* 3A06C 8004986C 1400BF8F */  lw         $ra, 0x14($sp)
/* 3A070 80049870 1000B08F */  lw         $s0, 0x10($sp)
/* 3A074 80049874 1800BD27 */  addiu      $sp, $sp, 0x18
/* 3A078 80049878 0800E003 */  jr         $ra
/* 3A07C 8004987C 00000000 */   nop
.size func_80049660, . - func_80049660
