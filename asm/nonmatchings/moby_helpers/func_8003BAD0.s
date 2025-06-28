.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003BAD0
/* 2C2D0 8003BAD0 90FFBD27 */  addiu      $sp, $sp, -0x70
/* 2C2D4 8003BAD4 5000B2AF */  sw         $s2, 0x50($sp)
/* 2C2D8 8003BAD8 21908000 */  addu       $s2, $a0, $zero
/* 2C2DC 8003BADC 5C00B5AF */  sw         $s5, 0x5C($sp)
/* 2C2E0 8003BAE0 21A80000 */  addu       $s5, $zero, $zero
/* 2C2E4 8003BAE4 5800B4AF */  sw         $s4, 0x58($sp)
/* 2C2E8 8003BAE8 8000B48F */  lw         $s4, 0x80($sp)
/* 2C2EC 8003BAEC 1800A427 */  addiu      $a0, $sp, 0x18
/* 2C2F0 8003BAF0 6400B7AF */  sw         $s7, 0x64($sp)
/* 2C2F4 8003BAF4 21B8C000 */  addu       $s7, $a2, $zero
/* 2C2F8 8003BAF8 5400B3AF */  sw         $s3, 0x54($sp)
/* 2C2FC 8003BAFC 0C005326 */  addiu      $s3, $s2, 0xC
/* 2C300 8003BB00 6000B6AF */  sw         $s6, 0x60($sp)
/* 2C304 8003BB04 8400B68F */  lw         $s6, 0x84($sp)
/* 2C308 8003BB08 21306002 */  addu       $a2, $s3, $zero
/* 2C30C 8003BB0C 4800B0AF */  sw         $s0, 0x48($sp)
/* 2C310 8003BB10 2180E000 */  addu       $s0, $a3, $zero
/* 2C314 8003BB14 6800BFAF */  sw         $ra, 0x68($sp)
/* 2C318 8003BB18 E35D000C */  jal        VecSub
/* 2C31C 8003BB1C 4C00B1AF */   sw        $s1, 0x4C($sp)
/* 2C320 8003BB20 1800A48F */  lw         $a0, 0x18($sp)
/* 2C324 8003BB24 1C00A58F */  lw         $a1, 0x1C($sp)
/* 2C328 8003BB28 AD5A000C */  jal        func_80016AB4
/* 2C32C 8003BB2C 21300000 */   addu      $a2, $zero, $zero
/* 2C330 8003BB30 21884000 */  addu       $s1, $v0, $zero
/* 2C334 8003BB34 1800A427 */  addiu      $a0, $sp, 0x18
/* 2C338 8003BB38 7F5C000C */  jal        VecMagnitude
/* 2C33C 8003BB3C 21280000 */   addu      $a1, $zero, $zero
/* 2C340 8003BB40 21204000 */  addu       $a0, $v0, $zero
/* 2C344 8003BB44 2000A58F */  lw         $a1, 0x20($sp)
/* 2C348 8003BB48 AD5A000C */  jal        func_80016AB4
/* 2C34C 8003BB4C 21300000 */   addu      $a2, $zero, $zero
/* 2C350 8003BB50 46004392 */  lbu        $v1, 0x46($s2)
/* 2C354 8003BB54 21384000 */  addu       $a3, $v0, $zero
/* 2C358 8003BB58 23102302 */  subu       $v0, $s1, $v1
/* 2C35C 8003BB5C FF005130 */  andi       $s1, $v0, 0xFF
/* 2C360 8003BB60 8000222A */  slti       $v0, $s1, 0x80
/* 2C364 8003BB64 02004014 */  bnez       $v0, .L8003BB70
/* 2C368 8003BB68 23201000 */   negu      $a0, $s0
/* 2C36C 8003BB6C 00FF3126 */  addiu      $s1, $s1, -0x100
.L8003BB70:
/* 2C370 8003BB70 2A102402 */  slt        $v0, $s1, $a0
/* 2C374 8003BB74 03004010 */  beqz       $v0, .L8003BB84
/* 2C378 8003BB78 2A101102 */   slt       $v0, $s0, $s1
/* 2C37C 8003BB7C 21888000 */  addu       $s1, $a0, $zero
/* 2C380 8003BB80 2A101102 */  slt        $v0, $s0, $s1
.L8003BB84:
/* 2C384 8003BB84 02004010 */  beqz       $v0, .L8003BB90
/* 2C388 8003BB88 00000000 */   nop
/* 2C38C 8003BB8C 21880002 */  addu       $s1, $s0, $zero
.L8003BB90:
/* 2C390 8003BB90 45004292 */  lbu        $v0, 0x45($s2)
/* 2C394 8003BB94 00000000 */  nop
/* 2C398 8003BB98 2310E200 */  subu       $v0, $a3, $v0
/* 2C39C 8003BB9C FF004730 */  andi       $a3, $v0, 0xFF
/* 2C3A0 8003BBA0 8000E228 */  slti       $v0, $a3, 0x80
/* 2C3A4 8003BBA4 02004014 */  bnez       $v0, .L8003BBB0
/* 2C3A8 8003BBA8 23201400 */   negu      $a0, $s4
/* 2C3AC 8003BBAC 00FFE724 */  addiu      $a3, $a3, -0x100
.L8003BBB0:
/* 2C3B0 8003BBB0 2A10E400 */  slt        $v0, $a3, $a0
/* 2C3B4 8003BBB4 03004010 */  beqz       $v0, .L8003BBC4
/* 2C3B8 8003BBB8 2A108702 */   slt       $v0, $s4, $a3
/* 2C3BC 8003BBBC 21388000 */  addu       $a3, $a0, $zero
/* 2C3C0 8003BBC0 2A108702 */  slt        $v0, $s4, $a3
.L8003BBC4:
/* 2C3C4 8003BBC4 02004010 */  beqz       $v0, .L8003BBD0
/* 2C3C8 8003BBC8 44004426 */   addiu     $a0, $s2, 0x44
/* 2C3CC 8003BBCC 21388002 */  addu       $a3, $s4, $zero
.L8003BBD0:
/* 2C3D0 8003BBD0 2800B027 */  addiu      $s0, $sp, 0x28
/* 2C3D4 8003BBD4 21280002 */  addu       $a1, $s0, $zero
/* 2C3D8 8003BBD8 21300000 */  addu       $a2, $zero, $zero
/* 2C3DC 8003BBDC 45004292 */  lbu        $v0, 0x45($s2)
/* 2C3E0 8003BBE0 21187100 */  addu       $v1, $v1, $s1
/* 2C3E4 8003BBE4 460043A2 */  sb         $v1, 0x46($s2)
/* 2C3E8 8003BBE8 21104700 */  addu       $v0, $v0, $a3
/* 2C3EC 8003BBEC 4B5B000C */  jal        RotVec8ToMatrix
/* 2C3F0 8003BBF0 450042A2 */   sb        $v0, 0x45($s2)
/* 2C3F4 8003BBF4 21200002 */  addu       $a0, $s0, $zero
/* 2C3F8 8003BBF8 1800A527 */  addiu      $a1, $sp, 0x18
/* 2C3FC 8003BBFC 2130A000 */  addu       $a2, $a1, $zero
/* 2C400 8003BC00 1800B7AF */  sw         $s7, 0x18($sp)
/* 2C404 8003BC04 1C00A0AF */  sw         $zero, 0x1C($sp)
/* 2C408 8003BC08 125C000C */  jal        VecRotateByMatrix
/* 2C40C 8003BC0C 2000A0AF */   sw        $zero, 0x20($sp)
/* 2C410 8003BC10 21206002 */  addu       $a0, $s3, $zero
/* 2C414 8003BC14 21286002 */  addu       $a1, $s3, $zero
/* 2C418 8003BC18 D65D000C */  jal        VecAdd
/* 2C41C 8003BC1C 1800A627 */   addiu     $a2, $sp, 0x18
/* 2C420 8003BC20 1600C012 */  beqz       $s6, .L8003BC7C
/* 2C424 8003BC24 2128C002 */   addu      $a1, $s6, $zero
/* 2C428 8003BC28 21206002 */  addu       $a0, $s3, $zero
/* 2C42C 8003BC2C 932F010C */  jal        func_8004BE4C
/* 2C430 8003BC30 2130C002 */   addu      $a2, $s6, $zero
/* 2C434 8003BC34 07004010 */  beqz       $v0, .L8003BC54
/* 2C438 8003BC38 21206002 */   addu      $a0, $s3, $zero
/* 2C43C 8003BC3C 0780053C */  lui        $a1, %hi(D_80076B80)
/* 2C440 8003BC40 806BA524 */  addiu      $a1, $a1, %lo(D_80076B80)
/* 2C444 8003BC44 C05D000C */  jal        VecCopy
/* 2C448 8003BC48 21206002 */   addu      $a0, $s3, $zero
/* 2C44C 8003BC4C 01001524 */  addiu      $s5, $zero, 0x1
/* 2C450 8003BC50 21206002 */  addu       $a0, $s3, $zero
.L8003BC54:
/* 2C454 8003BC54 2128C002 */  addu       $a1, $s6, $zero
/* 2C458 8003BC58 21300000 */  addu       $a2, $zero, $zero
/* 2C45C 8003BC5C 01000224 */  addiu      $v0, $zero, 0x1
/* 2C460 8003BC60 21380000 */  addu       $a3, $zero, $zero
/* 2C464 8003BC64 1000B2AF */  sw         $s2, 0x10($sp)
/* 2C468 8003BC68 F238010C */  jal        func_8004E3C8
/* 2C46C 8003BC6C 1400A2AF */   sw        $v0, 0x14($sp)
/* 2C470 8003BC70 02004010 */  beqz       $v0, .L8003BC7C
/* 2C474 8003BC74 00000000 */   nop
/* 2C478 8003BC78 01001524 */  addiu      $s5, $zero, 0x1
.L8003BC7C:
/* 2C47C 8003BC7C 21204002 */  addu       $a0, $s2, $zero
/* 2C480 8003BC80 794A010C */  jal        func_800529E4
/* 2C484 8003BC84 02000524 */   addiu     $a1, $zero, 0x2
/* 2C488 8003BC88 D0E0000C */  jal        func_80038340
/* 2C48C 8003BC8C 21204002 */   addu      $a0, $s2, $zero
/* 2C490 8003BC90 F44C010C */  jal        func_800533D0
/* 2C494 8003BC94 21204002 */   addu      $a0, $s2, $zero
/* 2C498 8003BC98 2110A002 */  addu       $v0, $s5, $zero
/* 2C49C 8003BC9C 6800BF8F */  lw         $ra, 0x68($sp)
/* 2C4A0 8003BCA0 6400B78F */  lw         $s7, 0x64($sp)
/* 2C4A4 8003BCA4 6000B68F */  lw         $s6, 0x60($sp)
/* 2C4A8 8003BCA8 5C00B58F */  lw         $s5, 0x5C($sp)
/* 2C4AC 8003BCAC 5800B48F */  lw         $s4, 0x58($sp)
/* 2C4B0 8003BCB0 5400B38F */  lw         $s3, 0x54($sp)
/* 2C4B4 8003BCB4 5000B28F */  lw         $s2, 0x50($sp)
/* 2C4B8 8003BCB8 4C00B18F */  lw         $s1, 0x4C($sp)
/* 2C4BC 8003BCBC 4800B08F */  lw         $s0, 0x48($sp)
/* 2C4C0 8003BCC0 7000BD27 */  addiu      $sp, $sp, 0x70
/* 2C4C4 8003BCC4 0800E003 */  jr         $ra
/* 2C4C8 8003BCC8 00000000 */   nop
.size func_8003BAD0, . - func_8003BAD0
