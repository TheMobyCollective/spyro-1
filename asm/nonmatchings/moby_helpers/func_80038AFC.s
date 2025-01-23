.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80038AFC
/* 292FC 80038AFC C8FFBD27 */  addiu      $sp, $sp, -0x38
/* 29300 80038B00 2000B2AF */  sw         $s2, 0x20($sp)
/* 29304 80038B04 21908000 */  addu       $s2, $a0, $zero
/* 29308 80038B08 2C00B5AF */  sw         $s5, 0x2C($sp)
/* 2930C 80038B0C 21A8A000 */  addu       $s5, $a1, $zero
/* 29310 80038B10 2400B3AF */  sw         $s3, 0x24($sp)
/* 29314 80038B14 FF00133C */  lui        $s3, (0xFFFFFF >> 16)
/* 29318 80038B18 FFFF7336 */  ori        $s3, $s3, (0xFFFFFF & 0xFFFF)
/* 2931C 80038B1C 3000BFAF */  sw         $ra, 0x30($sp)
/* 29320 80038B20 2800B4AF */  sw         $s4, 0x28($sp)
/* 29324 80038B24 1C00B1AF */  sw         $s1, 0x1C($sp)
/* 29328 80038B28 1800B0AF */  sw         $s0, 0x18($sp)
/* 2932C 80038B2C 00004292 */  lbu        $v0, 0x0($s2)
/* 29330 80038B30 00000000 */  nop
/* 29334 80038B34 11004018 */  blez       $v0, .L80038B7C
/* 29338 80038B38 21800000 */   addu      $s0, $zero, $zero
/* 2933C 80038B3C 08001124 */  addiu      $s1, $zero, 0x8
.L80038B40:
/* 29340 80038B40 0880043C */  lui        $a0, %hi(g_Spyro)
/* 29344 80038B44 588A8424 */  addiu      $a0, $a0, %lo(g_Spyro)
/* 29348 80038B48 645E000C */  jal        func_80017990
/* 2934C 80038B4C 21285102 */   addu      $a1, $s2, $s1
/* 29350 80038B50 21184000 */  addu       $v1, $v0, $zero
/* 29354 80038B54 2A107300 */  slt        $v0, $v1, $s3
/* 29358 80038B58 03004010 */  beqz       $v0, .L80038B68
/* 2935C 80038B5C 00000000 */   nop
/* 29360 80038B60 21986000 */  addu       $s3, $v1, $zero
/* 29364 80038B64 21A00002 */  addu       $s4, $s0, $zero
.L80038B68:
/* 29368 80038B68 00004292 */  lbu        $v0, 0x0($s2)
/* 2936C 80038B6C 01001026 */  addiu      $s0, $s0, 0x1
/* 29370 80038B70 2A100202 */  slt        $v0, $s0, $v0
/* 29374 80038B74 F2FF4014 */  bnez       $v0, .L80038B40
/* 29378 80038B78 10003126 */   addiu     $s1, $s1, 0x10
.L80038B7C:
/* 2937C 80038B7C 0200A012 */  beqz       $s5, .L80038B88
/* 29380 80038B80 21106002 */   addu      $v0, $s3, $zero
/* 29384 80038B84 0000B4AE */  sw         $s4, 0x0($s5)
.L80038B88:
/* 29388 80038B88 3000BF8F */  lw         $ra, 0x30($sp)
/* 2938C 80038B8C 2C00B58F */  lw         $s5, 0x2C($sp)
/* 29390 80038B90 2800B48F */  lw         $s4, 0x28($sp)
/* 29394 80038B94 2400B38F */  lw         $s3, 0x24($sp)
/* 29398 80038B98 2000B28F */  lw         $s2, 0x20($sp)
/* 2939C 80038B9C 1C00B18F */  lw         $s1, 0x1C($sp)
/* 293A0 80038BA0 1800B08F */  lw         $s0, 0x18($sp)
/* 293A4 80038BA4 3800BD27 */  addiu      $sp, $sp, 0x38
/* 293A8 80038BA8 0800E003 */  jr         $ra
/* 293AC 80038BAC 00000000 */   nop
.size func_80038AFC, . - func_80038AFC
