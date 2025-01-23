.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_titlescreen_8007CD38
/* 5DB00 8007CD38 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 5DB04 8007CD3C 21188000 */  addu       $v1, $a0, $zero
/* 5DB08 8007CD40 1400B1AF */  sw         $s1, 0x14($sp)
/* 5DB0C 8007CD44 21880000 */  addu       $s1, $zero, $zero
/* 5DB10 8007CD48 1800BFAF */  sw         $ra, 0x18($sp)
/* 5DB14 8007CD4C 0300C104 */  bgez       $a2, .Ltitlescreen_8007CD5C
/* 5DB18 8007CD50 1000B0AF */   sw        $s0, 0x10($sp)
/* 5DB1C 8007CD54 01001124 */  addiu      $s1, $zero, 0x1
/* 5DB20 8007CD58 23300600 */  negu       $a2, $a2
.Ltitlescreen_8007CD5C:
/* 5DB24 8007CD5C 0780103C */  lui        $s0, %hi(D_800757B0)
/* 5DB28 8007CD60 B057108E */  lw         $s0, %lo(D_800757B0)($s0)
/* 5DB2C 8007CD64 0009023C */  lui        $v0, (0x9000000 >> 16)
/* 5DB30 8007CD68 000002AE */  sw         $v0, 0x0($s0)
/* 5DB34 8007CD6C 80100700 */  sll        $v0, $a3, 2
/* 5DB38 8007CD70 0780013C */  lui        $at, %hi(D_8006FA74 + 0x48)
/* 5DB3C 8007CD74 21082200 */  addu       $at, $at, $v0
/* 5DB40 8007CD78 BCFA228C */  lw         $v0, %lo(D_8006FA74 + 0x48)($at)
/* 5DB44 8007CD7C C0200600 */  sll        $a0, $a2, 3
/* 5DB48 8007CD80 080003A6 */  sh         $v1, 0x8($s0)
/* 5DB4C 8007CD84 0A0005A6 */  sh         $a1, 0xA($s0)
/* 5DB50 8007CD88 040002AE */  sw         $v0, 0x4($s0)
/* 5DB54 8007CD8C 0780013C */  lui        $at, %hi(D_8006FA74 + 0x5C)
/* 5DB58 8007CD90 21082400 */  addu       $at, $at, $a0
/* 5DB5C 8007CD94 D0FA2290 */  lbu        $v0, %lo(D_8006FA74 + 0x5C)($at)
/* 5DB60 8007CD98 120005A6 */  sh         $a1, 0x12($s0)
/* 5DB64 8007CD9C 180003A6 */  sh         $v1, 0x18($s0)
/* 5DB68 8007CDA0 21104300 */  addu       $v0, $v0, $v1
/* 5DB6C 8007CDA4 100002A6 */  sh         $v0, 0x10($s0)
/* 5DB70 8007CDA8 0780013C */  lui        $at, %hi(D_8006FA74 + 0x5D)
/* 5DB74 8007CDAC 21082400 */  addu       $at, $at, $a0
/* 5DB78 8007CDB0 D1FA2290 */  lbu        $v0, %lo(D_8006FA74 + 0x5D)($at)
/* 5DB7C 8007CDB4 00000000 */  nop
/* 5DB80 8007CDB8 21104500 */  addu       $v0, $v0, $a1
/* 5DB84 8007CDBC 1A0002A6 */  sh         $v0, 0x1A($s0)
/* 5DB88 8007CDC0 0780013C */  lui        $at, %hi(D_8006FA74 + 0x5C)
/* 5DB8C 8007CDC4 21082400 */  addu       $at, $at, $a0
/* 5DB90 8007CDC8 D0FA2290 */  lbu        $v0, %lo(D_8006FA74 + 0x5C)($at)
/* 5DB94 8007CDCC 00000000 */  nop
/* 5DB98 8007CDD0 21104300 */  addu       $v0, $v0, $v1
/* 5DB9C 8007CDD4 200002A6 */  sh         $v0, 0x20($s0)
/* 5DBA0 8007CDD8 0780013C */  lui        $at, %hi(D_8006FA74 + 0x5D)
/* 5DBA4 8007CDDC 21082400 */  addu       $at, $at, $a0
/* 5DBA8 8007CDE0 D1FA2290 */  lbu        $v0, %lo(D_8006FA74 + 0x5D)($at)
/* 5DBAC 8007CDE4 00000000 */  nop
/* 5DBB0 8007CDE8 21104500 */  addu       $v0, $v0, $a1
/* 5DBB4 8007CDEC 220002A6 */  sh         $v0, 0x22($s0)
/* 5DBB8 8007CDF0 0780013C */  lui        $at, %hi(D_8006FA74 + 0x5E)
/* 5DBBC 8007CDF4 21082400 */  addu       $at, $at, $a0
/* 5DBC0 8007CDF8 D2FA2290 */  lbu        $v0, %lo(D_8006FA74 + 0x5E)($at)
/* 5DBC4 8007CDFC 00000000 */  nop
/* 5DBC8 8007CE00 0C0002A2 */  sb         $v0, 0xC($s0)
/* 5DBCC 8007CE04 0780013C */  lui        $at, %hi(D_8006FA74 + 0x5F)
/* 5DBD0 8007CE08 21082400 */  addu       $at, $at, $a0
/* 5DBD4 8007CE0C D3FA2290 */  lbu        $v0, %lo(D_8006FA74 + 0x5F)($at)
/* 5DBD8 8007CE10 00000000 */  nop
/* 5DBDC 8007CE14 0D0002A2 */  sb         $v0, 0xD($s0)
/* 5DBE0 8007CE18 0C000292 */  lbu        $v0, 0xC($s0)
/* 5DBE4 8007CE1C 0780013C */  lui        $at, %hi(D_8006FA74 + 0x5C)
/* 5DBE8 8007CE20 21082400 */  addu       $at, $at, $a0
/* 5DBEC 8007CE24 D0FA2590 */  lbu        $a1, %lo(D_8006FA74 + 0x5C)($at)
/* 5DBF0 8007CE28 0D000392 */  lbu        $v1, 0xD($s0)
/* 5DBF4 8007CE2C 1C0002A2 */  sb         $v0, 0x1C($s0)
/* 5DBF8 8007CE30 0C000292 */  lbu        $v0, 0xC($s0)
/* 5DBFC 8007CE34 150003A2 */  sb         $v1, 0x15($s0)
/* 5DC00 8007CE38 21104500 */  addu       $v0, $v0, $a1
/* 5DC04 8007CE3C 140002A2 */  sb         $v0, 0x14($s0)
/* 5DC08 8007CE40 0D000292 */  lbu        $v0, 0xD($s0)
/* 5DC0C 8007CE44 0780013C */  lui        $at, %hi(D_8006FA74 + 0x5D)
/* 5DC10 8007CE48 21082400 */  addu       $at, $at, $a0
/* 5DC14 8007CE4C D1FA2390 */  lbu        $v1, %lo(D_8006FA74 + 0x5D)($at)
/* 5DC18 8007CE50 00000000 */  nop
/* 5DC1C 8007CE54 21104300 */  addu       $v0, $v0, $v1
/* 5DC20 8007CE58 1D0002A2 */  sb         $v0, 0x1D($s0)
/* 5DC24 8007CE5C 14000292 */  lbu        $v0, 0x14($s0)
/* 5DC28 8007CE60 1D000392 */  lbu        $v1, 0x1D($s0)
/* 5DC2C 8007CE64 240002A2 */  sb         $v0, 0x24($s0)
/* 5DC30 8007CE68 250003A2 */  sb         $v1, 0x25($s0)
/* 5DC34 8007CE6C 0780013C */  lui        $at, %hi(D_8006FA74 + 0x58)
/* 5DC38 8007CE70 21082400 */  addu       $at, $at, $a0
/* 5DC3C 8007CE74 CCFA2294 */  lhu        $v0, %lo(D_8006FA74 + 0x58)($at)
/* 5DC40 8007CE78 00000000 */  nop
/* 5DC44 8007CE7C 160002A6 */  sh         $v0, 0x16($s0)
/* 5DC48 8007CE80 0780013C */  lui        $at, %hi(D_8006FA74 + 0x5A)
/* 5DC4C 8007CE84 21082400 */  addu       $at, $at, $a0
/* 5DC50 8007CE88 CEFA2294 */  lhu        $v0, %lo(D_8006FA74 + 0x5A)($at)
/* 5DC54 8007CE8C 21200002 */  addu       $a0, $s0, $zero
/* 5DC58 8007CE90 375A000C */  jal        func_800168DC
/* 5DC5C 8007CE94 0E0002A6 */   sh        $v0, 0xE($s0)
/* 5DC60 8007CE98 28000226 */  addiu      $v0, $s0, 0x28
/* 5DC64 8007CE9C 0780013C */  lui        $at, %hi(D_800757B0)
/* 5DC68 8007CEA0 B05722AC */  sw         $v0, %lo(D_800757B0)($at)
/* 5DC6C 8007CEA4 09002012 */  beqz       $s1, .Ltitlescreen_8007CECC
/* 5DC70 8007CEA8 00000000 */   nop
/* 5DC74 8007CEAC 14000292 */  lbu        $v0, 0x14($s0)
/* 5DC78 8007CEB0 1C000392 */  lbu        $v1, 0x1C($s0)
/* 5DC7C 8007CEB4 0C0002A2 */  sb         $v0, 0xC($s0)
/* 5DC80 8007CEB8 0C000292 */  lbu        $v0, 0xC($s0)
/* 5DC84 8007CEBC 140003A2 */  sb         $v1, 0x14($s0)
/* 5DC88 8007CEC0 14000392 */  lbu        $v1, 0x14($s0)
/* 5DC8C 8007CEC4 1C0002A2 */  sb         $v0, 0x1C($s0)
/* 5DC90 8007CEC8 240003A2 */  sb         $v1, 0x24($s0)
.Ltitlescreen_8007CECC:
/* 5DC94 8007CECC 1800BF8F */  lw         $ra, 0x18($sp)
/* 5DC98 8007CED0 1400B18F */  lw         $s1, 0x14($sp)
/* 5DC9C 8007CED4 1000B08F */  lw         $s0, 0x10($sp)
/* 5DCA0 8007CED8 2000BD27 */  addiu      $sp, $sp, 0x20
/* 5DCA4 8007CEDC 0800E003 */  jr         $ra
/* 5DCA8 8007CEE0 00000000 */   nop
.size func_titlescreen_8007CD38, . - func_titlescreen_8007CD38
