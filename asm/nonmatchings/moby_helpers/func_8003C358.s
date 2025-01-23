.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003C358
/* 2CB58 8003C358 80FFBD27 */  addiu      $sp, $sp, -0x80
/* 2CB5C 8003C35C 6800B4AF */  sw         $s4, 0x68($sp)
/* 2CB60 8003C360 21A08000 */  addu       $s4, $a0, $zero
/* 2CB64 8003C364 6400B3AF */  sw         $s3, 0x64($sp)
/* 2CB68 8003C368 2198A000 */  addu       $s3, $a1, $zero
/* 2CB6C 8003C36C 7C00BFAF */  sw         $ra, 0x7C($sp)
/* 2CB70 8003C370 7800BEAF */  sw         $fp, 0x78($sp)
/* 2CB74 8003C374 7400B7AF */  sw         $s7, 0x74($sp)
/* 2CB78 8003C378 7000B6AF */  sw         $s6, 0x70($sp)
/* 2CB7C 8003C37C 6C00B5AF */  sw         $s5, 0x6C($sp)
/* 2CB80 8003C380 6000B2AF */  sw         $s2, 0x60($sp)
/* 2CB84 8003C384 5C00B1AF */  sw         $s1, 0x5C($sp)
/* 2CB88 8003C388 0B006012 */  beqz       $s3, .L8003C3B8
/* 2CB8C 8003C38C 5800B0AF */   sw        $s0, 0x58($sp)
/* 2CB90 8003C390 0000828E */  lw         $v0, 0x0($s4)
/* 2CB94 8003C394 00000000 */  nop
/* 2CB98 8003C398 0000428C */  lw         $v0, 0x0($v0)
/* 2CB9C 8003C39C 46009792 */  lbu        $s7, 0x46($s4)
/* 2CBA0 8003C3A0 80100200 */  sll        $v0, $v0, 2
/* 2CBA4 8003C3A4 0780013C */  lui        $at, %hi(D_8006F7F0)
/* 2CBA8 8003C3A8 21082200 */  addu       $at, $at, $v0
/* 2CBAC 8003C3AC F0F7328C */  lw         $s2, %lo(D_8006F7F0)($at)
/* 2CBB0 8003C3B0 FCF00008 */  j          .L8003C3F0
/* 2CBB4 8003C3B4 FF00F032 */   andi      $s0, $s7, 0xFF
.L8003C3B8:
/* 2CBB8 8003C3B8 21300000 */  addu       $a2, $zero, $zero
/* 2CBBC 8003C3BC 0780123C */  lui        $s2, %hi(D_8006F880)
/* 2CBC0 8003C3C0 80F8528E */  lw         $s2, %lo(D_8006F880)($s2)
/* 2CBC4 8003C3C4 0880033C */  lui        $v1, %hi(g_Spyro)
/* 2CBC8 8003C3C8 588A638C */  lw         $v1, %lo(g_Spyro)($v1)
/* 2CBCC 8003C3CC 0C00848E */  lw         $a0, 0xC($s4)
/* 2CBD0 8003C3D0 0880023C */  lui        $v0, %hi(g_Spyro + 0x4)
/* 2CBD4 8003C3D4 5C8A428C */  lw         $v0, %lo(g_Spyro + 0x4)($v0)
/* 2CBD8 8003C3D8 1000858E */  lw         $a1, 0x10($s4)
/* 2CBDC 8003C3DC 23206400 */  subu       $a0, $v1, $a0
/* 2CBE0 8003C3E0 AD5A000C */  jal        func_80016AB4
/* 2CBE4 8003C3E4 23284500 */   subu      $a1, $v0, $a1
/* 2CBE8 8003C3E8 21B84000 */  addu       $s7, $v0, $zero
/* 2CBEC 8003C3EC FF00F032 */  andi       $s0, $s7, 0xFF
.L8003C3F0:
/* 2CBF0 8003C3F0 00891000 */  sll        $s1, $s0, 4
/* 2CBF4 8003C3F4 2C5B000C */  jal        func_80016CB0
/* 2CBF8 8003C3F8 21202002 */   addu      $a0, $s1, $zero
/* 2CBFC 8003C3FC 21202002 */  addu       $a0, $s1, $zero
/* 2CC00 8003C400 40180200 */  sll        $v1, $v0, 1
/* 2CC04 8003C404 21186200 */  addu       $v1, $v1, $v0
/* 2CC08 8003C408 03190300 */  sra        $v1, $v1, 4
/* 2CC0C 8003C40C 165B000C */  jal        func_80016C58
/* 2CC10 8003C410 1000A3AF */   sw        $v1, 0x10($sp)
/* 2CC14 8003C414 40001026 */  addiu      $s0, $s0, 0x40
/* 2CC18 8003C418 00811000 */  sll        $s0, $s0, 4
/* 2CC1C 8003C41C 21200002 */  addu       $a0, $s0, $zero
/* 2CC20 8003C420 40180200 */  sll        $v1, $v0, 1
/* 2CC24 8003C424 21186200 */  addu       $v1, $v1, $v0
/* 2CC28 8003C428 03190300 */  sra        $v1, $v1, 4
/* 2CC2C 8003C42C 1400A3AF */  sw         $v1, 0x14($sp)
/* 2CC30 8003C430 2C5B000C */  jal        func_80016CB0
/* 2CC34 8003C434 1800A0AF */   sw        $zero, 0x18($sp)
/* 2CC38 8003C438 21200002 */  addu       $a0, $s0, $zero
/* 2CC3C 8003C43C 43110200 */  sra        $v0, $v0, 5
/* 2CC40 8003C440 165B000C */  jal        func_80016C58
/* 2CC44 8003C444 2000A2AF */   sw        $v0, 0x20($sp)
/* 2CC48 8003C448 43110200 */  sra        $v0, $v0, 5
/* 2CC4C 8003C44C 2400A2AF */  sw         $v0, 0x24($sp)
/* 2CC50 8003C450 13006012 */  beqz       $s3, .L8003C4A0
/* 2CC54 8003C454 2800A0AF */   sw        $zero, 0x28($sp)
/* 2CC58 8003C458 49008292 */  lbu        $v0, 0x49($s4)
/* 2CC5C 8003C45C 00000000 */  nop
/* 2CC60 8003C460 04004014 */  bnez       $v0, .L8003C474
/* 2CC64 8003C464 3000B027 */   addiu     $s0, $sp, 0x30
/* 2CC68 8003C468 46008292 */  lbu        $v0, 0x46($s4)
/* 2CC6C 8003C46C 28F10008 */  j          .L8003C4A0
/* 2CC70 8003C470 80FF5724 */   addiu     $s7, $v0, -0x80
.L8003C474:
/* 2CC74 8003C474 46009792 */  lbu        $s7, 0x46($s4)
/* 2CC78 8003C478 BC5D000C */  jal        VecNull
/* 2CC7C 8003C47C 21200002 */   addu      $a0, $s0, $zero
/* 2CC80 8003C480 1000A427 */  addiu      $a0, $sp, 0x10
/* 2CC84 8003C484 21280002 */  addu       $a1, $s0, $zero
/* 2CC88 8003C488 E35D000C */  jal        VecSub
/* 2CC8C 8003C48C 21308000 */   addu      $a2, $a0, $zero
/* 2CC90 8003C490 2000A427 */  addiu      $a0, $sp, 0x20
/* 2CC94 8003C494 21280002 */  addu       $a1, $s0, $zero
/* 2CC98 8003C498 E35D000C */  jal        VecSub
/* 2CC9C 8003C49C 21308000 */   addu      $a2, $a0, $zero
.L8003C4A0:
/* 2CCA0 8003C4A0 DB89010C */  jal        strlen
/* 2CCA4 8003C4A4 21204002 */   addu      $a0, $s2, $zero
/* 2CCA8 8003C4A8 3000A427 */  addiu      $a0, $sp, 0x30
/* 2CCAC 8003C4AC 2000B027 */  addiu      $s0, $sp, 0x20
/* 2CCB0 8003C4B0 21280002 */  addu       $a1, $s0, $zero
/* 2CCB4 8003C4B4 21F04000 */  addu       $fp, $v0, $zero
/* 2CCB8 8003C4B8 FFFFD127 */  addiu      $s1, $fp, -0x1
/* 2CCBC 8003C4BC F05D000C */  jal        func_800177C0
/* 2CCC0 8003C4C0 21302002 */   addu      $a2, $s1, $zero
/* 2CCC4 8003C4C4 21200002 */  addu       $a0, $s0, $zero
/* 2CCC8 8003C4C8 A85D000C */  jal        func_800176A0
/* 2CCCC 8003C4CC 01000524 */   addiu     $a1, $zero, 0x1
/* 2CCD0 8003C4D0 40A81100 */  sll        $s5, $s1, 1
/* 2CCD4 8003C4D4 FF00B032 */  andi       $s0, $s5, 0xFF
/* 2CCD8 8003C4D8 00811000 */  sll        $s0, $s0, 4
/* 2CCDC 8003C4DC 2C5B000C */  jal        func_80016CB0
/* 2CCE0 8003C4E0 21200002 */   addu      $a0, $s0, $zero
/* 2CCE4 8003C4E4 21200002 */  addu       $a0, $s0, $zero
/* 2CCE8 8003C4E8 40180200 */  sll        $v1, $v0, 1
/* 2CCEC 8003C4EC 21186200 */  addu       $v1, $v1, $v0
/* 2CCF0 8003C4F0 3800A28F */  lw         $v0, 0x38($sp)
/* 2CCF4 8003C4F4 C3180300 */  sra        $v1, $v1, 3
/* 2CCF8 8003C4F8 21104300 */  addu       $v0, $v0, $v1
/* 2CCFC 8003C4FC 2C5B000C */  jal        func_80016CB0
/* 2CD00 8003C500 3800A2AF */   sw        $v0, 0x38($sp)
/* 2CD04 8003C504 1000A38F */  lw         $v1, 0x10($sp)
/* 2CD08 8003C508 00000000 */  nop
/* 2CD0C 8003C50C 18006200 */  mult       $v1, $v0
/* 2CD10 8003C510 21200002 */  addu       $a0, $s0, $zero
/* 2CD14 8003C514 12380000 */  mflo       $a3
/* 2CD18 8003C518 2C5B000C */  jal        func_80016CB0
/* 2CD1C 8003C51C 4000A7AF */   sw        $a3, 0x40($sp)
/* 2CD20 8003C520 1400A38F */  lw         $v1, 0x14($sp)
/* 2CD24 8003C524 00000000 */  nop
/* 2CD28 8003C528 18006200 */  mult       $v1, $v0
/* 2CD2C 8003C52C 21980000 */  addu       $s3, $zero, $zero
/* 2CD30 8003C530 4800A0AF */  sw         $zero, 0x48($sp)
/* 2CD34 8003C534 12380000 */  mflo       $a3
/* 2CD38 8003C538 5D00C01B */  blez       $fp, .L8003C6B0
/* 2CD3C 8003C53C 4400A7AF */   sw        $a3, 0x44($sp)
/* 2CD40 8003C540 21B04002 */  addu       $s6, $s2, $zero
.L8003C544:
/* 2CD44 8003C544 0000C392 */  lbu        $v1, 0x0($s6)
/* 2CD48 8003C548 20000224 */  addiu      $v0, $zero, 0x20
/* 2CD4C 8003C54C FF006430 */  andi       $a0, $v1, 0xFF
/* 2CD50 8003C550 4E008210 */  beq        $a0, $v0, .L8003C68C
/* 2CD54 8003C554 BFFF6224 */   addiu     $v0, $v1, -0x41
/* 2CD58 8003C558 1A00422C */  sltiu      $v0, $v0, 0x1A
/* 2CD5C 8003C55C 03004010 */  beqz       $v0, .L8003C56C
/* 2CD60 8003C560 00000000 */   nop
/* 2CD64 8003C564 5CF10008 */  j          .L8003C570
/* 2CD68 8003C568 69018424 */   addiu     $a0, $a0, 0x169
.L8003C56C:
/* 2CD6C 8003C56C 4C000424 */  addiu      $a0, $zero, 0x4C
.L8003C570:
/* 2CD70 8003C570 0780023C */  lui        $v0, %hi(D_800758CC)
/* 2CD74 8003C574 CC58428C */  lw         $v0, %lo(D_800758CC)($v0)
/* 2CD78 8003C578 00000000 */  nop
/* 2CD7C 8003C57C 09F84000 */  jalr       $v0
/* 2CD80 8003C580 21288002 */   addu      $a1, $s4, $zero
/* 2CD84 8003C584 21904000 */  addu       $s2, $v0, $zero
/* 2CD88 8003C588 0000428E */  lw         $v0, 0x0($s2)
/* 2CD8C 8003C58C FF00B132 */  andi       $s1, $s5, 0xFF
/* 2CD90 8003C590 000054AC */  sw         $s4, 0x0($v0)
/* 2CD94 8003C594 0000428E */  lw         $v0, 0x0($s2)
/* 2CD98 8003C598 00891100 */  sll        $s1, $s1, 4
/* 2CD9C 8003C59C 04005EA4 */  sh         $fp, 0x4($v0)
/* 2CDA0 8003C5A0 0000428E */  lw         $v0, 0x0($s2)
/* 2CDA4 8003C5A4 21202002 */  addu       $a0, $s1, $zero
/* 2CDA8 8003C5A8 2C5B000C */  jal        func_80016CB0
/* 2CDAC 8003C5AC 060053A4 */   sh        $s3, 0x6($v0)
/* 2CDB0 8003C5B0 1000A38F */  lw         $v1, 0x10($sp)
/* 2CDB4 8003C5B4 00000000 */  nop
/* 2CDB8 8003C5B8 18006200 */  mult       $v1, $v0
/* 2CDBC 8003C5BC 21202002 */  addu       $a0, $s1, $zero
/* 2CDC0 8003C5C0 12380000 */  mflo       $a3
/* 2CDC4 8003C5C4 2C5B000C */  jal        func_80016CB0
/* 2CDC8 8003C5C8 0C0047AE */   sw        $a3, 0xC($s2)
/* 2CDCC 8003C5CC 1400A38F */  lw         $v1, 0x14($sp)
/* 2CDD0 8003C5D0 00000000 */  nop
/* 2CDD4 8003C5D4 18006200 */  mult       $v1, $v0
/* 2CDD8 8003C5D8 0C005026 */  addiu      $s0, $s2, 0xC
/* 2CDDC 8003C5DC 21200002 */  addu       $a0, $s0, $zero
/* 2CDE0 8003C5E0 21280002 */  addu       $a1, $s0, $zero
/* 2CDE4 8003C5E4 4000A627 */  addiu      $a2, $sp, 0x40
/* 2CDE8 8003C5E8 140040AE */  sw         $zero, 0x14($s2)
/* 2CDEC 8003C5EC 12380000 */  mflo       $a3
/* 2CDF0 8003C5F0 E35D000C */  jal        VecSub
/* 2CDF4 8003C5F4 100047AE */   sw        $a3, 0x10($s2)
/* 2CDF8 8003C5F8 21200002 */  addu       $a0, $s0, $zero
/* 2CDFC 8003C5FC B25D000C */  jal        func_800176C8
/* 2CE00 8003C600 0A000524 */   addiu     $a1, $zero, 0xA
/* 2CE04 8003C604 21200002 */  addu       $a0, $s0, $zero
/* 2CE08 8003C608 21280002 */  addu       $a1, $s0, $zero
/* 2CE0C 8003C60C D65D000C */  jal        VecAdd
/* 2CE10 8003C610 1000A627 */   addiu     $a2, $sp, 0x10
/* 2CE14 8003C614 21200002 */  addu       $a0, $s0, $zero
/* 2CE18 8003C618 21280002 */  addu       $a1, $s0, $zero
/* 2CE1C 8003C61C D65D000C */  jal        VecAdd
/* 2CE20 8003C620 0C008626 */   addiu     $a2, $s4, 0xC
/* 2CE24 8003C624 21200002 */  addu       $a0, $s0, $zero
/* 2CE28 8003C628 21288000 */  addu       $a1, $a0, $zero
/* 2CE2C 8003C62C E35D000C */  jal        VecSub
/* 2CE30 8003C630 3000A627 */   addiu     $a2, $sp, 0x30
/* 2CE34 8003C634 2C5B000C */  jal        func_80016CB0
/* 2CE38 8003C638 21202002 */   addu      $a0, $s1, $zero
/* 2CE3C 8003C63C 40180200 */  sll        $v1, $v0, 1
/* 2CE40 8003C640 21186200 */  addu       $v1, $v1, $v0
/* 2CE44 8003C644 1400428E */  lw         $v0, 0x14($s2)
/* 2CE48 8003C648 C3180300 */  sra        $v1, $v1, 3
/* 2CE4C 8003C64C 21204300 */  addu       $a0, $v0, $v1
/* 2CE50 8003C650 36004386 */  lh         $v1, 0x36($s2)
/* 2CE54 8003C654 4C000224 */  addiu      $v0, $zero, 0x4C
/* 2CE58 8003C658 03006214 */  bne        $v1, $v0, .L8003C668
/* 2CE5C 8003C65C 140044AE */   sw        $a0, 0x14($s2)
/* 2CE60 8003C660 00018224 */  addiu      $v0, $a0, 0x100
/* 2CE64 8003C664 140042AE */  sw         $v0, 0x14($s2)
.L8003C668:
/* 2CE68 8003C668 FF00E232 */  andi       $v0, $s7, 0xFF
/* 2CE6C 8003C66C 460057A2 */  sb         $s7, 0x46($s2)
/* 2CE70 8003C670 380042A6 */  sh         $v0, 0x38($s2)
/* 2CE74 8003C674 49008392 */  lbu        $v1, 0x49($s4)
/* 2CE78 8003C678 C0101300 */  sll        $v0, $s3, 3
/* 2CE7C 8003C67C 490042A2 */  sb         $v0, 0x49($s2)
/* 2CE80 8003C680 02000224 */  addiu      $v0, $zero, 0x2
/* 2CE84 8003C684 4F0042A2 */  sb         $v0, 0x4F($s2)
/* 2CE88 8003C688 480043A2 */  sb         $v1, 0x48($s2)
.L8003C68C:
/* 2CE8C 8003C68C 3000A427 */  addiu      $a0, $sp, 0x30
/* 2CE90 8003C690 21288000 */  addu       $a1, $a0, $zero
/* 2CE94 8003C694 E35D000C */  jal        VecSub
/* 2CE98 8003C698 2000A627 */   addiu     $a2, $sp, 0x20
/* 2CE9C 8003C69C FCFFB526 */  addiu      $s5, $s5, -0x4
/* 2CEA0 8003C6A0 01007326 */  addiu      $s3, $s3, 0x1
/* 2CEA4 8003C6A4 2A107E02 */  slt        $v0, $s3, $fp
/* 2CEA8 8003C6A8 A6FF4014 */  bnez       $v0, .L8003C544
/* 2CEAC 8003C6AC 0100D626 */   addiu     $s6, $s6, 0x1
.L8003C6B0:
/* 2CEB0 8003C6B0 7C00BF8F */  lw         $ra, 0x7C($sp)
/* 2CEB4 8003C6B4 7800BE8F */  lw         $fp, 0x78($sp)
/* 2CEB8 8003C6B8 7400B78F */  lw         $s7, 0x74($sp)
/* 2CEBC 8003C6BC 7000B68F */  lw         $s6, 0x70($sp)
/* 2CEC0 8003C6C0 6C00B58F */  lw         $s5, 0x6C($sp)
/* 2CEC4 8003C6C4 6800B48F */  lw         $s4, 0x68($sp)
/* 2CEC8 8003C6C8 6400B38F */  lw         $s3, 0x64($sp)
/* 2CECC 8003C6CC 6000B28F */  lw         $s2, 0x60($sp)
/* 2CED0 8003C6D0 5C00B18F */  lw         $s1, 0x5C($sp)
/* 2CED4 8003C6D4 5800B08F */  lw         $s0, 0x58($sp)
/* 2CED8 8003C6D8 8000BD27 */  addiu      $sp, $sp, 0x80
/* 2CEDC 8003C6DC 0800E003 */  jr         $ra
/* 2CEE0 8003C6E0 00000000 */   nop
.size func_8003C358, . - func_8003C358
