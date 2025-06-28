.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003BCCC
/* 2C4CC 8003BCCC 0780033C */  lui        $v1, %hi(D_800756C4)
/* 2C4D0 8003BCD0 C456638C */  lw         $v1, %lo(D_800756C4)($v1)
/* 2C4D4 8003BCD4 98FFBD27 */  addiu      $sp, $sp, -0x68
/* 2C4D8 8003BCD8 5000B2AF */  sw         $s2, 0x50($sp)
/* 2C4DC 8003BCDC 21908000 */  addu       $s2, $a0, $zero
/* 2C4E0 8003BCE0 4800B0AF */  sw         $s0, 0x48($sp)
/* 2C4E4 8003BCE4 2180A000 */  addu       $s0, $a1, $zero
/* 2C4E8 8003BCE8 5400B3AF */  sw         $s3, 0x54($sp)
/* 2C4EC 8003BCEC 2198C000 */  addu       $s3, $a2, $zero
/* 2C4F0 8003BCF0 5800B4AF */  sw         $s4, 0x58($sp)
/* 2C4F4 8003BCF4 21A0E000 */  addu       $s4, $a3, $zero
/* 2C4F8 8003BCF8 5C00B5AF */  sw         $s5, 0x5C($sp)
/* 2C4FC 8003BCFC 7800B58F */  lw         $s5, 0x78($sp)
/* 2C500 8003BD00 03000224 */  addiu      $v0, $zero, 0x3
/* 2C504 8003BD04 6400BFAF */  sw         $ra, 0x64($sp)
/* 2C508 8003BD08 6000B6AF */  sw         $s6, 0x60($sp)
/* 2C50C 8003BD0C 04006214 */  bne        $v1, $v0, .L8003BD20
/* 2C510 8003BD10 4C00B1AF */   sw        $s1, 0x4C($sp)
/* 2C514 8003BD14 43101000 */  sra        $v0, $s0, 1
/* 2C518 8003BD18 4CEF0008 */  j          .L8003BD30
/* 2C51C 8003BD1C 21800202 */   addu      $s0, $s0, $v0
.L8003BD20:
/* 2C520 8003BD20 04000224 */  addiu      $v0, $zero, 0x4
/* 2C524 8003BD24 03006214 */  bne        $v1, $v0, .L8003BD34
/* 2C528 8003BD28 44004426 */   addiu     $a0, $s2, 0x44
/* 2C52C 8003BD2C 40801000 */  sll        $s0, $s0, 1
.L8003BD30:
/* 2C530 8003BD30 44004426 */  addiu      $a0, $s2, 0x44
.L8003BD34:
/* 2C534 8003BD34 1800A527 */  addiu      $a1, $sp, 0x18
/* 2C538 8003BD38 4B5B000C */  jal        RotVec8ToMatrix
/* 2C53C 8003BD3C 21300000 */   addu      $a2, $zero, $zero
/* 2C540 8003BD40 1800A427 */  addiu      $a0, $sp, 0x18
/* 2C544 8003BD44 3800B127 */  addiu      $s1, $sp, 0x38
/* 2C548 8003BD48 21282002 */  addu       $a1, $s1, $zero
/* 2C54C 8003BD4C 21302002 */  addu       $a2, $s1, $zero
/* 2C550 8003BD50 3800B0AF */  sw         $s0, 0x38($sp)
/* 2C554 8003BD54 4000A0AF */  sw         $zero, 0x40($sp)
/* 2C558 8003BD58 125C000C */  jal        VecRotateByMatrix
/* 2C55C 8003BD5C 3C00A0AF */   sw        $zero, 0x3C($sp)
/* 2C560 8003BD60 21202002 */  addu       $a0, $s1, $zero
/* 2C564 8003BD64 21282002 */  addu       $a1, $s1, $zero
/* 2C568 8003BD68 D65D000C */  jal        VecAdd
/* 2C56C 8003BD6C 0C004626 */   addiu     $a2, $s2, 0xC
/* 2C570 8003BD70 0100A232 */  andi       $v0, $s5, 0x1
/* 2C574 8003BD74 06004010 */  beqz       $v0, .L8003BD90
/* 2C578 8003BD78 00000000 */   nop
/* 2C57C 8003BD7C 4000A28F */  lw         $v0, 0x40($sp)
/* 2C580 8003BD80 00000000 */  nop
/* 2C584 8003BD84 2C014224 */  addiu      $v0, $v0, 0x12C
/* 2C588 8003BD88 21105400 */  addu       $v0, $v0, $s4
/* 2C58C 8003BD8C 4000A2AF */  sw         $v0, 0x40($sp)
.L8003BD90:
/* 2C590 8003BD90 14006012 */  beqz       $s3, .L8003BDE4
/* 2C594 8003BD94 0200A232 */   andi      $v0, $s5, 0x2
/* 2C598 8003BD98 0B004014 */  bnez       $v0, .L8003BDC8
/* 2C59C 8003BD9C 21202002 */   addu      $a0, $s1, $zero
/* 2C5A0 8003BDA0 21286002 */  addu       $a1, $s3, $zero
/* 2C5A4 8003BDA4 21300000 */  addu       $a2, $zero, $zero
/* 2C5A8 8003BDA8 21380000 */  addu       $a3, $zero, $zero
/* 2C5AC 8003BDAC 1000B2AF */  sw         $s2, 0x10($sp)
/* 2C5B0 8003BDB0 F238010C */  jal        func_8004E3C8
/* 2C5B4 8003BDB4 1400A0AF */   sw        $zero, 0x14($sp)
/* 2C5B8 8003BDB8 0A004010 */  beqz       $v0, .L8003BDE4
/* 2C5BC 8003BDBC 01000224 */   addiu     $v0, $zero, 0x1
/* 2C5C0 8003BDC0 ABEF0008 */  j          .L8003BEAC
/* 2C5C4 8003BDC4 00000000 */   nop
.L8003BDC8:
/* 2C5C8 8003BDC8 21286002 */  addu       $a1, $s3, $zero
/* 2C5CC 8003BDCC 21300000 */  addu       $a2, $zero, $zero
/* 2C5D0 8003BDD0 21380000 */  addu       $a3, $zero, $zero
/* 2C5D4 8003BDD4 03000224 */  addiu      $v0, $zero, 0x3
/* 2C5D8 8003BDD8 1000B2AF */  sw         $s2, 0x10($sp)
/* 2C5DC 8003BDDC F238010C */  jal        func_8004E3C8
/* 2C5E0 8003BDE0 1400A2AF */   sw        $v0, 0x14($sp)
.L8003BDE4:
/* 2C5E4 8003BDE4 06008012 */  beqz       $s4, .L8003BE00
/* 2C5E8 8003BDE8 3800A427 */   addiu     $a0, $sp, 0x38
/* 2C5EC 8003BDEC 21288002 */  addu       $a1, $s4, $zero
/* 2C5F0 8003BDF0 932F010C */  jal        func_8004BE4C
/* 2C5F4 8003BDF4 21308002 */   addu      $a2, $s4, $zero
/* 2C5F8 8003BDF8 2C004014 */  bnez       $v0, .L8003BEAC
/* 2C5FC 8003BDFC 02000224 */   addiu     $v0, $zero, 0x2
.L8003BE00:
/* 2C600 8003BE00 0100A232 */  andi       $v0, $s5, 0x1
/* 2C604 8003BE04 07004010 */  beqz       $v0, .L8003BE24
/* 2C608 8003BE08 1400A232 */   andi      $v0, $s5, 0x14
/* 2C60C 8003BE0C 4000A28F */  lw         $v0, 0x40($sp)
/* 2C610 8003BE10 00000000 */  nop
/* 2C614 8003BE14 D4FE4224 */  addiu      $v0, $v0, -0x12C
/* 2C618 8003BE18 23105400 */  subu       $v0, $v0, $s4
/* 2C61C 8003BE1C 4000A2AF */  sw         $v0, 0x40($sp)
/* 2C620 8003BE20 1400A232 */  andi       $v0, $s5, 0x14
.L8003BE24:
/* 2C624 8003BE24 07004010 */  beqz       $v0, .L8003BE44
/* 2C628 8003BE28 3800A427 */   addiu     $a0, $sp, 0x38
/* 2C62C 8003BE2C 4000A28F */  lw         $v0, 0x40($sp)
/* 2C630 8003BE30 00080524 */  addiu      $a1, $zero, 0x800
/* 2C634 8003BE34 00044224 */  addiu      $v0, $v0, 0x400
/* 2C638 8003BE38 7B35010C */  jal        func_8004D5EC
/* 2C63C 8003BE3C 4000A2AF */   sw        $v0, 0x40($sp)
/* 2C640 8003BE40 21B04000 */  addu       $s6, $v0, $zero
.L8003BE44:
/* 2C644 8003BE44 1000A232 */  andi       $v0, $s5, 0x10
/* 2C648 8003BE48 10004010 */  beqz       $v0, .L8003BE8C
/* 2C64C 8003BE4C 0C004426 */   addiu     $a0, $s2, 0xC
/* 2C650 8003BE50 1400438E */  lw         $v1, 0x14($s2)
/* 2C654 8003BE54 00000000 */  nop
/* 2C658 8003BE58 2310C302 */  subu       $v0, $s6, $v1
/* 2C65C 8003BE5C 05004018 */  blez       $v0, .L8003BE74
/* 2C660 8003BE60 C9004228 */   slti      $v0, $v0, 0xC9
/* 2C664 8003BE64 11004010 */  beqz       $v0, .L8003BEAC
/* 2C668 8003BE68 02000224 */   addiu     $v0, $zero, 0x2
/* 2C66C 8003BE6C A3EF0008 */  j          .L8003BE8C
/* 2C670 8003BE70 00000000 */   nop
.L8003BE74:
/* 2C674 8003BE74 23107600 */  subu       $v0, $v1, $s6
/* 2C678 8003BE78 C9004228 */  slti       $v0, $v0, 0xC9
/* 2C67C 8003BE7C 03004014 */  bnez       $v0, .L8003BE8C
/* 2C680 8003BE80 0C004426 */   addiu     $a0, $s2, 0xC
/* 2C684 8003BE84 ABEF0008 */  j          .L8003BEAC
/* 2C688 8003BE88 02000224 */   addiu     $v0, $zero, 0x2
.L8003BE8C:
/* 2C68C 8003BE8C C05D000C */  jal        VecCopy
/* 2C690 8003BE90 3800A527 */   addiu     $a1, $sp, 0x38
/* 2C694 8003BE94 F44C010C */  jal        func_800533D0
/* 2C698 8003BE98 21204002 */   addu      $a0, $s2, $zero
/* 2C69C 8003BE9C 21204002 */  addu       $a0, $s2, $zero
/* 2C6A0 8003BEA0 794A010C */  jal        func_800529E4
/* 2C6A4 8003BEA4 02000524 */   addiu     $a1, $zero, 0x2
/* 2C6A8 8003BEA8 21100000 */  addu       $v0, $zero, $zero
.L8003BEAC:
/* 2C6AC 8003BEAC 6400BF8F */  lw         $ra, 0x64($sp)
/* 2C6B0 8003BEB0 6000B68F */  lw         $s6, 0x60($sp)
/* 2C6B4 8003BEB4 5C00B58F */  lw         $s5, 0x5C($sp)
/* 2C6B8 8003BEB8 5800B48F */  lw         $s4, 0x58($sp)
/* 2C6BC 8003BEBC 5400B38F */  lw         $s3, 0x54($sp)
/* 2C6C0 8003BEC0 5000B28F */  lw         $s2, 0x50($sp)
/* 2C6C4 8003BEC4 4C00B18F */  lw         $s1, 0x4C($sp)
/* 2C6C8 8003BEC8 4800B08F */  lw         $s0, 0x48($sp)
/* 2C6CC 8003BECC 6800BD27 */  addiu      $sp, $sp, 0x68
/* 2C6D0 8003BED0 0800E003 */  jr         $ra
/* 2C6D4 8003BED4 00000000 */   nop
.size func_8003BCCC, . - func_8003BCCC
