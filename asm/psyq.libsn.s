.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

dlabel D_800730BC
/* 638BC 800730BC 00000000 */ .word 0x00000000
.size D_800730BC, . - D_800730BC

dlabel D_800730C0
/* 638C0 800730C0 00000000 */ .word 0x00000000
.size D_800730C0, . - D_800730C0

dlabel D_800730C4
/* 638C4 800730C4 00000000 */ .word 0x00000000
/* 638C8 800730C8 04220180 */ .word main
/* 638CC 800730CC DC990500 */ .word 0x000599DC
/* 638D0 800730D0 E0BB0680 */ .word D_8006BBE0
/* 638D4 800730D4 84960000 */ .word 0x00009684
/* 638D8 800730D8 78590780 */ .word 0x00000000
/* 638DC 800730DC C0500000 */ .word 0x000050C0
/* 638E0 800730E0 50731115 */ .word 0x15117350
/* 638E4 800730E4 9CB44000 */ .word 0x0040B49C
.size D_800730C4, . - D_800730C4

dlabel D_80075640
/* 65E40 80075640 */ .space 0x08

dlabel D_80075648
/* 65E48 80075648 */ .space 0x10

dlabel D_80075658
/* 65E58 80075658 */ .space 0x10


glabel func_8005B8E0
/* 4C0E0 8005B8E0 0780023C */  lui        $v0, %hi(main_BSS_START)
/* 4C0E4 8005B8E4 40564224 */  addiu      $v0, $v0, %lo(main_BSS_START)
/* 4C0E8 8005B8E8 0880033C */  lui        $v1, %hi(main_BSS_END)
/* 4C0EC 8005B8EC 38AA6324 */  addiu      $v1, $v1, %lo(main_BSS_END)
.L8005B8F0:
/* 4C0F0 8005B8F0 000040AC */  sw         $zero, 0x0($v0)
/* 4C0F4 8005B8F4 04004224 */  addiu      $v0, $v0, 0x4
/* 4C0F8 8005B8F8 2B084300 */  sltu       $at, $v0, $v1
/* 4C0FC 8005B8FC FCFF2014 */  bnez       $at, .L8005B8F0
/* 4C100 8005B900 00000000 */   nop
/* 4C104 8005B904 0780023C */  lui        $v0, %hi(_ramsize)
/* 4C108 8005B908 A855428C */  lw         $v0, %lo(_ramsize)($v0)
/* 4C10C 8005B90C 00000000 */  nop
/* 4C110 8005B910 F8FF4220 */  addi       $v0, $v0, -0x8 /* handwritten instruction */
/* 4C114 8005B914 0080083C */  lui        $t0, %hi(0x80000004)
/* 4C118 8005B918 25E84800 */  or         $sp, $v0, $t0
/* 4C11C 8005B91C 0880043C */  lui        $a0, %hi(main_BSS_END)
/* 4C120 8005B920 38AA8424 */  addiu      $a0, $a0, %lo(main_BSS_END)
/* 4C124 8005B924 C0200400 */  sll        $a0, $a0, 3
/* 4C128 8005B928 C2200400 */  srl        $a0, $a0, 3
/* 4C12C 8005B92C 0780033C */  lui        $v1, %hi(_stacksize)
/* 4C130 8005B930 A455638C */  lw         $v1, %lo(_stacksize)($v1)
/* 4C134 8005B934 00000000 */  nop
/* 4C138 8005B938 23284300 */  subu       $a1, $v0, $v1
/* 4C13C 8005B93C 2328A400 */  subu       $a1, $a1, $a0
/* 4C140 8005B940 0780013C */  lui        $at, %hi(D_800730C4)
/* 4C144 8005B944 C43025AC */  sw         $a1, %lo(D_800730C4)($at)
/* 4C148 8005B948 25208800 */  or         $a0, $a0, $t0
/* 4C14C 8005B94C 0780013C */  lui        $at, %hi(D_800730C0)
/* 4C150 8005B950 C03024AC */  sw         $a0, %lo(D_800730C0)($at)
/* 4C154 8005B954 0780013C */  lui        $at, %hi(D_80075640)
/* 4C158 8005B958 40563FAC */  sw         $ra, %lo(D_80075640)($at)
/* 4C15C 8005B95C 07801C3C */  lui        $gp, %hi(_gp)
/* 4C160 8005B960 64529C27 */  addiu      $gp, $gp, %lo(_gp)
/* 4C164 8005B964 21F0A003 */  addu       $fp, $sp, $zero
 /* 4C168 8005B968 C576010C */  /*jal        func_8005DB14*/
