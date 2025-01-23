.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8001860C
/* 8E0C 8001860C D0FFBD27 */  addiu      $sp, $sp, -0x30
/* 8E10 80018610 2800B4AF */  sw         $s4, 0x28($sp)
/* 8E14 80018614 21A08000 */  addu       $s4, $a0, $zero
/* 8E18 80018618 1C00B1AF */  sw         $s1, 0x1C($sp)
/* 8E1C 8001861C 2188A000 */  addu       $s1, $a1, $zero
/* 8E20 80018620 2400B3AF */  sw         $s3, 0x24($sp)
/* 8E24 80018624 2198C000 */  addu       $s3, $a2, $zero
/* 8E28 80018628 2000B2AF */  sw         $s2, 0x20($sp)
/* 8E2C 8001862C 2190E000 */  addu       $s2, $a3, $zero
/* 8E30 80018630 01000524 */  addiu      $a1, $zero, 0x1
/* 8E34 80018634 21300000 */  addu       $a2, $zero, $zero
/* 8E38 80018638 1800B0AF */  sw         $s0, 0x18($sp)
/* 8E3C 8001863C 0780103C */  lui        $s0, %hi(D_800757B0)
/* 8E40 80018640 B057108E */  lw         $s0, %lo(D_800757B0)($s0)
/* 8E44 80018644 40000724 */  addiu      $a3, $zero, 0x40
/* 8E48 80018648 2C00BFAF */  sw         $ra, 0x2C($sp)
/* 8E4C 8001864C 1000A0AF */  sw         $zero, 0x10($sp)
/* 8E50 80018650 9C81010C */  jal        SetDrawMode
/* 8E54 80018654 21200002 */   addu      $a0, $s0, $zero
/* 8E58 80018658 375A000C */  jal        func_800168DC
/* 8E5C 8001865C 21200002 */   addu      $a0, $s0, $zero
/* 8E60 80018660 0C000426 */  addiu      $a0, $s0, 0xC
/* 8E64 80018664 0005023C */  lui        $v0, (0x5000000 >> 16)
/* 8E68 80018668 0C0002AE */  sw         $v0, 0xC($s0)
/* 8E6C 8001866C 2A000224 */  addiu      $v0, $zero, 0x2A
/* 8E70 80018670 130002A2 */  sb         $v0, 0x13($s0)
/* 8E74 80018674 70000224 */  addiu      $v0, $zero, 0x70
/* 8E78 80018678 140014A6 */  sh         $s4, 0x14($s0)
/* 8E7C 8001867C 180011A6 */  sh         $s1, 0x18($s0)
/* 8E80 80018680 1C0014A6 */  sh         $s4, 0x1C($s0)
/* 8E84 80018684 200011A6 */  sh         $s1, 0x20($s0)
/* 8E88 80018688 160013A6 */  sh         $s3, 0x16($s0)
/* 8E8C 8001868C 1A0013A6 */  sh         $s3, 0x1A($s0)
/* 8E90 80018690 1E0012A6 */  sh         $s2, 0x1E($s0)
/* 8E94 80018694 220012A6 */  sh         $s2, 0x22($s0)
/* 8E98 80018698 100002A2 */  sb         $v0, 0x10($s0)
/* 8E9C 8001869C 110002A2 */  sb         $v0, 0x11($s0)
/* 8EA0 800186A0 375A000C */  jal        func_800168DC
/* 8EA4 800186A4 120002A2 */   sb        $v0, 0x12($s0)
/* 8EA8 800186A8 21208002 */  addu       $a0, $s4, $zero
/* 8EAC 800186AC 21286002 */  addu       $a1, $s3, $zero
/* 8EB0 800186B0 21302002 */  addu       $a2, $s1, $zero
/* 8EB4 800186B4 24001026 */  addiu      $s0, $s0, 0x24
/* 8EB8 800186B8 0780013C */  lui        $at, %hi(D_800757B0)
/* 8EBC 800186BC B05730AC */  sw         $s0, %lo(D_800757B0)($at)
/* 8EC0 800186C0 1361000C */  jal        func_8001844C
/* 8EC4 800186C4 21386002 */   addu      $a3, $s3, $zero
/* 8EC8 800186C8 21202002 */  addu       $a0, $s1, $zero
/* 8ECC 800186CC 21286002 */  addu       $a1, $s3, $zero
/* 8ED0 800186D0 21302002 */  addu       $a2, $s1, $zero
/* 8ED4 800186D4 1361000C */  jal        func_8001844C
/* 8ED8 800186D8 21384002 */   addu      $a3, $s2, $zero
/* 8EDC 800186DC 21202002 */  addu       $a0, $s1, $zero
/* 8EE0 800186E0 21284002 */  addu       $a1, $s2, $zero
/* 8EE4 800186E4 21308002 */  addu       $a2, $s4, $zero
/* 8EE8 800186E8 1361000C */  jal        func_8001844C
/* 8EEC 800186EC 21384002 */   addu      $a3, $s2, $zero
/* 8EF0 800186F0 21208002 */  addu       $a0, $s4, $zero
/* 8EF4 800186F4 21284002 */  addu       $a1, $s2, $zero
/* 8EF8 800186F8 21308000 */  addu       $a2, $a0, $zero
/* 8EFC 800186FC 1361000C */  jal        func_8001844C
/* 8F00 80018700 21386002 */   addu      $a3, $s3, $zero
/* 8F04 80018704 2C00BF8F */  lw         $ra, 0x2C($sp)
/* 8F08 80018708 2800B48F */  lw         $s4, 0x28($sp)
/* 8F0C 8001870C 2400B38F */  lw         $s3, 0x24($sp)
/* 8F10 80018710 2000B28F */  lw         $s2, 0x20($sp)
/* 8F14 80018714 1C00B18F */  lw         $s1, 0x1C($sp)
/* 8F18 80018718 1800B08F */  lw         $s0, 0x18($sp)
/* 8F1C 8001871C 3000BD27 */  addiu      $sp, $sp, 0x30
/* 8F20 80018720 0800E003 */  jr         $ra
/* 8F24 80018724 00000000 */   nop
.size func_8001860C, . - func_8001860C
