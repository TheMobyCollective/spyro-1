.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003D52C
/* 2DD2C 8003D52C C8FFBD27 */  addiu      $sp, $sp, -0x38
/* 2DD30 8003D530 2400B1AF */  sw         $s1, 0x24($sp)
/* 2DD34 8003D534 21888000 */  addu       $s1, $a0, $zero
/* 2DD38 8003D538 2800B2AF */  sw         $s2, 0x28($sp)
/* 2DD3C 8003D53C 0880123C */  lui        $s2, %hi(g_Spyro + 0x124)
/* 2DD40 8003D540 7C8B5226 */  addiu      $s2, $s2, %lo(g_Spyro + 0x124)
/* 2DD44 8003D544 3400BFAF */  sw         $ra, 0x34($sp)
/* 2DD48 8003D548 3000B4AF */  sw         $s4, 0x30($sp)
/* 2DD4C 8003D54C 2C00B3AF */  sw         $s3, 0x2C($sp)
/* 2DD50 8003D550 2000B0AF */  sw         $s0, 0x20($sp)
/* 2DD54 8003D554 0000448E */  lw         $a0, 0x0($s2)
/* 2DD58 8003D558 2C5B000C */  jal        func_80016CB0
/* 2DD5C 8003D55C 00000000 */   nop
/* 2DD60 8003D560 0000448E */  lw         $a0, 0x0($s2)
/* 2DD64 8003D564 165B000C */  jal        func_80016C58
/* 2DD68 8003D568 21A04000 */   addu      $s4, $v0, $zero
/* 2DD6C 8003D56C FCFF448E */  lw         $a0, -0x4($s2)
/* 2DD70 8003D570 21984000 */  addu       $s3, $v0, $zero
/* 2DD74 8003D574 23200400 */  negu       $a0, $a0
/* 2DD78 8003D578 2C5B000C */  jal        func_80016CB0
/* 2DD7C 8003D57C FF0F8430 */   andi      $a0, $a0, 0xFFF
/* 2DD80 8003D580 21804000 */  addu       $s0, $v0, $zero
/* 2DD84 8003D584 02000016 */  bnez       $s0, .L8003D590
/* 2DD88 8003D588 00000000 */   nop
/* 2DD8C 8003D58C 01001024 */  addiu      $s0, $zero, 0x1
.L8003D590:
/* 2DD90 8003D590 FCFF448E */  lw         $a0, -0x4($s2)
/* 2DD94 8003D594 00000000 */  nop
/* 2DD98 8003D598 23200400 */  negu       $a0, $a0
/* 2DD9C 8003D59C 165B000C */  jal        func_80016C58
/* 2DDA0 8003D5A0 FF0F8430 */   andi      $a0, $a0, 0xFFF
/* 2DDA4 8003D5A4 18002202 */  mult       $s1, $v0
/* 2DDA8 8003D5A8 12100000 */  mflo       $v0
/* 2DDAC 8003D5AC 00000000 */  nop
/* 2DDB0 8003D5B0 00000000 */  nop
/* 2DDB4 8003D5B4 1A005000 */  div        $zero, $v0, $s0
/* 2DDB8 8003D5B8 02000016 */  bnez       $s0, .L8003D5C4
/* 2DDBC 8003D5BC 00000000 */   nop
/* 2DDC0 8003D5C0 0D000700 */  break      7
.L8003D5C4:
/* 2DDC4 8003D5C4 FFFF0124 */  addiu      $at, $zero, -0x1
/* 2DDC8 8003D5C8 04000116 */  bne        $s0, $at, .L8003D5DC
/* 2DDCC 8003D5CC 0080013C */   lui       $at, (0x80000000 >> 16)
/* 2DDD0 8003D5D0 02004114 */  bne        $v0, $at, .L8003D5DC
/* 2DDD4 8003D5D4 00000000 */   nop
/* 2DDD8 8003D5D8 0D000600 */  break      6
.L8003D5DC:
/* 2DDDC 8003D5DC 12280000 */  mflo       $a1
/* 2DDE0 8003D5E0 00000000 */  nop
/* 2DDE4 8003D5E4 00000000 */  nop
/* 2DDE8 8003D5E8 18003402 */  mult       $s1, $s4
/* 2DDEC 8003D5EC 12100000 */  mflo       $v0
/* 2DDF0 8003D5F0 00000000 */  nop
/* 2DDF4 8003D5F4 00000000 */  nop
/* 2DDF8 8003D5F8 1A005000 */  div        $zero, $v0, $s0
/* 2DDFC 8003D5FC 02000016 */  bnez       $s0, .L8003D608
/* 2DE00 8003D600 00000000 */   nop
/* 2DE04 8003D604 0D000700 */  break      7
.L8003D608:
/* 2DE08 8003D608 FFFF0124 */  addiu      $at, $zero, -0x1
/* 2DE0C 8003D60C 04000116 */  bne        $s0, $at, .L8003D620
/* 2DE10 8003D610 0080013C */   lui       $at, (0x80000000 >> 16)
/* 2DE14 8003D614 02004114 */  bne        $v0, $at, .L8003D620
/* 2DE18 8003D618 00000000 */   nop
/* 2DE1C 8003D61C 0D000600 */  break      6
.L8003D620:
/* 2DE20 8003D620 12200000 */  mflo       $a0
/* 2DE24 8003D624 00000000 */  nop
/* 2DE28 8003D628 00000000 */  nop
/* 2DE2C 8003D62C 18003302 */  mult       $s1, $s3
/* 2DE30 8003D630 FCFF438E */  lw         $v1, -0x4($s2)
/* 2DE34 8003D634 12380000 */  mflo       $a3
/* 2DE38 8003D638 03130700 */  sra        $v0, $a3, 12
/* 2DE3C 8003D63C 21186200 */  addu       $v1, $v1, $v0
/* 2DE40 8003D640 FF0F6330 */  andi       $v1, $v1, 0xFFF
/* 2DE44 8003D644 1400A2AF */  sw         $v0, 0x14($sp)
/* 2DE48 8003D648 1800B400 */  mult       $a1, $s4
/* 2DE4C 8003D64C FCFF43AE */  sw         $v1, -0x4($s2)
/* 2DE50 8003D650 0880023C */  lui        $v0, %hi(g_Spyro + 0x11C)
/* 2DE54 8003D654 748B428C */  lw         $v0, %lo(g_Spyro + 0x11C)($v0)
/* 2DE58 8003D658 03190300 */  sra        $v1, $v1, 4
/* 2DE5C 8003D65C 0880013C */  lui        $at, %hi(g_Spyro + 0xD)
/* 2DE60 8003D660 658A23A0 */  sb         $v1, %lo(g_Spyro + 0xD)($at)
/* 2DE64 8003D664 21104400 */  addu       $v0, $v0, $a0
/* 2DE68 8003D668 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 2DE6C 8003D66C 0880013C */  lui        $at, %hi(g_Spyro + 0x11C)
/* 2DE70 8003D670 748B22AC */  sw         $v0, %lo(g_Spyro + 0x11C)($at)
/* 2DE74 8003D674 03110200 */  sra        $v0, $v0, 4
/* 2DE78 8003D678 1800A4AF */  sw         $a0, 0x18($sp)
/* 2DE7C 8003D67C 0880013C */  lui        $at, %hi(g_Spyro + 0xE)
/* 2DE80 8003D680 668A22A0 */  sb         $v0, %lo(g_Spyro + 0xE)($at)
/* 2DE84 8003D684 0000428E */  lw         $v0, 0x0($s2)
/* 2DE88 8003D688 12280000 */  mflo       $a1
/* 2DE8C 8003D68C 031B0500 */  sra        $v1, $a1, 12
/* 2DE90 8003D690 1000A3AF */  sw         $v1, 0x10($sp)
/* 2DE94 8003D694 21104300 */  addu       $v0, $v0, $v1
/* 2DE98 8003D698 FF0F4230 */  andi       $v0, $v0, 0xFFF
/* 2DE9C 8003D69C 000042AE */  sw         $v0, 0x0($s2)
/* 2DEA0 8003D6A0 03110200 */  sra        $v0, $v0, 4
/* 2DEA4 8003D6A4 0880013C */  lui        $at, %hi(g_Spyro + 0xC)
/* 2DEA8 8003D6A8 648A22A0 */  sb         $v0, %lo(g_Spyro + 0xC)($at)
/* 2DEAC 8003D6AC 3400BF8F */  lw         $ra, 0x34($sp)
/* 2DEB0 8003D6B0 3000B48F */  lw         $s4, 0x30($sp)
/* 2DEB4 8003D6B4 2C00B38F */  lw         $s3, 0x2C($sp)
/* 2DEB8 8003D6B8 2800B28F */  lw         $s2, 0x28($sp)
/* 2DEBC 8003D6BC 2400B18F */  lw         $s1, 0x24($sp)
/* 2DEC0 8003D6C0 2000B08F */  lw         $s0, 0x20($sp)
/* 2DEC4 8003D6C4 3800BD27 */  addiu      $sp, $sp, 0x38
/* 2DEC8 8003D6C8 0800E003 */  jr         $ra
/* 2DECC 8003D6CC 00000000 */   nop
.size func_8003D52C, . - func_8003D52C
