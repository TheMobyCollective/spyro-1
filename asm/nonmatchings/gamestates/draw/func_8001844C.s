.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8001844C
/* 8C4C 8001844C D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 8C50 80018450 21188000 */  addu       $v1, $a0, $zero
/* 8C54 80018454 2140A000 */  addu       $t0, $a1, $zero
/* 8C58 80018458 1400B1AF */  sw         $s1, 0x14($sp)
/* 8C5C 8001845C 2188C000 */  addu       $s1, $a2, $zero
/* 8C60 80018460 1C00B3AF */  sw         $s3, 0x1C($sp)
/* 8C64 80018464 2198E000 */  addu       $s3, $a3, $zero
/* 8C68 80018468 00FF6424 */  addiu      $a0, $v1, -0x100
/* 8C6C 8001846C 88FF0525 */  addiu      $a1, $t0, -0x78
/* 8C70 80018470 1000B0AF */  sw         $s0, 0x10($sp)
/* 8C74 80018474 0780103C */  lui        $s0, %hi(D_800757B0)
/* 8C78 80018478 B057108E */  lw         $s0, %lo(D_800757B0)($s0)
/* 8C7C 8001847C 0004023C */  lui        $v0, (0x4000000 >> 16)
/* 8C80 80018480 2000BFAF */  sw         $ra, 0x20($sp)
/* 8C84 80018484 1800B2AF */  sw         $s2, 0x18($sp)
/* 8C88 80018488 000002AE */  sw         $v0, 0x0($s0)
/* 8C8C 8001848C 50000224 */  addiu      $v0, $zero, 0x50
/* 8C90 80018490 070002A2 */  sb         $v0, 0x7($s0)
/* 8C94 80018494 080003A6 */  sh         $v1, 0x8($s0)
/* 8C98 80018498 0A0008A6 */  sh         $t0, 0xA($s0)
/* 8C9C 8001849C 100011A6 */  sh         $s1, 0x10($s0)
/* 8CA0 800184A0 6B5A000C */  jal        Atan2Fast
/* 8CA4 800184A4 120013A6 */   sh        $s3, 0x12($s0)
/* 8CA8 800184A8 0780123C */  lui        $s2, %hi(D_800770F4)
/* 8CAC 800184AC F4705226 */  addiu      $s2, $s2, %lo(D_800770F4)
/* 8CB0 800184B0 0000458E */  lw         $a1, 0x0($s2)
/* 8CB4 800184B4 425E000C */  jal        func_80017908
/* 8CB8 800184B8 21204000 */   addu      $a0, $v0, $zero
/* 8CBC 800184BC 00FF2426 */  addiu      $a0, $s1, -0x100
/* 8CC0 800184C0 88FF6526 */  addiu      $a1, $s3, -0x78
/* 8CC4 800184C4 80001124 */  addiu      $s1, $zero, 0x80
/* 8CC8 800184C8 23102202 */  subu       $v0, $s1, $v0
/* 8CCC 800184CC 60004324 */  addiu      $v1, $v0, 0x60
/* 8CD0 800184D0 040003A2 */  sb         $v1, 0x4($s0)
/* 8CD4 800184D4 050003A2 */  sb         $v1, 0x5($s0)
/* 8CD8 800184D8 6B5A000C */  jal        Atan2Fast
/* 8CDC 800184DC 060002A2 */   sb        $v0, 0x6($s0)
/* 8CE0 800184E0 0000458E */  lw         $a1, 0x0($s2)
/* 8CE4 800184E4 425E000C */  jal        func_80017908
/* 8CE8 800184E8 21204000 */   addu      $a0, $v0, $zero
/* 8CEC 800184EC 21200002 */  addu       $a0, $s0, $zero
/* 8CF0 800184F0 23882202 */  subu       $s1, $s1, $v0
/* 8CF4 800184F4 60002226 */  addiu      $v0, $s1, 0x60
/* 8CF8 800184F8 0C0002A2 */  sb         $v0, 0xC($s0)
/* 8CFC 800184FC 0D0002A2 */  sb         $v0, 0xD($s0)
/* 8D00 80018500 375A000C */  jal        func_800168DC
/* 8D04 80018504 0E0011A2 */   sb        $s1, 0xE($s0)
/* 8D08 80018508 14001026 */  addiu      $s0, $s0, 0x14
/* 8D0C 8001850C 0780013C */  lui        $at, %hi(D_800757B0)
/* 8D10 80018510 B05730AC */  sw         $s0, %lo(D_800757B0)($at)
/* 8D14 80018514 2000BF8F */  lw         $ra, 0x20($sp)
/* 8D18 80018518 1C00B38F */  lw         $s3, 0x1C($sp)
/* 8D1C 8001851C 1800B28F */  lw         $s2, 0x18($sp)
/* 8D20 80018520 1400B18F */  lw         $s1, 0x14($sp)
/* 8D24 80018524 1000B08F */  lw         $s0, 0x10($sp)
/* 8D28 80018528 2800BD27 */  addiu      $sp, $sp, 0x28
/* 8D2C 8001852C 0800E003 */  jr         $ra
/* 8D30 80018530 00000000 */   nop
.size func_8001844C, . - func_8001844C
