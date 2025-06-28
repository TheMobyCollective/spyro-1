.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003A16C
/* 2A96C 8003A16C 88FFBD27 */  addiu      $sp, $sp, -0x78
/* 2A970 8003A170 6000B4AF */  sw         $s4, 0x60($sp)
/* 2A974 8003A174 21A08000 */  addu       $s4, $a0, $zero
/* 2A978 8003A178 5800B2AF */  sw         $s2, 0x58($sp)
/* 2A97C 8003A17C 2190A000 */  addu       $s2, $a1, $zero
/* 2A980 8003A180 6C00B7AF */  sw         $s7, 0x6C($sp)
/* 2A984 8003A184 21B8C000 */  addu       $s7, $a2, $zero
/* 2A988 8003A188 5C00B3AF */  sw         $s3, 0x5C($sp)
/* 2A98C 8003A18C 2198E000 */  addu       $s3, $a3, $zero
/* 2A990 8003A190 5000B0AF */  sw         $s0, 0x50($sp)
/* 2A994 8003A194 2000B027 */  addiu      $s0, $sp, 0x20
/* 2A998 8003A198 21200002 */  addu       $a0, $s0, $zero
/* 2A99C 8003A19C 0C008626 */  addiu      $a2, $s4, 0xC
/* 2A9A0 8003A1A0 7400BFAF */  sw         $ra, 0x74($sp)
/* 2A9A4 8003A1A4 7000BEAF */  sw         $fp, 0x70($sp)
/* 2A9A8 8003A1A8 6800B6AF */  sw         $s6, 0x68($sp)
/* 2A9AC 8003A1AC 6400B5AF */  sw         $s5, 0x64($sp)
/* 2A9B0 8003A1B0 5400B1AF */  sw         $s1, 0x54($sp)
/* 2A9B4 8003A1B4 01004592 */  lbu        $a1, 0x1($s2)
/* 2A9B8 8003A1B8 8800BE8F */  lw         $fp, 0x88($sp)
/* 2A9BC 8003A1BC 8C00B18F */  lw         $s1, 0x8C($sp)
/* 2A9C0 8003A1C0 9000B68F */  lw         $s6, 0x90($sp)
/* 2A9C4 8003A1C4 9400B58F */  lw         $s5, 0x94($sp)
/* 2A9C8 8003A1C8 00290500 */  sll        $a1, $a1, 4
/* 2A9CC 8003A1CC 0800A524 */  addiu      $a1, $a1, 0x8
/* 2A9D0 8003A1D0 E35D000C */  jal        VecSub
/* 2A9D4 8003A1D4 21284502 */   addu      $a1, $s2, $a1
/* 2A9D8 8003A1D8 21200002 */  addu       $a0, $s0, $zero
/* 2A9DC 8003A1DC 21280000 */  addu       $a1, $zero, $zero
/* 2A9E0 8003A1E0 7F5C000C */  jal        VecMagnitude
/* 2A9E4 8003A1E4 1800A0A3 */   sb        $zero, 0x18($sp)
/* 2A9E8 8003A1E8 21204000 */  addu       $a0, $v0, $zero
/* 2A9EC 8003A1EC 2800A58F */  lw         $a1, 0x28($sp)
/* 2A9F0 8003A1F0 AD5A000C */  jal        func_80016AB4
/* 2A9F4 8003A1F4 21300000 */   addu      $a2, $zero, $zero
/* 2A9F8 8003A1F8 21200002 */  addu       $a0, $s0, $zero
/* 2A9FC 8003A1FC 21280000 */  addu       $a1, $zero, $zero
/* 2AA00 8003A200 7F5C000C */  jal        VecMagnitude
/* 2AA04 8003A204 1900A2A3 */   sb        $v0, 0x19($sp)
/* 2AA08 8003A208 2A105700 */  slt        $v0, $v0, $s7
/* 2AA0C 8003A20C 04004010 */  beqz       $v0, .L8003A220
/* 2AA10 8003A210 00000000 */   nop
/* 2AA14 8003A214 0000A28E */  lw         $v0, 0x0($s5)
/* 2AA18 8003A218 A7E80008 */  j          .L8003A29C
/* 2AA1C 8003A21C 1A00A2A3 */   sb        $v0, 0x1A($sp)
.L8003A220:
/* 2AA20 8003A220 2000A48F */  lw         $a0, 0x20($sp)
/* 2AA24 8003A224 2400A58F */  lw         $a1, 0x24($sp)
/* 2AA28 8003A228 AD5A000C */  jal        func_80016AB4
/* 2AA2C 8003A22C 21300000 */   addu      $a2, $zero, $zero
/* 2AA30 8003A230 0000A58E */  lw         $a1, 0x0($s5)
/* 2AA34 8003A234 00000000 */  nop
/* 2AA38 8003A238 23104500 */  subu       $v0, $v0, $a1
/* 2AA3C 8003A23C FF004330 */  andi       $v1, $v0, 0xFF
/* 2AA40 8003A240 81006228 */  slti       $v0, $v1, 0x81
/* 2AA44 8003A244 02004014 */  bnez       $v0, .L8003A250
/* 2AA48 8003A248 00000000 */   nop
/* 2AA4C 8003A24C 00FF6324 */  addiu      $v1, $v1, -0x100
.L8003A250:
/* 2AA50 8003A250 02006104 */  bgez       $v1, .L8003A25C
/* 2AA54 8003A254 21106000 */   addu      $v0, $v1, $zero
/* 2AA58 8003A258 23100200 */  negu       $v0, $v0
.L8003A25C:
/* 2AA5C 8003A25C 2A10C202 */  slt        $v0, $s6, $v0
/* 2AA60 8003A260 02004010 */  beqz       $v0, .L8003A26C
/* 2AA64 8003A264 23201100 */   negu      $a0, $s1
/* 2AA68 8003A268 21980000 */  addu       $s3, $zero, $zero
.L8003A26C:
/* 2AA6C 8003A26C 2A106400 */  slt        $v0, $v1, $a0
/* 2AA70 8003A270 03004010 */  beqz       $v0, .L8003A280
/* 2AA74 8003A274 2A102302 */   slt       $v0, $s1, $v1
/* 2AA78 8003A278 21188000 */  addu       $v1, $a0, $zero
/* 2AA7C 8003A27C 2A102302 */  slt        $v0, $s1, $v1
.L8003A280:
/* 2AA80 8003A280 03004010 */  beqz       $v0, .L8003A290
/* 2AA84 8003A284 21106500 */   addu      $v0, $v1, $a1
/* 2AA88 8003A288 21182002 */  addu       $v1, $s1, $zero
/* 2AA8C 8003A28C 21106500 */  addu       $v0, $v1, $a1
.L8003A290:
/* 2AA90 8003A290 1A00A2A3 */  sb         $v0, 0x1A($sp)
/* 2AA94 8003A294 FF004230 */  andi       $v0, $v0, 0xFF
/* 2AA98 8003A298 0000A2AE */  sw         $v0, 0x0($s5)
.L8003A29C:
/* 2AA9C 8003A29C 2000B127 */  addiu      $s1, $sp, 0x20
/* 2AAA0 8003A2A0 21202002 */  addu       $a0, $s1, $zero
/* 2AAA4 8003A2A4 7F5C000C */  jal        VecMagnitude
/* 2AAA8 8003A2A8 01000524 */   addiu     $a1, $zero, 0x1
/* 2AAAC 8003A2AC 21184000 */  addu       $v1, $v0, $zero
/* 2AAB0 8003A2B0 2A107300 */  slt        $v0, $v1, $s3
/* 2AAB4 8003A2B4 02004010 */  beqz       $v0, .L8003A2C0
/* 2AAB8 8003A2B8 1800A427 */   addiu     $a0, $sp, 0x18
/* 2AABC 8003A2BC 21986000 */  addu       $s3, $v1, $zero
.L8003A2C0:
/* 2AAC0 8003A2C0 3000B027 */  addiu      $s0, $sp, 0x30
/* 2AAC4 8003A2C4 21280002 */  addu       $a1, $s0, $zero
/* 2AAC8 8003A2C8 4B5B000C */  jal        RotVec8ToMatrix
/* 2AACC 8003A2CC 21300000 */   addu      $a2, $zero, $zero
/* 2AAD0 8003A2D0 21200002 */  addu       $a0, $s0, $zero
/* 2AAD4 8003A2D4 21282002 */  addu       $a1, $s1, $zero
/* 2AAD8 8003A2D8 21302002 */  addu       $a2, $s1, $zero
/* 2AADC 8003A2DC 2000B3AF */  sw         $s3, 0x20($sp)
/* 2AAE0 8003A2E0 2400A0AF */  sw         $zero, 0x24($sp)
/* 2AAE4 8003A2E4 125C000C */  jal        VecRotateByMatrix
/* 2AAE8 8003A2E8 2800A0AF */   sw        $zero, 0x28($sp)
/* 2AAEC 8003A2EC 21202002 */  addu       $a0, $s1, $zero
/* 2AAF0 8003A2F0 0C008526 */  addiu      $a1, $s4, 0xC
/* 2AAF4 8003A2F4 D65D000C */  jal        VecAdd
/* 2AAF8 8003A2F8 21302002 */   addu      $a2, $s1, $zero
/* 2AAFC 8003A2FC 0700C013 */  beqz       $fp, .L8003A31C
/* 2AB00 8003A300 21202002 */   addu      $a0, $s1, $zero
/* 2AB04 8003A304 2128C003 */  addu       $a1, $fp, $zero
/* 2AB08 8003A308 21300000 */  addu       $a2, $zero, $zero
/* 2AB0C 8003A30C 21380000 */  addu       $a3, $zero, $zero
/* 2AB10 8003A310 1000B4AF */  sw         $s4, 0x10($sp)
/* 2AB14 8003A314 F238010C */  jal        func_8004E3C8
/* 2AB18 8003A318 1400A0AF */   sw        $zero, 0x14($sp)
.L8003A31C:
/* 2AB1C 8003A31C 21202002 */  addu       $a0, $s1, $zero
/* 2AB20 8003A320 2800A28F */  lw         $v0, 0x28($sp)
/* 2AB24 8003A324 00040524 */  addiu      $a1, $zero, 0x400
/* 2AB28 8003A328 00044224 */  addiu      $v0, $v0, 0x400
/* 2AB2C 8003A32C 7B35010C */  jal        func_8004D5EC
/* 2AB30 8003A330 2800A2AF */   sw        $v0, 0x28($sp)
/* 2AB34 8003A334 21184000 */  addu       $v1, $v0, $zero
/* 2AB38 8003A338 03006010 */  beqz       $v1, .L8003A348
/* 2AB3C 8003A33C 00000000 */   nop
/* 2AB40 8003A340 D6E80008 */  j          .L8003A358
/* 2AB44 8003A344 2800A3AF */   sw        $v1, 0x28($sp)
.L8003A348:
/* 2AB48 8003A348 2800A28F */  lw         $v0, 0x28($sp)
/* 2AB4C 8003A34C 00000000 */  nop
/* 2AB50 8003A350 00FC4224 */  addiu      $v0, $v0, -0x400
/* 2AB54 8003A354 2800A2AF */  sw         $v0, 0x28($sp)
.L8003A358:
/* 2AB58 8003A358 0C009126 */  addiu      $s1, $s4, 0xC
/* 2AB5C 8003A35C 21202002 */  addu       $a0, $s1, $zero
/* 2AB60 8003A360 2000B027 */  addiu      $s0, $sp, 0x20
/* 2AB64 8003A364 C05D000C */  jal        VecCopy
/* 2AB68 8003A368 21280002 */   addu      $a1, $s0, $zero
/* 2AB6C 8003A36C F44C010C */  jal        func_800533D0
/* 2AB70 8003A370 21208002 */   addu      $a0, $s4, $zero
/* 2AB74 8003A374 21208002 */  addu       $a0, $s4, $zero
/* 2AB78 8003A378 794A010C */  jal        func_800529E4
/* 2AB7C 8003A37C 02000524 */   addiu     $a1, $zero, 0x2
/* 2AB80 8003A380 21980000 */  addu       $s3, $zero, $zero
/* 2AB84 8003A384 21200002 */  addu       $a0, $s0, $zero
/* 2AB88 8003A388 01004592 */  lbu        $a1, 0x1($s2)
/* 2AB8C 8003A38C 21302002 */  addu       $a2, $s1, $zero
/* 2AB90 8003A390 00290500 */  sll        $a1, $a1, 4
/* 2AB94 8003A394 0800A524 */  addiu      $a1, $a1, 0x8
/* 2AB98 8003A398 E35D000C */  jal        VecSub
/* 2AB9C 8003A39C 21284502 */   addu      $a1, $s2, $a1
/* 2ABA0 8003A3A0 21200002 */  addu       $a0, $s0, $zero
/* 2ABA4 8003A3A4 7F5C000C */  jal        VecMagnitude
/* 2ABA8 8003A3A8 01000524 */   addiu     $a1, $zero, 0x1
/* 2ABAC 8003A3AC 2A105700 */  slt        $v0, $v0, $s7
/* 2ABB0 8003A3B0 0E004010 */  beqz       $v0, .L8003A3EC
/* 2ABB4 8003A3B4 21106002 */   addu      $v0, $s3, $zero
/* 2ABB8 8003A3B8 490080A2 */  sb         $zero, 0x49($s4)
/* 2ABBC 8003A3BC 01004292 */  lbu        $v0, 0x1($s2)
/* 2ABC0 8003A3C0 00004392 */  lbu        $v1, 0x0($s2)
/* 2ABC4 8003A3C4 01004224 */  addiu      $v0, $v0, 0x1
/* 2ABC8 8003A3C8 010042A2 */  sb         $v0, 0x1($s2)
/* 2ABCC 8003A3CC FF004230 */  andi       $v0, $v0, 0xFF
/* 2ABD0 8003A3D0 02004314 */  bne        $v0, $v1, .L8003A3DC
/* 2ABD4 8003A3D4 00000000 */   nop
/* 2ABD8 8003A3D8 010040A2 */  sb         $zero, 0x1($s2)
.L8003A3DC:
/* 2ABDC 8003A3DC 01004292 */  lbu        $v0, 0x1($s2)
/* 2ABE0 8003A3E0 00000000 */  nop
/* 2ABE4 8003A3E4 00015324 */  addiu      $s3, $v0, 0x100
/* 2ABE8 8003A3E8 21106002 */  addu       $v0, $s3, $zero
.L8003A3EC:
/* 2ABEC 8003A3EC 7400BF8F */  lw         $ra, 0x74($sp)
/* 2ABF0 8003A3F0 7000BE8F */  lw         $fp, 0x70($sp)
/* 2ABF4 8003A3F4 6C00B78F */  lw         $s7, 0x6C($sp)
/* 2ABF8 8003A3F8 6800B68F */  lw         $s6, 0x68($sp)
/* 2ABFC 8003A3FC 6400B58F */  lw         $s5, 0x64($sp)
/* 2AC00 8003A400 6000B48F */  lw         $s4, 0x60($sp)
/* 2AC04 8003A404 5C00B38F */  lw         $s3, 0x5C($sp)
/* 2AC08 8003A408 5800B28F */  lw         $s2, 0x58($sp)
/* 2AC0C 8003A40C 5400B18F */  lw         $s1, 0x54($sp)
/* 2AC10 8003A410 5000B08F */  lw         $s0, 0x50($sp)
/* 2AC14 8003A414 7800BD27 */  addiu      $sp, $sp, 0x78
/* 2AC18 8003A418 0800E003 */  jr         $ra
/* 2AC1C 8003A41C 00000000 */   nop
.size func_8003A16C, . - func_8003A16C
