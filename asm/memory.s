.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Generated by spimdisasm 1.27.0 */

/* Handwritten function */
glabel Memset
/* 7114 80016914 2030C400 */  add        $a2, $a2, $a0 /* handwritten instruction */
/* 7118 80016918 FCFFC620 */  addi       $a2, $a2, -0x4 /* handwritten instruction */
.L8001691C:
/* 711C 8001691C 000085AC */  sw         $a1, 0x0($a0)
/* 7120 80016920 FEFF8614 */  bne        $a0, $a2, .L8001691C
/* 7124 80016924 04008420 */   addi      $a0, $a0, 0x4 /* handwritten instruction */
/* 7128 80016928 0800E003 */  jr         $ra
/* 712C 8001692C 00000000 */   nop
.size Memset, . - Memset

/* Handwritten function */
glabel Memset16
/* 7130 80016930 2030C400 */  add        $a2, $a2, $a0 /* handwritten instruction */
/* 7134 80016934 F0FFC620 */  addi       $a2, $a2, -0x10 /* handwritten instruction */
.L80016938:
/* 7138 80016938 000085AC */  sw         $a1, 0x0($a0)
/* 713C 8001693C 040085AC */  sw         $a1, 0x4($a0)
/* 7140 80016940 080085AC */  sw         $a1, 0x8($a0)
/* 7144 80016944 0C0085AC */  sw         $a1, 0xC($a0)
/* 7148 80016948 FBFF8614 */  bne        $a0, $a2, .L80016938
/* 714C 8001694C 10008420 */   addi      $a0, $a0, 0x10 /* handwritten instruction */
/* 7150 80016950 0800E003 */  jr         $ra
/* 7154 80016954 00000000 */   nop
.size Memset16, . - Memset16

/* Handwritten function */
glabel Memcpy
/* 7158 80016958 2030C400 */  add        $a2, $a2, $a0 /* handwritten instruction */
/* 715C 8001695C FCFFC620 */  addi       $a2, $a2, -0x4 /* handwritten instruction */
.L80016960:
/* 7160 80016960 0000AA8C */  lw         $t2, 0x0($a1)
/* 7164 80016964 0400AB8C */  lw         $t3, 0x4($a1)
/* 7168 80016968 0800AC8C */  lw         $t4, 0x8($a1)
/* 716C 8001696C 0C00AD8C */  lw         $t5, 0xC($a1)
/* 7170 80016970 00008AAC */  sw         $t2, 0x0($a0)
/* 7174 80016974 1000A520 */  addi       $a1, $a1, 0x10 /* handwritten instruction */
/* 7178 80016978 0A008610 */  beq        $a0, $a2, .L800169A4
/* 717C 8001697C 04008420 */   addi      $a0, $a0, 0x4 /* handwritten instruction */
/* 7180 80016980 00008BAC */  sw         $t3, 0x0($a0)
/* 7184 80016984 07008610 */  beq        $a0, $a2, .L800169A4
/* 7188 80016988 04008420 */   addi      $a0, $a0, 0x4 /* handwritten instruction */
/* 718C 8001698C 00008CAC */  sw         $t4, 0x0($a0)
/* 7190 80016990 04008610 */  beq        $a0, $a2, .L800169A4
/* 7194 80016994 04008420 */   addi      $a0, $a0, 0x4 /* handwritten instruction */
/* 7198 80016998 00008DAC */  sw         $t5, 0x0($a0)
/* 719C 8001699C F0FF8614 */  bne        $a0, $a2, .L80016960
/* 71A0 800169A0 04008420 */   addi      $a0, $a0, 0x4 /* handwritten instruction */
.L800169A4:
/* 71A4 800169A4 0800E003 */  jr         $ra
/* 71A8 800169A8 00000000 */   nop
.size Memcpy, . - Memcpy
