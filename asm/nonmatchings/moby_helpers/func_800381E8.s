.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_800381E8
/* 289E8 800381E8 E0FFBD27 */  addiu      $sp, $sp, -0x20
/* 289EC 800381EC 1000B0AF */  sw         $s0, 0x10($sp)
/* 289F0 800381F0 21808000 */  addu       $s0, $a0, $zero
/* 289F4 800381F4 1400B1AF */  sw         $s1, 0x14($sp)
/* 289F8 800381F8 2188A000 */  addu       $s1, $a1, $zero
/* 289FC 800381FC 0880033C */  lui        $v1, %hi(g_Spyro)
/* 28A00 80038200 588A638C */  lw         $v1, %lo(g_Spyro)($v1)
/* 28A04 80038204 21300000 */  addu       $a2, $zero, $zero
/* 28A08 80038208 1800BFAF */  sw         $ra, 0x18($sp)
/* 28A0C 8003820C 0C00048E */  lw         $a0, 0xC($s0)
/* 28A10 80038210 0880023C */  lui        $v0, %hi(g_Spyro + 0x4)
/* 28A14 80038214 5C8A428C */  lw         $v0, %lo(g_Spyro + 0x4)($v0)
/* 28A18 80038218 1000058E */  lw         $a1, 0x10($s0)
/* 28A1C 8003821C 23206400 */  subu       $a0, $v1, $a0
/* 28A20 80038220 AD5A000C */  jal        func_80016AB4
/* 28A24 80038224 23284500 */   subu      $a1, $v0, $a1
/* 28A28 80038228 46000592 */  lbu        $a1, 0x46($s0)
/* 28A2C 8003822C 425E000C */  jal        func_80017908
/* 28A30 80038230 21204000 */   addu      $a0, $v0, $zero
/* 28A34 80038234 2A105100 */  slt        $v0, $v0, $s1
/* 28A38 80038238 1800BF8F */  lw         $ra, 0x18($sp)
/* 28A3C 8003823C 1400B18F */  lw         $s1, 0x14($sp)
/* 28A40 80038240 1000B08F */  lw         $s0, 0x10($sp)
/* 28A44 80038244 2000BD27 */  addiu      $sp, $sp, 0x20
/* 28A48 80038248 0800E003 */  jr         $ra
/* 28A4C 8003824C 00000000 */   nop
.size func_800381E8, . - func_800381E8