/* 4C16C 8005B96C 04008420 */   addi      $a0, $a0, %lo(0x80000004) /* handwritten instruction */
/* 4C170 8005B970 07801F3C */  lui        $ra, %hi(D_80075640)
/* 4C174 8005B974 4056FF8F */  lw         $ra, %lo(D_80075640)($ra)
/* 4C178 8005B978 00000000 */  nop
/* 4C17C 8005B97C 8148000C */  jal        main
/* 4C180 8005B980 00000000 */   nop
/* 4C184 8005B984 4D000000 */  break      0, 1
.size func_8005B8E0, . - func_8005B8E0

glabel __main
/* 4C188 8005B988 0780083C */  lui        $t0, %hi(D_800730BC)
/* 4C18C 8005B98C BC30088D */  lw         $t0, %lo(D_800730BC)($t0)
/* 4C190 8005B990 F0FFBD27 */  addiu      $sp, $sp, -0x10
/* 4C194 8005B994 0400B0AF */  sw         $s0, 0x4($sp)
/* 4C198 8005B998 0800B1AF */  sw         $s1, 0x8($sp)
/* 4C19C 8005B99C 0C00BFAF */  sw         $ra, 0xC($sp)
/* 4C1A0 8005B9A0 0F000015 */  bnez       $t0, .L8005B9E0
/* 4C1A4 8005B9A4 01000834 */   ori       $t0, $zero, 0x1
/* 4C1A8 8005B9A8 0780013C */  lui        $at, %hi(D_800730BC)
/* 4C1AC 8005B9AC BC3028AC */  sw         $t0, %lo(D_800730BC)($at)
/* 4C1B0 8005B9B0 0180103C */  lui        $s0, %hi(D_80010000)
/* 4C1B4 8005B9B4 00001026 */  addiu      $s0, $s0, %lo(D_80010000)
/* 4C1B8 8005B9B8 0000113C */  lui        $s1, (0x0 >> 16)
/* 4C1BC 8005B9BC 00003126 */  addiu      $s1, $s1, 0x0
/* 4C1C0 8005B9C0 07002012 */  beqz       $s1, .L8005B9E0
/* 4C1C4 8005B9C4 00000000 */   nop
.L8005B9C8:
/* 4C1C8 8005B9C8 0000088E */  lw         $t0, 0x0($s0)
/* 4C1CC 8005B9CC 04001026 */  addiu      $s0, $s0, 0x4
/* 4C1D0 8005B9D0 09F80001 */  jalr       $t0
/* 4C1D4 8005B9D4 FFFF3126 */   addiu     $s1, $s1, -0x1
/* 4C1D8 8005B9D8 FBFF2016 */  bnez       $s1, .L8005B9C8
/* 4C1DC 8005B9DC 00000000 */   nop
.L8005B9E0:
/* 4C1E0 8005B9E0 0C00BF8F */  lw         $ra, 0xC($sp)
/* 4C1E4 8005B9E4 0800B18F */  lw         $s1, 0x8($sp)
/* 4C1E8 8005B9E8 0400B08F */  lw         $s0, 0x4($sp)
/* 4C1EC 8005B9EC 1000BD27 */  addiu      $sp, $sp, 0x10
/* 4C1F0 8005B9F0 0800E003 */  jr         $ra
/* 4C1F4 8005B9F4 00000000 */   nop
.size __main, . - __main
