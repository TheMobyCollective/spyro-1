.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80038250
/* 28A50 80038250 A0FFBD27 */  addiu      $sp, $sp, -0x60
/* 28A54 80038254 4C00B1AF */  sw         $s1, 0x4C($sp)
/* 28A58 80038258 21888000 */  addu       $s1, $a0, $zero
/* 28A5C 8003825C 1000A427 */  addiu      $a0, $sp, 0x10
/* 28A60 80038260 0880053C */  lui        $a1, %hi(g_Spyro)
/* 28A64 80038264 588AA524 */  addiu      $a1, $a1, %lo(g_Spyro)
/* 28A68 80038268 21302002 */  addu       $a2, $s1, $zero
/* 28A6C 8003826C 5C00BFAF */  sw         $ra, 0x5C($sp)
/* 28A70 80038270 5800B4AF */  sw         $s4, 0x58($sp)
/* 28A74 80038274 5400B3AF */  sw         $s3, 0x54($sp)
/* 28A78 80038278 5000B2AF */  sw         $s2, 0x50($sp)
/* 28A7C 8003827C E35D000C */  jal        VecSub
/* 28A80 80038280 4800B0AF */   sw        $s0, 0x48($sp)
/* 28A84 80038284 1000A427 */  addiu      $a0, $sp, 0x10
/* 28A88 80038288 7F5C000C */  jal        VecMagnitude
/* 28A8C 8003828C 01000524 */   addiu     $a1, $zero, 0x1
/* 28A90 80038290 1000A427 */  addiu      $a0, $sp, 0x10
/* 28A94 80038294 21804000 */  addu       $s0, $v0, $zero
/* 28A98 80038298 21280002 */  addu       $a1, $s0, $zero
/* 28A9C 8003829C A75C000C */  jal        func_8001729C
/* 28AA0 800382A0 01000624 */   addiu     $a2, $zero, 0x1
/* 28AA4 800382A4 1000A427 */  addiu      $a0, $sp, 0x10
/* 28AA8 800382A8 21280002 */  addu       $a1, $s0, $zero
/* 28AAC 800382AC 6E5D000C */  jal        func_800175B8
/* 28AB0 800382B0 00040624 */   addiu     $a2, $zero, 0x400
/* 28AB4 800382B4 2000B427 */  addiu      $s4, $sp, 0x20
/* 28AB8 800382B8 21208002 */  addu       $a0, $s4, $zero
/* 28ABC 800382BC C05D000C */  jal        VecCopy
/* 28AC0 800382C0 21282002 */   addu      $a1, $s1, $zero
/* 28AC4 800382C4 839A1000 */  sra        $s3, $s0, 10
/* 28AC8 800382C8 1300601A */  blez       $s3, .L80038318
/* 28ACC 800382CC 21880000 */   addu      $s1, $zero, $zero
/* 28AD0 800382D0 3000B227 */  addiu      $s2, $sp, 0x30
/* 28AD4 800382D4 21808002 */  addu       $s0, $s4, $zero
/* 28AD8 800382D8 21204002 */  addu       $a0, $s2, $zero
.L800382DC:
/* 28ADC 800382DC 21280002 */  addu       $a1, $s0, $zero
/* 28AE0 800382E0 D65D000C */  jal        VecAdd
/* 28AE4 800382E4 1000A627 */   addiu     $a2, $sp, 0x10
/* 28AE8 800382E8 21200002 */  addu       $a0, $s0, $zero
/* 28AEC 800382EC 8E2B010C */  jal        func_8004AE38
/* 28AF0 800382F0 21284002 */   addu      $a1, $s2, $zero
/* 28AF4 800382F4 09004014 */  bnez       $v0, .L8003831C
/* 28AF8 800382F8 21100000 */   addu      $v0, $zero, $zero
/* 28AFC 800382FC 21200002 */  addu       $a0, $s0, $zero
/* 28B00 80038300 C05D000C */  jal        VecCopy
/* 28B04 80038304 21284002 */   addu      $a1, $s2, $zero
/* 28B08 80038308 01003126 */  addiu      $s1, $s1, 0x1
/* 28B0C 8003830C 2A103302 */  slt        $v0, $s1, $s3
/* 28B10 80038310 F2FF4014 */  bnez       $v0, .L800382DC
/* 28B14 80038314 21204002 */   addu      $a0, $s2, $zero
.L80038318:
/* 28B18 80038318 01000224 */  addiu      $v0, $zero, 0x1
.L8003831C:
/* 28B1C 8003831C 5C00BF8F */  lw         $ra, 0x5C($sp)
/* 28B20 80038320 5800B48F */  lw         $s4, 0x58($sp)
/* 28B24 80038324 5400B38F */  lw         $s3, 0x54($sp)
/* 28B28 80038328 5000B28F */  lw         $s2, 0x50($sp)
/* 28B2C 8003832C 4C00B18F */  lw         $s1, 0x4C($sp)
/* 28B30 80038330 4800B08F */  lw         $s0, 0x48($sp)
/* 28B34 80038334 6000BD27 */  addiu      $sp, $sp, 0x60
/* 28B38 80038338 0800E003 */  jr         $ra
/* 28B3C 8003833C 00000000 */   nop
.size func_80038250, . - func_80038250
