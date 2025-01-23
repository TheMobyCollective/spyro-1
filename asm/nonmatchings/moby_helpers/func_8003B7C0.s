.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003B7C0
/* 2BFC0 8003B7C0 0780033C */  lui        $v1, %hi(D_80075828)
/* 2BFC4 8003B7C4 2858638C */  lw         $v1, %lo(D_80075828)($v1)
/* 2BFC8 8003B7C8 00000000 */  nop
/* 2BFCC 8003B7CC 2B108300 */  sltu       $v0, $a0, $v1
/* 2BFD0 8003B7D0 1E004014 */  bnez       $v0, .L8003B84C
/* 2BFD4 8003B7D4 00000000 */   nop
/* 2BFD8 8003B7D8 0780023C */  lui        $v0, %hi(D_80075890)
/* 2BFDC 8003B7DC 9058428C */  lw         $v0, %lo(D_80075890)($v0)
/* 2BFE0 8003B7E0 00000000 */  nop
/* 2BFE4 8003B7E4 2B108200 */  sltu       $v0, $a0, $v0
/* 2BFE8 8003B7E8 18004010 */  beqz       $v0, .L8003B84C
/* 2BFEC 8003B7EC 23208300 */   subu      $a0, $a0, $v1
/* 2BFF0 8003B7F0 40110400 */  sll        $v0, $a0, 5
/* 2BFF4 8003B7F4 23104400 */  subu       $v0, $v0, $a0
/* 2BFF8 8003B7F8 40110200 */  sll        $v0, $v0, 5
/* 2BFFC 8003B7FC 21104400 */  addu       $v0, $v0, $a0
/* 2C000 8003B800 C0180200 */  sll        $v1, $v0, 3
/* 2C004 8003B804 21104300 */  addu       $v0, $v0, $v1
/* 2C008 8003B808 C01B0200 */  sll        $v1, $v0, 15
/* 2C00C 8003B80C 23186200 */  subu       $v1, $v1, $v0
/* 2C010 8003B810 80180300 */  sll        $v1, $v1, 2
/* 2C014 8003B814 21186400 */  addu       $v1, $v1, $a0
/* 2C018 8003B818 23180300 */  negu       $v1, $v1
/* 2C01C 8003B81C C3280300 */  sra        $a1, $v1, 3
/* 2C020 8003B820 031A0300 */  sra        $v1, $v1, 8
/* 2C024 8003B824 1F00A530 */  andi       $a1, $a1, 0x1F
/* 2C028 8003B828 0780023C */  lui        $v0, %hi(D_800778B8)
/* 2C02C 8003B82C B8784224 */  addiu      $v0, $v0, %lo(D_800778B8)
/* 2C030 8003B830 80180300 */  sll        $v1, $v1, 2
/* 2C034 8003B834 21186200 */  addu       $v1, $v1, $v0
/* 2C038 8003B838 01000224 */  addiu      $v0, $zero, 0x1
/* 2C03C 8003B83C 0000648C */  lw         $a0, 0x0($v1)
/* 2C040 8003B840 0410A200 */  sllv       $v0, $v0, $a1
/* 2C044 8003B844 25208200 */  or         $a0, $a0, $v0
/* 2C048 8003B848 000064AC */  sw         $a0, 0x0($v1)
.L8003B84C:
/* 2C04C 8003B84C 0800E003 */  jr         $ra
/* 2C050 8003B850 00000000 */   nop
.size func_8003B7C0, . - func_8003B7C0
