.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003A79C
/* 2AF9C 8003A79C D8FFBD27 */  addiu      $sp, $sp, -0x28
/* 2AFA0 8003A7A0 2400BFAF */  sw         $ra, 0x24($sp)
/* 2AFA4 8003A7A4 2000B0AF */  sw         $s0, 0x20($sp)
/* 2AFA8 8003A7A8 0100A290 */  lbu        $v0, 0x1($a1)
/* 2AFAC 8003A7AC 0C00838C */  lw         $v1, 0xC($a0)
/* 2AFB0 8003A7B0 00110200 */  sll        $v0, $v0, 4
/* 2AFB4 8003A7B4 2110A200 */  addu       $v0, $a1, $v0
/* 2AFB8 8003A7B8 0800428C */  lw         $v0, 0x8($v0)
/* 2AFBC 8003A7BC 00000000 */  nop
/* 2AFC0 8003A7C0 23104300 */  subu       $v0, $v0, $v1
/* 2AFC4 8003A7C4 1000A2AF */  sw         $v0, 0x10($sp)
/* 2AFC8 8003A7C8 0100A290 */  lbu        $v0, 0x1($a1)
/* 2AFCC 8003A7CC 1000838C */  lw         $v1, 0x10($a0)
/* 2AFD0 8003A7D0 00110200 */  sll        $v0, $v0, 4
/* 2AFD4 8003A7D4 2110A200 */  addu       $v0, $a1, $v0
/* 2AFD8 8003A7D8 0C00428C */  lw         $v0, 0xC($v0)
/* 2AFDC 8003A7DC 2180C000 */  addu       $s0, $a2, $zero
/* 2AFE0 8003A7E0 23104300 */  subu       $v0, $v0, $v1
/* 2AFE4 8003A7E4 1400A2AF */  sw         $v0, 0x14($sp)
/* 2AFE8 8003A7E8 0100A290 */  lbu        $v0, 0x1($a1)
/* 2AFEC 8003A7EC 1400838C */  lw         $v1, 0x14($a0)
/* 2AFF0 8003A7F0 1000A427 */  addiu      $a0, $sp, 0x10
/* 2AFF4 8003A7F4 00110200 */  sll        $v0, $v0, 4
/* 2AFF8 8003A7F8 2128A200 */  addu       $a1, $a1, $v0
/* 2AFFC 8003A7FC 1000A28C */  lw         $v0, 0x10($a1)
/* 2B000 8003A800 01000524 */  addiu      $a1, $zero, 0x1
/* 2B004 8003A804 23104300 */  subu       $v0, $v0, $v1
/* 2B008 8003A808 7F5C000C */  jal        func_800171FC
/* 2B00C 8003A80C 1800A2AF */   sw        $v0, 0x18($sp)
/* 2B010 8003A810 1A005000 */  div        $zero, $v0, $s0
/* 2B014 8003A814 02000016 */  bnez       $s0, .L8003A820
/* 2B018 8003A818 00000000 */   nop
/* 2B01C 8003A81C 0D000700 */  break      7
.L8003A820:
/* 2B020 8003A820 FFFF0124 */  addiu      $at, $zero, -0x1
/* 2B024 8003A824 04000116 */  bne        $s0, $at, .L8003A838
/* 2B028 8003A828 0080013C */   lui       $at, (0x80000000 >> 16)
/* 2B02C 8003A82C 02004114 */  bne        $v0, $at, .L8003A838
/* 2B030 8003A830 00000000 */   nop
/* 2B034 8003A834 0D000600 */  break      6
.L8003A838:
/* 2B038 8003A838 12100000 */  mflo       $v0
/* 2B03C 8003A83C 2400BF8F */  lw         $ra, 0x24($sp)
/* 2B040 8003A840 2000B08F */  lw         $s0, 0x20($sp)
/* 2B044 8003A844 2800BD27 */  addiu      $sp, $sp, 0x28
/* 2B048 8003A848 0800E003 */  jr         $ra
/* 2B04C 8003A84C 00000000 */   nop
.size func_8003A79C, . - func_8003A79C
