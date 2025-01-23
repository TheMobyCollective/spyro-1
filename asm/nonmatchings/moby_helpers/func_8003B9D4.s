.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003B9D4
/* 2C1D4 8003B9D4 0780023C */  lui        $v0, %hi(D_800756C8)
/* 2C1D8 8003B9D8 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 2C1DC 8003B9DC D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 2C1E0 8003B9E0 2000B0AF */  sw         $s0, 0x20($sp)
/* 2C1E4 8003B9E4 21808000 */  addu       $s0, $a0, $zero
/* 2C1E8 8003B9E8 2400BFAF */  sw         $ra, 0x24($sp)
/* 2C1EC 8003B9EC 36000396 */  lhu        $v1, 0x36($s0)
/* 2C1F0 8003B9F0 1F004230 */  andi       $v0, $v0, 0x1F
/* 2C1F4 8003B9F4 0780013C */  lui        $at, %hi(D_80077DB8)
/* 2C1F8 8003B9F8 21082200 */  addu       $at, $at, $v0
/* 2C1FC 8003B9FC B87D23A0 */  sb         $v1, %lo(D_80077DB8)($at)
/* 2C200 8003BA00 0780023C */  lui        $v0, %hi(D_800756C8)
/* 2C204 8003BA04 C856428C */  lw         $v0, %lo(D_800756C8)($v0)
/* 2C208 8003BA08 0780033C */  lui        $v1, %hi(D_80075758)
/* 2C20C 8003BA0C 5857638C */  lw         $v1, %lo(D_80075758)($v1)
/* 2C210 8003BA10 01004224 */  addiu      $v0, $v0, 0x1
/* 2C214 8003BA14 0780013C */  lui        $at, %hi(D_800756C8)
/* 2C218 8003BA18 C85622AC */  sw         $v0, %lo(D_800756C8)($at)
/* 2C21C 8003BA1C 04000316 */  bne        $s0, $v1, .L8003BA30
/* 2C220 8003BA20 21200002 */   addu      $a0, $s0, $zero
/* 2C224 8003BA24 03000224 */  addiu      $v0, $zero, 0x3
/* 2C228 8003BA28 0780013C */  lui        $at, %hi(D_80075830)
/* 2C22C 8003BA2C 305822AC */  sw         $v0, %lo(D_80075830)($at)
.L8003BA30:
/* 2C230 8003BA30 794A010C */  jal        func_800529E4
/* 2C234 8003BA34 04000524 */   addiu     $a1, $zero, 0x4
/* 2C238 8003BA38 06000424 */  addiu      $a0, $zero, 0x6
/* 2C23C 8003BA3C 0C000524 */  addiu      $a1, $zero, 0xC
/* 2C240 8003BA40 36000286 */  lh         $v0, 0x36($s0)
/* 2C244 8003BA44 0780033C */  lui        $v1, %hi(D_800758E4)
/* 2C248 8003BA48 E458638C */  lw         $v1, %lo(D_800758E4)($v1)
/* 2C24C 8003BA4C 80100200 */  sll        $v0, $v0, 2
/* 2C250 8003BA50 0780013C */  lui        $at, %hi(D_8006E330)
/* 2C254 8003BA54 21082200 */  addu       $at, $at, $v0
/* 2C258 8003BA58 30E3278C */  lw         $a3, %lo(D_8006E330)($at)
/* 2C25C 8003BA5C 09F86000 */  jalr       $v1
/* 2C260 8003BA60 21300002 */   addu      $a2, $s0, $zero
/* 2C264 8003BA64 36000386 */  lh         $v1, 0x36($s0)
/* 2C268 8003BA68 53000224 */  addiu      $v0, $zero, 0x53
/* 2C26C 8003BA6C 03006214 */  bne        $v1, $v0, .L8003BA7C
/* 2C270 8003BA70 54000224 */   addiu     $v0, $zero, 0x54
/* 2C274 8003BA74 ADEE0008 */  j          .L8003BAB4
/* 2C278 8003BA78 01000424 */   addiu     $a0, $zero, 0x1
.L8003BA7C:
/* 2C27C 8003BA7C 03006214 */  bne        $v1, $v0, .L8003BA8C
/* 2C280 8003BA80 55000224 */   addiu     $v0, $zero, 0x55
/* 2C284 8003BA84 ADEE0008 */  j          .L8003BAB4
/* 2C288 8003BA88 02000424 */   addiu     $a0, $zero, 0x2
.L8003BA8C:
/* 2C28C 8003BA8C 03006214 */  bne        $v1, $v0, .L8003BA9C
/* 2C290 8003BA90 56000224 */   addiu     $v0, $zero, 0x56
/* 2C294 8003BA94 ADEE0008 */  j          .L8003BAB4
/* 2C298 8003BA98 05000424 */   addiu     $a0, $zero, 0x5
.L8003BA9C:
/* 2C29C 8003BA9C 03006214 */  bne        $v1, $v0, .L8003BAAC
/* 2C2A0 8003BAA0 57000224 */   addiu     $v0, $zero, 0x57
/* 2C2A4 8003BAA4 ADEE0008 */  j          .L8003BAB4
/* 2C2A8 8003BAA8 0A000424 */   addiu     $a0, $zero, 0xA
.L8003BAAC:
/* 2C2AC 8003BAAC 03006214 */  bne        $v1, $v0, .L8003BABC
/* 2C2B0 8003BAB0 19000424 */   addiu     $a0, $zero, 0x19
.L8003BAB4:
/* 2C2B4 8003BAB4 15EE000C */  jal        func_8003B854
/* 2C2B8 8003BAB8 21280002 */   addu      $a1, $s0, $zero
.L8003BABC:
/* 2C2BC 8003BABC 2400BF8F */  lw         $ra, 0x24($sp)
/* 2C2C0 8003BAC0 2000B08F */  lw         $s0, 0x20($sp)
/* 2C2C4 8003BAC4 2800BD27 */  addiu      $sp, $sp, 0x28
/* 2C2C8 8003BAC8 0800E003 */  jr         $ra
/* 2C2CC 8003BACC 00000000 */   nop
.size func_8003B9D4, . - func_8003B9D4
