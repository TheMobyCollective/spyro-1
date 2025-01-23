.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003AAEC
/* 2B2EC 8003AAEC D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 2B2F0 8003AAF0 1400B1AF */  sw         $s1, 0x14($sp)
/* 2B2F4 8003AAF4 21888000 */  addu       $s1, $a0, $zero
/* 2B2F8 8003AAF8 1C00B3AF */  sw         $s3, 0x1C($sp)
/* 2B2FC 8003AAFC 2198A000 */  addu       $s3, $a1, $zero
/* 2B300 8003AB00 2000BFAF */  sw         $ra, 0x20($sp)
/* 2B304 8003AB04 1800B2AF */  sw         $s2, 0x18($sp)
/* 2B308 8003AB08 0B62010C */  jal        func_8005882C
/* 2B30C 8003AB0C 1000B0AF */   sw        $s0, 0x10($sp)
/* 2B310 8003AB10 21904000 */  addu       $s2, $v0, $zero
/* 2B314 8003AB14 21004006 */  bltz       $s2, .L8003AB9C
/* 2B318 8003AB18 21202002 */   addu      $a0, $s1, $zero
/* 2B31C 8003AB1C 04000524 */  addiu      $a1, $zero, 0x4
/* 2B320 8003AB20 40801200 */  sll        $s0, $s2, 1
/* 2B324 8003AB24 21801202 */  addu       $s0, $s0, $s2
/* 2B328 8003AB28 C0801000 */  sll        $s0, $s0, 3
/* 2B32C 8003AB2C 0780023C */  lui        $v0, %hi(D_80077108)
/* 2B330 8003AB30 08714224 */  addiu      $v0, $v0, %lo(D_80077108)
/* 2B334 8003AB34 21800202 */  addu       $s0, $s0, $v0
/* 2B338 8003AB38 FF000224 */  addiu      $v0, $zero, 0xFF
/* 2B33C 8003AB3C 100002A2 */  sb         $v0, 0x10($s0)
/* 2B340 8003AB40 110002A2 */  sb         $v0, 0x11($s0)
/* 2B344 8003AB44 794A010C */  jal        func_800529E4
/* 2B348 8003AB48 120002A2 */   sb        $v0, 0x12($s0)
/* 2B34C 8003AB4C 20002426 */  addiu      $a0, $s1, 0x20
/* 2B350 8003AB50 21286002 */  addu       $a1, $s3, $zero
/* 2B354 8003AB54 125C000C */  jal        func_80017048
/* 2B358 8003AB58 21300002 */   addu      $a2, $s0, $zero
/* 2B35C 8003AB5C 21200002 */  addu       $a0, $s0, $zero
/* 2B360 8003AB60 21280002 */  addu       $a1, $s0, $zero
/* 2B364 8003AB64 D65D000C */  jal        VecAdd
/* 2B368 8003AB68 0C002626 */   addiu     $a2, $s1, 0xC
/* 2B36C 8003AB6C CB89010C */  jal        rand
/* 2B370 8003AB70 00000000 */   nop
/* 2B374 8003AB74 0E0002A2 */  sb         $v0, 0xE($s0)
/* 2B378 8003AB78 03000224 */  addiu      $v0, $zero, 0x3
/* 2B37C 8003AB7C 20000324 */  addiu      $v1, $zero, 0x20
/* 2B380 8003AB80 0F0002A2 */  sb         $v0, 0xF($s0)
/* 2B384 8003AB84 10000224 */  addiu      $v0, $zero, 0x10
/* 2B388 8003AB88 0D0002A2 */  sb         $v0, 0xD($s0)
/* 2B38C 8003AB8C 40000224 */  addiu      $v0, $zero, 0x40
/* 2B390 8003AB90 0C0003A2 */  sb         $v1, 0xC($s0)
/* 2B394 8003AB94 140003A2 */  sb         $v1, 0x14($s0)
/* 2B398 8003AB98 150002A2 */  sb         $v0, 0x15($s0)
.L8003AB9C:
/* 2B39C 8003AB9C 21104002 */  addu       $v0, $s2, $zero
/* 2B3A0 8003ABA0 2000BF8F */  lw         $ra, 0x20($sp)
/* 2B3A4 8003ABA4 1C00B38F */  lw         $s3, 0x1C($sp)
/* 2B3A8 8003ABA8 1800B28F */  lw         $s2, 0x18($sp)
/* 2B3AC 8003ABAC 1400B18F */  lw         $s1, 0x14($sp)
/* 2B3B0 8003ABB0 1000B08F */  lw         $s0, 0x10($sp)
/* 2B3B4 8003ABB4 2800BD27 */  addiu      $sp, $sp, 0x28
/* 2B3B8 8003ABB8 0800E003 */  jr         $ra
/* 2B3BC 8003ABBC 00000000 */   nop
.size func_8003AAEC, . - func_8003AAEC
