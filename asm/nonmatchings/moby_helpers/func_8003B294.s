.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003B294
/* 2BA94 8003B294 0780023C */  lui        $v0, %hi(g_MobyPodCount)
/* 2BA98 8003B298 B457428C */  lw         $v0, %lo(g_MobyPodCount)($v0)
/* 2BA9C 8003B29C C8FFBD27 */  addiu      $sp, $sp, -0x38
/* 2BAA0 8003B2A0 2000B4AF */  sw         $s4, 0x20($sp)
/* 2BAA4 8003B2A4 4800B48F */  lw         $s4, 0x48($sp)
/* 2BAA8 8003B2A8 1C00B3AF */  sw         $s3, 0x1C($sp)
/* 2BAAC 8003B2AC 4C00B38F */  lw         $s3, 0x4C($sp)
/* 2BAB0 8003B2B0 2C00B7AF */  sw         $s7, 0x2C($sp)
/* 2BAB4 8003B2B4 5000B78F */  lw         $s7, 0x50($sp)
/* 2BAB8 8003B2B8 1400B1AF */  sw         $s1, 0x14($sp)
/* 2BABC 8003B2BC 21888000 */  addu       $s1, $a0, $zero
/* 2BAC0 8003B2C0 2400B5AF */  sw         $s5, 0x24($sp)
/* 2BAC4 8003B2C4 21A8C000 */  addu       $s5, $a2, $zero
/* 2BAC8 8003B2C8 2800B6AF */  sw         $s6, 0x28($sp)
/* 2BACC 8003B2CC 21B0E000 */  addu       $s6, $a3, $zero
/* 2BAD0 8003B2D0 3000BFAF */  sw         $ra, 0x30($sp)
/* 2BAD4 8003B2D4 1800B2AF */  sw         $s2, 0x18($sp)
/* 2BAD8 8003B2D8 2A10A200 */  slt        $v0, $a1, $v0
/* 2BADC 8003B2DC 5B004010 */  beqz       $v0, .L8003B44C
/* 2BAE0 8003B2E0 1000B0AF */   sw        $s0, 0x10($sp)
/* 2BAE4 8003B2E4 0780033C */  lui        $v1, %hi(g_MobyPods)
/* 2BAE8 8003B2E8 F857638C */  lw         $v1, %lo(g_MobyPods)($v1)
/* 2BAEC 8003B2EC 80100500 */  sll        $v0, $a1, 2
/* 2BAF0 8003B2F0 21104300 */  addu       $v0, $v0, $v1
/* 2BAF4 8003B2F4 0000528C */  lw         $s2, 0x0($v0)
.L8003B2F8:
/* 2BAF8 8003B2F8 00000000 */  nop
/* 2BAFC 8003B2FC 00004396 */  lhu        $v1, 0x0($s2)
/* 2BB00 8003B300 00000000 */  nop
/* 2BB04 8003B304 FF7F6330 */  andi       $v1, $v1, 0x7FFF
/* 2BB08 8003B308 40100300 */  sll        $v0, $v1, 1
/* 2BB0C 8003B30C 21104300 */  addu       $v0, $v0, $v1
/* 2BB10 8003B310 80100200 */  sll        $v0, $v0, 2
/* 2BB14 8003B314 23104300 */  subu       $v0, $v0, $v1
/* 2BB18 8003B318 0780033C */  lui        $v1, %hi(D_80075828)
/* 2BB1C 8003B31C 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 2BB20 8003B320 C0100200 */  sll        $v0, $v0, 3
/* 2BB24 8003B324 21806200 */  addu       $s0, $v1, $v0
/* 2BB28 8003B328 48000292 */  lbu        $v0, 0x48($s0)
/* 2BB2C 8003B32C 00000000 */  nop
/* 2BB30 8003B330 8000422C */  sltiu      $v0, $v0, 0x80
/* 2BB34 8003B334 41004010 */  beqz       $v0, .L8003B43C
/* 2BB38 8003B338 00000000 */   nop
/* 2BB3C 8003B33C 0C00248E */  lw         $a0, 0xC($s1)
/* 2BB40 8003B340 0C00038E */  lw         $v1, 0xC($s0)
/* 2BB44 8003B344 00000000 */  nop
/* 2BB48 8003B348 23108300 */  subu       $v0, $a0, $v1
/* 2BB4C 8003B34C 05004018 */  blez       $v0, .L8003B364
/* 2BB50 8003B350 2A105300 */   slt       $v0, $v0, $s3
/* 2BB54 8003B354 39004010 */  beqz       $v0, .L8003B43C
/* 2BB58 8003B358 00000000 */   nop
/* 2BB5C 8003B35C DDEC0008 */  j          .L8003B374
/* 2BB60 8003B360 00000000 */   nop
.L8003B364:
/* 2BB64 8003B364 23106400 */  subu       $v0, $v1, $a0
/* 2BB68 8003B368 2A105300 */  slt        $v0, $v0, $s3
/* 2BB6C 8003B36C 33004010 */  beqz       $v0, .L8003B43C
/* 2BB70 8003B370 00000000 */   nop
.L8003B374:
/* 2BB74 8003B374 1000248E */  lw         $a0, 0x10($s1)
/* 2BB78 8003B378 1000038E */  lw         $v1, 0x10($s0)
/* 2BB7C 8003B37C 00000000 */  nop
/* 2BB80 8003B380 23108300 */  subu       $v0, $a0, $v1
/* 2BB84 8003B384 05004018 */  blez       $v0, .L8003B39C
/* 2BB88 8003B388 2A105300 */   slt       $v0, $v0, $s3
/* 2BB8C 8003B38C 07004014 */  bnez       $v0, .L8003B3AC
/* 2BB90 8003B390 0C002426 */   addiu     $a0, $s1, 0xC
/* 2BB94 8003B394 0FED0008 */  j          .L8003B43C
/* 2BB98 8003B398 00000000 */   nop
.L8003B39C:
/* 2BB9C 8003B39C 23106400 */  subu       $v0, $v1, $a0
/* 2BBA0 8003B3A0 2A105300 */  slt        $v0, $v0, $s3
/* 2BBA4 8003B3A4 25004010 */  beqz       $v0, .L8003B43C
/* 2BBA8 8003B3A8 0C002426 */   addiu     $a0, $s1, 0xC
.L8003B3AC:
/* 2BBAC 8003B3AC 645E000C */  jal        OctDistance
/* 2BBB0 8003B3B0 0C000526 */   addiu     $a1, $s0, 0xC
/* 2BBB4 8003B3B4 2A105600 */  slt        $v0, $v0, $s6
/* 2BBB8 8003B3B8 20004010 */  beqz       $v0, .L8003B43C
/* 2BBBC 8003B3BC 00000000 */   nop
/* 2BBC0 8003B3C0 1400048E */  lw         $a0, 0x14($s0)
/* 2BBC4 8003B3C4 1400238E */  lw         $v1, 0x14($s1)
/* 2BBC8 8003B3C8 00000000 */  nop
/* 2BBCC 8003B3CC 23108300 */  subu       $v0, $a0, $v1
/* 2BBD0 8003B3D0 05004018 */  blez       $v0, .L8003B3E8
/* 2BBD4 8003B3D4 2A105400 */   slt       $v0, $v0, $s4
/* 2BBD8 8003B3D8 07004014 */  bnez       $v0, .L8003B3F8
/* 2BBDC 8003B3DC 21300000 */   addu      $a2, $zero, $zero
/* 2BBE0 8003B3E0 0FED0008 */  j          .L8003B43C
/* 2BBE4 8003B3E4 00000000 */   nop
.L8003B3E8:
/* 2BBE8 8003B3E8 23106400 */  subu       $v0, $v1, $a0
/* 2BBEC 8003B3EC 2A105400 */  slt        $v0, $v0, $s4
/* 2BBF0 8003B3F0 12004010 */  beqz       $v0, .L8003B43C
/* 2BBF4 8003B3F4 21300000 */   addu      $a2, $zero, $zero
.L8003B3F8:
/* 2BBF8 8003B3F8 0C00038E */  lw         $v1, 0xC($s0)
/* 2BBFC 8003B3FC 0C00248E */  lw         $a0, 0xC($s1)
/* 2BC00 8003B400 1000028E */  lw         $v0, 0x10($s0)
/* 2BC04 8003B404 1000258E */  lw         $a1, 0x10($s1)
/* 2BC08 8003B408 23206400 */  subu       $a0, $v1, $a0
/* 2BC0C 8003B40C AD5A000C */  jal        func_80016AB4
/* 2BC10 8003B410 23284500 */   subu      $a1, $v0, $a1
/* 2BC14 8003B414 46002492 */  lbu        $a0, 0x46($s1)
/* 2BC18 8003B418 425E000C */  jal        func_80017908
/* 2BC1C 8003B41C 21284000 */   addu      $a1, $v0, $zero
/* 2BC20 8003B420 2A105700 */  slt        $v0, $v0, $s7
/* 2BC24 8003B424 05004010 */  beqz       $v0, .L8003B43C
/* 2BC28 8003B428 00000000 */   nop
/* 2BC2C 8003B42C 1800028E */  lw         $v0, 0x18($s0)
/* 2BC30 8003B430 00000000 */  nop
/* 2BC34 8003B434 25105500 */  or         $v0, $v0, $s5
/* 2BC38 8003B438 180002AE */  sw         $v0, 0x18($s0)
.L8003B43C:
/* 2BC3C 8003B43C 00004286 */  lh         $v0, 0x0($s2)
/* 2BC40 8003B440 00000000 */  nop
/* 2BC44 8003B444 ACFF4104 */  bgez       $v0, .L8003B2F8
/* 2BC48 8003B448 02005226 */   addiu     $s2, $s2, 0x2
.L8003B44C:
/* 2BC4C 8003B44C 3000BF8F */  lw         $ra, 0x30($sp)
/* 2BC50 8003B450 2C00B78F */  lw         $s7, 0x2C($sp)
/* 2BC54 8003B454 2800B68F */  lw         $s6, 0x28($sp)
/* 2BC58 8003B458 2400B58F */  lw         $s5, 0x24($sp)
/* 2BC5C 8003B45C 2000B48F */  lw         $s4, 0x20($sp)
/* 2BC60 8003B460 1C00B38F */  lw         $s3, 0x1C($sp)
/* 2BC64 8003B464 1800B28F */  lw         $s2, 0x18($sp)
/* 2BC68 8003B468 1400B18F */  lw         $s1, 0x14($sp)
/* 2BC6C 8003B46C 1000B08F */  lw         $s0, 0x10($sp)
/* 2BC70 8003B470 3800BD27 */  addiu      $sp, $sp, 0x38
/* 2BC74 8003B474 0800E003 */  jr         $ra
/* 2BC78 8003B478 00000000 */   nop
.size func_8003B294, . - func_8003B294
