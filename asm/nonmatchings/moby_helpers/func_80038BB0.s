.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80038BB0
/* 293B0 80038BB0 D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 293B4 80038BB4 2000B2AF */  sw         $s2, 0x20($sp)
/* 293B8 80038BB8 21908000 */  addu       $s2, $a0, $zero
/* 293BC 80038BBC 2400B3AF */  sw         $s3, 0x24($sp)
/* 293C0 80038BC0 21980000 */  addu       $s3, $zero, $zero
/* 293C4 80038BC4 2C00BFAF */  sw         $ra, 0x2C($sp)
/* 293C8 80038BC8 2800B4AF */  sw         $s4, 0x28($sp)
/* 293CC 80038BCC 1C00B1AF */  sw         $s1, 0x1C($sp)
/* 293D0 80038BD0 1800B0AF */  sw         $s0, 0x18($sp)
/* 293D4 80038BD4 00004292 */  lbu        $v0, 0x0($s2)
/* 293D8 80038BD8 00000000 */  nop
/* 293DC 80038BDC 11004018 */  blez       $v0, .L80038C24
/* 293E0 80038BE0 21800000 */   addu      $s0, $zero, $zero
/* 293E4 80038BE4 08001124 */  addiu      $s1, $zero, 0x8
.L80038BE8:
/* 293E8 80038BE8 0880043C */  lui        $a0, %hi(g_Spyro)
/* 293EC 80038BEC 588A8424 */  addiu      $a0, $a0, %lo(g_Spyro)
/* 293F0 80038BF0 645E000C */  jal        func_80017990
/* 293F4 80038BF4 21285102 */   addu      $a1, $s2, $s1
/* 293F8 80038BF8 21184000 */  addu       $v1, $v0, $zero
/* 293FC 80038BFC 2A106302 */  slt        $v0, $s3, $v1
/* 29400 80038C00 03004010 */  beqz       $v0, .L80038C10
/* 29404 80038C04 00000000 */   nop
/* 29408 80038C08 21986000 */  addu       $s3, $v1, $zero
/* 2940C 80038C0C 21A00002 */  addu       $s4, $s0, $zero
.L80038C10:
/* 29410 80038C10 00004292 */  lbu        $v0, 0x0($s2)
/* 29414 80038C14 01001026 */  addiu      $s0, $s0, 0x1
/* 29418 80038C18 2A100202 */  slt        $v0, $s0, $v0
/* 2941C 80038C1C F2FF4014 */  bnez       $v0, .L80038BE8
/* 29420 80038C20 10003126 */   addiu     $s1, $s1, 0x10
.L80038C24:
/* 29424 80038C24 21108002 */  addu       $v0, $s4, $zero
/* 29428 80038C28 2C00BF8F */  lw         $ra, 0x2C($sp)
/* 2942C 80038C2C 2800B48F */  lw         $s4, 0x28($sp)
/* 29430 80038C30 2400B38F */  lw         $s3, 0x24($sp)
/* 29434 80038C34 2000B28F */  lw         $s2, 0x20($sp)
/* 29438 80038C38 1C00B18F */  lw         $s1, 0x1C($sp)
/* 2943C 80038C3C 1800B08F */  lw         $s0, 0x18($sp)
/* 29440 80038C40 3000BD27 */  addiu      $sp, $sp, 0x30
/* 29444 80038C44 0800E003 */  jr         $ra
/* 29448 80038C48 00000000 */   nop
.size func_80038BB0, . - func_80038BB0
