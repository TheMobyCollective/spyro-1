.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80019698
/* 9E98 80019698 E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 9E9C 8001969C 1000BFAF */  sw         $ra, 0x10($sp)
/* 9EA0 800196A0 567C000C */  jal        func_8001F158
/* 9EA4 800196A4 00000000 */   nop
/* 9EA8 800196A8 0780043C */  lui        $a0, %hi(D_8006FCF4)
/* 9EAC 800196AC F4FC8424 */  addiu      $a0, $a0, %lo(D_8006FCF4)
/* 9EB0 800196B0 21280000 */  addu       $a1, $zero, $zero
/* 9EB4 800196B4 455A000C */  jal        Memset
/* 9EB8 800196B8 00090624 */   addiu     $a2, $zero, 0x900
/* 9EBC 800196BC E67D000C */  jal        func_8001F798
/* 9EC0 800196C0 00000000 */   nop
/* 9EC4 800196C4 3F82000C */  jal        func_800208FC
/* 9EC8 800196C8 00000000 */   nop
/* 9ECC 800196CC CD83000C */  jal        func_80020F34
/* 9ED0 800196D0 00000000 */   nop
/* 9ED4 800196D4 8B8A000C */  jal        func_80022A2C
/* 9ED8 800196D8 00000000 */   nop
/* 9EDC 800196DC E367010C */  jal        func_80059F8C
/* 9EE0 800196E0 00000000 */   nop
/* 9EE4 800196E4 0780023C */  lui        $v0, %hi(D_80075814)
/* 9EE8 800196E8 1458428C */  lw         $v0, %lo(D_80075814)($v0)
/* 9EEC 800196EC 00000000 */  nop
/* 9EF0 800196F0 05004014 */  bnez       $v0, .L80019708
/* 9EF4 800196F4 00000000 */   nop
/* 9EF8 800196F8 B18E000C */  jal        func_80023AC4
/* 9EFC 800196FC 00000000 */   nop
/* 9F00 80019700 9266010C */  jal        func_80059A48
/* 9F04 80019704 00000000 */   nop
.L80019708:
/* 9F08 80019708 0880023C */  lui        $v0, %hi(D_80078760)
/* 9F0C 8001970C 60874290 */  lbu        $v0, %lo(D_80078760)($v0)
/* 9F10 80019710 00000000 */  nop
/* 9F14 80019714 03004010 */  beqz       $v0, .L80019724
/* 9F18 80019718 00000000 */   nop
/* 9F1C 8001971C 5963010C */  jal        func_80058D64
/* 9F20 80019720 00000000 */   nop
.L80019724:
/* 9F24 80019724 EA62010C */  jal        func_80058BA8
/* 9F28 80019728 00000000 */   nop
/* 9F2C 8001972C 1000BF8F */  lw         $ra, 0x10($sp)
/* 9F30 80019730 1800BD27 */  addiu      $sp, $sp, 0x18
/* 9F34 80019734 0800E003 */  jr         $ra
/* 9F38 80019738 00000000 */   nop
.size func_80019698, . - func_80019698
