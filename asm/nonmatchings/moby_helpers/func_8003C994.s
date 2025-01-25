.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003C994
/* 2D194 8003C994 B8FFBD27 */  addiu      $sp, $sp, -0x48
/* 2D198 8003C998 3400B3AF */  sw         $s3, 0x34($sp)
/* 2D19C 8003C99C 21988000 */  addu       $s3, $a0, $zero
/* 2D1A0 8003C9A0 2C00B1AF */  sw         $s1, 0x2C($sp)
/* 2D1A4 8003C9A4 2188A000 */  addu       $s1, $a1, $zero
/* 2D1A8 8003C9A8 2800B0AF */  sw         $s0, 0x28($sp)
/* 2D1AC 8003C9AC 2180C000 */  addu       $s0, $a2, $zero
/* 2D1B0 8003C9B0 3000B2AF */  sw         $s2, 0x30($sp)
/* 2D1B4 8003C9B4 2190E000 */  addu       $s2, $a3, $zero
/* 2D1B8 8003C9B8 1800A427 */  addiu      $a0, $sp, 0x18
/* 2D1BC 8003C9BC 0C006526 */  addiu      $a1, $s3, 0xC
/* 2D1C0 8003C9C0 4000BFAF */  sw         $ra, 0x40($sp)
/* 2D1C4 8003C9C4 3C00B5AF */  sw         $s5, 0x3C($sp)
/* 2D1C8 8003C9C8 3800B4AF */  sw         $s4, 0x38($sp)
/* 2D1CC 8003C9CC 01002692 */  lbu        $a2, 0x1($s1)
/* 2D1D0 8003C9D0 5800B58F */  lw         $s5, 0x58($sp)
/* 2D1D4 8003C9D4 6000B48F */  lw         $s4, 0x60($sp)
/* 2D1D8 8003C9D8 00310600 */  sll        $a2, $a2, 4
/* 2D1DC 8003C9DC 0800C624 */  addiu      $a2, $a2, 0x8
/* 2D1E0 8003C9E0 E35D000C */  jal        VecSub
/* 2D1E4 8003C9E4 21302602 */   addu      $a2, $s1, $a2
/* 2D1E8 8003C9E8 1800A427 */  addiu      $a0, $sp, 0x18
/* 2D1EC 8003C9EC 7F5C000C */  jal        VecMagnitude
/* 2D1F0 8003C9F0 01000524 */   addiu     $a1, $zero, 0x1
/* 2D1F4 8003C9F4 21304000 */  addu       $a2, $v0, $zero
/* 2D1F8 8003C9F8 2A80D000 */  slt        $s0, $a2, $s0
/* 2D1FC 8003C9FC 19000012 */  beqz       $s0, .L8003CA64
/* 2D200 8003CA00 FFFF0224 */   addiu     $v0, $zero, -0x1
/* 2D204 8003CA04 06002386 */  lh         $v1, 0x6($s1)
/* 2D208 8003CA08 00000000 */  nop
/* 2D20C 8003CA0C 0A006214 */  bne        $v1, $v0, .L8003CA38
/* 2D210 8003CA10 FF000324 */   addiu     $v1, $zero, 0xFF
/* 2D214 8003CA14 01002292 */  lbu        $v0, 0x1($s1)
/* 2D218 8003CA18 00002392 */  lbu        $v1, 0x0($s1)
/* 2D21C 8003CA1C 01004224 */  addiu      $v0, $v0, 0x1
/* 2D220 8003CA20 010022A2 */  sb         $v0, 0x1($s1)
/* 2D224 8003CA24 FF004230 */  andi       $v0, $v0, 0xFF
/* 2D228 8003CA28 0E004314 */  bne        $v0, $v1, .L8003CA64
/* 2D22C 8003CA2C 00000000 */   nop
/* 2D230 8003CA30 99F20008 */  j          .L8003CA64
/* 2D234 8003CA34 010020A2 */   sb        $zero, 0x1($s1)
.L8003CA38:
/* 2D238 8003CA38 01002292 */  lbu        $v0, 0x1($s1)
/* 2D23C 8003CA3C 00000000 */  nop
/* 2D240 8003CA40 FFFF4224 */  addiu      $v0, $v0, -0x1
/* 2D244 8003CA44 010022A2 */  sb         $v0, 0x1($s1)
/* 2D248 8003CA48 FF004230 */  andi       $v0, $v0, 0xFF
/* 2D24C 8003CA4C 05004314 */  bne        $v0, $v1, .L8003CA64
/* 2D250 8003CA50 00000000 */   nop
/* 2D254 8003CA54 00002292 */  lbu        $v0, 0x0($s1)
/* 2D258 8003CA58 00000000 */  nop
/* 2D25C 8003CA5C FFFF4224 */  addiu      $v0, $v0, -0x1
/* 2D260 8003CA60 010022A2 */  sb         $v0, 0x1($s1)
.L8003CA64:
/* 2D264 8003CA64 03310600 */  sra        $a2, $a2, 4
/* 2D268 8003CA68 2A104602 */  slt        $v0, $s2, $a2
/* 2D26C 8003CA6C 02004010 */  beqz       $v0, .L8003CA78
/* 2D270 8003CA70 00000000 */   nop
/* 2D274 8003CA74 21304002 */  addu       $a2, $s2, $zero
.L8003CA78:
/* 2D278 8003CA78 01002592 */  lbu        $a1, 0x1($s1)
/* 2D27C 8003CA7C 5C00A78F */  lw         $a3, 0x5C($sp)
/* 2D280 8003CA80 21206002 */  addu       $a0, $s3, $zero
/* 2D284 8003CA84 1000B4AF */  sw         $s4, 0x10($sp)
/* 2D288 8003CA88 1400B5AF */  sw         $s5, 0x14($sp)
/* 2D28C 8003CA8C 00290500 */  sll        $a1, $a1, 4
/* 2D290 8003CA90 0800A524 */  addiu      $a1, $a1, 0x8
/* 2D294 8003CA94 B4EE000C */  jal        func_8003BAD0
/* 2D298 8003CA98 21282502 */   addu      $a1, $s1, $a1
/* 2D29C 8003CA9C 4000BF8F */  lw         $ra, 0x40($sp)
/* 2D2A0 8003CAA0 3C00B58F */  lw         $s5, 0x3C($sp)
/* 2D2A4 8003CAA4 3800B48F */  lw         $s4, 0x38($sp)
/* 2D2A8 8003CAA8 3400B38F */  lw         $s3, 0x34($sp)
/* 2D2AC 8003CAAC 3000B28F */  lw         $s2, 0x30($sp)
/* 2D2B0 8003CAB0 2C00B18F */  lw         $s1, 0x2C($sp)
/* 2D2B4 8003CAB4 2800B08F */  lw         $s0, 0x28($sp)
/* 2D2B8 8003CAB8 4800BD27 */  addiu      $sp, $sp, 0x48
/* 2D2BC 8003CABC 0800E003 */  jr         $ra
/* 2D2C0 8003CAC0 00000000 */   nop
.size func_8003C994, . - func_8003C994
