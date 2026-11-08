.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

dlabel __initialised
/* 638BC 800730BC 00000000 */ .word 0x00000000
.size __initialised, . - __initialised

dlabel __heapbase
/* 638C0 800730C0 00000000 */ .word 0x00000000
.size __heapbase, . - __heapbase

dlabel __heapsize
/* 638C4 800730C4 00000000 */ .word 0x00000000
.size __heapsize, . - __heapsize

dlabel __text
/* 638C8 800730C8 04220180 */ .word main_TEXT_START
.size __text, . - __text

dlabel __textlen
/* 638CC 800730CC DC990500 */ .word main_TEXT_SIZE
.size __textlen, . - __textlen

dlabel __data
/* 638D0 800730D0 E0BB0680 */ .word main_DATA_START
.size __data, . - __data

dlabel __datalen
/* 638D4 800730D4 84960000 */ .word main_DATA_SIZE
.size __datalen, . - __datalen

dlabel __bss
/* 638D8 800730D8 78590780 */ .word main_BSS_START
.size __bss, . - __bss

dlabel __bsslen
/* 638DC 800730DC C0500000 */ .word main_BSS_SIZE
.size __bsslen, . - __bsslen

dlabel D_800730E0
/* 638E0 800730E0 50731115 */ .word 0x15117350
/* 638E4 800730E4 9CB44000 */ .word 0x0040B49C
.size D_800730E0, . - D_800730E0

dlabel __ra_temp
/* 65E40 80075640 */ .space 0x08

dlabel D_80075648
/* 65E48 80075648 */ .space 0x10

dlabel D_80075658
/* 65E58 80075658 */ .space 0x10


glabel __SN_ENTRY_POINT
  la         $v0, main_SBSS_START
  la         $v1, main_BSS_END
.L8005B8F0:
  sw         $zero, 0x0($v0)
  addiu      $v0, $v0, 0x4
  sltu       $at, $v0, $v1
  bnez       $at, .L8005B8F0
   nop
  lw         $v0, _ramsize
  nop
  addi       $v0, $v0, -0x8
  lui        $t0, 0x8000
  or         $sp, $v0, $t0 /* SP = 0x80000000 + (_ramsize - 8) */
  la         $a0, main_BSS_END
  sll        $a0, $a0, 3
  srl        $a0, $a0, 3
  lw         $v1, _stacksize
  nop
  subu       $a1, $v0, $v1
  subu       $a1, $a1, $a0
  lui        $at, %hi(__heapsize)
  sw         $a1, %lo(__heapsize)($at)
  or         $a0, $a0, $t0
  lui        $at, %hi(__heapbase)
  sw         $a0, %lo(__heapbase)($at)
  lui        $at, %hi(__ra_temp)
  sw         $ra, %lo(__ra_temp)($at)
  la         $gp, _gp
  addu       $fp, $sp, $zero
  jal        InitHeap
   addi      $a0, $a0, 0x4
  lw         $ra, __ra_temp
  nop
  jal        main
   nop
  break      0, 1
.size __SN_ENTRY_POINT, . - __SN_ENTRY_POINT

glabel __main
/* 4C188 8005B988 0780083C */  lui        $t0, %hi(__initialised)
/* 4C18C 8005B98C BC30088D */  lw         $t0, %lo(__initialised)($t0)
/* 4C190 8005B990 F0FFBD27 */  addiu      $sp, $sp, -0x10
/* 4C194 8005B994 0400B0AF */  sw         $s0, 0x4($sp)
/* 4C198 8005B998 0800B1AF */  sw         $s1, 0x8($sp)
/* 4C19C 8005B99C 0C00BFAF */  sw         $ra, 0xC($sp)
/* 4C1A0 8005B9A0 0F000015 */  bnez       $t0, .L8005B9E0
/* 4C1A4 8005B9A4 01000834 */   ori       $t0, $zero, 0x1
/* 4C1A8 8005B9A8 0780013C */  lui        $at, %hi(__initialised)
/* 4C1AC 8005B9AC BC3028AC */  sw         $t0, %lo(__initialised)($at)
/* 4C1B0 8005B9B0 0180103C */  lui        $s0, %hi(main_RODATA_START)
/* 4C1B4 8005B9B4 00001026 */  addiu      $s0, $s0, %lo(main_RODATA_START)
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

glabel func_8005B9F8
/* 4C1F8 8005B9F8 0780083C */  lui        $t0, %hi(__initialised)
/* 4C1FC 8005B9FC BC30088D */  lw         $t0, %lo(__initialised)($t0)
/* 4C200 8005BA00 F0FFBD27 */  addiu      $sp, $sp, -0x10
/* 4C204 8005BA04 0400B0AF */  sw         $s0, 0x4($sp)
/* 4C208 8005BA08 0800B1AF */  sw         $s1, 0x8($sp)
/* 4C20C 8005BA0C 0C00BFAF */  sw         $ra, 0xC($sp)
/* 4C210 8005BA10 0D000011 */  beqz       $t0, .L8005BA48
/* 4C214 8005BA14 00000000 */   nop
/* 4C218 8005BA18 0180103C */  lui        $s0, %hi(main_RODATA_START)
/* 4C21C 8005BA1C 00001026 */  addiu      $s0, $s0, %lo(main_RODATA_START)
/* 4C220 8005BA20 0000113C */  lui        $s1, (0x0 >> 16)
/* 4C224 8005BA24 00003126 */  addiu      $s1, $s1, 0x0
/* 4C228 8005BA28 07002012 */  beqz       $s1, .L8005BA48
/* 4C22C 8005BA2C 00000000 */   nop
.L8005BA30:
/* 4C230 8005BA30 0000088E */  lw         $t0, 0x0($s0)
/* 4C234 8005BA34 04001026 */  addiu      $s0, $s0, 0x4
/* 4C238 8005BA38 09F80001 */  jalr       $t0
/* 4C23C 8005BA3C FFFF3126 */   addiu     $s1, $s1, -0x1
/* 4C240 8005BA40 FBFF2016 */  bnez       $s1, .L8005BA30
/* 4C244 8005BA44 00000000 */   nop
.L8005BA48:
/* 4C248 8005BA48 0C00BF8F */  lw         $ra, 0xC($sp)
/* 4C24C 8005BA4C 0800B18F */  lw         $s1, 0x8($sp)
/* 4C250 8005BA50 0400B08F */  lw         $s0, 0x4($sp)
/* 4C254 8005BA54 1000BD27 */  addiu      $sp, $sp, 0x10
/* 4C258 8005BA58 0800E003 */  jr         $ra
/* 4C25C 8005BA5C 00000000 */   nop
.size func_8005B9F8, . - func_8005B9F8
