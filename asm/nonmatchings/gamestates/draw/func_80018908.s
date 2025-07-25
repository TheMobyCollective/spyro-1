.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

.section .rodata
.align 2
dlabel D_80010AC0
/* 12C0 80010AC0 */ .asciz "DEMO MODE"
.align 2
.size D_80010AC0, . - D_80010AC0


.section .text
/* Generated by spimdisasm 1.27.0 */

glabel func_80018908
/* 9108 80018908 C0FFBD27 */  addiu      $sp, $sp, -0x40
/* 910C 8001890C 10000224 */  addiu      $v0, $zero, 0x10
/* 9110 80018910 2800A2AF */  sw         $v0, 0x28($sp)
/* 9114 80018914 01000224 */  addiu      $v0, $zero, 0x1
/* 9118 80018918 2C00A2AF */  sw         $v0, 0x2C($sp)
/* 911C 8001891C 00140224 */  addiu      $v0, $zero, 0x1400
/* 9120 80018920 3000A2AF */  sw         $v0, 0x30($sp)
/* 9124 80018924 C7000224 */  addiu      $v0, $zero, 0xC7
/* 9128 80018928 1800A2AF */  sw         $v0, 0x18($sp)
/* 912C 8001892C C8000224 */  addiu      $v0, $zero, 0xC8
/* 9130 80018930 1C00A2AF */  sw         $v0, 0x1C($sp)
/* 9134 80018934 00110224 */  addiu      $v0, $zero, 0x1100
/* 9138 80018938 2000A2AF */  sw         $v0, 0x20($sp)
/* 913C 8001893C 02000224 */  addiu      $v0, $zero, 0x2
/* 9140 80018940 0180043C */  lui        $a0, %hi(D_80010AC0)
/* 9144 80018944 C00A8424 */  addiu      $a0, $a0, %lo(D_80010AC0)
/* 9148 80018948 1800A527 */  addiu      $a1, $sp, 0x18
/* 914C 8001894C 2800A627 */  addiu      $a2, $sp, 0x28
/* 9150 80018950 3800B0AF */  sw         $s0, 0x38($sp)
/* 9154 80018954 0780103C */  lui        $s0, %hi(g_HudMobys)
/* 9158 80018958 1057108E */  lw         $s0, %lo(g_HudMobys)($s0)
/* 915C 8001895C 12000724 */  addiu      $a3, $zero, 0x12
/* 9160 80018960 3C00BFAF */  sw         $ra, 0x3C($sp)
/* 9164 80018964 6B60000C */  jal        func_800181AC
/* 9168 80018968 1000A2AF */   sw        $v0, 0x10($sp)
/* 916C 8001896C 0780023C */  lui        $v0, %hi(g_HudMobys)
/* 9170 80018970 1057428C */  lw         $v0, %lo(g_HudMobys)($v0)
/* 9174 80018974 A8FF1026 */  addiu      $s0, $s0, -0x58
/* 9178 80018978 2A100202 */  slt        $v0, $s0, $v0
/* 917C 8001897C 15004014 */  bnez       $v0, .L800189D4
/* 9180 80018980 21180000 */   addu      $v1, $zero, $zero
/* 9184 80018984 0780043C */  lui        $a0, %hi(D_8006CC78)
/* 9188 80018988 78CC8424 */  addiu      $a0, $a0, %lo(D_8006CC78)
.L8001898C:
/* 918C 8001898C 0780023C */  lui        $v0, %hi(D_800758C8)
/* 9190 80018990 C858428C */  lw         $v0, %lo(D_800758C8)($v0)
/* 9194 80018994 00000000 */  nop
/* 9198 80018998 80100200 */  sll        $v0, $v0, 2
/* 919C 8001899C 21104300 */  addu       $v0, $v0, $v1
/* 91A0 800189A0 FF004230 */  andi       $v0, $v0, 0xFF
/* 91A4 800189A4 40100200 */  sll        $v0, $v0, 1
/* 91A8 800189A8 21104400 */  addu       $v0, $v0, $a0
/* 91AC 800189AC 00004294 */  lhu        $v0, 0x0($v0)
/* 91B0 800189B0 00000000 */  nop
/* 91B4 800189B4 C2110200 */  srl        $v0, $v0, 7
/* 91B8 800189B8 460002A2 */  sb         $v0, 0x46($s0)
/* 91BC 800189BC 0780023C */  lui        $v0, %hi(g_HudMobys)
/* 91C0 800189C0 1057428C */  lw         $v0, %lo(g_HudMobys)($v0)
/* 91C4 800189C4 A8FF1026 */  addiu      $s0, $s0, -0x58
/* 91C8 800189C8 2A100202 */  slt        $v0, $s0, $v0
/* 91CC 800189CC EFFF4010 */  beqz       $v0, .L8001898C
/* 91D0 800189D0 0C006324 */   addiu     $v1, $v1, 0xC
.L800189D4:
/* 91D4 800189D4 2062000C */  jal        func_80018880
/* 91D8 800189D8 00000000 */   nop
/* 91DC 800189DC 3C00BF8F */  lw         $ra, 0x3C($sp)
/* 91E0 800189E0 3800B08F */  lw         $s0, 0x38($sp)
/* 91E4 800189E4 4000BD27 */  addiu      $sp, $sp, 0x40
/* 91E8 800189E8 0800E003 */  jr         $ra
/* 91EC 800189EC 00000000 */   nop
.size func_80018908, . - func_80018908
