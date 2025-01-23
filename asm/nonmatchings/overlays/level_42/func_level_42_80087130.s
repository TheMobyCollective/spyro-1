.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_level_42_80087130
/* 3A7A6F8 80087130 0800E003 */  jr         $ra
/* 3A7A6FC 80087134 00000000 */   nop
.size func_level_42_80087130, . - func_level_42_80087130
